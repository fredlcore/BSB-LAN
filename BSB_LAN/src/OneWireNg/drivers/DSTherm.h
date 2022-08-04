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

#ifndef __OWNG_DSTHERM__
#define __OWNG_DSTHERM__

#include <string.h>  /* memcpy */
#include "../OneWireNg.h"

/**
 * Dallas thermometers driver.
 *
 * The following sensors are supported: DS18B20, DS18S20, DS1822, DS1825,
 * DS28EA00.
 */
class DSTherm
{
public:
    enum Resolution {
        RES_9_BIT = 0,
        RES_10_BIT,
        RES_11_BIT,
        RES_12_BIT
    };

    /**
     * Sensor scratchpad.
     *
     * Object of this class is a placeholder for the raw scratchpad bytes read
     * from a sensor. Various class methods allow to access data contained
     * within. The scratchpad is associated with sensor id it has been read from.
     */
    class Scratchpad
    {
    public:
        static const size_t LENGTH = 9;

        /**
         * Get temperature.
         *
         * @return Temperature in Celsius degrees returned as fixed-point integer
         *     with multiplier 1000 , e.g. 20.125 C is returned as 20125.
         */
        long getTemp() const;

        /**
         * Get Th.
         * This is singed 1-byte integer (no fractional part) representing high
         * alarm trigger.
         *
         * @note This parameter is a part of thermometer configuration.
         */
        int8_t getTh() const {
            return (int8_t)_scrpd[2];
        }

        /**
         * Get Tl.
         * This is singed 1-byte integer (no fractional part) representing low
         * alarm trigger.
         *
         * @note This parameter is a part of thermometer configuration.
         */
        int8_t getTl() const {
            return (int8_t)_scrpd[3];
        }

        /**
         * Set Th and Tl alarm triggers.
         *
         * @param th High alarm trigger (signed 1-byte integer; no fractional
         *     part).
         * @param tl Low alarm trigger (signed 1-byte integer; no fractional
         *     part).
         *
         * @note The configuration is not sent to the sensor until
         *     @ref writeScratchpad() call.
         * @note If alarm functionality is not used Th and Tl bytes may contain
         *     user specific data.
         */
        void setThl(int8_t th, int8_t tl)
        {
            _scrpd[2] = (uint8_t)th;
            _scrpd[3] = (uint8_t)tl;
            _scrpd[LENGTH - 1] = OneWireNg::crc8(_scrpd, LENGTH - 1);
        }

        /**
         * Get temperature measurement resolution.
         * DS18S20 doesn't support resolution configuration (the method
         * returns RES_9_BIT for this type of sensors).
         *
         * @note This parameter is a part of thermometer configuration.
         */
        Resolution getResolution() const {
            if (_id[0] != DS18S20)
                return (Resolution)(RES_9_BIT + ((_scrpd[4] >> 5) & 3));
            else
                return RES_9_BIT;
        }

        /**
         * Set temperature measurement resolution.
         *
         * @param res Resolution to set.
         *
         * @note The configuration is not sent to the sensor until
         *     @ref writeScratchpad() call.
         * @note Don't use for DS18S20, which doesn't supports resolution
         *     configuration.
         */
        void setResolution(Resolution res)
        {
            if (_id[0] != DS18S20) {
                _scrpd[4] &= 0x9f;
                _scrpd[4] |= (uint8_t)(((res - RES_9_BIT) & 3) << 5);
                _scrpd[LENGTH - 1] = OneWireNg::crc8(_scrpd, LENGTH - 1);
            }
        }

        /**
         * Get sensor address (range: 0-15).
         *
         * @note This parameter is a part of thermometer configuration.
         * @note DS1825 only, for other sensors 15 is returned.
         */
        uint8_t getAddr() const {
            return (_scrpd[4] & 0x0f);
        }

        /**
         * Set sensor address; DS1825 sensors only.
         *
         * @param addr Address to set (range: 0-15).
         *
         * @note The configuration is not sent to the sensor until
         *     @ref writeScratchpad() call.
         */
        void setAddr(uint8_t addr)
        {
            if (_id[0] == DS1825) {
                _scrpd[4] &= 0xf0;
                _scrpd[4] |= addr & 0x0f;
                _scrpd[LENGTH - 1] = OneWireNg::crc8(_scrpd, LENGTH - 1);
            }
        }

        /**
         * Get sensor id the scratchpad belongs to.
         */
        const OneWireNg::Id& getId() const {
            return _id;
        }

        /**
         * Get scratchpad in a raw format as table of bytes.
         * Table's length is always 9 bytes long (denoted by @ref LENGTH
         * constant).
         */
        const uint8_t *getRaw() const {
            return _scrpd;
        }

        /**
         * Write configuration part of the scratchpad into the sensor owning
         * the scratchpad. This method allows to set only specific set of
         * thermometer configuration (by using appropriate setters) and remaining
         * the rest untouched.
         *
         * @note For DS18S20 Th and Tl (2 bytes) are the only sent. For
         *     remaining types of sensors Configuration Register is sent as
         *     the 3rd byte (containing resolution + DS1825 address).
         *
         * @return Error codes:
         *     - @c EC_SUCCESS: Operation finished with success.
         *     - @c EC_NO_DEVS: No devices on the bus.
         */
        OneWireNg::ErrorCode writeScratchpad() const;

        /*
         * Intentionally empty destructor - the same Scratchpad placeholder
         * may be used by subsequent sensor reads without explicit calls to
         * Scratchpad destructor.
         */
        // ~Scratchpad() {}

    protected:
        /**
         * Scratchpad intended to be created by @ref DSTherm::readScratchpad()
         * only.
         */
        Scratchpad(OneWireNg& ow, const OneWireNg::Id& id,
            const uint8_t scratchpad[LENGTH]):
            _ow(ow)
        {
            memcpy(_id, id, sizeof(id));
            memcpy(_scrpd, scratchpad, LENGTH);
        }

        OneWireNg& _ow;
        OneWireNg::Id _id;
        uint8_t _scrpd[LENGTH];

    friend class DSTherm;
#ifdef __TEST__
    friend class DSTherm_Test;
#endif
    };

    /**
     * DSTherm driver constructor.
     *
     * @param ow 1-wire service.
     *
     * @note @c DSTherm driver is a lightweight object which wraps over
     *     passed @c OneWireNg service to provide higher level API for
     *     handling supported devices. @c DSTherm drivers may be freely
     *     used as automatic variables created and destroyed on the running
     *     stack without additional overhead.
     */
    DSTherm(OneWireNg& ow): _ow(ow) {}

    /**
     * Start temperature conversion for an addressed sensor.
     * Optionally wait appropriate amount of time needed to perform the
     * conversion for the connected slave. If @c parasitic is @c true the bus
     * is powered during the conversion time.
     *
     * After calling this routine @ref readScratchpad() may be used to get
     * measured temperature from the sensor scratchpad.
     *
     * @param id Sensor id for temperature conversion.
     * @param convTime Conversion time. The parameter has 3 variants:
     * - @c convTime > 0: It specifies amount of time (in milliseconds) the
     *   routine waits for conversion completion. The time depends on configured
     *   sensor resolution (9 - 12 bits): lesser resolution, shorter conversion
     *   time. If the resolution is not known it's advisable to use max
     *   conversion time equal to 750 msecs (denoted by @ref MAX_CONV_TIME
     *   constant). Otherwise @ref getConversionTime() may be used to retrieve
     *   conversion time for a given resolution.
     *   For DS18S20 only @c MAX_CONV_TIME is allowed for this variant.
     * - @c convTime == 0: The routine doesn't wait for conversion and returns
     *   immediately after sending conversion command to the sensor (optionally
     *   powering the bus if @c parasitic argument is @c true). It's up to
     *   a caller to scan the bus for conversion completion or wait specific
     *   amount of time for it. For parasitic powering, a caller doesn't need
     *   to de-power the bus explicitly by @ref OneWireNg::powerBus(), since
     *   1-wire service will do it automatically on the next bus activity.
     * - @c convTime < 0 (use @ref SCAN_BUS constant for this case):
     *   If @c parasitic is @c false (sensor is not parasitically powered)
     *   the routine scans 1-wire bus for conversion completion and returns if
     *   completed, otherwise waits @c MAX_CONV_TIME and returns.
     * @param parasitic If @c true 1-wire bus is powered during the conversion
     *     time.
     *
     * @return Error codes:
     *     - @c EC_SUCCESS: Operation finished with success.
     *     - @c EC_NO_DEVS: No devices on the bus.
     */
    OneWireNg::ErrorCode convertTemp(const OneWireNg::Id& id,
        int convTime = SCAN_BUS, bool parasitic = false)
    {
        return _convertTemp<MAX_CONV_TIME>(&id, convTime, parasitic);
    }

    /**
     * Start temperature conversion for all sensors on the bus.
     *
     * @see convertTemp()
     */
    OneWireNg::ErrorCode convertTempAll(
        int convTime = SCAN_BUS, bool parasitic = false)
    {
        return _convertTemp<MAX_CONV_TIME>(NULL, convTime, parasitic);
    }

    /**
     * Read sensor scratchpad.
     *
     * @param id Sensor id the scratchpad shall be read from.
     * @param scratchpad Points to memory region where DSTherm_Test::Scratchpad
     *    object representing read scratchpad will be created in-place:
     *
     * @code
     * #include "platform/Platform_New.h"
     *
     * ALLOC_ALIGNED uint8_t scrpd_buf[sizeof(DSTherm::Scratchpad)];
     * DSTherm::Scratchpad *scrpd =
     *     reinterpret_cast<DSTherm::Scratchpad*>(&scrpd_buf[0]);
     *
     * // dsth: DSTherm driver object
     * // id: sensor id
     * dsth.readScratchpad(id, scrpd);
     * @endcode
     *
     * or use @ref Placeholder template to store Scratchpad object:
     *
     * @code
     * // create placeholder
     * Placeholder<DSTherm::Scratchpad> _scrpd;
     *
     * // fill the placeholder with the read scratchpad
     * dsth.readScratchpad(id, &_scrpd);
     *
     * // access Scratchpad object via reference or pointer
     * DSTherm::Scratchpad& scrpd_ref = _scrpd;
     * DSTherm::Scratchpad *scrpd_ptr = &_scrpd;
     * @endcode
     *
     * The same Scratchpad placeholder may be used by subsequent sensor reads:
     *
     * @code
     * Placeholder<DSTherm::Scratchpad> _scrpd;
     * dsth.readScratchpad(id1, &_scrpd);
     * // ...
     * dsth.readScratchpad(id2, &_scrpd);
     * // ...
     * dsth.readScratchpad(id3, &_scrpd);
     * // ...
     * @endcode
     *
     * @return Error codes:
     *     - @c EC_SUCCESS Scratchpad successfully read and available under
     *         @c scratchpad address.
     *     - @c EC_NO_DEVS: No devices on the bus.
     *     - @c EC_CRC_ERROR: Scratchpad read with CRC error.
     */
    OneWireNg::ErrorCode readScratchpad(
        const OneWireNg::Id& id, Scratchpad *scratchpad);

    /**
     * Write whole thermometer configuration to a given sensor.
     * @see Scratchpad::writeScratchpad() to set only specific configuration
     * parameters.
     *
     * @param id Sensor id the configuration shall be set to.
     * @param th Low alarm trigger.
     * @param tl High alarm trigger.
     * @param res Temperature measurement resolution. For DS18S20 this
     *     parameter must be set to its default value.
     * @param addr DS1825 address (range: 0-15). For other types of sensors
     *     this parameter must be set to its default value.
     *
     * @return Error codes:
     *     - @c EC_SUCCESS: Operation finished with success.
     *     - @c EC_NO_DEVS: No devices on the bus.
     */
    OneWireNg::ErrorCode writeScratchpad(const OneWireNg::Id& id,
        int8_t th, int8_t tl, uint8_t res = RES_12_BIT, uint8_t addr = 15)
    {
        return _writeScratchpad(&id, th, tl, res, addr);
    }

    /**
     * Similar to @ref DSTherm::writeScratchpad() but all sensors on the bus
     * are addressed.
     */
    OneWireNg::ErrorCode writeScratchpadAll(
        int8_t th, int8_t tl, uint8_t res = RES_12_BIT, uint8_t addr = 15)
    {
        return _writeScratchpad(NULL, th, tl, res, addr);
    }

    /**
     * Copy sensor scratchpad into EEPROM.
     * Optionally wait appropriate amount of time needed to perform the
     * copy for the connected slave. If @c parasitic is @c true the bus is
     * powered during the copy time.
     *
     * @param id Sensor id the operation is performed on.
     * @param parasitic If @c true 1-wire bus is powered during the copy time.
     * @param copyTime Copy time. The parameter has 2 variants:
     * - @c copyTime > 0: It specifies amount of time (in milliseconds) the
     *   routine waits for copy completion. Default value is 10 ms (denoted by
     *   @ref COPY_SCRATCHPAD_TIME) which is a minimal time specified by Dallas
     *   data sheets.
     * - @c copyTime <= 0: The routine doesn't wait for copy completion and
     *   returns immediately after sending copy command to the sensor
     *   (optionally powering the bus if @c parasitic argument is @c true).
     *   It's up to a caller to wait for operation completion (note, a sensor
     *   doesn't provide copy completion signals on the bus for this command).
     *   For parasitic powering, a caller doesn't need to de-power the bus
     *   explicitly by @ref OneWireNg::powerBus(), since 1-wire service will
     *   do it automatically on the next bus activity.
     *
     * @return Error codes:
     *     - @c EC_SUCCESS: Operation finished with success.
     *     - @c EC_NO_DEVS: No devices on the bus.
     */
    OneWireNg::ErrorCode copyScratchpad(const OneWireNg::Id& id,
        bool parasitic = false, int copyTime = COPY_SCRATCHPAD_TIME)
    {
        return _copyScratchpad(&id, parasitic, copyTime);
    }

    /**
     * Similar to @ref copyScratchpad() but all sensors on the bus are addressed.
     */
    OneWireNg::ErrorCode copyScratchpadAll(
        bool parasitic = false, int copyTime = COPY_SCRATCHPAD_TIME)
    {
        return _copyScratchpad(NULL, parasitic, copyTime);
    }

    /**
     * For specific sensor recall thermometer configuration from EEPROM
     * and place it in the scratchpad.
     *
     * After finishing with success a caller may track completion status on
     * the sensor by performing reads on the bus - 0: in progress, 1: finished.
     *
     * @return Error codes:
     *     - @c EC_SUCCESS: Operation finished with success.
     *     - @c EC_NO_DEVS: No devices on the bus.
     *
     * @note Thermometer performs the recall EEPROM operation automatically on
     *     its startup.
     */
    OneWireNg::ErrorCode recallEeprom(const OneWireNg::Id& id) {
        return _recallEeprom(&id);
    }

    /**
     * Similar to @ref recallEeprom() but all sensors on the bus are addressed.
     */
    OneWireNg::ErrorCode recallEepromAll() {
        return _recallEeprom(NULL);
    }

    /**
     * Check if specified sensor is parasitically powered.
     *
     * @return 0: sensor is parasitically powered, 1: otherwise.
     * @note For no sensors on the bus the routine returns 1.
     */
    int readPowerSupply(const OneWireNg::Id& id) {
        return _readPowerSupply(&id);
    }

    /**
     * Check if any sensor on the bus is parasitically powered.
     *
     * @return 0: some sensor is parasitically powered, 1: otherwise.
     * @note For no sensors on the bus the routine returns 1.
     */
    int readPowerSupplyAll() {
        return _readPowerSupply(NULL);
    }

#if (CONFIG_MAX_SRCH_FILTERS > 0)
    /**
     * Add supported thermometers family codes into 1-wire service search filter.
     *
     * @return Error codes:
     *     - @c EC_SUCCESS: Codes successfully added to the filters set.
     *     - @c EC_FULL: No more place in filters table to add the codes.
     *         Search filters configuration is untouched in this case.
     */
    OneWireNg::ErrorCode filterSupportedSlaves();
#endif

    /**
     * Get family name of given slave id.
     *
     * @param id Dallas thermometer salve id.
     *
     * @return Family name or @c NULL in case the id doesn't represent Dallas
     *     thermometer or it is not supported.
     */
    static const char *getFamilyName(const OneWireNg::Id& id);

    /**
     * Get conversion time (in milliseconds) for given measurement resolution.
     */
    static int getConversionTime(Resolution res)
    {
        int ret = MAX_CONV_TIME;
        int sh = (3 - (res - RES_9_BIT)) & 3;
        if (((ret >>= sh) << sh) < MAX_CONV_TIME) ret++;
        return ret;
    }

    /** Max conversion time (12 bits resolution) in milliseconds */
    const static int MAX_CONV_TIME = 750;

    /** Scan bus for operation completion. */
    const static int SCAN_BUS = -1;

    /**
     * Time needed to copy thermometer configuration parameters from
     * scratchpad to EEPROM (in milliseconds).
     */
    const static int COPY_SCRATCHPAD_TIME = 10;

    /** Function command set */
    const static uint8_t CMD_CONVERT_T        = 0x44;
    const static uint8_t CMD_COPY_SCRATCHPAD  = 0x48;
    const static uint8_t CMD_WRITE_SCRATCHPAD = 0x4E;
    const static uint8_t CMD_RECALL_E2        = 0xB8;
    const static uint8_t CMD_READ_POW_SUPPLY  = 0xB4;
    const static uint8_t CMD_READ_SCRATCHPAD  = 0xBE;

    /** Supported thermometers families */
    const static uint8_t DS18S20  = 0x10;
    const static uint8_t DS1822   = 0x22;
    const static uint8_t DS18B20  = 0x28;
    const static uint8_t DS1825   = 0x3B;
    const static uint8_t DS28EA00 = 0x42;

    /** Number of thermometers types supported by this driver */
    const static int SUPPORTED_SLAVES_NUM = 5;

protected:
    void waitForCompletion(int ms, bool parasitic, int scanTimeoutMs);

    template<int MAX_TIME>
    OneWireNg::ErrorCode _convertTemp(
        const OneWireNg::Id *id, int convTime, bool parasitic)
    {
        OneWireNg::ErrorCode ec =
            (id ? _ow.addressSingle(*id) : _ow.addressAll());

        if (ec == OneWireNg::EC_SUCCESS) {
            _ow.writeByte(CMD_CONVERT_T);
            waitForCompletion(
                (convTime < 0 && parasitic ? MAX_TIME : convTime),
                parasitic, MAX_TIME);
        }
        return ec;
    }

    OneWireNg::ErrorCode _writeScratchpad(const OneWireNg::Id *id,
        int8_t th, int8_t tl, uint8_t res, uint8_t addr);

    OneWireNg::ErrorCode _copyScratchpad(
        const OneWireNg::Id *id, bool parasitic, int copyTime)
    {
        OneWireNg::ErrorCode ec =
            (id ? _ow.addressSingle(*id) : _ow.addressAll());

        if (ec == OneWireNg::EC_SUCCESS) {
            _ow.writeByte(CMD_COPY_SCRATCHPAD);
            waitForCompletion((copyTime <= 0 ? 0 : copyTime),
                parasitic, 0 /* not used */);
        }
        return ec;
    }

    OneWireNg::ErrorCode _recallEeprom(const OneWireNg::Id *id)
    {
        OneWireNg::ErrorCode ec =
            (id ? _ow.addressSingle(*id) : _ow.addressAll());

        if (ec == OneWireNg::EC_SUCCESS)
            _ow.writeByte(CMD_RECALL_E2);

        return ec;
    }

    int _readPowerSupply(const OneWireNg::Id *id)
    {
        int status = 1;
        OneWireNg::ErrorCode ec =
            (id ? _ow.addressSingle(*id) : _ow.addressAll());

        if (ec == OneWireNg::EC_SUCCESS) {
            _ow.writeByte(CMD_READ_POW_SUPPLY);
            status = _ow.readBit();
        }
        return status;
    }

    /* integer right shift (sign aware) */
    static long rsh(long v, int sh) {
        return (v < 0 ? ~((~v) >> sh) : (v >> sh));
    }

    /* integer power 2 division (sign aware) */
    static long div2(long v, int pow) {
        return (v < 0 ? -((-v) >> pow) : (v >> pow));
    }

    OneWireNg& _ow;

    typedef struct {
        uint8_t code;
        const char *name;
    } FamilyCodeName;

    static const FamilyCodeName FAMILY_NAMES[SUPPORTED_SLAVES_NUM];
};

#endif /* __OWNG_DSTHERM__ */
