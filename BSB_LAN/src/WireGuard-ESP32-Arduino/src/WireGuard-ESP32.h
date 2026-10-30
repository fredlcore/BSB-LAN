/*
 * WireGuard implementation for ESP32 Arduino by Kenta Ida (fuga@fugafuga.org)
 * SPDX-License-Identifier: BSD-3-Clause
*/

/*
refactor(WireGuard) by der-berni (github.com/der-berni): move lwIP operations to TCP/IP callback thread for thread safety

The ESP32 lwIP stack requires all network interface operations to run in the TCP/IP thread context. Previously, begin() and end() were called directly from the application thread — undefined behavior with potential corruption or silent failures.

Changes:

Wrap begin() initialization in _wireguard_init_callback() dispatched via tcpip_callback(); use a binary semaphore so the caller blocks until the callback completes (5s timeout)
Move end() teardown into _wireguard_end_callback() for same reason
Resolve remote peer hostname via Network.hostByName() instead of lwip_getaddrinfo — avoids calling DNS from lwIP thread directly and works with active Network interface
Add optional allowed_ip_cidr parameter to begin(): when specified, custom allowed-IP/mask is set; the WG interface still becomes the default route, but traffic outside the allowed range is sent out directly via the fallback netif (split tunnel, see wireguardif_set_fallback_netif)
Add restore_route() public method to manually restore the default route after shutdown
Replace esp32-hal-log.h with direct Serial.print output for better Arduino compatibility
Header: rename member wg_netif → wg_netiface, add new begin() overload with allowed_ip_cidr, add is_initialized(), is_connected(), and debug_status() helpers
  
*/

#ifndef WIREGUARD_ESP32_H
#define WIREGUARD_ESP32_H

#pragma once
#include <Arduino.h>
#include <IPAddress.h>
#include "lwip/ip.h"

class WireGuard
{
private:
    bool _is_initialized = false;
    struct netif *wg_netiface;
public:
    bool begin(const IPAddress& localIP, const char* privateKey, const char* remotePeerAddress, const char* remotePeerPublicKey, uint16_t remotePeerPort);
    bool begin(const IPAddress& localIP, const char* privateKey, const char* remotePeerAddress, const char* remotePeerPublicKey, uint16_t remotePeerPort, const char* presharedKey, uint16_t keepAlive = 0);
    bool begin(const IPAddress& localIP, const char* privateKey, const char* remotePeerAddress, const char* remotePeerPublicKey, uint16_t remotePeerPort, const char* presharedKey, const char* allowed_ip_cidr, uint16_t keepAlive = 0);
    
    void end();
    void restore_route();
    bool is_initialized() const { return this->_is_initialized; }
    bool is_connected() {
        return _is_initialized && (wg_netiface != nullptr) && netif_is_up(wg_netiface);
    }
    // True only when a WireGuard session (keypair) with the peer is actually
    // established - is_connected() alone only means the netif was configured.
    bool is_handshake_established();
    // Prints internal device/peer state: keypair flags, handshake counters, drop reasons
    void printStatus();
    void debug_status(void) {
        Serial.println("[WireGuard] === WireGuard Debug Status ===");
        if (_is_initialized) {
            Serial.println("[WireGuard] [x] Initialized: YES");
            if (wg_netiface) {
                Serial.print("[WireGuard] [x] Netif Pointer: 0x"); 
                Serial.println((uint32_t)wg_netiface, HEX);
                
                if (netif_is_up(wg_netiface)) {
                    Serial.println("[WireGuard] [x] Interface: UP");
                    ip_addr_t ip = wg_netiface->ip_addr;
                    Serial.printf("[WireGuard] [x] Local IP: %d.%d.%d.%d\n", ip4_addr1(&ip.u_addr.ip4), ip4_addr2(&ip.u_addr.ip4), ip4_addr3(&ip.u_addr.ip4), ip4_addr4(&ip.u_addr.ip4));
                } else {
                    Serial.println("[WireGuard] [!] Interface: DOWN (No Link)");
                }
            } else {
                Serial.println("[WireGuard] [!] Netif Pointer: NULL");
            }
        } else {
            Serial.println("[WireGuard] [x] Initialized: NO");
        }
    }
};
#endif