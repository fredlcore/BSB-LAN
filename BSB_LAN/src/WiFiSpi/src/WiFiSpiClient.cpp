/*
  WiFiSpiClient.cpp - Library for Arduino SPI connection to ESP8266
  Copyright (c) 2017 Jiri Bilek. All rights reserved.

  -----
  
  Based on WiFiClient.cpp - Library for Arduino Wifi shield.
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
  #include "utility/wl_definitions.h"
  #include "utility/wl_types.h"
  #include <string.h>
  #include "utility/debug.h"
}

#include "WiFiSpi.h"
#include "WiFiSpiClient.h"
#include "utility/wifi_spi.h"
#include "utility/srvspi_drv.h"
#include "utility/wifispi_drv.h"

WiFiSpiClient::WiFiSpiClient() : _sock(SOCK_NOT_AVAIL) {
}

WiFiSpiClient::WiFiSpiClient(uint8_t sock) : _sock(sock) {
}

/*
 * 
 */
int WiFiSpiClient::connect(const char* host, uint16_t port)
{
	IPAddress remote_addr;
	if (WiFiSpi.hostByName(host, remote_addr))
	{
		return _connect(remote_addr, port, false);
	}
	return 0;
}

/*
 * 
 */
int WiFiSpiClient::connect(IPAddress ip, uint16_t port)
{
    return _connect(ip, port, false);
}

/*
 * 
 */
int WiFiSpiClient::connectSSL(const char* host, uint16_t port)
{
  IPAddress remote_addr;
  if (WiFiSpi.hostByName(host, remote_addr))
  {
    return _connect(remote_addr, port, true);
  }
  return 0;
}

/*
 * 
 */
int WiFiSpiClient::connectSSL(IPAddress ip, uint16_t port)
{
    return _connect(ip, port, true);
}

/*
 * 
 */
int WiFiSpiClient::_connect(IPAddress ip, uint16_t port, bool isSSL)
{
    _sock = WiFiSpiClass::getSocket();
    if (_sock != SOCK_NOT_AVAIL)
    {
        if (! ServerSpiDrv::startClient(uint32_t(ip), port, _sock, (isSSL ? TCP_MODE_WITH_TLS : TCP_MODE)))
            return 0;   // unsuccessfull

        WiFiSpiClass::_state[_sock] = _sock;
    } 
    else 
    {
        Serial.println("No Socket available");
        return 0;
    }
    return 1;
}

/*
 * 
 */
size_t WiFiSpiClient::write(const uint8_t *buf, size_t size)
{
    if (_sock >= MAX_SOCK_NUM || size == 0)
    {
        setWriteError();
        return 0;
    }

    if (!ServerSpiDrv::sendData(_sock, buf, size))
    {
        setWriteError();
        return 0;
    }

    return size;
}

/*
 * 
 */
int WiFiSpiClient::available() 
{
    if (_sock == SOCK_NOT_AVAIL)
        return 0;
    else
        return ServerSpiDrv::availData(_sock);
}

/*
 * 
 */
int WiFiSpiClient::read() 
{
    int16_t b;
    ServerSpiDrv::getData(_sock, &b);  // returns -1 when error
    return b;
}

/*
    Reads data into a buffer.
    Return: 0 = success, size bytes read
           -1 = error (either no data or communication error)
 */
int WiFiSpiClient::read(uint8_t* buf, size_t size) {
    // sizeof(size_t) is architecture dependent
    // but we need a 16 bit data type here
    uint16_t _size = size;
    if (!ServerSpiDrv::getDataBuf(_sock, buf, &_size))
        return -1;
    return 0;
}

/*
 * 
 */
int WiFiSpiClient::peek() 
{
    int16_t b;
    ServerSpiDrv::getData(_sock, &b, 1);  // returns -1 when error
    return b;
}

/*
 * 
 */
void WiFiSpiClient::flush() {
  // TODO: a real check to ensure transmission has been completed
}

/*
 * 
 */
void WiFiSpiClient::stop() {
  if (_sock == SOCK_NOT_AVAIL)
    return;
    
  ServerSpiDrv::stopClient(_sock);

  int count = 0;
  // wait maximum 5 secs for the connection to close
  while (status() != CLOSED && ++count < 500)
    delay(10);

  if (WiFiSpiClass::_server_port[_sock] == 0)
    WiFiSpiClass::_state[_sock] = NA_STATE;  // Close only if it isn't server connection

  _sock = SOCK_NOT_AVAIL;
}

/*
 * 
 */
uint8_t WiFiSpiClient::connected()
{
    if (_sock == SOCK_NOT_AVAIL)
        return 0;
    else    
        return (status() == ESTABLISHED);
}

/*
 * 
 */
uint8_t WiFiSpiClient::status() 
{
    if (_sock == SOCK_NOT_AVAIL)
        return CLOSED;
    else
        return ServerSpiDrv::getClientState(_sock);
}

/*
 * 
 */
WiFiSpiClient::operator bool() {
  return (_sock != SOCK_NOT_AVAIL);
}

/*
 * 
 */
uint8_t WiFiSpiClient::verifySSL(uint8_t* fingerprint, const char *host) {
    if (_sock == SOCK_NOT_AVAIL || host[0] == 0)
        return 0;

    return ServerSpiDrv::verifySSLClient(_sock, fingerprint, host);
}

/*
 * 
 */
IPAddress WiFiSpiClient::remoteIP()
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
uint16_t WiFiSpiClient::remotePort()
{
    uint8_t _remoteIp[4];
    uint16_t _remotePort;

    if (WiFiSpiDrv::getRemoteData(_sock, _remoteIp, &_remotePort))
        return _remotePort;
    else
        return 0;
}
