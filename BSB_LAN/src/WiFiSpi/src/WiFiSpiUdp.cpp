/*
  WiFiSPIUdp.cpp - Library for Arduino Wifi SPI connection with ESP8266.
  Copyright (c) 2017 Jiri Bilek. All right reserved.

  ---
  
  Based on WiFiUdp.cpp - Library for Arduino Wifi shield.
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

extern "C" {
  #include "utility/debug.h"
  #include "utility/wifi_spi.h"
}
#include <string.h>
#include "utility/srvspi_drv.h"
#include "utility/wifispi_drv.h"

#include "WiFiSpi.h"
#include "WiFiSpiUdp.h"


/* Constructor */
WiFiSpiUdp::WiFiSpiUdp() : _sock(SOCK_NOT_AVAIL) {}

/*
 * Starts WiFiSpiUdp socket, listening at local port PORT 
 */
uint8_t WiFiSpiUdp::begin(uint16_t port) 
{
    uint8_t sock = WiFiSpiClass::getSocket();
    if (sock != SOCK_NOT_AVAIL)
    {
        if (ServerSpiDrv::startServer(port, sock, UDP_MODE))
        {
            WiFiSpiClass::_server_port[sock] = port;
            WiFiSpiClass::_state[sock] = sock;
            _sock = sock;
            _port = port;
            return 1;
        }
    }
    return 0;
}

/*
 * Starts WiFiSpiUdp socket, listening at port PORT for multicast messages from IP
 * Returns 1 if successful, 0 on failure
 */
uint8_t WiFiSpiUdp::beginMulticast(IPAddress ip, uint16_t port)
{
    uint8_t sock = WiFiSpiClass::getSocket();
    if (sock != SOCK_NOT_AVAIL)
    {
        if (ServerSpiDrv::startServerMulticast(uint32_t(ip), port, sock))
        {
            WiFiSpiClass::_server_port[sock] = port;
            WiFiSpiClass::_state[sock] = sock;
            _sock = sock;
            _port = port;
            return 1;
        }
    }
    return 0;
}

/* 
 *  Returns number of bytes available in the current packet
 */
int WiFiSpiUdp::available() 
{
    if (_sock != SOCK_NOT_AVAIL)
        return ServerSpiDrv::availData(_sock);
    
    return 0;
}

/*
 * Releases any resources being used by this WiFiSpiUdp instance 
 */
void WiFiSpiUdp::stop()
{
    ServerSpiDrv::stopServer(_sock);

    WiFiSpiClass::_server_port[_sock] = 0;
    WiFiSpiClass::_state[_sock] = NA_STATE;
}

/*
 * 
 */
int WiFiSpiUdp::beginPacket(const char *host, uint16_t port)
{
	// Look up the host first
	IPAddress remote_addr;
	if (WiFiSpi.hostByName(host, remote_addr))
		return beginPacket(remote_addr, port);
	else
	    return 0;
}

/*
 * 
 */
int WiFiSpiUdp::beginPacket(IPAddress ip, uint16_t port)
{
    if (_sock == SOCK_NOT_AVAIL)
        return 0;  // No socket available

    if (! ServerSpiDrv::beginUdpPacket(uint32_t(ip), port, _sock))
        return 0;  // Client not opened
    else
        return 1;
}

/*
 * 
 */
int WiFiSpiUdp::endPacket()
{
	return ServerSpiDrv::sendUdpData(_sock);
}

/*
 * 
 */
size_t WiFiSpiUdp::write(uint8_t byte)
{
    return write(&byte, 1);
}

/*
 * 
 */
size_t WiFiSpiUdp::write(const uint8_t *buffer, size_t size)
{
    if (ServerSpiDrv::insertDataBuf(_sock, buffer, size))
	    return size;
    else
        return 0;
}

/*
 * 
 */
int WiFiSpiUdp::parsePacket()
{
    return ServerSpiDrv::parsePacket(_sock);
}

/*
 * 
 */
int WiFiSpiUdp::read()
{
    int16_t b;
    ServerSpiDrv::getData(_sock, &b);  // returns -1 when error
    return b;
}

/*
 * 
 */
int WiFiSpiUdp::read(unsigned char* buffer, size_t len)
{
    // sizeof(size_t) is architecture dependent
    // but we need a 16 bit data type here
    uint16_t _size = len;
    
    if (!ServerSpiDrv::getDataBuf(_sock, buffer, &_size))
        return -1;
    else
        return 0;
}

/*
 * 
 */
int WiFiSpiUdp::peek()
{
    int16_t b;
    ServerSpiDrv::getData(_sock, &b, 1);  // returns -1 when error
    return b;
}

/*
 * 
 */
void WiFiSpiUdp::flush()
{
  // TODO: a real check to ensure transmission has been completed
}

/*
 * 
 */
IPAddress WiFiSpiUdp::remoteIP()
{
    uint8_t _remoteIp[4];
    uint16_t _remotePort;

    if (WiFiSpiDrv::getRemoteData(_sock, _remoteIp, &_remotePort))
        return IPAddress(_remoteIp);
    else
        return IPAddress(0UL);
}

/*
 * 
 */
uint16_t WiFiSpiUdp::remotePort()
{
    uint8_t _remoteIp[4];
    uint16_t _remotePort;

    if (WiFiSpiDrv::getRemoteData(_sock, _remoteIp, &_remotePort))
        return _remotePort;
    else
        return 0;
}

