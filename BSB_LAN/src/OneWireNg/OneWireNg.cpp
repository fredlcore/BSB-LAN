/*
 * Copyright (c) 2019-2021 Piotr Stolarz
 * OneWireNg: Arduino 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

#include <string.h>  /* memcpy, memset */
#include "OneWireNg.h"

#define CRC8_BASIC      1
#define CRC8_TAB_16LH   2

#define CRC16_BASIC     1
#define CRC16_TAB_16LH  2

#if defined(CONFIG_CRC8_ALGO) && \
    !(CONFIG_CRC8_ALGO == CRC8_BASIC || CONFIG_CRC8_ALGO == CRC8_TAB_16LH)
# error "Invalid CONFIG_CRC8_ALGO"
#endif

#if defined(CONFIG_CRC16_ALGO) && \
    !(CONFIG_CRC16_ALGO == CRC16_BASIC || CONFIG_CRC16_ALGO == CRC16_TAB_16LH)
# error "Invalid CONFIG_CRC16_ALGO"
#endif

#ifdef CONFIG_FLASH_CRC_TAB
# include "platform/Platform_FlashMem.h"
# define tabRead_u8 flashRead_u8
# define tabRead_u16 flashRead_u16
# define tabRead_u32 flashRead_u32
#else
# define CRCTAB_STORAGE
# define tabRead_u8(addr) (*(const uint8_t*)(addr))
# define tabRead_u16(addr) (*(const uint16_t*)(addr))
# define tabRead_u32(addr) (*(const uint32_t*)(addr))
#endif

uint8_t OneWireNg::touchByte(uint8_t byte)
{
    uint8_t ret = 0;
    for (int i = 0; i < 8; i++) {
        if (touchBit(byte & 1)) ret |= 1 << i;
        byte >>= 1;
    }
    return ret;
}

#define __UPDATE_DISCREPANCY() \
    (memcpy(_lsrch, id, sizeof(Id)), ((_lzero = lzero) < 0))

OneWireNg::ErrorCode OneWireNg::search(Id& id, bool alarm)
{
    ErrorCode ec;
    int lzero;

    if (_lzero < -1)
        /* search process finished; no more slave devices available */
        return EC_NO_DEVS;

#if (CONFIG_MAX_SRCH_FILTERS > 0)
restart:
#endif
    lzero = -2;
    memset(&id, 0, sizeof(Id));

    /* initialize search process on slave devices */
    ec = reset();
    if (ec != EC_SUCCESS)
        return ec;

#if (CONFIG_MAX_SRCH_FILTERS > 0)
    searchFilterSelectAll();
#endif
    touchByte(alarm ? CMD_SEARCH_ROM_COND : CMD_SEARCH_ROM);

    for (int n = 0; n < (int)(8 * sizeof(Id)); n++)
    {
        ec = transmitSearchTriplet(n, id, lzero);

#if (CONFIG_MAX_SRCH_FILTERS > 0)
        if (ec == EC_NO_DEVS) {
            if (__UPDATE_DISCREPANCY())
                return EC_NO_DEVS;
            else
                goto restart;
        } else
#endif
        if (ec != EC_SUCCESS)
            return ec;
    }

    ec = checkCrcId(id);
    if (ec != EC_SUCCESS)
        return ec;

    __UPDATE_DISCREPANCY();
    return EC_MORE;
}

#undef __UPDATE_DISCREPANCY

#define __BITMASK8(n)       ((uint8_t)(1 << ((n) & 7)))
#define __BYTE_OF_BIT(t, n) ((t)[(n) >> 3])
#define __BIT_IN_BYTE(t, n) (__BYTE_OF_BIT(t, n) & __BITMASK8(n))
#define __BIT_SET(t, n)     (__BYTE_OF_BIT(t, n) |= __BITMASK8(n))

#if (CONFIG_MAX_SRCH_FILTERS > 0)
OneWireNg::ErrorCode OneWireNg::searchFilterAdd(uint8_t code)
{
    for (int i = 0; i < _n_fltrs; i++) {
        /* check if the code is already added */
        if (_fltrs[i].code == code)
            return EC_SUCCESS;
    }

    if (_n_fltrs >= CONFIG_MAX_SRCH_FILTERS)
        return EC_FULL;

    _fltrs[_n_fltrs].code = code;
    _fltrs[_n_fltrs].ns = false;
    _n_fltrs++;

    return EC_SUCCESS;
}

void OneWireNg::searchFilterDel(uint8_t code)
{
    for (int i = 0; i < _n_fltrs; i++) {
        if (_fltrs[i].code == code) {
            for (i++; i < _n_fltrs; i++) {
                _fltrs[i-1].code = _fltrs[i].code;
            }
            _n_fltrs--;
            break;
        }
    }
}

int OneWireNg::searchFilterApply(int n)
{
    if (!_n_fltrs)
        /* no filtering - any bit value applies */
        return 2;

    uint8_t ba = 0, bo = 0, bm = __BITMASK8(n);
    ba--; /* all 1s */

    for (int i = 0; i < _n_fltrs; i++) {
        if (!_fltrs[i].ns) {
            ba &= _fltrs[i].code;
            bo |= _fltrs[i].code;
        }
    }
    return (!(bo & bm) ? 0 : ((ba & bm) ? 1 : 2));
}

void OneWireNg::searchFilterSelect(int n, int bit)
{
    uint8_t bm = __BITMASK8(n);
    for (int i = 0; i < _n_fltrs; i++) {
        if (!_fltrs[i].ns) {
            if ((((_fltrs[i].code & bm) != 0) ^ (bit != 0)))
                _fltrs[i].ns = true;
        }
    }
}
#endif /* CONFIG_MAX_SRCH_FILTERS */

/**
 * Transmit search triplet on the bus (for a given bit position @c n)
 * consisting of the following bits:
 * - bit 1: 0 present for this bit position (master reads, slave writes),
 * - bit 2: 1 present for this bit position (master reads, slave writes),
 * - bit 3: select slave with a given bit value (master writes, slave reads).
 *     This bit may not be transmitted in case it has no sense (no slave
 *     devices on the bus or bus error).
 *
 * If selected bit value is 1 then the corresponding n-th bit in @c id is set
 * (the @id must be initialized with 0).
 *
 * @c lzero is set to @c n if discrepancy occurred at the processed bit and
 * the bit value is 0. @c lzero is not updated in other case.
 *
 * @return Error codes:
 *     - @c EC_SUCCESS: Searching step successfully finished; device @c id
 *         returned.
 *     - @c EC_BUS_ERROR: Unexpected response received - bus error.
 *     - @c EC_NO_DEVS: Returned if search filtering is enabled and there are
 *         no devices matching the filtering criteria in the current searching
 *         step. Search-scan process needs to be continued with a subsequent
 *         searching step or finished (depending on the binary tree processing
 *         condition).
 */
OneWireNg::ErrorCode OneWireNg::transmitSearchTriplet(int n, Id& id, int& lzero)
{
    int selBit; /* selected bit value */

    int v0 = touchBit(1);   /* 0-presence */
    int v1 = touchBit(1);   /* 1-presence */

    if (v1 && v0)
    {
        /*
         * No slave devices present on the bus. Reset pulse
         * indicated presence of some - bus error is returned.
         */
        return EC_BUS_ERROR;
    } else
    if (!v1 && !v0)
    {
        /*
         * Discrepancy detected for this bit position.
         */
        if (n >= (int)(8 * (sizeof(Id)-1))) {
            /* no discrepancy is expected for CRC part of the id - bus error */
            return EC_BUS_ERROR;
        } else {
#if (CONFIG_MAX_SRCH_FILTERS > 0)
            if (n >= 8 || (selBit = searchFilterApply(n)) == 2)
#endif
            {
                if (n < _lzero) {
                    selBit = (__BIT_IN_BYTE(_lsrch, n) != 0);
                } else
                if (n == _lzero) {
                    selBit = 1;
                } else {
                    selBit = 0;
                }

                if (!selBit)
                    lzero = n;
            }
        }
    } else
    {
        /*
         * Unambiguous value for this bit position.
         */
        selBit = !v1;
#if (CONFIG_MAX_SRCH_FILTERS > 0)
        if (n < 8)
        {
            /* check if code matches filtering criteria */
            int fltBit = searchFilterApply(n);
            if (fltBit != 2 && fltBit != selBit)
                return EC_NO_DEVS;
        }
#endif
    }

    touchBit(selBit);
#if (CONFIG_MAX_SRCH_FILTERS > 0)
    searchFilterSelect(n, selBit);
#endif
    if (selBit) {
        __BIT_SET(id, n);
    }
    return EC_SUCCESS;
}

#undef __BIT_SET
#undef __BIT_IN_BYTE
#undef __BYTE_OF_BIT
#undef __BITMASK8

uint8_t OneWireNg::crc8(const void *in, size_t len, uint8_t crc_in)
{
    uint8_t crc = crc_in;

#if (CONFIG_CRC8_ALGO == CRC8_TAB_16LH)
    const uint8_t *in_bts = (const uint8_t*)in;

    static const uint8_t CRCTAB_STORAGE CRC8_16L[] = {
        0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83,
        0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41
    };
    static const uint8_t CRCTAB_STORAGE CRC8_16H[] = {
        0x00, 0x9d, 0x23, 0xbe, 0x46, 0xdb, 0x65, 0xf8,
        0x8c, 0x11, 0xaf, 0x32, 0xca, 0x57, 0xe9, 0x74
    };

    while (len--) {
        crc ^= *in_bts++;
        crc = tabRead_u8(CRC8_16L + (crc & 0x0f)) ^
            tabRead_u8(CRC8_16H + (crc >> 4));
    }
#else
    crc = OneWireNg::crc<uint8_t, 0x8c>(in, len, crc);
#endif
    return crc;
}

#ifdef CONFIG_CRC16_ENABLED
uint16_t OneWireNg::crc16(const void *in, size_t len, uint16_t crc_in)
{
    uint16_t crc = crc_in;

# if (CONFIG_CRC8_ALGO == CRC16_TAB_16LH)
    const uint8_t *in_bts = (const uint8_t*)in;

    static const uint16_t CRCTAB_STORAGE CRC16_16L[] = {
        0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
        0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440
    };
    static const uint16_t CRCTAB_STORAGE CRC16_16H[] = {
        0x0000, 0xcc01, 0xd801, 0x1400, 0xf001, 0x3c00, 0x2800, 0xe401,
        0xa001, 0x6c00, 0x7800, 0xb401, 0x5000, 0x9c01, 0x8801, 0x4400
    };

    while (len--) {
        crc ^= *in_bts++;
        crc = (crc >> 8) ^
            tabRead_u16(CRC16_16L + (crc & 0x0f)) ^
            tabRead_u16(CRC16_16H + ((crc >> 4) & 0x0f));
    }
# else
    crc = OneWireNg::crc<uint16_t, 0xa001>(in, len, crc_in);
# endif
    return crc;
}
#endif
