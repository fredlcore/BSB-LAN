/*
  Receive multicast UDP packets

  This sketch receives multicast UDP packets from address 239.1.74.74, port 7474
  Uses WiFi ESP8266 module.

  This example is written for a network using WPA encryption.

  Circuit:
   1. On ESP8266 must be running (flashed) WiFiSPIESP application.

   2. Connect the Arduino to the following pins on the esp8266:

            ESP8266         |
    GPIO    NodeMCU   Name  |   STM32F103
   ===================================
     15       D8       SS   |   PA4
     13       D7      MOSI  |   PA7
     12       D6      MISO  |   PA6
     14       D5      SCK   |   PA5
     RESET                  |   PB12

    Note: If the ESP is booting at the moment when the SPI Master (i.e. Arduino) has the Select line HIGH (deselected)
    the ESP8266 WILL FAIL to boot!

*/

#include <WiFiSpi.h>

char ssid[] = "your ssid here"; //  your network SSID (name)
char pass[] = "your password here";    // your network password

#if defined(MCU_STM32F103C8)
const uint8_t RESET_PIN = PB12;  // For STM32F103
#endif

// Note: remoteIP is a multicast address, it should begin with 239.x.x.x or some other
// appropriate multicast address.
// It's not the same as your local IP address (192.168.x.x, for example)!
IPAddress remoteIP(239, 1, 74, 74);

// The remote port must be otherwise unused on any machine that is receiving these packets
int remotePort = 7474;

// Create the UDP object
WiFiSpiUdp udp;

void setup() {
#if defined(MCU_STM32F103C8)
  // Reset PIN
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, HIGH);
#endif

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial.available()) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Reset ESP8266");

#if defined(MCU_STM32F103C8)
  // Reset the ESP
  digitalWrite(RESET_PIN, LOW);
  delay(100);
  digitalWrite(RESET_PIN, HIGH);
  delay(500);
#endif

  // Initialize the library
  WiFiSpi.init(SS, 100000);

  // check for the presence of the shield:
  if (WiFiSpi.status() == WL_NO_SHIELD) {
    Serial.println("Error in communication with the ESP board, halted");
    WiFiSpi.status();
    // don't continue:
    while (true);
  }

  if (! WiFiSpi.checkProtocolVersion())
    Serial.println("Please upgrade the firmware");

  // attempt to connect to Wifi network:
  uint8_t status;
  do {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network.
    status = WiFiSpi.begin(ssid, pass);
  } while (status != WL_CONNECTED);

  Serial.println("Connected to wifi");

  // Start listening for multicast messages
  udp.beginMulticast(remoteIP, remotePort);
}

void loop() {
  // If there's data available, read a packet
  int packetSize = udp.parsePacket();

  // If there's data, read them and print them
  if (packetSize > 0) {
    Serial.print("Incoming packet, size=");  Serial.println(packetSize);
    while (udp.available()) {
      int inp = udp.read();
      if (inp >= ' ' && inp <= 0x7f)
        Serial.print(char(inp));
      else {
        Serial.print(inp);  Serial.print(' ');
      }
    }
    Serial.println();
  }

  delay(100);
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFiSpi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFiSpi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFiSpi.RSSI();
  Serial.print("signal strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}
