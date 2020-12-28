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


// Static private class members

uint8_t *WiFiSpiEspCommandProcessor::data;
const char WiFiSpiEspCommandProcessor::INVALID_MESSAGE_HEADER[] PROGMEM = "Invalid message header - message rejected.";
const char WiFiSpiEspCommandProcessor::INVALID_MESSAGE_BODY[] PROGMEM = "Invalid message body - message rejected.";

// no assumption about MAX_SOCK_NUM value
WiFiClient *WiFiSpiEspCommandProcessor::clients[MAX_SOCK_NUM];
WiFiServer *WiFiSpiEspCommandProcessor::servers[MAX_SOCK_NUM];
WiFiUDP *WiFiSpiEspCommandProcessor::serversUDP[MAX_SOCK_NUM];
int8_t WiFiSpiEspCommandProcessor::clientsProto[MAX_SOCK_NUM];


/*
    Processes the input buffer for a command.
 */
void WiFiSpiEspCommandProcessor::processCommand(uint8_t *dataIn) {
    
    // Save the pointer to the input buffer
    data = dataIn;

    #ifdef _DEBUG_MESSAGES
        // Debug printout
        Serial.print(F("<< "));
        for (int i=0; i<32; ++i) {
            Serial.printf("%2x ", data[i]);
        }
        Serial.println("");
    #endif

    // Decode the buffer
    if ((data[0] != MESSAGE_FINISHED && data[0] != MESSAGE_CONTINUES) || data[1] != START_CMD) {
        Serial.println(FPSTR(INVALID_MESSAGE_HEADER));

    #ifdef _DEBUG
        for (uint8_t i=0; i<32; ++i)
            Serial.printf("%02x ", data[i]);
        Serial.println(); 
    #endif

        return;  // Failure - received invalid message
   }

    // Decode the command
    uint8_t cmd = data[2];

    switch (cmd) {
        // ----- GENERAL COMMANDS

        case GET_FW_VERSION_CMD:
            cmdGetFwVersion();  break;

        case GET_MACADDR_CMD:
            cmdGetMacAddr();  break;
    
        case SET_IP_CONFIG_CMD:
            cmdSetIpConfig();  break;

        case START_SCAN_NETWORKS:
            cmdStartScanNetworks();  break;

        case SCAN_NETWORKS:
            cmdScanNetworks();  break;

        case GET_SCANNED_DATA_CMD:
            cmdGetScannedData();  break;

        case SOFTWARE_RESET_CMD:
            cmdSoftwareReset();  break;
    
        case GET_PROTOCOL_VERSION_CMD:
            cmdGetProtocolVersion();  break;

        // ----- CONNECTION COMMANDS

        case GET_CONN_STATUS_CMD:
            cmdGetConnStatus();  break;
    
        case SET_PASSPHRASE_CMD:
            cmdSetPassphrase();  break;

        case SET_NET_CMD:
            cmdSetNet();  break;

        case DISCONNECT_CMD:
            cmdDisconnect();  break;
        
        case GET_IPADDR_CMD:
            cmdGetIpAddr();  break; 

        case GET_CURR_SSID_CMD:
            cmdGetCurrSsid();  break;

        case GET_CURR_RSSI_CMD:
            cmdGetCurrRssi();  break;   

        case GET_CURR_BSSID_CMD:
            cmdGetCurrBssid();  break;

        case GET_HOST_BY_NAME_CMD:
            cmdGetHostByName();  break;


        // ----- CLIENT COMMANDS
    
        case START_CLIENT_TCP_CMD:
            cmdStartClientTcp();  break;

        case GET_CLIENT_STATE_TCP_CMD:
            cmdGetClientStateTcp();  break;

        case AVAIL_DATA_TCP_CMD:
            cmdAvailDataTcp();  break;

        case SEND_DATA_TCP_CMD:
            cmdSendDataTcp();  break;

        case GET_DATA_TCP_CMD:
            cmdGetDataTcp();  break;

        case GET_DATABUF_TCP_CMD:
            cmdGetDatabufTcp();  break;

        case STOP_CLIENT_TCP_CMD:
            cmdStopClientTcp();  break;

        case VERIFY_SSL_CLIENT_CMD:
            cmdVerifySSLClient();  break;
            
        // ----- SERVER COMMANDS
    
        case START_SERVER_TCP_CMD:
            cmdStartServer();  break;  // TCP or UDP
    
        case GET_STATE_TCP_CMD:
            cmdGetStateTcp();  break;
       
        case STOP_SERVER_TCP_CMD:
            cmdStopServer();  break;
    
        case GET_REMOTE_DATA_CMD:
            cmdGetRemoteDataCmd();  break;


        // ----- UDP COMMANDS
    
        case BEGIN_UDP_PACKET_CMD:
            cmdBeginUdpPacket();  break;
    
        case INSERT_DATABUF_CMD:
            cmdInsertDatabuf();  break;
    
        case SEND_DATA_UDP_CMD:
            cmdSendDataUdp();  break;

        case UDP_PARSE_PACKET_CMD:
            cmdUdpParsePacket();  break;
            
        default:
            Serial.printf("Unknown command: %2x\n", cmd);
    }
}

/*
    Stops servers and client for the socket sock.
    Frees server from memory and nulls server pointer.
 */
void WiFiSpiEspCommandProcessor::stopServer(uint8_t sock) {
    if (servers[sock] != nullptr) {
        if (clients[sock] != nullptr) {
            clients[sock]->stop();

            delete clients[sock];
            clients[sock] = nullptr;
        }
        servers[sock]->stop();
        
        delete servers[sock];
        servers[sock] = nullptr;
    }
    else if (serversUDP[sock] != nullptr) {
        serversUDP[sock]->stop();
        
        delete serversUDP[sock];
        serversUDP[sock] = nullptr;
    }
}

/*
 * 
 */
uint8_t WiFiSpiEspCommandProcessor::disconnect() {
    // Stops all servers (TCP and/or UDP)
    for (uint8_t sock = 0; sock < MAX_SOCK_NUM; ++sock)
        stopServer(sock);
    
    // Stops all clients
    WiFiClient::stopAll();

    // Disconnect
    uint8_t status;
    if (WiFi.disconnect(false))  // disconnect and do NOT turn station mode off
    {
        delay(100);  // FIXME: We need some time to stabilize the internal state machine. It would be better to poll the state.
        status = WL_DISCONNECTED;
    }
    else
        status = WL_CONNECT_FAILED;  // TODO: better return code in case of an error

    #ifdef _DEBUG
        Serial.printf("Disconnect status=%d\n", status);
    #endif

    return status;
}

/*
    Initializes needed structures
 */
void WiFiSpiEspCommandProcessor::init() {
    // Server array initialization
    for (uint8_t sock=0;  sock<MAX_SOCK_NUM; ++sock) {
        clients[sock] = nullptr;
        clientsProto[sock] = -1;
        servers[sock] = nullptr;
        serversUDP[sock] = nullptr;
    }
}

