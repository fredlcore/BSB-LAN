/*
 * Copyright (c) 2020,2021 Piotr Stolarz
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
 * DS2431 EEPROM usage example.
 *
 * Required configuration:
 * - @c CONFIG_CRC16_ENABLED,
 * - @c CONFIG_MAX_SRCH_FILTERS >= 1,
 * - @c CONFIG_OVERDRIVE_ENABLED if @c USE_OD_MODE defined.
 */
#include "OneWireNg_CurrentPlatform.h"

#define OW_PIN      10

/* if defined use overdrive mode */
//#define USE_OD_MODE

/* if defined write demo is enabled */
//#define WRITE_DEMO

/* DS2431 family code */
#define DS2431      0x2D

/* memory function commands */
#define CMD_WRITE_SCRATCHPAD    0x0F
#define CMD_COPY_SCRATCHPAD     0x55
#define CMD_READ_SCRATCHPAD     0xAA
#define CMD_READ_MEMORY         0xF0

/* EEPROM row size */
#define ROW_SIZE    8
/* EEPROM page size */
#define PAGE_SIZE   (4 * ROW_SIZE)
/* DS2431 memory size */
#define MEM_SIZE    (18 * ROW_SIZE)

#ifndef CONFIG_CRC16_ENABLED
# error "Example requires CONFIG_CRC16_ENABLED to be configured"
#endif

#if (CONFIG_MAX_SRCH_FILTERS < 1)
# error "Example requires CONFIG_MAX_SRCH_FILTERS >= 1 to be configured"
#endif

#if defined(USE_OD_MODE) && !defined(CONFIG_OVERDRIVE_ENABLED)
# error "Example requires CONFIG_OVERDRIVE_ENABLED to be configured for USE_OD_MODE"
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

/**
 * Prints device EEPROM memory on serial. The memory is ready via READ_MEMORY
 * (0xF0) command which doesn't incorporate CRC protection. Therefore usage of
 * the function is problematic on transmission error vulnerable environments
 * (including OD mode).
 *
 * If @c id is NULL the routine resumes communication with lastly addressed
 * device.
 */
static void printMem(const OneWireNg::Id *id)
{
    static const char HEX_DIGS[] = "0123456789ABCDEF";
    uint8_t cmd[MEM_SIZE + 3];

    cmd[0] = CMD_READ_MEMORY;
    /* start reading from 0x0000 */
    cmd[1] = 0x00; /* TA1 (LSB) */
    cmd[2] = 0x00; /* TA2 (MSB) */

    /* read memory will be placed here */
    uint8_t *mem = &cmd[3];
    memset(mem, 0xff, MEM_SIZE);

    if (id) {
        ow->addressSingle(*id);
    } else {
        ow->resume();
    }
    ow->touchBytes(cmd, MEM_SIZE + 3);

    for (int i = 0; i < MEM_SIZE; i++)
    {
        char hex[3] = {};

        if (!(i % ROW_SIZE))
        {
            hex[0] = HEX_DIGS[(i >> 4)];
            hex[1] = HEX_DIGS[(i & 0x0f)];

            Serial.print("00");
            Serial.print(hex);
            Serial.print(' ');
        }
        hex[0] = HEX_DIGS[(mem[i] >> 4)];
        hex[1] = HEX_DIGS[(mem[i] & 0x0f)];

        Serial.print(hex);
        if (((i+1) % ROW_SIZE) != 0) {
            Serial.print(':');
        } else {
            switch (i/ROW_SIZE)
            {
            case 0:
                Serial.println(" Data Memory Page 0");
                break;
            case 4:
                Serial.println(" Data Memory Page 1");
                break;
            case 8:
                Serial.println(" Data Memory Page 2");
                break;
            case 12:
                Serial.println(" Data Memory Page 3");
                break;
            case 16:
                Serial.println(" Control Bytes: PCB0:PCB1:PCB2:PCB3:CPB:FACT:USR1:USR2");
                break;
            case 17:
                Serial.println(" Reserved");
                break;
            default:
                Serial.println();
                break;
            }
        }
    }
}

#ifdef WRITE_DEMO
/**
 * Write a single EEPROM row passed in @c rowData. Row address (0-17) passed
 * by @c rowAddr.
 *
 * If @c checkDataIntegr is @c true scratchpad data are verified against
 * the data being set (@c rowData) if both are the same. This parameter shall
 * be set to @c false for EPROM mode (logical AND performed by write).
 *
 * If @c id is NULL the routine resumes communication with lastly addressed
 * device.
 *
 * On success the routine returns @c true.
 */
static bool writeRow(const OneWireNg::Id *id,
    unsigned rowAddr, const uint8_t rowData[ROW_SIZE], bool checkDataIntegr)
{
    if (rowAddr > 17) return false;

    uint8_t cmd[ROW_SIZE + 6];

    uint8_t ta1 = (rowAddr * ROW_SIZE); /* TA1 (LSB) */
    uint8_t ta2 = 0x00;                 /* TA2 (MSB) */

    /* STEP 1: write row data into scratchpad
     */
    cmd[0] = CMD_WRITE_SCRATCHPAD;
    cmd[1] = ta1;
    cmd[2] = ta2;
    memcpy(&cmd[3], rowData, ROW_SIZE);

    /* inverted CRC-16 will be placed here */
    uint8_t *crc16 = &cmd[ROW_SIZE + 3];
    crc16[0] = 0xff;
    crc16[1] = 0xff;

    if (id) {
        ow->addressSingle(*id);
    } else {
        ow->resume();
    }
    ow->touchBytes(cmd, ROW_SIZE + 5);

    if (ow->checkInvCrc16(cmd, ROW_SIZE + 3, ow->getLSB_u16(crc16)) !=
        OneWireNg::EC_SUCCESS)
    {
        Serial.println("WRITE SCRATCHPAD: CRC error");
        return false;
    }

    /* STEP 2: verify scratchpad integrity
     */
    cmd[0] = CMD_READ_SCRATCHPAD;
    /* TA1, TA2, E/S, row data, CRC16 will be placed here */
    memset(&cmd[1], 0xff, ROW_SIZE + 5);

    ow->resume();
    ow->touchBytes(cmd, ROW_SIZE + 6);

    crc16 = &cmd[ROW_SIZE + 4];
    if (ow->checkInvCrc16(cmd, ROW_SIZE + 4, ow->getLSB_u16(crc16)) !=
        OneWireNg::EC_SUCCESS)
    {
        Serial.println("READ SCRATCHPAD: CRC error");
        return false;
    }

    /* PF and AA flags must be cleared TA1, TA2 must match */
    uint8_t es = cmd[3];
    if (ta1 != cmd[1] || ta2 != cmd[2] || (es & 0x20) || (es & 0x80))
    {
        Serial.println("READ SCRATCHPAD: command status error");
        return false;
    }

    /* check if data was set in scratchpad */
    if (checkDataIntegr && memcmp(&cmd[4], rowData, ROW_SIZE))
    {
        Serial.println("READ SCRATCHPAD: row is write protected");
        return false;
    }

    /* STEP 3: copy scratchpad into EEPROM
     */
    cmd[0] = CMD_COPY_SCRATCHPAD;
    /* TA1, TA2, E/S already set as required */

    ow->resume();
    ow->touchBytes(cmd, 4);

    /* wait for completion (10 ms) */
    delay(10);

    return true;
}

/**
 * @ref writeRow() analogous to write EEPROM page. Page specified by
 * @c pageAddr (0-3).
 */
static bool writePage(const OneWireNg::Id *id,
    unsigned pageAddr, const uint8_t pageData[PAGE_SIZE], bool checkDataIntegr)
{
    if (pageAddr > 3) return false;

    int i;
    uint8_t row = pageAddr * (PAGE_SIZE / ROW_SIZE);

    for (i = 0; i < (PAGE_SIZE / ROW_SIZE); i++, row++) {
        if (!writeRow((!i ? id : NULL),
            row, &pageData[i * ROW_SIZE], checkDataIntegr)) break;
    }

    if (i < (PAGE_SIZE / ROW_SIZE))
    {
        Serial.print("Error writing row ");
        Serial.print(row);
        Serial.print(" in page ");
        Serial.print(pageAddr);
        return false;
    }
    return true;
}
#endif /* WRITE_DEMO */

void setup()
{
    OneWireNg::Id id;

    /* id of a DS2431 device for write demo;
       if not set 1st available DS2431 device will be chosen */
    OneWireNg::Id dev = {};

    ow = new OneWireNg_CurrentPlatform(OW_PIN, false);

    Serial.begin(115200);

#ifdef USE_OD_MODE
    ow->overdriveAll();
#endif

    /* search for DS2431 devices connected to the bus
     */
    ow->searchFilterAdd(DS2431);
    Serial.println("Connected DS2431 devices:");

    ow->searchReset();
    while (ow->search(id) == OneWireNg::EC_MORE) {
        if (dev[0] != DS2431)
            memcpy(&dev, &id[0], sizeof(OneWireNg::Id));

        printId(id);
        printMem(NULL);

        Serial.println("----------");
    }

#ifdef WRITE_DEMO
    /* if no DS2431 found finish the demo */
    if (dev[0] != DS2431) return;

    uint8_t pageData[PAGE_SIZE] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08,
        0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00
    };
    if (writePage(&dev, 1, pageData, true)) {
        Serial.println("Page successfully written to EEPROM");
    }
#endif
}

void loop()
{
    delay(1000);
}
