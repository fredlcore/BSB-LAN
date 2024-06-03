/*
 * Copyright (c) 2021,2022 Piotr Stolarz
 * OneWireNg: Arduino 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

#ifndef __OWNG_PLATFORM_FLASH_MEM__
#define __OWNG_PLATFORM_FLASH_MEM__

#ifdef ARDUINO
# include "Arduino.h"
# define FLASH_STORAGE PROGMEM const
# define flashRead_u8(addr) pgm_read_byte(addr)
# define flashRead_u16(addr) pgm_read_word(addr)
# define flashRead_u32(addr) pgm_read_dword(addr)
#else
# define FLASH_STORAGE const
# define flashRead_u8(addr) (*(const uint8_t*)(addr))
# define flashRead_u16(addr) (*(const uint16_t*)(addr))
# define flashRead_u32(addr) (*(const uint32_t*)(addr))
#endif

#endif /* __OWNG_PLATFORM_FLASH_MEM__ */
