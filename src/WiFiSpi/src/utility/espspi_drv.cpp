/*
  espspi_drv.cpp - Library for Arduino SPI connection with ESP8266
  
  Copyright (c) 2017 Jiri Bilek. All right reserved.

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

#include "../config.h"
#include "espspi_drv.h"

// Read and check one byte from the input
#if defined(ESPSPI_DEBUG_OPTION_BAD_MESSAGE)
#define READ_AND_CHECK_BYTE(c, err)                         \
            do {                                       \
                uint8_t _b = espSpiProxy.readByte();   \
                if (_b != (c)) {                       \
                    Serial.print(err);                 \
                    Serial.print(" exp:");  Serial.print(c, HEX);    \
                    Serial.print(", got:");  Serial.print(_b, HEX);  \
                    return 0;                          \
                }                                      \
            } while (false)
#else
#define READ_AND_CHECK_BYTE(c, err)                   \
            do {                                     \
                if (espSpiProxy.readByte() != (c))   \
                    return 0;                        \
            } while (false)
#endif

/* 
    Sends a command to ESP. If numParam == 0 ends the command otherwise keeps it open.
    
    Cmd Struct Message
   _______________________________________________________________________
  | START CMD | C/R  | CMD  | N.PARAM | PARAM LEN | PARAM  | .. | END CMD |
  |___________|______|______|_________|___________|________|____|_________|
  |   8 bit   | 1bit | 7bit |  8bit   |   8bit    | nbytes | .. |   8bit  |
  |___________|______|______|_________|___________|________|____|_________|

  The last byte (position 31) is crc8.
*/
void EspSpiDrv::sendCmd(const uint8_t cmd, const uint8_t numParam)
{
    WAIT_FOR_SLAVE_RX_READY();

    // Send Spi START CMD
    espSpiProxy.writeByte(START_CMD);

    // Send Spi C + cmd
    espSpiProxy.writeByte(cmd & ~(REPLY_FLAG));

    // Send Spi numParam
    espSpiProxy.writeByte(numParam);

    // If numParam == 0 send END CMD and flush
    if (numParam == 0)
        endCmd();
}

/*
   Ends a command and flushes the buffer
 */
void EspSpiDrv::endCmd()
{
    espSpiProxy.writeByte(END_CMD);
    espSpiProxy.flush(MESSAGE_FINISHED);
}

/*
    Sends a parameter.
    param ... parameter value
    param_len ... length of the parameter
 */
void EspSpiDrv::sendParam(const uint8_t* param, const uint8_t param_len)
{
    // Send paramLen
    espSpiProxy.writeByte(param_len);

    // Send param data
    for (int i=0; i<param_len; ++i)
        espSpiProxy.writeByte(param[i]);
}

/*
    Sends a 8 bit integer parameter. Sends high byte first.
    param ... parameter value
 */
void EspSpiDrv::sendParam(const uint8_t param)
{
    // Send paramLen
    espSpiProxy.writeByte(1);

    // Send param data
    espSpiProxy.writeByte(param );
}


/*
    Sends a buffer as a parameter.
    Parameter length is 16 bit.
 */
void EspSpiDrv::sendBuffer(const uint8_t* param, uint16_t param_len)
{
    // Send paramLen
    espSpiProxy.writeByte(param_len & 0xff);
    espSpiProxy.writeByte(param_len >> 8);

    // Send param data
    for (uint16_t i=0;  i<param_len;  ++i)
        espSpiProxy.writeByte(param[i]);
}


/*
    Gets a response from the ESP
    cmd ... command id
    numParam ... number of parameters - currently supported 0 or 1
    param  ... pointer to space for the first parameter
    param_len ... max length of the first parameter, returns actual length
 */
uint8_t EspSpiDrv::waitResponseCmd(const uint8_t cmd, uint8_t numParam, uint8_t* param, uint8_t* param_len)
{
    WAIT_FOR_SLAVE_TX_READY();
    READ_AND_CHECK_BYTE(START_CMD, "Start");
    READ_AND_CHECK_BYTE(cmd | REPLY_FLAG, "Cmd");
    READ_AND_CHECK_BYTE(numParam, "Param");

    if (numParam == 1)
    {
        // Reads the length of the first parameter
        uint8_t len = espSpiProxy.readByte();

        // Reads the parameter, checks buffer overrun
        for (uint8_t ii=0; ii<len; ++ii)
        {
            if (ii < *param_len)
                param[ii] = espSpiProxy.readByte();
        }

        // Sets the actual length of the parameter
        if (len < *param_len)
            *param_len = len;
    }
    else if (numParam != 0)
        return 0;  // Bad number of parameters
  
    READ_AND_CHECK_BYTE(END_CMD, "End");

    return 1;
}

/*
    Gets a response from the ESP
    cmd ... command id
    numParam ... number of parameters - currently supported 0 or 1
    param  ... pointer to space for the first parameter
    param_len ... max length of the first parameter (16 bit integer), returns actual length
 */
uint8_t EspSpiDrv::waitResponseCmd16(const uint8_t cmd, uint8_t numParam, uint8_t* param, uint16_t* param_len)
{
    WAIT_FOR_SLAVE_TX_READY();
    READ_AND_CHECK_BYTE(START_CMD, "Start");
    READ_AND_CHECK_BYTE(cmd | REPLY_FLAG, "Cmd");
    READ_AND_CHECK_BYTE(numParam, "Param");

    if (numParam == 1)
    {
        // Reads the length of the first parameter
        uint16_t len = espSpiProxy.readByte() << 8;
        len |= espSpiProxy.readByte();
        // Reads the parameter, checks buffer overrun
        for (uint16_t ii=0; ii<len; ++ii)
        {
            if (ii < *param_len)
                param[ii] = espSpiProxy.readByte();
        }

        // Sets the actual length of the parameter
        if (len < *param_len)
            *param_len = len;
    }
    else if (numParam != 0)
        return 0;  // Bad number of parameters
  
    READ_AND_CHECK_BYTE(END_CMD, "End");

    return 1;
}

/*
    Reads a response from the ESP. Decodes parameters and puts them into a return structure
 */
int8_t EspSpiDrv::waitResponseParams(const uint8_t cmd, uint8_t numParam, tParam* params)
{
    WAIT_FOR_SLAVE_TX_READY();
    READ_AND_CHECK_BYTE(START_CMD, "Start");
    READ_AND_CHECK_BYTE(cmd | REPLY_FLAG, "Cmd");
    READ_AND_CHECK_BYTE(numParam, "Param");

    if (numParam > 0)
    {
        for (uint8_t i=0;  i<numParam;  ++i)
        {
            // Reads the length of the first parameter
            uint8_t len = espSpiProxy.readByte();

            // Reads the parameter, checks buffer overrun
            for (uint8_t ii=0; ii<len; ++ii)
            {
                if (ii < params[i].paramLen)
                    params[i].param[ii] = espSpiProxy.readByte();
            }

            // Sets the actual length of the parameter
            if (len < params[i].paramLen)
                params[i].paramLen = len;
        }
    }
    READ_AND_CHECK_BYTE(END_CMD, "End");

    return 1;
}

