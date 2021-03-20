/*

 This example connects to an unencrypted Wifi network.
 Then it prints the MAC address of the Wifi module,
 the IP address obtained, and other network details.

 Circuit:
   1. On ESP8266 must be running (flashed) WiFiSPIESP application.
    
   2. Connect the master (Arduino or STM32F103) to the following pins on the esp8266:

            ESP8266         |        |
    GPIO    NodeMCU   Name  |   Uno  | STM32F103
  ===============================================
     15       D8       SS   |   D10  |    PA4
     13       D7      MOSI  |   D11  |    PA7
     12       D6      MISO  |   D12  |    PA6
     14       D5      SCK   |   D13  |    PA5

    Note: If the ESP is booting at a moment when the SPI Master (i.e. Arduino) has the Select line HIGH (deselected)
    the ESP8266 WILL FAIL to boot!

 original sketch for WiFi library created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 
 modified for WiFiSpi library 14 Mar 2017
 by Jiri Bilek
 */
 
#include <WiFiSpi.h>

// WiFi credentials
char ssid[] = "yourNetwork";     // your network SSID (name)
char pass[] = "secretPassword";  // your network password

int status = WL_IDLE_STATUS;     // the Wifi radio's status

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Initialize the WifiSpi library
  WiFiSpi.init();

  // check for the presence of the ESP module:
  if (WiFiSpi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi module not present");
    // don't continue:
    while (true);
  }

  if (!WiFiSpi.checkProtocolVersion()) {
    Serial.println("Protocol version mismatch. Please upgrade the firmware");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFiSpi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();
}

void loop() {
  // check the network connection once every 10 seconds:
  delay(10000);
  printCurrentNet();
}

void printWifiData() {
  // print your WiFi module's IP address:
  IPAddress ip = WiFiSpi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFiSpi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFiSpi.SSID());

  // print the MAC address of the router you're attached to:
  byte *bssid = WiFiSpi.BSSID();
  Serial.print("BSSID: ");
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);

  // print the received signal strength:
  long rssi = WiFiSpi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);
}
