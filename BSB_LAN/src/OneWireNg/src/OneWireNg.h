/*
 * Copyright (c) 2019-2023 Piotr Stolarz
 * OneWireNg: Arduino 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

#ifndef __OWNG__
#define __OWNG__

#include <stddef.h>
#include <stdint.h>
#include "platform/Platform_New.h"  /* operator delete (~OneWireNg) */

#if CONFIG_EXT_VIRTUAL_INTF
# define EXT_VIRTUAL_INTF virtual
#else
# define EXT_VIRTUAL_INTF
#endif

#if (CONFIG_MAX_SEARCH_FILTERS > 0)
# if !CONFIG_SEARCH_ENABLED
/* search filtering is disabled if 1-wire search is disabled */
#  undef CONFIG_MAX_SEARCH_FILTERS
#  define CONFIG_MAX_SEARCH_FILTERS 0
# elif (CONFIG_MAX_SEARCH_FILTERS > 255)
#  error "Invalid CONFIG_MAX_SEARCH_FILTERS"
# endif
#endif

#if (__cplusplus >= 201103L) && CONFIG_SEARCH_ENABLED
# define USE_SEARCH_RANGE_LOOP 1
#endif

/**
 * 1-wire service interface specification.
 *
 * The class relies on virtual functions provided by derivative class to
 * perform platform specific operations. The platform specific class shall
 * provide:
 * - @ref reset() - reset cycle transmission,
 * - @ref touchBit() - 1-wire touch (write and read are touch derived).
 *
 * and optionally:
 * - @ref powerBus() - if parasite powering is supported.
 *
 * @note If the extended virtual interface is enabled a derivative class may
 *     override additional methods being part of this extended interface.
 */
class OneWireNg
{
public:
    /**
     * 1-wire 64-bit id; little-endian
     *
     * Id[0]: device family id,
     * Id[1..6]: unique s/n,
     * Id[7]: CRC-8.
     */
    typedef uint8_t Id[8];

    typedef enum
    {
        /** Success */
        EC_SUCCESS = 0,
        /** Search process in progress - more slave devices available */
        EC_MORE = EC_SUCCESS,
        /** No slave devices; search process finished */
        EC_NO_DEVS,
        /** 1-wire bus error */
        EC_BUS_ERROR,
        /** CRC error */
        EC_CRC_ERROR,
        /** Service is not supported by the platform */
        EC_UNSUPPORED,
        /** No space (e.g. filters table is full) */
        EC_FULL
    } ErrorCode;

    /**
     * Destructor needs to be virtual.
     *
     * @note As part of implementation of a virtual destructor body the C++
     *     compiler provides deleting-destructor code responsible for object
     *     deallocation via delete. This implies operator delete() (global or
     *     class specific) needs to be accessible for any class with virtual
     *     destructor defined.
     */
    virtual ~OneWireNg() {}

    /**
     * Transmit reset cycle on the 1-wire bus.
     *
     * @return Error codes:
     *     - @c EC_SUCCESS: Detected device(s) connected to the bus (presence
     *         pulse observed after the reset cycle).
     *     - @c EC_NO_DEVS: No devices on the bus.
     */
    virtual ErrorCode reset() = 0;

    /**
     * Bit touch.
     *
     * 1-wire bus touching depends on a touched bit as follows:
     * 0: Writes 0 on the bus. There is no bus sampling (the function returns 0),
     * 1: Writes 1 on the bus and samples for response (returned by the
     *    function). The write-1 cycle is equivalent for reading cycle, except
     *    the writing cycle doesn't sample the bus for a response.
     *
     * @param bit Bit to be touched on the bus.
     * @param power If parasite powering is supported, setting the argument
     *     to @c true powers the bus after the operation finishes. See @ref
     *     powerBus() for details.
     *
     * @return Touching result.
     */
    virtual int touchBit(int bit, bool power = false) = 0;

    /**
     * Byte touch with least significant bit transmitted first.
     *
     * @param bit Byte to be touched on the bus.
     * @param power Same as for @ref touchBit().
     *
     * @return Touching result.
     *
     * @note This method is part of the extended virtual interface.
     */
    EXT_VIRTUAL_INTF uint8_t touchByte(uint8_t byte, bool power = false)
    {
        uint8_t ret = 0;
        for (int i = 0; i < 8; i++) {
            if (touchBit(byte & 1, power && (i >= 7)))
                ret |= 1 << i;

            byte >>= 1;
        }
        return ret;
    }

    /**
     * Array of bytes touch.
     *
     * @param bytes Array of bytes to be touched on the bus.
     *     Result is passed back in the same buffer.
     * @param len Length of the array.
     * @param power Same as for @ref touchBit().
     *
     * @note This method is part of the extended virtual interface.
     */
    EXT_VIRTUAL_INTF void touchBytes(
        uint8_t *bytes, size_t len, bool power = false)
    {
        for (size_t i = 0; i < len; i++)
            bytes[i] = touchByte(bytes[i], power && (i + 1 >= len));
    }

    /**
     * Bit write.
     *
     * @param bit Bit to be written on the bus.
     * @param power If parasite powering is supported, setting the argument
     *     to @c true powers the bus after the operation finishes. See @ref
     *     powerBus() for details.
     *
     * @note This method is part of the extended virtual interface.
     */
    EXT_VIRTUAL_INTF void writeBit(int bit, bool power = false) {
        touchBit(bit, power);
    }

    /**
     * Byte write with least significant bit transmitted first.
     *
     * @param bit Byte to be written on the bus.
     * @param power Same as for @ref writeBit().
     *
     * @note This method is part of the extended virtual interface.
     */
    EXT_VIRTUAL_INTF void writeByte(uint8_t byte, bool power = false) {
        touchByte(byte, power);
    }

    /**
     * Array of bytes write.
     *
     * @param bytes Array of bytes to be written on the bus.
     * @param len Length of the array.
     * @param power Same as for @ref writeBit().
     *
     * @note This method is part of the extended virtual interface.
     */
    EXT_VIRTUAL_INTF void writeBytes(
        const uint8_t *bytes, size_t len, bool power = false)
    {
        for (size_t i = 0; i < len; i++)
            touchByte(bytes[i], power && (i + 1 >= len));
    }

    /**
     * Bit read.
     *
     * @return Reading result.
     *
     * @note This method is part of the extended virtual interface.
     */
    EXT_VIRTUAL_INTF int readBit() {
        return touchBit(1);
    }

    /**
     * Byte read with least significant bit transmitted first.
     *
     * @return Reading result.
     *
     * @note This method is part of the extended virtual interface.
     */
    EXT_VIRTUAL_INTF uint8_t readByte() {
        return touchByte(0xff);
    }

    /**
     * Array of bytes read.
     *
     * @param bytes Array of bytes to store the reading result.
     * @param len Number of bytes to read (length of the array).
     *
     * @note This method is part of the extended virtual interface.
     */
    EXT_VIRTUAL_INTF void readBytes(uint8_t *bytes, size_t len) {
        for (size_t i = 0; i < len; i++)
            bytes[i] = touchByte(0xff);
    }

#if CONFIG_SEARCH_ENABLED
    /**
     * Perform single search step in the search-scan process to detect slave
     * devices connected to the bus. Before calling this routine for the first
     * time in the search-scan @ref searchReset() must be called to initialize
     * the search context.
     *
     * @param id In case of success will be filled with an id of the slave
     *     device detected in this step.
     * @param alarm If @c true - search for devices only with alarm state set,
     *     @c false - search for all devices.
     *
     * @return
     *     Non-failure error codes:
     *     - @c EC_MORE (aka @c EC_SUCCESS): More devices available by
     *         subsequent calls of this routine. @c id is written with slave id.
     *     - @c EC_NO_DEVS: No more slave devices (@c id not returned; passed
     *         variable content may be changed).
     *     Failure error codes (@c id not returned; passed variable content may
     *     be changed):
     *     - @c EC_BUS_ERROR: Bus error.
     *     - @c EC_CRC_ERROR: CRC error.
     *
     * @note This method is part of the extended virtual interface.
     *
     * @note It is possible to use C++11 range loop to iterate over connected
     *     slaves as in the following code snippet:
     *
     * @code
     * OneWireNg *ow;
     *
     * for (const auto& id: *ow) {
     *     // 'id' contains 1-wire address of a connected slave
     * }
     * @endcode
     */
    EXT_VIRTUAL_INTF ErrorCode search(Id& id, bool alarm = false);

    /**
     * Reset 1-wire search state for a subsequent search-scan process.
     *
     * @note This method is part of the extended virtual interface.
     */
    EXT_VIRTUAL_INTF void searchReset() {
        _lzero = -1;
    }
#endif /* CONFIG_SEARCH_ENABLED */

#if USE_SEARCH_RANGE_LOOP
# if __cplusplus >= 201703L
    /* due to std namespace discrepancies between various toolchains
       decltype(nullptr) is used here instead of std::nullptr_t */
    typedef decltype(nullptr) end_iterator;
# else
    class iterator;
    typedef iterator end_iterator;
# endif

    /** Range-loop iterator. */
    class iterator
    {
    public:
        iterator& operator++() {
            if (searchStep() != EC_MORE)
                /* last iteration step; mark the iterator as final */
                _ow = nullptr;

            return *this;
        }

        Id& operator*() {
            return _id;
        }

        /* called only to detect the final iteration */
        bool operator!=(const end_iterator&) {
            return (_ow != nullptr);
        }

    private:
        /* iterator is not intended to be created outside search range-loops */
        iterator(): _ow(nullptr) {};

        iterator(OneWireNg *ow): _ow(ow) {
            searchStep();
        }

        ErrorCode searchStep()
        {
            ErrorCode ec;
# if (CONFIG_ITERATION_RETRIES > 0)
            int retry = CONFIG_ITERATION_RETRIES;

            do {
                ec = _ow->search(_id, _ow->_italm);
            } while ((ec == EC_CRC_ERROR || ec == EC_BUS_ERROR) &&
                retry-- > 0);
# else
            ec = _ow->search(_id, _ow->_italm);
# endif
            if (ec != EC_MORE)
                /* last iteration step; mark the iterator as final */
                _ow = nullptr;

            return ec;
        }

        Id _id;
        OneWireNg *_ow;

    friend class OneWireNg;
    };

    iterator begin() {
        searchReset();
        return iterator(this);
    }

    end_iterator end() {
        return end_iterator();
    }

    /**
     * Set iteration mode for subsequent search range-loops.
     *
     * @param alarm If @c true iterate over slaves in alarm mode,
     *     @c false iterate over all slaves connected to the bus.
     *
     * @note Default mode is "all-slaves". A newly configured mode is
     *     persistent until the next call of this routine changing it.
     */
    void setIterationMode(bool alarm) {
        _italm = alarm;
    }
#endif /* USE_SEARCH_RANGE_LOOP */

#if (CONFIG_MAX_SEARCH_FILTERS > 0)
    /**
     * Add a family @c code to the search filters.
     * During the search process slave devices with given family code
     * are filtered from the whole set of devices connected to the bus.
     *
     * @return Error codes:
     *     - @c EC_SUCCESS: The @c code added to the filters set.
     *     - @c EC_FULL: No more place in filters table to add the code.
     */
    ErrorCode searchFilterAdd(uint8_t code);

    /**
     * Remove a family @c code from the search filters.
     */
    void searchFilterDel(uint8_t code);

    /**
     * Remove all currently set family codes.
     * Consequently no filtering will be applied during the search process.
     */
    void searchFilterDelAll() {
        _n_fltrs = 0;
    }

    /**
     * Get number of family codes already added to the search filters.
     *
     * Note, adding the same family code into search filters results with only
     * one code effectively added. For this reason the value returned by this
     * function indicates number of different family codes configured to be
     * filtered out (not number of calls to @ref searchFilterAdd()) and is
     * always less or equal than @CONFIG_MAX_SEARCH_FILTERS.
     */
    int searchFilterSize() const {
        return _n_fltrs;
    }
#endif /* CONFIG_MAX_SEARCH_FILTERS */

    /**
     * In case there is only one slave connected to the 1-wire bus the routine
     * enables reading its id (without performing the whole search-scan process)
     * by:
     * - Send the reset pulse.
     * - If presence pulse indicates some slave(s) present on the bus, send
     *   "Read ROM" command (0x33).
     * - Read followed 8 bytes constituting the id.
     * - Check CRC of the read id. In case of CRC failure there is probably
     *   more than one slave on the bus causing garbage (logical AND) of the
     *   received data.
     *
     * @param id @c Id object placeholder where the read id will be stored.
     *
     * @return Error codes:
     *     - @c EC_SUCCESS: Success, the result written to @c id.
     *     - @c EC_NO_DEVS: No slave devices.
     *     - @c EC_CRC_ERROR: Probably more than one slave on the bus.
     */
    ErrorCode readSingleId(Id& id)
    {
        ErrorCode ret = reset();
        if (ret == EC_SUCCESS) {
            writeByte(CMD_READ_ROM);
            readBytes(&id[0], sizeof(Id));
            ret = checkCrcId(id);
        }
        return ret;
    }

    /**
     * Address single slave device by:
     * - Send the reset pulse.
     * - If presence pulse indicates some slave(s) present on the bus, send
     *   "Match ROM" command (0x55) followed by the slave id.
     *
     * After calling this routine subsequent data sent over the bus will be
     * received by the selected slave until the next reset pulse.
     *
     * @param id Id of the addressed device.
     *
     * @return Same as for @ref reset().
     */
    ErrorCode addressSingle(const Id& id)
    {
        ErrorCode ret = reset();
        if (ret == EC_SUCCESS) {
            writeByte(CMD_MATCH_ROM);
            writeBytes(&id[0], sizeof(Id));
        }
        return ret;
    }

    /**
     * Address all slave devices connected to the bus by:
     * - Send the reset pulse.
     * - If presence pulse indicates some slave(s) present on the bus, send
     *   "Skip ROM" command (0xCC).
     *
     * After calling this routine subsequent data sent over the bus will be
     * received by all connected slaves until the next reset pulse.
     *
     * @return Same as for @ref reset().
     */
    ErrorCode addressAll()
    {
        ErrorCode ret = reset();
        if (ret == EC_SUCCESS) {
            writeByte(CMD_SKIP_ROM);
        }
        return ret;
    }

    /**
     * Resume communication with a slave device which was previously addressed
     * by @ref addressSingle(), @ref overdriveSingle() or @ref search().
     * Activities performed by the routine:
     * - Send the reset pulse.
     * - If presence pulse indicates some slave(s) present on the bus, send
     *   "Resume" command (0xA5).
     *
     * @return Same as for @ref reset().
     *
     * @note The command is supported only by limited number of 1-wire devices
     *     (e.g. DS2408, DS2431).
     */
    ErrorCode resume()
    {
        ErrorCode ret = reset();
        if (ret == EC_SUCCESS) {
            writeByte(CMD_RESUME);
        }
        return ret;
    }

#if CONFIG_OVERDRIVE_ENABLED
    /**
     * Enable overdrive mode for single slave device (the device must support
     * the mode):
     * - Send the reset pulse (standard mode).
     * - If presence pulse indicates some slave(s) present on the bus, send
     *   "Match ROM Overdrive" command (0x69) followed by the slave id. The id
     *   is sent in the overdrive (high-speed) mode.
     * - Turn on overdrive mode for all subsequent 1-wire activities performed
     *   by the library (reset, read, write, touch, search).
     *
     * The routine is intended to start high-speed 1-wire communication with a
     * single, overdrive enabled device. There is no need to perform additional
     * reset after calling the routine since the "Match ROM Overdrive" command
     * selects the overdrive enabled device, therefore device specific command
     * may be sent directly after calling the routine.
     *
     * To switch back to the standard mode @c setOverdrive(false) needs to be
     * called. After performing 1-wire reset in the standard mode the overdrive
     * mode is disabled on all devices connected to the bus - only standard mode
     * communication is possible.
     *
     * @param id Id of the addressed device.
     *
     * @return Same as for @ref reset().
     */
    ErrorCode overdriveSingle(const Id& id)
    {
        setOverdrive(false);
        ErrorCode ret = reset();
        if (ret == EC_SUCCESS) {
            writeByte(CMD_MATCH_ROM_OVERDRIVE);
            setOverdrive(true);
            writeBytes(&id[0], sizeof(Id));
        }
        return ret;
    }

    /**
     * Enable overdrive mode for all slave devices supporting the mode:
     * - Send the reset pulse (standard mode).
     * - If presence pulse indicates some slave(s) present on the bus, send
     *   "Skip ROM Overdrive" command (0x3C).
     * - Turn on overdrive mode for all subsequent 1-wire activities performed
     *   by the library (reset, read, write, touch, search).
     *
     * The routine is intended to start high-speed 1-wire communication with
     * overdrive enabled devices. All 1-wire activities after calling this
     * routine are confined to overdrive enabled devices. For example a user
     * may need to:
     * - Perform @ref search() to get ids of overdrive enabled devices.
     * - Address specific device(s) via @ref addressAll() or @ref addressSingle()
     *   to perform commands in the overdrive mode.
     *
     * To switch back to the standard mode @c setOverdrive(false) needs to be
     * called. After performing 1-wire reset in the standard mode the overdrive
     * mode is disabled on all devices connected to the bus - only standard mode
     * communication is possible.
     *
     * @return Same as for @ref reset().
     */
    ErrorCode overdriveAll()
    {
        setOverdrive(false);
        ErrorCode ret = reset();
        if (ret == EC_SUCCESS) {
            writeByte(CMD_SKIP_ROM_OVERDRIVE);
            setOverdrive(true);
        }
        return ret;
    }

    /**
     * Set the library in the standard/overdrive mode. After calling the routine
     * all 1-wire activities performed on the bus by the library (reset, read,
     * write, touch, search) are performed in a configured mode.
     *
     * It's important to note the routine doesn't enable/disable overdrive mode
     * on slave devices connected to the bus. See @ref overdriveAll() and @ref
     * overdriveSingle() for more information.
     *
     * @param on If @c true - overdrive mode, @c false - standard mode.
     */
    void setOverdrive(bool on) {
        _overdrive = on;
    }
#endif /* CONFIG_OVERDRIVE_ENABLED */

    /**
     * Power the 1-wire bus via direct connection a voltage source to the bus.
     * The function enables to leverage parasite powering of slave devices
     * required to perform energy consuming operation, where energy provided
     * by resistor-pulled-up data wire is not sufficient.
     *
     * The power is provided until the next activity on the bus (reset, read,
     * write, touch) or the routine is called with @c on set to @c false.
     *
     * @param on If @true - power the bus, @false - depower the bus.
     *
     * @return Error codes:
     *     - @c EC_UNSUPPORED: Service is unsupported by the platform.
     *     - @c EC_SUCCESS: Otherwise.
     *
     * @note This is low level function. Its direct usage is not recommended.
     *     Use appropriate version of touch or write method to power the bus
     *     and relay on automatic depowering on a subsequent activity on the
     *     bus.
     */
    virtual ErrorCode powerBus(bool on) {
        (void)(on);
        return EC_UNSUPPORED;
    }

    /**
     * Generic CRC calculation (reflected-input, reflected-output mode).
     *
     * Template parameters:
     * @param CrcType CRC type. For example @c uint8_t for CRC-8, @c uint16_t
     *     for CRC-16, @c uint32_t for CRC-32.
     * @param RevPoly CRC polynomial coefficients in reverse order, e.g. 0x8C
     *     (not 0x31) for CRC-8/MAXIM, 0xA001 (not 0x8005) for CRC-16/ARC.
     */
    template<class CrcType, CrcType RevPoly>
    static inline CrcType crc(const void *in, size_t len, CrcType crc_in = 0)
    {
        CrcType crc = crc_in;
        const uint8_t *in_bts = (const uint8_t*)in;

        while (len--) {
            crc ^= *in_bts++;
            for (int i = 8; i; i--)
                crc = (crc & 1 ? RevPoly : 0) ^ (crc >> 1);
        }
        return crc;
    }

    /**
     * Compute CRC-8/MAXIM.
     * Polynomial used: x^8 + x^5 + x^4 + 1
     */
    static uint8_t crc8(const void *in, size_t len, uint8_t crc_in = 0);

#if CONFIG_CRC16_ENABLED
    /**
     * Compute CRC-16/ARC.
     * Polynomial used: x^16 + x^15 + x^2 + 1
     */
    static uint16_t crc16(const void *in, size_t len, uint16_t crc_in = 0);

    /**
     * Check bitwise inverted CRC-16/ARC (aka CRC-16/MAXIM) for a given input
     * @c in of length @c len bytes.
     *
     * @c invCrc argument represents a bitwise inverted CRC checksum sent over
     * the 1-wire bus which needs to be compliant with the computed checksum.
     * Use @ref getLSB_u16() routine to get this little-endian encoded CRC from
     * received bytes sent over the bus, e.g.:
     *
     * @code
     *     OneWireNg::checkInvCrc16(
     *         &recv_buf[recv_data_to_check_offset],
     *         recv_data_to_check_length,
     *         OneWireNg::getLSB_u16(&recv_buf[recv_data_inv_crc16_offset]));
     * @endcode
     *
     * @return Error codes:
     *     - @c EC_SUCCESS: Compliant CRC.
     *     - @c EC_CRC_ERROR: CRC mismatch.
     */
    static ErrorCode checkInvCrc16(const void *in, size_t len, uint16_t invCrc) {
        return (!(uint16_t)(crc16(in, len) ^ ~invCrc) ? EC_SUCCESS : EC_CRC_ERROR);
    }
#endif

    /**
     * Check CRC-8/MAXIM for a given @c id.
     *
     * @return Error codes:
     *     - @c EC_SUCCESS: Compliant CRC.
     *     - @c EC_CRC_ERROR: CRC mismatch.
     */
    static ErrorCode checkCrcId(const Id& id)
    {
        uint8_t crc = crc8(&id[0], sizeof(Id) - 1);
        return (crc == id[sizeof(Id) - 1] ? EC_SUCCESS : EC_CRC_ERROR);
    }

    /**
     * Read 2 consecutive bytes starting at address @c addr and interpret them
     * as @c uin16_t little-endian integer.
     *
     * @note This function may be useful as a platform endianess agnostic
     *     routine reading multi-byte integers sent over 1-wire bus
     *     (characterised by LSB first byte order).
     */
    static uint16_t getLSB_u16(const void *addr)
    {
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) || defined(__LITTLE_ENDIAN__)
        return *(const uint16_t*)addr;
#else
        return (uint16_t)((const uint8_t*)addr)[0] |
            ((uint16_t)((const uint8_t*)addr)[1] << 8);
#endif
    }

    /**
     * Read 4 consecutive bytes starting at address @c addr and interpret them
     * as @c uin32_t little-endian integer.
     *
     * @see getLSB_u16()
     */
    static uint32_t getLSB_u32(const void *addr)
    {
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) || defined(__LITTLE_ENDIAN__)
        return *(const uint32_t*)addr;
#else
        return (uint32_t)((const uint8_t*)addr)[0] |
            ((uint32_t)((const uint8_t*)addr)[1] << 8) |
            ((uint32_t)((const uint8_t*)addr)[2] << 16) |
            ((uint32_t)((const uint8_t*)addr)[3] << 24);
#endif
    }

    const static uint8_t CMD_READ_ROM            = 0x33;
    const static uint8_t CMD_MATCH_ROM           = 0x55;
    const static uint8_t CMD_RESUME              = 0xA5;
    const static uint8_t CMD_SKIP_ROM            = 0xCC;
    const static uint8_t CMD_SEARCH_ROM_COND     = 0xEC;
    const static uint8_t CMD_SEARCH_ROM          = 0xF0;
#if CONFIG_OVERDRIVE_ENABLED
    const static uint8_t CMD_SKIP_ROM_OVERDRIVE  = 0x3C;
    const static uint8_t CMD_MATCH_ROM_OVERDRIVE = 0x69;
#endif

protected:
   /**
    * This class is intended to be inherited by specialized classes.
    */
    OneWireNg() {
#if CONFIG_SEARCH_ENABLED
        searchReset();
#endif
#if (CONFIG_MAX_SEARCH_FILTERS > 0)
        searchFilterDelAll();
#endif
#if CONFIG_OVERDRIVE_ENABLED
        _overdrive = false;
#endif
#if USE_SEARCH_RANGE_LOOP
        _italm = false;
#endif
    }

#if (CONFIG_MAX_SEARCH_FILTERS > 0)
    struct {
        uint8_t code;   /** family code */
        bool ns;        /** not-selected flag */
    } _fltrs[CONFIG_MAX_SEARCH_FILTERS];

    int _n_fltrs;       /** number of configured filters */
#endif

#if CONFIG_OVERDRIVE_ENABLED
    bool _overdrive;    /** overdrive turned on */
#endif
#if USE_SEARCH_RANGE_LOOP
    bool _italm;        /** search range-loop in alarm mode */
#endif

private:
    /* OneWireNg objects are not intended to be copied or moved */
    OneWireNg(const OneWireNg&);
    OneWireNg& operator=(const OneWireNg&);

#if __cplusplus >= 201103L
    OneWireNg(OneWireNg&&) noexcept;
    OneWireNg& operator=(OneWireNg&&) noexcept;
#endif

#if CONFIG_SEARCH_ENABLED
    ErrorCode transmitSearchTriplet(int n, Id& id, int& lzero);

    Id _lsrch;  /** last search result */
    int _lzero; /** last 0-value search discrepancy bit number */
#endif

#if (CONFIG_MAX_SEARCH_FILTERS > 0)
    int searchFilterApply(uint8_t bm);
    void searchFilterSelect(uint8_t bm, int bit);
    void searchFilterSelectAll();

    /* AND/OR bit-fields used for family code filtering */
    bool _bao_reuse;
    uint8_t _ba;
    uint8_t _bo;
#endif

#ifdef OWNG_TEST
friend class OneWireNg_Test;
#endif
};

#undef USE_SEARCH_RANGE_LOOP
#undef EXT_VIRTUAL_INTF
#endif /* __OWNG__ */
