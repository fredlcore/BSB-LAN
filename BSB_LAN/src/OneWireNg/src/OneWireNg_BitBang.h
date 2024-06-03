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

#ifndef __OWNG_BITBANG__
#define __OWNG_BITBANG__

#include "OneWireNg.h"

/**
 * GPIO bit-banged implementation of 1-wire bus activities: reset, touch,
 * parasite powering.
 *
 * The class relies on virtual functions provided by derivative class to
 * perform platform specific GPIO operations. The platform specific class
 * shall provide:
 * - @ref readDtaGpioIn(), @ref writeGpioOut(): read/write operations.
 * - @ref setDtaGpioAsInput(), @ref setGpioAsOutput(): set GPIO working mode.
 *
 * and optionally:
 * - @ref touch1Overdrive(): if overdrive mode is enabled and requires specific
 *       implementation.
 */
class OneWireNg_BitBang: public OneWireNg
{
public:
    ErrorCode reset();
    int touchBit(int bit, bool power);

    /**
     * Enable/disable direct voltage source provisioning on the 1-wire data bus.
     * Function always successes.
     */
    ErrorCode powerBus(bool on);

protected:
#if CONFIG_PWR_CTRL_ENABLED
    typedef enum
    {
        GPIO_DTA = 0,   /** 1-wire data GPIO */
        GPIO_CTRL_PWR   /** power-control-GPIO */
    } GpioType;
#endif

    /**
     * This class is intended to be inherited by specialized classes.
     */
    OneWireNg_BitBang()
    {
        _pwre = false;
#if CONFIG_PWR_CTRL_ENABLED
        _pwrp = false;
#endif
    }

#if CONFIG_PWR_CTRL_ENABLED
    /**
     * For open-drain type of platform data bus GPIO can't serve as a voltage
     * source for parasitically power connected slaves. This routine enables /
     * disables power-control-GPIO (working in the output mode) controlling
     * power switching transistor providing the voltage source to the bus.
     * The GPIO is set to the low state in case the power is enabled on the
     * bus and to the high state otherwise. The logic may be inverted by
     * @ref CONFIG_PWR_CTRL_REV_POLARITY configuration.
     */
    void setupPwrCtrlGpio(bool on)
    {
        if (on) {
# if CONFIG_PWR_CTRL_REV_POLARITY
            setGpioAsOutput(0, GPIO_CTRL_PWR);
# else
            setGpioAsOutput(1, GPIO_CTRL_PWR);
# endif
            _pwrp = true;
        } else {
            _pwrp = false;
        }
    }
#endif

    /**
     * Utility routine. Shall be called from inheriting class to initialize
     * data GPIO.
     */
    void setupDtaGpio() {
        setBus(1);
    }

    /**
     * Read 1-wire data GPIO and return its state (0: low, 1: high).
     */
    virtual int readDtaGpioIn() = 0;

    /**
     * Set 1-wire data GPIO in the input-mode.
     */
    virtual void setDtaGpioAsInput() = 0;

    /**
     * Write output-mode @c GPIO with a given @c state (0: low, 1: high).
     *
     * @note If the library is configured with @c CONFIG_PWR_CTRL_ENABLED then
     *     the routine's second argument is present and specifies a GPIO the
     *     routine is called for: data (@c GPIO_DTA) or power-control-GPIO
     *     (@c GPIO_CTRL_PWR). The latter case happens if and only if
     *     power-control-GPIO has been configured via @ref setupPwrCtrlGpio().
     */
#if CONFIG_PWR_CTRL_ENABLED
    virtual void writeGpioOut(int state, GpioType gpio) = 0;
#else
    virtual void writeGpioOut(int state) = 0;
#endif

    /**
     * Set @c GPIO in the output-mode with an initial @c state (0: low, 1: high).
     *
     * @note The function should guarantee no intermediate "blink" state between
     *     switching the GPIO into the output mode and setting the initial
     *     value on the pin. In case of problem with fulfilling such assumption
     *     there may be feasible to compile the library with @ref
     *     CONFIG_BUS_BLINK_PROTECTION, but such approach is burdened with its
     *     own drawback (see the configuration parameter description for more
     *     details).
     *
     * @note If the library is configured with @c CONFIG_PWR_CTRL_ENABLED then
     *     the routine's second argument is present and specifies a GPIO the
     *     routine is called for: data (@c GPIO_DTA) or power-control-GPIO
     *     (@c GPIO_CTRL_PWR). The latter case happens if and only if
     *     power-control-GPIO has been configured via @ref setupPwrCtrlGpio().
     */
#if CONFIG_PWR_CTRL_ENABLED
    virtual void setGpioAsOutput(int state, GpioType gpio) = 0;
#else
    virtual void setGpioAsOutput(int state) = 0;
#endif

#if CONFIG_OVERDRIVE_ENABLED
    /**
     * 1-wire touch-1 in overdrive mode is defined by 2-steps procedure:
     * 1. Set data bus low for 1 usec.
     * 2. Switch the bus into input and sample it at 2 usec max (measuring
     *    from setting the bus low in the previous step).
     *
     * The timings here are very strict and vulnerable for improper values.
     * In case the library is not able to properly bit-bang overdriven touch-1
     * via standard OneWireNg_BitBang's GPIO interface (read/write/set mode)
     * due to insufficient platform's CPU frequency causing too long timings,
     * the platform's GPIO implementation may override this method to directly
     * implement the touch-1 activity.
     *
     * @note The routine is called inside time critical section.
     *
     * @note Implementation shall respect @ref CONFIG_BUS_BLINK_PROTECTION
     *     configuration if the platform doesn't guarantee input to output GPIO
     *     switch with a desired initial state.
     */
    virtual int touch1Overdrive();
#endif

    /**
     * Set 1-wire data bus state: high (1) or low (0).
     */
    void setBus(int state)
    {
        if (state) {
#if CONFIG_BUS_BLINK_PROTECTION
            writeDtaGpioOut(1);
#endif
            setDtaGpioAsInput();
        } else {
            setDtaGpioAsOutput(0);
        }
    }

    bool _pwre; /** bus is powered indicator */
#if CONFIG_PWR_CTRL_ENABLED
    bool _pwrp; /** power-control-GPIO pin is valid */
#endif

private:
#if CONFIG_PWR_CTRL_ENABLED
    void writeDtaGpioOut(int state) { writeGpioOut(state, GPIO_DTA); }
    void setDtaGpioAsOutput(int state) { setGpioAsOutput(state, GPIO_DTA); }
#else
    void writeDtaGpioOut(int state) { writeGpioOut(state); }
    void setDtaGpioAsOutput(int state) { setGpioAsOutput(state); }
#endif

#ifdef OWNG_TEST
friend class OneWireNg_BitBang_Test;
#endif
};

#endif /* __OWNG_BITBANG__ */
