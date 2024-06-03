/*
 * Copyright (c) 2019-2022 Piotr Stolarz
 * OneWireNg: Arduino 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

#ifndef OneWireNg_CurrentPlatform

#include "OneWireNg_Config.h"
#ifdef IDF_VER
# include "sdkconfig.h"
#endif

/*
 * Try to detect current platform by inspecting the environment and:
 * - include proper platform class header,
 * - assign OneWireNg_CurrentPlatform macro-define to the detected platform class.
 */
#if defined(ARDUINO_ARCH_AVR)
# include "platform/OneWireNg_ArduinoAVR.h"
# define OneWireNg_CurrentPlatform OneWireNg_ArduinoAVR
#elif defined(ARDUINO_ARCH_MEGAAVR)
# include "platform/OneWireNg_ArduinoMegaAVR.h"
# define OneWireNg_CurrentPlatform OneWireNg_ArduinoMegaAVR
#elif defined(ARDUINO_ARCH_SAM)
# include "platform/OneWireNg_ArduinoSAM.h"
# define OneWireNg_CurrentPlatform OneWireNg_ArduinoSAM
#elif defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_SAMD_BETA)
# include "platform/OneWireNg_ArduinoSAMD.h"
# define OneWireNg_CurrentPlatform OneWireNg_ArduinoSAMD
#elif defined(ARDUINO_ARCH_ESP8266) || defined(CONFIG_IDF_TARGET_ESP8266)
# include "platform/OneWireNg_ArduinoIdfESP8266.h"
# define OneWireNg_CurrentPlatform OneWireNg_ArduinoIdfESP8266
#elif defined(ARDUINO_ARCH_ESP32) || defined(IDF_VER)
# include "platform/OneWireNg_ArduinoIdfESP32.h"
# define OneWireNg_CurrentPlatform OneWireNg_ArduinoIdfESP32
#elif defined(ARDUINO_ARCH_STM32)
# include "platform/OneWireNg_ArduinoSTM32.h"
# define OneWireNg_CurrentPlatform OneWireNg_ArduinoSTM32
#elif defined(PICO_BUILD) || defined(ARDUINO_ARCH_RP2040)
# if CONFIG_RP2040_PIO_DRIVER
#  include "platform/OneWireNg_PicoRP2040PIO.h"
#  define OneWireNg_CurrentPlatform OneWireNg_PicoRP2040PIO
# else
#  include "platform/OneWireNg_PicoRP2040.h"
#  define OneWireNg_CurrentPlatform OneWireNg_PicoRP2040
# endif
#elif defined(ARDUINO_ARCH_MBED) || defined(__MBED__)
# include "platform/OneWireNg_ArduinoMbedHAL.h"
# define OneWireNg_CurrentPlatform OneWireNg_ArduinoMbedHAL
#else
# define OneWireNg_CurrentPlatform
# warning "Can't detect platform. Use proper class for the platform you are compiling for!"
#endif

#endif /* OneWireNg_CurrentPlatform */
