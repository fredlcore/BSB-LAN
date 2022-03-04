/*
 * Copyright (c) 2021 Piotr Stolarz
 * OneWireNg: Arduino 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

#include "../platform/Platform_Delay.h"
#include "../drivers/DSTherm.h"

#define STR(m) #m

const DSTherm::FamilyCodeName
    DSTherm::FAMILY_NAMES[SUPPORTED_SLAVES_NUM] =
{
    { DS18S20, STR(DS18S20) },
    { DS1822, STR(DS1822) },
    { DS18B20, STR(DS18B20) },
    { DS1825, STR(DS1825) },
    { DS28EA00, STR(DS28EA00) }
};

OneWireNg::ErrorCode DSTherm::readScratchpad(
    const OneWireNg::Id& id, Scratchpad *scratchpad)
{
    OneWireNg::ErrorCode ec = _ow.addressSingle(id);
    if (ec == OneWireNg::EC_SUCCESS)
    {
        uint8_t cmd[1 + Scratchpad::LENGTH] = {
            CMD_READ_SCRATCHPAD,
            /* the read scratchpad will be placed here (9 bytes) */
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
        };

        _ow.touchBytes(cmd, sizeof(cmd));

        if (OneWireNg::crc8(&cmd[1], Scratchpad::LENGTH - 1) ==
            cmd[Scratchpad::LENGTH])
        {
            new (scratchpad) Scratchpad(_ow, id, &cmd[1]);
        } else
            ec = OneWireNg::EC_CRC_ERROR;
    }
    return ec;
}

#if (CONFIG_MAX_SRCH_FILTERS > 0)
OneWireNg::ErrorCode DSTherm::filterSupportedSlaves()
{
    size_t i;

    /* if n-th bit is set corresponding code from FAMILY_NAMES was added */
    uint8_t bm = 0;

    for (i = 0; i < SUPPORTED_SLAVES_NUM; bm <<= 1, i++) {
        int sz = _ow.searchFilterSize();

        if (_ow.searchFilterAdd(FAMILY_NAMES[i].code) != OneWireNg::EC_SUCCESS)
            break;

        if (_ow.searchFilterSize() > sz)
            bm |= 1;
    }
    bm >>= 1;

    if (i >= SUPPORTED_SLAVES_NUM)
        return OneWireNg::EC_SUCCESS;

    /* not enough space to add the codes, revert partially added codes */
    for (i = 0; bm; bm >>= 1, i++) {
        if (bm & 1)
            _ow.searchFilterDel(FAMILY_NAMES[i].code);
    }
    return OneWireNg::EC_FULL;
}
#endif

const char *DSTherm::getFamilyName(const OneWireNg::Id& id)
{
    for (size_t i = 0; i < SUPPORTED_SLAVES_NUM; i++) {
        if (id[0] == FAMILY_NAMES[i].code)
            return FAMILY_NAMES[i].name;
    }
    return NULL;
}

void DSTherm::waitForCompletion(int ms, bool parasitic, int scanTimeoutMs)
{
    if (ms > 0) {
        /* wait specified amount of time */
        if (parasitic) {
            _ow.powerBus(true);
            delayMs(ms);
            _ow.powerBus(false);
        } else
            delayMs(ms);
    } else if (!ms) {
        /* return immediately; power the bus for parasitic mode */
        if (parasitic)
            _ow.powerBus(true);
    } else {
        /* scan the bus for completion */
        for (int i = 0; i < scanTimeoutMs; i++) {
            if (_ow.readBit())
                break;
            else
                delayMs(1);
        }
    }
}

OneWireNg::ErrorCode DSTherm::_writeScratchpad(
    const OneWireNg::Id *id, int8_t th, int8_t tl, uint8_t res, uint8_t addr)
{
    OneWireNg::ErrorCode ec =
        (id ? _ow.addressSingle(*id) : _ow.addressAll());

    if (ec == OneWireNg::EC_SUCCESS)
    {
        uint8_t cmd[4] = {
            CMD_WRITE_SCRATCHPAD,
            (uint8_t)th, (uint8_t)tl,
            (uint8_t)((((res - RES_9_BIT) & 3) << 5) | 0x10 | (addr & 0x0f))
        };

        /*
         * While sending the command to all sensors on the bus, all 3
         * bytes of configuration are sent event though DS18S20 requires
         * only first 2 of them. This approach seems to be more safe on
         * environments where various types of sensors are connected.
         */
        size_t cmd_len =
            (id && (*id)[0] == DS18S20 ? sizeof(cmd)-1 : sizeof(cmd));

        _ow.writeBytes(cmd, cmd_len);
    }
    return ec;
}

OneWireNg::ErrorCode DSTherm::Scratchpad::writeScratchpad() const
{
    OneWireNg::ErrorCode ec = _ow.addressSingle(_id);
    if (ec == OneWireNg::EC_SUCCESS)
    {
        uint8_t cmd[4] = {
            CMD_WRITE_SCRATCHPAD, _scrpd[2], _scrpd[3], _scrpd[4]
        };
        size_t len = (_id[0] == DS18S20 ? sizeof(cmd)-1 : sizeof(cmd));

        _ow.writeBytes(cmd, len);
    }
    return ec;
}

long DSTherm::Scratchpad::getTemp() const
{
    long temp = ((long)(int8_t)_scrpd[1] << 8) | _scrpd[0];

    if (_id[0] != DS18S20) {
        unsigned res = (_scrpd[4] >> 5) & 3;

        if (res < 3) {
            /* truncate fractional undefined bits */
            temp = rsh(temp, 3 - res);
        }
        temp = div2(temp * 1000, res + 1);
    } else {
#ifdef CONFIG_DS18S20_EXT_RES
        if (_scrpd[7]) {
            /* truncate fractional part */
            temp = rsh(temp, 1) * 1000;
            temp += (1000L * (int8_t)(_scrpd[7] - _scrpd[6]) / _scrpd[7]) - 250;
        } else
#endif
            temp = div2(temp * 1000, 1);
    }
    return temp;
}
