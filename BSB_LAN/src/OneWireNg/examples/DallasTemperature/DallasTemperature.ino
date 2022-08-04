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

/**
 * Dallas family thermometers access example.
 */
#include "OneWireNg_CurrentPlatform.h"
#include "drivers/DSTherm.h"
#include "utils/Placeholder.h"

#define OW_PIN          10

/*
 * Set to true for parasitically powered sensors.
 */
#define PARASITE_POWER  false

/*
 * Uncomment for power provided by a switching
 * transistor and controlled by this pin.
 */
//#define PWR_CTRL_PIN    9

/*
 * Uncomment to set permanent, common resolution for all
 * sensors on the bus. Resolution may vary from 9 to 12 bits.
 */
//#define COMMON_RES      (DSTherm::RES_12_BIT)

static Placeholder<OneWireNg_CurrentPlatform> _ow;

/* returns false if not supported */
static bool printId(const OneWireNg::Id& id)
{
    const char *name = DSTherm::getFamilyName(id);

    Serial.print(id[0], HEX);
    for (size_t i = 1; i < sizeof(OneWireNg::Id); i++) {
        Serial.print(':');
        Serial.print(id[i], HEX);
    }
    if (name) {
        Serial.print(" -> ");
        Serial.print(name);
    }
    Serial.println();

    return (name != NULL);
}

static void printScratchpad(const DSTherm::Scratchpad& scrpd)
{
    const uint8_t *scrpd_raw = scrpd.getRaw();

    Serial.print("  Scratchpad:");
    for (size_t i = 0; i < DSTherm::Scratchpad::LENGTH; i++) {
        Serial.print(!i ? ' ' : ':');
        Serial.print(scrpd_raw[i], HEX);
    }

    Serial.print("; Th:");
    Serial.print(scrpd.getTh());

    Serial.print("; Tl:");
    Serial.print(scrpd.getTl());

    Serial.print("; Resolution:");
    Serial.print(9 + (int)(scrpd.getResolution() - DSTherm::RES_9_BIT));

    long temp = scrpd.getTemp();
    Serial.print("; Temp:");
    if (temp < 0) {
        temp = -temp;
        Serial.print('-');
    }
    Serial.print(temp / 1000);
    Serial.print('.');
    Serial.print(temp % 1000);
    Serial.print(" C");

    Serial.println();
}

void setup()
{
#ifdef PWR_CTRL_PIN
# ifndef CONFIG_PWR_CTRL_ENABLED
#  error "CONFIG_PWR_CTRL_ENABLED needs to be enabled"
# endif
    new (&_ow) OneWireNg_CurrentPlatform(OW_PIN, PWR_CTRL_PIN, false);
#else
    new (&_ow) OneWireNg_CurrentPlatform(OW_PIN, false);
#endif
    DSTherm drv(_ow);

    Serial.begin(115200);

#if (CONFIG_MAX_SRCH_FILTERS > 0)
    static_assert(CONFIG_MAX_SRCH_FILTERS >= DSTherm::SUPPORTED_SLAVES_NUM,
        "CONFIG_MAX_SRCH_FILTERS too small");

    drv.filterSupportedSlaves();
#endif

#ifdef COMMON_RES
    /*
     * Set common resolution for all sensors.
     * Th, Tl (high/low alarm triggers) are set to 0.
     */
    drv.writeScratchpadAll(0, 0, COMMON_RES);

    /*
     * The configuration above is stored in volatile sensors scratchpad
     * memory and will be lost after power unplug. Therefore store the
     * configuration permanently in sensors EEPROM.
     */
    drv.copyScratchpadAll(PARASITE_POWER);
#endif
}

void loop()
{
    DSTherm drv(_ow);
    Placeholder<DSTherm::Scratchpad> _scrpd;

    /* convert temperature on all sensors connected... */
    drv.convertTempAll(DSTherm::SCAN_BUS, PARASITE_POWER);

    /* ...and read them one-by-one */
    for (const auto& id: (OneWireNg&)_ow) {
        if (printId(id)) {
            if (drv.readScratchpad(id, &_scrpd) == OneWireNg::EC_SUCCESS)
                printScratchpad(_scrpd);
            else
                Serial.println("  Invalid CRC!");
        }
    }

    Serial.println("----------");
    delay(1000);
}
