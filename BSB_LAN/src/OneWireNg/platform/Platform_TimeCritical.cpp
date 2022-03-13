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

#ifdef ARDUINO_ARCH_ESP32
# include "../platform/Platform_TimeCritical.h"

unsigned esp_int_level[portNUM_PROCESSORS];
#endif
