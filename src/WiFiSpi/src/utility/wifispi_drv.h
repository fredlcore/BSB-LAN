/*
  wifispi_drv.h - Library for Arduino SPI connection to ESP8266
  Copyright (c) 2017 Jiri Bilek. All right reserved.

  ---
  
  Based on: wifi_drv.h - Library for Arduino Wifi shield.
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

#ifndef _WIFISPI_DRV_H_INCLUDED
#define _WIFISPI_DRV_H_INCLUDED

#include <inttypes.h>
#include "wifi_spi.h"
#include "IPAddress.h"
#include <SPI.h>

// Key index length
///#define KEY_IDX_LEN     1
// 100 ms secs of delay to test if the connection is established
#define WL_DELAY_START_CONNECTION 100
// Firmware version string length (format a.b.c)
#define WL_FW_VER_LENGTH 6
// Protocol version string length (format a.b.c)
#define WL_PROTOCOL_VER_LENGTH 6

#define DUMMY_DATA  0xFF


class WiFiSpiDrv
{
private:
    // SPI object
    static SPIClass *spi_obj;

	// settings of requested network
	static char 	_networkSsid[WL_SSID_MAX_LENGTH+1];
	static int32_t 	_networkRssi;
	static uint8_t 	_networkEncr;

	// firmware version string in the format a.b.c
	static char 	fwVersion[WL_FW_VER_LENGTH];
	// protocol version string in the format a.b.c
	static char 	protocolVersion[WL_PROTOCOL_VER_LENGTH];

	// settings of current selected network
	static char 	_ssid[WL_SSID_MAX_LENGTH+1];
	static uint8_t 	_bssid[WL_MAC_ADDR_LENGTH];
	static uint8_t 	_mac[WL_MAC_ADDR_LENGTH];
	static uint8_t  _localIp[WL_IPV4_LENGTH];
	static uint8_t  _subnetMask[WL_IPV4_LENGTH];
	static uint8_t  _gatewayIp[WL_IPV4_LENGTH];

	/*
	 * Get network Data information
	 */
    static int8_t getNetworkData(uint8_t *ip, uint8_t *mask, uint8_t *gwip);

    /*
     * Get scanned data information
     */
    static int8_t getScannedData(uint8_t networkItem, char *ssid, int32_t *rssi, uint8_t *encr);

    static uint8_t reqHostByName(const char* aHostname);

    static int getHostByName(IPAddress& aResult);

public:
    // Public constant strings
    static const char ERROR_WAITRESPONSE[] PROGMEM;  // "Error waitResponse"
    static const char ERROR_BADREPLY[] PROGMEM;  // "Error badReply"

    /*
     * Driver initialization, pin is GPIO port number used as SS
     */
    static void wifiDriverInit(uint8_t pin, uint32_t max_speed = 0, SPIClass *in_spi = &SPI);

    /*
     * Set the desired network which the connection manager should try to
     * connect to.
     *
     * The ssid of the desired network should be specified.
     *
     * param ssid: The ssid of the desired network.
     * param ssid_len: Lenght of ssid string.
     * return: WL_SUCCESS or WL_FAILURE
	 */
    static int8_t wifiSetNetwork(const char* ssid, uint8_t ssid_len);

    /* Start Wifi connection with passphrase
     * the most secure supported mode will be automatically selected
     *
     * param ssid: Pointer to the SSID string.
     * param ssid_len: Length of ssid string.
     * param passphrase: Passphrase. Valid characters in a passphrase
     *        must be between ASCII 32-126 (decimal).
     * param len: Length of passphrase string.
     * return: WL_SUCCESS or WL_FAILURE
     */
    static uint8_t wifiSetPassphrase(const char* ssid, const uint8_t ssid_len, const char *passphrase, const uint8_t len);

    /* Start Wifi connection with WEP encryption.
     * Configure a key into the device. The key type (WEP-40, WEP-104)
     * is determined by the size of the key (5 bytes for WEP-40, 13 bytes for WEP-104).
     *
     * param ssid: Pointer to the SSID string.
     * param ssid_len: Lenght of ssid string.
     * param key_idx: The key index to set. Valid values are 0-3.
     * param key: Key input buffer.
     * param len: Lenght of key string.
     * return: WL_SUCCESS or WL_FAILURE
     */
///    static int8_t wifiSetKey(const char* ssid, uint8_t ssid_len, uint8_t key_idx, const void *key, const uint8_t len);

    /* Set ip configuration disabling dhcp client
     *
     * param local_ip: 	Static ip configuration
     * param gateway: 	Static gateway configuration
     * param subnet: 	Static subnet mask configuration
     * param dns_server1: Static DNS server1 configuration
     * param dns_server2: Static DNS server2 configuration
     */
    static bool config(uint32_t local_ip, uint32_t gateway, uint32_t subnet, uint32_t dns_server1, uint32_t dns_server2);

    /* Set DNS ip configuration
     *
     * param validParams: set the number of parameters that we want to change
     * 					 i.e. validParams = 1 means that we'll change only dns_server1
     * 					 	  validParams = 2 means that we'll change dns_server1 and dns_server2
     * param dns_server1: Static DNS server1 configuration
     * param dns_server2: Static DNS server2 configuration
     */
 ///   static void setDNS(uint8_t validParams, uint32_t dns_server1, uint32_t dns_server2);

    /*
     * Disconnect from the network
     *
     * return: WL_SUCCESS or WL_FAILURE
     */
    static uint8_t disconnect();

    /*
     * Disconnect from the network
     *
     * return: one value of wl_status_t enum
     */
    static uint8_t getConnectionStatus();

    /*
     * Get the interface MAC address.
     *
     * return: pointer to uint8_t array with length WL_MAC_ADDR_LENGTH
     */
    static uint8_t* getMacAddress();

    /*
     * Get the interface IP address.
     *
     * return: copy the ip address value in IPAddress object
     */
    static int8_t getIpAddress(IPAddress& ip);

    /*
     * Get the interface subnet mask address.
     *
     * return: copy the subnet mask address value in IPAddress object
     */
    static int8_t getSubnetMask(IPAddress& mask);

    /*
     * Get the gateway ip address.
     *
     * return: copy the gateway ip address value in IPAddress object
     */
    static int8_t getGatewayIP(IPAddress& ip);

    /*
     * Return the current SSID associated with the network
     *
     * return: ssid string
     */
    static char* getCurrentSSID();

    /*
     * Return the current BSSID associated with the network.
     * It is the MAC address of the Access Point
     *
     * return: pointer to uint8_t array with length WL_MAC_ADDR_LENGTH
     */
    static uint8_t* getCurrentBSSID();

    /*
     * Return the current RSSI /Received Signal Strength in dBm)
     * associated with the network
     *
     * return: signed value
     */
    static int32_t getCurrentRSSI();

    /*
     * Return the Encryption Type associated with the network
     *
     * return: one value of wl_enc_type enum
     */
 ///   static uint8_t getCurrentEncryptionType();

    /*
     * Start scan WiFi networks available
     *
     * return: Number of discovered networks
     */
    static int8_t startScanNetworks();

    /*
     * Get the networks available
     *
     * return: Number of discovered networks
     */
    static int8_t getScanNetworks();

    /*
     * Return the SSID discovered during the network scan.
     *
     * param networkItem: specify from which network item want to get the information
	 *
     * return: ssid string of the specified item on the networks scanned list
     */
    static char* getSSIDNetworks(uint8_t networkItem);

    /*
     * Return the RSSI of the networks discovered during the scanNetworks
     *
     * param networkItem: specify from which network item want to get the information
	 *
     * return: signed value of RSSI of the specified item on the networks scanned list
     */
    static int32_t getRSSINetworks(uint8_t networkItem);

    /*
     * Return the encryption type of the networks discovered during the scanNetworks
     *
     * param networkItem: specify from which network item want to get the information
	 *
     * return: encryption type (enum wl_enc_type) of the specified item on the networks scanned list
     */
    static uint8_t getEncTypeNetworks(uint8_t networkItem);

    /*
     * Resolve the given hostname to an IP address.
     * param aHostname: Name to be resolved
     * param aResult: IPAddress structure to store the returned IP address
     * result: 1 if aIPAddrString was successfully converted to an IP address,
     *         0 error, hostname not found
     *        -1 error, command was not performed
     */
    static int8_t getHostByName(const char* aHostname, IPAddress& aResult);

    /*
     * Get the firmware version
     * result: version as string with this format a.b.c
     */
    static const char* getFwVersion();

    /*
     * Get remote Data information on UDP socket
     */
    static bool getRemoteData(uint8_t sock, uint8_t *ip, uint16_t *port);

    /*
     * Perform software reset of the ESP8266 module. 
     * The reset succeedes only if the SPI communication is not broken.
     * After the reset wait for the ESP8266 to came to life again. Typically, the ESP8266 boots within 100 ms,
     * but with the WifiManager installed on ESP it can be a couple of seconds.
     */
    static void softReset(void);

    /*
     * Get the SPI protocol version
     * result: version as string with this format a.b.c
     */
    static const char* getProtocolVersion();

};

extern WiFiSpiDrv wiFiSpiDrv;

#endif
