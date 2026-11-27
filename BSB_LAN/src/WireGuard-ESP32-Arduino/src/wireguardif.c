/*
 * Ported to ESP32 Arduino by Kenta Ida (fuga@fugafuga.org)
 * The original license is below:
 * 
 * Copyright (c) 2021 Daniel Hope (www.floorsense.nz)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *  list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this
 *  list of conditions and the following disclaimer in the documentation and/or
 *  other materials provided with the distribution.
 *
 * 3. Neither the name of "Floorsense Ltd", "Agile Workspace Ltd" nor the names of
 *  its contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Daniel Hope <daniel.hope@smartalock.com>
 */

#include "wireguardif.h"

#include <string.h>
#include <stdlib.h>

#include "lwip/netif.h"
#include "lwip/ip.h"
#include "lwip/ip4.h"
#include "lwip/udp.h"
#include "lwip/prot/tcp.h"
#include "lwip/tcp.h"
#include "lwip/priv/tcp_priv.h"
#include "lwip/mem.h"
#include "lwip/sys.h"
#include "lwip/timeouts.h"
#include "lwip/inet_chksum.h"

#include "wireguard.h"
#include "crypto.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_netif_net_stack.h"

#include "esp32-hal-log.h"

#define WIREGUARDIF_TIMER_MSECS 400

#define TAG "[WireGuard] "

static void update_peer_addr(struct wireguard_peer *peer, const ip_addr_t *addr, u16_t port) {
	peer->ip = *addr;
	peer->port = port;
}

static struct wireguard_peer *peer_lookup_by_allowed_ip(struct wireguard_device *device, const ip_addr_t *ipaddr) {
	struct wireguard_peer *result = NULL;
	struct wireguard_peer *tmp;
	int x;
	int y;
	for (x=0; (!result) && (x < WIREGUARD_MAX_PEERS); x++) {
		tmp = &device->peers[x];
		if (tmp->valid) {
			for (y=0; y < WIREGUARD_MAX_SRC_IPS; y++) {
				if ((tmp->allowed_source_ips[y].valid) && ip_addr_netcmp(ipaddr, &tmp->allowed_source_ips[y].ip, ip_2_ip4(&tmp->allowed_source_ips[y].mask))) {
					result = tmp;
					break;
				}
			}
		}
	}
	return result;
}

static bool wireguardif_can_send_initiation(struct wireguard_peer *peer) {
	return ((peer->last_initiation_tx == 0) || (wireguard_expired(peer->last_initiation_tx, REKEY_TIMEOUT)));
}

static struct netif* wireguardif_get_underlying(struct wireguard_device *device) {
	// The interface we send the encapsulated UDP packets out on. Recover it lazily:
	// BSB-LAN may run on Ethernet (no WIFI_STA_DEF esp_netif) or the STA netif may
	// have been down/without IP when the WG device was initialised.
	struct netif *u = device->underlying_netif;
	if (u && (u != device->netif) && netif_is_up(u) && !ip4_addr_isany_val(*netif_ip4_addr(u))) {
		return u;
	}
	struct netif *d = netif_default;
	if (d && (d != device->netif) && netif_is_up(d) && !ip4_addr_isany_val(*netif_ip4_addr(d))) {
		device->underlying_netif = d;
		wg_dbg("[WireGuard] underlying netif set to current default '%c%c%d'\n", d->name[0], d->name[1], d->num);
		return d;
	}
	return u;
}

// RX sniffer for the fallback netif: wraps netif->input and logs every received
// packet (TCP/UDP/ARP). Decides definitively whether replies to split-out
// traffic (SYN-ACK etc.) actually reach the interface at all.
static err_t (*wg_fb_orig_input)(struct pbuf *, struct netif *);
static struct netif *wg_fb_sniff_netif = NULL;

// Split-tunnel self-heal: the socket layer binds pcb->local_ip to the lwIP
// default netif's IP at connect() — the WG IP after netif_set_default(wg) —
// but split-out rewrites the wire source to the fallback netif's IP, so the
// 4-tuple match in tcp_input fails on dest != local_ip and the SYN-ACK is
// dropped silently (no RST visible). esp-lwip can additionally pin pcbs via
// netif_idx. Re-bind the matched SYN_SENT pcb to the reality on the wire
// before the packet reaches tcp_input (tcp_active_pcbs walk needs priv/tcp_priv.h).
static void wg_fixup_synack_pcb(struct netif *inp, const uint8_t *h, size_t ip_off, uint8_t hlen) {
	uint16_t sport = (uint16_t)((h[ip_off + hlen] << 8) | h[ip_off + hlen + 1]);
	uint16_t dport = (uint16_t)((h[ip_off + hlen + 2] << 8) | h[ip_off + hlen + 3]);
	ip4_addr_t sip, dip;
	IP4_ADDR(&sip, h[ip_off + 12], h[ip_off + 13], h[ip_off + 14], h[ip_off + 15]);
	IP4_ADDR(&dip, h[ip_off + 16], h[ip_off + 17], h[ip_off + 18], h[ip_off + 19]);
	struct tcp_pcb *pcb;
	for (pcb = tcp_active_pcbs; pcb != NULL; pcb = pcb->next) {
		if (pcb->state != SYN_SENT) {
			continue;
		}
		if (pcb->remote_port != sport || pcb->local_port != dport ||
		    (!ip_addr_eq(&pcb->remote_ip, IP_ADDR_ANY) && !ip4_addr_eq(ip_2_ip4(&pcb->remote_ip), &sip))) {
			continue;
		}
		if (pcb->netif_idx != NETIF_NO_INDEX && pcb->netif_idx != netif_get_index(inp)) {
			pcb->netif_idx = netif_get_index(inp);
		}
		if (IP_IS_V4_VAL(pcb->local_ip) && !ip4_addr_eq(ip_2_ip4(&pcb->local_ip), &dip)) {
			ip_2_ip4(&pcb->local_ip)->addr = dip.addr;
		}
		return;
	}
}

static err_t wg_fb_input_sniff(struct pbuf *p, struct netif *inp) {
	uint8_t h[96];
	size_t ip_off = 0;
	bool have_ip = false;

	if (p->tot_len >= 16 && pbuf_copy_partial(p, h, 16, 0) == 16) {
		if (h[12] == 0x08 && h[13] == 0x00) {
			ip_off = 14; /* ethernet_input style: Ethernet header still present */
			have_ip = true;
		} else if (h[12] == 0x08 && h[13] == 0x06) {
			return wg_fb_orig_input(p, inp);
		}
	}
	if (!have_ip && p->tot_len >= 20 && pbuf_copy_partial(p, h, 20, 0) == 20 && (h[0] >> 4) == 4) {
		ip_off = 0; /* IP header already at payload start */
		have_ip = true;
	}
	if (have_ip && p->tot_len >= ip_off + 20 && pbuf_copy_partial(p, h, 40, 0) == 40) {
		uint8_t proto = h[ip_off + 9];
		uint8_t hlen = (uint8_t)((h[ip_off] & 0x0F) << 2);
		if (proto == 6 && p->tot_len >= (u16_t)(ip_off + hlen + 14) &&
		    pbuf_copy_partial(p, h, (u16_t)(ip_off + hlen + 14), 0) == (u16_t)(ip_off + hlen + 14)) {
			uint8_t flg = h[ip_off + hlen + 13];
			if ((flg & 0x12) == 0x12) {
				/* re-bind a mismatched pcb before the packet reaches tcp_input */
				wg_fixup_synack_pcb(inp, h, ip_off, hlen);
			}
		}
	}
	return wg_fb_orig_input(p, inp);
}

// Split tunnel support: netif to use for locally-generated traffic that no peer's
// allowed_ip/mask matches (normally the Ethernet/WiFi interface that was the lwIP
// default before the WireGuard interface took over).
void wireguardif_set_fallback_netif(struct netif *netif, struct netif *fallback) {
	if (!netif || !netif->state) {
		return;
	}
	struct wireguard_device *device = (struct wireguard_device *)netif->state;
	device->fallback_netif = fallback;
	if (fallback) {
		wg_dbg("[WireGuard] split-tunnel fallback netif: '%c%c%d'\n", fallback->name[0], fallback->name[1], fallback->num);
		if (wg_fb_sniff_netif != fallback) {
			if (wg_fb_sniff_netif && wg_fb_orig_input) {
				wg_fb_sniff_netif->input = wg_fb_orig_input;
			}
			wg_fb_orig_input = fallback->input;
			wg_fb_sniff_netif = fallback;
			fallback->input = wg_fb_input_sniff;
			wg_dbg("[WireGuard] fb RX sniffer installed on '%c%c%d'\n", fallback->name[0], fallback->name[1], fallback->num);
		}
	} else {
		if (wg_fb_sniff_netif && wg_fb_orig_input) {
			wg_fb_sniff_netif->input = wg_fb_orig_input;
			wg_fb_orig_input = NULL;
			wg_fb_sniff_netif = NULL;
		}
		wg_dbg("[WireGuard] split-tunnel fallback netif cleared\n");
	}
}

static err_t wireguardif_peer_output(struct netif *netif, struct pbuf *q, struct wireguard_peer *peer) {
	struct wireguard_device *device = (struct wireguard_device *)netif->state;
	// Send to last know port, not the connect port
	//TODO: Support DSCP and ECN - lwip requires this set on PCB globally, not per packet
	err_t r = udp_sendto_if(device->udp_pcb, q, &peer->ip, peer->port, wireguardif_get_underlying(device));
	if (r == ERR_ARG) {
		wg_dbg("[WireGuard] TX udp err=ERR_ARG: NO usable underlying netif (Ethernet/WiFi down or WG is default before any netif was set)\n");
	}
	return r;
}

static err_t wireguardif_device_output(struct wireguard_device *device, struct pbuf *q, const ip_addr_t *ipaddr, u16_t port) {
	return udp_sendto_if(device->udp_pcb, q, ipaddr, port, wireguardif_get_underlying(device));
}

static err_t wireguardif_output_to_peer(struct netif *netif, struct pbuf *q, const ip_addr_t *ipaddr, struct wireguard_peer *peer) {
	// The LWIP IP layer wants to send an IP packet out over the interface - we need to encrypt and send it to the peer
	struct message_transport_data *hdr;
	struct pbuf *pbuf;
	err_t result;
	size_t unpadded_len;
	size_t padded_len;
	size_t header_len = 16;
	uint8_t *dst;
	uint32_t now;
	struct wireguard_keypair *keypair = &peer->curr_keypair;

	// Note: We may not be able to use the current keypair if we haven't received data, may need to resort to using previous keypair
	if (keypair->valid && (!keypair->initiator) && (keypair->last_rx == 0)) {
		keypair = &peer->prev_keypair;
	}

	if (keypair->valid && (keypair->initiator || keypair->last_rx != 0)) {

		if (
				!wireguard_expired(keypair->keypair_millis, REJECT_AFTER_TIME) &&
				(keypair->sending_counter < REJECT_AFTER_MESSAGES)
		) {

			// Calculate the outgoing packet size - round up to next 16 bytes, add 16 bytes for header
			if (q) {
				// This is actual transport data
				unpadded_len = q->tot_len;
			} else {
				// This is a keep-alive
				unpadded_len = 0;
			}
			padded_len = (unpadded_len + 15) & 0xFFFFFFF0; // Round up to next 16 byte boundary

			// The buffer needs to be allocated from "transport" pool to leave room for LwIP generated IP headers
			// The IP packet consists of 16 byte header (struct message_transport_data), data padded upto 16 byte boundary + encrypted auth tag (16 bytes)
			pbuf = pbuf_alloc(PBUF_TRANSPORT, header_len + padded_len + WIREGUARD_AUTHTAG_LEN, PBUF_RAM);
			if (pbuf) {
				log_v(TAG "preparing transport data...");
				// Note: allocating pbuf from RAM above guarantees that the pbuf is in one section and not chained
				// - i.e payload points to the contiguous memory region
				memset(pbuf->payload, 0, pbuf->tot_len);

				hdr = (struct message_transport_data *)pbuf->payload;

				hdr->type = MESSAGE_TRANSPORT_DATA;
				hdr->receiver = keypair->remote_index;
				// Alignment required... pbuf_alloc has probably aligned data, but want to be sure
				U64TO8_LITTLE(hdr->counter, keypair->sending_counter);

				// Copy the encrypted (padded) data to the output packet - chacha20poly1305_encrypt() can encrypt data in-place which avoids call to mem_malloc
				dst = &hdr->enc_packet[0];
				if ((padded_len > 0) && q) {
					// Note: before copying make sure we have inserted the IP header checksum
					// The IP header checksum (and other checksums in the IP packet - e.g. ICMP) need to be calculated by LWIP before calling
					// The Wireguard interface always needs checksums to be generated in software but the base netif may have some checksums generated by hardware

					// Copy pbuf to memory - handles case where pbuf is chained
					pbuf_copy_partial(q, dst, unpadded_len, 0);
				}

				// Then encrypt
				wireguard_encrypt_packet(dst, dst, padded_len, keypair);

				result = wireguardif_peer_output(netif, pbuf, peer);

				if (result == ERR_OK) {
					now = wireguard_sys_now();
					peer->last_tx = now;
					keypair->last_tx = now;
					peer->dbg_data_tx++;
				} else {
					wg_dbg("[WireGuard] TX: udp_sendto_if FAILED err=%d (endpoint %d.%d.%d.%d:%d)\n", result,
						ip4_addr1(ip_2_ip4(&peer->ip)), ip4_addr2(ip_2_ip4(&peer->ip)), ip4_addr3(ip_2_ip4(&peer->ip)), ip4_addr4(ip_2_ip4(&peer->ip)), peer->port);
				}

				pbuf_free(pbuf);

				// Check to see if we should rekey
				if (keypair->sending_counter >= REKEY_AFTER_MESSAGES) {
					peer->send_handshake = true;
				} else if (keypair->initiator && wireguard_expired(keypair->keypair_millis, REKEY_AFTER_TIME)) {
					peer->send_handshake = true;
				}

			} else {
				// Failed to allocate memory
				result = ERR_MEM;
			}
		} else {
			// key has expired...
			wg_dbg("[WireGuard] TX: current keypair expired/rejected -> keypair destroyed, packet dropped\n");
			keypair_destroy(keypair);
			result = ERR_CONN;
		}
	} else {
		// No valid keys!
		result = ERR_CONN;
		peer->dbg_tx_no_keypair++;
		if ((peer->dbg_tx_no_keypair == 1) || ((peer->dbg_tx_no_keypair % 10) == 0)) {
			wg_dbg("[WireGuard] TX data dropped: NO established keypair (handshake incomplete), drops so far=%lu\n", (unsigned long)peer->dbg_tx_no_keypair);
		}
	}
	return result;
}

// This is used as the output function for the Wireguard netif
// The ipaddr here is the one inside the VPN which we use to lookup the correct peer/endpoint
static err_t wireguardif_output(struct netif *netif, struct pbuf *q, const ip4_addr_t *ip4addr) {
	struct wireguard_device *device = (struct wireguard_device *)netif->state;
	// Send to peer that matches dest IP
	ip_addr_t ipaddr;
	ip_addr_copy_from_ip4(ipaddr, *ip4addr);
	struct wireguard_peer *peer = peer_lookup_by_allowed_ip(device, &ipaddr);
	if (peer) {
		return wireguardif_output_to_peer(netif, q, &ipaddr, peer);
	}
	// Split tunnel: no peer's allowed_ip/mask covers the destination. If a fallback
	// netif (the interface we were default on before WG, e.g. Ethernet) is set,
	// rewrite the source address (lwIP stamped it with the WG interface address)
	// and send the packet out directly - like "Table = off" on Windows.
	if (device->fallback_netif && (device->fallback_netif != netif) &&
		netif_is_up(device->fallback_netif) && netif_is_link_up(device->fallback_netif) &&
		!ip4_addr_isany_val(*netif_ip4_addr(device->fallback_netif)) &&
		(q->len >= IP_HLEN)) {
		struct ip_hdr *h = (struct ip_hdr *)q->payload;
		if (IPH_V(h) == 4) {
			struct netif *fb = device->fallback_netif;
			ip4_addr_t newsrc = *netif_ip4_addr(fb);
			u8_t hlen = IPH_HL_BYTES(h);
			wg_dbg("[WireGuard] split-tunnel: dest %d.%d.%d.%d not in any allowed_ip -> direct out '%c%c%d' (src %d.%d.%d.%d -> %d.%d.%d.%d)\n",
					ip4_addr1(ip4addr), ip4_addr2(ip4addr), ip4_addr3(ip4addr), ip4_addr4(ip4addr),
					fb->name[0], fb->name[1], fb->num,
					ip4_addr1(&h->src), ip4_addr2(&h->src), ip4_addr3(&h->src), ip4_addr4(&h->src),
					ip4_addr1(&newsrc), ip4_addr2(&newsrc), ip4_addr3(&newsrc), ip4_addr4(&newsrc));
			if (!ip4_addr_eq(&h->src, &newsrc)) {
				if (hlen <= q->len) {
					h->src.addr = newsrc.addr;
					IPH_CHKSUM_SET(h, 0);
					IPH_CHKSUM_SET(h, inet_chksum(h, hlen));
					if ((h->_proto == IP_PROTO_TCP) || (h->_proto == IP_PROTO_UDP)) {
						ip_addr_t src4, dst4;
						ip_addr_copy_from_ip4(src4, newsrc);
						ip_addr_copy_from_ip4(dst4, *ip4addr);
						if (pbuf_remove_header(q, hlen) == ERR_OK) {
							// ip_chksum_pseudo RETURNS the checksum value (u16_t), not an err_t:
							// zero the field, then store the value - same as tcp_output()/udp_output().
							if (h->_proto == IP_PROTO_TCP) {
								struct tcp_hdr *th = (struct tcp_hdr *)q->payload;
								th->chksum = 0;
								th->chksum = ip_chksum_pseudo(q, IP_PROTO_TCP, q->tot_len, &src4, &dst4);
							} else {
								struct udp_hdr *uh = (struct udp_hdr *)q->payload;
								uh->chksum = 0;
								uh->chksum = ip_chksum_pseudo(q, IP_PROTO_UDP, q->tot_len, &src4, &dst4);
							}
							pbuf_add_header(q, hlen);
						} else {
							wg_dbg("[WireGuard] split: pbuf_remove_header FAILED len=%d hlen=%d\n", q->len, hlen);
						}
					}
				}
			}
			err_t fo = fb->output(fb, q, ip4addr);
			if (fo != ERR_OK) {
				wg_dbg("[WireGuard] split-out via '%c%c%d' FAILED err=%d\n", fb->name[0], fb->name[1], fb->num, fo);
			}
			return fo;
		}
	}
	wg_dbg("[WireGuard] TX: no peer matches dest %d.%d.%d.%d (not in allowed_ip/mask) and no usable fallback netif -> ERR_RTE\n",
		ip4_addr1(ip4addr), ip4_addr2(ip4addr), ip4_addr3(ip4addr), ip4_addr4(ip4addr));
	return ERR_RTE;
}

static void wireguardif_send_keepalive(struct wireguard_device *device, struct wireguard_peer *peer) {
	// Send a NULL packet as a keep-alive
	wireguardif_output_to_peer(device->netif, NULL, NULL, peer);
}

static void wireguardif_process_response_message(struct wireguard_device *device, struct wireguard_peer *peer, struct message_handshake_response *response, const ip_addr_t *addr, u16_t port) {
	if (wireguard_process_handshake_response(device, peer, response)) {
		// Packet is good
		// Update the peer location
		log_i(TAG "good handshake from %08x:%d", addr->u_addr.ip4.addr, port);
		wg_dbg("[WireGuard] HANDSHAKE RESPONSE OK from %d.%d.%d.%d:%d -> session started\n",
			ip4_addr1(ip_2_ip4(addr)), ip4_addr2(ip_2_ip4(addr)), ip4_addr3(ip_2_ip4(addr)), ip4_addr4(ip_2_ip4(addr)), port);
		peer->dbg_response_rx++;
		update_peer_addr(peer, addr, port);

		wireguard_start_session(peer, true);
		wireguardif_send_keepalive(device, peer);

		// Set the IF-UP flag on netif
		netif_set_link_up(device->netif);
	} else {
		// Packet bad
		log_i(TAG "bad handshake from %08x:%d", addr->u_addr.ip4.addr, port);
		wg_dbg("[WireGuard] HANDSHAKE RESPONSE REJECTED from %d.%d.%d.%d:%d (crypto/DH failed - wrong key?)\n",
			ip4_addr1(ip_2_ip4(addr)), ip4_addr2(ip_2_ip4(addr)), ip4_addr3(ip_2_ip4(addr)), ip4_addr4(ip_2_ip4(addr)), port);
	}
}

static bool peer_add_ip(struct wireguard_peer *peer, ip_addr_t ip, ip_addr_t mask) {
	bool result = false;
	struct wireguard_allowed_ip *allowed;
	int x;
	// Look for existing match first
	for (x=0; x < WIREGUARD_MAX_SRC_IPS; x++) {
		allowed = &peer->allowed_source_ips[x];
		if ((allowed->valid) && ip_addr_cmp(&allowed->ip, &ip) && ip_addr_cmp(&allowed->mask, &mask)) {
			result = true;
			break;
		}
	}
	if (!result) {
		// Look for a free slot
		for (x=0; x < WIREGUARD_MAX_SRC_IPS; x++) {
			allowed = &peer->allowed_source_ips[x];
			if (!allowed->valid) {
				allowed->valid = true;
				allowed->ip = ip;
				allowed->mask = mask;
				result = true;
				break;
			}
		}
	}
	return result;
}

static void wireguardif_process_data_message(struct wireguard_device *device, struct wireguard_peer *peer, struct message_transport_data *data_hdr, size_t data_len, const ip_addr_t *addr, u16_t port) {
	struct wireguard_keypair *keypair;
	uint64_t nonce;
	uint8_t *src;
	size_t src_len;
	struct pbuf *pbuf;
	struct ip_hdr *iphdr;
	ip_addr_t dest;
	bool dest_ok = false;
	int x;
	uint32_t now;
	uint16_t header_len = 0xFFFF;
	uint32_t idx = data_hdr->receiver;

	keypair = get_peer_keypair_for_idx(peer, idx);

	if (keypair) {
		if (
				(keypair->receiving_valid) &&
				!wireguard_expired(keypair->keypair_millis, REJECT_AFTER_TIME) &&
				(keypair->sending_counter < REJECT_AFTER_MESSAGES)

		) {

			nonce = U8TO64_LITTLE(data_hdr->counter);
			src = &data_hdr->enc_packet[0];
			src_len = data_len;

			// We don't know the unpadded size until we have decrypted the packet and validated/inspected the IP header
			pbuf = pbuf_alloc(PBUF_TRANSPORT, src_len - WIREGUARD_AUTHTAG_LEN, PBUF_RAM);
			if (pbuf) {
				// Decrypt the packet
				memset(pbuf->payload, 0, pbuf->tot_len);
				if (wireguard_decrypt_packet(pbuf->payload, src, src_len, nonce, keypair)) {

					// 3. Since the packet has authenticated correctly, the source IP of the outer UDP/IP packet is used to update the endpoint for peer TrMv...WXX0.
					// Update the peer location
					update_peer_addr(peer, addr, port);

					now = wireguard_sys_now();
					keypair->last_rx = now;
					peer->last_rx = now;

					// Might need to shuffle next key --> current keypair
					keypair_update(peer, keypair);

					// Check to see if we should rekey
					if (keypair->initiator && wireguard_expired(keypair->keypair_millis, REJECT_AFTER_TIME - peer->keepalive_interval - REKEY_TIMEOUT)) {
						peer->send_handshake = true;
					}

					// Make sure that link is reported as up
					netif_set_link_up(device->netif);

					if (pbuf->tot_len > 0) {
						//4a. Once the packet payload is decrypted, the interface has a plaintext packet. If this is not an IP packet, it is dropped.
						iphdr = (struct ip_hdr *)pbuf->payload;
						// Check for packet replay / dupes
						if (wireguard_check_replay(keypair, nonce)) {

							// 4b. Otherwise, WireGuard checks to see if the source IP address of the plaintext inner-packet routes correspondingly in the cryptokey routing table
							// Also check packet length!
#if LWIP_IPV4
						if (IPH_V(iphdr) == 4) {
							header_len = PP_NTOHS(IPH_LEN(iphdr));
							// WireGuard inbound rule: packets accepted from a peer must ORIGINATE
							// within that peer's AllowedIPs (cryptokey routing on SOURCE, not dest).
							ip_addr_copy_from_ip4(dest, iphdr->src);
							for (x=0; x < WIREGUARD_MAX_SRC_IPS; x++) {
								if (peer->allowed_source_ips[x].valid) {
									if (ip_addr_netcmp(&dest, &peer->allowed_source_ips[x].ip, ip_2_ip4(&peer->allowed_source_ips[x].mask))) {
										dest_ok = true;
										break;
									}
								}
							}
						}
#endif /* LWIP_IPV4 */
#if LWIP_IPV6
						if (IPH_V(iphdr) == 6) {
							// TODO: IPV6 support for route filtering
							header_len = PP_NTOHS(IPH_LEN(iphdr));
							dest_ok = true;
						}
#endif /* LWIP_IPV6 */
							if (header_len <= pbuf->tot_len) {

								// 5. If the plaintext packet has not been dropped, it is inserted into the receive queue of the wg0 interface.
								if (dest_ok) {
									// Send packet to be process by LWIP
									ip_input(pbuf, device->netif);
									// pbuf is owned by IP layer now
									pbuf = NULL;
									peer->dbg_data_rx_ok++;
								} else {
									peer->dbg_data_rx_drop++;
									wg_dbg("[WireGuard] RX data decrypted but inner src %08x not in peer allowed_ip/mask -> dropped\n", dest.u_addr.ip4.addr);
								}
							} else {
								// IP header is corrupt or lied about packet size
								peer->dbg_data_rx_drop++;
								wg_dbg("[WireGuard] RX data: inner IP header corrupt (declared len %u > %u)\n", header_len, pbuf->tot_len);
							}
						} else {
							// This is a duplicate packet / replayed / too far out of order
							peer->dbg_data_rx_drop++;
							wg_dbg("[WireGuard] RX data: replay/duplicate check FAILED (nonce %llu outside window)\n", (unsigned long long)nonce);
						}
					} else {
						// This was a keep-alive packet
					}
					} else {
					peer->dbg_data_rx_drop++;
					wg_dbg("[WireGuard] RX data: DECRYPT FAILED (auth tag mismatch - wrong keys or corrupted packet)\n");
					}

					if (pbuf) {
					pbuf_free(pbuf);
					}
			}


		} else {
			//After Reject-After-Messages transport data messages or after the current secure session is Reject- After-Time seconds old,
			// whichever comes first, WireGuard will refuse to send or receive any more transport data messages using the current secure session,
			// until a new secure session is created through the 1-RTT handshake
			wg_dbg("[WireGuard] RX data: keypair expired/rejected -> destroyed\n");
			keypair_destroy(keypair);
		}

	} else {
		// Could not locate valid keypair for remote index
		peer->dbg_data_rx_drop++;
		if ((peer->dbg_data_rx_drop == 1) || ((peer->dbg_data_rx_drop % 10) == 0)) {
			wg_dbg("[WireGuard] RX data: no keypair for receiver index %08lx (session lost?), drops=%lu\n", (unsigned long)idx, (unsigned long)peer->dbg_data_rx_drop);
		}
	}
}

static struct pbuf *wireguardif_initiate_handshake(struct wireguard_device *device, struct wireguard_peer *peer, struct message_handshake_initiation *msg, err_t *error) {
	struct pbuf *pbuf = NULL;
	err_t err = ERR_OK;
	if (wireguard_create_handshake_initiation(device, peer, msg)) {
		// Send this packet out!
		pbuf = pbuf_alloc(PBUF_TRANSPORT, sizeof(struct message_handshake_initiation), PBUF_RAM);
		if (pbuf) {
			err = pbuf_take(pbuf, msg, sizeof(struct message_handshake_initiation));
			if (err == ERR_OK) {
				// OK!
			} else {
				pbuf_free(pbuf);
				pbuf = NULL;
			}
		} else {
			err = ERR_MEM;
		}
	} else {
		err = ERR_ARG;
	}
	if (error) {
		*error = err;
	}
	return pbuf;
}

static void wireguardif_send_handshake_response(struct wireguard_device *device, struct wireguard_peer *peer) {
	struct message_handshake_response packet;
	struct pbuf *pbuf = NULL;
	err_t err = ERR_OK;

	if (wireguard_create_handshake_response(device, peer, &packet)) {

		wireguard_start_session(peer, false);

		// Send this packet out!
		pbuf = pbuf_alloc(PBUF_TRANSPORT, sizeof(struct message_handshake_response), PBUF_RAM);
		if (pbuf) {
			err = pbuf_take(pbuf, &packet, sizeof(struct message_handshake_response));
			if (err == ERR_OK) {
				// OK!
				wireguardif_peer_output(device->netif, pbuf, peer);
			}
			pbuf_free(pbuf);
		}
	}
}

static size_t get_source_addr_port(const ip_addr_t *addr, u16_t port, uint8_t *buf, size_t buflen) {
	size_t result = 0;

#if LWIP_IPV4
	if (IP_IS_V4(addr) && (buflen >= 4)) {
		U32TO8_BIG(buf + result, PP_NTOHL(ip4_addr_get_u32(ip_2_ip4(addr))));
		result += 4;
	}
#endif
#if LWIP_IPV6
	if (IP_IS_V6(addr) && (buflen >= 16)) {
		U16TO8_BIG(buf + result + 0, IP6_ADDR_BLOCK1(ip_2_ip6(addr)));
		U16TO8_BIG(buf + result + 2, IP6_ADDR_BLOCK2(ip_2_ip6(addr)));
		U16TO8_BIG(buf + result + 4, IP6_ADDR_BLOCK3(ip_2_ip6(addr)));
		U16TO8_BIG(buf + result + 6, IP6_ADDR_BLOCK4(ip_2_ip6(addr)));
		U16TO8_BIG(buf + result + 8, IP6_ADDR_BLOCK5(ip_2_ip6(addr)));
		U16TO8_BIG(buf + result + 10, IP6_ADDR_BLOCK6(ip_2_ip6(addr)));
		U16TO8_BIG(buf + result + 12, IP6_ADDR_BLOCK7(ip_2_ip6(addr)));
		U16TO8_BIG(buf + result + 14, IP6_ADDR_BLOCK8(ip_2_ip6(addr)));
		result += 16;
	}
#endif
	if (buflen >= result + 2) {
		U16TO8_BIG(buf + result, port);
		result += 2;
	}
	return result;
}

static void wireguardif_send_handshake_cookie(struct wireguard_device *device, const uint8_t *mac1, uint32_t index, const ip_addr_t *addr, u16_t port) {
	struct message_cookie_reply packet;
	struct pbuf *pbuf = NULL;
	err_t err = ERR_OK;
	uint8_t source_buf[18];
	size_t source_len = get_source_addr_port(addr, port, source_buf, sizeof(source_buf));

	wireguard_create_cookie_reply(device, &packet, mac1, index, source_buf, source_len);

	// Send this packet out!
	pbuf = pbuf_alloc(PBUF_TRANSPORT, sizeof(struct message_cookie_reply), PBUF_RAM);
	if (pbuf) {
		err = pbuf_take(pbuf, &packet, sizeof(struct message_cookie_reply));
		if (err == ERR_OK) {
			wireguardif_device_output(device, pbuf, addr, port);
		}
		pbuf_free(pbuf);
	}
}

static bool wireguardif_check_initiation_message(struct wireguard_device *device, struct message_handshake_initiation *msg, const ip_addr_t *addr, u16_t port) {
	bool result = false;
	uint8_t *data = (uint8_t *)msg;
	uint8_t source_buf[18];
	size_t source_len;
	// We received an initiation packet check it is valid

	if (wireguard_check_mac1(device, data, sizeof(struct message_handshake_initiation) - (2 * WIREGUARD_COOKIE_LEN), msg->mac1)) {
		// mac1 is valid!
		if (!wireguard_is_under_load()) {
			// If we aren't under load we only need mac1 to be correct
			result = true;
		} else {
			// If we are under load then check mac2
			source_len = get_source_addr_port(addr, port, source_buf, sizeof(source_buf));

			result = wireguard_check_mac2(device, data, sizeof(struct message_handshake_initiation) - (WIREGUARD_COOKIE_LEN), source_buf, source_len, msg->mac2);

			if (!result) {
				// mac2 is invalid (cookie may have expired) or not present
				// 5.3 Denial of Service Mitigation & Cookies
				// If the responder receives a message with a valid msg.mac1 yet with an invalid msg.mac2, and is under load, it may respond with a cookie reply message
				wireguardif_send_handshake_cookie(device, msg->mac1, msg->sender, addr, port);
			}
		}

	} else {
		// mac1 is invalid
	}
	return result;
}

static bool wireguardif_check_response_message(struct wireguard_device *device, struct message_handshake_response *msg, const ip_addr_t *addr, u16_t port) {
	bool result = false;
	uint8_t *data = (uint8_t *)msg;
	uint8_t source_buf[18];
	size_t source_len;
	// We received an initiation packet check it is valid

	if (wireguard_check_mac1(device, data, sizeof(struct message_handshake_response) - (2 * WIREGUARD_COOKIE_LEN), msg->mac1)) {
		// mac1 is valid!
		if (!wireguard_is_under_load()) {
			// If we aren't under load we only need mac1 to be correct
			result = true;
		} else {
			// If we are under load then check mac2
			source_len = get_source_addr_port(addr, port, source_buf, sizeof(source_buf));

			result = wireguard_check_mac2(device, data, sizeof(struct message_handshake_response) - (WIREGUARD_COOKIE_LEN), source_buf, source_len, msg->mac2);

			if (!result) {
				// mac2 is invalid (cookie may have expired) or not present
				// 5.3 Denial of Service Mitigation & Cookies
				// If the responder receives a message with a valid msg.mac1 yet with an invalid msg.mac2, and is under load, it may respond with a cookie reply message
				wireguardif_send_handshake_cookie(device, msg->mac1, msg->sender, addr, port);
			}
		}

	} else {
		// mac1 is invalid
	}
	return result;
}


void wireguardif_network_rx(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port) {
	LWIP_ASSERT("wireguardif_network_rx: invalid arg", arg != NULL);
	LWIP_ASSERT("wireguardif_network_rx: invalid pbuf", p != NULL);
	// We have received a packet from the base_netif to our UDP port - process this as a possible Wireguard packet
	struct wireguard_device *device = (struct wireguard_device *)arg;
	struct wireguard_peer *peer;
	uint8_t *data = p->payload;
	size_t len = p->len; // This buf, not chained ones

	struct message_handshake_initiation *msg_initiation;
	struct message_handshake_response *msg_response;
	struct message_cookie_reply *msg_cookie;
	struct message_transport_data *msg_data;

	uint8_t type = wireguard_get_message_type(data, len);
	ESP_LOGV(TAG, "network_rx: %08x:%d", addr->u_addr.ip4.addr, port);

	switch (type) {
		case MESSAGE_HANDSHAKE_INITIATION:
			msg_initiation = (struct message_handshake_initiation *)data;
			log_i(TAG "HANDSHAKE_INITIATION: %08x:%d", addr->u_addr.ip4.addr, port);
			wg_dbg("[WireGuard] RX HANDSHAKE_INITIATION from %d.%d.%d.%d:%d\n",
				ip4_addr1(ip_2_ip4(addr)), ip4_addr2(ip_2_ip4(addr)), ip4_addr3(ip_2_ip4(addr)), ip4_addr4(ip_2_ip4(addr)), port);
			// Check mac1 (and optionally mac2) are correct - note it may internally generate a cookie reply packet
			if (wireguardif_check_initiation_message(device, msg_initiation, addr, port)) {

				peer = wireguard_process_initiation_message(device, msg_initiation);
				if (peer) {
					peer->dbg_initiation_rx++;
					// Update the peer location
					update_peer_addr(peer, addr, port);

					// Send back a handshake response
					wireguardif_send_handshake_response(device, peer);
				} else {
					wg_dbg("[WireGuard] RX initiation: no matching peer (unknown static key / bad message)\n");
				}
			}
			break;

		case MESSAGE_HANDSHAKE_RESPONSE:
			log_i(TAG "HANDSHAKE_RESPONSE: %08x:%d", addr->u_addr.ip4.addr, port);
			msg_response = (struct message_handshake_response *)data;

			// Check mac1 (and optionally mac2) are correct - note it may internally generate a cookie reply packet
			if (wireguardif_check_response_message(device, msg_response, addr, port)) {

				peer = peer_lookup_by_handshake(device, msg_response->receiver);
				if (peer) {
					// Process the handshake response
					wireguardif_process_response_message(device, peer, msg_response, addr, port);
				} else {
					wg_dbg("[WireGuard] RX HANDSHAKE_RESPONSE for receiver index %08lx but NO pending handshake (stale or for another peer)\n", (unsigned long)msg_response->receiver);
				}
			} else {
				wg_dbg("[WireGuard] RX HANDSHAKE_RESPONSE mac1/mac2 check FAILED (dropped)\n");
			}
			break;

		case MESSAGE_COOKIE_REPLY:
			log_i(TAG "COOKIE_REPLY: %08x:%d", addr->u_addr.ip4.addr, port);
			msg_cookie = (struct message_cookie_reply *)data;
			peer = peer_lookup_by_handshake(device, msg_cookie->receiver);
			if (peer) {
				peer->dbg_cookie_rx++;
				if (wireguard_process_cookie_message(device, peer, msg_cookie)) {
					// Update the peer location
					update_peer_addr(peer, addr, port);
					wg_dbg("[WireGuard] RX COOKIE_REPLY processed OK - next initiation will carry mac2\n");

					// Don't send anything out - we stay quiet until the next initiation message
				}
			} else {
				wg_dbg("[WireGuard] RX COOKIE_REPLY for unknown receiver index %08lx\n", (unsigned long)msg_cookie->receiver);
			}
			break;

		case MESSAGE_TRANSPORT_DATA:
			ESP_LOGV(TAG, "TRANSPORT_DATA: %08x:%d", addr->u_addr.ip4.addr, port);

			msg_data = (struct message_transport_data *)data;
			peer = peer_lookup_by_receiver(device, msg_data->receiver);
			if (peer) {
				// header is 16 bytes long so take that off the length
				wireguardif_process_data_message(device, peer, msg_data, len - 16, addr, port);
			} else {
				peer = &device->peers[0];
				peer->dbg_unknown_rx++;
				if ((peer->dbg_unknown_rx == 1) || ((peer->dbg_unknown_rx % 10) == 0)) {
					wg_dbg("[WireGuard] RX TRANSPORT_DATA for unknown receiver index %08lx (remote has session we don't?), drops=%lu\n",
						(unsigned long)msg_data->receiver, (unsigned long)peer->dbg_unknown_rx);
				}
			}
			break;

		default:
			// Unknown or bad packet header
			device->peers[0].dbg_unknown_rx++;
			wg_dbg("[WireGuard] RX unknown packet type=%d len=%d from %d.%d.%d.%d:%d (UDP port traffic is not WireGuard?)\n", type, len,
				ip4_addr1(ip_2_ip4(addr)), ip4_addr2(ip_2_ip4(addr)), ip4_addr3(ip_2_ip4(addr)), ip4_addr4(ip_2_ip4(addr)), port);
			break;
	}
	// Release data!
	pbuf_free(p);
}

static err_t wireguard_start_handshake(struct netif *netif, struct wireguard_peer *peer) {
	struct wireguard_device *device = (struct wireguard_device *)netif->state;
	err_t result;
	struct pbuf *pbuf;
	struct message_handshake_initiation msg;

	pbuf = wireguardif_initiate_handshake(device, peer, &msg, &result);
	if (pbuf) {
		result = wireguardif_peer_output(netif, pbuf, peer);
		log_i(TAG "start handshake %08x,%d - %d", peer->ip.u_addr.ip4.addr, peer->port, result);
		peer->dbg_initiation_tx++;
		wg_dbg("[WireGuard] -> handshake initiation #%lu to %d.%d.%d.%d:%d (udp err=%d)\n", (unsigned long)peer->dbg_initiation_tx,
			ip4_addr1(ip_2_ip4(&peer->ip)), ip4_addr2(ip_2_ip4(&peer->ip)), ip4_addr3(ip_2_ip4(&peer->ip)), ip4_addr4(ip_2_ip4(&peer->ip)), peer->port, result);
		pbuf_free(pbuf);
		peer->send_handshake = false;
		peer->last_initiation_tx = wireguard_sys_now();
		memcpy(peer->handshake_mac1, msg.mac1, WIREGUARD_COOKIE_LEN);
		peer->handshake_mac1_valid = true;
	} else {
		wg_dbg("[WireGuard] !! handshake initiation could NOT be built (err=%d) - check local/peer keys\n", result);
	}
	return result;
}

static err_t wireguardif_lookup_peer(struct netif *netif, u8_t peer_index, struct wireguard_peer **out) {
	LWIP_ASSERT("netif != NULL", (netif != NULL));
	LWIP_ASSERT("state != NULL", (netif->state != NULL));
	struct wireguard_device *device = (struct wireguard_device *)netif->state;
	struct wireguard_peer *peer = NULL;
	err_t result;

	if (device->valid) {
		peer = peer_lookup_by_peer_index(device, peer_index);
		if (peer) {
			result = ERR_OK;
		} else {
			result = ERR_ARG;
		}
	} else {
		result = ERR_ARG;
	}
	*out = peer;
	return result;
}

err_t wireguardif_connect(struct netif *netif, u8_t peer_index) {
	struct wireguard_peer *peer;
	err_t result = wireguardif_lookup_peer(netif, peer_index, &peer);
	if (result == ERR_OK) {
		// Check that a valid connect ip and port have been set
		if (!ip_addr_isany(&peer->connect_ip) && (peer->connect_port > 0)) {
			// Set the flag that we want to try connecting
			peer->active = true;
			peer->ip = peer->connect_ip;
			peer->port = peer->connect_port;
			result = ERR_OK;
			wg_dbg("[WireGuard] connect: endpoint %d.%d.%d.%d:%d, active=YES, curr_keypair.valid=%d prev=%d next=%d\n",
				ip4_addr1(ip_2_ip4(&peer->connect_ip)), ip4_addr2(ip_2_ip4(&peer->connect_ip)), ip4_addr3(ip_2_ip4(&peer->connect_ip)), ip4_addr4(ip_2_ip4(&peer->connect_ip)), peer->connect_port,
				peer->curr_keypair.valid, peer->prev_keypair.valid, peer->next_keypair.valid);
		} else {
			result = ERR_ARG;
			wg_dbg("[WireGuard] connect FAILED: connect_ip is 0.0.0.0 or connect_port is 0\n");
		}
		// Sanity: is the physical (WLAN) interface underneath usable at all?
		struct wireguard_device *device = (struct wireguard_device *)netif->state;
		if (device->underlying_netif == NULL) {
			wg_dbg("[WireGuard] connect: WARNING underlying netif is NULL - WG packets cannot leave the device\n");
		} else if (!netif_is_up(device->underlying_netif)) {
			wg_dbg("[WireGuard] connect: WARNING underlying netif '%c%c%d' is DOWN - UDP to server cannot leave the device\n",
				device->underlying_netif->name[0], device->underlying_netif->name[1], device->underlying_netif->num);
		}
		// netif_ip4_addr() already returns const ip4_addr_t* - do NOT wrap in ip_2_ip4()
		if (!ip4_addr_isany_val(*netif_ip4_addr(netif))) {
			wg_dbg("[WireGuard] connect: wg local IP %d.%d.%d.%d (server must have this in AllowedIPs of the peer)\n",
				ip4_addr1(netif_ip4_addr(netif)), ip4_addr2(netif_ip4_addr(netif)),
				ip4_addr3(netif_ip4_addr(netif)), ip4_addr4(netif_ip4_addr(netif)));
		}
	}
	return result;
}

err_t wireguardif_disconnect(struct netif *netif, u8_t peer_index) {
	struct wireguard_peer *peer;
	err_t result = wireguardif_lookup_peer(netif, peer_index, &peer);
	if (result == ERR_OK) {
		// Set the flag that we want to try connecting
		peer->active = false;
		// Wipe out current keys
		keypair_destroy(&peer->next_keypair);
		keypair_destroy(&peer->curr_keypair);
		keypair_destroy(&peer->prev_keypair);
		result = ERR_OK;
	}
	return result;
}

err_t wireguardif_peer_is_up(struct netif *netif, u8_t peer_index, ip_addr_t *current_ip, u16_t *current_port) {
	struct wireguard_peer *peer;
	err_t result = wireguardif_lookup_peer(netif, peer_index, &peer);
	if (result == ERR_OK) {
		if ((peer->curr_keypair.valid) || (peer->prev_keypair.valid)) {
			result = ERR_OK;
		} else {
			result = ERR_CONN;
		}
		if (current_ip) {
			*current_ip = peer->ip;
		}
		if (current_port) {
			*current_port = peer->port;
		}
	}
	return result;
}

err_t wireguardif_remove_peer(struct netif *netif, u8_t peer_index) {
	struct wireguard_peer *peer;
	err_t result = wireguardif_lookup_peer(netif, peer_index, &peer);
	if (result == ERR_OK) {
		crypto_zero(peer, sizeof(struct wireguard_peer));
		peer->valid = false;
		result = ERR_OK;
	}
	return result;
}

err_t wireguardif_update_endpoint(struct netif *netif, u8_t peer_index, const ip_addr_t *ip, u16_t port) {
	struct wireguard_peer *peer;
	err_t result = wireguardif_lookup_peer(netif, peer_index, &peer);
	if (result == ERR_OK) {
		peer->connect_ip = *ip;
		peer->connect_port = port;
		result = ERR_OK;
	}
	return result;
}


err_t wireguardif_add_peer(struct netif *netif, struct wireguardif_peer *p, u8_t *peer_index) {
	LWIP_ASSERT("netif != NULL", (netif != NULL));
	LWIP_ASSERT("state != NULL", (netif->state != NULL));
	LWIP_ASSERT("p != NULL", (p != NULL));
	struct wireguard_device *device = (struct wireguard_device *)netif->state;
	err_t result;
	uint8_t public_key[WIREGUARD_PUBLIC_KEY_LEN];
	size_t public_key_len = sizeof(public_key);
	struct wireguard_peer *peer = NULL;

	uint32_t t1 = wireguard_sys_now();

	if (wireguard_base64_decode(p->public_key, public_key, &public_key_len)
			&& (public_key_len == WIREGUARD_PUBLIC_KEY_LEN)) {

		// See if the peer is already registered
		peer = peer_lookup_by_pubkey(device, public_key);
		if (!peer) {
			// Not active - see if we have room to allocate a new one
			peer = peer_alloc(device);
			if (peer) {

				if (wireguard_peer_init(device, peer, public_key, p->preshared_key)) {

					peer->connect_ip = p->endpoint_ip;
					peer->connect_port = p->endport_port;
					peer->ip = peer->connect_ip;
					peer->port = peer->connect_port;
					if (p->keep_alive == WIREGUARDIF_KEEPALIVE_DEFAULT) {
						peer->keepalive_interval = KEEPALIVE_TIMEOUT;
					} else {
						peer->keepalive_interval = p->keep_alive;
					}
					peer_add_ip(peer, p->allowed_ip, p->allowed_mask);
					memcpy(peer->greatest_timestamp, p->greatest_timestamp, sizeof(peer->greatest_timestamp));

					result = ERR_OK;
				} else {
					result = ERR_ARG;
				}
			} else {
				result = ERR_MEM;
			}
		} else {
			result = ERR_OK;
		}
	} else {
		result = ERR_ARG;
	}

	uint32_t t2 = wireguard_sys_now();
	log_i(TAG "Adding peer took %ums\r\n", (t2-t1));
	if (result != ERR_OK) {
		switch (result) {
			case ERR_ARG:  wg_dbg("[WireGuard] add_peer FAILED: invalid base64 public_key or preshared_key\n"); break;
			case ERR_MEM:  wg_dbg("[WireGuard] add_peer FAILED: no free peer slot\n"); break;
			default:       wg_dbg("[WireGuard] add_peer FAILED: err=%d\n", result); break;
		}
	} else {
		wg_dbg("[WireGuard] add_peer OK: remote pubkey b64='%s' endpoint=%d.%d.%d.%d:%d keepalive=%us\n",
			p->public_key ? p->public_key : "?",
			ip4_addr1(ip_2_ip4(&p->endpoint_ip)), ip4_addr2(ip_2_ip4(&p->endpoint_ip)),
			ip4_addr3(ip_2_ip4(&p->endpoint_ip)), ip4_addr4(ip_2_ip4(&p->endpoint_ip)),
			p->endport_port, (unsigned)(p->keep_alive == WIREGUARDIF_KEEPALIVE_DEFAULT ? KEEPALIVE_TIMEOUT : p->keep_alive));
	}

	if (peer_index) {
		if (peer) {
			*peer_index = wireguard_peer_index(device, peer);
		} else {
			*peer_index = WIREGUARDIF_INVALID_INDEX;
		}
	}
	return result;
}

static bool should_send_initiation(struct wireguard_peer *peer) {
	bool result = false;
	if (wireguardif_can_send_initiation(peer)) {
		if (peer->send_handshake) {
			result = true;
		} else if (peer->curr_keypair.valid && !peer->curr_keypair.initiator && wireguard_expired(peer->curr_keypair.keypair_millis, REJECT_AFTER_TIME - peer->keepalive_interval)) {
			result = true;
		} else if (!peer->curr_keypair.valid && peer->active) {
			result = true;
		}
	}
	return result;
}

static bool should_send_keepalive(struct wireguard_peer *peer) {
	bool result = false;
	if (peer->keepalive_interval > 0) {
		if ((peer->curr_keypair.valid) || (peer->prev_keypair.valid)) {
			if (wireguard_expired(peer->last_tx, peer->keepalive_interval)) {
				result = true;
			}
		}
	}
	return result;
}

static bool should_destroy_current_keypair(struct wireguard_peer *peer) {
	bool result = false;
	if (peer->curr_keypair.valid &&
			(wireguard_expired(peer->curr_keypair.keypair_millis, REJECT_AFTER_TIME) ||
			(peer->curr_keypair.sending_counter >= REJECT_AFTER_MESSAGES))
		) {
		result = true;
	}
	return result;
}

static bool should_reset_peer(struct wireguard_peer *peer) {
	bool result = false;
	if (peer->curr_keypair.valid && (wireguard_expired(peer->curr_keypair.keypair_millis, REJECT_AFTER_TIME * 3))) {
		result = true;
	}
	return result;
}

static void wireguardif_tmr(void *arg) {
	struct wireguard_device *device = (struct wireguard_device *)arg;
	struct wireguard_peer *peer;
	int x;
	// Reschedule this timer
	sys_timeout(WIREGUARDIF_TIMER_MSECS, wireguardif_tmr, device);
	
	// Check periodic things
	bool link_up = false;
	for (x=0; x < WIREGUARD_MAX_PEERS; x++) {
		peer = &device->peers[x];
		if (peer->valid) {
			// Do we need to rekey / send a handshake?
			if (should_reset_peer(peer)) {
				// Nothing back for too long - we should wipe out all crypto state
				keypair_destroy(&peer->next_keypair);
				keypair_destroy(&peer->curr_keypair);
				keypair_destroy(&peer->prev_keypair);
				handshake_destroy(&peer->handshake);

				// Revert back to default IP/port if these were altered
				peer->ip = peer->connect_ip;
				peer->port = peer->connect_port;
			}
			if (should_destroy_current_keypair(peer)) {
				// Destroy current keypair
				keypair_destroy(&peer->curr_keypair);
			}
			if (should_send_keepalive(peer)) {
				wireguardif_send_keepalive(device, peer);
			}
			if (should_send_initiation(peer)) {
				wireguard_start_handshake(device->netif, peer);
			}

			if ((peer->curr_keypair.valid) || (peer->prev_keypair.valid)) {
				link_up = true;
			}
		}
	}

	if (!link_up) {
		// Clear the IF-UP flag on netif
		netif_set_link_down(device->netif);
	}
}

void wireguardif_shutdown(struct netif *netif) {
	LWIP_ASSERT("netif != NULL", (netif != NULL));
	LWIP_ASSERT("state != NULL", (netif->state != NULL));

	struct wireguard_device * device = (struct wireguard_device *)netif->state;
	// Disable timer.
	sys_untimeout(wireguardif_tmr, device);
	// remove UDP context.
	if( device->udp_pcb ) {
		udp_disconnect(device->udp_pcb);
		udp_remove(device->udp_pcb);
		device->udp_pcb = NULL;
	}
	// remove device context.
	free(device);
	netif->state = NULL;
}

err_t wireguardif_init(struct netif *netif) {
	err_t result;
	struct wireguardif_init_data *init_data;
	struct wireguard_device *device;
	struct udp_pcb *udp;
	uint8_t private_key[WIREGUARD_PRIVATE_KEY_LEN];
	size_t private_key_len = sizeof(private_key);

	struct netif* underlying_netif;
	esp_netif_t *esp_nif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
	underlying_netif = esp_nif ? (struct netif*)esp_netif_get_netif_impl(esp_nif) : NULL;
	log_i(TAG "underlying_netif (WIFI_STA_DEF) = %p", underlying_netif);
	if (underlying_netif == NULL) {
		// BSB-LAN can run on Ethernet - then there is no WIFI_STA_DEF netif at all.
		// At this point (inside netif_add) the active interface (ETH/WLAN) is still
		// lwIP's default netif - BSB-LAN switches the default to the WG netif later.
		underlying_netif = netif_default;
		if (underlying_netif) {
			wg_dbg("[WireGuard] init: no WIFI_STA_DEF netif - using current default '%c%c%d' as underlying interface\n",
				underlying_netif->name[0], underlying_netif->name[1], underlying_netif->num);
		} else {
			wg_dbg("[WireGuard] init: WARNING no underlying netif found at all - WG packets cannot leave the device until one comes up\n");
		}
	}

	LWIP_ASSERT("netif != NULL", (netif != NULL));
	LWIP_ASSERT("state != NULL", (netif->state != NULL));

	// We need to initialise the wireguard module
	wireguard_init();
	log_i(TAG "wireguard module initialized.");

	if (netif && netif->state) {

		// The init data is passed into the netif_add call as the 'state' - we will replace this with our private state data
		init_data = (struct wireguardif_init_data *)netif->state;

		// Clear out and set if function is successful
		netif->state = NULL;

		if (wireguard_base64_decode(init_data->private_key, private_key, &private_key_len)
				&& (private_key_len == WIREGUARD_PRIVATE_KEY_LEN)) {

			udp = udp_new();

			if (udp) {
				result = udp_bind(udp, IP_ADDR_ANY, init_data->listen_port); // Note this listens on all interfaces! Really just want the passed netif
				if (result == ERR_OK) {
					device = (struct wireguard_device *)mem_calloc(1, sizeof(struct wireguard_device));
					if (device) {
						device->netif = netif;
						device->underlying_netif = underlying_netif;
						//udp_bind_netif(udp, underlying_netif);

						device->udp_pcb = udp;
						log_d(TAG "start device initialization");
						// Per-wireguard netif/device setup
						uint32_t t1 = wireguard_sys_now();
						if (wireguard_device_init(device, private_key)) {
							uint32_t t2 = wireguard_sys_now();
							log_d(TAG "Device init took %ums\r\n", (t2-t1));

#if LWIP_CHECKSUM_CTRL_PER_NETIF
							NETIF_SET_CHECKSUM_CTRL(netif, NETIF_CHECKSUM_ENABLE_ALL);
#endif
							netif->state = device;
							netif->name[0] = 'w';
							netif->name[1] = 'g';
							netif->output = wireguardif_output;
							netif->linkoutput = NULL;
							netif->hwaddr_len = 0;
							netif->mtu = WIREGUARDIF_MTU;
							// We set up no state flags here - caller should set them
							// NETIF_FLAG_LINK_UP is automatically set/cleared when at least one peer is connected
							netif->flags = 0;

							udp_recv(udp, wireguardif_network_rx, device);

							// Start a periodic timer for this wireguard device
							sys_timeout(WIREGUARDIF_TIMER_MSECS, wireguardif_tmr, device);

							result = ERR_OK;
						} else {
							log_e(TAG "failed to initialize WireGuard device.");
							mem_free(device);
							device = NULL;
							udp_remove(udp);
							result = ERR_ARG;
						}
					} else {
						log_e(TAG "failed to allocate device context.");
						udp_remove(udp);
						result = ERR_MEM;
					}
				} else {
					log_e(TAG "failed to bind UDP err=%d", result);
					wg_dbg("[WireGuard] INIT FAILED: udp_bind on port %d err=%d (port in use?)\n", init_data->listen_port, result);
					udp_remove(udp);
				}

			} else {
				log_e(TAG "failed to allocate UDP");
				result = ERR_MEM;
			}
		} else {
			log_e(TAG "invalid init_data private key");
			wg_dbg("[WireGuard] INIT FAILED: local private key is not valid base64 or wrong length!\n");
			result = ERR_ARG;
		}
	} else {
		log_e(TAG "netif or state is NULL: netif=%p, netif.state:%p", netif, netif ? netif->state : NULL);
		result = ERR_ARG;
	}
	return result;
}

static long wg_age_s(uint32_t t) {
	if (t == 0) {
		return -1;
	}
	return (long)((int32_t)(wireguard_sys_now() - t) / 1000);
}

void wireguardif_dump_status(struct netif *netif) {
	if (!netif || !netif->state) {
		wg_dbg("[WireGuard] status: no initialized device on this interface\n");
		return;
	}
	struct wireguard_device *device = (struct wireguard_device *)netif->state;
	int x;
	wg_dbg("[WireGuard] ==== status (netif up=%d link_up=%d default=%d mtu=%d) ====\n",
		netif_is_up(netif), netif_is_link_up(netif),
		(netif == netif_default) ? 1 : 0, netif->mtu);
	wg_dbg("[WireGuard] underlying netif=%p", (void*)device->underlying_netif);
	if (device->underlying_netif) {
		wg_dbg(" '%c%c%d' (up=%d)", device->underlying_netif->name[0], device->underlying_netif->name[1],
			device->underlying_netif->num, netif_is_up(device->underlying_netif));
	} else {
		wg_dbg(" (NONE - WG packets cannot leave the device!)");
	}
	wg_dbg(" udp_pcb=%d\n", device->udp_pcb ? 1 : 0);
	if (device->fallback_netif) {
		struct netif *fb = device->fallback_netif;
		wg_dbg("[WireGuard] fb netif '%c%c%d' ip=%d.%d.%d.%d gw=%d.%d.%d.%d up=%d link=%d\n",
			fb->name[0], fb->name[1], fb->num,
			ip4_addr1(netif_ip4_addr(fb)), ip4_addr2(netif_ip4_addr(fb)),
			ip4_addr3(netif_ip4_addr(fb)), ip4_addr4(netif_ip4_addr(fb)),
			ip4_addr1(netif_ip4_gw(fb)), ip4_addr2(netif_ip4_gw(fb)),
			ip4_addr3(netif_ip4_gw(fb)), ip4_addr4(netif_ip4_gw(fb)),
			fb->flags & NETIF_FLAG_UP ? 1 : 0, fb->flags & NETIF_FLAG_LINK_UP ? 1 : 0);
	}
	for (x=0; x < WIREGUARD_MAX_PEERS; x++) {
		struct wireguard_peer *peer = &device->peers[x];
		if (!peer->valid) {
			continue;
		}
		wg_dbg("[WireGuard] peer[%d] active=%d endpoint_now=%d.%d.%d.%d:%d connect=%d.%d.%d.%d:%d\n", x, peer->active,
			ip4_addr1(ip_2_ip4(&peer->ip)), ip4_addr2(ip_2_ip4(&peer->ip)), ip4_addr3(ip_2_ip4(&peer->ip)), ip4_addr4(ip_2_ip4(&peer->ip)), peer->port,
			ip4_addr1(ip_2_ip4(&peer->connect_ip)), ip4_addr2(ip_2_ip4(&peer->connect_ip)), ip4_addr3(ip_2_ip4(&peer->connect_ip)), ip4_addr4(ip_2_ip4(&peer->connect_ip)), peer->connect_port);
		wg_dbg("[WireGuard] peer[%d] keypair curr=%d(prev=%d) prev=%d next=%d handshake_pending=%d send_handshake=%d\n", x,
			peer->curr_keypair.valid, (peer->curr_keypair.valid ? peer->curr_keypair.initiator : 0),
			peer->prev_keypair.valid, peer->next_keypair.valid,
			peer->handshake.valid, peer->send_handshake);
		wg_dbg("[WireGuard] peer[%d] timings(s): init_tx_ago=%ld resp_rx_ago=- data_rx_ago=%ld data_tx_ago=%ld keypair_age=%ld\n", x,
			wg_age_s(peer->last_initiation_tx), wg_age_s(peer->last_rx), wg_age_s(peer->last_tx),
			wg_age_s(peer->curr_keypair.keypair_millis));
		wg_dbg("[WireGuard] peer[%d] counters: init_tx=%lu resp_rx=%lu init_rx=%lu cookie_rx=%lu data_tx=%lu data_rx_ok=%lu rx_drop=%lu unknown_rx=%lu tx_no_key=%lu\n", x,
			(unsigned long)peer->dbg_initiation_tx, (unsigned long)peer->dbg_response_rx,
			(unsigned long)peer->dbg_initiation_rx, (unsigned long)peer->dbg_cookie_rx,
			(unsigned long)peer->dbg_data_tx, (unsigned long)peer->dbg_data_rx_ok,
			(unsigned long)peer->dbg_data_rx_drop, (unsigned long)peer->dbg_unknown_rx,
			(unsigned long)peer->dbg_tx_no_keypair);
		if (peer->dbg_data_rx_drop || peer->dbg_tx_no_keypair) {
			wg_dbg("[WireGuard] peer[%d] => handshake%sestablished (drops mean packets were seen but could not be used)\n", x,
				((peer->curr_keypair.valid) || (peer->prev_keypair.valid)) ? " " : " NOT ");
		} else if (!peer->dbg_data_tx && !peer->dbg_response_rx && peer->dbg_initiation_tx) {
			wg_dbg("[WireGuard] peer[%d] => %lu initiation(s) sent, ZERO answer from server "
				"(server does not know this peer / wrong port / firewall)\n", x, (unsigned long)peer->dbg_initiation_tx);
		}
	}
	wg_dbg("[WireGuard] ==== end status ====\n");
}

void wireguardif_peer_init(struct wireguardif_peer *peer) {
	LWIP_ASSERT("peer != NULL", (peer != NULL));
	memset(peer, 0, sizeof(struct wireguardif_peer));
	// Caller must provide 'public_key'
	peer->public_key = NULL;
	ip_addr_set_any(false, &peer->endpoint_ip);
	peer->endport_port = WIREGUARDIF_DEFAULT_PORT;
	peer->keep_alive = WIREGUARDIF_KEEPALIVE_DEFAULT;
	ip_addr_set_any(false, &peer->allowed_ip);
	ip_addr_set_any(false, &peer->allowed_mask);
	memset(peer->greatest_timestamp, 0, sizeof(peer->greatest_timestamp));
	peer->preshared_key = NULL;
}
