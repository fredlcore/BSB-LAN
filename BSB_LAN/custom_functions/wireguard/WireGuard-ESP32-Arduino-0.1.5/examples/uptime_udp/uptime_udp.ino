#include <WiFi.h>
#include <WireGuard-ESP32.h>
#include <WiFiUdp.h>
#include "lwip/netif.h"
#include "esp_task_wdt.h"

// WiFi configuration --- UPDATE these for your WiFi network
char ssid[] = "your-ssid";
char password[] = "your-password";

// WireGuard configuration --- UPDATE these from your .conf file
char private_key[] = "your-private-key-base64";       // [Interface] PrivateKey
IPAddress local_ip(10, 0, 0, 2);                      // [Interface] Address
char public_key[] = "peer-public-key-base64";          // [Peer] PublicKey
char preshared_key[] = "preshared-key-base64";         // [Peer] PresharedKey (or "" to disable)
char endpoint_address[] = "vpn.example.com";           // [Peer] Endpoint
int endpoint_port = 51820;                             // [Peer] Endpoint port
int keepalive = 25;                                    // [Peer] PersistentKeepalive

// UDP target inside VPN
char udp_target[] = "10.0.0.1";
int udp_port = 23080;

static constexpr const uint32_t UPDATE_INTERVAL_MS = 5000;

static WireGuard wg;

void setup()
{
    Serial.begin(115200);

    // Connect to WiFi
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    while (!WiFi.isConnected()) {
        delay(1000);
    }
    Serial.printf("WiFi connected. IP: %s\n", WiFi.localIP().toString().c_str());

    // Sync time via NTP (required before WireGuard init)
    Serial.println("Syncing time via NTP...");
    configTime(0, 0, "pool.ntp.org", "time.google.com");
    time_t now = 0;
    while (now < 1609459200) {
        delay(500);
        time(&now);
    }
    Serial.println("Time synced.");

    // Disable task watchdog during WireGuard init (ESP-IDF v5 workaround)
    esp_task_wdt_deinit();

    // Initialize WireGuard with preshared key and keepalive
    Serial.println("Initializing WireGuard...");
    bool success = wg.begin(
        local_ip,
        private_key,
        endpoint_address,
        public_key,
        endpoint_port,
        strlen(preshared_key) > 0 ? preshared_key : NULL,
        keepalive);

    if (success) {
        Serial.printf("WireGuard connected. VPN IP: %s\n", local_ip.toString().c_str());
    } else {
        Serial.println("WireGuard initialization failed!");
    }

    // Re-enable task watchdog
    esp_task_wdt_config_t wdt_cfg = {
        .timeout_ms = 5000,
        .idle_core_mask = 0,
        .trigger_panic = false,
    };
    esp_task_wdt_init(&wdt_cfg);
}

void loop()
{
    static uint64_t send_count = 0;
    WiFiUDP client;

    if (!client.beginPacket(udp_target, udp_port)) {
        Serial.println("Failed to begin packet...");
        delay(5000);
        return;
    }

    uint64_t uptime_msec = millis();
    uint8_t buffer[16];
    buffer[ 0] = (uptime_msec >>  0) & 0xff;
    buffer[ 1] = (uptime_msec >>  8) & 0xff;
    buffer[ 2] = (uptime_msec >> 16) & 0xff;
    buffer[ 3] = (uptime_msec >> 24) & 0xff;
    buffer[ 4] = (uptime_msec >> 32) & 0xff;
    buffer[ 5] = (uptime_msec >> 40) & 0xff;
    buffer[ 6] = (uptime_msec >> 48) & 0xff;
    buffer[ 7] = (uptime_msec >> 56) & 0xff;
    buffer[ 8] = (send_count  >>  0) & 0xff;
    buffer[ 9] = (send_count  >>  8) & 0xff;
    buffer[10] = (send_count  >> 16) & 0xff;
    buffer[11] = (send_count  >> 24) & 0xff;
    buffer[12] = (send_count  >> 32) & 0xff;
    buffer[13] = (send_count  >> 40) & 0xff;
    buffer[14] = (send_count  >> 48) & 0xff;
    buffer[15] = (send_count  >> 56) & 0xff;

    Serial.printf("Sending uptime %lu [ms], count=%llu\r\n", uptime_msec, send_count);
    client.write(buffer, sizeof(buffer));
    client.endPacket();

    send_count++;
    delay(UPDATE_INTERVAL_MS);
}
