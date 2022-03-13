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

#ifndef __OWNG_ARDUINO_ESP8266__
#define __OWNG_ARDUINO_ESP8266__

#include <assert.h>
#include "Arduino.h"
#include "../OneWireNg_BitBang.h"
#include "../platform/Platform_Delay.h"
#include "../platform/Platform_TimeCritical.h"

#define __READ_GPIO(gs) \
    ((*gs.inReg & gs.bmsk) != 0)

#define __WRITE0_GPIO(gs) GPOC = gs.bmsk
#define __WRITE0_GPIO16() GP16O &= ~(uint32_t)1

#define __WRITE1_GPIO(gs) GPOS = gs.bmsk
#define __WRITE1_GPIO16() GP16O |= (uint32_t)1

#define __WRITE_GPIO(gs, st) \
    if (gs.pin < 16) { \
        if (st) { __WRITE1_GPIO(gs); } else { __WRITE0_GPIO(gs); } \
    } else { \
        if (st) { __WRITE1_GPIO16(); } else { __WRITE0_GPIO16(); } \
    }

#define __GPIO_SET_INPUT(gs) GPEC = gs.bmsk
#define __GPIO16_SET_INPUT() GP16E &= ~(uint32_t)1

#define __GPIO_AS_INPUT(gs) \
    if (gs.pin < 16) { __GPIO_SET_INPUT(gs); } else { __GPIO16_SET_INPUT(); }

#define __GPIO_SET_OUTPUT(gs) GPES = gs.bmsk
#define __GPIO16_SET_OUTPUT() GP16E |= (uint32_t)1

#define __GPIO_AS_OUTPUT(gs) \
    if (gs.pin < 16) { __GPIO_SET_OUTPUT(gs); } else { __GPIO16_SET_OUTPUT(); }

/**
 * Arduino ESP8266 platform GPIO specific implementation.
 */
class OneWireNg_ArduinoESP8266: public OneWireNg_BitBang
{
public:
    /**
     * OneWireNg 1-wire service for Arduino ESP8266 platform.
     *
     * Bus powering is supported via switching its GPIO to the high state.
     * In this case the GPIO servers as a voltage source for connected slaves
     * working in parasite powering configuration.
     *
     * @param pin Arduino GPIO pin number used for bit-banging 1-wire bus.
     * @param pullUp If @c true configure internal pull-up resistor for the bus.
     */
    OneWireNg_ArduinoESP8266(unsigned pin, bool pullUp)
    {
        initDtaGpio(pin, pullUp);
#if (CONFIG_ESP8266_INIT_TIME > 0)
        delayMs(CONFIG_ESP8266_INIT_TIME);
#endif
    }

#ifdef CONFIG_PWR_CTRL_ENABLED
    /**
     * OneWireNg 1-wire service for Arduino ESP8266 platform.
     *
     * Bus powering is supported via a switching transistor providing
     * the power to the bus and controlled by a dedicated GPIO (@see
     * OneWireNg_BitBang::setupPwrCtrlGpio()). In this configuration the
     * service mimics the open-drain type of output. The approach may be
     * feasible if the GPIO is unable to provide sufficient power for
     * connected slaves working in parasite powering configuration.
     *
     * @param pin Arduino GPIO pin number used for bit-banging 1-wire bus.
     * @param pwrCtrlPin Arduino GPIO pin number controlling the switching
     *     transistor.
     * @param pullUp If @c true configure internal pull-up resistor for the bus.
     */
    OneWireNg_ArduinoESP8266(unsigned pin, unsigned pwrCtrlPin, bool pullUp)
    {
        initDtaGpio(pin, pullUp);
        initPwrCtrlGpio(pwrCtrlPin);
# if (CONFIG_ESP8266_INIT_TIME > 0)
        delayMs(CONFIG_ESP8266_INIT_TIME);
# endif
    }
#endif

protected:
    TIME_CRITICAL int readDtaGpioIn()
    {
        return __READ_GPIO(_dtaGpio);
    }

    TIME_CRITICAL void setDtaGpioAsInput()
    {
        __GPIO_AS_INPUT(_dtaGpio);
    }

#ifdef CONFIG_PWR_CTRL_ENABLED
    TIME_CRITICAL void writeGpioOut(int state, GpioType gpio)
    {
        if (gpio == GPIO_DTA) {
            __WRITE_GPIO(_dtaGpio, state);
        } else {
            __WRITE_GPIO(_pwrCtrlGpio, state);
        }
    }

    TIME_CRITICAL void setGpioAsOutput(int state, GpioType gpio)
    {
        if (gpio == GPIO_DTA) {
            __WRITE_GPIO(_dtaGpio, state);
            __GPIO_AS_OUTPUT(_dtaGpio);
        } else {
            __WRITE_GPIO(_pwrCtrlGpio, state);
            __GPIO_AS_OUTPUT(_pwrCtrlGpio);
        }
    }
#else
    TIME_CRITICAL void writeGpioOut(int state )
    {
        __WRITE_GPIO(_dtaGpio, state);
    }

    TIME_CRITICAL void setGpioAsOutput(int state)
    {
        __WRITE_GPIO(_dtaGpio, state);
        __GPIO_AS_OUTPUT(_dtaGpio);
    }
#endif /* CONFIG_PWR_CTRL_ENABLED */

#ifdef CONFIG_OVERDRIVE_ENABLED
    TIME_CRITICAL int touch1Overdrive()
    {
        if (_dtaGpio.pin < 16)
        {
            __WRITE0_GPIO(_dtaGpio);
            __GPIO_SET_OUTPUT(_dtaGpio);

            /* speed up low-to-high transition */
            __WRITE1_GPIO(_dtaGpio);
            __GPIO_SET_INPUT(_dtaGpio);
        } else
        {
            __WRITE0_GPIO16();
            __GPIO16_SET_OUTPUT();

            /* speed up low-to-high transition */
            __WRITE1_GPIO16();
            __GPIO16_SET_INPUT();
        }
        return __READ_GPIO(_dtaGpio);
    }
#endif

    void initDtaGpio(unsigned pin, bool pullUp)
    {
        /* only pins < 16 can be configured with internal pull-up */
        assert(pullUp ? pin < 16 : pin <= 16);

        _dtaGpio.pin = pin;
        _dtaGpio.bmsk = (pin < 16 ? (uint32_t)(1UL << pin) : 1);
        _dtaGpio.inReg = (pin < 16 ? &GPI : &GP16I);

        pinMode(pin, (pullUp ? INPUT_PULLUP : INPUT));
        setupDtaGpio();
    }

#ifdef CONFIG_PWR_CTRL_ENABLED
    void initPwrCtrlGpio(unsigned pin)
    {
        assert(pin <= 16);

        _pwrCtrlGpio.pin = pin;
        _pwrCtrlGpio.bmsk = (pin < 16 ? (uint32_t)(1UL << pin) : 1);

        pinMode(pin, OUTPUT);
        setupPwrCtrlGpio(true);
    }

    struct {
        uint32_t pin;
        uint32_t bmsk;
    } _pwrCtrlGpio;
#endif

    struct {
        uint32_t pin;
        uint32_t bmsk;
        volatile uint32_t *inReg;
    } _dtaGpio;
};

#undef __GPIO_AS_OUTPUT
#undef __GPIO_AS_INPUT
#undef __WRITE_GPIO
#undef __READ_GPIO

#endif /* __OWNG_ARDUINO_ESP8266__ */
