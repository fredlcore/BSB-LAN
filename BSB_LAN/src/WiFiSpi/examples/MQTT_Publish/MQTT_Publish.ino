/*
 Publishing in the callback

 Uses the PubSubClient library

  - connects to an MQTT server (broker.hivemq.com)
  - subscribes to the topic "EspSpi/inTopic"
  - when a message is received, republishes it to "EspSpi/outTopic"
  - every 5 seconds writes number in sequence from 1 to "EspSpi/outTopic/msg"

  This example shows how to publish messages within the
  callback function. The callback function header needs to
  be declared before the PubSubClient constructor and the
  actual callback defined afterwards.
  This ensures the client reference in the callback function
  is valid.

  The result could be viewed online on http://www.hivemq.com/demos/websocket-client/

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

    Note: If the ESP is booting at the moment when the SPI Master (i.e. Arduino) has the Select line HIGH (deselected)
    the ESP8266 WILL FAIL to boot!
*/

#include <WiFiSpi.h>
#include <PubSubClient.h>

// WiFi credentials
char ssid[] = "yourNetwork";        // your network SSID (name)
char pass[] = "secretPassword";     // your network password (use for WPA)

// MQTT Broker Address
//IPAddress server(18, 185, 232, 233);  // broker.hivemq.com (check it if the client does not connect, the IP address may change)
const char *server = "broker.hivemq.com";

// Callback function header
void callback(char* topic, byte* payload, unsigned int length);

WiFiSpiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);

// Callback function
void callback(char* topic, byte* payload, unsigned int length) {
  // In order to republish this payload, a copy must be made
  // as the orignal payload buffer will be overwritten whilst
  // constructing the PUBLISH packet.

  // Allocate the correct amount of memory for the payload copy
  byte* p = (byte*)malloc(length);
  // Copy the payload to the new buffer
  memcpy(p, payload, length);
  client.publish("EspSpi/outTopic", p, length);
  // Free the memory
  free(p);
}

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Initialize the WifiSpi library
  WiFiSpi.init();

  // check for the presence of the shield:
  if (WiFiSpi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  if (!WiFiSpi.checkProtocolVersion()) {
    Serial.println("Protocol version mismatch. Please upgrade the firmware");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network
  int status = WL_IDLE_STATUS;     // the Wifi radio's status

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFiSpi.begin(ssid, pass);
  }
  Serial.println("Connected to wifi");
  
  // Connect to mqtt broker
  if (client.connect("arduinoTest")) {
    client.publish("EspSpi/outTopic","hello world");
    client.subscribe("EspSpi/inTopic");
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print(F("Attempting MQTT connection..."));
    
    // Attempt to connect
    if (client.connect("arduinoTest")) {
      Serial.println(F("reconnected"));
      
      // Once connected, publish an announcement...
      client.publish("EspSpi/outTopic", "reconnected");
      
      // ... and resubscribe
      client.subscribe("EspSpi/inTopic");
    } else {
      Serial.print(F("failed, rc="));
      Serial.println(client.state());
    }
  }
}

unsigned long lastMillis = millis();
unsigned int number = 1;

void loop() {
  client.loop();

  // Sending every 5 seconds
  if (lastMillis < millis()) {
    if (!client.connected())
      reconnect();

    char payload[10];
    sprintf(payload, "%u", number); 
    client.publish("EspSpi/outTopic/msg", payload);
    ++number;

    lastMillis = millis() + 5000;
  }
}
