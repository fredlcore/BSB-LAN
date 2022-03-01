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

#ifndef __OWNG_PLATFORM_TIME_CRITICAL__
#define __OWNG_PLATFORM_TIME_CRITICAL__

#ifdef ARDUINO
# include "Arduino.h"
# ifdef ARDUINO_ARCH_ESP32
# include "freertos/task.h"
/*
 * NOTE: Arduino ESP32 has interrupts() and noInterrupts() implemented as NOPs,
 * therefore they don't provide proper timing guards in time critical parts of
 * code.
 *
 * This implementation of time critical enter/exit routines bases on Xtensa
 * FreeRTOS API for disabling/enabling interrupts locally (exclusively for
 * a CPU core the routine is called on).
 *
 * Time critical routines need to be marked by TIME_CRITICAL attribute.
 * Currently it's required for ESP32 platforms only to place the routines
 * into IRAM due to xPortGetCoreID() usage, which is IRAM inlined.
 */
static unsigned _int_level[portNUM_PROCESSORS];

#  define timeCriticalEnter() \
    _int_level[xPortGetCoreID()] = portSET_INTERRUPT_MASK_FROM_ISR()
#  define timeCriticalExit() \
    portCLEAR_INTERRUPT_MASK_FROM_ISR(_int_level[xPortGetCoreID()])
#  define TIME_CRITICAL IRAM_ATTR
# else
#  define timeCriticalEnter() noInterrupts()
#  define timeCriticalExit() interrupts()
# endif
#else
# ifndef __TEST__
#  warning "Time critical API unsupported for the target platform. Disabled."
# endif
# define timeCriticalEnter()
# define timeCriticalExit()
#endif

#ifndef TIME_CRITICAL
# define TIME_CRITICAL
#endif

#endif /* __OWNG_PLATFORM_TIME_CRITICAL__ */
