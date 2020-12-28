/*
  SPISlave library for esp8266

  Copyright (c) 2017 Jiri Bilek. All rights reserved.

  Based on SPISlave example application for ESP8266.
  Copyright (c) 2015 Hristo Gochkov. All rights reserved.
  This file is part of the esp8266 core for Arduino environment.

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
#ifndef _SPISLAVE_H_INCLUDED
#define _SPISLAVE_H_INCLUDED

#include "Arduino.h"

class SPISlaveClass
{
protected:
    void (*_data_cb)(uint8_t *data, size_t len);
    void (*_status_cb)(uint16_t status);
    void (*_data_sent_cb)(void);
    void (*_status_sent_cb)(void);
    
    void _data_rx(uint8_t * data, uint8_t len);
    void _status_rx(uint16_t data);
    void _data_tx(void);
    void _status_tx(void);
    
    static void _s_data_rx(void *arg, uint8_t * data, uint8_t len);
    static void _s_status_rx(void *arg, uint16_t data);
    static void _s_data_tx(void *arg);
    static void _s_status_tx(void *arg);
    
public:
    SPISlaveClass()
        : _data_cb(NULL)
        , _status_cb(NULL)
        , _data_sent_cb(NULL)
        , _status_sent_cb(NULL)
    {}
    ~SPISlaveClass() {}
    void begin();
    void setData(uint8_t * data, size_t len = 32);
    void setStatus(uint16_t status);

    void onData(void (*cb)(uint8_t *data, size_t len));
    void onDataSent(void (*cb)(void));
    void onStatus(void (*cb)(uint16_t status));
    void onStatusSent(void (*cb)(void));
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SPISLAVE)
extern SPISlaveClass SPISlave;
#endif

#endif
