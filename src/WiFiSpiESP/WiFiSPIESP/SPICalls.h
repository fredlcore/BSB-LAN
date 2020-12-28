/*
    Callback functions called by SPI events

  Copyright (c) 2017 Jiri Bilek. All rights reserved.

  Based on SPISlave example application for ESP8266.
  Copyright (c) 2015 Hristo Gochkov. All rights reserved.

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

#ifndef _SPICALLS_H_INCLUDED
#define _SPICALLS_H_INCLUDED

#include "Arduino.h"

// Prints out debugging information
//#define _DEBUG
// Prints out received and transmitted messages. Severely slows down the communication!
//#define _DEBUG_MESSAGES

// Globals
extern volatile boolean dataReceived;
extern uint8_t* inputBuffer;

// Prototypes
void setRxStatus(uint8_t state);
void setTxStatus(uint8_t state);
void refreshStatus();

void replyStart(const uint8_t cmd, const uint8_t numParams);
void replyParam(const uint8_t* param, const uint8_t paramLen);
void replyParam16(const uint8_t* param, const uint16_t paramLen);
void replyEnd();

int16_t readByte(uint8_t* data, uint8_t &dataPos);
int8_t getParameter(uint8_t* data, uint8_t &dataPos, uint8_t* param, const uint8_t paramLen);
int8_t getParameter(uint8_t* data, uint8_t &dataPos, uint16_t* param);
int8_t getParameterString(uint8_t* data, uint8_t &dataPos, char* param, const uint8_t paramLen);


#define REPLY_FLAG      1<<7

// Max waiting time for next chunk of a message
#define MSG_RECEIVE_TIMEOUT  1000

// SPI Events
void SPIOnData(uint8_t* data, size_t len);
void SPIOnDataSent();
void SPIOnStatus(uint16_t data);
void SPIOnStatusSent();

// SPI Status
enum {
    SPISLAVE_RX_BUSY,
    SPISLAVE_RX_READY,
    SPISLAVE_RX_CRC_PROCESSING,
    SPISLAVE_RX_ERROR
};
enum {
    SPISLAVE_TX_NODATA,
    SPISLAVE_TX_READY,
    SPISLAVE_TX_PREPARING_DATA,
    SPISLAVE_TX_WAITING_FOR_CONFIRM
};

// Command start and end flags
#define START_CMD   0xE0
#define END_CMD     0xEE

// Message indicators
#define MESSAGE_FINISHED     0xDF
#define MESSAGE_CONTINUES    0xDC

#endif

