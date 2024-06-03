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

#ifndef __OWNG_ARDUINO_IDF_ESP32__
#define __OWNG_ARDUINO_IDF_ESP32__

#include "../OneWireNg_BitBang.h"
#include "Platform_Delay.h"

/**
 * Arduino/ESP-IDF ESP32 platform GPIO specific implementation.
 */
class OneWireNg_ArduinoIdfESP32: public OneWireNg_BitBang
{
public:
    /**
     * OneWireNg 1-wire service for Arduino/ESP-IDF ESP32 platform.
     *
     * Bus powering is supported via switching its GPIO to the high state.
     * In this case the GPIO servers as a voltage source for connected slaves
     * working in parasite powering configuration.
     *
     * @param pin GPIO pin number used for bit-banging 1-wire bus.
     * @param pullUp If @c true configure internal pull-up resistor for the bus.
     */
    OneWireNg_ArduinoIdfESP32(unsigned pin, bool pullUp)
    {
        initDtaGpio(pin, pullUp);
    }

#if CONFIG_PWR_CTRL_ENABLED
    /**
     * OneWireNg 1-wire service for Arduino/ESP-IDF ESP32 platform.
     *
     * Bus powering is supported via a switching transistor providing
     * the power to the bus and controlled by a dedicated GPIO (@see
     * OneWireNg_BitBang::setupPwrCtrlGpio()). In this configuration the
     * service mimics the open-drain type of output. The approach may be
     * feasible if the GPIO is unable to provide sufficient power for
     * connected slaves working in parasite powering configuration.
     *
     * @param pin GPIO pin number used for bit-banging 1-wire bus.
     * @param pwrCtrlPin GPIO pin number controlling the switching
     *     transistor.
     * @param pullUp If @c true configure internal pull-up resistor for the bus.
     */
    OneWireNg_ArduinoIdfESP32(unsigned pin, unsigned pwrCtrlPin, bool pullUp)
    {
        initDtaGpio(pin, pullUp);
        initPwrCtrlGpio(pwrCtrlPin);
    }
#endif

protected:
    int readDtaGpioIn();
    void setDtaGpioAsInput();

#if CONFIG_PWR_CTRL_ENABLED
    void writeGpioOut(int state, GpioType gpio);
    void setGpioAsOutput(int state, GpioType gpio);
#else
    void writeGpioOut(int state);
    void setGpioAsOutput(int state);
#endif

#if CONFIG_OVERDRIVE_ENABLED
    int touch1Overdrive();
#endif

    void initDtaGpio(unsigned pin, bool pullUp);

#if CONFIG_PWR_CTRL_ENABLED
    void initPwrCtrlGpio(unsigned pin);

    struct {
        uint32_t bmsk;
        volatile uint32_t *outSetReg;
        volatile uint32_t *outClrReg;
        volatile uint32_t *modSetReg;
        volatile uint32_t *modClrReg;
    } _pwrCtrlGpio;
#endif

    struct {
        uint32_t bmsk;
        volatile uint32_t *inReg;
        volatile uint32_t *outSetReg;
        volatile uint32_t *outClrReg;
        volatile uint32_t *modSetReg;
        volatile uint32_t *modClrReg;
    } _dtaGpio;
};

#endif /* __OWNG_ARDUINO_IDF_ESP32__ */
