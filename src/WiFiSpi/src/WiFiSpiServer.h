/*
  WiFiSPIServer.h - Library for Arduino Wifi SPI connection with ESP8266.
  Copyright (c) 2017 Jiri Bilek. All right reserved.

  ---
  
  Based on WiFiServer.h - Library for Arduino Wifi shield.
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

#ifndef _WIFISPISERVER_H_INCLUDED
#define _WIFISPISERVER_H_INCLUDED

extern "C" {
  #include "utility/wl_definitions.h"
}

#include "Server.h"

class WiFiSpiClient;

class WiFiSpiServer : public Server {
private:
    uint16_t _port;
    void*     pcb;
    uint8_t  _sock;
    
public:
    WiFiSpiServer(uint16_t port);
    WiFiSpiClient available(uint8_t* status = NULL);
  
    void begin();
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buf, size_t size);
    uint8_t status();

    void stop();

    using Print::write;
};

#endif
