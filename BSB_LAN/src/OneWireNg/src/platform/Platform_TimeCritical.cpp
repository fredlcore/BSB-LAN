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

#include "Platform_TimeCritical.h"

#if defined(ARDUINO_ARCH_ESP8266) || defined(CONFIG_IDF_TARGET_ESP8266)
unsigned _tc_ccnt;
bool _tc_actv;
#elif defined(ARDUINO_ARCH_ESP32) || defined(IDF_VER) || defined(PICO_BUILD)
tc_t _tc[portNUM_PROCESSORS];
#endif
