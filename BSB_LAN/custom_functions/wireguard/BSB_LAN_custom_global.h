
/*
source: https://github.com/JULITHCH/arduino-wireguard

refactor(WireGuard) by der-berni (github.com/der-berni): move lwIP operations to TCP/IP callback thread for thread safety

The ESP32 lwIP stack requires all network interface operations to run in the TCP/IP thread context. Previously, begin() and end() were called directly from the application thread — undefined behavior with potential corruption or silent failures.

Changes:

Wrap begin() initialization in _wireguard_init_callback() dispatched via tcpip_callback(); use a binary semaphore so the caller blocks until the callback completes (5s timeout)
Move end() teardown into _wireguard_end_callback() for same reason
Resolve remote peer hostname via Network.hostByName() instead of lwip_getaddrinfo — avoids calling DNS from lwIP thread directly and works with active Network interface
Add optional allowed_ip_cidr parameter to begin(): when specified, custom allowed-IP/mask is set and the WG interface is NOT made the default route (preserves existing network routing)
Add restore_route() public method to manually restore the default route after shutdown
Replace esp32-hal-log.h with direct Serial.print output for better Arduino compatibility
Header: rename member wg_netif → wg_netiface, add new begin() overload with allowed_ip_cidr, add is_initialized(), is_connected(), and debug_status() helpers
  
*/

// you need to copy the folder WireGuard-ESP32-Arduino-0.1.5 from custom_functions/wireguard to src

#include <src/WireGuard-ESP32-Arduino-0.1.5/src/WireGuard-ESP32.h>
#include "lwip/netif.h"

static WireGuard wg;
static bool wg_connected = false;
static NetworkClient *httpclient = new NetworkClient();

// WireGuard configuration
const char* privateKey = "...";                     // [Interface] PrivateKey
IPAddress wg_local_ip(10, 0, 0, 2);                 // [Interface] Address
const char* remotePeerPublicKey = "...";            // [Peer] PublicKey
const char* remotePeerAddress = "vpn.example.com";  // [Peer] Endpoint Address
const int   remotePeerPort = 50821;                 // [Peer] Endpoint Port
const char* presharedKey = "...";                   // [Peer] Preshared Key
const uint16_t keepAlive = 10;
const char* checkIPAddress = "192.168.0.2";
const int checkIPAddressPort = 8123;
// const char* allowed_ip_cidr = "192.168.0.1/24";
const char* allowed_ip_cidr = "";

void debug_wireguard(void) {
    wg.debug_status();
    
    // Additional Hardware Checks
    if (wg.is_initialized() && !wg.is_connected()) {
        Serial.println("STATUS: Initialized = TRUE, but Interface NOT UP.");
        Serial.println("       --> Handshake failed or peer is unreachable.");
    }
}

void wg_connect() {
    if (!wg_connected) {
        Serial.println("Initializing WireGuard...");

        bool wg_success = wg.begin(
            wg_local_ip,
            privateKey,
            remotePeerAddress,
            remotePeerPublicKey,
            remotePeerPort,
            presharedKey,
            allowed_ip_cidr,
            keepAlive
        );
        if (!wg_success) {
            Serial.println("[FAIL] WG begin() returned false (timeout or parameter error).");
            debug_wireguard();
        } else {
            // Waiting for Stabilization
            Serial.println("Wait 5 seconds for the handshake...");
            delay(5000); 
            
            if (wg.is_connected()) {
                wg_connected = true;
                Serial.println("WireGuard is UP.");
                if (httpclient->connect("8.8.8.8", 53, 5000)) {
                    Serial.println("Yes, Internet is working via WireGuard!\r\n");
                    // Jetzt optional DNS testen
                    httpclient->stop();

                    if (httpclient->connect("google.com", 80, 3000)) {
                        Serial.println("DNS Resolution also working!\r\n");
                    } else {
                        Serial.println("Internet OK, but DNS might be blocked.\r\n");
                    }
                    httpclient->stop();

                    Serial.print("Connection to ");
                    Serial.print(checkIPAddress);
                    Serial.print(":");
                    Serial.println(String(checkIPAddressPort));
                    if (httpclient->connect(checkIPAddress, checkIPAddressPort, 5000)) {
                        Serial.println(" also working!\r\n");
                    } else {
                        Serial.println("might be blocked.\r\n");
                    }
                    httpclient->stop();
                } else {
                    Serial.println("No Internet! WireGuard route is up, but no connectivity.\r\n");
                    httpclient->stop();
                }
            } else {
                Serial.println("WireGuard interface DOWN or not initialized.\r\n");
                debug_wireguard();
            }
        }
    }
}