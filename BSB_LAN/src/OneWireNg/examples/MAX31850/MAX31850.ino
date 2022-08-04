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

/**
 * MAX31850/MAX31851 thermocouple example.
 *
 * Required configuration:
 * - @c CONFIG_MAX_SRCH_FILTERS >= 1.
 */
#include "OneWireNg_CurrentPlatform.h"
#include "drivers/MAX31850.h"
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

#if (CONFIG_MAX_SRCH_FILTERS < 1)
# error "Example requires CONFIG_MAX_SRCH_FILTERS >= 1 to be configured"
#endif

static OneWireNg *ow = NULL;

static void printId(const OneWireNg::Id& id)
{
    Serial.print(id[0], HEX);
    for (size_t i = 1; i < sizeof(OneWireNg::Id); i++) {
        Serial.print(':');
        Serial.print(id[i], HEX);
    }
    Serial.println();
}

static void printTemp(long temp)
{
    if (temp < 0) {
        temp = -temp;
        Serial.print('-');
    }
    Serial.print(temp / 1000);
    Serial.print('.');
    Serial.print(temp % 1000);
    Serial.print(" C");
}

static void printScratchpad(const MAX31850::Scratchpad& scrpd)
{
    const uint8_t *scrpd_raw = scrpd.getRaw();

    Serial.print("  Scratchpad:");
    for (size_t i = 0; i < MAX31850::Scratchpad::LENGTH; i++) {
        Serial.print(!i ? ' ' : ':');
        Serial.print(scrpd_raw[i], HEX);
    }

    Serial.print("; Temp:");
    printTemp(scrpd.getTemp());

    Serial.print("; Internal temp:");
    printTemp(scrpd.getTempInternal());

    Serial.print("; Fault:");
    Serial.print((scrpd.getFaultStatus() ? 1 : 0));

    Serial.print("; Input state:");
    Serial.print(scrpd.getInputState());

    Serial.print("; Address:");
    Serial.print(scrpd.getAddr());

    Serial.println();
}

void setup()
{
#ifdef PWR_CTRL_PIN
# ifndef CONFIG_PWR_CTRL_ENABLED
#  error "CONFIG_PWR_CTRL_ENABLED needs to be enabled"
# endif
    ow = new OneWireNg_CurrentPlatform(OW_PIN, PWR_CTRL_PIN, false);
#else
    ow = new OneWireNg_CurrentPlatform(OW_PIN, false);
#endif

    Serial.begin(115200);

    /* filter MAX31850/MAX31851 devices only */
    ow->searchFilterAdd(MAX31850::FAMILY_CODE);
}

void loop()
{
    MAX31850 drv(*ow);
    Placeholder<MAX31850::Scratchpad> _scrpd;

    /* convert temperature on all sensors connected... */
    drv.convertTempAll(MAX31850::SCAN_BUS, PARASITE_POWER);

    /* ...and read them one-by-one */
    for (const auto& id: *ow) {
        printId(id);

        if (drv.readScratchpad(id, &_scrpd) == OneWireNg::EC_SUCCESS)
            printScratchpad(_scrpd);
        else
            Serial.println("  Invalid CRC!");
    }

    Serial.println("----------");
    delay(1000);
}
