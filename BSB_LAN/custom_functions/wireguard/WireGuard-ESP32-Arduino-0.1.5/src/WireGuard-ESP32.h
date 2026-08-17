/*
 * WireGuard implementation for ESP32 Arduino by Kenta Ida (fuga@fugafuga.org)
 * SPDX-License-Identifier: BSD-3-Clause
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
    void debug_status(void) {
        Serial.println("=== WireGuard Debug Status ===");
        if (_is_initialized) {
            Serial.println("[x] Initialized: YES");
            if (wg_netiface) {
                Serial.print("[x] Netif Pointer: 0x"); 
                Serial.println((uint32_t)wg_netiface, HEX);
                
                if (netif_is_up(wg_netiface)) {
                    Serial.println("[x] Interface is UP");
                    // IP Adresse anzeigen (wenn gesetzt)
                    ip_addr_t ip = wg_netiface->ip_addr;
                    Serial.print("     Local IP: ");
                    Serial.print(ip.u_addr.ip4.addr & 0xFF);
                    Serial.print(".");
                    Serial.print((ip.u_addr.ip4.addr >> 8) & 0xFF);
                    Serial.print(".");
                    Serial.print((ip.u_addr.ip4.addr >> 16) & 0xFF);
                    Serial.println((ip.u_addr.ip4.addr >> 24) & 0xFF);
                } else {
                    Serial.println("[!] Interface is DOWN (No Link)");
                }
            } else {
                Serial.println("[!] Netif Pointer: NULL");
            }
        } else {
            Serial.println("[x] Initialized: NO");
        }
    }
};
#endif