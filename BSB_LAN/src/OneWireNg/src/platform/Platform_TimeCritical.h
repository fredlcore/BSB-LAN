/*
 * Copyright (c) 2021,2022,2024 Piotr Stolarz
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

#include "../OneWireNg_Config.h"
#ifdef ARDUINO
# include "Arduino.h"
#elif defined(IDF_VER)
# include "esp_attr.h"
# include "sdkconfig.h"
# include "freertos/FreeRTOS.h"
#elif defined(__MBED__)
# include "mbed.h"
#endif

#if CONFIG_BITBANG_DELAY_CCOUNT
# if defined(CONFIG_IDF_TARGET_ESP32C2) || defined(CONFIG_IDF_TARGET_ESP32C3) || \
    defined(CONFIG_IDF_TARGET_ESP32C6) || defined(CONFIG_IDF_TARGET_ESP32H2) || \
    defined(CONFIG_IDF_TARGET_ESP32P4)
#  include "esp_cpu.h"
#  include "esp_idf_version.h"
#  if (ESP_IDF_VERSION_MAJOR >= 5)
#   define get_cpu_cycle_count() esp_cpu_get_cycle_count()
#  else
#   define get_cpu_cycle_count() esp_cpu_get_ccount()
#  endif
# elif defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32) || defined(IDF_VER)
extern "C" unsigned xthal_get_ccount();
#  define get_cpu_cycle_count() xthal_get_ccount()
# endif
#endif

#if defined(ARDUINO_ARCH_ESP8266) || defined(CONFIG_IDF_TARGET_ESP8266)
extern unsigned _tc_ccnt;   /* cycle counter (at delay start) */
extern bool _tc_actv;       /* is time critical section active? */

# ifndef ARDUINO
#  define noInterrupts() portDISABLE_INTERRUPTS()
#  define interrupts() portENABLE_INTERRUPTS()
# endif

/*
 * If appropriately configured the cycle counter state is saved at the entry
 * point for a purpose of accurate timings calculation.
 */
# if CONFIG_BITBANG_DELAY_CCOUNT
#  define timeCriticalEnter() \
    _tc_actv = true; \
    noInterrupts(); \
    _tc_ccnt = get_cpu_cycle_count()

#  define timeCriticalExit() \
    interrupts(); \
    _tc_actv = false
# else
#  define timeCriticalEnter() noInterrupts()
#  define timeCriticalExit() interrupts()
# endif
#elif defined(ARDUINO_ARCH_ESP32) || defined(IDF_VER)
typedef struct {
    unsigned int_lev;       /* saved interrupt level */
# if CONFIG_BITBANG_DELAY_CCOUNT
    unsigned ccnt;          /* cycle counter (at delay start) */
    bool actv;              /* is time critical section active? */
# endif
} tc_t;
extern tc_t _tc[portNUM_PROCESSORS];

/*
 * ESP32 implementation of time critical enter/exit routines bases on Xtensa
 * FreeRTOS API for disabling/enabling interrupts locally (exclusively for
 * a CPU core the routine is called on).
 *
 * If appropriately configured the cycle counter state is saved at the entry
 * point for a purpose of accurate timings calculation.
 */
# if CONFIG_BITBANG_DELAY_CCOUNT
#  define timeCriticalEnter() \
    _tc[xPortGetCoreID()].actv = true; \
    _tc[xPortGetCoreID()].int_lev = portSET_INTERRUPT_MASK_FROM_ISR(); \
    _tc[xPortGetCoreID()].ccnt = get_cpu_cycle_count()

#  define timeCriticalExit() \
    portCLEAR_INTERRUPT_MASK_FROM_ISR(_tc[xPortGetCoreID()].int_lev); \
    _tc[xPortGetCoreID()].actv = false
# else
#  define timeCriticalEnter() \
    _tc[xPortGetCoreID()].int_lev = portSET_INTERRUPT_MASK_FROM_ISR()

#  define timeCriticalExit() \
    portCLEAR_INTERRUPT_MASK_FROM_ISR(_tc[xPortGetCoreID()].int_lev)
# endif
#elif defined(ARDUINO)
# define timeCriticalEnter() noInterrupts()
# define timeCriticalExit() interrupts()
#elif defined(__MBED__)
# define timeCriticalEnter() __disable_irq()
# define timeCriticalExit() __enable_irq()
#elif defined(PICO_BUILD)
# include "hardware/sync.h"

#define portNUM_PROCESSORS 2
typedef struct {
    uint32_t int_lev;       /* saved interrupt level */
} tc_t;
extern tc_t _tc[portNUM_PROCESSORS];

# define timeCriticalEnter() \
    _tc[get_core_num()].int_lev = save_and_disable_interrupts()

# define timeCriticalExit() \
    restore_interrupts(_tc[get_core_num()].int_lev)
#else
# ifndef OWNG_TEST
#  warning "Time critical API unsupported for the target platform. Disabled."
# endif
# define timeCriticalEnter()
# define timeCriticalExit()
#endif

/*
 * Time critical routines need to be marked by TIME_CRITICAL attribute.
 * Currently it's required for ESP platforms only to place the routines
 * into IRAM.
 */
#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32) || defined(IDF_VER)
# define TIME_CRITICAL IRAM_ATTR
#else
# define TIME_CRITICAL
#endif

#endif /* __OWNG_PLATFORM_TIME_CRITICAL__ */
