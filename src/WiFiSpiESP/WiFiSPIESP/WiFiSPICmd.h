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

#ifndef _WIFISPICMD_H_INCLUDED
#define _WIFISPICMD_H_INCLUDED

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include "WiFiUdp.h"


class WiFiSpiEspCommandProcessor {
    
    private:
        static uint8_t *data;  // Pointer to processed message
        
        
        // Private constant strings
        static const char INVALID_MESSAGE_HEADER[] PROGMEM;  // "Invalid message header - message rejected."
        static const char INVALID_MESSAGE_BODY[] PROGMEM;    // "Invalid message body - message rejected."

        static WiFiClient *clients[MAX_SOCK_NUM];
        static int8_t clientsProto[MAX_SOCK_NUM];  // Clients protocols (value of enum tProtMode)
        static WiFiServer *servers[MAX_SOCK_NUM];
        static WiFiUDP *serversUDP[MAX_SOCK_NUM];


    public:
        static void init();
        static void processCommand(uint8_t *dataIn);

    private:
        static uint8_t disconnect();
        static void stopServer(uint8_t sock);
        
        // WiFiSPICmdGeneral.cpp
        static void cmdGetFwVersion();
        static void cmdGetMacAddr();
        static void cmdSetIpConfig();
        static void cmdStartScanNetworks();
        static void cmdScanNetworks();
        static void cmdGetScannedData();
        static void cmdSoftwareReset();
        static void cmdGetProtocolVersion();

        // WiFiSPICmdConnection.cpp
        static void cmdGetConnStatus();
        static void cmdSetPassphrase();
        static void cmdSetNet();
        static void cmdDisconnect();
        static void cmdGetIpAddr();
        static void cmdGetCurrSsid();
        static void cmdGetCurrRssi();
        static void cmdGetCurrBssid();
        static void cmdGetHostByName();

        // WiFiSPICmdClient.cpp
        static void cmdStartClientTcp();
        static void cmdGetClientStateTcp();
        static void cmdAvailDataTcp();
        static void cmdSendDataTcp();
        static void cmdGetDataTcp();
        static void cmdGetDatabufTcp();
        static void cmdStopClientTcp();
        static void cmdVerifySSLClient();

        // WiFiSPICmdServer.cpp
        static void cmdStartServer();
        static void cmdGetStateTcp();
        static void cmdStopServer();
        static void cmdGetRemoteDataCmd();

        // WiFiSPICmdUdp.cpp
        static void cmdBeginUdpPacket();
        static void cmdInsertDatabuf();
        static void cmdSendDataUdp();
        static void cmdUdpParsePacket();
};

// SPI Commands
enum {
  SET_NET_CMD         = 0x10,
  SET_PASSPHRASE_CMD  = 0x11,
  SET_KEY_CMD         = 0x12,
  TEST_CMD            = 0x13,
  SET_IP_CONFIG_CMD   = 0x14,
  SET_DNS_CONFIG_CMD  = 0x15,

  GET_CONN_STATUS_CMD      = 0x20,
  GET_IPADDR_CMD           = 0x21,
  GET_MACADDR_CMD          = 0x22,
  GET_CURR_SSID_CMD        = 0x23,
  GET_CURR_BSSID_CMD       = 0x24,
  GET_CURR_RSSI_CMD        = 0x25,
  GET_CURR_ENCT_CMD        = 0x26,
  SCAN_NETWORKS            = 0x27,
  START_SERVER_TCP_CMD     = 0x28,
  GET_STATE_TCP_CMD        = 0x29,
  DATA_SENT_TCP_CMD        = 0x2A,
  AVAIL_DATA_TCP_CMD       = 0x2B,
  GET_DATA_TCP_CMD         = 0x2C,
  START_CLIENT_TCP_CMD     = 0x2D,
  STOP_CLIENT_TCP_CMD      = 0x2E,
  GET_CLIENT_STATE_TCP_CMD = 0x2F,
  DISCONNECT_CMD           = 0x30,
  GET_IDX_SSID_CMD         = 0x31,
  GET_IDX_RSSI_CMD         = 0x32,
  GET_IDX_ENCT_CMD         = 0x33,
  REQ_HOST_BY_NAME_CMD     = 0x34,
  GET_HOST_BY_NAME_CMD     = 0x35,
  START_SCAN_NETWORKS      = 0x36,
  GET_FW_VERSION_CMD       = 0x37,
  GET_TEST_CMD             = 0x38,
  SEND_DATA_UDP_CMD        = 0x39,
  GET_REMOTE_DATA_CMD      = 0x3A,

  // Not present in original protocol, added for ESP8266
  STOP_SERVER_TCP_CMD      = 0x3B,
  GET_SCANNED_DATA_CMD     = 0x3C,
  BEGIN_UDP_PACKET_CMD     = 0x3D,
  UDP_PARSE_PACKET_CMD     = 0x3E,
  SOFTWARE_RESET_CMD       = 0x3F,

  GET_PROTOCOL_VERSION_CMD = 0x50,
  VERIFY_SSL_CLIENT_CMD    = 0x51,

  // All commands with DATA_FLAG 0x40 send a 16bit Len

  SEND_DATA_TCP_CMD        = 0x44,
  GET_DATABUF_TCP_CMD      = 0x45,
  INSERT_DATABUF_CMD       = 0x46,
};


// Constants

// Maximum open connections
#define MAX_SOCK_NUM    4
// Size of a MAC-address or BSSID
#define WL_MAC_ADDR_LENGTH 6
// Maximum size of a SSID
#define WL_SSID_MAX_LENGTH 32
// Length of passphrase. Valid lengths are 8-63.
#define WL_WPA_KEY_MAX_LENGTH 63

// Max length of hostname
#define WL_HOSTNAME_MAX_LENGTH  255


// Supported protocols
typedef enum eProtMode {
    TCP_MODE, 
    UDP_MODE,
    TCP_MODE_WITH_TLS }
tProtMode;

#endif
