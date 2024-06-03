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

#ifndef __OWNG_PLATFORM_DELAY__
#define __OWNG_PLATFORM_DELAY__

#include "Platform_TimeCritical.h"

#ifdef ARDUINO
# define delayMs(ms) delay(ms)
# define _delayUs(us) delayMicroseconds(us)
#elif defined(IDF_VER)
# include "freertos/task.h"
void idf_delayUs(uint32_t us);
# define delayMs(ms) vTaskDelay((ms) / portTICK_PERIOD_MS)
# define _delayUs(us) idf_delayUs(us)
#elif defined(PICO_BUILD)
# include "pico/time.h"
# define delayMs(ms) sleep_ms(ms)
# define delayUs(us) sleep_us(us)
#elif defined(__MBED__)
# ifndef NO_RTOS
#  define delayMs(ms) rtos::ThisThread::sleep_for(ms * 1ms)
# else
#  define delayMs(ms) wait_us(ms * 1000)
# endif
# define delayUs(us) wait_us(us)
#elif OWNG_TEST
# include <unistd.h>
# define delayMs(ms) usleep(1000L * (ms))
# define delayUs(us) usleep(us)
#else
# error "Delay API unsupported for the target platform."
#endif

#if CONFIG_BITBANG_DELAY_CCOUNT
# if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32) || defined(IDF_VER)
/**
 * If the library is configured with @c CONFIG_BITBANG_DELAY_CCOUNT,
 * CPU frequency is detected at runtime by the library. Since the frequency
 * (in most common cases) is not an entity which is going to change, for
 * performance reason the library read the frequency once and next uses the
 * read value. If a user code changes the CPU frequency on runtime, it needs
 * to inform the library about the change by calling @c ccntUpdateCpuFreqMHz().
 *
 * @return Current CPU frequency (MHz).
 */
unsigned ccntUpdateCpuFreqMHz(void);

/* CPU frequency (MHz) */
extern unsigned cpuFreqMHz;

/*
 * Cycles counter adjustment
 * (important for accurate timings on lower frequencies).
 */
extern unsigned ccntAdjst;

/*
 * Delay may be performed in two modes:
 * - Relaxed (aside critical section) with interrupt re-entrancy enabled.
 *   Accuracy is not required.
 * - Strict (inside critical section) with interrupt disabled. Timing
 *   accuracy reached by CPU clock cycles tracking.
 */
#  if defined(ARDUINO_ARCH_ESP8266) || defined(CONFIG_IDF_TARGET_ESP8266)
#   define delayUs(us) \
    if (_tc_actv) { \
        unsigned stop = (_tc_ccnt += \
            (unsigned)(us) * cpuFreqMHz + ccntAdjst); \
        while ((int)(stop - get_cpu_cycle_count()) > 0); \
    } else { \
        _delayUs(us); \
    }
#  else
#   define delayUs(us) \
    if (_tc[xPortGetCoreID()].actv) { \
        unsigned stop = (_tc[xPortGetCoreID()].ccnt += \
            (unsigned)(us) * cpuFreqMHz + ccntAdjst); \
        while ((int)(stop - get_cpu_cycle_count()) > 0); \
    } else { \
        _delayUs(us); \
    }
#  endif
# endif /* ESP */
#endif /* CONFIG_BITBANG_DELAY_CCOUNT */

#ifndef delayUs
# define delayUs(us) _delayUs(us)
#endif

#endif /* __OWNG_PLATFORM_DELAY__ */
