# WireGuard-ESP32 (der-berni Fork)

Fork of [ciniml/WireGuard-ESP32-Arduino](https://github.com/ciniml/WireGuard-ESP32-Arduino) **v0.1.5** (itself the maintained fork of Kenta Ida's original).
Developed and verified on real hardware for BSB-LAN on ESP32 (OLIMEX ESP32-EVB) — with Ethernet *and* WiFi, against a real Linux kernel WireGuard server.

## Lineage of this codebase

```
ciniml/WireGuard-ESP32-Arduino v0.1.5
  └─ ESP-IDF v5.4 compatibility (esp_netif instead of tcpip_adapter, handshake_destroy declaration)
     + preshared-key / keepalive support
      └─ THIS fork: begin()/end() moved into the lwIP TCP/IP callback thread (thread safety)
         + protocol fixes, real split tunnel, SYN-ACK self-heal, diagnostics API
```

## Fixes — protocol correctness

- **Replay window accepts counter 0** (`wireguard.c`): the kernel server starts transport counters at 0; the upstream `if (seq != 0)` check unconditionally dropped the *first* data packet of every session (e.g. the SYN-ACK). Also, `ReplayWindowSize = sizeof(replay_bitmap)` was 4 instead of 32 — now a proper 32-bit sliding window.
- **`allowed_source_ips` was matched against the inner *destination*** (`wireguardif.c`) instead of the source: your own tunnel IP never matches the peer's AllowedIPs → every correctly decrypted reply from a kernel peer was discarded (`data_rx_ok=0`, `rx_drop>0`). Now compared against `iphdr->src`; fixed `header_len` initialization (0xFFFF → misleading "inner IP header corrupt" message).
- **Underlying netif was hardcoded to `WIFI_STA_DEF`** (`wireguardif_init`): without a WiFi-STA netif (e.g. Ethernet / `network_type=LAN`) it resolved to NULL → every `udp_sendto_if` returned `ERR_ARG` and not a single packet ever left the device. Now falls back to the current lwIP default netif, plus late re-acquisition (`wireguardif_get_underlying()`) at both send sites if the stored netif is down or has no IP.
- **lwIP 2.2 / arduino-esp32 core 3.x compatibility**: `ip_hdr` fields `src`/`dest` (packed `ip4_addr_p_t`), `pbuf_remove_header` instead of `pbuf_ref_header`, `ip4_addr_eq` instead of `*_cmp`, `ip_2_ip4()` only on `ip_addr_t`, correct checksum API usage (`ip_chksum_pseudo()` returns the *value*, not `ERR_OK`; `inet_chksum()` already returns network byte order).

## Split tunnel (a real, working one)

Upstream gated `netif_set_default(wg)` on `!custom_allowed_ip` → whenever an `allowed_ip` CIDR was set, nothing was ever routed into the WG netif (lwIP's `ip4_route` only knows directly-connected subnets + the default route) and traffic died silently.

- The WG netif **always** becomes the default route once the session is up.
- **`wireguardif_set_fallback_netif()`**: traffic outside all `allowed_ip/mask` ranges goes straight out via the physical netif — including source rewrite from tunnel IP to physical IP, with correct re-computation of the IP header checksum and the TCP/UDP pseudo checksum.
- **SYN-ACK self-heal**: lwIP binds `pcb->local_ip` to the default netif's IP (= tunnel IP) at `connect()` time; replies arriving over the fallback path hit the physical IP instead → the 4-tuple match fails and connections hang silently. An RX sniffer on the fallback netif rewrites `pcb->local_ip` on SYN-ACKs to the packet's destination IP (`wg_fixup_synack_pcb()`).
- **Caveat**: the local LAN subnet must not be identical to `allowed_ip` (the direct-subnet match in `ip4_route` always wins over the tunnel).

## Diagnostics API

- **`is_handshake_established()`** — real session state (a session keypair exists). `is_connected()` only checks `netif_is_up` and is true right after `begin()`, handshake or not.
- **`printStatus()`** / `wireguardif_dump_status()` — internal state: keypair flags, handshake timings, counters (`init_tx`, `resp_rx`, `data_tx`, `data_rx_ok`, `rx_drop`, `tx_no_keypair`, …).
- **`debug_status()`** — extra Arduino-side checks (init/UP/handshake combinations incl. typical server-side failure causes).
- **Compile switch `WIREGUARD_DEBUG`** (default **0** in `wireguard.h`, mirrored in `WireGuard.cpp`): at 0 all debug output compiles away — zero flash, zero RAM overhead. Enable with `-DWIREGUARD_DEBUG=1` (automatically applies to both files) or set the define to 1 in *both* files.

## API

```cpp
// with preshared key + keepalive
bool begin(const IPAddress& localIP, const char* privateKey,
           const char* remotePeerAddress, const char* remotePeerPublicKey,
           uint16_t remotePeerPort,
           const char* presharedKey,        // base64 PSK or NULL
           uint16_t keepAlive = 0);         // seconds, 0 = off

// additionally a split-tunnel CIDR (traffic outside it goes out directly)
bool begin(..., const char* presharedKey,
           const char* allowed_ip_cidr,     // e.g. "192.168.99.0"
           uint16_t keepAlive = 0);
```

Poll the session state properly instead of a blind `delay()`:

```cpp
wg.begin(local_ip, priv_key, endpoint, peer_pub, port, psk, allowed_cidr, 15);
uint32_t t0 = millis();
while (millis() - t0 < 10000 && !wg.is_handshake_established()) delay(250);
if (!wg.is_handshake_established()) wg.printStatus();
```

`restore_route()` manually restores the previous default netif.

## Tested on

- BSB-LAN on OLIMEX ESP32-EVB (Ethernet and WiFi), arduino-esp32 core 3.3.x (lwIP 2.2) compiled with Arduino IDE 2.3.10
- Against the WireGuard kernel module (Linux): handshake, tunnel connectivity and split-tunnel internet verified end-to-end

## AI assistance disclosure

The code in this fork was written with the assistance of AI (locally run LLM prompts, no cloud LLMs). Every change was reviewed by a human (der-berni) and verified end-to-end on real hardware.

## License

BSD 3-Clause — fork changes Copyright (c) 2026 der-berni, original Copyright (c) 2021 Kenta Ida / Daniel Hope. See [LICENSE](LICENSE).
