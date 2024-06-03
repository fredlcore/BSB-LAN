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

#ifndef __OWNG_ARDUINO_SAM__
#define __OWNG_ARDUINO_SAM__

#include <assert.h>
#include "Arduino.h"
#include "OneWireNg_BitBang.h"
#include "platform/Platform_TimeCritical.h"

/*
 * If configured - internal Arduino-SAM pin status in updated
 */
#ifndef ARDSAM_PIN_STATUS_UPDATE
# define ARDSAM_PIN_STATUS_UPDATE 0
#endif

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
 * Arduino SAM platform GPIO specific implementation.
 */
class OneWireNg_ArduinoSAM: public OneWireNg_BitBang
{
public:
    /**
     * OneWireNg 1-wire service for Arduino SAM platform.
     *
     * Bus powering is supported via switching its GPIO to the high state.
     * In this case the GPIO servers as a voltage source for connected slaves
     * working in parasite powering configuration.
     *
     * @param pin Arduino GPIO pin number used for bit-banging 1-wire bus.
     * @param pullUp If @c true configure internal pull-up resistor for the bus.
     */
    OneWireNg_ArduinoSAM(unsigned pin, bool pullUp)
    {
        initDtaGpio(pin, pullUp);
    }

#if CONFIG_PWR_CTRL_ENABLED
    /**
     * OneWireNg 1-wire service for Arduino SAM platform.
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
    OneWireNg_ArduinoSAM(unsigned pin, unsigned pwrCtrlPin, bool pullUp)
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
#if ARDSAM_PIN_STATUS_UPDATE
        *_dtaGpio.status = _dtaGpio.inputStatus;
#endif
        __GPIO_AS_INPUT(_dtaGpio);
    }

#if CONFIG_PWR_CTRL_ENABLED
    TIME_CRITICAL void writeGpioOut(int state, GpioType gpio)
    {
        if (gpio == GPIO_DTA) {
# if ARDSAM_PIN_STATUS_UPDATE
            *_dtaGpio.status = (state << 4) | PIN_STATUS_DIGITAL_OUTPUT;
# endif
            __WRITE_GPIO(_dtaGpio, state);
        } else {
# if ARDSAM_PIN_STATUS_UPDATE
            *_pwrCtrlGpio.status = (state << 4) | PIN_STATUS_DIGITAL_OUTPUT;
# endif
            __WRITE_GPIO(_pwrCtrlGpio, state);
        }
    }

    TIME_CRITICAL void setGpioAsOutput(int state, GpioType gpio)
    {
        if (gpio == GPIO_DTA) {
# if ARDSAM_PIN_STATUS_UPDATE
            *_dtaGpio.status = (state << 4) | PIN_STATUS_DIGITAL_OUTPUT;
# endif
            __WRITE_GPIO(_dtaGpio, state);
            __GPIO_AS_OUTPUT(_dtaGpio);
        } else {
# if ARDSAM_PIN_STATUS_UPDATE
            *_pwrCtrlGpio.status = (state << 4) | PIN_STATUS_DIGITAL_OUTPUT;
# endif
            __WRITE_GPIO(_pwrCtrlGpio, state);
            __GPIO_AS_OUTPUT(_pwrCtrlGpio);
        }
    }
#else
    TIME_CRITICAL void writeGpioOut(int state)
    {
# if ARDSAM_PIN_STATUS_UPDATE
        *_dtaGpio.status = (state << 4) | PIN_STATUS_DIGITAL_OUTPUT;
# endif
        __WRITE_GPIO(_dtaGpio, state);
    }

    TIME_CRITICAL void setGpioAsOutput(int state)
    {
# if ARDSAM_PIN_STATUS_UPDATE
        *_dtaGpio.status = (state << 4) | PIN_STATUS_DIGITAL_OUTPUT;
# endif
        __WRITE_GPIO(_dtaGpio, state);
        __GPIO_AS_OUTPUT(_dtaGpio);
    }
#endif /* CONFIG_PWR_CTRL_ENABLED */

#if CONFIG_OVERDRIVE_ENABLED
    TIME_CRITICAL int touch1Overdrive()
    {
# if ARDSAM_PIN_STATUS_UPDATE
        *_dtaGpio.status = PIN_STATUS_DIGITAL_OUTPUT;
# endif
        __WRITE_GPIO(_dtaGpio, 0);
        __GPIO_AS_OUTPUT(_dtaGpio);

        /* speed up low-to-high transition */
# if ARDSAM_PIN_STATUS_UPDATE
        *_dtaGpio.status = (1 << 4) | PIN_STATUS_DIGITAL_OUTPUT;
# endif
        __WRITE_GPIO(_dtaGpio, 1);
        __GPIO_AS_OUTPUT(_dtaGpio);

        return __READ_GPIO(_dtaGpio);
    }
#endif

    void initDtaGpio(unsigned pin, bool pullUp)
    {
        assert(g_APinDescription[pin].ulPinType != PIO_NOT_A_PIN);
        const PinDescription *desc = &g_APinDescription[pin];

#if ARDSAM_PIN_STATUS_UPDATE
        _dtaGpio.status = &g_pinStatus[pin];
        _dtaGpio.inputStatus =
            (pullUp ? PIN_STATUS_DIGITAL_INPUT_PULLUP : PIN_STATUS_DIGITAL_INPUT);
#endif
        _dtaGpio.bmsk = desc->ulPin;
        _dtaGpio.inReg = &desc->pPort->PIO_PDSR;
        _dtaGpio.outSetReg = &desc->pPort->PIO_SODR;
        _dtaGpio.outClrReg = &desc->pPort->PIO_CODR;
        _dtaGpio.modSetReg = &desc->pPort->PIO_OER;
        _dtaGpio.modClrReg = &desc->pPort->PIO_ODR;

        pinMode(pin,  (pullUp ? INPUT_PULLUP : INPUT));
        setupDtaGpio();
    }

#if CONFIG_PWR_CTRL_ENABLED
    void initPwrCtrlGpio(unsigned pin)
    {
        assert(g_APinDescription[pin].ulPinType != PIO_NOT_A_PIN);
        const PinDescription *desc = &g_APinDescription[pin];

# if ARDSAM_PIN_STATUS_UPDATE
        _pwrCtrlGpio.status = &g_pinStatus[pin];
# endif
        _pwrCtrlGpio.bmsk = desc->ulPin;
        _pwrCtrlGpio.outSetReg = &desc->pPort->PIO_SODR;
        _pwrCtrlGpio.outClrReg = &desc->pPort->PIO_CODR;
        _pwrCtrlGpio.modSetReg = &desc->pPort->PIO_OER;
        _pwrCtrlGpio.modClrReg = &desc->pPort->PIO_ODR;

        pinMode(pin, OUTPUT);
        setupPwrCtrlGpio(true);
    }

    struct {
# if ARDSAM_PIN_STATUS_UPDATE
        uint8_t *status;
# endif
        uint32_t bmsk;
        volatile uint32_t *outSetReg;
        volatile uint32_t *outClrReg;
        volatile uint32_t *modSetReg;
        volatile uint32_t *modClrReg;
    } _pwrCtrlGpio;
#endif /* CONFIG_PWR_CTRL_ENABLED */

    struct {
#if ARDSAM_PIN_STATUS_UPDATE
        uint8_t *status;
        uint8_t inputStatus;
#endif
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

#endif /* __OWNG_ARDUINO_SAM__ */
