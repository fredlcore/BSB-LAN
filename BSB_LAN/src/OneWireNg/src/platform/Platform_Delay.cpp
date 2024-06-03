/*
 * Copyright (c) 2022 Piotr Stolarz
 * OneWireNg: Arduino 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

#include "Platform_Delay.h"

#if CONFIG_BITBANG_DELAY_CCOUNT
# define CCOUNT_ADJUST 15

# if defined(ARDUINO_ARCH_ESP8266) || defined(CONFIG_IDF_TARGET_ESP8266)
unsigned cpuFreqMHz = 0;
unsigned ccntAdjst = CCOUNT_ADJUST;

#  ifdef ARDUINO
#   include "core_esp8266_features.h"

unsigned ccntUpdateCpuFreqMHz(void)
{
    cpuFreqMHz =  (unsigned)esp_get_cpu_freq_mhz();
    return cpuFreqMHz;
}
#  else
/* ESP8266 RTOS SDK specific */
#   include "driver/rtc.h"

unsigned ccntUpdateCpuFreqMHz(void)
{
    switch (rtc_clk_cpu_freq_get())
    {
    case RTC_CPU_FREQ_80M:
        cpuFreqMHz =  80;
        break;

    case RTC_CPU_FREQ_160M:
        cpuFreqMHz =  160;
        break;
    }
    return cpuFreqMHz;
}
#  endif
# elif defined(ARDUINO_ARCH_ESP32) || defined(IDF_VER)
#  include "soc/rtc.h"

unsigned cpuFreqMHz = 0;
unsigned ccntAdjst = 0;

unsigned ccntUpdateCpuFreqMHz(void)
{
    rtc_cpu_freq_config_t conf;
    rtc_clk_cpu_freq_get_config(&conf);

    cpuFreqMHz =  (unsigned)conf.freq_mhz;
    ccntAdjst = (cpuFreqMHz >= 20 ? CCOUNT_ADJUST : 0);

    return cpuFreqMHz;
}
# endif
#endif /* CONFIG_BITBANG_DELAY_CCOUNT */

#ifdef IDF_VER
# include "esp_timer.h"

TIME_CRITICAL void idf_delayUs(uint32_t us)
{
    if (us > 0) {
        uint64_t stop = ((uint64_t)esp_timer_get_time() + us);
        while((int64_t)(stop - (uint64_t)esp_timer_get_time()) > 0);
    }
}
#endif
