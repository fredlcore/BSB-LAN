/*
 * Copyright (c) 2021,2022 Piotr Stolarz
 * OneWireNg: Arduino 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

#ifndef __OWNG_ARDUINO_MBED_HAL__
#define __OWNG_ARDUINO_MBED_HAL__

#ifdef ARDUINO
# include "Arduino.h"
#else
# include "PinNames.h"
# define INPUT          PullNone
# define INPUT_PULLUP   PullUp
#endif

#include <assert.h>
#include "hal/gpio_api.h"
#include "OneWireNg_BitBang.h"
#include "platform/Platform_TimeCritical.h"

/**
 * Arduino Mbed OS based platform GPIO specific implementation via HAL API.
 */
class OneWireNg_ArduinoMbedHAL: public OneWireNg_BitBang
{
public:
    /**
     * OneWireNg 1-wire service for Arduino Mbed OS based platform.
     *
     * Bus powering is supported via switching its GPIO to the high state.
     * In this case the GPIO servers as a voltage source for connected slaves
     * working in parasite powering configuration.
     *
     * @param pin Arduino GPIO pin number used for bit-banging 1-wire bus.
     * @param pullUp If @c true configure internal pull-up resistor for the bus.
     */
    OneWireNg_ArduinoMbedHAL(unsigned pin, bool pullUp)
    {
        initDtaGpio(pin, pullUp);
    }

#if CONFIG_PWR_CTRL_ENABLED
    /**
     * OneWireNg 1-wire service for Arduino Mbed OS based platform.
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
    OneWireNg_ArduinoMbedHAL(unsigned pin, unsigned pwrCtrlPin, bool pullUp)
    {
        initDtaGpio(pin, pullUp);
        initPwrCtrlGpio(pwrCtrlPin);
    }
#endif

protected:
    TIME_CRITICAL int readDtaGpioIn()
    {
        return (gpio_read(&_dtaGpio) != 0);
    }

    TIME_CRITICAL void setDtaGpioAsInput()
    {
        gpio_dir(&_dtaGpio, PIN_INPUT);
    }

#if CONFIG_PWR_CTRL_ENABLED
    TIME_CRITICAL void writeGpioOut(int state, GpioType gpio)
    {
        if (gpio == GPIO_DTA) {
            gpio_write(&_dtaGpio, state);
        } else {
            gpio_write(&_pwrCtrlGpio, state);
        }
    }

    TIME_CRITICAL void setGpioAsOutput(int state, GpioType gpio)
    {
        if (gpio == GPIO_DTA) {
            gpio_write(&_dtaGpio, state);
            gpio_dir(&_dtaGpio, PIN_OUTPUT);
        } else {
            gpio_write(&_pwrCtrlGpio, state);
            gpio_dir(&_pwrCtrlGpio, PIN_OUTPUT);
        }
    }
#else
    TIME_CRITICAL void writeGpioOut(int state)
    {
        gpio_write(&_dtaGpio, state);
    }

    TIME_CRITICAL void setGpioAsOutput(int state)
    {
        gpio_write(&_dtaGpio, state);
        gpio_dir(&_dtaGpio, PIN_OUTPUT);
    }
#endif /* CONFIG_PWR_CTRL_ENABLED */

#if CONFIG_OVERDRIVE_ENABLED
    TIME_CRITICAL int touch1Overdrive()
    {
        gpio_write(&_dtaGpio, 0);
        gpio_dir(&_dtaGpio, PIN_OUTPUT);

        /* speed up low-to-high transition */
        gpio_write(&_dtaGpio, 1);
        gpio_dir(&_dtaGpio, PIN_INPUT);

        return (gpio_read(&_dtaGpio) != 0);
    }
#endif

    void initDtaGpio(unsigned pin, bool pullUp)
    {
#ifdef ARDUINO
        PinName pinName = digitalPinToPinName(pin);
        assert((int)pin != NC);
#else
        PinName pinName = (PinName)pin;
#endif
        gpio_init_in_ex(&_dtaGpio, pinName, (pullUp ? INPUT_PULLUP : INPUT));
        setupDtaGpio();
    }

#if CONFIG_PWR_CTRL_ENABLED
    void initPwrCtrlGpio(unsigned pin)
    {
#ifdef ARDUINO
        PinName pinName = digitalPinToPinName(pin);
        assert((int)pin != NC);
#else
        PinName pinName = (PinName)pin;
#endif
        gpio_init_out(&_pwrCtrlGpio, pinName);
        setupPwrCtrlGpio(true);
    }

    gpio_t _pwrCtrlGpio;
#endif

    gpio_t _dtaGpio;
};

#endif /* __OWNG_ARDUINO_MBED_HAL__ */
