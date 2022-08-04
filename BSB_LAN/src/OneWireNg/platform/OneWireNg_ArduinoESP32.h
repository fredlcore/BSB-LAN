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

#ifndef __OWNG_ARDUINO_ESP32__
#define __OWNG_ARDUINO_ESP32__

#include <assert.h>
#include "Arduino.h"
#include "../OneWireNg_BitBang.h"
#include "../platform/Platform_TimeCritical.h"

#ifndef GPIO_PIN_COUNT
# error "GPIO_PIN_COUNT not defined for this version of SDK"
#endif

#if (GPIO_PIN_COUNT <= 32)
# define REG_GPIO_IN_LO GPIO.in.val
# define REG_GPIO_OUT_SET_LO GPIO.out_w1ts.val
# define REG_GPIO_OUT_CLR_LO GPIO.out_w1tc.val
# define REG_GPIO_MOD_SET_LO GPIO.enable_w1ts.val
# define REG_GPIO_MOD_CLR_LO GPIO.enable_w1tc.val
#else
# define REG_GPIO_IN_LO GPIO.in
# define REG_GPIO_IN_HI GPIO.in1.val
# define REG_GPIO_OUT_SET_LO GPIO.out_w1ts
# define REG_GPIO_OUT_SET_HI GPIO.out1_w1ts.val
# define REG_GPIO_OUT_CLR_LO GPIO.out_w1tc
# define REG_GPIO_OUT_CLR_HI GPIO.out1_w1tc.val
# define REG_GPIO_MOD_SET_LO GPIO.enable_w1ts
# define REG_GPIO_MOD_SET_HI GPIO.enable1_w1ts.val
# define REG_GPIO_MOD_CLR_LO GPIO.enable_w1tc
# define REG_GPIO_MOD_CLR_HI GPIO.enable1_w1tc.val
#endif

#define __READ_GPIO(gs) \
    ((*gs.inReg & gs.bmsk) != 0)

#define __WRITE0_GPIO(gs) \
    *gs.outClrReg = gs.bmsk

#define __WRITE1_GPIO(gs) \
    *gs.outSetReg = gs.bmsk

#define __WRITE_GPIO(gs, st) \
    if (st) __WRITE1_GPIO(gs); \
    else __WRITE0_GPIO(gs)

#define __GPIO_AS_INPUT(gs) \
    *gs.modClrReg = gs.bmsk

#define __GPIO_AS_OUTPUT(gs) \
    *gs.modSetReg = gs.bmsk

/**
 * Arduino ESP32 platform GPIO specific implementation.
 */
class OneWireNg_ArduinoESP32: public OneWireNg_BitBang
{
public:
    /**
     * OneWireNg 1-wire service for Arduino ESP32 platform.
     *
     * Bus powering is supported via switching its GPIO to the high state.
     * In this case the GPIO servers as a voltage source for connected slaves
     * working in parasite powering configuration.
     *
     * @param pin Arduino GPIO pin number used for bit-banging 1-wire bus.
     * @param pullUp If @c true configure internal pull-up resistor for the bus.
     */
    OneWireNg_ArduinoESP32(unsigned pin, bool pullUp)
    {
        initDtaGpio(pin, pullUp);
    }

#ifdef CONFIG_PWR_CTRL_ENABLED
    /**
     * OneWireNg 1-wire service for Arduino ESP32 platform.
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
    OneWireNg_ArduinoESP32(unsigned pin, unsigned pwrCtrlPin, bool pullUp)
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

#ifdef CONFIG_OVERDRIVE_ENABLED
    TIME_CRITICAL int touch1Overdrive()
    {
        __WRITE0_GPIO(_dtaGpio);
        __GPIO_AS_OUTPUT(_dtaGpio);

        /* speed up low-to-high transition */
        __WRITE1_GPIO(_dtaGpio);
        __GPIO_AS_INPUT(_dtaGpio);

        return __READ_GPIO(_dtaGpio);
    }
#endif

    void initDtaGpio(unsigned pin, bool pullUp)
    {
        assert(GPIO_IS_VALID_GPIO(pin) && GPIO_IS_VALID_OUTPUT_GPIO(pin));

        if (pin < 32) {
            _dtaGpio.bmsk = (uint32_t)(1UL << pin);
            _dtaGpio.inReg = &REG_GPIO_IN_LO;
            _dtaGpio.outSetReg = &REG_GPIO_OUT_SET_LO;
            _dtaGpio.outClrReg = &REG_GPIO_OUT_CLR_LO;
            _dtaGpio.modSetReg = &REG_GPIO_MOD_SET_LO;
            _dtaGpio.modClrReg = &REG_GPIO_MOD_CLR_LO;
        }
#if (GPIO_PIN_COUNT > 32)
        else {
            _dtaGpio.bmsk = (uint32_t)(1UL << (pin-32));
            _dtaGpio.inReg = &REG_GPIO_IN_HI;
            _dtaGpio.outSetReg = &REG_GPIO_OUT_SET_HI;
            _dtaGpio.outClrReg = &REG_GPIO_OUT_CLR_HI;
            _dtaGpio.modSetReg = &REG_GPIO_MOD_SET_HI;
            _dtaGpio.modClrReg = &REG_GPIO_MOD_CLR_HI;
        }
#endif
        pinMode(pin, INPUT | (pullUp ? PULLUP : 0));
        setupDtaGpio();
    }

#ifdef CONFIG_PWR_CTRL_ENABLED
    void initPwrCtrlGpio(unsigned pin)
    {
        assert(GPIO_IS_VALID_GPIO(pin) && GPIO_IS_VALID_OUTPUT_GPIO(pin));

        if (pin < 32) {
            _pwrCtrlGpio.bmsk = (uint32_t)(1UL << pin);
            _pwrCtrlGpio.outSetReg = &REG_GPIO_OUT_SET_LO;
            _pwrCtrlGpio.outClrReg = &REG_GPIO_OUT_CLR_LO;
            _pwrCtrlGpio.modSetReg = &REG_GPIO_MOD_SET_LO;
            _pwrCtrlGpio.modClrReg = &REG_GPIO_MOD_CLR_LO;
        }
# if (GPIO_PIN_COUNT > 32)
        else {
            _pwrCtrlGpio.bmsk = (uint32_t)(1UL << (pin-32));
            _pwrCtrlGpio.outSetReg = &REG_GPIO_OUT_SET_HI;
            _pwrCtrlGpio.outClrReg = &REG_GPIO_OUT_CLR_HI;
            _pwrCtrlGpio.modSetReg = &REG_GPIO_MOD_SET_HI;
            _pwrCtrlGpio.modClrReg = &REG_GPIO_MOD_CLR_HI;
        }
# endif
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

#endif /* __OWNG_ARDUINO_ESP32__ */
