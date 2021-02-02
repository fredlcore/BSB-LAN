/*
  debug.c - Library for Arduino Wifi shield.
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
//*********************************************/
// 
//  File:   debug.c
// 
//  Author: Jiri Bilek
// 
//********************************************/

#include "debug.h"

#if defined(ESPSPI_DEBUG_OPTION)

#include <string.h>

// Only filename without path
const char *DbgFileName(const char *s) 
{
  const char *p = s + strlen(s);
  while (--p > s)
  {
    if (*p == '/' || *p == '\\')
      return p + 1;
  }

  return s;
}

#endif
