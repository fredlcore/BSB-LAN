/*
    ESP8266 SPI Slave for WiFi connection with Arduino
    Connect the SPI Master device to the following pins on the esp8266:

            ESP8266         |        |
    GPIO    NodeMCU   Name  |   Uno  | STM32F103
  ===============================================
     15       D8       SS   |   D10  |    PA4
     13       D7      MOSI  |   D11  |    PA7
     12       D6      MISO  |   D12  |    PA6
     14       D5      SCK   |   D13  |    PA5

    Note: If the ESP is booting at a moment when the SPI Master has the Select line HIGH (deselected)
    the ESP8266 WILL FAIL to boot!

    Device to be compiled for: ESP8266

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

  Version history:
  0.1.0 15.03.17 JB  First version
  0.1.1 25.11.17 JB  Fixed UDP protocol
  0.1.2 28.03.18 JB  Fixed crash when comes an invalid message
                     Removed some unnecessary debug printing from non-debug build
  0.1.3          JB  Added WifiManager (configurable)
  0.1.4 31.10.18 JB  Fixed bad timing of MISO signal - delayed by 1/2 clock cycle
  0.2.0 01.02.19 JB  New communication protocol, more changes
  0.2.1 06.02.19 GYC  WifiManager: added LED blinking
  0.2.2 15.02.19 JB  Dynamically allocated clients, changed NULL to nullptr
  0.2.3 17.02.19 JB  Added SSL Client option using AxTLS, added function VerifySSLClient, protocol 0.2.3
 */

// This define adds WifiManager to the project (optional) (see https://github.com/tzapu/WiFiManager)
//#define WIFIMANAGER_ENABLED

#include "SPISlave.h"
#include "SPICalls.h"
#include "WiFiSPICmd.h"

#include <ESP8266WiFi.h>

#ifdef WIFIMANAGER_ENABLED
    #include <WiFiManager.h>
    #include <Ticker.h>                       
#endif

// Library version (format a.b.c)
const char* VERSION = "0.2.3";
// Protocol version (format a.b.c) 
const char* PROTOCOL_VERSION = "0.2.3";

const uint8_t SS_ENABLE_PIN = 5;  // PIN for circuit blocking SS to GPIO15 on reset 

#ifdef WIFIMANAGER_ENABLED
Ticker ticker;  // for status LED

void tick()
{
    //toggle state
    int state = digitalRead(LED_BUILTIN);  // get the current state of LED
    digitalWrite(LED_BUILTIN, !state);     // set pin to the opposite state
}

// Gets called when WiFiManager enters configuration mode
void configModeCallback(WiFiManager *myWiFiManager)
{
    //Serial.println("Entered config mode");
    //Serial.println(WiFi.softAPIP());
    //if you used auto generated SSID, print it
    //Serial.println(myWiFiManager->getConfigPortalSSID());
    // entered config mode, make led toggle faster
    ticker.attach(1, tick);
}
#endif

/*
 * Setup
 */
void setup()
{
#ifdef WIFIMANAGER_ENABLED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); // turn led off
    // start ticker with 0.15 because we start in AP mode and try to connect
    ticker.attach(0.15, tick);
#endif

    // Serial line for debugging
    Serial.begin(115200);

#ifdef _DEBUG    // _DEBUG can be enabled in SPISlave.h
    Serial.setDebugOutput(true);
#endif

    Serial.printf("\n\nSPI SLAVE ver. %s\nProtocol ver. %s\n", VERSION, PROTOCOL_VERSION);

    WiFi.mode(WIFI_OFF);  // The Wifi is started either by the WifiManager or by user invoking "begin"

    pinMode(SS_ENABLE_PIN, OUTPUT);
    digitalWrite(SS_ENABLE_PIN, HIGH);  // enable SS signal to GPIO15 (https://github.com/JiriBilek/WiFiSpiESP/issues/6)

    #ifdef WIFIMANAGER_ENABLED
        WiFi.persistent(true);
        Serial.println(F("WifiManager enabled."));

        WiFiManager wifiManager;
        
        // set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
        wifiManager.setAPCallback(configModeCallback);
        // connect
        wifiManager.autoConnect();

        // connected successfully
        ticker.detach();
        digitalWrite(LED_BUILTIN, HIGH); // turn led off

    #else
        WiFi.persistent(false);  // Solving trap in ESP8266WiFiSTA.cpp#144 (wifi_station_ap_number_set)
                                 // Relevant for version 2.3.0 of the board SDK software
                                 // Erasing of flash memory might help: https://github.com/kentaylor/EraseEsp8266Flash/blob/master/EraseFlash.ino                
    #endif
    
    // --- Setting callbacks for SPI protocol

    // --- onData
    // Data has been received from the master. Beware that len is always 32
    // and the buffer is autofilled with zeroes if data is less than 32 bytes long
    SPISlave.onData(SPIOnData);

    // --- onDataSent
    // The master has read out outgoing data buffer
    // that buffer can be set with SPISlave.setData
    SPISlave.onDataSent(SPIOnDataSent);

    // --- onStatus
    // Status has been received from the master.
    // The status register is a special register that both the slave and the master can write to and read from.
    // Can be used to exchange small data or status information
    SPISlave.onStatus(SPIOnStatus);

    // --- onStatusSent
    // The master has read the status register
    SPISlave.onStatusSent(SPIOnStatusSent);

    // Setup SPI Slave registers and pins
    SPISlave.begin();

    // Receiver and transmitter state
    setRxStatus(SPISLAVE_RX_READY);
    setTxStatus(SPISLAVE_TX_NODATA);

    // Initialize command processor
    WiFiSpiEspCommandProcessor::init();
}


/**
 * Loop
 */
void loop() {
    // Loop until received data packet
    if (dataReceived) {

        uint8_t dataBuf[32];  // copy of receiver buffer
        
//        uint32_t savedPS = noInterrupts();  // cli();
        memcpy(dataBuf, inputBuffer, 32);
//        xt_wsr_ps(savedPS);  // sei();

#ifdef _DEBUG    
/*        Serial.print("gotData ");
            for (uint8_t i=0; i<32; ++i)
                Serial.printf("%02x ", dataBuf[i]);
        Serial.println();  */
#endif        
     
        WiFiSpiEspCommandProcessor::processCommand(dataBuf);

        // First enable the receiver and then enable the code in loop()
        setRxStatus(SPISLAVE_RX_READY);
        dataReceived = false;
    }
    else
        refreshStatus();  // Helps to stabilize the SPI bus after a reset, only ensures the status register value is ok
}
