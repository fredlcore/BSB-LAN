/*
 * Copyright (c) 2020 Piotr Stolarz
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
 * 1-wire overdrive mode example. Requires @c CONFIG_OVERDRIVE_ENABLED.
 */
#include "OneWireNg_CurrentPlatform.h"

#define OW_PIN          10

#ifndef CONFIG_OVERDRIVE_ENABLED
# error "Example requires CONFIG_OVERDRIVE_ENABLED to be configured"
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

void setup()
{
    OneWireNg::Id id;
    ow = new OneWireNg_CurrentPlatform(OW_PIN, false);

    Serial.begin(115200);

    /* enable overdrive (OD) mode on all devices supporting it */
    ow->overdriveAll();

    /* subsequent communication in OD mode */

    /* search for OD enabled devices */
    Serial.println("Overdrive enabled devices:");

    ow->searchReset();
    while (ow->search(id) == OneWireNg::EC_MORE)
        printId(id);

    /* back to the standard mode */
    ow->setOverdrive(false);
}

void loop()
{
    delay(1000);
}
