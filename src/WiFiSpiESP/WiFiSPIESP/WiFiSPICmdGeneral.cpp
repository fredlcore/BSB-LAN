/*
    SPI Command Processor for ESP8266 communicating as a slave.
    
  Copyright (c) 2017 Jiri Bilek. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "WiFiSPICmd.h"
#include "SPICalls.h"
#include <ESP8266WiFi.h>

// Library version
extern const char* VERSION;
// Protocol version
extern const char* PROTOCOL_VERSION;


/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdGetFwVersion() {
    uint8_t cmd = data[2];
    
    // Test the parameters
    if (data[3] != 0 || data[4] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    replyStart(cmd, 1);
    replyParam((uint8_t*)VERSION, 5);
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdGetMacAddr() {
    uint8_t cmd = data[2];
    
    // Test the parameters
    if (data[3] != 0 || data[4] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }
  
    uint8_t macAddr[WL_MAC_ADDR_LENGTH];
    WiFi.macAddress(macAddr);

    replyStart(cmd, 1);
    replyParam(macAddr, WL_MAC_ADDR_LENGTH);
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdSetIpConfig() {
    uint8_t cmd = data[2];
    
    // Get and test the parameters (5 input parameters)
    if (data[3] != 5) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }
    uint32_t local_ip, gateway, subnet, dns_server1, dns_server2;
    uint8_t dataPos = 4;  // Position in the input buffer

    // Read parameters
    if (getParameter(data, dataPos, reinterpret_cast<uint8_t*>(&local_ip), sizeof(local_ip)) < 0)
        return;  // Failure - received invalid parameter
    if (getParameter(data, dataPos, reinterpret_cast<uint8_t*>(&gateway), sizeof(gateway)) < 0)
        return;  // Failure - received invalid parameter
    if (getParameter(data, dataPos, reinterpret_cast<uint8_t*>(&subnet), sizeof(subnet)) < 0)
        return;  // Failure - received invalid parameter
    if (getParameter(data, dataPos, reinterpret_cast<uint8_t*>(&dns_server1), sizeof(dns_server1)) < 0)
        return;  // Failure - received invalid parameter
    if (getParameter(data, dataPos, reinterpret_cast<uint8_t*>(&dns_server2), sizeof(dns_server2)) < 0)
        return;  // Failure - received invalid parameter

    if (data[dataPos] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }
    
    Serial.printf("Wifi.config, local_ip=%lx, gateway=%lx, subnet=%lx, dns_server1=%lx, dns_server2=%lx\n", local_ip, gateway, subnet, dns_server1, dns_server2);

    uint8_t status = WiFi.config(local_ip, gateway, subnet, dns_server1, dns_server2);

    replyStart(cmd, 1);
    replyParam(&status, 1);
    replyEnd();
}    

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdStartScanNetworks() {
    uint8_t cmd = data[2];
    
    // Test the parameters
    if (data[3] != 0 || data[4] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }
  
    int8_t resp = WiFi.scanNetworks(true, true);

    replyStart(cmd, 1);
    replyParam(reinterpret_cast<const uint8_t*>(&resp), sizeof(resp));
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdScanNetworks() {
    uint8_t cmd = data[2];
    
    // Test the parameters
    if (data[3] != 0 || data[4] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }
      
    int8_t resp = WiFi.scanComplete();

    replyStart(cmd, 1);
    replyParam(reinterpret_cast<const uint8_t*>(&resp), sizeof(resp));
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdGetScannedData() {
    uint8_t cmd = data[2];
    
    // Test the parameters
    if (data[3] != 1 || data[4] != 1 || data[6] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    uint8_t index = data[5];

    String ssid = WiFi.SSID(index);
    int32_t rssi = WiFi.RSSI(index);
    uint8_t encType = WiFi.encryptionType(index);

    replyStart(cmd, 3);
    replyParam(reinterpret_cast<const uint8_t*>(ssid.c_str()), ssid.length());
    replyParam(reinterpret_cast<const uint8_t*>(&rssi), sizeof(rssi));
    replyParam(&encType, sizeof(encType));
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdSoftwareReset() {
    uint8_t cmd = data[2];

    // Test the parameters
    if (data[3] != 0 || data[4] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    replyStart(cmd, 0);
    replyEnd();

    // Wait 500 ms for sending the reply and reset
    delay(500);
    ESP.restart();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdGetProtocolVersion() {
    uint8_t cmd = data[2];
    
    // Test the parameters
    if (data[3] != 0 || data[4] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    replyStart(cmd, 1);
    replyParam((uint8_t*)PROTOCOL_VERSION, 5);
    replyEnd();
}

