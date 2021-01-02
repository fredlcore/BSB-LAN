/*
  espspi_proxy.h - Library for Arduino SPI connection with ESP8266
  
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

  -------------

    WiFi SPI Safe Master for connecting with ESP8266
    On ESP8266 must be flashed WiFiSPIESP application
    Connect the SPI Master device to the following pins on the esp8266:

            ESP8266         |
    GPIO    NodeMCU   Name  |   Uno
   ===================================
     15       D8       SS   |   D10**
     13       D7      MOSI  |   D11
     12       D6      MISO  |   D12
     14       D5      SCK   |   D13

    **) User changeable

    Based on Hristo Gochkov's SPISlave library.
*/

#ifndef _ESPSPI_PROXY_H_INCLUDED
#define _ESPSPI_PROXY_H_INCLUDED

#include "../config.h"
#include <SPI.h>
#include "debug.h"

// The command codes are fixed by ESP8266 hardware
#define CMD_WRITESTATUS  0x01
#define CMD_WRITEDATA    0x02
#define CMD_READDATA     0x03
#define CMD_READSTATUS   0x04

// Message indicators
#define MESSAGE_FINISHED     0xDF
#define MESSAGE_CONTINUES    0xDC

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

// How long we will wait for slave to be ready
#define SLAVE_RX_READY_TIMEOUT     3000UL
#define SLAVE_TX_READY_TIMEOUT     3000UL

// How long will be SS held high when starting transmission
//#define SS_PULSE_DELAY_MICROSECONDS   50


class EspSpiProxy
{
private:
    SPIClass *spi_obj;

    uint8_t _ss_pin;
    uint8_t buffer[32];
    uint8_t buflen;
    uint8_t bufpos;
    
    void _pulseSS(boolean start)
    {
        if (_ss_pin >= 0)
        {

#if defined(ESP8266_SAFE_RESET_IMPLEMENTED)
            if (start) {
                digitalWrite(_ss_pin, LOW);
                delayMicroseconds(20);  // 10us is low (some errors), 15 is ok, 25 us is safe for speeds > 4MHz
            }
            else {
                digitalWrite(_ss_pin, HIGH);
            }
#else
            if (start) {  // tested ok: 5, 15 / 5
                digitalWrite(_ss_pin, HIGH);
                delayMicroseconds(5);
                
                digitalWrite(_ss_pin, LOW);
                delayMicroseconds(20);  // 10us is low (some errors), 15 is ok, 25 us is safe for speeds > 4MHz
            }
            else {
                digitalWrite(_ss_pin, HIGH);
                delayMicroseconds(5);
                digitalWrite(_ss_pin, LOW);
            }
#endif

        }
    }
    
public:
    EspSpiProxy()
    {
       _ss_pin = -1;
       buflen = 0;
    }

    void begin(uint8_t pin, SPIClass *in_spi)
    {
        spi_obj = in_spi;

        _ss_pin = pin;
        pinMode(_ss_pin, OUTPUT);
#if defined(ESP8266_SAFE_RESET_IMPLEMENTED)
        digitalWrite(_ss_pin, HIGH);
#else
        digitalWrite(_ss_pin, LOW);  // Safe value for ESP8266 GPIO15 
#endif
    }

    uint16_t readStatus()
    {
        _pulseSS(true);

        spi_obj->transfer(CMD_READSTATUS);
        uint16_t status = (spi_obj->transfer(0) | ((uint16_t)(spi_obj->transfer(0)) << 8));
        
        _pulseSS(false);

        return status;
    }

    void writeStatus(uint8_t status)
    {
        _pulseSS(true);

        spi_obj->transfer(CMD_WRITESTATUS);
        spi_obj->transfer(status);
        spi_obj->transfer(status ^ 0xff);  // byte inverted value as a check

        _pulseSS(false);
    }

    void readData(uint8_t* buf)
    {
        _pulseSS(true);

        spi_obj->transfer(CMD_READDATA);
        spi_obj->transfer(0x00);
        for(uint8_t i=0; i<32; i++) {
            buf[i] = spi_obj->transfer(0);  // the value is not important
        }

        _pulseSS(false);
    }

    void writeData(uint8_t * data)
    {
        _pulseSS(true);
        
        spi_obj->transfer(CMD_WRITEDATA);
        spi_obj->transfer(0x00);

        for (uint8_t i = 0;  i < 32;  ++i)
            spi_obj->transfer(data[i]);

        _pulseSS(false);
    }


    void flush(uint8_t indicator)
    {
        // Is buffer empty?
        if (buflen == 0)
            return;  

        // Message state indicator
        buffer[0] = indicator;
        
        // Pad the buffer with zeroes
        while (buflen < 30)
            buffer[++buflen] = 0;

        // Compute CRC8
        buffer[31] = crc8(buffer, 31);

        // Wait for slave ready
        // TODO: move the waiting loop to writeByte (defer waiting)
        uint8_t s = waitForSlaveRxReady();
        if (s == SPISLAVE_RX_READY || s == SPISLAVE_RX_ERROR)  // Error state can't be recovered, we can send new data
        {
            // Try to send the buffer 10 times, we may not be stuck in an endless loop
            for (uint8_t i=0; i<10; ++i)
            {
                // Send the buffer
                writeData(buffer);

                if (waitForSlaveRxConfirmation())
                    break;
                else
                    WARN("Bad CRC, retransmitting");
            }
        }
            
        buflen = 0;
    }
    
    void writeByte(uint8_t b)
    {
        bufpos = 0;  // discard input data in the buffer
        
        if (buflen >= 30)
            flush(MESSAGE_CONTINUES);
            
        buffer[++buflen] = b;
    }

    uint8_t readByte()
    {
        buflen = 0;  // discard output data in the buffer
        
        if (bufpos >= 31)  // the buffer segment was read
        {
            if (buffer[0] != MESSAGE_CONTINUES)
              return 0;

            bufpos = 0;  // read next chunk
            
            // Wait for the slave
            waitForSlaveTxReady();
        }
        
        if (bufpos == 0)  // buffer empty
        {
            uint32_t thisTime = millis();

            do {
                readData(buffer);

                if (buffer[31] == crc8(buffer, 31))
                    break;

                WARN("Bad CRC, request repeated");

            }  while (millis() - thisTime < 200);  // repeat until crc is ok or 200 ms elapsed
            
            // Send confirmation to the slave (done through querying a status)
            readStatus();

            // Check the buffer for correctness
            if (buffer[0] != MESSAGE_FINISHED && buffer[0] != MESSAGE_CONTINUES)
              return 0;  // incorrect message (should not happen)

            bufpos = 1;
        }
        return buffer[bufpos++];
    }

    /*
        Waits for slave receiver ready status.
        Return: receiver status
     */
    int8_t waitForSlaveRxReady()
    {
        uint32_t startTime = millis();
        uint16_t status = 0;

        do
        {
            status = readStatus();

            if ((status & 0xff) == ((status >> 8) ^ 0xff))  // check the xor
            {
                uint16_t s = (status >> 4) & 0x0f;
                if (s == SPISLAVE_RX_READY || s == SPISLAVE_RX_ERROR)  // From the perspective of rx state the error is the same as ready 
                    return ((status >> 4) & 0x0f);  // status
            }

            yield();
        } while (millis() - startTime < SLAVE_RX_READY_TIMEOUT);

        WARN2("Slave rx is not ready, status ", (status >> 4) & 0x0f);

        return ((status >> 4) & 0x0f);  // timeout
    }



    /*
        Waits for slave transmitter ready status.
        Return: transmitter status
     */
    int8_t waitForSlaveTxReady()
    {
        uint32_t startTime = millis();
        uint16_t status = 0;

        do
        {
            status = readStatus();

            if ((status & 0xff) == ((status >> 8) ^ 0xff))  // check the xor
            {
                if ((status & 0x0f) == SPISLAVE_TX_READY)
                    return (status & 0x0f);  // status
            }

            yield();
        } while (millis() - startTime < SLAVE_TX_READY_TIMEOUT);

        WARN2("Slave tx is not ready, status ", status & 0x0f);
        
        return (status & 0x0f);  // timeout
    }
    
    /*
        Waits for slave receiver read confirmation or rejection status.
        Status SPISLAVE_RX_CRC_PROCESSING holds the loop, SPISLAVE_RX_ERROR exits with error, other exits ok
        Return: receiver read data ok
     */
    int8_t waitForSlaveRxConfirmation()
    {
        uint32_t startTime = millis();
        uint16_t status = 0;

        do
        {
            status = readStatus();

            if ((status & 0xff) == ((status >> 8) ^ 0xff))  // check the xor
            {
                uint8_t stat = (status >> 4) & 0x0f;

                if (stat == SPISLAVE_RX_ERROR)
                    return false;  // Error status
                else if (stat != SPISLAVE_RX_CRC_PROCESSING)
                    return true;  // OK status

                // Slave is still processing the CRC
            }

            yield();
        } while (millis() - startTime < SLAVE_RX_READY_TIMEOUT);

        WARN2("Slave rx (confirm) is not ready, status ", (status >> 4) & 0x0f);

        return true;  // timeout - we can't retransmit in order not to replay old data, assume everything is ok
    }

    /*
     * Compute crc8 with polynom 0x107 (x^8 + x^2 + x + 1)
     * Lookup table idea: https://lentz.com.au/blog/tag/crc-table-generator
     */
    uint8_t crc8(uint8_t *buffer, uint8_t bufLen)
    {
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

    /*
     * Puts the SS low (required for successfull boot) and resets the ESP
     */
    void hardReset(int8_t hwResetPin)
    {
#if !defined(ESP8266_SAFE_RESET_IMPLEMENTED)
        digitalWrite(_ss_pin, LOW);  // Safe value for ESP8266 GPIO15 
#endif
        digitalWrite(hwResetPin, LOW);
        delay(50);
        digitalWrite(hwResetPin, HIGH);
        delay(200);
    }

};

extern EspSpiProxy espSpiProxy;

#endif

