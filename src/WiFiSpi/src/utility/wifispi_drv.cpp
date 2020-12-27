/*
  wifispi_drv.cpp - Library for Arduino SPI connection to ESP8266
  Copyright (c) 2017 Jiri Bilek. All right reserved.

  ---
  
  Based on wifi_drv.cpp - Library for Arduino Wifi shield.
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

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "Arduino.h"

#include "espspi_proxy.h"
#include "espspi_drv.h"
#include "wifispi_drv.h"

extern "C" {
#include "wl_types.h"
#include "debug.h"
}

#define FPSTR(pstr_pointer) (reinterpret_cast<const __FlashStringHelper *>(pstr_pointer))

SPIClass *WiFiSpiDrv::spi_obj;

// Array of data to cache the information related to the networks discovered
char 	WiFiSpiDrv::_networkSsid[] = {0};
int32_t WiFiSpiDrv::_networkRssi = 0;
uint8_t WiFiSpiDrv::_networkEncr = 0;

// Cached values of retrieved data
char 	WiFiSpiDrv::_ssid[] = {0};
uint8_t	WiFiSpiDrv::_bssid[] = {0};
uint8_t WiFiSpiDrv::_mac[] = {0};
uint8_t WiFiSpiDrv::_localIp[] = {0};
uint8_t WiFiSpiDrv::_subnetMask[] = {0};
uint8_t WiFiSpiDrv::_gatewayIp[] = {0};

// Firmware and protocol version
char    WiFiSpiDrv::fwVersion[] = {0};
char    WiFiSpiDrv::protocolVersion[] = {0};

// Static private class members
const char WiFiSpiDrv::ERROR_WAITRESPONSE[] PROGMEM = "Error waitResponse";
const char WiFiSpiDrv::ERROR_BADREPLY[] PROGMEM = "Error badReply";

// Private Methods

/*
 * 
 */
int8_t WiFiSpiDrv::getNetworkData(uint8_t *ip, uint8_t *mask, uint8_t *gwip)
{
    tParam params[PARAM_NUMS_3] = { {WL_IPV4_LENGTH, (char*)ip}, {WL_IPV4_LENGTH, (char*)mask}, {WL_IPV4_LENGTH, (char*)gwip}};

    // Send Command
    EspSpiDrv::sendCmd(GET_IPADDR_CMD, PARAM_NUMS_0);

    if (!EspSpiDrv::waitResponseParams(GET_IPADDR_CMD, PARAM_NUMS_3, params))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
        return WL_FAILURE;
    }

    return WL_SUCCESS;
}

/*
 * 
 */
int8_t WiFiSpiDrv::getScannedData(uint8_t networkItem, char *ssid, int32_t *rssi, uint8_t *encr)
{
    tParam params[PARAM_NUMS_3] = { {WL_SSID_MAX_LENGTH, (char*)ssid}, {sizeof(*rssi), (char*)rssi}, {sizeof(*encr), (char*)encr}};

    // Send Command
    EspSpiDrv::sendCmd(GET_SCANNED_DATA_CMD, PARAM_NUMS_1);
    EspSpiDrv::sendParam(networkItem);
    EspSpiDrv::endCmd();

    ssid[0] = 0;  // Default is empty SSID
    
    if (!EspSpiDrv::waitResponseParams(GET_SCANNED_DATA_CMD, PARAM_NUMS_3, params))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
        return WL_FAILURE;
    }

    ssid[params[0].paramLen] = 0;  // end of string

    return WL_SUCCESS;    
}

/*
 * 
 */
bool WiFiSpiDrv::getRemoteData(uint8_t sock, uint8_t *ip, uint16_t *port)
{
    tParam params[PARAM_NUMS_2] = { {4, (char*)ip}, {sizeof(*port), (char*)port} };
    
    // Send Command
    EspSpiDrv::sendCmd(GET_REMOTE_DATA_CMD, PARAM_NUMS_1);
    EspSpiDrv::sendParam(sock);
    EspSpiDrv::endCmd();

    if (!EspSpiDrv::waitResponseParams(GET_REMOTE_DATA_CMD, PARAM_NUMS_2, params))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
        return false;
    }

    return true;    
}


// Public Methods

/*
 * 
 */
void WiFiSpiDrv::wifiDriverInit(uint8_t pin, uint32_t max_speed, SPIClass *in_spi)
{
    spi_obj = in_spi;
    spi_obj->begin();

    if (max_speed != 0)
        spi_obj->beginTransaction(SPISettings(max_speed, MSBFIRST, SPI_MODE0));
    
    espSpiProxy.begin(pin, spi_obj);
}

/*
 * 
 */
int8_t WiFiSpiDrv::wifiSetNetwork(const char* ssid, uint8_t ssid_len)
{
    // Test the input
    if (ssid_len > WL_SSID_MAX_LENGTH)
        return WL_FAILURE;
         
    // Send Command
    EspSpiDrv::sendCmd(SET_NET_CMD, PARAM_NUMS_1);
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(ssid), ssid_len);
    EspSpiDrv::endCmd();

    // Wait for reply
    uint8_t _data = -1;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(SET_NET_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
        _data = WL_FAILURE;
    }

    return _data;
}

/*
 * Connects to AP with given parameters
 * Returns: status - see getConnectionStatus()
 */
uint8_t WiFiSpiDrv::wifiSetPassphrase(const char* ssid, const uint8_t ssid_len, const char *passphrase, const uint8_t len)
{
    // Test the input
    if (ssid_len > WL_SSID_MAX_LENGTH || len > WL_WPA_KEY_MAX_LENGTH)
        return WL_FAILURE;
         
    // Send Command
    EspSpiDrv::sendCmd(SET_PASSPHRASE_CMD, PARAM_NUMS_2);
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(ssid), ssid_len);
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(passphrase), len);
    EspSpiDrv::endCmd();

    // Wait for reply
    uint8_t _data = -1;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(SET_PASSPHRASE_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
        _data = WL_FAILURE;
    }

    return _data;
}

/*
 * 
 */
bool WiFiSpiDrv::config(uint32_t local_ip, uint32_t gateway, uint32_t subnet, uint32_t dns_server1, uint32_t dns_server2)
{
    // Send Command
    EspSpiDrv::sendCmd(SET_IP_CONFIG_CMD, PARAM_NUMS_5);
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(&local_ip), sizeof(local_ip));
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(&gateway), sizeof(gateway));
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(&subnet), sizeof(subnet));
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(&dns_server1), sizeof(dns_server1));
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(&dns_server2), sizeof(dns_server2));
    EspSpiDrv::endCmd();

    // Wait for reply
    uint8_t _data = false;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(SET_IP_CONFIG_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
        _data = false;
    }

    return _data;
}

/*
 * 
 */                     
uint8_t WiFiSpiDrv::disconnect()
{
    // Send Command
    EspSpiDrv::sendCmd(DISCONNECT_CMD, PARAM_NUMS_0);

    // Wait for reply
    uint8_t _data = -1;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(DISCONNECT_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
        _data = WL_FAILURE;
    }

    return _data;
}

/*
 * 
 */
uint8_t WiFiSpiDrv::getConnectionStatus()
{
    // Send Command
    EspSpiDrv::sendCmd(GET_CONN_STATUS_CMD, PARAM_NUMS_0);

    // Wait for reply
    uint8_t _data = -1;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(GET_CONN_STATUS_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
    }

    return _data;
}

/*
 * 
 */
uint8_t* WiFiSpiDrv::getMacAddress()
{
    // Send Command
    EspSpiDrv::sendCmd(GET_MACADDR_CMD, PARAM_NUMS_0);
    
    // Wait for reply
    uint8_t _dataLen = WL_MAC_ADDR_LENGTH;
    if (!EspSpiDrv::waitResponseCmd(GET_MACADDR_CMD, PARAM_NUMS_1, _mac, &_dataLen))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
    }
    
    if (_dataLen != WL_MAC_ADDR_LENGTH)
    {
        WARN(FPSTR(ERROR_BADREPLY));
    }

    return _mac;
}

/*
 * 
 */
int8_t WiFiSpiDrv::getIpAddress(IPAddress& ip)
{
	int8_t status = getNetworkData(_localIp, _subnetMask, _gatewayIp);
	if (status == WL_SUCCESS)
    	ip = _localIp;

    return status;
}

/*
 * 
 */
int8_t WiFiSpiDrv::getSubnetMask(IPAddress& mask)
{
    int8_t status = getNetworkData(_localIp, _subnetMask, _gatewayIp);
    if (status == WL_SUCCESS)
        mask = _subnetMask;

    return status;
}

/*
 * 
 */
int8_t WiFiSpiDrv::getGatewayIP(IPAddress& ip)
{
    int8_t status = getNetworkData(_localIp, _subnetMask, _gatewayIp);
    if (status == WL_SUCCESS)
        ip = _gatewayIp;

     return status;
}

/*
 * 
 */
char* WiFiSpiDrv::getCurrentSSID()
{
    // Send Command
    EspSpiDrv::sendCmd(GET_CURR_SSID_CMD, PARAM_NUMS_0);
    
    // Wait for reply
    uint8_t _dataLen = WL_SSID_MAX_LENGTH;
    if (!EspSpiDrv::waitResponseCmd(GET_CURR_SSID_CMD, PARAM_NUMS_1, reinterpret_cast<uint8_t*>(_ssid), &_dataLen))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
    }
    
    _ssid[_dataLen] = 0;  // terminate the string

    return _ssid;
}

/*
 * 
 */
uint8_t* WiFiSpiDrv::getCurrentBSSID()
{
    // Send Command
    EspSpiDrv::sendCmd(GET_CURR_BSSID_CMD, PARAM_NUMS_0);

    // Wait for reply
    uint8_t _dataLen = WL_MAC_ADDR_LENGTH;
    if (!EspSpiDrv::waitResponseCmd(GET_CURR_BSSID_CMD, PARAM_NUMS_1, _bssid, &_dataLen))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
    }
    
    if (_dataLen != WL_MAC_ADDR_LENGTH)
    {
        WARN(FPSTR(ERROR_BADREPLY));
    }

    return _bssid;
}

/*
 * 
 */
int32_t WiFiSpiDrv::getCurrentRSSI()
{
    // Send Command
    EspSpiDrv::sendCmd(GET_CURR_RSSI_CMD, PARAM_NUMS_0);
    
    // Wait for reply
    int32_t _rssi;
    uint8_t _dataLen = sizeof(_rssi);
    if (!EspSpiDrv::waitResponseCmd(GET_CURR_RSSI_CMD, PARAM_NUMS_1, reinterpret_cast<uint8_t *>(&_rssi), &_dataLen))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
        _dataLen = 0;
    }

    if (_dataLen != sizeof(_rssi))
    {
        WARN(FPSTR(ERROR_BADREPLY));
    }

    return _rssi;
}

/*
 * 
 */
int8_t WiFiSpiDrv::startScanNetworks()
{
    // Send Command
    EspSpiDrv::sendCmd(START_SCAN_NETWORKS, PARAM_NUMS_0);
    
    int8_t _data = -1;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(START_SCAN_NETWORKS, PARAM_NUMS_1, reinterpret_cast<uint8_t *>(&_data), &_dataLen))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
    }

    return _data;
}

/*
 * 
 */
int8_t WiFiSpiDrv::getScanNetworks()
{
    // Send Command
    EspSpiDrv::sendCmd(SCAN_NETWORKS, PARAM_NUMS_0);
    
    int8_t _data = -1;
    uint8_t _dataLen = sizeof(_data);
    if (!EspSpiDrv::waitResponseCmd(SCAN_NETWORKS, PARAM_NUMS_1, reinterpret_cast<uint8_t *>(&_data), &_dataLen))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
    }

    return _data;
}

/*
 * 
 */
char* WiFiSpiDrv::getSSIDNetworks(uint8_t networkItem)
{
    int8_t status = getScannedData(networkItem, _networkSsid, &_networkRssi, &_networkEncr);
    if (status != WL_SUCCESS)
        _networkSsid[0] = 0;  // Empty string

    return _networkSsid;
}

/*
 * 
 */
uint8_t WiFiSpiDrv::getEncTypeNetworks(uint8_t networkItem)
{
    int8_t status = getScannedData(networkItem, _networkSsid, &_networkRssi, &_networkEncr);
    if (status != WL_SUCCESS)
        return 0;

    return _networkEncr;
}

/*
 * 
 */
int32_t WiFiSpiDrv::getRSSINetworks(uint8_t networkItem)
{
    int8_t status = getScannedData(networkItem, _networkSsid, &_networkRssi, &_networkEncr);
    if (status != WL_SUCCESS)
        return 0;

    return _networkRssi;
}

/*
 * 
 */
int8_t WiFiSpiDrv::getHostByName(const char* aHostname, IPAddress& aResult)
{
    // Send Command
    EspSpiDrv::sendCmd(GET_HOST_BY_NAME_CMD, PARAM_NUMS_1);
    EspSpiDrv::sendParam(reinterpret_cast<const uint8_t*>(aHostname), strlen(aHostname));
    EspSpiDrv::endCmd();

    // Wait for reply
    uint8_t _ipAddr[WL_IPV4_LENGTH];
    uint8_t _status;

    tParam params[PARAM_NUMS_2] = { {sizeof(_status), (char*)&_status}, {sizeof(_ipAddr), (char*)_ipAddr}};

    // Extended waiting time for status SPISLAVE_PREPARING_DATA
    for (int i=1;  i<10;  ++i)
    {
        if (espSpiProxy.waitForSlaveTxReady() != SPISLAVE_TX_PREPARING_DATA) 
            break;  // The state is either SPISLAVE_TX_READY or SPISLAVE_TX_NODATA with timeout
        WARN(F("Status: Preparing data"));
    }
      
    if (!EspSpiDrv::waitResponseParams(GET_HOST_BY_NAME_CMD, PARAM_NUMS_2, params))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
        return WL_FAILURE;
    }
    
    if (params[0].paramLen != sizeof(_status) || params[1].paramLen != sizeof(_ipAddr))
    {
        WARN(FPSTR(ERROR_BADREPLY));
        return 0;
    }

    aResult = _ipAddr;
    
    return _status;
}

/*
 * 
 */
const char* WiFiSpiDrv::getFwVersion()
{
    // Send Command
    EspSpiDrv::sendCmd(GET_FW_VERSION_CMD, PARAM_NUMS_0);

    // Wait for reply
    uint8_t _dataLen = WL_FW_VER_LENGTH;
    if (!EspSpiDrv::waitResponseCmd(GET_FW_VERSION_CMD, PARAM_NUMS_1, (uint8_t*)fwVersion, &_dataLen))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
    }

    return fwVersion;
}

/*
 * Perform remote software reset of the ESP8266 module. 
 * The reset succeedes only if the SPI communication is not broken.
 * The function does not wait for the ESP8266.
 */
void WiFiSpiDrv::softReset(void) {
    // Send Command
    EspSpiDrv::sendCmd(SOFTWARE_RESET_CMD, PARAM_NUMS_0);

    // Wait for reply
    uint8_t _dataLen = WL_FW_VER_LENGTH;
    if (!EspSpiDrv::waitResponseCmd(SOFTWARE_RESET_CMD, PARAM_NUMS_0, NULL, NULL))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
    }
}

/*
 * 
 */
const char* WiFiSpiDrv::getProtocolVersion()
{
    // Send Command
    EspSpiDrv::sendCmd(GET_PROTOCOL_VERSION_CMD, PARAM_NUMS_0);

    // Wait for reply
    uint8_t _dataLen = WL_PROTOCOL_VER_LENGTH;
    if (!EspSpiDrv::waitResponseCmd(GET_PROTOCOL_VERSION_CMD, PARAM_NUMS_1, (uint8_t*)protocolVersion, &_dataLen))
    {
        WARN(FPSTR(ERROR_WAITRESPONSE));
    }

    return protocolVersion;
}


WiFiSpiDrv wiFiSPIDrv;

