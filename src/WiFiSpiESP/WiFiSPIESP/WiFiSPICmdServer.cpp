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
void WiFiSpiEspCommandProcessor::cmdStartServer() {
    uint8_t cmd = data[2];
    
    // Get and test the parameters (3 input parameters)
    if (data[3] != 3) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }
    uint16_t port;
    uint8_t sock;
    uint8_t protocol;  // TCP / UDP

    uint8_t dataPos = 4;  // Position in the input buffer

    // Read parameters
    if (getParameter(data, dataPos, reinterpret_cast<uint8_t*>(&port), sizeof(port)) < 0)
        return;  // Failure - received invalid parameter
    if (getParameter(data, dataPos, &sock, sizeof(sock)) < 0)
        return;  // Failure - received invalid parameter
    if (getParameter(data, dataPos, &protocol, sizeof(protocol)) < 0)
        return;  // Failure - received invalid parameter
    if (sock >= MAX_SOCK_NUM)
        return;  // Invalid socket number
    
    if (data[dataPos] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    #ifdef _DEBUG
        Serial.printf("WifiServer.startServer, sock=%d, port=%d, protocol=%d\n", sock, port, protocol);
    #endif

    // Close existing server on this socket
    stopServer(sock);

    // Open
    uint8_t status;
    
    if (protocol == TCP_MODE) {
        servers[sock] = new WiFiServer(port);
        servers[sock]->begin();
        status = servers[sock]->status();
        status = (status == LISTEN || status == ESTABLISHED);
    } else {
        serversUDP[sock] = new WiFiUDP();
        status = serversUDP[sock]->begin(port);
    }

    replyStart(cmd, 1);
    replyParam(&status, 1);
    replyEnd();
}

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdGetStateTcp() {
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
    
    if (servers[sock] == nullptr)
        status = CLOSED;
    else
        status = servers[sock]->status();

    replyStart(cmd, 1);
    replyParam(&status, 1);
    replyEnd();
} 

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdStopServer() {
    uint8_t cmd = data[2];
    
    // Get and test the input parameter
    if (data[3] != 1 || data[4] != 1 || data[6] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    uint8_t sock = data[5];
    if (sock >= MAX_SOCK_NUM)
        return;  // Invalid socket number

    stopServer(sock);

    replyStart(cmd, 0);
    replyEnd();
}        

/*
 * 
 */
void WiFiSpiEspCommandProcessor::cmdGetRemoteDataCmd() {
    uint8_t cmd = data[2];
    
    // Get and test the input parameter
    if (data[3] != 1 || data[4] != 1 || data[6] != END_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_BODY));
        return;  // Failure - received invalid message
    }

    uint8_t sock = data[5];
    if (sock >= MAX_SOCK_NUM)
        return;  // Invalid socket number

    uint32_t ipAddr = 0;
    uint16_t port = 0;
    
    if (serversUDP[sock] != nullptr) {
        ipAddr = serversUDP[sock]->remoteIP();  // UDP connection
        port = serversUDP[sock]->remotePort();
    } else if (clients[sock] != nullptr) {
        ipAddr = clients[sock]->remoteIP();  // TCP connection (server or client)
        port = clients[sock]->remotePort();
    }

    #ifdef _DEBUG
        Serial.printf("%d: IP=%lx, port=%d\n", sock, ipAddr, port);
    #endif

    replyStart(cmd, 2);
    replyParam(reinterpret_cast<const uint8_t*>(&ipAddr), sizeof(ipAddr));
    replyParam(reinterpret_cast<const uint8_t*>(&port), sizeof(port));
    replyEnd();
}

