/*
  config.h - Library for Arduino SPI connection to ESP8266
  Copyright (c) 2019 Jiri Bilek. All rights reserved.

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

  -----------------------------------------------------

  This file is a "center of configuration options". All important options for the
  library are concentrated here.
*/

#ifndef _CONFIG_H_INCLUDED
#define _CONFIG_H_INCLUDED

// Uncomment the following define if the safe reset circuit (https://github.com/JiriBilek/WiFiSpiESP/issues/6)
// is connected to SS pin on ESP8266. This allows the SS signal to behave exactly
// according SPI specification (goes low before transmission and high after)
#define ESP8266_SAFE_RESET_IMPLEMENTED

// Allow debugging information to be print on Serial
#define ESPSPI_DEBUG_OPTION

// Print information about received bad message on Serial
//#define ESPSPI_DEBUG_OPTION_BAD_MESSAGE

#endif
