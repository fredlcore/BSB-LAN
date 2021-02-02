/*
  srvspi_drv.cpp - Library for Arduino Wifi SPI connection with ESP8266.
  Copyright (c) 2017 Jiri Bilek. All right reserved.

  ---
  
  Based on server_drv.cpp - Library for Arduino Wifi shield.
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

#include "srvspi_drv.h"

#include "Arduino.h"
#include "espspi_drv.h"

extern "C" {
#include "wl_types.h"
#include "debug.h"
}

#define FPSTR(pstr_pointer) (reinterpret_cast<const __FlashStringHelper *>(pstr_pointer))

/*
    Start server TCP / UDP on port specified
*/
bool ServerSpiDrv::startServer(uint16_t port, uint8_t sock, uint8_t protMode)
{
    // Send Command
    EspSpiDrv::sendCmd(START_SERVER_TCP_CMD, PARAM_NUMS_3);
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(&port), sizeof(port));
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::sendParam(protMode);
    EspSpiDrv::endCmd();

    uint8_t _data = 0;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(START_SERVER_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
        _data = 0;
    }
    
    return (_data == 1);  // return value 1 means ok
}

/*
    Start server UDP Multicast on port specified listening given ip address
*/
bool ServerSpiDrv::startServerMulticast(const uint32_t ipAddress, const uint16_t port, const uint8_t sock)
{
    // Send Command
    EspSpiDrv::sendCmd(START_SERVER_MULTICAST_CMD, PARAM_NUMS_3);
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(&ipAddress), sizeof(ipAddress));
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(&port), sizeof(port));
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::endCmd();

    uint8_t _data = 0;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(START_SERVER_MULTICAST_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
        _data = 0;
    }
    
    return (_data == 1);  // return value 1 means ok
}

/*
 * 
 */
void ServerSpiDrv::stopServer(uint8_t sock)
{
    // Send Command
    EspSpiDrv::sendCmd(STOP_SERVER_TCP_CMD, PARAM_NUMS_1);
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::endCmd();

    if (!EspSpiDrv::waitResponseCmd(STOP_SERVER_TCP_CMD, PARAM_NUMS_0, NULL, NULL))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
    }
}

/*
    Start client TCP on port specified
    Note: protMode is ignored
*/
bool ServerSpiDrv::startClient(uint32_t ipAddress, uint16_t port, uint8_t sock, uint8_t protMode)
{
    // Send Command
    EspSpiDrv::sendCmd(START_CLIENT_TCP_CMD, PARAM_NUMS_4);
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(&ipAddress), sizeof(ipAddress));
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(&port), sizeof(port));
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::sendParam(protMode);
    EspSpiDrv::endCmd();

    // Wait for reply

    // Extended waiting time for status SPISLAVE_TX_PREPARING_DATA
    for (int i=1;  i<10;  ++i)
    {
        if (espSpiProxy.waitForSlaveTxReady() != SPISLAVE_TX_PREPARING_DATA) 
            break;  // The state is either SPISLAVE_TX_READY or SPISLAVE_TX_NODATA with timeout
        WARN(F("Status: Preparing data"));
    }
    
    uint8_t _data = 0;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(START_CLIENT_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
        _data = 0;
    }

    return (_data == 1);  // return value 1 means ok
}

/*
 * 
 */
void ServerSpiDrv::stopClient(uint8_t sock)
{
    // Send Command
    EspSpiDrv::sendCmd(STOP_CLIENT_TCP_CMD, PARAM_NUMS_1);
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::endCmd();

    uint8_t _data = 0;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(STOP_CLIENT_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
    }
}

/*
 * 
 */
uint8_t ServerSpiDrv::getServerState(uint8_t sock)
{
    // Send Command
    EspSpiDrv::sendCmd(GET_STATE_TCP_CMD, PARAM_NUMS_1);
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::endCmd();

    uint8_t _data = 0;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(GET_STATE_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
        _data = CLOSED;
    }

    return (_data ? ESTABLISHED : CLOSED);
}

/*
 * 
 */
uint8_t ServerSpiDrv::getClientState(const uint8_t sock)
{
    // Send Command
    EspSpiDrv::sendCmd(GET_CLIENT_STATE_TCP_CMD, PARAM_NUMS_1);
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::endCmd();

    // Wait for reply
    uint8_t _data = -1;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(GET_CLIENT_STATE_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
        _data = 0;
    }

    return (_data ? ESTABLISHED : CLOSED);
}

/*
 * 
 */
uint16_t ServerSpiDrv::availData(const uint8_t sock)
{
    // Send Command
    EspSpiDrv::sendCmd(AVAIL_DATA_TCP_CMD, PARAM_NUMS_1);
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::endCmd();

    // Wait for reply
    uint16_t _data16;
    uint8_t _dataLen = sizeof(_data16);
    if (!EspSpiDrv::waitResponseCmd(AVAIL_DATA_TCP_CMD, PARAM_NUMS_1, reinterpret_cast<uint8_t *>(&_data16), &_dataLen))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
        _data16 = 0;
    }

    return _data16;
}

/*
 * 
 */
bool ServerSpiDrv::getData(const uint8_t sock, int16_t *data, const uint8_t peek)
{
    // Send Command
    EspSpiDrv::sendCmd(GET_DATA_TCP_CMD, PARAM_NUMS_2);
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::sendParam(peek);
    EspSpiDrv::endCmd();

    // Wait for reply
    int16_t _data16 = -1;  // -1 is error indicator
    uint8_t _dataLen = sizeof(_data16);
    if (!EspSpiDrv::waitResponseCmd(GET_DATA_TCP_CMD, PARAM_NUMS_1, reinterpret_cast<uint8_t *>(&_data16), &_dataLen))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
        _dataLen = 0;
    }
    else
        *data = _data16;
    
    return (_dataLen == sizeof(_data16));
}

/*
    Reads data into a buffer. There must be enough data for the whole buffer or the return code is false (error).
    It is not very clever but it is how the original WiFi library works.
 */
bool ServerSpiDrv::getDataBuf(const uint8_t sock, uint8_t *_data, uint16_t *_dataLen)
{
    // Send Command
    EspSpiDrv::sendCmd(GET_DATABUF_TCP_CMD, PARAM_NUMS_2);
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(_dataLen), sizeof(*_dataLen));
    EspSpiDrv::endCmd();

    // Wait for reply (length is 16 bit integer)
    uint16_t _dataLenRead = *_dataLen;
    if (!EspSpiDrv::waitResponseCmd16(GET_DATABUF_TCP_CMD, PARAM_NUMS_1, _data, &_dataLenRead))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
        _dataLenRead = 0;
    }

    if (_dataLenRead != *_dataLen)
        return false;

    return true;
}

/*
    Works for UDP connection only
 */
bool ServerSpiDrv::insertDataBuf(uint8_t sock, const uint8_t *data, uint16_t _len)
{
    // Send Command
    EspSpiDrv::sendCmd(INSERT_DATABUF_CMD, PARAM_NUMS_2);
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::sendBuffer(data, _len);
    EspSpiDrv::endCmd();

    // Wait for reply
    uint16_t _data16;
    uint8_t _dataLen = sizeof(_data16);
    if (!EspSpiDrv::waitResponseCmd(INSERT_DATABUF_CMD, PARAM_NUMS_1, reinterpret_cast<uint8_t *>(&_data16), &_dataLen))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
        _data16 = 0;
    }
    return (_dataLen == sizeof(_data16) && _data16 == _len);
}

/*
 * 
 */
bool ServerSpiDrv::sendUdpData(uint8_t sock)
{
    // Send Command
    EspSpiDrv::sendCmd(SEND_DATA_UDP_CMD, PARAM_NUMS_1);
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::endCmd();

    // Wait for reply
    uint8_t _data = 0;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(SEND_DATA_UDP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
        _data = 0;
    }

    return (_data == 1);
}

/*
 * 
 */
bool ServerSpiDrv::sendData(const uint8_t sock, const uint8_t *data, const uint16_t len)
{
    // Send Command
    EspSpiDrv::sendCmd(SEND_DATA_TCP_CMD, PARAM_NUMS_2);
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::sendBuffer(data, len);
    EspSpiDrv::endCmd();

    // Wait for reply
    uint16_t _data16;
    uint8_t _dataLen = sizeof(_data16);
    if (!EspSpiDrv::waitResponseCmd(SEND_DATA_TCP_CMD, PARAM_NUMS_1, reinterpret_cast<uint8_t *>(&_data16), &_dataLen))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
        _data16 = 0;
    }
    return (_dataLen == sizeof(_data16) && _data16 == len);
}

/*
    Opens UDP communication on defined IP address and port
 */
bool ServerSpiDrv::beginUdpPacket(uint32_t ipAddress, uint16_t port, uint8_t sock)
{
    // Send Command
    EspSpiDrv::sendCmd(BEGIN_UDP_PACKET_CMD, PARAM_NUMS_3);
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(&ipAddress), sizeof(ipAddress));
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(&port), sizeof(port));
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::endCmd();

    // Wait for reply

    // Extended waiting time for status SPISLAVE_TX_PREPARING_DATA
    for (int i=1;  i<10;  ++i)
    {
        if (espSpiProxy.waitForSlaveTxReady() != SPISLAVE_TX_PREPARING_DATA) 
            break;  // The state is either SPISLAVE_TX_READY or SPISLAVE_TX_NODATA with timeout
        WARN(F("Status: Preparing data")); ///
    }
    
    uint8_t _data = 0;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(BEGIN_UDP_PACKET_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
        _data = 0;
    }

    return (_data == 1);  // return value 1 means ok
}

/*
 * 
 */
uint16_t ServerSpiDrv::parsePacket(const uint8_t sock)
{
    // Send Command
    EspSpiDrv::sendCmd(UDP_PARSE_PACKET_CMD, PARAM_NUMS_1);
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::endCmd();

    // Wait for reply
    uint16_t _data16;
    uint8_t _dataLen = sizeof(_data16);
    if (!EspSpiDrv::waitResponseCmd(UDP_PARSE_PACKET_CMD, PARAM_NUMS_1, reinterpret_cast<uint8_t *>(&_data16), &_dataLen))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
        _data16 = 0;
    }

    return _data16;
}

/*
 * Sends verifySSL command
 * fingerprint - SHA1 of server certificate - must be 20 bytes (not character string!)
 * host - host name
 */
uint8_t ServerSpiDrv::verifySSLClient(const uint8_t sock, uint8_t *fingerprint, const char *host) 
{
    // Send Command
    EspSpiDrv::sendCmd(VERIFY_SSL_CLIENT_CMD, PARAM_NUMS_3);
    EspSpiDrv::sendParam(fingerprint, 20);
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t *>(host), strlen(host));
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::endCmd();

    // Wait for reply

    uint8_t _data = 0;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(VERIFY_SSL_CLIENT_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN(FPSTR(WiFiSpiDrv::ERROR_WAITRESPONSE));
        _data = 0;
    }

    return _data;  // return value 1 means ok
}
