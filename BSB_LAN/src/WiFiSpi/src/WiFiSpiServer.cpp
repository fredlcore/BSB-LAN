/*
  WiFiSPIServer.cpp - Library for Arduino Wifi SPI connection with ESP8266.
  Copyright (c) 2017 Jiri Bilek. All right reserved.

  ---
  
  Based on WiFiServer.cpp - Library for Arduino Wifi shield.
  Copyright (c) 2011-2014 Arduino LLC.  All right reserved.

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

#include <string.h>
#include "utility/srvspi_drv.h"

extern "C" {
  #include "utility/debug.h"
}

#include "WiFiSpi.h"
#include "WiFiSpiClient.h"
#include "WiFiSpiServer.h"

WiFiSpiServer::WiFiSpiServer(uint16_t port)
{
    _port = port;
}

/*
 * 
 */
void WiFiSpiServer::begin()
{
    uint8_t sock = WiFiSpiClass::getSocket();
    
    if (sock != SOCK_NOT_AVAIL)
    {
        _sock = sock;
        ServerSpiDrv::startServer(_port, _sock);
        WiFiSpiClass::_server_port[_sock] = _port;
        WiFiSpiClass::_state[_sock] = _sock;
    }
}

/*
 * 
 */
WiFiSpiClient WiFiSpiServer::available(uint8_t* status)
{
    WiFiSpiClient client(_sock);

    uint8_t _client_status = client.status();  // creates Client object on ESP side if there is established connection
//    uint8_t _server_status = this->status();  removed, may be related with the comment below, running fine without it 

    if (status != NULL)
        *status = _client_status;

    // TODO: If server is not in listen state, restart it (code present in original WiFiServer.h). I think it is useless.

    if (_client_status == ESTABLISHED)
        return client;

    return WiFiSpiClient(SOCK_NOT_AVAIL);  // closed Client
}

/*
 * 
 */
uint8_t WiFiSpiServer::status() {
    return ServerSpiDrv::getServerState(0);
}

/*
 * 
 */
size_t WiFiSpiServer::write(uint8_t b)
{
    return write(&b, 1);
}

/*
 * 
 */
size_t WiFiSpiServer::write(const uint8_t *buffer, size_t size)
{
    size_t n = 0;
    WiFiSpiClient client(_sock);

    if (client.status() == ESTABLISHED)
        n = client.write(buffer, size);

    return n;
}

/*
 * 
 */
void WiFiSpiServer::stop()
{
    ServerSpiDrv::stopServer(_sock);

    WiFiSpiClass::_server_port[_sock] = 0;
    WiFiSpiClass::_state[_sock] = NA_STATE;
}

