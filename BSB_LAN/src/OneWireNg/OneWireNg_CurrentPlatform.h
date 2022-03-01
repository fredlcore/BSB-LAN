/*
 * Copyright (c) 2019-2021 Piotr Stolarz
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
#elif defined(ARDUINO_ARCH_ESP8266)
# include "platform/OneWireNg_ArduinoESP8266.h"
# define OneWireNg_CurrentPlatform OneWireNg_ArduinoESP8266
#elif defined(ARDUINO_ARCH_ESP32)
# include "platform/OneWireNg_ArduinoESP32.h"
# define OneWireNg_CurrentPlatform OneWireNg_ArduinoESP32
#elif defined(ARDUINO_ARCH_STM32)
# include "platform/OneWireNg_ArduinoSTM32.h"
# define OneWireNg_CurrentPlatform OneWireNg_ArduinoSTM32
#elif defined(ARDUINO_ARCH_MBED)
# include "platform/OneWireNg_ArduinoMbedHAL.h"
# define OneWireNg_CurrentPlatform OneWireNg_ArduinoMbedHAL
#else
# define OneWireNg_CurrentPlatform
# warning "Can't detect platform. Use proper class for the platform you are compiling for!"
#endif

#endif /* OneWireNg_CurrentPlatform */
