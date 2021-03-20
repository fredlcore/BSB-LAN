/*
  debug.h - Library for Arduino Wifi shield.
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
//  File:   debug.h
// 
//  Author: dlf (Metodo2 srl)
// 
//********************************************/


#ifndef _DEBUG_H_INCLUDED
#define _DEBUG_H_INCLUDED

#define DBGOUT  Serial

#include <stdio.h>
#include <string.h>
#include "../config.h"

const char *DbgFileName(const char *s);


#define PRINT_FILE_LINE() do { 						\
		DBGOUT.print("[");DBGOUT.print(DbgFileName(__FILE__));		\
		DBGOUT.print(":");DBGOUT.print(__LINE__);DBGOUT.print("]");\
}while (0);

#if defined(ESPSPI_DEBUG_OPTION)

#define INFO(format, args...) do { \
	char buf[250];	\
	sprintf(buf, format, args); \
	DBGOUT.println(buf); \
} while(0);

#define INFO1(x) do { PRINT_FILE_LINE() DBGOUT.print(" I: ");\
		DBGOUT.println(x);    			\
}while (0);


#define INFO2(x,y) do { PRINT_FILE_LINE() DBGOUT.print(" I: ");\
		DBGOUT.print(x,16);DBGOUT.print(",");DBGOUT.println(y,16); \
}while (0);


#else
#define INFO1(x) do {} while(0);
#define INFO2(x,y) do {} while(0);
#define INFO(format, args...) do {} while(0);
#endif

#if defined(ESPSPI_DEBUG_OPTION)
#define WARN(args) do { PRINT_FILE_LINE()			\
		DBGOUT.print(" W: "); DBGOUT.println(args);	\
}while (0);
#define WARN2(arg1,args) do { PRINT_FILE_LINE()			\
		DBGOUT.print(" W: "); DBGOUT.print(arg1); DBGOUT.println(args);	\
}while (0);
#else
#define WARN(args) do {} while (0);
#define WARN2(arg1,args) do {} while (0);
#endif

#endif
