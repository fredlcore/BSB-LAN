/*
 * Copyright (c) 2021,2022,2024 Piotr Stolarz
 * OneWireNg: Arduino 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */


#ifndef __OWNG_MAX31850__
#define __OWNG_MAX31850__

#include "drivers/DSTherm.h"

/**
 * Dallas MAX31850/MAX31851 thermocouples driver.
 */
class MAX31850: DSTherm
{
public:
    /**
     * Thermocouple scratchpad.
     */
    class Scratchpad: DSTherm::Scratchpad
    {
    public:
        using DSTherm::Scratchpad::LENGTH;

        /**
         * Get thermocouple temperature (1000 scaled).
         *
         * @return Temperature in Celsius degrees returned as fixed-point integer
         *     with multiplier 1000 , e.g. 20.125 C is returned as 20125.
         *
         * @note @ref getFaultStatus() shall be checked first to ensure
         *     correctness of the returned temperature.
         */
        long getTemp() const
        {
            long temp =
                (long)((unsigned long)(long)(int8_t)_scrpd[1] << 8) | _scrpd[0];
            temp = rsh(temp, 2); /* truncate unused bits */
            temp = div2(temp * 1000, 2);
            return temp;
        }

        /**
         * Get thermocouple temperature (16 scaled).
         *
         * @return Temperature in Celsius degrees returned as fixed-point integer
         *     with multiplier 16, e.g. 20.125 C is returned as 322.
         *
         * @note @ref getFaultStatus() shall be checked first to ensure
         *     correctness of the returned temperature.
         *
         * @see DSTherm::Scratchpad::getTemp2()
         */
        long getTemp2() const
        {
            long temp =
                (long)((unsigned long)(long)(int8_t)_scrpd[1] << 8) | _scrpd[0];
            temp &= ~3L; /* mask unused bits to zeroes, 16-scaled */
            return temp;
        }

        /**
         * Get thermocouple fault status.
         *
         * @return
         *     @c true: Fault detected.
         *     @c false: No fault.
         *
         * @note In case of failure @ref getInputState() routine should
         *     be used to detect state of the thermocouple input state.
         */
        bool getFaultStatus() const {
            return ((_scrpd[0] & 1) != 0);
        }

        /**
         * Get internal (cold-junction) temperature (1000 scaled).
         *
         * @return Temperature in Celsius degrees returned as fixed-point integer
         *     with multiplier 1000 , e.g. 20.125 C is returned as 20125.
         */
        long getTempInternal() const
        {
            long temp =
                (long)((unsigned long)(long)(int8_t)_scrpd[3] << 8) | _scrpd[2];
            temp = rsh(temp, 4); /* truncate unused bits */
            temp = div2(temp * 1000, 4);
            return temp;
        }

        /**
         * Get internal (cold-junction) temperature (16 scaled).
         *
         * @return Temperature in Celsius degrees returned as fixed-point integer
         *     with multiplier 16, e.g. 20.125 C is returned as 322.
         *
         * @see DSTherm::Scratchpad::getTemp2()
         */
        long getTempInternal2() const
        {
            long temp =
                (long)((unsigned long)(long)(int8_t)_scrpd[3] << 8) | _scrpd[2];
            temp = rsh(temp, 4); /* truncate unused bits */
            return temp;
        }

        /**
         * Get thermocouple input state.
         *
         * @return Normally the returned value should be 0.
         *     If the returned value is not 0 it constitutes bit-filed describing
         *     a problem with the thermocouple input circuit as follows:
         *     - @c INPUT_OC (bit 0): open circuit,
         *     - @c INPUT_SCG (bit 1): short to GND,
         *     - @c INPUT_SCV (bit 2): short to VDD.
         */
        uint8_t getInputState() const {
            return (_scrpd[2] & 7);
        }

        /**
         * Get sensor address (range: 0-15).
         *
         * @note MAX31850 addresses as set on the HW layer by AD0-AD3 pins.
         */
        using DSTherm::Scratchpad::getAddr;

        /**
         * Get sensor id the scratchpad belongs to.
         */
        using DSTherm::Scratchpad::getId;

        /**
         * Get scratchpad in a raw format as table of bytes.
         *
         * @see DSTherm::Scratchpad::getRaw()
         */
        using DSTherm::Scratchpad::getRaw;

        /*
         * Intentionally empty destructor - the same Scratchpad placeholder
         * may be used by subsequent sensor reads without explicit calls to
         * Scratchpad destructor.
         */
        // ~Scratchpad() {}

    protected:
        /**
         * Scratchpad intended to be created by @ref MAX31850::readScratchpad()
         * only.
         */
        Scratchpad(OneWireNg& ow, const OneWireNg::Id& id,
            const uint8_t scratchpad[LENGTH]):
            DSTherm::Scratchpad(ow, id, scratchpad) {}

    friend class MAX31850;
#ifdef OWNG_TEST
    friend class MAX31850_Test;
#endif
    };

    /**
     * MAX31850 driver constructor.
     *
     * @param ow 1-wire service.
     *
     * @note @c MAX31850 driver is a lightweight object which wraps over
     *     passed @c OneWireNg service to provide higher level API for
     *     handling supported devices. @c MAX31850 drivers may be freely
     *     used as automatic variables created and destroyed on the running
     *     stack without additional overhead.
     */
    MAX31850(OneWireNg& ow): DSTherm(ow) {}

    /**
     * Start temperature conversion for an addressed sensor.
     *
     * @note MAX31850 has constant 14-bits resolution for thermocouple
     *     temperature and 12-bits for internal cold-junction temperature.
     *     Max temperature conversion time is 100 msecs (denoted by
     *     @c MAX_CONV_TIME constant) with typical conversion time 72 msec.
     *
     * @see DSTherm::convertTemp()
     */
    OneWireNg::ErrorCode convertTemp(const OneWireNg::Id& id,
        int convTime = SCAN_BUS, bool parasitic = false)
    {
        return DSTherm::_convertTemp<MAX_CONV_TIME>(&id, convTime, parasitic);
    }

    /**
     * Start temperature conversion for all sensors on the bus.
     *
     * @see convertTemp()
     */
    OneWireNg::ErrorCode convertTempAll(
        int convTime = SCAN_BUS, bool parasitic = false)
    {
        return DSTherm::_convertTemp<MAX_CONV_TIME>(NULL, convTime, parasitic);
    }

    /**
     * Read sensor scratchpad.
     *
     * @see DSTherm::readScratchpad
     */
    OneWireNg::ErrorCode readScratchpad(
        const OneWireNg::Id& id, Scratchpad *scratchpad)
    {
        return DSTherm::readScratchpad(id, scratchpad);
    }

    /**
     * Read sensor scratchpad - single sensor mode.
     *
     * @see DSTherm::readScratchpadSingle
     */
    OneWireNg::ErrorCode readScratchpadSingle(
        Scratchpad *scratchpad, bool reuseId = true)
    {
        return DSTherm::readScratchpadSingle(scratchpad, reuseId);
    }

    /**
     * Check if specified sensor is parasitically powered.
     *
     * @see DSTherm::readPowerSupply
     */
    using DSTherm::readPowerSupply;

    /**
     * Check if any sensor on the bus is parasitically powered.
     *
     * @see DSTherm::readPowerSupplyAll
     */
    using DSTherm::readPowerSupplyAll;

    using DSTherm::SCAN_BUS;

    /** Function command set */
    using DSTherm::CMD_CONVERT_T;
    using DSTherm::CMD_READ_POW_SUPPLY;
    using DSTherm::CMD_READ_SCRATCHPAD;

    /** MAX31850/MAX31851 family code */
    const static uint8_t FAMILY_CODE = 0x3B;

    /** Max conversion time in milliseconds */
    const static int MAX_CONV_TIME = 100;

    /** Thermocouple inout state bit numbers */
    const static uint8_t INPUT_OC  = 1;
    const static uint8_t INPUT_SCG = 2;
    const static uint8_t INPUT_SCV = 4;
};

#endif /* __OWNG_MAX31850__ */
