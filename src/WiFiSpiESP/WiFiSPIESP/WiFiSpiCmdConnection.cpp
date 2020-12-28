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

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdGetConnStatus() {
    uint8_t cmd = data[2];
    
    // Test the parameters
    if (data[3] != 0 || data[4] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    uint8_t status = WiFi.status();
      
    replyStart(cmd, 1);
    replyParam(&status, 1);
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdSetPassphrase() {
    uint8_t cmd = data[2];
    
    // Get and test the parameters (2 input parameters)
    if (data[3] != 2) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }
    char ssid[WL_SSID_MAX_LENGTH+1];
    char passphrase[WL_WPA_KEY_MAX_LENGTH+1];

    uint8_t dataPos = 4;  // Position in the input buffer

    // Read parameters
    if (getParameterString(data, dataPos, ssid, sizeof(ssid)-1) < 0)
        return;  // Failure - received invalid parameter
    if (getParameterString(data, dataPos, passphrase, sizeof(passphrase)-1) < 0)
        return;  // Failure - received invalid parameter
    
    if (data[dataPos] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    #ifdef _DEBUG
        Serial.printf("Wifi.begin, ssid=%s\n", ssid);
    #endif

    if (WiFi.status() == WL_CONNECTED) {
        disconnect();  // Needed, without disconnecting the WiFi.begin fails
    }
    
    WiFi.mode(WIFI_OFF); 
    WiFi.mode(WIFI_STA); 
    uint8_t status = WiFi.begin(ssid, passphrase);

    replyStart(cmd, 1);
    replyParam(&status, 1);
    replyEnd();
}
    
/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdSetNet() {
    uint8_t cmd = data[2];
    
    // Get and test the parameter
    if (data[3] != 1) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }
    
    char ssid[WL_SSID_MAX_LENGTH+1];

    uint8_t dataPos = 4;  // Position in the input buffer

    // Read parameters
    if (getParameterString(data, dataPos, ssid, sizeof(ssid)-1) < 0)
        return;  // Failure - received invalid parameter
    
    if (data[dataPos] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    #ifdef _DEBUG
        Serial.printf("Wifi.begin, ssid=%s\n", ssid);
    #endif

    if (WiFi.status() == WL_CONNECTED)
        disconnect();

    uint8_t status = WiFi.begin(ssid);

    replyStart(cmd, 1);
    replyParam(&status, 1);
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdDisconnect() {
    uint8_t cmd = data[2];
    
    // Test the parameters
    if (data[3] != 0 || data[4] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    uint8_t status = disconnect();

    replyStart(cmd, 1);
    replyParam(&status, 1);
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdGetIpAddr() {
    uint8_t cmd = data[2];
    
    // Test the parameters
    if (data[3] != 0 || data[4] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }
    
    union {
        uint8_t bytes[4];  // IPv4 address
        uint32_t dword;
    } localIP, subnetMask, gatewayIP;
    
    localIP.dword = WiFi.localIP();
    subnetMask.dword = WiFi.subnetMask();
    gatewayIP.dword = WiFi.gatewayIP();
    
    replyStart(cmd, 3);
    replyParam(localIP.bytes, 4);
    replyParam(subnetMask.bytes, 4);
    replyParam(gatewayIP.bytes, 4);
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdGetCurrSsid() {
    uint8_t cmd = data[2];
    
    // Test the parameters
    if (data[3] !=0 || data[4] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }
    
    replyStart(cmd, 1);
    replyParam(reinterpret_cast<const uint8_t*>(WiFi.SSID().c_str()), WiFi.SSID().length());
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdGetCurrRssi() {
    uint8_t cmd = data[2];
    
    // Test the parameters
    if (data[3] != 0 || data[4] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    int32_t rssi = WiFi.RSSI();
    
    replyStart(cmd, 1);
    replyParam(reinterpret_cast<const uint8_t*>(&rssi), sizeof(rssi));
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdGetCurrBssid() {
    uint8_t cmd = data[2];
    
    // Test the parameters
    if (data[3] != 0 || data[4] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }
  
    replyStart(cmd, 1);
    replyParam(WiFi.BSSID(), WL_MAC_ADDR_LENGTH);
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdGetHostByName() {
    uint8_t cmd = data[2];
    
    // Test the parameters
    if (data[3] != 1) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    char hostName[WL_HOSTNAME_MAX_LENGTH];

    uint8_t dataPos = 4;  // Position in the input buffer

    if (getParameterString(data, dataPos, hostName, sizeof(hostName)-1) < 0)
        return;  // Failure - received invalid parameter
        
    if (data[dataPos] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    IPAddress ipAddress;

    setTxStatus(SPISLAVE_TX_PREPARING_DATA);

    uint8_t status = WiFi.hostByName(hostName, ipAddress);
    
    union {
        uint8_t bytes[4];  // IPv4 address
        uint32_t dword;
    } ipAddr;
    
    if (status == 1)
        ipAddr.dword = ipAddress;
    else
        ipAddr.dword = 0;
    
    replyStart(cmd, 2);
    replyParam(&status, 1);
    replyParam(ipAddr.bytes, 4);
    replyEnd();
}

