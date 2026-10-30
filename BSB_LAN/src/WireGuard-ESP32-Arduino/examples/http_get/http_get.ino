#include <WiFi.h>
#include <WireGuard-ESP32.h>

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
char allowed_ip_cidr[] = "10.0.0.0";                   // [Peer] AllowedIPs network: traffic in this
                                                       // range goes through the tunnel, everything
                                                       // else out directly (split tunnel)
// TCP target inside VPN
char tcp_target[] = "192.168.0.1";
int tcp_port = 80;

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
    while (now < 1609459200) { // Wait until time is valid (2021+)
        delay(500);
        time(&now);
    }
    Serial.println("Time synced.");

    // Initialize WireGuard: preshared key, keepalive and split-tunnel CIDR.
    // Traffic inside allowed_ip_cidr goes through the tunnel, everything else
    // (incl. internet) leaves directly via WiFi.
    Serial.println("Initializing WireGuard...");
    bool success = wg.begin(
        local_ip,
        private_key,
        endpoint_address,
        public_key,
        endpoint_port,
        strlen(preshared_key) > 0 ? preshared_key : NULL,
        allowed_ip_cidr,
        keepalive);

    if (!success) {
        Serial.println("WireGuard initialization failed!");
        return;
    }

    // begin() only sets up the interface - wait for the real handshake:
    Serial.println("Waiting for WireGuard handshake...");
    uint32_t t0 = millis();
    while (millis() - t0 < 15000 && !wg.is_handshake_established()) {
        delay(250);
    }
    if (wg.is_handshake_established()) {
        Serial.printf("WireGuard session established. VPN IP: %s\n", local_ip.toString().c_str());
    } else {
        Serial.println("Handshake not established yet - check keys/endpoint/server config:");
        wg.printStatus();
    }
}

void loop()
{
    NetworkClient client;   // no heap, no leak
    Serial.printf("Connection to %s:%d", tcp_target, tcp_port);
    if (client.connect(tcp_target, tcp_port, 5000)) {
        Serial.println(" working!");
    } else {
        Serial.println(" blocked or unreachable.");
    }
    client.stop();
    delay(UPDATE_INTERVAL_MS);
}
