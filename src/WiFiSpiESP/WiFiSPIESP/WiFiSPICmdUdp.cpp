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
#include <WiFiUdp.h>

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdBeginUdpPacket() {
    uint8_t cmd = data[2];
    
    // Get and test the parameters (3 input parameters)
    if (data[3] != 3) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }
    
    int32_t ipAddr;
    uint16_t port;
    uint8_t sock;

    uint8_t dataPos = 4;  // Position in the input buffer

    // Read parameters
    if (getParameter(data, dataPos, reinterpret_cast<uint8_t*>(&ipAddr), sizeof(ipAddr)) < 0)
        return;  // Failure - received invalid parameter
    if (getParameter(data, dataPos, reinterpret_cast<uint8_t*>(&port), sizeof(port)) < 0)
        return;  // Failure - received invalid parameter
    if (getParameter(data, dataPos, &sock, sizeof(sock)) < 0)
        return;  // Failure - received invalid parameter
    if (sock >= MAX_SOCK_NUM)
        return;  // Invalid socket number
    
    if (data[dataPos] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    setTxStatus(SPISLAVE_TX_PREPARING_DATA);
    
    #ifdef _DEBUG
        Serial.printf("WifiUdp.beginUdpPacket, sock=%d, ip=%s, port=%d\n", sock, IPAddress(ipAddr).toString().c_str(), port);
    #endif
    
    uint8_t status;
    
    if (serversUDP[sock] != nullptr)
        status = serversUDP[sock]->beginPacket(IPAddress(ipAddr), port);
    else
        status = 0;

    replyStart(cmd, 1);
    replyParam(&status, 1);
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdInsertDatabuf() {
    uint8_t cmd = data[2];
    
    // Get and test the input parameter
    if (data[3] != 2 || data[4] != 1) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    uint8_t sock = data[5];
    if (sock >= MAX_SOCK_NUM)
        return;  // Invalid socket number

    uint16_t len = data[6] | (data[7] << 8);

    // Limit the length to 4000 characters
    // TODO: Remove the limit
    if (len > 4000) {
        #ifdef _DEBUG
            Serial.println(F("Too much data (>4000 bytes)."));
        #endif
        return;  // Failure
    }

    uint8_t dataPos = 8;  // Position in the input buffer

    // Allocate a buffer
    uint8_t* buffer = static_cast<uint8_t*>(malloc(len));
    if (buffer == nullptr) {
        #ifdef _DEBUG
            Serial.printf("Malloc (%d) failed.\n", len);
        #endif
        return;  // Failure
    }

    // Read input data into the buffer
    uint8_t* buf = buffer;
    for (uint16_t i = 0;  i < len;  ++i)
    {
        // Get next character
        int16_t b = readByte(data, dataPos);
        if (b < 0) {
            #ifdef _DEBUG
                Serial.println(F("Not enough data."));
            #endif
            return;  // Failure
        }
    
        *buf++ = b;
    }

    if (serversUDP[sock] != nullptr)
        len = serversUDP[sock]->write(static_cast<const uint8_t*>(buffer), len);
    else
        len = 0;

    free(buffer);

    replyStart(cmd, 1);
    replyParam(reinterpret_cast<const uint8_t *>(&len), sizeof(len));
    replyEnd();    
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdSendDataUdp() {
    uint8_t cmd = data[2];
    
    // Get and test the input parameter
    if (data[3] != 1 || data[4] != 1 || data[6] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    uint8_t sock = data[5];
    if (sock >= MAX_SOCK_NUM)
        return;  // Invalid socket number

    uint8_t status;
    
    if (serversUDP[sock] != nullptr)
        status = serversUDP[sock]->endPacket();
    else
        status = 0;

    replyStart(cmd, 1);
    replyParam(&status, 1);
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdUdpParsePacket() {
    uint8_t cmd = data[2];
    
    // Get and test the input parameter
    if (data[3] != 1 || data[4] != 1 || data[6] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    uint8_t sock = data[5];
    if (sock >= MAX_SOCK_NUM)
        return;  // Invalid socket number

    int16_t avail;
    
    if (serversUDP[sock] != nullptr)
        avail = serversUDP[sock]->parsePacket();
    else
        avail = 0;

    #ifdef _DEBUG
        Serial.printf("ParsePacket[%d] = %d\n", sock, avail);
    #endif
    
    replyStart(cmd, 1);
    replyParam(reinterpret_cast<const uint8_t *>(&avail), sizeof(avail));
    replyEnd();
}

