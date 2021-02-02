/*
  srvspi_drv.h - Library for Arduino Wifi SPI connection with ESP8266.
  Copyright (c) 2017 Jiri Bilek. All right reserved.

  ---
  
  Based on server_drv.h - Library for Arduino Wifi shield.
  Copyright (c) 2011-2014 Arduino.  All right reserved.

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

#ifndef _SRVSPI_DRV_H_INCLUDED
#define _SRVSPI_DRV_H_INCLUDED

#include <inttypes.h>
#include "wifi_spi.h"

typedef enum eProtMode {
    TCP_MODE, 
    UDP_MODE, 
    TCP_MODE_WITH_TLS }
tProtMode;

class ServerSpiDrv
{
public:

    // Start server TCP / UDP on port specified
    static bool startServer(const uint16_t port, const uint8_t sock, const uint8_t protMode=TCP_MODE);

    // Start server UDP Multicast on port specified listening given ip address
    static bool startServerMulticast(const uint32_t ipAddress, const uint16_t port, const uint8_t sock);

    static void stopServer(const uint8_t sock);

    static bool startClient(const uint32_t ipAddress, const uint16_t port, const uint8_t sock, const uint8_t protMode=TCP_MODE);

    static void stopClient(const uint8_t sock);
                                                                                  
    static uint8_t getServerState(const uint8_t sock);

    static uint8_t getClientState(const uint8_t sock);

    static bool getData(const uint8_t sock, int16_t *data, uint8_t peek = 0);

    static bool getDataBuf(const uint8_t sock, uint8_t *data, uint16_t *len);

    static bool sendData(const uint8_t sock, const uint8_t *data, const uint16_t len);

    static bool sendUdpData(const uint8_t sock);

    static bool insertDataBuf(const uint8_t sock, const uint8_t *_data, const uint16_t _dataLen);

    static uint16_t availData(const uint8_t sock);

  ///  static uint8_t checkDataSent(uint8_t sock);

    static bool beginUdpPacket(uint32_t ip, uint16_t port, uint8_t sock);

    static uint16_t parsePacket(const uint8_t sock);

    static uint8_t verifySSLClient(const uint8_t sock, uint8_t *fingerprint, const char *host);
};

#endif
