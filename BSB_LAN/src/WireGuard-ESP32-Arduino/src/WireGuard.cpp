/*
 * WireGuard implementation for ESP32 Arduino by Kenta Ida (fuga@fugafuga.org)
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "WireGuard-ESP32.h"
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"

#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/ip.h"
#include "lwip/netdb.h"

#include "esp_log.h"

#include "lwip/tcpip.h"
#include "freertos/semphr.h"

#include "Network.h"
#include <WiFi.h>
#include "lwip/ip_addr.h"
#include <arpa/inet.h>

extern "C" {
#include "wireguardif.h"
#include "wireguard-platform.h"
bool wireguard_base64_decode(const char *str, uint8_t *out, size_t *outlen);
}

/* Same switch as in wireguard.h. The C header must NOT be included here:
 * it has no extern "C" guards and its wireguard_peer_index() function
 * conflicts with the static peer-index variable below. To enable WG debug
 * output use -DWIREGUARD_DEBUG=1 (affects both files) or flip the default
 * in BOTH this file and wireguard.h. */
#ifndef WIREGUARD_DEBUG
#define WIREGUARD_DEBUG 0
#endif

// WireGuard instance variables (file-global)
static struct netif wg_netif_struct = {0};
static struct netif *wg_netif = NULL;
static struct netif *previous_default_netif = NULL;
static uint8_t wireguard_peer_index = WIREGUARDIF_INVALID_INDEX;

// Static buffer for decoded preshared key
static uint8_t psk_decoded[32];

// Semaphore to wait for initialization to complete in the LWIP thread
static SemaphoreHandle_t wg_init_semaphore = NULL; 
// Status flag for returning from the callback
static bool wg_init_result = false;

// Structure for passing parameters to the TCP/IP callback
struct InitArgs {
    IPAddress localIP;             // Kopie, kein Pointer
    const char* privateKey;        // Pointer ist hier ok, solange String lebt
    // const char* remotePeerAddress;
    IPAddress remotePeerIPAddress;
    const char* remotePeerPublicKey;
    uint16_t remotePeerPort;
    const char* presharedKey;
    uint16_t keepAlive;
    const char* allowed_ip_cidr;
};

int ip_cidr_parse_ipv4(const char *str, ip_addr_t *ip, ip_addr_t *mask) {
    if (!str || !ip || !mask) return -1;

    char ip_part[64];
    int cidr = 0;

    char *slash = strchr(str, '/');
    if (!slash || (size_t)(slash - str) >= sizeof(ip_part)) {
        return -1;
    }

    strncpy(ip_part, str, slash - str);
    ip_part[slash - str] = '\0';

    if (ipaddr_aton(ip_part, ip) != 1) return -1;

    cidr = atoi(slash + 1);
    if (cidr < 0 || cidr > 32) return -1;

    mask->u_addr.ip4.addr = htonl((uint32_t)(-1U << (32 - cidr)));
    mask->type = IPADDR_TYPE_V4;

    return 0;
}

// Helper function for DNS resolution on a popular interface (Wi-Fi or Ethernet)
bool resolveHostname(const char* hostname, IPAddress& result) {
#if WIREGUARD_DEBUG
    Serial.print("[WireGuard] Resolves a hostname: "); Serial.println(hostname);
#endif /* WIREGUARD_DEBUG */
    // Try Wi-Fi first (enabled by default on the ESP32)
    int status = -1;

    status = Network.hostByName(hostname, result);
    if (status >= 0) {
#if WIREGUARD_DEBUG
        Serial.print("[WireGuard]    -> DNS OK: ");
        Serial.println(result);
#endif /* WIREGUARD_DEBUG */
        return true;
    }

    if (!result) {
#if WIREGUARD_DEBUG
        Serial.println("[WireGuard]    -> ERROR: No IP address found!");
#endif /* WIREGUARD_DEBUG */
        return false;
    }

    return true;
}

// Callback for initialization (runs in the TCP/IP thread)
static void _wireguard_init_callback(void *arg) {
    InitArgs *args = (InitArgs *)arg;
    
#if WIREGUARD_DEBUG
    Serial.println("[WireGuard] Callback startet");
#endif /* WIREGUARD_DEBUG */

    struct wireguardif_init_data wg;
    struct wireguardif_peer peer;

    // Create a copy of the IP address for local use
    ip_addr_t ipaddr = IPADDR4_INIT(static_cast<uint32_t>(args->localIP));
    ip_addr_t netmask = IPADDR4_INIT_BYTES(255, 255, 255, 255);
    ip_addr_t gateway = IPADDR4_INIT_BYTES(0, 0, 0, 0);

    // Validate arguments (basic check)
    if (!args->privateKey || !args->remotePeerPublicKey || args->remotePeerPort == 0) {
#if WIREGUARD_DEBUG
        Serial.println("[WireGuard] Error: Incorrect parameters (privateKey or remoteIP is missing).");
#endif /* WIREGUARD_DEBUG */
        wg_init_result = false;
        if(wg_init_semaphore) xSemaphoreGive(wg_init_semaphore);
        return;
    }
    
    // Setup the WireGuard device structure
    wg.private_key = args->privateKey;
    wg.listen_port = args->remotePeerPort;

    // // Initialise the first WireGuard peer structure
    wireguardif_peer_init(&peer);

    if (!args->remotePeerIPAddress) {
        // Fallback wenn NULL (optional, z.B. 0.0.0.0)
#if WIREGUARD_DEBUG
        Serial.println("[WireGuard] No remote peer IP-Address provided");
#endif /* WIREGUARD_DEBUG */
        wg_init_result = false;
        if(wg_init_semaphore) xSemaphoreGive(wg_init_semaphore);
        return;
    } else {
#if WIREGUARD_DEBUG
        Serial.print("[WireGuard] Set Endpoint IP:");
        Serial.println(args->remotePeerIPAddress);
#endif /* WIREGUARD_DEBUG */

        peer.endpoint_ip.u_addr.ip4.addr = static_cast<uint32_t>(args->remotePeerIPAddress);
        
#if WIREGUARD_DEBUG
        Serial.print("[WireGuard] peer.endpoint_ip is:");
        Serial.print(((uint8_t*)&peer.endpoint_ip.u_addr.ip4.addr)[0]);
        Serial.print(".");
        Serial.print(((uint8_t*)&peer.endpoint_ip.u_addr.ip4.addr)[1]);
        Serial.print(".");
        Serial.print(((uint8_t*)&peer.endpoint_ip.u_addr.ip4.addr)[2]);
        Serial.print(".");
        Serial.println(((uint8_t*)&peer.endpoint_ip.u_addr.ip4.addr)[3]);
#endif /* WIREGUARD_DEBUG */

    }

#if WIREGUARD_DEBUG
    Serial.println("[WireGuard] Register the new WireGuard network interface with lwIP...");
#endif /* WIREGUARD_DEBUG */
    wg_netif = netif_add(&wg_netif_struct, ip_2_ip4(&ipaddr), ip_2_ip4(&netmask), ip_2_ip4(&gateway), &wg, &wireguardif_init, &ip_input);
    
    if(!wg_netif) {
#if WIREGUARD_DEBUG
        Serial.println("[WireGuard] failed to initialize WG netif.");
#endif /* WIREGUARD_DEBUG */
        wg_init_result = false;
        if(wg_init_semaphore) xSemaphoreGive(wg_init_semaphore);
        return;
    }

    // Mark the interface as administratively up
#if WIREGUARD_DEBUG
    Serial.println("[WireGuard] Set we_netif UP...");
#endif /* WIREGUARD_DEBUG */
    netif_set_up(wg_netif);

    peer.public_key = args->remotePeerPublicKey;

    // Decode and set preshared key if provided
    const char* psk = (args->presharedKey) ? args->presharedKey : NULL;
    size_t psk_len = sizeof(psk_decoded);
    
    if (psk != NULL && strlen(psk) > 0) {
        // WireGuard keys are base64-encoded and must be decoded before use.
        // Note: wireguard_base64_decode is defined extern
        if (wireguard_base64_decode(psk, psk_decoded, &psk_len) && psk_len == 32) {
            peer.preshared_key = psk_decoded;
#if WIREGUARD_DEBUG
            Serial.println("[WireGuard] preshared key set");
#endif /* WIREGUARD_DEBUG */
        } else {
#if WIREGUARD_DEBUG
            Serial.println("[WireGuard] failed to decode preshared key");
#endif /* WIREGUARD_DEBUG */
            peer.preshared_key = NULL;
        }
    } else {
        peer.preshared_key = NULL;
    }

    // Set keepalive interval
    if (args->keepAlive > 0) {
        peer.keep_alive = args->keepAlive;
#if WIREGUARD_DEBUG
        Serial.print("[WireGuard] keepalive: ");
        Serial.print(args->keepAlive);
        Serial.println(" seconds");
#endif /* WIREGUARD_DEBUG */
    }
    ip_addr_t allowed_ip, allowed_mask;
    bool custom_allowed_ip = false;

    // Allow all IPs through tunnel
    if (args->allowed_ip_cidr && ip_cidr_parse_ipv4(args->allowed_ip_cidr, &allowed_ip, &allowed_mask) == 0 ) {
#if WIREGUARD_DEBUG
        Serial.println("[WireGuard] allowed_ip configured...");
#endif /* WIREGUARD_DEBUG */
        peer.allowed_ip = allowed_ip;
        peer.allowed_mask = allowed_mask;
        custom_allowed_ip = true;
    } else {
        allowed_ip = IPADDR4_INIT_BYTES(0, 0, 0, 0);
        peer.allowed_ip = allowed_ip;
        allowed_mask = IPADDR4_INIT_BYTES(0, 0, 0, 0);
        peer.allowed_mask = allowed_mask;
    }
#if WIREGUARD_DEBUG
    Serial.print("[WireGuard] allowed_ip: ");
    Serial.print(((uint8_t*)&allowed_ip.u_addr.ip4.addr)[0]);
    Serial.print(".");
    Serial.print(((uint8_t*)&allowed_ip.u_addr.ip4.addr)[1]);
    Serial.print(".");
    Serial.print(((uint8_t*)&allowed_ip.u_addr.ip4.addr)[2]);
    Serial.print(".");
    Serial.println(((uint8_t*)&allowed_ip.u_addr.ip4.addr)[3]);
    Serial.print("[WireGuard] allowed_mask: ");
    Serial.print(((uint8_t*)&allowed_mask.u_addr.ip4.addr)[0]);
    Serial.print(".");
    Serial.print(((uint8_t*)&allowed_mask.u_addr.ip4.addr)[1]);
    Serial.print(".");
    Serial.print(((uint8_t*)&allowed_mask.u_addr.ip4.addr)[2]);
    Serial.print(".");
    Serial.println(((uint8_t*)&allowed_mask.u_addr.ip4.addr)[3]);
#endif /* WIREGUARD_DEBUG */

    peer.endport_port = args->remotePeerPort;

#if WIREGUARD_DEBUG
    Serial.println("[WireGuard] Initialize the platform (WireGuard Hardware Crypto Init)...");
#endif /* WIREGUARD_DEBUG */
    wireguard_platform_init();

#if WIREGUARD_DEBUG
    Serial.println("[WireGuard] Register the new WireGuard peer with the network interface...");
#endif /* WIREGUARD_DEBUG */
    wireguardif_add_peer(wg_netif, &peer, &wireguard_peer_index);
    if (wireguard_peer_index == WIREGUARDIF_INVALID_INDEX) {
#if WIREGUARD_DEBUG
        Serial.println("[WireGuard] ERROR: Unable to register the peer.");
#endif /* WIREGUARD_DEBUG */
        wg_init_result = false;
        if(wg_init_semaphore) xSemaphoreGive(wg_init_semaphore);
        return;
    }

    if ((wireguard_peer_index != WIREGUARDIF_INVALID_INDEX) && !ip_addr_isany(&peer.endpoint_ip)) {
#if WIREGUARD_DEBUG
        Serial.println("[WireGuard] connecting wireguard...");
#endif /* WIREGUARD_DEBUG */
        
#if WIREGUARD_DEBUG
        Serial.println("[WireGuard] Start outbound connection to peer...");
#endif /* WIREGUARD_DEBUG */
        wireguardif_connect(wg_netif, wireguard_peer_index);

        // Save the current default interface for restoring when shutting down
        previous_default_netif = netif_default;

        // Split tunnel support: traffic destined outside this peer's allowed_ip
        // is sent directly out the old default interface instead of ERR_RTE.
        wireguardif_set_fallback_netif(wg_netif, previous_default_netif);

        // The WG netif does its own per-destination cryptokey routing:
        // allowed_ip matches go through the tunnel, everything else via fallback.
        // (lwIP's ip4_route sends destinations in a directly connected subnet -
        // e.g. the local LAN - straight to that netif, never through us.)
#if WIREGUARD_DEBUG
        Serial.println("[WireGuard] Set default interface to WG device...");
#endif /* WIREGUARD_DEBUG */
        netif_set_default(wg_netif);

        // IMPORTANT: Wait a moment to give the handshake time to complete
        delay(1000); 
    }
    
    wg_init_result = true;

    // Indicate that initialization is complete
    if(wg_init_semaphore) xSemaphoreGive(wg_init_semaphore);
}

// Shutdown callback (runs in the TCP/IP thread)
static void _wireguard_end_callback(void *arg) {
    struct netif *default_netif = nullptr;
    if (previous_default_netif != nullptr) default_netif = previous_default_netif;
    
    // Restore the default interface.
    netif_set_default(default_netif);
    previous_default_netif = nullptr;
    
    // Disconnect the WG interface.
    if(wg_netif) wireguardif_disconnect(wg_netif, wireguard_peer_index);
    
    // Remove peer from the WG interface
    if(wg_netif) wireguardif_remove_peer(wg_netif, wireguard_peer_index);
    wireguard_peer_index = WIREGUARDIF_INVALID_INDEX;
    
    // Shutdown the wireguard interface.
    if(wg_netif) wireguardif_shutdown(wg_netif);
    
    // Remove the WG interface;
    if(wg_netif) netif_remove(wg_netif);
    wg_netif = nullptr;
}

static void _wireguard_restore_route_callback(void *arg) {
    if (previous_default_netif != nullptr) {
#if WIREGUARD_DEBUG
        Serial.println("[WireGuard] Restore the default interface.\r\n");
#endif /* WIREGUARD_DEBUG */
        netif_set_default(previous_default_netif); 
        previous_default_netif = nullptr;
    }
}

// ---------------------------------------------------------------------
// Public Interface Functions (WireGuard Class)
// ---------------------------------------------------------------------

bool WireGuard::begin(const IPAddress& localIP, const char* privateKey, const char* remotePeerAddress, const char* remotePeerPublicKey, uint16_t remotePeerPort) {
    return begin(localIP, privateKey, remotePeerAddress, remotePeerPublicKey, remotePeerPort, NULL, NULL, 0);
}
bool WireGuard::begin(const IPAddress& localIP, const char* privateKey, const char* remotePeerAddress, const char* remotePeerPublicKey, uint16_t remotePeerPort, const char* presharedKey, uint16_t keepAlive) {
    return begin(localIP, privateKey, remotePeerAddress, remotePeerPublicKey, remotePeerPort, presharedKey, NULL, keepAlive);
}
bool WireGuard::begin(const IPAddress& localIP, const char* privateKey, const char* remotePeerAddress, const char* remotePeerPublicKey, uint16_t remotePeerPort, const char* presharedKey, const char* allowed_ip_cidr, uint16_t keepAlive) {
    // Create the semaphore once (if it doesn't already exist)
    if (!wg_init_semaphore) {
        wg_init_semaphore = xSemaphoreCreateBinary();
    }

    // Reset Status
    wg_init_result = false;
    
    IPAddress resolved_vpn_ip;

#if WIREGUARD_DEBUG
    Serial.print("[WireGuard] remotePeerAddress:");
    Serial.println(remotePeerAddress);
#endif /* WIREGUARD_DEBUG */

    if (!resolveHostname(remotePeerAddress, resolved_vpn_ip)) {
#if WIREGUARD_DEBUG
        Serial.println("[WireGuard] [FATAL] DNS resolution failed! Use a static IP address instead of a domain name.");
#endif /* WIREGUARD_DEBUG */
        return false;
    }
#if WIREGUARD_DEBUG
    Serial.print("[WireGuard] Resolved to IP-Address:");
    Serial.println(resolved_vpn_ip);
#endif /* WIREGUARD_DEBUG */

    InitArgs args;
    args.localIP = localIP;        
    args.privateKey = privateKey;
    args.remotePeerIPAddress = resolved_vpn_ip;
    args.remotePeerPublicKey = remotePeerPublicKey;
    args.remotePeerPort = remotePeerPort;
    args.presharedKey = presharedKey;
    args.keepAlive = keepAlive;
    args.allowed_ip_cidr = allowed_ip_cidr;

    // Request Initialization in a TCP/IP Context (Secure Call)
    err_t ret = tcpip_callback(_wireguard_init_callback, &args);

    if (ret == ERR_OK) {
#if WIREGUARD_DEBUG
        Serial.print("[WireGuard] callback:");
        Serial.println(ret);
#endif /* WIREGUARD_DEBUG */

        // Waiting for the semaphore signal from the callback 
        BaseType_t status = xSemaphoreTake(wg_init_semaphore, pdMS_TO_TICKS(5000));
        
        if (status == pdTRUE) {
            // Successful only if `callback` is set to `true`
            this->_is_initialized = wg_init_result;
            this->wg_netiface = wg_netif;
            return wg_init_result;
        } else {
#if WIREGUARD_DEBUG
            Serial.println("[WireGuard] timeout waiting for initialization");
#endif /* WIREGUARD_DEBUG */
            return false;
        }
    } else {
#if WIREGUARD_DEBUG
        Serial.print("[WireGuard] failed to schedule init callback:");
        Serial.println(ret);
#endif /* WIREGUARD_DEBUG */
        return false;
    }
}

void WireGuard::end() {
    if( !this->_is_initialized ) return; 
    
    // TCP/IP Queue a callback for a clean termination
    tcpip_callback(_wireguard_end_callback, NULL); 
    
    // A short delay to give the callback time to start
    delay(20);
    
    this->_is_initialized = false;
}

void WireGuard::restore_route() {
    tcpip_callback(_wireguard_restore_route_callback, NULL);
}

bool WireGuard::is_handshake_established() {
    if (!_is_initialized || wg_netiface == nullptr || wireguard_peer_index == WIREGUARDIF_INVALID_INDEX) {
        return false;
    }
    ip_addr_t current_ip;
    u16_t current_port = 0;
    return (wireguardif_peer_is_up(wg_netiface, wireguard_peer_index, &current_ip, &current_port) == ERR_OK);
}

void WireGuard::printStatus() {
#if WIREGUARD_DEBUG
    Serial.println(F("[WireGuard] ---- detailed internal state ----"));
    if (!_is_initialized || wg_netiface == nullptr) {
        Serial.println(F("[WireGuard] not initialized - nothing to dump"));
        return;
    }
    wireguardif_dump_status(wg_netiface);
    Serial.print(F("[WireGuard] handshake established: "));
    Serial.println(is_handshake_established() ? F("YES") : F("NO"));
#endif /* WIREGUARD_DEBUG */
}