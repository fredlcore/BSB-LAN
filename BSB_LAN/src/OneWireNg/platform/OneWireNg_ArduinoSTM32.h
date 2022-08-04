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

#ifndef __OWNG_ARDUINO_STM32__
#define __OWNG_ARDUINO_STM32__

#include <assert.h>
#include "Arduino.h"
#include "../OneWireNg_BitBang.h"
#include "../platform/Platform_TimeCritical.h"

/**
 * Arduino STM32 platform GPIO specific implementation.
 */
class OneWireNg_ArduinoSTM32: public OneWireNg_BitBang
{
public:
    /**
     * OneWireNg 1-wire service for Arduino STM32 platform.
     *
     * Bus powering is supported via switching its GPIO to the high state.
     * In this case the GPIO servers as a voltage source for connected slaves
     * working in parasite powering configuration.
     *
     * @param pin Arduino GPIO pin number used for bit-banging 1-wire bus.
     * @param pullUp If @c true configure internal pull-up resistor for the bus.
     */
    OneWireNg_ArduinoSTM32(unsigned pin, bool pullUp)
    {
        initDtaGpio(pin, pullUp);
    }

#ifdef CONFIG_PWR_CTRL_ENABLED
    /**
     * OneWireNg 1-wire service for Arduino STM32 platform.
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
    OneWireNg_ArduinoSTM32(unsigned pin, unsigned pwrCtrlPin, bool pullUp)
    {
        initDtaGpio(pin, pullUp);
        initPwrCtrlGpio(pwrCtrlPin);
    }
#endif

protected:
    TIME_CRITICAL int readDtaGpioIn()
    {
        return (digitalReadFast(_dtaGpio.pinName) == LOW ? 0 : 1);
    }

    TIME_CRITICAL void setDtaGpioAsInput()
    {
        LL_GPIO_SetPinMode(
            _dtaGpio.gpio, _dtaGpio.ll_pin, LL_GPIO_MODE_INPUT);
    }

#ifdef CONFIG_PWR_CTRL_ENABLED
    TIME_CRITICAL void writeGpioOut(int state, GpioType gpio)
    {
        if (gpio == GPIO_DTA) {
            digitalWriteFast(_dtaGpio.pinName, state);
        } else {
            digitalWriteFast(_pwrCtrlGpio.pinName, state);
        }
    }

    TIME_CRITICAL void setGpioAsOutput(int state, GpioType gpio)
    {
        if (gpio == GPIO_DTA) {
            digitalWriteFast(_dtaGpio.pinName, state);
            LL_GPIO_SetPinMode(
                _dtaGpio.gpio, _dtaGpio.ll_pin, LL_GPIO_MODE_OUTPUT);
        } else {
            digitalWriteFast(_pwrCtrlGpio.pinName, state);
            LL_GPIO_SetPinMode(
                _pwrCtrlGpio.gpio, _pwrCtrlGpio.ll_pin, LL_GPIO_MODE_OUTPUT);
        }
    }
#else
    TIME_CRITICAL void writeGpioOut(int state)
    {
        digitalWriteFast(_dtaGpio.pinName, state);
    }

    TIME_CRITICAL void setGpioAsOutput(int state)
    {
        digitalWriteFast(_dtaGpio.pinName, state);
        LL_GPIO_SetPinMode(
            _dtaGpio.gpio, _dtaGpio.ll_pin, LL_GPIO_MODE_OUTPUT);
    }
#endif /* CONFIG_PWR_CTRL_ENABLED */

    void initDtaGpio(unsigned pin, bool pullUp)
    {
        _dtaGpio.pinName = digitalPinToPinName(pin);
        assert(_dtaGpio.pinName != NC);

        _dtaGpio.gpio = GPIOPort[STM_PORT(_dtaGpio.pinName)];
        _dtaGpio.ll_pin = STM_LL_GPIO_PIN(_dtaGpio.pinName);

        pinMode(pin, (pullUp ? INPUT_PULLUP : INPUT));
        setupDtaGpio();
    }

#ifdef CONFIG_PWR_CTRL_ENABLED
    void initPwrCtrlGpio(unsigned pin)
    {
        _pwrCtrlGpio.pinName = digitalPinToPinName(pin);
        assert(_pwrCtrlGpio.pinName != NC);

        _pwrCtrlGpio.gpio = GPIOPort[STM_PORT(_pwrCtrlGpio.pinName)];
        _pwrCtrlGpio.ll_pin = STM_LL_GPIO_PIN(_pwrCtrlGpio.pinName);

        pinMode(pin, OUTPUT);
        setupPwrCtrlGpio(true);
    }

    struct {
        PinName pinName;
        GPIO_TypeDef *gpio;
        uint32_t ll_pin;
    } _pwrCtrlGpio;
#endif

    struct {
        PinName pinName;
        GPIO_TypeDef *gpio;
        uint32_t ll_pin;
    } _dtaGpio;
};

#endif /* __OWNG_ARDUINO_STM32__ */
