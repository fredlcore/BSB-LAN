/*
  ModbusTCP Server for ClearCore Arduino wrapper

  (c)2021 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266

  This code is licensed under the BSD New License. See LICENSE.txt for more info.
*/

#include <Ethernet.h>       // Ethernet library v2 is required

#include <ModbusAPI.h>
#include <ModbusTCPTemplate.h>

class ModbusEthernet : public ModbusAPI<ModbusTCPTemplate<EthernetServer, EthernetClient>> {};

const uint16_t REG = 512;               // Modbus Hreg Offset
const int32_t showDelay = 5000;   // Show result every n'th mellisecond

bool usingDhcp = true;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE }; // MAC address for your controller
IPAddress ip(192, 168, 30, 178); // The IP address will be dependent on your local network
ModbusEthernet mb;               // Declare ModbusTCP instance

// Callback function for client connect. Returns true to allow connection.
bool cbConn(IPAddress ip) {
  Serial.println(ip);
  return true;
}

void setup() {
    Serial.begin(9600);
    uint32_t timeout = 5000;
    uint32_t startTime = millis();
    while (!Serial && millis() - startTime < timeout)
        continue;

    // Get the Ethernet module up and running.
    if (usingDhcp) {
        int dhcpSuccess = Ethernet.begin(mac);
        if (dhcpSuccess)
            Serial.println("DHCP configuration was successful.");
        else {
            Serial.println("DHCP configuration was unsuccessful!");
            Serial.println("Try again using a manual configuration...");
            while (true)
                continue;
        }
    }
    else {
        Ethernet.begin(mac, ip);
    }

    // Make sure the physical link is up before continuing.
    while (Ethernet.linkStatus() == LinkOFF) {
        Serial.println("The Ethernet cable is unplugged...");
        delay(1000);
    }
  mb.server();              // Act as Modbus TCP server
  mb.onConnect(cbConn);
  mb.addHreg(100);          // Expose Holding Register #100
}

void loop() {
  mb.task();                      // Common local Modbus task
  delay(10);
}