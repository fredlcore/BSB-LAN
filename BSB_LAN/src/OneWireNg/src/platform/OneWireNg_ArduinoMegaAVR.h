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

#ifndef __OWNG_ARDUINO_MEGAAVR__
#define __OWNG_ARDUINO_MEGAAVR__

#include <assert.h>
#include "Arduino.h"
#include "OneWireNg_BitBang.h"
#include "platform/Platform_TimeCritical.h"

#define __READ_GPIO(gs) \
    ((gs.port->IN & gs.bmsk) != 0)

#define __WRITE_GPIO(gs, st) \
    if (st) gs.port->OUTSET = gs.bmsk; \
    else gs.port->OUTCLR = gs.bmsk

#define __GPIO_AS_INPUT(gs) \
    gs.port->DIRCLR = gs.bmsk

#define __GPIO_AS_OUTPUT(gs) \
    gs.port->DIRSET = gs.bmsk

/**
 * Arduino megaAVR platform GPIO specific implementation
 * (this is recent Microchip architecture: ATmega4809, 4808, 3209, 3208).
 */
class OneWireNg_ArduinoMegaAVR: public OneWireNg_BitBang
{
public:
    /**
     * OneWireNg 1-wire service for Arduino megaAVR platform.
     *
     * Bus powering is supported via switching its GPIO to the high state.
     * In this case the GPIO servers as a voltage source for connected slaves
     * working in parasite powering configuration.
     *
     * @param pin Arduino GPIO pin number used for bit-banging 1-wire bus.
     * @param pullUp If @c true configure internal pull-up resistor for the bus.
     */
    OneWireNg_ArduinoMegaAVR(unsigned pin, bool pullUp)
    {
        initDtaGpio(pin, pullUp);
    }

#if CONFIG_PWR_CTRL_ENABLED
    /**
     * OneWireNg 1-wire service for Arduino megaAVR platform.
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
    OneWireNg_ArduinoMegaAVR(unsigned pin, unsigned pwrCtrlPin, bool pullUp)
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

#if CONFIG_OVERDRIVE_ENABLED
    TIME_CRITICAL int touch1Overdrive()
    {
        __WRITE_GPIO(_dtaGpio, 0);
        __GPIO_AS_OUTPUT(_dtaGpio);

        /* speed up low-to-high transition */
        __WRITE_GPIO(_dtaGpio, 1);
        __GPIO_AS_INPUT(_dtaGpio);

        return __READ_GPIO(_dtaGpio);
    }
#endif

    void initDtaGpio(unsigned pin, bool pullUp)
    {
        _dtaGpio.bmsk = digitalPinToBitMask(pin);
        _dtaGpio.port = digitalPinToPortStruct(pin);
        volatile uint8_t *ctrlReg = getPINnCTRLregister(_dtaGpio.port,
            digitalPinToBitPosition(pin));

        assert(_dtaGpio.port != NULL && ctrlReg != NULL);

        __GPIO_AS_INPUT(_dtaGpio);

        /* non-inverting mode */
        *ctrlReg &= ~(PORT_INVEN_bm);

        if (pullUp) {
            *ctrlReg |= PORT_PULLUPEN_bm;
        } else {
            *ctrlReg &= ~(PORT_PULLUPEN_bm);
        }

        setupDtaGpio();
    }

#if CONFIG_PWR_CTRL_ENABLED
    void initPwrCtrlGpio(unsigned pin)
    {
        _pwrCtrlGpio.bmsk = digitalPinToBitMask(pin);
        _pwrCtrlGpio.port = digitalPinToPortStruct(pin);
        volatile uint8_t *ctrlReg = getPINnCTRLregister(_pwrCtrlGpio.port,
            digitalPinToBitPosition(pin));

        assert(_pwrCtrlGpio.port != NULL && ctrlReg != NULL);

        /* non-inverting mode */
        *ctrlReg &= ~(PORT_INVEN_bm);

        setupPwrCtrlGpio(true);
    }

    struct {
        uint8_t bmsk;
        volatile PORT_t *port;
    } _pwrCtrlGpio;
#endif

    struct {
        uint8_t bmsk;
        volatile PORT_t *port;
    } _dtaGpio;
};

#undef __GPIO_AS_OUTPUT
#undef __GPIO_AS_INPUT
#undef __WRITE_GPIO
#undef __READ_GPIO

#endif /* __OWNG_ARDUINO_MEGAAVR__ */
