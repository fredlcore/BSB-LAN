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

#ifndef __OWNG_ARDUINO_AVR__
#define __OWNG_ARDUINO_AVR__

#include <assert.h>
#include "Arduino.h"
#include "OneWireNg_BitBang.h"
#include "platform/Platform_TimeCritical.h"

#if CONFIG_OVERDRIVE_ENABLED
# if (F_CPU < 16000000L)
#  warning "Overdrive mode supported for 16MHz CPU freq."
# endif
#endif

#define __READ_GPIO(gs) \
    ((*gs.inReg & gs.bmsk) != 0)

#define __WRITE0_GPIO(gs) \
    *gs.outReg &= ~gs.bmsk

#define __WRITE1_GPIO(gs) \
    *gs.outReg |= gs.bmsk

#define __WRITE_GPIO(gs, st) \
    if (st) __WRITE1_GPIO(gs); \
    else __WRITE0_GPIO(gs)

#define __GPIO_AS_INPUT(gs) \
    *gs.modReg &= ~gs.bmsk

#define __GPIO_AS_OUTPUT(gs) \
    *gs.modReg |= gs.bmsk

/**
 * Arduino AVR platform GPIO specific implementation.
 */
class OneWireNg_ArduinoAVR: public OneWireNg_BitBang
{
public:
    /**
     * OneWireNg 1-wire service for Arduino AVR platform.
     *
     * Bus powering is supported via switching its GPIO to the high state.
     * In this case the GPIO servers as a voltage source for connected slaves
     * working in parasite powering configuration.
     *
     * @param pin Arduino GPIO pin number used for bit-banging 1-wire bus.
     * @param pullUp If @c true configure internal pull-up resistor for the bus.
     */
    OneWireNg_ArduinoAVR(unsigned pin, bool pullUp)
    {
        initDtaGpio(pin, pullUp);
    }

#if CONFIG_PWR_CTRL_ENABLED
    /**
     * OneWireNg 1-wire service for Arduino AVR platform.
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
    OneWireNg_ArduinoAVR(unsigned pin, unsigned pwrCtrlPin, bool pullUp)
    {
        initDtaGpio(pin, pullUp);
        initPwrCtrlGpio(pwrCtrlPin);
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

#if CONFIG_PWR_CTRL_ENABLED
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
            __GPIO_AS_OUTPUT(_dtaGpio);
            __WRITE_GPIO(_dtaGpio, state);
        } else {
            __GPIO_AS_OUTPUT(_pwrCtrlGpio);
            __WRITE_GPIO(_pwrCtrlGpio, state);
        }
    }
#else
    TIME_CRITICAL void writeGpioOut(int state)
    {
        __WRITE_GPIO(_dtaGpio, state);
    }

    TIME_CRITICAL void setGpioAsOutput(int state)
    {
        __GPIO_AS_OUTPUT(_dtaGpio);
        __WRITE_GPIO(_dtaGpio, state);
    }
#endif /* CONFIG_PWR_CTRL_ENABLED */

#if CONFIG_OVERDRIVE_ENABLED
    TIME_CRITICAL int touch1Overdrive()
    {
        __GPIO_AS_OUTPUT(_dtaGpio);
        __WRITE0_GPIO(_dtaGpio);

        /* speed up low-to-high transition */
        __WRITE1_GPIO(_dtaGpio);
        __GPIO_AS_INPUT(_dtaGpio);

        return __READ_GPIO(_dtaGpio);
    }
#endif

    void initDtaGpio(unsigned pin, bool pullUp)
    {
        uint8_t port = digitalPinToPort(pin);
        assert(port != NOT_A_PIN);

        _dtaGpio.bmsk = digitalPinToBitMask(pin);
        _dtaGpio.inReg = portInputRegister(port);
        _dtaGpio.outReg = portOutputRegister(port);
        _dtaGpio.modReg = portModeRegister(port);

        __GPIO_AS_INPUT(_dtaGpio);

        /* writing the output register when the GPIO is set
           in the input mode configures its pull-up resistor */
        if (pullUp) {
            __WRITE_GPIO(_dtaGpio, 0);
        } else {
            __WRITE_GPIO(_dtaGpio, 1);
        }

        setupDtaGpio();
    }

#if CONFIG_PWR_CTRL_ENABLED
    void initPwrCtrlGpio(unsigned pin)
    {
        uint8_t port = digitalPinToPort(pin);
        assert(port != NOT_A_PIN);

        _pwrCtrlGpio.bmsk = digitalPinToBitMask(pin);
        _pwrCtrlGpio.outReg = portOutputRegister(port);
        _pwrCtrlGpio.modReg = portModeRegister(port);

        setupPwrCtrlGpio(true);
    }

    struct {
        uint8_t bmsk;
        volatile uint8_t *outReg;
        volatile uint8_t *modReg;
    } _pwrCtrlGpio;
#endif

    struct {
        uint8_t bmsk;
        volatile uint8_t *inReg;
        volatile uint8_t *outReg;
        volatile uint8_t *modReg;
    } _dtaGpio;
};

#undef __GPIO_AS_OUTPUT
#undef __GPIO_AS_INPUT
#undef __WRITE_GPIO
#undef __READ_GPIO

#endif /* __OWNG_ARDUINO_AVR__ */
