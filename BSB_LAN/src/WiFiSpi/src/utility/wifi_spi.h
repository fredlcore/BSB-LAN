/*
  wifi_spi.h - Library for Arduino Wifi SPI connection with ESP8266.
  Copyright (c) 2017 Jiri Bilek. All right reserved.

  ---
  
  Based on wifi_spi.h - Library for Arduino Wifi shield.
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

#ifndef _WIFI_SPI_H_INCLUDED
#define _WIFI_SPI_H_INCLUDED

#include <inttypes.h>
#include "wl_definitions.h"

#define REPLY_FLAG      1<<7

#define START_CMD   0xE0
#define END_CMD     0xEE
//#define ERR_CMD   	0xEF
  
enum {
	SET_NET_CMD 		= 0x10,
	SET_PASSPHRASE_CMD	= 0x11,
	SET_KEY_CMD	        = 0x12,
//	TEST_CMD	        = 0x13,
	SET_IP_CONFIG_CMD	= 0x14,
//	SET_DNS_CONFIG_CMD	= 0x15,

	GET_CONN_STATUS_CMD	     = 0x20,
	GET_IPADDR_CMD		     = 0x21,
	GET_MACADDR_CMD		     = 0x22,
	GET_CURR_SSID_CMD	     = 0x23,
	GET_CURR_BSSID_CMD	     = 0x24,
	GET_CURR_RSSI_CMD	     = 0x25,
	GET_CURR_ENCT_CMD	     = 0x26,
	SCAN_NETWORKS		     = 0x27,
	START_SERVER_TCP_CMD     = 0x28,
	GET_STATE_TCP_CMD        = 0x29,
	DATA_SENT_TCP_CMD	     = 0x2A,
    AVAIL_DATA_TCP_CMD	     = 0x2B,
    GET_DATA_TCP_CMD	     = 0x2C,
    START_CLIENT_TCP_CMD     = 0x2D,
    STOP_CLIENT_TCP_CMD      = 0x2E,
    GET_CLIENT_STATE_TCP_CMD = 0x2F,
    DISCONNECT_CMD		     = 0x30,
	GET_IDX_SSID_CMD	     = 0x31,
	GET_IDX_RSSI_CMD	     = 0x32,
	GET_IDX_ENCT_CMD	     = 0x33,
	REQ_HOST_BY_NAME_CMD     = 0x34,
	GET_HOST_BY_NAME_CMD     = 0x35,
	START_SCAN_NETWORKS	     = 0x36,
	GET_FW_VERSION_CMD	     = 0x37,
	GET_TEST_CMD		     = 0x38,
	SEND_DATA_UDP_CMD	     = 0x39,
	GET_REMOTE_DATA_CMD      = 0x3A,

    // Not present in original protocol, added for ESP8266
    STOP_SERVER_TCP_CMD      = 0x3B,
    GET_SCANNED_DATA_CMD     = 0x3C,
    BEGIN_UDP_PACKET_CMD     = 0x3D,
    UDP_PARSE_PACKET_CMD     = 0x3E,
    SOFTWARE_RESET_CMD       = 0x3F,

    GET_PROTOCOL_VERSION_CMD = 0x50,
    VERIFY_SSL_CLIENT_CMD    = 0x51,
    START_SERVER_MULTICAST_CMD = 0x52,

    // All command with DATA_FLAG 0x40 send a 16bit Len

	SEND_DATA_TCP_CMD		 = 0x44,
    GET_DATABUF_TCP_CMD		 = 0x45,
    INSERT_DATABUF_CMD		 = 0x46,
};


enum wl_tcp_state {
  CLOSED      = 0,
  ESTABLISHED = 4
};

/*enum wl_tcp_state {
  CLOSED      = 0,
  LISTEN      = 1,
  SYN_SENT    = 2,
  SYN_RCVD    = 3,
  ESTABLISHED = 4,
  FIN_WAIT_1  = 5,
  FIN_WAIT_2  = 6,
  CLOSE_WAIT  = 7,
  CLOSING     = 8,
  LAST_ACK    = 9,
  TIME_WAIT   = 10
};*/


enum numParams{
    PARAM_NUMS_0,
    PARAM_NUMS_1,
    PARAM_NUMS_2,
    PARAM_NUMS_3,
    PARAM_NUMS_4,
    PARAM_NUMS_5,
    MAX_PARAM_NUMS
};

#define MAX_PARAMS MAX_PARAM_NUMS-1
#define PARAM_LEN_SIZE 1

typedef struct  __attribute__((__packed__))
{
	uint8_t     paramLen;
	char*	    param;
} tParam;

#endif
