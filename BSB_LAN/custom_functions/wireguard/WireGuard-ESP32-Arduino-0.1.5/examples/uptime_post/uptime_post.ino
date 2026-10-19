#include <WiFi.h>
#include <WireGuard-ESP32.h>
#include <HTTPClient.h>
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

static constexpr const uint32_t UPDATE_INTERVAL_MS = 5000;

static WireGuard wg;
static HTTPClient httpClient;

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
    while (now < 1609459200) { // Wait until time is valid (2021+)
        delay(500);
        time(&now);
    }
    Serial.println("Time synced.");

    // Disable task watchdog during WireGuard init (ESP-IDF v5 workaround)
    esp_task_wdt_deinit();

    // Save WiFi as default interface before WireGuard takes over
    struct netif *wifi_netif = netif_default;

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

    // Restore WiFi as default outbound interface (split tunnel)
    // VPN traffic still works for inbound connections
    if (wifi_netif) {
        netif_set_default(wifi_netif);
        Serial.println("Split tunnel: WiFi is default outbound route");
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
    // Example: POST uptime to an HTTP endpoint
    WiFiClient client;

    if (!client.connect("httpbin.org", 80)) {
        Serial.println("Failed to connect...");
        delay(5000);
        return;
    }

    uint64_t uptime_msec = millis();
    Serial.printf("Sending uptime %lu [ms]\r\n", uptime_msec);

    String json = "{\"uptime_msec\":";
    json.concat(static_cast<unsigned long>(uptime_msec));
    json += "}";

    client.printf("POST /post HTTP/1.1\r\n");
    client.printf("Host: httpbin.org\r\n");
    client.printf("Connection: close\r\n");
    client.printf("Content-Type: application/json\r\n");
    client.printf("Content-Length: %d\r\n\r\n", json.length());
    client.print(json);

    while (client.connected()) {
        auto line = client.readStringUntil('\n');
        Serial.println(line);
        if (line == "\r") break;
    }

    delay(UPDATE_INTERVAL_MS);
}
