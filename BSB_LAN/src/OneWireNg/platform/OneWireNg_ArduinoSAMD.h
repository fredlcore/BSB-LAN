/*
 * Copyright (c) 2020-2022 Piotr Stolarz
 * OneWireNg: Arduino 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

#ifndef __OWNG_ARDUINO_SAMD__
#define __OWNG_ARDUINO_SAMD__

#include <assert.h>
#include "Arduino.h"
#include "../OneWireNg_BitBang.h"
#include "../platform/Platform_TimeCritical.h"

#define __READ_GPIO(gs) \
    ((*gs.inReg & gs.bmsk) != 0)

#define __WRITE_GPIO(gs, st) \
    if (st) *gs.outSetReg = gs.bmsk; \
    else *gs.outClrReg = gs.bmsk

#define __GPIO_AS_INPUT(gs) \
    *gs.modClrReg = gs.bmsk

#define __GPIO_AS_OUTPUT(gs) \
    *gs.modSetReg = gs.bmsk

/**
 * Arduino SAMD platform GPIO specific implementation.
 */
class OneWireNg_ArduinoSAMD: public OneWireNg_BitBang
{
public:
    /**
     * OneWireNg 1-wire service for Arduino SAMD platform.
     *
     * Bus powering is supported via switching its GPIO to the high state.
     * In this case the GPIO servers as a voltage source for connected slaves
     * working in parasite powering configuration.
     *
     * @param pin Arduino GPIO pin number used for bit-banging 1-wire bus.
     * @param pullUp If @c true configure internal pull-up resistor for the bus.
     */
    OneWireNg_ArduinoSAMD(unsigned pin, bool pullUp)
    {
        initDtaGpio(pin, pullUp);
    }

#ifdef CONFIG_PWR_CTRL_ENABLED
    /**
     * OneWireNg 1-wire service for Arduino SAMD platform.
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
    OneWireNg_ArduinoSAMD(unsigned pin, unsigned pwrCtrlPin, bool pullUp)
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
    TIME_CRITICAL void writeGpioOut(int state)
    {
        __WRITE_GPIO(_dtaGpio, state);
    }

    TIME_CRITICAL void setGpioAsOutput(int state)
    {
        __WRITE_GPIO(_dtaGpio, state);
        __GPIO_AS_OUTPUT(_dtaGpio);
    }
#endif /* CONFIG_PWR_CTRL_ENABLED */

    void initDtaGpio(unsigned pin, bool pullUp)
    {
        assert(g_APinDescription[pin].ulPinType != PIO_NOT_A_PIN);
        const PinDescription *desc = &g_APinDescription[pin];

        _dtaGpio.bmsk = (uint32_t)(1UL << desc->ulPin);
        _dtaGpio.inReg = &PORT->Group[desc->ulPort].IN.reg;
        _dtaGpio.outSetReg = &PORT->Group[desc->ulPort].OUTSET.reg;
        _dtaGpio.outClrReg = &PORT->Group[desc->ulPort].OUTCLR.reg;
        _dtaGpio.modSetReg = &PORT->Group[desc->ulPort].DIRSET.reg;
        _dtaGpio.modClrReg = &PORT->Group[desc->ulPort].DIRCLR.reg;

        pinMode(pin,  (pullUp ? INPUT_PULLUP : INPUT));
        setupDtaGpio();
    }

#ifdef CONFIG_PWR_CTRL_ENABLED
    void initPwrCtrlGpio(unsigned pin)
    {
        assert(g_APinDescription[pin].ulPinType != PIO_NOT_A_PIN);
        const PinDescription *desc = &g_APinDescription[pin];

        _pwrCtrlGpio.bmsk = (uint32_t)(1UL << desc->ulPin);
        _pwrCtrlGpio.outSetReg = &PORT->Group[desc->ulPort].OUTSET.reg;
        _pwrCtrlGpio.outClrReg = &PORT->Group[desc->ulPort].OUTCLR.reg;
        _pwrCtrlGpio.modSetReg = &PORT->Group[desc->ulPort].DIRSET.reg;
        _pwrCtrlGpio.modClrReg = &PORT->Group[desc->ulPort].DIRCLR.reg;

        pinMode(pin, OUTPUT);
        setupPwrCtrlGpio(true);
    }

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

#undef __GPIO_AS_OUTPUT
#undef __GPIO_AS_INPUT
#undef __WRITE_GPIO
#undef __READ_GPIO

#endif /* __OWNG_ARDUINO_SAMD__ */
