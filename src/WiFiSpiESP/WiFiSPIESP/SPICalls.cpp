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

#include "SPICalls.h"
#include "SPISlave.h"

// Very dangerous, may produce Illegal Instruction traps!!
//#define _DEBUG_SPICALLS

// Global variables
volatile uint8_t SPISlaveState = (SPISLAVE_RX_READY << 4) | SPISLAVE_TX_NODATA;
volatile boolean dataReceived = false;
volatile boolean dataSent = true;
uint8_t* inputBuffer;

// Reply bufer
uint8_t reply[32];
uint8_t replyPos;

// Local prototypes
void writeByte(uint8_t byte);
void flush(uint8_t indicator);
uint8_t crc8(uint8_t *buffer, uint8_t bufLen);

/*
   Event: onStatus
   CALLED FROM INTERRUPT
   
   Status has been received from the master.
   The status register is a special register that both the slave and the master can write to and read from.
   Can be used to exchange small data or status information
*/
void ICACHE_RAM_ATTR SPIOnStatus(uint16_t data) {
    #ifdef _DEBUG_SPICALLS
        Serial.printf("Status: %04x\n", data);
    #endif
}


/*
   Event: onStatusSent
   CALLED FROM INTERRUPT
   
   The master has read the status register
*/
void ICACHE_RAM_ATTR SPIOnStatusSent() {
    #ifdef _DEBUG_SPICALLS
        Serial.println(F("Status Sent"));
    #endif

    // querying status after transmitting data confirms the data
    uint32_t savedPS = noInterrupts();  // cli();
    if ((SPISlaveState & 0x0f) == SPISLAVE_TX_WAITING_FOR_CONFIRM) {
        dataSent = true;
        setTxStatus(SPISLAVE_TX_NODATA);
    }

    xt_wsr_ps(savedPS);  // sei();
}


/*
   Event: onData
   CALLED FROM INTERRUPT

   Data has been received from the master. Beware that len is always 32
   and the buffer is autofilled with zeroes if data is less than 31 bytes long
   The 32nd byte is crc8.

   Cmd Struct Message:
   __________________________________________________________________________________
  | INDICATOR | START CMD | C/R   CMD  | N.PARAM | PARAM LEN | PARAM  | .. | END CMD |
  |___________|___________|____________|_________|___________|________|____|_________|
  |   8 bit   |   8 bit   | 1bit  7bit |  8bit   |   8bit    | nbytes | .. |   8bit  |
  |___________|___________|____________|_________|___________|________|____|_________|
*/
void ICACHE_RAM_ATTR SPIOnData(uint8_t* data, size_t len) {

    // TODO: Fix buffer overwriting when the processing of the buffer is too slow
  
    uint32_t savedPS = noInterrupts();  // cli();

    // Check the CRC
    setRxStatus(SPISLAVE_RX_CRC_PROCESSING);

    if (data[31] == crc8(data, 31)) {
        // CRC ok
        dataReceived = true;
        setRxStatus(SPISLAVE_RX_BUSY);
        inputBuffer = data;
    }
    else {
        // Bad CRC, ignore the message
        setRxStatus(SPISLAVE_RX_ERROR);
    }

    xt_wsr_ps(savedPS);  // sei();
}


/*
   Event: onDataSent
   CALLED FROM INTERRUPT

   The master has read out outgoing data buffer
   that buffer can be set with SPISlave.setData
*/
void ICACHE_RAM_ATTR SPIOnDataSent() {
    uint32_t savedPS = noInterrupts();  // cli();
    
    setTxStatus(SPISLAVE_TX_WAITING_FOR_CONFIRM);

    xt_wsr_ps(savedPS);  // sei();

    #ifdef _DEBUG_SPICALLS
        Serial.println(F("Answer Sent"));
    #endif
}

/*
    Sets receiver status
 */
void ICACHE_RAM_ATTR setRxStatus(uint8_t stateRx) {
//    uint32_t savedPS = noInterrupts();

    SPISlaveState = (SPISlaveState & 0x0f) | (stateRx << 4);
    refreshStatus();        

//    xt_wsr_ps(savedPS);
}

/*
    Sets transmitter status
 */
void ICACHE_RAM_ATTR setTxStatus(uint8_t stateTx) {
//    uint32_t savedPS = noInterrupts();

    SPISlaveState = (SPISlaveState & 0xf0) | stateTx;
    refreshStatus();        
        
//    xt_wsr_ps(savedPS);
}

/*
    Puts status data into the status register
 */
void ICACHE_RAM_ATTR refreshStatus() {
    uint16_t data = SPISlaveState | ((SPISlaveState ^ 0xff) << 8);
    SPISlave.setStatus(data);  // Return indicator of the slave state
}

/*
 * 
 */
void replyStart(const uint8_t cmd, const uint8_t numParams) {
    reply[1] = START_CMD;
    reply[2] = cmd | REPLY_FLAG;
    reply[3] = numParams;  // number of params

    replyPos = 3;

    dataSent = true;  // discard previous message (when master sends a new command it is clear it does not care about a previous one)
}

void replyParam(const uint8_t* param, const uint8_t paramLen) {
    writeByte(paramLen);
    
    for (uint8_t i=0;  i<paramLen;  ++i) {
        writeByte(*param++);
    }
}

void replyParam16(const uint8_t* param, const uint16_t paramLen) {
    writeByte(paramLen >> 8);
    writeByte(paramLen & 0xff);
    
    for (uint16_t i=0;  i<paramLen;  ++i) {
        writeByte(*param++);
    }
}

void replyEnd() {
    writeByte(END_CMD);
    flush(MESSAGE_FINISHED);
}

void writeByte(const uint8_t b) {
    if (replyPos >= 30) {
        // Buffer full - send it now
        flush(MESSAGE_CONTINUES);
    }
        
    reply[++replyPos] = b;
}

void flush(uint8_t indicator) {
    // Is buffer empty?
    if (replyPos == 0)
        return;  

    // Message indicator
    reply[0] = indicator;

    // Pad the data with zeros
    while (replyPos < 30)
        reply[++replyPos] = 0;

    // CRC
    reply[31] = crc8(reply, 31);

    // Debugging printout
    #ifdef _DEBUG_MESSAGES
        // Debugging printout
        Serial.print(F(">> "));
        for (int i=0; i<replyPos+1; ++i) {
            Serial.printf("%2x ", reply[i]);
        }
        Serial.println("");
        Serial.flush();
    #endif

    // Wait until the previous message was sent
    uint32_t thisTime = millis();

    while (!dataSent && (millis() - thisTime < 1000));

    // Send the buffer
    uint32_t savedPS = noInterrupts();  // cli();

    dataSent = false;
    SPISlave.setData(reply);
    setTxStatus(SPISLAVE_TX_READY);

    xt_wsr_ps(savedPS);  // sei();

    replyPos = 0;
}

/*
    Reads a byte from the input buffer, waits for another data chunk if necessary.
    Ensures there is at least one byte left in the data buffer.
    Return the byte read or -1 when error
 */
int16_t readByte(uint8_t* data, uint8_t &dataPos) {
    uint8_t b = data[dataPos++];

    // Check the buffer (only 31 bytes available, 32th byte is the crc8)
    if (dataPos >= 31) {
        if (data[0] != MESSAGE_CONTINUES)
            return -1;  // Error: No more data

        // Read next 32 bytes of the message
        dataReceived = false;
        data[0] = 0;  // invalidate the rx buffer (to be sure it wouldn't be read twice)
        setRxStatus(SPISLAVE_RX_READY);

        uint32_t thisTime = millis();

        while (millis() - thisTime < MSG_RECEIVE_TIMEOUT) {
            if (dataReceived) {
                // Get the data
                uint32_t savedPS = noInterrupts();  // cli();
                dataReceived = false;
                memcpy(data, inputBuffer, 32);
                xt_wsr_ps(savedPS);  // sei();

                // Debug printout
                #ifdef _DEBUG_MESSAGES
                    Serial.print(F("<< "));
                    for (int i=0; i<32; ++i) {
                        Serial.printf("%2x ", data[i]);
                    }
                    Serial.println("");
                #endif

                // Test
                if ((data[0] != MESSAGE_FINISHED && data[0] != MESSAGE_CONTINUES)) {
                    Serial.println(F("Invalid message header - message rejected."));
                    return -1;  // Failure - received invalid message
                }
                dataPos = 1;
                break;
            }
        }

        if (dataPos != 1)
            return -1;  // Timeout
    }

    return (int16_t)b;
}

/*
    Reads a parameter from the input buffer, waits for another data chunk if necessary.
    Ensures there is at least one byte left in the data buffer.
 */
int8_t getParameter(uint8_t* data, uint8_t &dataPos, uint8_t* param, const uint8_t paramLen) {
    int16_t b = readByte(data, dataPos);
    if (b < 0)
        return -1;
    uint8_t len = (b & 0xff);

    for (uint8_t i = 0;  i < len;  ++i)
    {
        // Get next character
        b = readByte(data, dataPos);
        if (b < 0)
            return -1;
        
        if (i < paramLen)  // don't overrun the buffer
            *param++ = b;
    }

    return len;
}

/*
    Reads a 16 bit integer parameter from the input buffer, waits for another data chunk if necessary.
    Ensures there is at least one byte left in the data buffer.
 */
int8_t getParameter(uint8_t* data, uint8_t &dataPos, uint16_t* param) {
    uint16_t p = 0;
    
    int16_t b = readByte(data, dataPos);
    if (b < 0 || (b & 0xff) != 2)
        return -1;

    // Get two bytes
    if ((b = readByte(data, dataPos)) < 0)
        return -1;
    p = b << 8;
    if ((b = readByte(data, dataPos)) < 0)
        return -1;
    *param = p | b;
        
    return 2;
}

/*
    Reads a string parameter from the input buffer, waits for another data chunk if necessary.
    Ensures there is at least one byte left in the data buffer.
 */
int8_t getParameterString(uint8_t* data, uint8_t &dataPos, char* param, const uint8_t paramLen) {
    uint8_t len;
    
    len = getParameter(data, dataPos, reinterpret_cast<uint8_t*>(param), paramLen);
    if (len < 0)
        return -1;
    param[len] = 0;

    return len;
}

/*
 * Compute crc8 with polynom 0x107 (x^8 + x^2 + x + 1)
 * Lookup table idea: https://lentz.com.au/blog/tag/crc-table-generator
 *
 * INVESTIGATION: Doesn't the crc computing take too long to be processed in interrupt handler?
 */
uint8_t ICACHE_RAM_ATTR crc8(uint8_t *buffer, uint8_t bufLen)
{
    const static uint8_t POLY = 0x07;

    static const uint8_t PROGMEM tableLow[] = { 0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15, 
                                                0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D };
    static const uint8_t PROGMEM tableHigh[] = { 0x00, 0x70, 0xE0, 0x90, 0xC7, 0xB7, 0x27, 0x57,
                                                 0x89, 0xF9, 0x69, 0x19, 0x4E, 0x3E, 0xAE, 0xDE };

    uint8_t crcValue = 0x00;

    for (int i = 0; i < bufLen; ++i) {
        crcValue ^= buffer[i];
        crcValue = pgm_read_byte(tableLow + (crcValue & 0x0f)) ^ 
                   pgm_read_byte(tableHigh +((crcValue >> 4) & 0x0f));
    }

    return crcValue;
}