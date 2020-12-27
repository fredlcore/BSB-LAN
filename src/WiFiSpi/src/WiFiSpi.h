/*
  WiFiSPI.h - Library for Arduino SPI connection to ESP8266
  Copyright (c) 2017 Jiri Bilek. All rights reserved.

 Circuit:
   1. On ESP8266 must be running (flashed) WiFiSPIESP application.
    
   2. Connect the Arduino to the following pins on the esp8266:

            ESP8266         |
    GPIO    NodeMCU   Name  |   Uno
   ===================================
     15       D8       SS   |   D10
     13       D7      MOSI  |   D11
     12       D6      MISO  |   D12
     14       D5      SCK   |   D13

    Note: If the ESP is booting at a moment when the SPI Master (i.e. Arduino) has the Select line HIGH (deselected)
    the ESP8266 WILL FAIL to boot!

  -----
  
  Based on WiFi.h - Library for Arduino Wifi shield.
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

#ifndef _WIFISPI_H_INCLUDED
#define _WIFISPI_H_INCLUDED

#include <inttypes.h>
#include <SPI.h>

extern "C" {
	#include "utility/wl_definitions.h"
	#include "utility/wl_types.h"
}

#include "utility/wifi_spi.h"
#include "IPAddress.h"

#include "WiFiSpiClient.h"
#include "WiFiSpiServer.h"
#include "WiFiSpiUdp.h"


class WiFiSpiClass
{
public:
    /*
     * Initialization of the library.
     *
     * param pin: SS pin, default value get default pin
     * param max_speed: maximum speed of SPI interface
     * param in_spi: pointer to SPI Class
     * param hwResetPin: number of the PIN connected to ESP's RESET or -1
     */
    static void init(int8_t pin = -1, uint32_t max_speed = 0, SPIClass *in_spi = &SPI, int8_t hwResetPin = -1);

private:
    static int16_t 	_state[MAX_SOCK_NUM];
    static uint16_t _server_port[MAX_SOCK_NUM];

    static int8_t hwResetPin;

    static const char *protocolVer;

public:
    WiFiSpiClass();

    /*
     * Get the first socket available
     */
    static uint8_t getSocket();

    /*
     * Get firmware version
     */
    static const char* firmwareVersion();


    /* Start Wifi connection for OPEN networks
     *
     * param ssid: Pointer to the SSID string.
     */
    uint8_t begin(const char* ssid);

    /* Start Wifi connection with WEP encryption.
     * Configure a key into the device. The key type (WEP-40, WEP-104)
     * is determined by the size of the key (5 bytes for WEP-40, 13 bytes for WEP-104).
     *
     * param ssid: Pointer to the SSID string.
     * param key_idx: The key index to set. Valid values are 0-3.
     * param key: Key input buffer.
     */
///    uint8_t begin(const char* ssid, uint8_t key_idx, const char* key);

    /* Start Wifi connection with passphrase
     * the most secure supported mode will be automatically selected
     *
     * param ssid: Pointer to the SSID string.
     * param passphrase: Passphrase. Valid characters in a passphrase
     *        must be between ASCII 32-126 (decimal).
     */
    uint8_t begin(const char* ssid, const char *passphrase);

    /* Change Ip configuration settings disabling the dhcp client
     *
     * param local_ip: 	Static ip configuration
     */
    bool config(IPAddress local_ip);

    /* Change Ip configuration settings disabling the dhcp client
     *
     * param local_ip: 	Static ip configuration
     * param dns_server:     IP configuration for DNS server 1
     */
    bool config(IPAddress local_ip, IPAddress dns_server);

    /* Change Ip configuration settings disabling the dhcp client
     *
     * param local_ip: 	Static ip configuration
	 * param dns_server:     IP configuration for DNS server 1
     * param gateway : 	Static gateway configuration
     */
    bool config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway);

    /* Change Ip configuration settings disabling the dhcp client
     *
     * param local_ip: 	Static ip configuration
	 * param dns_server:     IP configuration for DNS server 1
     * param gateway: 	Static gateway configuration
     * param subnet:		Static Subnet mask
     */
    bool config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet);

    /* Change DNS Ip configuration
     *
     * param dns_server1: ip configuration for DNS server 1
     */
    bool setDNS(IPAddress dns_server1);

    /* Change DNS Ip configuration
     *
     * param dns_server1: ip configuration for DNS server 1
     * param dns_server2: ip configuration for DNS server 2
     *
     */
    bool setDNS(IPAddress dns_server1, IPAddress dns_server2);

    /*
     * Disconnect from the network
     *
     * return: one value of wl_status_t enum
     */
    int disconnect(void);

    /*
     * Get the interface MAC address.
     *
     * return: pointer to uint8_t array with length WL_MAC_ADDR_LENGTH
     */
    uint8_t* macAddress(uint8_t* mac);

    /*
     * Get the interface IP address.
     *
     * return: Ip address value
     */
    IPAddress localIP();

    /*
     * Get the interface subnet mask address.
     *
     * return: subnet mask address value
     */
    IPAddress subnetMask();

    /*
     * Get the gateway ip address.
     *
     * return: gateway ip address value
     */
   IPAddress gatewayIP();

    /*
     * Return the current SSID associated with the network
     *
     * return: ssid string
     */
    char* SSID();

    /*
     * Return the current BSSID associated with the network.
     * It is the MAC address of the Access Point
     *
     * return: pointer to uint8_t array with length WL_MAC_ADDR_LENGTH
     */
    uint8_t* BSSID();

    /*
     * Return the current RSSI /Received Signal Strength in dBm)
     * associated with the network
     *
     * return: signed value
     */
    int32_t RSSI();

    /*
     * Return the Encryption Type associated with the network
     *
     * return: one value of wl_enc_type enum
     */
    ///uint8_t	encryptionType();

    /*
     * Start scan WiFi networks available
     *
     * return: Number of discovered networks
     */
    int8_t scanNetworks();

    /*
     * Return the SSID discovered during the network scan.
     *
     * param networkItem: specify from which network item want to get the information
	 *
     * return: ssid string of the specified item on the networks scanned list
     */
    char* SSID(uint8_t networkItem);

    /*
     * Return the encryption type of the networks discovered during the scanNetworks
     *
     * param networkItem: specify from which network item want to get the information
	 *
     * return: encryption type (enum wl_enc_type) of the specified item on the networks scanned list
     */
    uint8_t	encryptionType(uint8_t networkItem);

    /*
     * Return the RSSI of the networks discovered during the scanNetworks
     *
     * param networkItem: specify from which network item want to get the information
	 *
     * return: signed value of RSSI of the specified item on the networks scanned list
     */
    int32_t RSSI(uint8_t networkItem);

    /*
     * Return Connection status.
     *
     * return: one of the value defined in wl_status_t
     */
    uint8_t status();

    /*
     * Resolve the given hostname to an IP address.
     * param aHostname: Name to be resolved
     * param aResult: IPAddress structure to store the returned IP address
     * result: 1 if aIPAddrString was successfully converted to an IP address,
     *          else error code
     */
    int8_t hostByName(const char* aHostname, IPAddress& aResult);

    /*
     * Perform software reset of the ESP8266 module. 
     * The reset succeedes only if the SPI communication is not broken.
     * After the reset wait for the ESP8266 to came to life again. Typically, the ESP8266 boots within 100 ms,
     * but with the WifiManager installed on ESP it can be a couple of seconds.
     */
    static void softReset(void);
    
    /*
     * Perform hardware reset of the ESP8266 module. The PIN connected to ESP's reset must be declared in init() 
     * After the reset wait for the ESP8266 to came to life again. Typically, the ESP8266 boots within 100 ms,
     * but with the WifiManager installed on ESP it can be a couple of seconds.
     * This function waits for 200 ms.
     */
    static void hardReset(void);
    
    /*
     * Get slave protocol version
     */
    static const char* protocolVersion();

    /*
     * Get master protocol version
     */
    static const char* masterProtocolVersion();

    /*
     * Check protocol version
     * result: 1 if protocol version of both master and slave match
     *         0 otherwise
     */
    static uint8_t checkProtocolVersion();

    /*
     * The following classes need r/w access to private arrays
     */
    friend class WiFiSpiClient;
    friend class WiFiSpiServer;
    friend class WiFiSpiUdp;
};

extern WiFiSpiClass WiFiSpi;

#endif
