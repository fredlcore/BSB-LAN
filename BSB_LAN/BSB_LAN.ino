/*
 *
 * BSB Boiler-System-Bus LAN Interface
 *
 * ATTENTION:
 *       There is no warranty that this system will not damage your heating system!
 *
 * Authors Gero Schumacher (up to version 0.16)
 *         Frederik Holst (bsb@code-it.de) (from version 0.17 onwards)
 *         (based on the code and work from many other developers. Many thanks!)
 *         Special thanks to Ulf Diekmann for maintaining the manual up to version 3.3 and to Sergey Dukachev for lots of helpful code optimizations and restructurings as well as providing a profound Russian localization since version 0.43
 *
 * 
 * ChangeLog has moved to separate file docs/CHANGELOG.md
 * 
 */

#if defined(__AVR__)
#error "Sorry, Arduino Mega not supported since BSB-LAN 2.1"
#endif

#if defined(ESP32) && !defined(ARDUINO_PARTITION_min_spiffs)
  #error "Wrong partition scheme selected! You have to select Minimal/SPIFFS! Please, please, please(!) do read the manual at docs.bsb-lan.de - if you don't even read the quickstart instructions, you _will_ not be able to run BSB-LAN! Thank you."
#endif

#include <Arduino.h>

#define ESP32_OLIMEX 1
#define ESP32_NODEMCU 2
#define ARDUINO_DUE 3
#if defined(ESP32)
  #if (defined(ARDUINO_ESP32_EVB) || defined(ARDUINO_ESP32_POE) || defined(ARDUINO_ESP32_POE_ISO))
    #define BOARD ESP32_OLIMEX
  #else
    #define BOARD ESP32_NODEMCU
  #endif
#else
  #define BOARD ARDUINO_DUE
#endif

#define BUS_OK 1
#define BUS_NOTFREE -1
#define BUS_NOMATCH -2

#define LOGTELEGRAM_OFF 0
#define LOGTELEGRAM_ON 1
#define LOGTELEGRAM_UNKNOWN_ONLY 2
#define LOGTELEGRAM_BROADCAST_ONLY 4

#define HTTP_AUTH 1
#define HTTP_GZIP 2
#define HTTP_HEAD_REQ 4
#define HTTP_ETAG 8
#define HTTP_GET_ROOT 16
#define HTTP_FRAG 128

#define HTTP_FILE_NOT_GZIPPED false
#define HTTP_FILE_GZIPPED true

#define HTTP_NO_DOWNLOAD false
#define HTTP_IS_DOWNLOAD true

#define HTTP_ADD_CHARSET_TO_HEADER true
#define HTTP_DO_NOT_ADD_CHARSET_TO_HEADER false
#define HTTP_DO_NOT_CACHE -1
#define HTTP_AUTO_CACHE_AGE 0

#define HTTP_OK 200
#define HTTP_NOT_MODIFIED 304
#define HTTP_AUTH_REQUIRED 401
#define HTTP_NOT_FOUND 404

#define MIME_TYPE_TEXT_HTML 1
#define MIME_TYPE_TEXT_CSS 2
#define MIME_TYPE_APP_JS 3
#define MIME_TYPE_APP_XML 4
#define MIME_TYPE_TEXT_TEXT 5
#define MIME_TYPE_APP_JSON 6
#define MIME_TYPE_TEXT_PLAIN 7
#define MIME_TYPE_IMAGE_JPEG 101
#define MIME_TYPE_IMAGE_GIF 102
#define MIME_TYPE_IMAGE_SVG 103
#define MIME_TYPE_IMAGE_PNG 104
#define MIME_TYPE_IMAGE_ICON 105
#define MIME_TYPE_APP_GZ 201
#define MIME_TYPE_FORCE_DOWNLOAD 202

#define DO_NOT_PRINT_DISABLED_VALUE false
#define PRINT_DISABLED_VALUE true
#define PRINT_NOTHING 0
#define PRINT_VALUE 1
#define PRINT_DESCRIPTION 2
#define PRINT_VALUE_FIRST 4
#define PRINT_DESCRIPTION_FIRST 8
#define PRINT_ONLY_VALUE_LINE 16
#define PRINT_ENUM_AS_DT_BITS 32

#define LAN 0
#define WLAN 1
#define SDCARD 0
#define FLASH 1
#define DEVELOPER_DEBUG 2
#define REMOVE 0
#define CREATE 1

// These are configuration options that are set in main code in order not to confuse ordinary users. 
// If you really feel you need to change them, undefine them in BSB_LAN_config.h and then set them to your desired value.
// e.g.:
// #undef UDP_LOG_PORT
// #define UDP_LOG_PORT 6800

#define UDP_LOG_PORT 6502 // UDP log port number
#define QUERY_RETRIES  3

typedef struct {
  float number;
  int16_t dest_addr;
} parameter;

typedef struct {
  uint16_t dev_fam;
  uint16_t dev_var;
  uint8_t dev_id;
  uint32_t dev_serial;
  char name[33];
} device_map;
device_map dev_lookup[10];

// Forward declarations
#if defined(ESP32)
uint64_t usedBytes();
uint64_t totalBytes();
void scanAndConnectToStrongestNetwork();
void removeTemporaryAP();
void createTemporaryAP();
#else
#define WiFiEvent_t int         // Very strange that the netEvent() function which is completely guarded by preprocessor directives throws an error on Arduino Due, complaining that WiFiEvent_t is not defined. This workaround fixes this.
#endif
void loop();
int set(float line, const char *val, bool setcmd);
uint8_t recognizeVirtualFunctionGroup(float nr);
void GetDevId();
void SerialPrintRAW(byte* msg, byte len);
int bin2hex(char *toBuffer, byte *fromAddr, int len, char delimiter);
const char* printError(uint16_t error);
void query(float line);
void startLoggingDevice();
void resetAverageCalculation();
void connectToMaxCul();
void SetDevId();
void mqtt_callback(char* topic, byte* payload, unsigned int length);  //Luposoft: predefintion
void mqtt_sendtoBroker(parameter param);
uint32_t printKat(uint8_t cat, int print_val, boolean debug_output=true);

#include "src/Base64/src/Base64.h"

//#include "src/BSB/BSBSoftwareSerial.h"
#include "src/BSB/bsb.h"
#include "BSB_LAN_config.h"
#include "BSB_LAN_defs.h"

#define REQUIRED_CONFIG_VERSION 39
#if CONFIG_VERSION < REQUIRED_CONFIG_VERSION
  #error "Your BSB_LAN_config.h is not up to date! Please use the most recent BSB_LAN_config.h.default, rename it to BSB_LAN_config.h and make the necessary changes to this new one." 
#endif


#define EEPROM_SIZE 0x1000
#if !defined(EEPROM_ERASING_PIN)
  #if defined(ESP32)
    #if (BOARD == ESP32_OLIMEX)   // GPIO 34 for ESP32-Olimex
      #undef EEPROM_ERASING_PIN
      #define EEPROM_ERASING_PIN 34
    #else                         // GPIO 21 for ESP32-NodeMCU
      #undef EEPROM_ERASING_PIN
      #define EEPROM_ERASING_PIN 21
    #endif
  #else                           // GPIO 31 for Arduino Due
    #undef EEPROM_ERASING_PIN
    #define EEPROM_ERASING_PIN 31
  #endif
#endif
#if !defined(EEPROM_ERASING_GND_PIN) && !defined(ESP32)
  #define EEPROM_ERASING_GND_PIN 33
#endif
#if !defined(LED_BUILTIN)
  #define LED_BUILTIN 2
#endif

#if defined(__arm__)
  #include <SPI.h>
  #include <Wire.h>
  #include "src/I2C_EEPROM/I2C_EEPROM.h"
template<uint8_t I2CADDRESS=0x50> class UserDefinedEEP : public  eephandler<I2CADDRESS, 4096U,2,32>{};
// EEPROM 24LC32: Size 4096 Byte, 2-Byte address mode, 32 byte page size
// EEPROM 24LC16: Size 2048 Byte, 1-Byte address mode, 16 byte page size
UserDefinedEEP<> EEPROM; // default Adresse 0x50 (80)
#endif

#if defined(ESP32)
  #include <WiFi.h>
  #include <esp_task_wdt.h>
  #include <EEPROM.h>
  #include <WiFiUdp.h>
  #include <esp_wifi.h>
WiFiUDP udp, udp_log;
  #include <WebServer.h>
  #include <Update.h>
WebServer update_server(8080);

EEPROMClass EEPROM_ESP((const char *)"nvs");
  #define EEPROM EEPROM_ESP     // This is a dirty hack because the Arduino IDE does not pass on #define NO_GLOBAL_EEPROM which would prevent the double declaration of the EEPROM object
#else
  #ifdef WIFISPI
    #warning "Support for WiFi on Arduino Due may be removed in future versions. Please inform Frederik (bsb (ät) code-it.de) that you are still using it."
    #include "src/WiFiSpi/src/WiFiSpiUdp.h"
WiFiSpiUdp udp, udp_log;
  #else
    #include <EthernetUdp.h>
EthernetUDP udp, udp_log;
  #endif
#endif


//#include <CRC32.h>
#include "src/CRC32/CRC32.h"
//#include <util/crc16.h>
#if defined(ESP32)
  #include "src/esp32_time.h"
#else
  #include "src/Time/TimeLib.h"
#endif

#include "src/PubSubClient/src/PubSubClient.h"
#include "html_strings.h"

//BME280 library was modified. Definitions for SDA1/SCL1 on Due added:
//#if defined(__SAM3X8E__)
//#define Wire Wire1
//#endif
#include <Wire.h>
#include "src/BlueDot_BME280/BlueDot_BME280.h"
BlueDot_BME280 *bme;  //Set 2 if you need two sensors.
//Multiplexor TCA9548A (if presented) address on I2C bus
#define TCA9548A_ADDR 0x70

bool client_flag = false;

#ifdef WIFISPI
    #include "src/WiFiSpi/src/WiFiSpi.h"
using ComServer = WiFiSpiServer;
using ComClient = WiFiSpiClient;
    #define WiFi WiFiSpi
#endif

bool localAP = false;
unsigned long localAPtimeout = millis();

#ifdef ESP32
  #ifndef ETH_PHY_ADDR
  #define ETH_PHY_ADDR 0
  #endif
  #ifndef ETH_PHY_TYPE
  #define ETH_PHY_TYPE ETH_PHY_LAN8720
  #endif
  #ifndef ETH_PHY_POWER
  #define ETH_PHY_POWER -1
  #endif
  #ifndef ETH_PHY_MDC
  #define ETH_PHY_MDC 23
  #endif
  #ifndef ETH_PHY_MDIO
  #define ETH_PHY_MDIO 18
  #endif
  #ifndef ETH_CLK_MODE
  #define ETH_CLK_MODE ETH_CLOCK_GPIO0_IN
  #endif

  #include <ETH.h>

  // For some reason, pins_arduino.h for the Olimex EVB does not contain the configuration for the LAN interface (while Olimex POE and POE-ISO do have it), so we have to define them here before including ETH.h.
class Eth : public ETHClass {
public:
    int maintain(void) const { return 0;} ; // handled internally
    bool begin(uint8_t *mac, IPAddress ip, IPAddress dnsserver, IPAddress gateway, IPAddress subnet) {
      bool success = begin(mac);
      config(ip, gateway, subnet, dnsserver, dnsserver); //Static
      return success;
    }
    bool begin(uint8_t *mac) {
      return ETHClass::begin();
    }
};

Eth Ethernet;
using ComServer = WiFiServer;
using ComClient = WiFiClient;
#else
    #include <Ethernet.h>
using ComServer = EthernetServer;
using ComClient = EthernetClient;
#endif

#if !defined(ESP32)
  #include "src/ArduinoMDNS/ArduinoMDNS.h"
MDNS mdns(udp);
#else
  #include <ESPmDNS.h>
#endif

bool EEPROM_ready = true;
byte programWriteMode = 0; //0 - read only, 1 - write ordinary programs, 2 - write ordinary + OEM programs

ComServer *server;
ComServer *telnetServer;
Stream *SerialOutput;

//BSB bus definitions
BSB *bus;
//end BSB bus definitions

// Define a structure to hold a buffer and its size
typedef struct {
    char* buffer;
    size_t size;
    size_t currentLength; // Track current length to avoid recomputing
} StringBuffer;

/* buffer to print output lines and to load PROGMEM values in RAM*/
#define OUTBUF_LEN  450
char outBuf[OUTBUF_LEN] = { 0 };

// big output buffer with automatic flushing. Do not do direct access
#undef OUTBUF_USEFUL_LEN
#define OUTBUF_USEFUL_LEN (OUTBUF_LEN * 2)

char bigBuff[OUTBUF_USEFUL_LEN + OUTBUF_LEN] = { 0 };
int bigBuffPos=0;

// buffer for debug output
char DebugBuff[OUTBUF_LEN] = { 0 };

#if defined(__SAM3X8E__)
const char averagesFileName[] = "averages.txt";
const char datalogFileName[] = "datalog.txt";
const char datalogIndexFileName[] = "datalog.idx";
const char journalFileName[] = "journal.txt";
const char datalogTemporaryFileName[] = "datalog.tmp";
const char datalogIndexTemporaryFileName[] = "dataidx.tmp";
#elif defined(ESP32)
const char averagesFileName[] = "/averages.txt";
const char datalogFileName[] = "/datalog.txt";
const char datalogIndexFileName[] = "/datalog.idx";
const char journalFileName[] = "/journal.txt";
const char datalogTemporaryFileName[] = "/datalog.tmp";
const char datalogIndexTemporaryFileName[] = "/dataidx.tmp";
#endif

// datalogIndexFile (c.f. above) is a binary file,
// in which a set of two values is logged whenever a new calendar date is reached:
// the calendar day just reached (see typedef below), and the size of the actual datalogFile
// just before that calendar day.
typedef union {
  struct { uint8_t day, month; uint16_t year; } elements;  // order is important here!
  uint32_t combined;
} compactDate_t;
#if BYTE_ORDER != LITTLE_ENDIAN  // we need this for direct .combined comparisons of two dates
#error "Unexpected endian, please contact DE-cr on github"
#endif
#define datalogIndexEntrySize (sizeof(compactDate_t)+sizeof(uint32_t))
compactDate_t previousDatalogDate, firstDatalogDate, currentDate;  // GetDateTime() sets currentDate

ComClient client;
ComClient *mqtt_client;   //Luposoft: own instance
ComClient httpclient;
ComClient telnetClient;
ComClient *max_cul;

PubSubClient *MQTTPubSubClient;
bool haveTelnetClient = false;

#define MAX_CUL_DEVICES (sizeof(max_device_list)/sizeof(max_device_list[0]))
int32_t max_devices[MAX_CUL_DEVICES] = { 0 };
uint16_t max_cur_temp[MAX_CUL_DEVICES] = { 0 };
uint8_t max_dst_temp[MAX_CUL_DEVICES] = { 0 };
int8_t max_valve[MAX_CUL_DEVICES] = { -1 };

// char _ipstr[INET6_ADDRSTRLEN];    // addr in format xxx.yyy.zzz.aaa
// char _ipstr[20];    // addr in format xxx.yyy.zzz.aaa
// byte __remoteIP[4] = {0,0,0,0};   // IP address in bin format

#if defined(ESP32)
uint64_t minimum_SD_size = 0;
    #include "FS.h"
    #include <LittleFS.h>
  #if (BOARD == ESP32_NODEMCU && !defined(FORCE_SD_MMC_ON_NODEMCU))    // Joy-It NodeMCU with SPI-based SD card reader
    #include "SD.h"
    #include "SPI.h"
FS& SDCard = SD;
  #else
    #include "SD_MMC.h"
FS& SDCard = SD_MMC;
  #endif
#else     // !ESP32
int32_t minimum_SD_size = 0;
    #define FILE_APPEND FILE_WRITE  // FILE_APPEND does not exist on Arduino, FILE_WRITE seems to do the same (create if not existing, start writing from EOF onwards)
    // set MAINTAIN_FREE_CLUSTER_COUNT to 1 in SdFatConfig.h if you want increase speed of free space calculation
    // do not forget set it up after SdFat upgrading
    #include "src/SdFat/SdFat.h"
SdFat SDCard;
#endif    // ESP32

// CONFIG_DS18S20_EXT_RES can be enabled in OneWireNg_Config.h
// Paths in some files should be changed after library updating.
#include "src/OneWireNg/src/OneWire.h"
#include "src/DallasTemperature/DallasTemperature.h"
#ifndef TEMPERATURE_PRECISION //Not used in this time
  #define TEMPERATURE_PRECISION 9 //9 bit. Time to calculation: 94 ms
//    #define TEMPERATURE_PRECISION 10 //10 bit. Time to calculation: 188 ms
#endif
OneWire *oneWire;
DallasTemperature *sensors;
uint8_t numSensors;
unsigned long lastOneWireRequestTime = 0;
#ifndef ONE_WIRE_REQUESTS_PERIOD
  #define ONE_WIRE_REQUESTS_PERIOD 25000 //sensors->requestTemperatures() calling period
#endif

#include "src/DHTesp/DHTesp.h"
DHTesp dht;
//Save state between queries
unsigned long DHT_Timer = 0;
int last_DHT_State = 0;
uint8_t last_DHT_pin = 0;

unsigned long maintenance_timer = millis();
unsigned long lastAvgTime = 0;
unsigned long lastLogTime = millis();
unsigned long lastMQTTTime = millis();
unsigned long custom_timer = millis();
unsigned long custom_timer_compare = 0;
float custom_floats[20] = { 0 };
long custom_longs[20] = { 0 };

static const int numLogValues = sizeof(log_parameters) / sizeof(log_parameters[0]);
static const int numCustomFloats = sizeof(custom_floats) / sizeof(custom_floats[0]);
static const int numCustomLongs = sizeof(custom_longs) / sizeof(custom_longs[0]);

static const int numAverages = (sizeof(avg_parameters) / sizeof(avg_parameters[0]));
float avgValues_Old[numAverages] = {0};
float avgValues[numAverages] = {0};
float avgValues_Current[numAverages] = {0};
int avgCounter = 1;
int loopCount = 0;

byte config_level = 0;
byte monitor = 0;     // Bus monitor mode. This is only necessary for in-depth debug sessions.

struct decodedTelegram_t {
//Commented fields for future use
int cat; //category number
float prognr; //program number
uint32_t cmd; // Command ID
uint_farptr_t catdescaddr; //category description string address
uint_farptr_t prognrdescaddr; //prognr description string address
uint_farptr_t enumdescaddr; //enum description string address
uint_farptr_t enumstr; //address of first element of enum
uint_farptr_t progtypedescaddr; //program type description string address
uint_farptr_t data_type_descaddr; //data type description DT_*, dt_types_text[?].type_text
uint16_t enumstr_len;  //enum length
uint16_t error; //0 - ok, 7 - parameter not supported, 1-255 - LPB/BSB bus errors, 256 - decoding error, 257 - unknown command, 258 - not found, 259 - no enum str, 260 - unknown type, 261 - query failed, 262 - Too few/many arguments in SET command, 263 - invalid category
uint8_t msg_type; //telegram type
uint8_t src_addr; //telegram address
uint8_t dest_addr; //telegram address
uint16_t flags; //flags
uint8_t readwrite; // 0 - read/write, 1 - read only, 2 - write only
uint8_t isswitch; // 0 - Any type, 1 - ONOFF or YESNO type
uint8_t type; //prog type (cmdtbl[].type). VT_*
uint8_t data_type; //data type DT_*, optbl[?].data_type
uint8_t precision;//optbl[?].precision
uint8_t enable_byte;//optbl[?].enable_byte
uint8_t payload_length;//optbl[?].payload_length
uint8_t payload[33];
uint8_t sensorid; //id of external (OneWire, DHT, BME, MAX!) sensor for virtual programs. Must be zero for real program numbers.
// uint8_t unit_len;//optbl[?].unit_len. internal variable
float operand; //optbl[?].operand
char value[64]; //decoded value from telegram to string
char unit[32]; //unit of measurement. former char div_unit[32];
char *telegramDump; //Telegram dump for debugging in case of error. Dynamic allocation is big evil for MCU but allow to save RAM
} decodedTelegram;

uint8_t my_dev_fam = DEV_FAM(DEV_NONE);
uint8_t my_dev_var = DEV_VAR(DEV_NONE);
uint32_t my_dev_serial = 0;
uint8_t default_flag = DEFAULT_FLAG;  // necessary for ESP32 SDK 2.0.4 and above to prevent tautological-compare errors


// variables for handling of broadcast messages
int brenner_stufe = 0;
unsigned long brenner_start   = 0;
unsigned long brenner_start_2   = 0;
unsigned long brenner_duration= 0;
unsigned long brenner_duration_2= 0;
unsigned long brenner_count   = 0;
unsigned long brenner_count_2   = 0;
unsigned long TWW_start   = 0;
unsigned long TWW_duration= 0;
unsigned long TWW_count   = 0;

// PPS-bus variables
uint8_t msg_cycle = 0;
uint8_t saved_msg_cycle = 0;
int16_t pps_values[PPS_ANZ] = { 0 };
uint8_t allow_write_pps_values[PPS_ANZ/8 + 1] = { 0 }; //Bitwise array. 0 - pps_values[] writing to EEPROM now allowed. 1 - allowed to write
bool pps_time_received = false;
bool pps_time_set = false;
bool pps_wday_set = false;
uint8_t current_switchday = 0;
unsigned long pps_mcba_timer = millis();

#include "BSB_LAN_EEPROMconfig.h"

static uint16_t baseConfigAddrInEEPROM = 0; //offset from start address in EEPROM

#include "include/eeprom_io.h"

#include "json-api-version.h"
#include "bsb-version.h"
const char BSB_VERSION[] = MAJOR "." MINOR "." PATCH "-" COMPILETIME;

#ifdef CUSTOM_COMMANDS
#include "BSB_LAN_custom_global.h"
#endif

/* ******************************************************************
 *      ************** Program code starts here **************
 * *************************************************************** */

#ifdef WATCH_SOCKETS

byte socketStat[MAX_SOCK_NUM];
unsigned long connectTime[MAX_SOCK_NUM];

#include <utility/w5100.h>
//#include <utility/socket.h>

void ShowSockStatus()
{
  for (int i = 0; i < MAX_SOCK_NUM; i++) {
    printFmtToDebug("Socket#%d", i);
    SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
    uint8_t s = W5100.readSnSR(i);
    SPI.endTransaction();
    socketStat[i] = s;
    printFmtToDebug(":0x%02X %d D:", s, W5100.readSnPORT(i));
    uint8_t dip[4];
    SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
    W5100.readSnDIPR(i, dip);
    SPI.endTransaction();
    SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
    printFmtToDebug("%d.%d.%d.%d(%d)\r\n", dip[0], dip[1], dip[2], dip[3], W5100.readSnDPORT(i));
    SPI.endTransaction();
  }
}

void checkSockStatus()
{
  unsigned long thisTime = millis();

  for (int i = 0; i < MAX_SOCK_NUM; i++) {
    SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
    uint8_t s = W5100.readSnSR(i);
    SPI.endTransaction();

    if ((s == 0x14) || (s == 0x1C)) {
        if (thisTime - connectTime[i] > 30000UL) {
          printFmtToDebug("\r\nSocket frozen: %d\r\n", i);
          SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
          W5100.execCmdSn(s, Sock_DISCON);
          SPI.endTransaction();

          printlnToDebug("Socket freed.");
          ShowSockStatus();
        }
    } else {
      connectTime[i] = thisTime;
    }
    SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
    socketStat[i] = W5100.readSnSR(i);
    SPI.endTransaction();
  }
}

#endif

void initStringBuffer(StringBuffer* sb, char* buf, size_t bufSize) {
    sb->buffer = buf;
    sb->size = bufSize;
    sb->currentLength = strlen(buf); // Initialize current length
}

/*
void logParameter(const char* format, va_list args) {
    for (const char* p = format; *p; p++) {
        if (*p != '%') {
            continue; // Not a format specifier, skip
        }
        switch (*++p) { // Check the next character to determine the type
            case 's': { // String
                char* str = va_arg(args, char*);
                printf("String: %s\n", str);
                break;
            }
            case 'd': { // Integer
                int val = va_arg(args, int);
                printf("Integer: %d\n", val);
                break;
            }
            case 'f': { // Float (note: 'float' is promoted to 'double' when passed through '...')
                double dbl = va_arg(args, double);
                printf("Float: %f\n", dbl);
                break;
            }
        }
    }
}
*/

void appendStringBuffer(StringBuffer* sb, const char* format, ...) {
    va_list args;
/*
    va_start(args, format);

    // Log parameters
    logParameter(format, args);

    // Reset va_list for the actual appending
    va_end(args);
*/
    va_start(args, format);

    size_t remainingSpace = sb->size - sb->currentLength; // Calculate remaining space
    // Use vsnprintf with calculated current length and remaining space
    int charsWritten = vsnprintf(sb->buffer + sb->currentLength, remainingSpace, format, args);
    if (charsWritten > 0) {
        sb->currentLength += (size_t)charsWritten > remainingSpace ? remainingSpace : (size_t)charsWritten;
    }
    va_end(args);
}

int char2int(char input)
{
  if(input >= '0' && input <= '9')
    return input - '0';
  input |= 0x20; //to lower case
  if(input >= 'a' && input <= 'f')
    return input - 'a' + 10;
  return 0;
}

/* Functions for management "Ring" debug buffer */
#include "include/print2debug.h"
/* Functions for management "Ring" output buffer */
#include "include/print2webclient.h"

// This function will extract parameter number and destination address from string like xxxxx[!yyy],[xxxxx[!yyy][,...]]
parameter parsingStringToParameter(char *data){
  parameter param;
  param.number = atof(data); // convert until non-digit char is found
  param.dest_addr = -1;
  char* token = strchr(data, '!');
  if (token != NULL) {
    token++;
    if (token[0] > 0) {
      param.dest_addr = atoi(token);
    }
  }
  return param;
}

void printHTTPheader(uint16_t code, int mimetype, bool addcharset, bool isGzip, bool isDownload, long cachingTime) {
  const char *getfarstrings;
  long autoDetectCachingTime = 590800; // 590800 = 7 days. If -1 then no-cache, no-store etc.
  printFmtToWebClient("HTTP/1.1 %d ", code);
  switch (code) {
    case HTTP_OK: printToWebClient("OK"); break;
    case HTTP_NOT_MODIFIED: printToWebClient("Not Modified"); break;
    case HTTP_AUTH_REQUIRED: printToWebClient("Authorization Required"); break;
    case HTTP_NOT_FOUND: printToWebClient("Not Found"); break;
    default: break;
  }
  printToWebClient("\r\nContent-Type: "); // 17 bytes with zero
  switch (mimetype) {
    case MIME_TYPE_TEXT_HTML: getfarstrings = "text/html"; break;
    case MIME_TYPE_TEXT_CSS: getfarstrings = "text/css"; break;
    case MIME_TYPE_APP_JS: getfarstrings = "application/x-javascript"; break;
    case MIME_TYPE_APP_XML: getfarstrings = "application/xml"; autoDetectCachingTime = HTTP_DO_NOT_CACHE; break;
    // case 5 below
    case MIME_TYPE_APP_JSON: getfarstrings = "application/json"; autoDetectCachingTime = HTTP_DO_NOT_CACHE; break;
    case MIME_TYPE_TEXT_PLAIN: getfarstrings = "text/plain"; autoDetectCachingTime = 60; break;
    case MIME_TYPE_IMAGE_JPEG: getfarstrings = "image/jpeg"; break;
    case MIME_TYPE_IMAGE_GIF: getfarstrings = "image/gif"; break;
    case MIME_TYPE_IMAGE_SVG: getfarstrings = "image/svg+xml"; break;
    case MIME_TYPE_IMAGE_PNG: getfarstrings = "image/png"; break;
    case MIME_TYPE_IMAGE_ICON: getfarstrings = "image/x-icon"; autoDetectCachingTime = 2592000; break; // 30 days
    case MIME_TYPE_APP_GZ: getfarstrings = "application/x-gzip"; break;
    case MIME_TYPE_FORCE_DOWNLOAD: getfarstrings = "application/force-download"; autoDetectCachingTime = HTTP_DO_NOT_CACHE; break;
    case MIME_TYPE_TEXT_TEXT:
    default: getfarstrings = "text"; autoDetectCachingTime = 60; break;
  }
  printToWebClient(getfarstrings);
  if (cachingTime == HTTP_AUTO_CACHE_AGE)cachingTime = autoDetectCachingTime;
  if (addcharset)printToWebClient("; charset=utf-8");
  printToWebClient("\r\n");
  if (isGzip) printToWebClient("Content-Encoding: gzip\r\n");
  printToWebClient("Cache-Control: ");
  if (cachingTime > 0) {
    //max-age=84400 = one day, max-age=590800 = 7 days, max-age=2592000 = 30 days.
    printFmtToWebClient("max-age=%ld, public", cachingTime);
  } else {
    printToWebClient("no-cache, no-store, must-revalidate\r\nPragma: no-cache\r\nExpires: 0");
  }
  printToWebClient("\r\n");
  if (isDownload) {
    printToWebClient("Content-Disposition: attachment; filename=\"BSB-LAN-");
    printFmtToWebClient("%03u-%03u-%u.txt\"\r\n", my_dev_fam, my_dev_var, my_dev_serial);
  }
}


int recognize_mime(char *str) {
//        if (strlen(dot)) {
  char mimebuf[64];
  int i = 0;
  int mimetype = 0;
  if (!str) return mimetype;

  strncpy(mimebuf, str, sizeof(mimebuf));

  while (mimebuf[i]) {
    mimebuf[i] |= 0x20; //to lower case
    i++;
  }

  if (!strcmp(mimebuf, "html") || !strcmp(mimebuf, "htm")) mimetype = MIME_TYPE_TEXT_HTML;
  else if (!strcmp(mimebuf, "css")) mimetype = MIME_TYPE_TEXT_CSS;
  else if (!strcmp(mimebuf, "js")) mimetype = MIME_TYPE_APP_JS;
  else if (!strcmp(mimebuf, "xml")) mimetype = MIME_TYPE_APP_XML;
  else if (!strcmp(mimebuf, "txt")) mimetype = MIME_TYPE_TEXT_TEXT;
  else if (!strcmp(mimebuf, "jpg")) mimetype = MIME_TYPE_IMAGE_JPEG;
  else if (!strcmp(mimebuf, "gif")) mimetype = MIME_TYPE_IMAGE_GIF;
  else if (!strcmp(mimebuf, "svg")) mimetype = MIME_TYPE_IMAGE_SVG;
  else if (!strcmp(mimebuf, "png")) mimetype = MIME_TYPE_IMAGE_PNG;
  else if (!strcmp(mimebuf, "ico")) mimetype = MIME_TYPE_IMAGE_ICON;
  else if (!strcmp(mimebuf, "gz")) mimetype = MIME_TYPE_APP_GZ;
//          else mimetype = 0;
  // You can add more MIME types here
  return mimetype;
}


void setBusType() {
  switch (bus_type) {
    default:
    case BUS_BSB:
    case BUS_LPB:  bus->setBusType(bus_type, own_address, dest_address); break;
    case BUS_PPS:  bus->setBusType(bus_type, pps_write); break;
  }
}

/** *****************************************************************
 *  Function: dayofweek()
 *  Does:     Accepts a date as day / month / year and calculates
 *            the day of the week for this day.
 *            1=Monday, .. , 7=Sunday
 *            No sanity checks are performed on the pass parameters.
 * Pass parameters:
 *  uint8  day    1 .. 31
 *  uint8  month  1 .. 12
 *  uint16 year
 * Parameters passed back:
 *  none
 * Function value returned:
 *  day-of-week [1-7]
 * Global resources used:
 *  none
 * *************************************************************** */

int dayofweek(uint8_t day, uint8_t month, uint16_t year)
{
   /** Zeller's congruence for the Gregorian calendar. **/
   /** With 1=Monday, ... 5=Saturday, 7=Sunday         **/
   if (month < 3) {
      month += 12;
      year--;
   }
   return (((13*month+3)/5 + day + year + year/4 - year/100 + year/400) % 7) + 1;
}

/** *****************************************************************
 *  Function: listEnumValues()
 *  Does:     Print to web client list of values and descriptions from enum
* Pass parameters:
uint_farptr_t enumstr - ENUM address
uint16_t enumstr_len - ENUM length
const char *prefix - print string before enum element
 const char *delimiter - print string between value and description
 const char *alt_delimiter - alternative delimiter. see below.
 const char *suffix - print string after  enum element
 const char *string_delimiter - if string_delimiter is set, string_delimiter will be print between enum elements
 uint16_t value - if alt_delimiter is set then alt_delimiter will be print when "value" will be found in enum
 uint8_t print_mode. 0 - print nothing, 1 - print value, 2 - print description, 4 - print value first and description then, 8 - print description first and value then, 16 - print suitable for "value" line only, 32 - it is DT_BITS enum
 bool canBeDisabled - if true, then "---" value will be print

 * Parameters passed back:
 *  none
 * Function value returned:
 *  none
 * Global resources used:
 *  none
 * *************************************************************** */
void listEnumValues(uint_farptr_t enumstr, uint16_t enumstr_len, const char *prefix, const char *delimiter, const char *alt_delimiter, const char *suffix, const char *string_delimiter, uint16_t value, uint8_t print_mode) {
  uint16_t val = 0;
  uint16_t c=0;
  uint8_t bitmask=0;
  bool isFirst = true;
  if (decodedTelegram.type == VT_CUSTOM_BIT) c++;  // first byte of VT_CUSTOM_BIT enumstr contains index to payload

  while (c + 2 < enumstr_len) {
    uint_farptr_t descAddr;
    if ((decodedTelegram.type == VT_ENUM || decodedTelegram.isswitch == true) && (decodedTelegram.enable_byte > 1 || decodedTelegram.payload[0] == 0x01) && isFirst == true) {
      val = 65535;
      value = 65535;
      descAddr = STR_DISABLED;
    } else {
      if ((byte)(pgm_read_byte_far(enumstr+c+2))==' ') { // ENUMs must not contain two consecutive spaces! Necessary because VT_BIT bitmask may be 0x20 which equals space
        val = uint16_t(pgm_read_byte_far(enumstr+c+1));
        if (decodedTelegram.type != VT_CUSTOM_ENUM) val |= uint16_t((pgm_read_byte_far(enumstr+c) << 8));
        if (print_mode & PRINT_ENUM_AS_DT_BITS) { //decodedTelegram.data_type is DT_BITS
          bitmask = val & 0xff;
          val = val >> 8 & 0xff;
        }
        c++;
      } else if ((byte)(pgm_read_byte_far(enumstr+c+1))==' ') {
        val=uint16_t(pgm_read_byte_far(enumstr+c));
      }
      //skip leading space
      c+=2;
      if ((print_mode & PRINT_ONLY_VALUE_LINE) && val != value) {
        while(c < enumstr_len){
          if ((byte)(pgm_read_byte_far(enumstr+c)) == '\0'){
            break;
          }
          c++;
        }
        continue;
      }
      descAddr = enumstr + c;
    }

    if (isFirst) {isFirst = false;} else {if (string_delimiter) printToWebClient(string_delimiter);}
    if (prefix) printToWebClient(prefix);

    if (print_mode & PRINT_DESCRIPTION && print_mode & PRINT_DESCRIPTION_FIRST) {
      c += printToWebClient(descAddr) + 1;
      //                      All enums except DT_BITS                                         DT_BITS  enums
      if (alt_delimiter && ((value == val && !(print_mode & PRINT_ENUM_AS_DT_BITS)) || ((value & bitmask) == (val & bitmask) && (print_mode & PRINT_ENUM_AS_DT_BITS)))) {
        printToWebClient(alt_delimiter);
      } else {
        if (delimiter) printToWebClient(delimiter);
      }
    }
    if (print_mode & PRINT_VALUE) printFmtToWebClient("%u", val);
    if (print_mode & PRINT_DESCRIPTION && print_mode & PRINT_VALUE_FIRST) {
      //                      All enums except DT_BITS                                               DT_BITS  enums
      if (alt_delimiter && ((value == val && !(print_mode & PRINT_ENUM_AS_DT_BITS)) || ((value & bitmask) == (val & bitmask) && (print_mode & PRINT_ENUM_AS_DT_BITS)))) {
        printToWebClient(alt_delimiter);
      } else {
        if (delimiter) printToWebClient(delimiter);
      }
      c += printToWebClient(descAddr) + 1;
    }
    if (suffix) printToWebClient(suffix);
    if (descAddr == STR_DISABLED) c = 0;
  }
}

inline uint8_t get_cmdtbl_category(int i) {
  int cat_min = 0;
  int cat_max = 0;
  for (uint cat=0;cat<CAT_UNKNOWN;cat++) {
    printKat(cat, 0, false);
    if (decodedTelegram.error != 258 && decodedTelegram.error != 263) {
      cat_min = ENUM_CAT_NR[cat*2];
      cat_max = ENUM_CAT_NR[cat*2+1];
/*
    if (cat*2+2 < sizeof(ENUM_CAT_NR)/sizeof(*ENUM_CAT_NR)) { // only perform category boundary check if there is a higher category present
      if (cat_max > ENUM_CAT_NR[cat*2+2]) {
        cat_max = ENUM_CAT_NR[cat*2+2]-1;
      }
    }
*/
      if (cmdtbl[i].line >= cat_min && cmdtbl[i].line < cat_max+1) {
        return cat;
      }
    }
  }
  return 0;
//  return cmdtbl[i].category;
}

void set_temp_destination(int16_t destAddr){
  if (destAddr == -1) {
    destAddr = dest_address;
  }
  if (destAddr != bus->getBusDest()) {
    printFmtToDebug("Setting temporary destination to %d\r\n", destAddr);
    bus->setBusType(bus->getBusType(), bus->getBusAddr(), destAddr);
    GetDevId();
  } else {
    if (debug_mode == DEVELOPER_DEBUG) {
      printFmtToDebug("Bus destination already set to %d, no change necessary.\r\n", destAddr);
    }
  }
}

void return_to_default_destination(int destAddr){
  if (destAddr != bus->getBusDest()) {
    printFmtToDebug("Returning to default destination %d\r\n", destAddr);
    bus->setBusType(bus->getBusType(), bus->getBusAddr(), destAddr);
  } else {
    if (debug_mode == DEVELOPER_DEBUG) {
      printFmtToDebug("Bus destination already set to %d, no change necessary.\r\n", destAddr);
    }
  }
}

/** *****************************************************************
 *  Function:  recognizeVirtualFunctionGroup(uint16_t)
 *  Does:      Calculate and return virtual function "group id"
 *             for code readability
 *  Pass parameters:
 *   uint16_t nr - program number
 *  Parameters passed back:
 *   none
 *  Function value returned:
 *   "group"
 * Global resources used:
 *   none
 * *************************************************************** */
uint8_t recognizeVirtualFunctionGroup(float nr) {
  if (nr >= (float)BSP_INTERNAL && nr < (float)BSP_INTERNAL+7) { return 1;}
  else if (nr >= (float)BSP_AVERAGES && nr < (float)BSP_AVERAGES + numAverages) {return 2;} //20050 - 20099#endif
  else if (nr >= (float)BSP_DHT22 && nr < (float)BSP_DHT22 + sizeof(DHT_Pins) / sizeof(DHT_Pins[0])) {return 3;} //20100 - 20199
  else if (nr >= (float)BSP_BME280 && nr < (float)BSP_BME280 + BME_Sensors) {return 8;} //20200 - 20299
  else if (nr >= (float)BSP_ONEWIRE && nr < (float)BSP_ONEWIRE + (uint16_t)numSensors) {return 4;} //20300 - 20499
  else if (nr >= (float)BSP_MAX && nr < (float)BSP_MAX + MAX_CUL_DEVICES) {return 5;} //20500 - 20699
  else if (nr >= (float)BSP_FLOAT && nr < (float)BSP_FLOAT + numCustomFloats) {return 6;} //20700 - 20799
  else if (nr >= (float)BSP_LONG && nr < (float)BSP_LONG + numCustomLongs) {return 7;} //20800 - 20899
  return 0;
}

/** *****************************************************************
 *  Function: findLine()
 *  Does:     Scans the command table struct for a matching line
 *            number (ProgNr) and returns the command code.
 * Pass parameters:
 *  float  line     the requested match (ProgNr)
 *  uint16  startidx starting line (ProgNr) for search .
 *                   Works best if i>0 ;-)
 *  uint32 *cmd      pointer to 32-bit command code variable
 * Parameters passed back:
 *  uint32 *cmd      32-bit command code value filled in
 * Function value returned:
 *  -1        command (ProgNr) not found
 *   i >= 0   success, usable to index the matching table row
 * Global resources used:
 *  none
 * *************************************************************** */
int findLine(float line)
{
  uint8_t found = 0;
  int i = -1;
  int save_i = 0;
  uint32_t c;
  float l;
  if (verbose == DEVELOPER_DEBUG) printFmtToDebug("line = %.1f\r\n", line);

  //Virtual programs. do not forget sync changes with loadPrognrElementsFromTable()
  if (line >= (float)BSP_INTERNAL && line < (float)BSP_END) {
    switch (recognizeVirtualFunctionGroup(line)) {
      case 1: break;
      case 2: line = avg_parameters[(((uint16_t)line) - BSP_AVERAGES)].number; if (line == 0) return -1; else break;
      case 3: {
        if ((int8_t)DHT_Pins[(((uint16_t)line) - BSP_DHT22)] == -1) { //pin not assigned to DHT sensor
          return -1;
        } else {
#if defined(__SAM3X8E__)
          double intpart;
#else
          float intpart;
#endif
          line = (float)BSP_DHT22 + modf(line, &intpart);
        }
        break;
      }
      case 4: {
#if defined(__SAM3X8E__)
        double intpart;
#else
        float intpart;
#endif
        line = (float)BSP_ONEWIRE + modf(line, &intpart);
        break;
      }
      case 5:{
        if (max_device_list[((uint16_t)line) - BSP_MAX][0] == 0) {  //device not set
          return -1;
        } else {
#if defined(__SAM3X8E__)
          double intpart;
#else
          float intpart;
#endif
          line = (float)BSP_MAX + modf(line, &intpart);
        }
        break;
      }
      case 6: line = (float)BSP_FLOAT; break;
      case 7: line = (float)BSP_LONG; break;
      case 8: {
        if ((int)roundf(line - (float)BSP_BME280) < BME_Sensors) { //
#if defined(__SAM3X8E__)
          double intpart;
#else
          float intpart;
#endif
          line = (float)BSP_BME280 + modf(line, &intpart);
        } else {
          return -1;
        }
        break;
      }
      default: return -1;
    }
  }

  // binary search for the line in cmdtbl

  int line_dd = roundf(line * 10);
  for (uint16_t j=0;j<sizeof(cmdtbl)/sizeof(cmdtbl[0]) - 1;j++) {
    if (roundf(cmdtbl[j].line * 10) == line_dd) {
      i = j;
      break;
    }
  }
/*
  int left = start_idx;
  int right = (int)(sizeof(cmdtbl)/sizeof(cmdtbl[0]) - 1);
  int mid = 0;
  while (!(left >= right))
    {
    if (verbose == DEVELOPER_DEBUG) printFmtToDebug("get_cmdtbl_line: left = %f, line = %f\r\n", cmdtbl[left].line, line);
    if (roundf(cmdtbl[left].line * 10) == line_dd){ i = left; break; }
    mid = left + (right - left) / 2;
    int temp_dd = roundf(cmdtbl[mid].line * 10);
    if (verbose == DEVELOPER_DEBUG) {
      printFmtToDebug("get_cmdtbl_line integer: temp = %d, line = %d\r\n", temp_dd, line_dd);
      printFmtToDebug("get_cmdtbl_line: left = %.1f, mid = %.1f\r\n", cmdtbl[left].line, cmdtbl[mid].line);
    }
    if (temp_dd == line_dd) {
      if (mid == left + 1) {
            i = mid; break;
      } else {
        right = mid + 1;
      }
    } else if (temp_dd > line_dd) {
      right = mid;
    } else {
      left = mid + 1;
    }
    if (verbose == DEVELOPER_DEBUG) printFmtToDebug("left = %d, mid = %d, right = %d\r\n", left, mid, right);
  }
  if (verbose == DEVELOPER_DEBUG) printFmtToDebug("i = %d\r\n", i);
*/
  if (i == -1) return i;

  l = cmdtbl[i].line;
  while (l == line) {
    c = cmdtbl[i].cmd;
    uint8_t dev_fam = cmdtbl[i].dev_fam;
    uint8_t dev_var = cmdtbl[i].dev_var;
    uint16_t dev_flags = cmdtbl[i].flags;
    if (verbose == DEVELOPER_DEBUG) printFmtToDebug("l = %.1f, dev_fam = %d,  dev_var = %d, dev_flags = %d\r\n", l, dev_fam, dev_var, dev_flags);

    if ((dev_fam == my_dev_fam || dev_fam == DEV_FAM(DEV_ALL)) && (dev_var == my_dev_var || dev_var == DEV_VAR(DEV_ALL))) {
      if (dev_fam == my_dev_fam && dev_var == my_dev_var) {
        if ((dev_flags & FL_NO_CMD) == FL_NO_CMD) {
          while (c==cmdtbl[i].cmd) {
            i++;
          }
          found=0;
          i--;
        } else {
          found=1;
          save_i=i;
          break;
        }
      } else if ((!found && dev_fam!=my_dev_fam) || (dev_fam==my_dev_fam)) { // wider match has hit -> store in case of best match
        if ((dev_flags & FL_NO_CMD) == FL_NO_CMD) {
          while (c==cmdtbl[i].cmd) {
            i++;
          }
          found=0;
          i--;
        } else {
          found=1;
          save_i=i;
        }
      }
    }
    i++;
    l = cmdtbl[i].line;
  }

  if (!found) {
    return -1;
  }
  return save_i;
}

float get_next_prognr(float currentProgNr){
  int startFromTableLine = findLine(currentProgNr);

  if(startFromTableLine < 0) {    // Parameter does not exist? Then there is no same parameter with a decimal part, so skip to next integer
#if defined(__SAM3X8E__)
    double intpart;
#else
    float intpart;
#endif
    modf(currentProgNr, &intpart);
    return intpart + 1;
  }

  int cmdtblsize = sizeof(cmdtbl)/sizeof(cmdtbl[0]);
  float prognr = cmdtbl[startFromTableLine].line;
  float nextprognr = -1;
  if (verbose == DEVELOPER_DEBUG) printFmtToDebug("prognr: %.1f, startindex: %d\r\n", prognr, startFromTableLine);
  do{
    startFromTableLine++;
    if(cmdtblsize <= startFromTableLine) {
      if (verbose == DEVELOPER_DEBUG) printFmtToDebug("nextprognr: -1\r\n");
      return -1;
    }
    nextprognr = cmdtbl[startFromTableLine].line;
    if (verbose == DEVELOPER_DEBUG) printFmtToDebug("nextindex: %d\r\n", startFromTableLine);
  } while (prognr == nextprognr);
  if(currentProgNr >= (float)BSP_INTERNAL && currentProgNr < (float)BSP_END) {
    float prognrDiff = currentProgNr - prognr;
#if defined(__SAM3X8E__)
    double intpart1, intpart2;
#else
    float intpart1, intpart2;
#endif
    modf(prognr, &intpart1);
    modf(nextprognr, &intpart2);
    if(intpart1 == intpart2) {
      nextprognr += prognrDiff;
    } else {
      if(recognizeVirtualFunctionGroup(currentProgNr + 1)){
#if defined(__SAM3X8E__)
          double intpart;
#else
          float intpart;
#endif
        modf(currentProgNr, &intpart);
        nextprognr = intpart + 1;
      }
    }
  }
  if (verbose == DEVELOPER_DEBUG) printFmtToDebug("nextprognr: %.1f\r\n", nextprognr);
  return nextprognr;
}

/** *****************************************************************
 *  Function: freeRam()
 *  Does:     Returns the amount of available RAM
 *
 * *************************************************************** */
#if defined(__arm__)
extern "C" char* sbrk(int incr);
#endif
int freeRam () {
#ifdef ESP32
	return (int)ESP.getFreeHeap();
#else
  char top;
  return &top - reinterpret_cast<char*>(sbrk(0));
#endif
}

/** *****************************************************************
 *  Function:  SerialPrintData()
 *  Does:      Sends the payload of a telegram in hex to the PC
 *             hardware serial interface in hex.
 *  Pass parameters:
 *   byte *msg bus telegram with magic byte, header, payload and
 *             checksum
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *   Serial  instance
 * *************************************************************** */
void SerialPrintData(byte* msg) {
  // Calculate pure data length without housekeeping info
  int data_len=0;
  byte offset = 0;
  byte msg_type = msg[4+bus->offset];
  if (bus_type != BUS_PPS) {
    if (msg_type >= 0x12 && msg_type <= 0x15) {
      offset = 4;
    }
  }
  switch (bus->getBusType()) {
  case BUS_BSB: data_len=msg[bus->getLen_idx()]-11+offset; break;    // get packet length, then subtract
  case BUS_LPB: data_len=msg[bus->getLen_idx()]-14+offset; break;    // get packet length, then subtract
  case BUS_PPS: data_len=9; break;
  }
  // Start indexing where the payload begins
  SerialPrintRAW(msg + bus->getPl_start() - offset, data_len);
}

/** *****************************************************************
 *  Function:  SerialPrintRAW()
 *  Does:      Sends the telegram content in hex to the PC hardware
 *             serial interface, starting at position null. It stops
 *             when it has sent the requested number of message bytes.
 *             WARNING: this routine does not perform a sanity check
 *             of the length pass parameter.
 *  Pass parameters:
 *   byte *msg pointer to the telegram buffer
 *   byte len  the requested number of bytes to send.
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   Serial  instance
 * *************************************************************** */
void SerialPrintRAW(byte* msg, byte len) {
  int outBufLen = strlen(outBuf);
  bin2hex(outBuf + outBufLen, msg, len, ' ');
  printToDebug(outBuf + outBufLen);
  outBuf[outBufLen] = 0;
}

void EEPROM_dump() {
  if ((debug_mode == 1 || haveTelnetClient) && EEPROM_ready) {
    printlnToDebug("EEPROM dump:");
    for (uint16_t x=0; x<EEPROM_SIZE; x++) {
      printFmtToDebug("%02X ", EEPROM.read(x));
    }
  }
}

bool programIsreadOnly(uint16_t param_len) {
  if ((default_flag & FL_SW_CTL_RONLY) == FL_SW_CTL_RONLY) { //software-controlled
    switch (programWriteMode) {
      case 0: return true; //All read-only.
      case 1: if ((param_len & FL_OEM) == FL_OEM || ((param_len & FL_RONLY) == FL_RONLY && (default_flag & FL_RONLY) != FL_RONLY)) return true; else return false; //All writable except read-only and OEM
      case 2: if ((param_len & FL_RONLY) == FL_RONLY) return true; else return false; //All writable except read-only
    }
  } else { //defs-controlled.
    if ((param_len & FL_RONLY) == FL_RONLY) return true;
  }
  return false;
}

 /** *****************************************************************
  *  Function:  loadPrognrElementsFromTable(int, int)
  *  Does:      Get flags and data from tables and fill with this data
  *             decodedTelegram structure.
  *             Always called in query();. User can call the function when need it
  *  Pass parameters:
  *   int nr - program number
  *   int i - program line
  * Parameters passed back:
  *   none
  * Function value returned:
  *   none
  * Global resources used:
  *   decodedTelegram
  * *************************************************************** */
void loadPrognrElementsFromTable(float nr, int i) {
  if (i<0) i = findLine(19999); // Using "Unknown command" if not found
  decodedTelegram.cmd = cmdtbl[i].cmd;
  decodedTelegram.prognrdescaddr = cmdtbl[i].desc;
  decodedTelegram.type = cmdtbl[i].type;
  decodedTelegram.cat=get_cmdtbl_category(i);
  decodedTelegram.enumstr_len=cmdtbl[i].enumstr_len;
  decodedTelegram.enumstr = cmdtbl[i].enumstr;
  decodedTelegram.flags=cmdtbl[i].flags;
  if (programIsreadOnly(decodedTelegram.flags)) {
    decodedTelegram.readwrite = FL_RONLY; //read only
  } else if ((decodedTelegram.flags & FL_WONLY) == FL_WONLY) {
    decodedTelegram.readwrite = FL_WONLY; //write only
    decodedTelegram.prognr = nr;
  } else {
    decodedTelegram.readwrite = FL_WRITEABLE; //read/write
  }
  decodedTelegram.data_type=optbl[decodedTelegram.type].data_type;
  decodedTelegram.operand=optbl[decodedTelegram.type].operand;
  decodedTelegram.precision=optbl[decodedTelegram.type].precision;
  decodedTelegram.enable_byte=optbl[decodedTelegram.type].enable_byte;
  decodedTelegram.payload_length=optbl[decodedTelegram.type].payload_length;
  memcpy(decodedTelegram.unit, optbl[decodedTelegram.type].unit, optbl[decodedTelegram.type].unit_len);
  decodedTelegram.progtypedescaddr = optbl[decodedTelegram.type].type_text;
  decodedTelegram.data_type_descaddr = dt_types_text[decodedTelegram.data_type].type_text;

  if (decodedTelegram.type == VT_BINARY_ENUM || decodedTelegram.type == VT_ONOFF || decodedTelegram.type == VT_YESNO|| decodedTelegram.type == VT_CLOSEDOPEN || decodedTelegram.type == VT_VOLTAGEONOFF) {
    decodedTelegram.isswitch = 1;
  } else {
    decodedTelegram.isswitch = 0;
  }

  decodedTelegram.sensorid = 0;
  if (nr >= (float)BSP_INTERNAL) { //Virtual programs. do not forget sync changes with findline()
    decodedTelegram.prognr = nr;
    switch (recognizeVirtualFunctionGroup(nr)) {
      case 1: break;
      case 2: decodedTelegram.cat = CAT_USERSENSORS; decodedTelegram.readwrite = FL_RONLY; break; //overwrite native program categories with CAT_USERSENSORS
      case 3: decodedTelegram.sensorid = nr - (float)BSP_DHT22 + 1; break;
      case 4: decodedTelegram.sensorid = nr - (float)BSP_ONEWIRE + 1; break;
      case 5: decodedTelegram.sensorid = nr - (float)BSP_MAX + 1; break;
      case 6: decodedTelegram.sensorid = nr - (float)BSP_FLOAT + 1; break;
      case 7: decodedTelegram.sensorid = nr - (float)BSP_LONG + 1; break;
      case 8: decodedTelegram.sensorid = nr - (float)BSP_BME280 + 1; break;
    }
  }
}

// calling in every printTelegram()
void resetDecodedTelegram() {
  decodedTelegram.prognr = -1;
  decodedTelegram.cat = -1;
  decodedTelegram.catdescaddr = 0;
  decodedTelegram.prognrdescaddr = 0;
  decodedTelegram.enumdescaddr = 0;
  decodedTelegram.progtypedescaddr = 0;
  decodedTelegram.type = 0;
  decodedTelegram.data_type = 0;
  decodedTelegram.data_type_descaddr = 0;
//  decodedTelegram.unit_len = 0;
  decodedTelegram.precision = 1;
  decodedTelegram.enable_byte = 0;
  decodedTelegram.payload_length = 0;
  decodedTelegram.payload[0] = 0;
  decodedTelegram.error = 0;
  decodedTelegram.readwrite = FL_WRITEABLE;
  decodedTelegram.isswitch = 0;
  decodedTelegram.value[0] = 0;
  decodedTelegram.unit[0] = 0;
  decodedTelegram.enumstr_len = 0;
  decodedTelegram.enumstr = 0;
  decodedTelegram.msg_type = 0;
  decodedTelegram.src_addr = 0;
  decodedTelegram.dest_addr = 0;
  decodedTelegram.operand = 1;
  decodedTelegram.sensorid = 0;
  if (decodedTelegram.telegramDump) {free(decodedTelegram.telegramDump); decodedTelegram.telegramDump = NULL;} //free memory before new telegram
}
/** *****************************************************************
 *  Function:  TranslateAddr()
 *  Does:      Returns human-readable device names
 *             selected by a device address.
 *             If the device number is not in the list of known
 *             addresses, return the number itself.
 *
 * Pass parameters:
 *   byte addr the Int8 address value for which we seek the device
 *             name; values GT 127 are mapped to 0 <= addr <= 127
 * Parameters passed back:
 *   none
 * Function value returned:
 *   device string
 * Global resources used:
 *   none
 * *************************************************************** */
char *TranslateAddr(byte addr, char *device) {
  const char *p = NULL;
  switch (addr & 0x7F) {
    case ADDR_HEIZ: p = "HEIZ"; break;
    case ADDR_EM1: p = "EM1"; break;
    case ADDR_EM2: p = "EM2"; break;
    case ADDR_RGT1: p = "RGT1"; break;
    case ADDR_RGT2: p = "RGT2"; break;
    case ADDR_RGT3: p = "RGT3"; break;
    case ADDR_SRVC: p = "SRVC"; break;
    case ADDR_DSP1: p = "DSP1"; break;
    case ADDR_DSP2: p = "DSP2"; break;
    case ADDR_DSP3: p = "DSP3"; break;
    case ADDR_LAN: p = "LAN"; break;
    case ADDR_OZW: p = "OZW"; break;
    case ADDR_FUNK: p = "FUNK"; break;
    case ADDR_RC: p = "REMO"; break;
    case ADDR_ALL: p = "ALL "; break;
    default: bin2hex(device, &addr, 1, 0); break;
  }
  if (p) strcpy(device, p);
  device[4] = 0;
  return device;
}

/** *****************************************************************
 *  Function:  SerialPrintAddr()
 *  Does:      Sends human-readable device names to the PC hardware
 *             serial interface, selected by a device address.
 *             If the device number is not in the list of known
 *             addresses, send the number itself.
 *
 * Pass parameters:
 *   byte addr the Int8 address value for which we seek the device
 *             name; values GT 127 are mapped to 0 <= addr <= 127
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   Serial  instance
 * *************************************************************** */
void SerialPrintAddr(byte addr) {
  char device[5];
  printToDebug(TranslateAddr(addr, device));
}

/** *****************************************************************
 *  Function:  bin2hex()
 *  Does:      Convert binary date to human-readable HEX codes
 *
 * Pass parameters:
 *   char *toBuffer - address of result buffer
 *   byte *fromAddr - address of source Array
 *   int len - source array size
 *   char delimiter - character for HEX codes delimition. If delimiter == 0 then delimiter will not print to buffer.
 * Parameters passed back:
 *   char *toBuffer
 * Function value returned:
 *   result length
 * Global resources used:
 *   none
 * *************************************************************** */
int bin2hex(char *toBuffer, byte *fromAddr, int len, char delimiter){
  int resultLen = 0;
  bool isNotFirst = false;
  for (int i = 0; i < len; i++) {
    if(isNotFirst) {
      if(delimiter != 0) {
        toBuffer[resultLen] = delimiter;
        resultLen++;
      }
    } else {
      isNotFirst = true;
    }
    resultLen += sprintf_P(toBuffer + resultLen, "%02X", fromAddr[i]);
  }
  return resultLen;
}

/** *****************************************************************
 *  Function:  TranslateType()
 *  Does:      Returns the message type in human-readable form.
 *  Pass parameters:
 *   byte type a number which indicates the type
 * Parameters passed back:
 *   none
 * Function value returned:
 *   message type
 * Global resources used:
 *   none
 * *************************************************************** */
char *TranslateType(byte type, char *mtype) {
  const char *p = NULL;
  if (type > 0x20) {
    type = type & 0x0F;
  }
  switch (type) {
    case TYPE_QINF: p = "QINF"; break;
    case TYPE_INF: p = "INF"; break;
    case TYPE_SET: p = "SET"; break;
    case TYPE_ACK: p = "ACK"; break;
    case TYPE_NACK: p = "NACK"; break;
    case TYPE_QUR: p = "QUR"; break;
    case TYPE_ANS: p = "ANS"; break;
    case TYPE_QRV: p = "QRV"; break;
    case TYPE_ARV: p = "ARV"; break;
    case TYPE_ERR: p = "ERR"; break;
    case TYPE_QRE: p = "QRE"; break;
    case TYPE_IQ1: p = "IQ1"; break;
    case TYPE_IA1: p = "IA1"; break;
    case TYPE_IQ2: p = "IQ2"; break;
    case TYPE_IA2: p = "IA2"; break;
    // If no match found: print the hex value
    default: bin2hex(mtype, &type, 1, 0); break;
  } // endswitch
  if (p) strcpy(mtype, p);
  mtype[4] = 0;
  return mtype;
}

/** *****************************************************************
 *  Function:  SerialPrintType()
 *  Does:      Prints the message type in human-readable form.
 *  Pass parameters:
 *   byte type a number which indicates the type
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   Serial    the hardware serial interface to a PC
 * *************************************************************** */
void SerialPrintType(byte type) {
  char device[5];
  printToDebug(TranslateType(type, device));
} // --- SerialPrintType() ---

/** *****************************************************************
 *  Function: prepareToPrintHumanReadableTelegram
 *  Does: copy telegram in human-readable format into buffer
 *  Pass parameters: msg, data_len, shift
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void prepareToPrintHumanReadableTelegram(byte *msg, byte data_len, int shift) {
  SerialPrintData(msg);
  decodedTelegram.telegramDump = (char *) malloc(data_len * 2 + 1); //two chars per telegram byte + zero
  if (decodedTelegram.telegramDump) {
    bin2hex(decodedTelegram.telegramDump, msg + shift, data_len, 0);
  } else {
    printlnToDebug("Can't alloc memory");
  }
}

/** *****************************************************************
 *  Function: undefinedValueToBuffer
 *  Does: copy undefined (---) value into buffer
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
int undefinedValueToBuffer(char *p) {
  strcpy(p, STR_DISABLED);
  return 3;
}

void printPassKey(void) {
  if (PASSKEY[0]) {
    printToWebClient(PASSKEY);
    printToWebClient("/");
  }
}

/** *****************************************************************
 *  Function: printyesno
 *  Does: print HTML yes or no
 *  Pass parameters:
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   client variable
 * *************************************************************** */
void printyesno(bool i) {
  if (i) {
    printToWebClient(MENU_TEXT_YES "<BR>");
  } else {
    printToWebClient(MENU_TEXT_NO "<BR>");
  }
  printToWebClient("\r\n");
}

/** *****************************************************************
 *  Function: printDebugValueAndUnit
 *  Does: debug output
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
 void printDebugValueAndUnit(char *p1, char *p2) {
   printToDebug(p1);
   if (p2[0] != 0) {
     printFmtToDebug(" %s", p2);
   }
}

/** *****************************************************************
 *  Function: remove_char()
 *  Does:     Removes a character from a given char array
 * Pass parameters:
 *  str, c
 * Parameters passed back:
 *  none
 * Function value returned:
 *  none
 * Global resources used:
 *  none
 * *************************************************************** */

void remove_char(char* str, char c) {
  char *pr = str, *pw = str;
  while (*pr) {
    *pw = *pr++;
    pw += (*pw != c);
  }
  *pw = '\0';
}

void resetDurations() {
  brenner_duration=0;
  brenner_count=0;
  brenner_duration_2=0;
  brenner_count_2=0;
  TWW_duration=0;
  TWW_count=0;
}

#include "include/print_telegram.h"
#include "include/mqtt_handler.h"


/** *****************************************************************
 *  Function: UpdateMaxDeviceList()
 *  Does:     Reads the MAX! device list serial numbers and populates a reference list with the internal IDs
 * Pass parameters:
 *  none
 * Parameters passed back:
 *  none
 * Function value returned:
 *  none
 * Global resources used:
 *  max_device_list, max_devices
 * *************************************************************** */

void UpdateMaxDeviceList() {
  char max_id_eeprom[sizeof(max_device_list[0])] = { 0 };
  int32_t max_addr = 0;
  for (uint16_t z = 0; z < MAX_CUL_DEVICES; z++) {
    max_devices[z] = 0; //clearing old MAX! device address for avoiding doublettes
  }

  for (uint16_t z = 0; z < MAX_CUL_DEVICES; z++) {
    if (EEPROM_ready) {
      for (uint16_t i = 0; i < sizeof(max_id_eeprom); i++) {
        max_id_eeprom[i] = EEPROM.read(getEEPROMaddress(CF_MAX_DEVICES) + sizeof(max_id_eeprom) * z + i);
      }
    }
    for (uint16_t x = 0; x < MAX_CUL_DEVICES; x++) {
      if (!memcmp(max_device_list[x], max_id_eeprom, sizeof(max_id_eeprom))) {
        if (EEPROM_ready) {
          for (uint16_t i = 0; i < sizeof(max_addr); i++) {
           ((char *)&max_addr)[i] = EEPROM.read(getEEPROMaddress(CF_MAX_DEVADDR) + sizeof(max_devices[0]) * z + i);
          }
          max_devices[x] = max_addr;
          printFmtToDebug("Adding known Max ID to list: %08lX\r\n", max_devices[x]);
        }
        break;
      }
    }
  }
  writeToEEPROM(CF_MAX_DEVICES);
  writeToEEPROM(CF_MAX_DEVADDR);
}

void printPStr(uint_farptr_t outstr, uint16_t outstr_len) {
  for (uint16_t x=0;x<outstr_len-1;x++) {
    bigBuff[bigBuffPos] = pgm_read_byte_far(outstr+x);
    bigBuffPos++;
    if (bigBuffPos >= OUTBUF_USEFUL_LEN + OUTBUF_LEN) {
      flushToWebClient();
    }
  }
//  final packet writing must be called from outside but it can be uncommented here for ensure.
//  if (bigBuffPos > 0) flushToWebClient();
}

#include "include/print_webpage.h"

#if defined(ESP32)
void init_ota_update(){
  if(enable_ota_update) {
    update_server.on("/", HTTP_GET, []() {
      char temp_user_pass[64] = { 0 };
      strncpy(temp_user_pass, USER_PASS, 64);
      if (USER_PASS[0]) {
        if (!update_server.authenticate(strtok(temp_user_pass,":"),strtok(NULL,":"))) {
          return update_server.requestAuthentication();
        }
      }
      update_server.sendHeader("Connection", "close");
      update_server.send(200, "text/html", serverIndex);
    });
    update_server.on("/update", HTTP_POST, []() {
      char temp_user_pass[64] = { 0 };
      strncpy(temp_user_pass, USER_PASS, 64);
      if (USER_PASS[0]) {
        if (!update_server.authenticate(strtok(temp_user_pass,":"),strtok(NULL,":"))) {
          return update_server.requestAuthentication();
        }
      }
      update_server.sendHeader("Connection", "close");
      update_server.send(200, "text/plain", (Update.hasError()) ? "Failed" : "Success");
      delay(1000);
      ESP.restart();
    }, []() {
      HTTPUpload& upload = update_server.upload();
      if (upload.status == UPLOAD_FILE_START) {
        uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
        printFmtToDebug("%d free bytes for firmware.\r\n", maxSketchSpace);
        printlnToDebug("Updating ESP32 firmware...");
        if (!Update.begin(maxSketchSpace)) { //start with max available size
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { //true to set the size to the current progress
          printlnToDebug("Update success, rebooting...");
        } else {
          Update.printError(Serial);
        }
      }
      yield();
    });
    update_server.begin();
    printlnToDebug("Update Server started on port 8080.");
  }
}
#endif

char *lookup_descr(float line) {
  int i=findLine(line);
  if (i<0) {                    // Not found (for this heating system)?
    strcpy(outBuf, cmdtbl[findLine(19999)].desc); // Unknown command has line no. 19999
  } else {
    strcpy(outBuf, cmdtbl[i].desc);
  }
  return outBuf;
}

void printDeviceArchToWebClient(){
  #if defined(ESP32)
    printToWebClient("ESP32");
  #elif defined(__SAM3X8E__)
    printToWebClient("Due");
  #else
    printToWebClient("Unknown");
  #endif
}

/** *****************************************************************
 *  Function:  GetDateTime()
 *  Does:      Returns human-readable date/time string
 *
 * Pass parameters:
 *   date buffer
 * Parameters passed back:
 *   none
 * Function value returned:
 *   date/time string
 * Global resources used:
 *   none
 * *************************************************************** */
char *GetDateTime(char *date) {
#if defined(ESP32)
  struct tm now;
  getLocalTime(&now,100);
  sprintf_P(date,"%02d.%02d.%d %02d:%02d:%02d",
            currentDate.elements.day   = now.tm_mday,
            currentDate.elements.month = now.tm_mon + 1,
            currentDate.elements.year  = now.tm_year + 1900,
            now.tm_hour,now.tm_min,now.tm_sec);
#else
  sprintf_P(date,"%02d.%02d.%d %02d:%02d:%02d",
            currentDate.elements.day   = day(),
            currentDate.elements.month = month(),
            currentDate.elements.year  = year(),
            hour(),minute(),second());
#endif
  date[19] = 0;
  return date;
}

void generateConfigPage(void) {
  printToWebClient("<BR>" MENU_TEXT_MCU ": ");
  printDeviceArchToWebClient();
  printToWebClient("<BR>\r\n" MENU_TEXT_VER ": ");
  printToWebClient(BSB_VERSION);
  printFmtToWebClient("<BR>\r\n" MENU_TEXT_RAM ": %d " MENU_TEXT_BYT "<BR>\r\n", freeRam());
  unsigned long ms = millis();
  unsigned long s = ms / 1000;
  unsigned long m = s / 60;
  unsigned long h = m / 60;
  unsigned d = h / 24;
  printFmtToWebClient(MENU_TEXT_UPT ": %lu\r\nms = %ud+%02lu:%02lu:%02lu.%03lu<BR>\r\n", ms, d, h%24, m%60, s%60, ms%1000);
  char tmp_date[20];
  printFmtToWebClient(ENUM_CAT_00_TEXT ": %s<BR>\r\n", GetDateTime(tmp_date));
  printlnToWebClient(MENU_TEXT_BUS ": ");
  int bustype = bus->getBusType();

  switch (bustype) {
    case 0: printToWebClient("BSB"); break;
    case 1: printToWebClient("LPB"); break;
    case 2: printToWebClient("PPS"); break;
  }
  if (bustype != BUS_PPS) {
    printFmtToWebClient(" (%d, %d) ", bus->getBusAddr(), bus->getBusDest());

    if ((default_flag & FL_RONLY) == FL_RONLY || ((default_flag & FL_SW_CTL_RONLY) == FL_SW_CTL_RONLY && !programWriteMode)) {
      printToWebClient(MENU_TEXT_BRO);
    } else {
      printToWebClient(MENU_TEXT_BRW);
    }
  } else {
    if (pps_write == 1) {
      printToWebClient(" (" MENU_TEXT_BRW ")");
    } else {
      printToWebClient(" (" MENU_TEXT_BRO ")");
    }
  }
  printToWebClient("<BR>\r\n");
  if (webserver || (LoggingMode & CF_LOGMODE_SD_CARD)) {
//    uint32_t m = micros();
    printToWebClient(STR_TEXT_FSP);
#if !defined(ESP32)
    uint32_t volFree = SDCard.vol()->freeClusterCount();
    uint32_t fs = (uint32_t)(volFree*SDCard.vol()->sectorsPerCluster()/2048);
    printFmtToWebClient(": %lu MB<br>\r\n", fs);
#else
    uint64_t fs = totalBytes()-usedBytes();
    printFmtToWebClient(": %llu Bytes<br>\r\n", fs);
#endif
//    printFmtToWebClient("Free space: %lu MB<br>free clusters: %lu<BR>freeClusterCount() call time: %lu microseconds<BR><br>\r\n", fs, volFree, micros() - m);
  }
  printToWebClient("<BR>\r\n");

// list of enabled modules
  printToWebClient(MENU_TEXT_MOD ": <BR>\r\n"

  #ifdef CUSTOM_COMMANDS
  #ifdef ANY_MODULE_COMPILED
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "CUSTOM_COMMANDS"
  #endif

  #ifdef USE_ADVANCED_PLOT_LOG_FILE
  #ifdef ANY_MODULE_COMPILED
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "USE_ADVANCED_PLOT_LOG_FILE"
  #endif

  #ifdef WIFISPI
  #ifdef ANY_MODULE_COMPILED
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "WIFISPI"
  #endif

  #if !defined (ANY_MODULE_COMPILED)
  "NONE"
  #endif
  "<BR><BR>\r\n");

  // end of list of enabled modules

  printToWebClient("<a href='/");
  printPassKey();
  printToWebClient("M1'>" MENU_TEXT_CLH "</a> " MENU_TEXT_MQ1);
  printToWebClient("<br><a href='/");
  printPassKey();
  printToWebClient("M0'>" MENU_TEXT_CLH "</a> " MENU_TEXT_MQ0);
  printToWebClient("<br><BR>");

  printToWebClient("<BR>\r\n");
}

uint8_t takeNewConfigValueFromUI_andWriteToRAM(int option_id, char *buf) {
  bool found = false;
  configuration_struct cfg;

  for (uint16_t f = 0; f < sizeof(config)/sizeof(config[0]); f++) {
    if (config[f].var_type == CDT_VOID) continue;
    memcpy(&cfg, &config[f], sizeof(cfg));
    if (cfg.id == option_id) {found = true; break;}
  }
  if (!found) {
    return 2;
  }

  switch (cfg.var_type) {
    case CDT_VOID: break;
    case CDT_BYTE:{
      byte variable = atoi(buf);
      writeToConfigVariable(option_id, (byte *)&variable);
      break;}
    case CDT_INT8:{
      int8_t variable = -1;
      if (*buf != '\0') {
        variable = atoi(buf);
      }
      writeToConfigVariable(option_id, (byte *)&variable);
      break;}
    case CDT_UINT16:{
      uint16_t variable = atoi(buf);
      writeToConfigVariable(option_id, (byte *)&variable);
      break;}
    case CDT_UINT32:{
      uint32_t variable = atoi(buf);
      writeToConfigVariable(option_id, (byte *)&variable);
      break;}
    case CDT_STRING:{
      char *variable = (char *)getConfigVariableAddress(option_id);
      memset(variable, 0, cfg.size);
      strncpy(variable, buf, cfg.size);
      break;}
    case CDT_MAC:{
      unsigned int i0, i1, i2, i3, i4, i5;
      uint16_t j = 0;
      char *ptr = buf;
      byte *variable = getConfigVariableAddress(option_id);
      memset(variable, 0, cfg.size);
      do{
        char *ptr_t = ptr;
        ptr = strchr(ptr, ',');
        if (ptr) ptr[0] = 0;
        if(sscanf(ptr_t, "%x:%x:%x:%x:%x:%x", &i0, &i1, &i2, &i3, &i4, &i5) == 6) {
          ((byte *)variable)[j * sizeof(mac) + 0] = (byte)(i0 & 0xFF);
          ((byte *)variable)[j * sizeof(mac) + 1] = (byte)(i1 & 0xFF);
          ((byte *)variable)[j * sizeof(mac) + 2] = (byte)(i2 & 0xFF);
          ((byte *)variable)[j * sizeof(mac) + 3] = (byte)(i3 & 0xFF);
          ((byte *)variable)[j * sizeof(mac) + 4] = (byte)(i4 & 0xFF);
          ((byte *)variable)[j * sizeof(mac) + 5] = (byte)(i5 & 0xFF);
        }
        if (ptr) {ptr[0] = ','; ptr++;}
        j++;
      }while (ptr && j < cfg.size/sizeof(mac));
      break;
    }
    case CDT_IPV4:{
      unsigned int i0, i1, i2, i3;
      sscanf(buf, "%u.%u.%u.%u", &i0, &i1, &i2, &i3);
      byte variable[4];
      variable[0] = (byte)(i0 & 0xFF);
      variable[1] = (byte)(i1 & 0xFF);
      variable[2] = (byte)(i2 & 0xFF);
      variable[3] = (byte)(i3 & 0xFF);
      writeToConfigVariable(option_id, variable);
      break;
    }
    case CDT_PROGNRLIST:{
      uint16_t j = 0;
      char *ptr = buf;
      byte *variable = getConfigVariableAddress(option_id);
      memset(variable, 0, cfg.size);
      do{
        char *ptr_t = ptr;
        ptr = strchr(ptr, ',');
        if (ptr) ptr[0] = 0;
        ((parameter *)variable)[j] = parsingStringToParameter(ptr_t);
        if (ptr) {ptr[0] = ','; ptr++;}
        j++;
      }while (ptr && j < cfg.size/sizeof(parameter));
      // writeToConfigVariable(option_id, variable); not needed here
      break;}
    case CDT_DHTBUS:{
      uint16_t j = 0;
      char *ptr = buf;
      byte *temp_variable = getConfigVariableAddress(option_id);
      int8_t *variable = 0;
      memcpy(&variable, &temp_variable, sizeof temp_variable);
      memset(variable, -1, cfg.size);
      if (*ptr == '\0') break;
      do{
        char *ptr_t = ptr;
        ptr = strchr(ptr, ',');
        if (ptr) {
          ptr[0] = 0;
        }
        variable[j] = atoi(ptr_t);
        if (ptr) {
          ptr[0] = ','; ptr++;
        }
        j++;
      }while (ptr && j < cfg.size/sizeof(byte));
      // writeToConfigVariable(option_id, variable); not needed here
      break;}
    case CDT_MAXDEVICELIST:{
      uint16_t j = 0;
      char *ptr = buf;
      byte *variable = getConfigVariableAddress(option_id);
      memset(variable, 0, cfg.size);
      do{
        char *ptr_t = ptr;
        ptr = strchr(ptr, ',');
        if (ptr) ptr[0] = 0;
        strncpy((char *)(variable + j * sizeof(max_device_list[0])), ptr_t, sizeof(max_device_list[0]));
        if (ptr) {ptr[0] = ','; ptr++;}
        j++;
      }while (ptr && j < cfg.size/sizeof(max_device_list[0]));
      // writeToConfigVariable(option_id, variable); not needed here
      UpdateMaxDeviceList();
      break;}
    default: break;
  }

return 1;
}

bool SaveConfigFromRAMtoEEPROM() {
  bool buschanged = false;
  bool needReboot = false;
  //save new values from RAM to EEPROM
  for (uint8_t i = 0; i < CF_LAST_OPTION; i++) {
    if (writeToEEPROM(i)) {
      if (verbose == DEVELOPER_DEBUG) printFmtToDebug("Option %d updated. EEPROM address: %04d\n", i, getEEPROMaddress(i));
      switch (i) {
        case CF_BUSTYPE:
        case CF_OWN_BSBLPBADDR:
        case CF_DEST_BSBLPBADDR:
        case CF_PPS_MODE:
          buschanged = true;
          break;
        case CF_RX_PIN:
        case CF_TX_PIN:
        //Unfortunately Ethernet Shield not supported dynamic reconfiguration of EthernetServer(s)
        // so here no reason do dynamic reconfiguration.
        // Topic: Possible to STOP an ethernet server once started and release resources ?
        // https://forum.arduino.cc/index.php?topic=395827.0
        // Topic: Dynamically changing IP address of Ethernet Shield (not DHCP and without reboot)
        // https://forum.arduino.cc/index.php?topic=89469.0
        // Resume: it possible but can cause unpredicable effects
        case CF_MAC:
        case CF_NETWORK_TYPE:
        case CF_DHCP:
        case CF_IPADDRESS:
        case CF_MASK:
        case CF_GATEWAY:
        case CF_DNS:
        case CF_DHTBUS:
        case CF_ONEWIREBUS:
        case CF_WWWPORT:
        case CF_WIFI_SSID:
        case CF_WIFI_PASSWORD:
        case CF_MDNS_HOSTNAME:
        case CF_ESP32_ENERGY_SAVE:
          needReboot = true;
          break;
        case CF_BMEBUS:
          if(BME_Sensors > 16) BME_Sensors = 16;
          needReboot = true;
          break;
#if defined(ESP32)
        case CF_OTA_UPDATE:
          if (enable_ota_update){
            init_ota_update();
          } else {
            update_server.stop();
            printlnToDebug("Update Server stopped.");
          }
          break;
#endif
        case CF_LOG_DEST:
          startLoggingDevice();
          break;
        case CF_AVERAGESLIST:
          resetAverageCalculation();
          break;
        case CF_MAX:
        case CF_MAX_IPADDRESS:
          connectToMaxCul();
          break;
        case CF_MQTT:
        case CF_MQTT_SERVER:
          mqtt_disconnect();
          break;
        default: break;
      }
    }
  }
  // EEPROM dump require ~3 sec so let it be last operation.
  // Dump when serial debug active or have telnet client
  EEPROM_dump();

  if (buschanged) {
    setBusType();
    SetDevId();
  }
  return needReboot;
}

int returnENUMID4ConfigOption(uint8_t id) {
  int i = 0;
  switch (id) {
    case CF_BUSTYPE:
      i=findLine(65532); //return ENUM_BUSTYPE
      break;
    case CF_LOGTELEGRAM:
      i=findLine(65531); //return ENUM_LOGTELEGRAM
      break;
    case CF_DEBUG:
      i=findLine(65530); //return ENUM_DEBUG
      break;
    case CF_MQTT:
      i=findLine(65529); //return ENUM_MQTT
      break;
    case CF_WRITEMODE:
      i=findLine(65528); //return ENUM_WRITEMODE
      break;
    case CF_PPS_MODE:
      i=findLine(65527); //return ENUM_PPS_MODE
      break;
    case CF_LOGMODE:
      i=findLine(65526); //return ENUM_LOGMODE
      break;
    case CF_NETWORK_TYPE:
      i=findLine(65525); //return ENUM_NETWORK_TYPE
      break;
    case CF_LOG_DEST:
      i=findLine(65524); //return ENUM_LOG_DEST
      break;
    case CF_VERBOSE:
      i=findLine(65523); //return ENUM_VERBOSE
      break;
    default:
      i = -1;
      break;
  }
  return i;
}

void printMAClistToWebClient(byte *variable, uint16_t size) {
  bool isFirst = true;
  for (uint16_t j = 0; j < size/sizeof(mac); j++) {
    bool mac_valid = false;
    for(uint m = 0; m < sizeof(mac); m++){
      if(variable[j * sizeof(mac) + m]){
        mac_valid = true;
        break;
      }
    }
    if (mac_valid) {
      if (!isFirst) printToWebClient(",");
      isFirst = false;
      bin2hex(outBuf, variable + j * sizeof(mac), sizeof(mac), ':');
      printToWebClient(outBuf);
      outBuf[0] = 0;
    }
  }
}

void printDHTlistToWebClient(byte *variable, uint16_t size) {
  int8_t *signed_variable = 0;
  memcpy(&signed_variable, &variable, sizeof variable);
  bool isFirst = true;
  for (uint16_t j = 0; j < size/sizeof(byte); j++) {
    if (signed_variable[j]>=0) {
      if (!isFirst) printToWebClient(",");
      isFirst = false;
      printFmtToWebClient("%d", signed_variable[j]);
    }
  }
}

void printProglistToWebClient(parameter *variable, uint16_t size) {
  bool isFirst = true;
  for (uint16_t j = 0; j < size/sizeof(parameter); j++) {
    if (variable[j].number) {
      if (!isFirst) printToWebClient(",");
      isFirst = false;
      printFmtToWebClient("%g", variable[j].number);
      if (variable[j].dest_addr > 0) {
        printFmtToWebClient("!%d", variable[j].dest_addr);
      }
    }
  }
}

void printMAXlistToWebClient(byte *variable, uint16_t size) {
  bool isFirst = true;
  for (uint16_t j = 0; j < size/sizeof(byte); j += sizeof(max_device_list[0])) {
    if (variable[j]) {
      if (!isFirst) printToWebClient(",");
      isFirst = false;
      printFmtToWebClient("%s", variable + j);
    }
  }
}

void applyingConfig() {
  bool k_flag = false;
  int i = 0;
  int option_id = 0;

  while (client.available()) {
    char c = client.read();
    if (!k_flag && i == OUTBUF_LEN - 2) { //buffer filled. trash in buffer?
      for (int j = 0; j < 16; j++) {
        outBuf[j] = outBuf[i - 16 + j];
      }
      i = 16;
    }

    if (c == '=') { //key/value delimiter
      char *ptr = strstr(outBuf, "option_");
      if (!ptr) continue;
      ptr += 7; //len of "option_" string
      option_id = atoi(ptr) - 1;
      printFmtToDebug("Option ID: %d\r\n", option_id);
      k_flag = true;
      i = 0;
      outBuf[i] = 0;
      continue;
    }
    if (k_flag && (c == '&' || i == OUTBUF_LEN - 2 || !client.available())) { //new pair key=value or buffer filled or last symbol was reading
      if (!client.available()) { //copy last symbol to buffer
        outBuf[i++] = c;
        outBuf[i] = 0;
      }

      if (takeNewConfigValueFromUI_andWriteToRAM(option_id, outBuf)  == 1)
        printFmtToDebug("Option value: %s\r\n", outBuf);

      k_flag = false;
      i = 0;
      outBuf[i] = 0;
      continue;
    }
    if (c == '+') {
      c = ' ';
    }
    if (c == '%') { //%HEX_CODE to char. Must be placed here for avoiding wrong behavior when =%& symbols decoded
      if (client.available()) {outBuf[i] = client.read();}
      if (client.available()) {outBuf[i + 1] = client.read();}
      outBuf[i + 2] = 0;
      unsigned int symbol;
      sscanf(outBuf + i, "%x", &symbol);
      c = symbol & 0xFF;
    }

    outBuf[i++] = c;
    outBuf[i] = 0;
  }

}

void printConfigWebPossibleValues(int i, uint16_t temp_value, bool printCurrentSelectionOnly) {
  uint16_t enumstr_len=cmdtbl[i].enumstr_len;
  uint_farptr_t enumstr = cmdtbl[i].enumstr;
  if(printCurrentSelectionOnly){
    listEnumValues(enumstr, enumstr_len, NULL, NULL, NULL, NULL, NULL, temp_value, PRINT_DESCRIPTION|PRINT_VALUE_FIRST|PRINT_ONLY_VALUE_LINE);
  } else {
    listEnumValues(enumstr, enumstr_len, STR_OPTION_VALUE, "'>", STR_SELECTED, STR_CLOSE_OPTION, NULL, temp_value, PRINT_VALUE|PRINT_DESCRIPTION|PRINT_VALUE_FIRST);
  }
}

void generateWebConfigPage(bool printOnly) {
  resetDecodedTelegram();
  printlnToWebClient(MENU_TEXT_CFG "<BR>");
  if(!printOnly){
    //This script will used for CPI_CHECKBOXES values calculation. It depended from HTML page structure: <div><input>...</input><label>...</label><label>...</label>...</div>
    printToWebClient("<script>function bvc(e,v){o=e.closest('div').querySelector('input');n=Number(o.value);n&v?p=n-v:p=n+v;o.value=p}</script>");
    printToWebClient("<form id=\"config\" method=\"post\" action=\"");
    if (PASSKEY[0]) {printToWebClient("/"); printToWebClient(PASSKEY);}
    printToWebClient("/CI\">");
  }
  printToWebClient("<table align=\"center\"><tbody>\r\n");
  for (uint16_t i = 0; i < sizeof(config)/sizeof(config[0]); i++) {
    configuration_struct cfg;

    memcpy(&cfg, &config[i], sizeof(cfg));

    if (cfg.var_type == CDT_VOID) continue;
    if(!printOnly){
      if(config_level == 0 && !(cfg.flags & OPT_FL_BASIC)) continue;
      if(config_level == 1 && !(cfg.flags & OPT_FL_ADVANCED)) continue;
    }
    byte *variable = getConfigVariableAddress(cfg.id);
    if (!variable) continue;

    printToWebClient("<tr><td>");
//Print param category
    printToWebClient(catalist[cfg.category].desc);
    const char fieldDelimiter[] = "</td><td>\r\n";
    printToWebClient(fieldDelimiter);
//Param Name
    printToWebClient(cfg.desc);
    printToWebClient(fieldDelimiter);
//Param Value

//Open tag
    if(!printOnly){
      switch (cfg.input_type) {
        case CPI_TEXT:
        printFmtToWebClient("<input type=text id='option_%d' name='option_%d' ", cfg.id + 1, cfg.id + 1);
        switch (cfg.var_type) {
          case CDT_MAC:
            printToWebClient("pattern='([0-9A-Fa-f]{2}[-:]){5}[0-9A-Fa-f]{2}'");
            break;
          case CDT_IPV4:
            printToWebClient("pattern='((^|\\.)(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){4}'");
            break;
          case CDT_PROGNRLIST:
            printToWebClient("pattern='((^|,)\\d{1,5}(\\.\\d)?((!|!-)\\d{1,3})?)+'");
            break;
          }
        printToWebClient(" value='");
        break;
        case CPI_SWITCH:
        case CPI_DROPDOWN:
           printFmtToWebClient("<select id='option_%d' name='option_%d'>\r\n", cfg.id + 1, cfg.id + 1);
        break;
        case CPI_CHECKBOXES:
           printFmtToWebClient("<div><input type=hidden id='option_%d' name='option_%d' value='%d'>\r\n", cfg.id + 1, cfg.id + 1, (int)variable[0]);
        break;
        default: break;
      }
    } else {
      printFmtToWebClient("<output id='option_%d' name='option_%d'>\r\n", cfg.id + 1, cfg.id + 1);
    }
  
  
    switch (cfg.var_type) {
      case CDT_VOID: break;
      case CDT_BYTE:
        switch (cfg.input_type) {
          case CPI_TEXT: printFmtToWebClient("%d", (int)variable[0]); break;
          case CPI_SWITCH:{
            int i;
            switch (cfg.id) {
              case CF_USEEEPROM:
                i=findLine(65534); //return ENUM_EEPROM_ONOFF
                break;
              default:
                i=findLine(65533); //return ENUM_ONOFF
                break;
            }
            printConfigWebPossibleValues(i, (uint16_t)variable[0], printOnly);
            break;}
          case CPI_CHECKBOXES:{
            int i = returnENUMID4ConfigOption(cfg.id);
            if (i > 0) {
              uint16_t enumstr_len=cmdtbl[i].enumstr_len;
              uint_farptr_t enumstr = cmdtbl[i].enumstr;
              listEnumValues(enumstr, enumstr_len, "<label style='display:flex;flex-direction:row;justify-content:flex-start;align-items:center'><input type='checkbox' style='width:40px;' onclick=\"bvc(this,", ")\">", ")\" checked>", "</label>", NULL, variable[0], PRINT_DESCRIPTION|PRINT_VALUE|PRINT_VALUE_FIRST|PRINT_ENUM_AS_DT_BITS);
            }
            break;}
          case CPI_DROPDOWN:{
            int i = returnENUMID4ConfigOption(cfg.id);
             if (i > 0) {
              printConfigWebPossibleValues(i, variable[0], printOnly);
            }
            break;}
        }
        break;
      case CDT_INT8:
        if (((int8_t *)variable)[0] >= 0) {
          printFmtToWebClient("%d", ((int8_t *)variable)[0]);
        }
        break;
      case CDT_UINT16:
        switch (cfg.input_type) {
          case CPI_TEXT: printFmtToWebClient("%u", ((uint16_t *)variable)[0]); break;
          case CPI_DROPDOWN:{
            int i;
            switch (cfg.id) {
              case CF_ROOM_DEVICE:
                i=findLine(15000 + PPS_QTP); //return ENUM15062 (device type)
                break;
              default:
                i = -1;
                break;
            }
            if (i > 0) {
              printConfigWebPossibleValues(i, ((uint16_t *)variable)[0], printOnly);
            }
            break;}
          }
        break;
      case CDT_UINT32:
        printFmtToWebClient("%lu", ((uint32_t *)variable)[0]);
        break;
      case CDT_STRING:
        printFmtToWebClient("%s", (char *)variable);
        break;
      case CDT_MAC:
        printMAClistToWebClient((byte *)variable, cfg.size);
        break;
      case CDT_IPV4:
        printFmtToWebClient("%u.%u.%u.%u", (int)variable[0], (int)variable[1], (int)variable[2], (int)variable[3]);
        break;
      case CDT_PROGNRLIST:
        printProglistToWebClient((parameter *)variable, cfg.size);
        break;
      case CDT_DHTBUS:
         printDHTlistToWebClient((byte *)variable, cfg.size);
        break;
      case CDT_MAXDEVICELIST:
        printMAXlistToWebClient((byte *)variable, cfg.size);
        break;
      default: break;
    }
  
  //Closing tag
    if(!printOnly){
      switch (cfg.input_type) {
        case CPI_TEXT: printToWebClient("'>"); break;
        case CPI_SWITCH:
        case CPI_DROPDOWN: printToWebClient("</select>"); break;
        case CPI_CHECKBOXES: printToWebClient("</div>");break;
        default: break;
      }
    } else {
      printToWebClient("</output>");
    }
    printToWebClient("</td></tr>\r\n");
  }
  printToWebClient("</tbody></table><p>");
  if(!printOnly){
    printToWebClient("<input type=\"submit\" value=\"");
    printToWebClient(STR_SAVE);
    printToWebClient("\"></p>\r\n</form>\r\n");
  }
}

void printConfigJSONPossibleValues(int i, bool its_a_bits_enum) {
  printToWebClient("    \"possibleValues\": [\r\n");
  uint16_t enumstr_len=cmdtbl[i].enumstr_len;
  uint_farptr_t enumstr = cmdtbl[i].enumstr;
  listEnumValues(enumstr, enumstr_len, "      { \"enumValue\": \"", "\", \"desc\": \"", NULL, "\" }", ",\r\n", 0,
    its_a_bits_enum?PRINT_VALUE|PRINT_DESCRIPTION|PRINT_VALUE_FIRST|PRINT_ENUM_AS_DT_BITS:
    PRINT_VALUE|PRINT_DESCRIPTION|PRINT_VALUE_FIRST);
  printToWebClient("\r\n      ]");
}

void generateJSONwithConfig() {
  bool notFirst = false;
  for (uint16_t i = 0; i < sizeof(config)/sizeof(config[0]); i++) {
    configuration_struct cfg;

    memcpy(&cfg, &config[i], sizeof(cfg));

    if (cfg.var_type == CDT_VOID) continue;
    if(config_level == 0 && !(cfg.flags & OPT_FL_BASIC)) continue;
    if(config_level == 1 && !(cfg.flags & OPT_FL_ADVANCED)) continue;
    byte *variable = getConfigVariableAddress(cfg.id);
    if (!variable) continue;
    if (notFirst) {printToWebClient("\r\n    },\r\n");} else notFirst = true;

    printFmtToWebClient("  \"%d\": {\r\n    \"parameter\": %d,\r\n    \"type\": %d,\r\n    \"format\": %d,\r\n    \"category\": \"", i, cfg.id, cfg.var_type, cfg.input_type);
//Print param category
    printToWebClient(catalist[cfg.category].desc);

    printToWebClient("\",\r\n    \"name\": \"");
//Param Name
    printToWebClient(cfg.desc);
    printToWebClient("\",\r\n    \"value\": \"");
//Param Value

    switch (cfg.var_type) {
      case CDT_VOID: break;
      case CDT_BYTE:
        switch (cfg.input_type) {
          case CPI_TEXT: printFmtToWebClient("%d\"", (int)variable[0]); break;
          case CPI_SWITCH:{
            int i;
            switch (cfg.id) {
              case CF_USEEEPROM:
                i=findLine(65534); //return ENUM_EEPROM_ONOFF
                break;
              default:
                i=findLine(65533); //return ENUM_ONOFF
                break;
            }
            printFmtToWebClient("%u\",\r\n", (uint16_t)variable[0]);
            printConfigJSONPossibleValues(i, false);
            break;}
          case CPI_CHECKBOXES:
          case CPI_DROPDOWN:{
            int i = returnENUMID4ConfigOption(cfg.id);
            if (i > 0) {
              printFmtToWebClient("%u\",\r\n", (uint16_t)variable[0]);
              printConfigJSONPossibleValues(i, cfg.input_type == CPI_CHECKBOXES);
            }
            break;}
          }
        break;
      case CDT_INT8:
        if (((int8_t *)variable)[0] >= 0) {
          printFmtToWebClient("%d\"", ((int8_t *)variable)[0]);
        }
        break;
      case CDT_UINT16:
        switch (cfg.input_type) {
          case CPI_TEXT: printFmtToWebClient("%u\"", ((uint16_t *)variable)[0]); break;
          case CPI_DROPDOWN:{
            int i;
            switch (cfg.id) {
              case CF_ROOM_DEVICE:
                i=findLine(15000 + PPS_QTP); //return ENUM15062 (device type)
                break;
              default:
                i = -1;
                break;
            }
            if (i > 0) {
              printFmtToWebClient("%u\",\r\n", ((uint16_t *)variable)[0]);
              printConfigJSONPossibleValues(i, false);
            }
            break;}
          }
        break;
      case CDT_UINT32:
        printFmtToWebClient("%lu\"", ((uint32_t *)variable)[0]);
        break;
      case CDT_STRING:
        printFmtToWebClient("%s\"", (char *)variable);
        break;
      case CDT_MAC:
        printMAClistToWebClient((byte *)variable, cfg.size);
        printToWebClient("\"");
   //       printFmtToWebClient("%02X:%02X:%02X:%02X:%02X:%02X", (int)variable[0], (int)variable[1], (int)variable[2], (int)variable[3], (int)variable[4], (int)variable[5]);
        break;
      case CDT_IPV4:
        printFmtToWebClient("%u.%u.%u.%u\"", (int)variable[0], (int)variable[1], (int)variable[2], (int)variable[3]);
        break;
      case CDT_PROGNRLIST:
        printProglistToWebClient((parameter *)variable, cfg.size);
        printToWebClient("\"");
        break;
      case CDT_DHTBUS:
        printDHTlistToWebClient((byte *)variable, cfg.size);
        printToWebClient("\"");
        break;
      case CDT_MAXDEVICELIST:
        printMAXlistToWebClient((byte *)variable, cfg.size);
        printToWebClient("\"");
        break;
      default: break;
    }
  }
  printToWebClient("\r\n    }\r\n");
}

/** *****************************************************************
 *  Function:  LogTelegram()
 *  Does:      Logs the telegram content in hex to the SD card,
 *             starting at position null. It stops
 *             when it has sent the requested number of message bytes.
 *  Pass parameters:
 *   byte *msg pointer to the telegram buffer
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   log_parameters
 * *************************************************************** */
void LogTelegram(byte* msg) {
  if (!(logTelegram & LOGTELEGRAM_ON) || !(LoggingMode & CF_LOGMODE_SD_CARD)) return;
  File dataFile;
  uint32_t cmd;
  int i=0;        // begin with line 0
  int save_i=0;
  bool known=0;
  uint32_t c;     // command code
  uint8_t cmd_type=0;
  float operand=1;
  uint8_t precision=0;
  int data_len;
  float dval;
  float line = 0;
#if !defined(ESP32)
  if (SDCard.vol()->freeClusterCount() < minimum_SD_size) return;
#else
  if (totalBytes()-usedBytes() < minimum_SD_size) return;
#endif

  if (bus->getBusType() != BUS_PPS) {
    if (msg[4+bus->offset]==TYPE_QUR || msg[4+bus->offset]==TYPE_SET || (((msg[2]!=ADDR_ALL && bus->getBusType()==BUS_BSB) || (msg[2]<0xF0 && bus->getBusType()==BUS_LPB)) && msg[4+bus->offset]==TYPE_INF)) { //QUERY and SET: byte 5 and 6 are in reversed order
      cmd=(uint32_t)msg[6+bus->offset]<<24 | (uint32_t)msg[5+bus->offset]<<16 | (uint32_t)msg[7+bus->offset] << 8 | (uint32_t)msg[8+bus->offset];
    } else {
      cmd=(uint32_t)msg[5+bus->offset]<<24 | (uint32_t)msg[6+bus->offset]<<16 | (uint32_t)msg[7+bus->offset] << 8 | (uint32_t)msg[8+bus->offset];
    }
  } else {
//      cmd=msg[1+(msg[0]==0x17 && pps_write != 1)];
    cmd=msg[1];
  }
  // search for the command code in cmdtbl
  c=cmdtbl[i].cmd;
//    c=pgm_read_dword(&cmdtbl[i].cmd);    // extract the command code from line i
  while (c!=CMD_END) {
    line=cmdtbl[i].line;
    if ((bus->getBusType() != BUS_PPS && (c & 0xFF00FFFF) == (cmd & 0xFF00FFFF)) || (bus->getBusType() == BUS_PPS && line >= 15000 && (cmd == ((c & 0x00FF0000) >> 16)))) {   // one-byte command code of PPS is stored in bitmask 0x00FF0000 of command ID
      uint8_t dev_fam = cmdtbl[i].dev_fam;
      uint8_t dev_var = cmdtbl[i].dev_var;
      if ((dev_fam == my_dev_fam || dev_fam == DEV_FAM(DEV_ALL)) && (dev_var == my_dev_var || dev_var == DEV_VAR(DEV_ALL))) {
        if (dev_fam == my_dev_fam && dev_var == my_dev_var) {
          known=1;
          break;
        } else if ((!known && dev_fam!=my_dev_fam) || (dev_fam==my_dev_fam)) { // wider match has hit -> store in case of best match
          known=1;
          save_i=i;
        }
      }
    }
    if (known && (c & 0xFF00FFFF) != (cmd & 0xFF00FFFF)) {
      i=save_i;
      break;
    }
    i++;
    c=cmdtbl[i].cmd;
  }
  if (cmd <= 0) return;
  bool logThis = false;
  switch (logTelegram) {
    case LOGTELEGRAM_ON: logThis = true; break;
    case LOGTELEGRAM_ON + LOGTELEGRAM_UNKNOWN_ONLY: if (known == 0)  logThis = true; break;
    case LOGTELEGRAM_ON + LOGTELEGRAM_BROADCAST_ONLY: if ((msg[2]==ADDR_ALL && bus->getBusType()==BUS_BSB) || (msg[2]>=0xF0 && bus->getBusType()==BUS_LPB)) logThis = true; break;
    case LOGTELEGRAM_ON + LOGTELEGRAM_BROADCAST_ONLY+LOGTELEGRAM_UNKNOWN_ONLY: if (known == 0 && ((msg[2]==ADDR_ALL && bus->getBusType()==BUS_BSB) || (msg[2]>=0xF0 && bus->getBusType()==BUS_LPB))) logThis = true; break;
    default: logThis = false; break;
  }
  if (logThis) {
    dataFile = SDCard.open(journalFileName, FILE_APPEND);
    if (dataFile) {
      int outBufLen = 0;
      outBufLen += sprintf_P(outBuf, "%lu;%s;", millis(), GetDateTime(outBuf + outBufLen + 80));
      if (!known) {                          // no hex code match
      // Entry in command table is "UNKNOWN" (0x00000000)
        outBufLen += strlen(strcpy(outBuf + outBufLen, "UNKNOWN"));
      } else {
        // Entry in command table is a documented command code
        line=cmdtbl[i].line;
        cmd_type=cmdtbl[i].type;
        outBufLen += sprintf_P(outBuf + outBufLen, "%g", line);
      }

      uint8_t msg_len = 0;
      if (bus->getBusType() != BUS_PPS) {
        outBufLen += sprintf_P(outBuf + outBufLen, ";%s->%s %s;", TranslateAddr(msg[1+(bus->getBusType()*2)], outBuf + outBufLen + 40), TranslateAddr(msg[2], outBuf + outBufLen + 50), TranslateType(msg[4+bus->offset], outBuf + outBufLen + 60));
        msg_len = msg[bus->getLen_idx()]+bus->getBusType();
      } else {
        strcat(outBuf + outBufLen, ";");
        const char *getfarstrings;
        if (msg[0] < 0xF0) {
          switch (msg[0] & 0x0F) {                              // messages from heater
            case 0x0D: getfarstrings = "PPS INF"; break;  // 0x1D
            case 0x0E: getfarstrings = "PPS REQ"; break;  // 0x1E
            case 0x07: getfarstrings = "PPS RTS"; break;  // 0x17
            default: getfarstrings = ""; break;
          }
        } else {
          switch (msg[0]) {                                     // messages from room unit - had to split this up because some PPS devices change high byte, but room units not, so 0x1D and 0xFD would clash
            case 0xF8:
            case 0xFB:
            case 0xFD:
            case 0xFE:
              getfarstrings = "PPS ANS"; break;
            default: getfarstrings = ""; break;
          }
        }
        strcat(outBuf + outBufLen, getfarstrings);
        strcat(outBuf + outBufLen, ";");
        outBufLen += strlen(outBuf + outBufLen);
//            msg_len = 9+(msg[0]==0x17 && pps_write != 1);
        msg_len = 9;
      }

      outBufLen += bin2hex(outBuf + outBufLen, msg, msg_len, ' ');
      // additionally log data payload in addition to raw messages when data payload is max. 32 Bit
      uint8_t msg_type = msg[4+bus->offset];
      if (bus->getBusType() != BUS_PPS && (msg_type == TYPE_INF || msg_type == TYPE_SET || msg_type == TYPE_ANS) && msg[bus->getLen_idx()] < 17+bus->getBusType()) {
        outBufLen += strlen(strcat(outBuf + outBufLen, ";"));
// payload length includes one byte for enable/disable byte, except for INF telegrams which have none of these. We have to subtract this one and add it back if it's an INF.
        if (bus->getBusType() == BUS_LPB) {
          data_len=msg[1]-14-1+(msg_type==TYPE_INF);
        } else {
          data_len=msg[3]-11-1+(msg_type==TYPE_INF);
        }
        dval = 0;
        operand=optbl[cmd_type].operand;
        precision=optbl[cmd_type].precision;
/*
// Check whether this for loop was really wrong for all those years...
        for (i=0;i<data_len-1+bus->getBusType();i++) {
          if (bus->getBusType() == BUS_LPB) {
            dval = dval + long(msg[14+i-(msg[8]==TYPE_INF)]<<((data_len-2-i)*8));
          } else {
            dval = dval + long(msg[10+i-(msg[4]==TYPE_INF)]<<((data_len-2-i)*8));
          }
        }
*/
        for (i=0;i<data_len;i++) {
          if (bus->getBusType() == BUS_LPB) {
            dval = dval + long(msg[14+i-(msg_type==TYPE_INF)]<<((data_len-1-i)*8));   // Starts one byte after payload begins, except for INF
          } else {
            dval = dval + long(msg[10+i-(msg_type==TYPE_INF)]<<((data_len-1-i)*8));
          }
        }

        dval = dval / operand;
        _printFIXPOINT(outBuf + outBufLen, dval, precision);
        // print ',' instead '.'
        char *p = strchr(outBuf + outBufLen,'.');
        if (p != NULL) *p=',';
        outBufLen += strlen(outBuf + outBufLen);
      }
      strcat(outBuf + outBufLen, "\r\n");
      dataFile.print(outBuf);
      dataFile.close();
    }
  }
}

#define MAX_PARAM_LEN 22

/**  *****************************************************************
 *  Function: set()
 *  Does:     This routine does all the work to set up a SET
 *            command for various heater parameters.  As such,
 *            it uses a BIG switch statement to differentiate
 *            between the various parameter types and formats
 *            them according to the rules of the heater mfgr.
 * Pass parameters:
 *  uint16  line     the line number (ProgNr)
 *  char  * val      the value to set
 *  bool setcmd      True:  builds a SET msg;
 *                   False: builds an INF msg
 * Parameters passed back:
 *
 * Function value returned:
 *  0         failure (incomplete input data, ..)
 *
 * Global resources used:
 *  Serial instance
 *  bus    instance
 * *************************************************************** */
int set(float line      // the ProgNr of the heater parameter
      , const char *val          // the value to set
      , bool setcmd)       // true: SET msg; false: INF msg
{
  byte msg[33];            // we know the maximum length
  byte tx_msg[33];
  int i;
  uint8_t param[MAX_PARAM_LEN]; // 33 -9 - 2
  uint8_t param_len = 0;
#if defined(ESP32)
  esp_task_wdt_reset();
#endif

  if (line < 0) {
    return 0;
  }
  // Search the command table from the start for a matching line nbr.
  i=findLine(line);   // find the ProgNr and get the command code
  uint32_t c = cmdtbl[i].cmd;
  if (i<0) return 0;        // no match

  uint16_t dev_flags = cmdtbl[i].flags;
  // Check for readonly parameter
  if (programIsreadOnly(dev_flags)) {
    printlnToDebug("Parameter is readonly!");
    return 2;   // return value for trying to set a readonly parameter
  }
  if ((dev_flags & FL_FORCE_INF) && setcmd) {
    printlnToDebug("Parameter is of FORCE_INF type and thus requires setting via INF, not SET, doing the switch for you now...");
    setcmd = false;     // FORCE_INF indicates that parameter requires setting a value via INF, not SET. So in case a command is sent via the web interface's "Set" button, make sure that it is still successful.
  }

  // Force to publish MQTT update in 1s as state may have been modified by this SET command
  // Wait 1s to ensure all values are updated in the microcontroller
  // (e.g., moving from Off to Automatic: state circuit 1 is updated after dozen of ms)
  // EDIT: Should no longer be necessary as SET command includes a QUeRy command, and this one updates MQTT automatically
/*
  if (setcmd) {  // Only for SET messages
    lastMQTTTime = millis() - log_interval * 1000 + 1000;
  }
*/

  loadPrognrElementsFromTable(line, i);

  if ((line >= (float)BSP_INTERNAL && line < (float)BSP_END)) //virtual functions handler
    {
      if(line == (float)BSP_INTERNAL + 6){
        if (atoi(val)) resetDurations(); return 1; // reset furnace duration
      }
      if ((line >= (float)BSP_FLOAT && line < (float)BSP_FLOAT + numCustomFloats)) {// set custom_float
        custom_floats[(int)line - BSP_FLOAT] = atof(val);
        return 1;
      }
      if ((line >= (float)BSP_LONG && line < (float)BSP_LONG + numCustomLongs)) {// set custom_longs
        custom_longs[(int)line - BSP_LONG] = atol(val);
        return 1;
      }

      return 2;
    }

  if (bus->getBusType() == BUS_PPS && line >= 15000 && line < 15000 + PPS_ANZ) { // PPS-Bus set parameter
    int cmd_no = line - 15000;
    switch (decodedTelegram.type) {
      case VT_TEMP: pps_values[cmd_no] = atof(val) * 64; break;
      case VT_WEEKDAY:
      {
        int dow = atoi(val);
        pps_values[PPS_DOW] = dow;
      #if defined(ESP32)
/*
        struct tm now;
        getLocalTime(&now,0);
        setTime(now.tm_hour,now.tm_min,now.tm_sec, dow, 1, 2018);
*/
      #else
        setTime(hour(), minute(), second(), dow, 1, 2018);
      #endif
        if (verbose == DEVELOPER_DEBUG) printFmtToDebug("Setting weekday to %d\r\n", weekday());
        pps_wday_set = true;
        break;
      }
      case VT_PPS_TIME:
      {
        int hour=0, minute=0, second=0;
        sscanf(val, "%d.%d.%d", &hour, &minute, &second);
        setTime(hour, minute, second, weekday(), 1, 2024);
        if (verbose == DEVELOPER_DEBUG) printFmtToDebug("Setting time to %d:%d:%d\r\n", hour, minute, second);
        pps_time_set = true;
        break;
      }
/*
      case VT_HOUR_MINUTES:
      {
        uint8_t h=atoi(val);
        uint8_t m=0;
        while (*val!='\0' && *val!=':' && *val!='.') val++;
        if (*val==':' || *val=='.') {
          val++;
          m=atoi(val);
        }
        pps_values[cmd_no] = h * 6 + m / 10;
        break;
      }
*/
      case VT_TIMEPROG: // TODO test it
      {
        // Default values if not requested otherwise
        int h1s=0xFF,m1s=0xFF,h2s=0xFF,m2s=0xFF,h3s=0xFF,m3s=0xFF;
        int h1e=0xFF,m1e=0xFF,h2e=0xFF,m2e=0xFF,h3e=0xFF,m3e=0xFF;
        // we need at least the first period
        if (sscanf(val,"%d:%d-%d:%d%*c%d:%d-%d:%d%*c%d:%d-%d:%d",&h1s,&m1s,&h1e,&m1e,&h2s,&m2s,&h2e,&m2e,&h3s,&m3s,&h3e,&m3e)<4) {     // BEGIN hour/minute and END hour/minute
          return 0;
        }
        pps_values[cmd_no] = (h1s==0xFF || h1e==0xFF)?0xFF:h1s * 6 + m1s / 10;
        pps_values[cmd_no+1] = (h1s==0xFF || h1e==0xFF)?0xFF:h1e * 6 + m1e / 10;
        pps_values[cmd_no+2] = (h2s==0xFF || h2e==0xFF)?0xFF:h2s * 6 + m2s / 10;
        pps_values[cmd_no+3] = (h2s==0xFF || h2e==0xFF)?0xFF:h2e * 6 + m2e / 10;
        pps_values[cmd_no+4] = (h3s==0xFF || h3e==0xFF)?0xFF:h3s * 6 + m3s / 10;
        pps_values[cmd_no+5] = (h3s==0xFF || h3e==0xFF)?0xFF:h3e * 6 + m3e / 10;
        break;
      }
      default: pps_values[cmd_no] = atoi(val); break;
    }

    uint16_t flags=cmdtbl[i].flags;
    if ((flags & FL_EEPROM) == FL_EEPROM && EEPROM_ready) {
//    if(EEPROM_ready && (allow_write_pps_values[cmd_no / 8] & (1 << (cmd_no % 8)))) {
      printFmtToDebug("Writing EEPROM slot %d with value %u", cmd_no, pps_values[cmd_no]);
      writelnToDebug();
      writeToEEPROM(CF_PPS_VALUES);
    }

    return 1;
  }

  // Get the parameter type from the table row[i]
  switch (decodedTelegram.type) {
    // ---------------------------------------------
    // No input values sanity check

    // 8-bit representations
    case VT_MONTHS: //(Wartungsintervall)
    case VT_MONTHS_N: //(Wartungsintervall)
    case VT_MINUTES_SHORT: // ( Fehler - Alarm)
    case VT_MINUTES_SHORT_N: // ( Fehler - Alarm)
    case VT_PERCENT:
    case VT_PERCENT_NN:
    case VT_PERCENT1:
    case VT_ENUM:          // enumeration types
    case VT_BINARY_ENUM:
    case VT_WEEKDAY:
    case VT_ONOFF: // 1 = On                      // on = Bit 0 = 1 (i.e. 1=on, 3=on... 0=off, 2=off etc.)
    case VT_CLOSEDOPEN: // 1 = geschlossen
    case VT_YESNO: // 1 = Ja
    case VT_DAYS: // (Legionellenfkt. Periodisch)
    case VT_HOURS_SHORT: // (Zeitkonstante Gebäude)
    case VT_HOURS_SHORT_N: // (Zeitkonstante Gebäude)
    case VT_BIT:
    case VT_BYTE:
    case VT_BYTE_N:
    case VT_BYTE5_N:
    case VT_BYTE10:
    case VT_BYTE10_N:
    case VT_TEMP_SHORT:
    case VT_TEMP_SHORT_US:
    case VT_TEMP_SHORT_US_N:
    case VT_TEMP_PER_MIN:
    case VT_TEMP_SHORT5_US:
    case VT_TEMP_SHORT5:
    case VT_PERCENT5:
    case VT_TEMP_SHORT64:
    case VT_SECONDS_SHORT2:
    case VT_SECONDS_SHORT2_N:
    case VT_SECONDS_SHORT4:
    case VT_SECONDS_SHORT5:
    case VT_PRESSURE:
    case VT_PRESSURE_NN:
    case VT_GRADIENT_SHORT:
    case VT_LPBADDR:
    case VT_SECONDS_SHORT:
    case VT_SECONDS_SHORT_N:
    case VT_VOLTAGE:
    case VT_VOLTAGE_N:
    case VT_VOLTAGE_WORD1:
    case VT_LITER:
    case VT_POWER_SHORT:
    case VT_POWER_SHORT_N:

    // 16-bit representations
    case VT_UINT:
    case VT_UINT_N:
    case VT_UINT100_WORD_N:
    case VT_SINT:
    case VT_SINT_NN:
    case VT_PERCENT_WORD1:
    case VT_METER:
    case VT_HOURS_WORD: // (Brennerstunden Intervall - nur durch 100 teilbare Werte)
    case VT_HOURS_WORD_N: // (Brennerstunden Intervall - nur durch 100 teilbare Werte)
    case VT_MINUTES_WORD: // (Legionellenfunktion Verweildauer)
    case VT_MINUTES_WORD_N:
    case VT_MINUTES_WORD10:
    case VT_UINT2_N:
    case VT_UINT5:
    case VT_UINT10:
    case VT_MSECONDS_WORD:
    case VT_MSECONDS_WORD_N:
    case VT_SECONDS_WORD:
    case VT_SECONDS_WORD_N:
    case VT_SECONDS_WORD16:
    case VT_TEMP_WORD:
    case VT_CELMIN:
    case VT_CELMIN_N:
    case VT_PERCENT_100:
    case VT_PERCENT_WORD:
    case VT_LITERPERHOUR:
    case VT_LITERPERHOUR_N:
    case VT_LITERPERHOUR100:
    case VT_LITERPERHOUR100_N:
    case VT_LITERPERMIN:
    case VT_LITERPERMIN_N:
    case VT_CONSUMPTION:
    case VT_PRESSURE_WORD1:
    case VT_PRESSURE_1000:
    case VT_PPM:
    case VT_FP02:
    case VT_SECONDS_WORD5:
    case VT_SECONDS_WORD5_N:
    case VT_SECONDS_WORD4:
    case VT_SECONDS_WORD4_N:
    case VT_TEMP_WORD5_US:
    case VT_GRADIENT:
    case VT_POWER_W:
    case VT_POWER_WORD:
    case VT_POWER_WORD_N:
    case VT_MONTHS_WORD:
    case VT_DAYS_WORD:
    case VT_FREQ:
    case VT_FREQ10:

    // 32-bit representations
    case VT_UINT100:
    case VT_ENERGY:
    case VT_ENERGY_N:
    case VT_ENERGY10:
    case VT_ENERGY10_N:
    case VT_ENERGY_MWH:
    case VT_ENERGY_MWH_N:
    case VT_AMP:
    case VT_CUBICMETER:
    case VT_MINUTES:
    case VT_HOURS:
    case VT_HOURS_N:
    case VT_TEMP_DWORD:
      {
      char* val1 = (char *)val;
      if (val[0] == '-') {
        val1++;
      }
      uint32_t t = atoi(val1) * decodedTelegram.operand;
      val1 = strchr(val, '.');
      if(val1) {
        val1++;
        int len = strlen(val1);
        uint32_t tpart = atoi(val1) * decodedTelegram.operand;
        for(int d = 0; d < len; d++) {
          if(tpart % 10 > 4 && d + 1 == len) tpart += 10; //rounding
          tpart /= 10;
        }
        t += tpart;
      }
      if (val[0] == '-') {
        t = -1 * (int) t;
      }
      for (int x=decodedTelegram.payload_length;x>0;x--) {
        param[decodedTelegram.payload_length-x+1] = (t >> ((x-1)*8)) & 0xff;
      }
      if (val[0] == '\0' || (decodedTelegram.type == VT_ENUM && t == 0xFFFF) || !strcmp(val, "---")) {
        param[0]=decodedTelegram.enable_byte-1;  // disable
      } else {
        param[0]=decodedTelegram.enable_byte;  //enable
      }
      param_len=decodedTelegram.payload_length + 1;
      }
      break;

    // ---------------------------------------------
    // 32-bit representation
    case VT_DWORD:      // can this be merged with the 32-bit above?
    case VT_DWORD_N:
    case VT_DWORD10:
      {
      if (val[0]!='\0' && strcmp(val, "---")) {
        uint32_t t = (uint32_t)strtoul(val, NULL, 10);
        param[0]=decodedTelegram.enable_byte;  //enable
        param[1]=(t >> 24) & 0xff;
        param[2]=(t >> 16) & 0xff;
        param[3]=(t >> 8) & 0xff;
        param[4]= t & 0xff;
      } else {
        param[0]=decodedTelegram.enable_byte-1;  // disable
        param[1]=0x00;
        param[2]=0x00;
        param[3]=0x00;
        param[4]=0x00;
      }
      param_len=5;
      }
      break;

    // Special parameters

    case VT_HOUR_MINUTES: //TODO test it
    case VT_HOUR_MINUTES_N:
      {
      if (val[0]!='\0' && strcmp(val, "---")) {
        uint8_t h=atoi(val);
        uint8_t m=0;
        while (*val!='\0' && *val!=':' && *val!='.') val++;
        if (*val==':' || *val=='.') {
          val++;
          m=atoi(val);
        }
        param[0]=decodedTelegram.enable_byte;  //enable
        param[1]= h;
        param[2]= m;
      } else {
        param[0]=decodedTelegram.enable_byte-1;  // disable
        param[1]=0x00;
        param[2]=0x00;
      }
      param_len=3;
      }
      break;

    // ---------------------------------------------
    // Example: (Telefon Kundendienst)
    case VT_STRING:
      {
      strncpy((char *)param,val,MAX_PARAM_LEN);
      param[MAX_PARAM_LEN-1]='\0';
      param_len=strlen((char *)param)+1;
      }
      break;

    case VT_SINT1000:
      {
      uint16_t t=atof(val)*1000.0;
      if (setcmd) {
        if (val[0]!='\0' && strcmp(val, "---")) {
          param[0]=decodedTelegram.enable_byte;
        } else {
          param[0]=decodedTelegram.enable_byte-1;
        }
        param[1]=(t >> 8);
        param[2]= t & 0xff;
      } else { // INF message type (e.g. for room temperature)
        param[0]=(t >> 8);
        param[1]= t & 0xff;
        param[2]=0x00;
      }
      param_len=3;
      }
      break;

    // ---------------------------------------------
    // 16-bit unsigned integer representation
    // Temperature values, mult=64
    case VT_TEMP:
    case VT_TEMP_N:
      {
      uint32_t t=((int)(atof(val)*decodedTelegram.operand));
      if (setcmd) {
        if (val[0]!='\0' && strcmp(val, "---")) {
          param[0]=decodedTelegram.enable_byte;
        } else {
          param[0]=decodedTelegram.enable_byte-1;
        }
        param[1]=(t >> 8);
        param[2]= t & 0xff;
      } else { // INF message type
        if ((cmdtbl[i].flags & FL_SPECIAL_INF)) {   // Case for room temperature
          param[0]=(t >> 8);
          param[1]= t & 0xff;
          param[2]=0x00;
        } else {                // Case for outside temperature
          param[0]=0;
          param[1]=(t >> 8);
          param[2]= t & 0xff;
        }
      }
      param_len=3;
      }
      break;

    // ---------------------------------------------
    // Schedule data
    case VT_YEAR:
    case VT_DAYMONTH:
    case VT_TIME:
    case VT_VACATIONPROG:
    case VT_DATETIME:
      {
      // /S0=dd.mm.yyyy_mm:hh:ss
      int d = 1; int m = 1; int y = 0xFF; int hour = y; int min = y; int sec = y;
      uint8_t date_flag = 0;
      const char *error_msg = NULL;
      if (val[0]!='\0' && strcmp(val, "---")) {
        switch(decodedTelegram.type){
          case VT_YEAR:
            if (sscanf(val, "%d", &y) != 1) {
              decodedTelegram.error = 262;
              error_msg = "year!";
            } else {
              // Send to the PC hardware serial interface (DEBUG)
              printFmtToDebug("year: %d\r\n", y);
              date_flag = 0x0F;
            }
          break;
          case VT_DAYMONTH:
          case VT_VACATIONPROG:
            if (sscanf(val, "%d.%d.", &d, &m) != 2) {
              decodedTelegram.error = 262;
              error_msg = "day/month!";
            } else {
              // Send to the PC hardware serial interface (DEBUG)
              printFmtToDebug("day/month: %d.%d.\r\n", d, m);
              if (decodedTelegram.type == VT_DAYMONTH) {
                date_flag = 0x16;
              } else {
                date_flag = 0x17;
              }
            }
          break;
          case VT_TIME:
            if (sscanf(val, "%d:%d:%d", &hour, &min, &sec) != 3) {
              decodedTelegram.error = 262;
              error_msg = "time!";
            } else {
              // Send to the PC hardware serial interface (DEBUG)
              printFmtToDebug("time: %d:%d:%d\r\n", hour, min, sec);
              date_flag = 0x1D;
            }
          break;
          case VT_DATETIME:
            if (sscanf(val, "%d.%d.%d%*c%d:%d:%d", &d, &m, &y, &hour, &min, &sec) != 6) {
              decodedTelegram.error = 262;
              error_msg = "date/time!";
            } else {
              // Send to the PC hardware serial interface (DEBUG)
              printFmtToDebug("date time: %d.%d.%d %d:%d:%d\r\n", d, m, y, hour, min, sec);
              date_flag = 0x00;
            }
          break;
        }
        if(decodedTelegram.error == 262){
          printToDebug("Too few/many arguments for ");
          printlnToDebug(error_msg);
          return 0;
        }
        param[0]=decodedTelegram.enable_byte;
      } else {
        param[0]=decodedTelegram.enable_byte-1;
      }
      // Set up the command payload
      uint8_t dow = dayofweek(d,m,y);
      if (decodedTelegram.type == VT_VACATIONPROG) {
        y = 1900; dow = 0; hour = dow; min = dow; sec = dow; date_flag = 0x17;
      }
      param[1]=y-1900;
      param[2]=m;
      param[3]=d;
      param[4]=dow;
      param[5]=hour;
      param[6]=min;
      param[7]=sec;
      param[8]=date_flag;
      param_len=9;
      }
      break;
    // ---------------------------------------------
    // Schedule up to three ON-OFF blocks per day; at least one ON-OFF
    // block must be defined. Begin and end times are given hour minute.
    case VT_TIMEPROG: // TODO test it
      {
      //S502=05:00-22:00_xx:xx-xx:xx_xx:xx-xx:xx
      //DISP->HEIZ SET  502 Zeitprogramm Heizkreis 1 -  Mi: 1. 05:00 - 22:00 2. --:-- - --:-- 3. --:-- - --:--
      //DC 8A 00 17 03 3D 05 0A 8E 05 00 16 00 80 00 00 00 80 00 00 00 08 98
      // Default values if not requested otherwise
      int h1s=0x80,m1s=0x00,h2s=0x80,m2s=0x00,h3s=0x80,m3s=0x00;
      int h1e=0x80,m1e=0x00,h2e=0x80,m2e=0x00,h3e=0x80,m3e=0x00;
      // we need at least the first period
      if (sscanf(val,"%d:%d-%d:%d%*c%d:%d-%d:%d%*c%d:%d-%d:%d",&h1s,&m1s,&h1e,&m1e,&h2s,&m2s,&h2e,&m2e,&h3s,&m3s,&h3e,&m3e)<4) {     // BEGIN hour/minute and END hour/minute
        return 0;
      }
      param[0]=h1s;     // minimum definition
      param[1]=m1s;
      param[2]=h1e;
      param[3]=m1e;

      param[4]=h2s;     // use default values if undefined
      param[5]=m2s;
      param[6]=h2e;
      param[7]=m2e;

      param[8]=h3s;     // use default values if undefined
      param[9]=m3s;
      param[10]=h3e;
      param[11]=m3e;
      param_len=12;
      }
      break;
    // ---------------------------------------------
    case VT_CUSTOM_ENUM:
    {
      uint8_t t=atoi(val);
      int8_t return_value = bus->Send(TYPE_QINF, c, msg, tx_msg);
      if (return_value != BUS_OK) {
        printlnToWebClient("No response to initial query, cannot get required data, aborting.");
        printFmtToDebug("Error: %d", return_value);
      }
      int data_len;
      if (bus->getBusType() == BUS_LPB) {
        data_len=msg[bus->getLen_idx()]-14;     // get packet length, then subtract
      } else {
        data_len=msg[bus->getLen_idx()]-11;     // get packet length, then subtract
      }

      if (data_len > 18) {
        printFmtToDebug("Set failed, invalid data length: %d\r\n", data_len);
        return 0;
      }

      uint8_t idx = pgm_read_byte_far(decodedTelegram.enumstr+0);

      for (int x=bus->getPl_start();x<bus->getPl_start()+data_len;x++) {
        param[x-bus->getPl_start()] = msg[x];
      }
      param[idx] = t;
      param_len = data_len;
      break;
    }
    // ---------------------------------------------
/*
    case VT_VOLTAGE: // read only (Ein-/Ausgangstest)
    case VT_LPBADDR: // read only (LPB-System - Aussentemperaturlieferant)
    case VT_PRESSURE_WORD: // read only (Diagnose Verbraucher)
    case VT_FP1: // read only (SW-Version)
    case VT_ERRORCODE: // read only
    case VT_UNKNOWN:
*/
    default:
      printlnToDebug("Unknown type or read-only parameter");
      return 2;
    break;
  } // endswitch

  // Send a message to PC hardware serial port
  printFmtToDebug("setting line: %g val: ", line);
  SerialPrintRAW(param,param_len);
  writelnToDebug();

  uint8_t t=setcmd?TYPE_SET:TYPE_INF;

  // Send telegram to the bus
  if (bus->Send(t           // message type
             , c           // command code
             , msg         // receive buffer
             , tx_msg      // xmit buffer
             , param       // payload
             , param_len   // payload length
             , setcmd) != BUS_OK)    // wait_for_reply
  {
    printFmtToDebug("set failed\r\n");
    return 0;
  }

  // Decode the xmit telegram and send it to the PC serial interface
  if (verbose) {
    printTelegram(tx_msg, line);
    LogTelegram(tx_msg);
  }

  // no answer for TYPE_INF
  if (t!=TYPE_SET) return 1;

  // Decode the rcv telegram and send it to the PC serial interface
  printTelegram(msg, line);
  LogTelegram(msg);
  // Expect an acknowledgement to our SET telegram
  if (msg[4+bus->offset]!=TYPE_ACK) {      // msg type at 4 (BSB) or 8 (LPB)
    printlnToDebug("set failed NACK");
    return 0;
  }

  return 1;
} // --- set() ---

/**  *****************************************************************
 *  Function: queryDefaultValue()
 *  Does:     This routine reset parameters to their default values.
 * Pass parameters:
 *  uint16  line     the line number (ProgNr)
 *  byte  * msg     telegram
 *  byte *tx_msg      telegram
 * Parameters passed back:
 *
 * Function value returned:
 *  0         failure (incomplete input data, ..)
 *
 * Global resources used:
 *  Serial instance
 *  bus    instance
 * *************************************************************** */
int queryDefaultValue(float line, byte *msg, byte *tx_msg) {
  resetDecodedTelegram();
  if (line < 0) {
    decodedTelegram.error = 258; //not found
    return 0;
  }
  int i=findLine(line);
  uint32_t c = cmdtbl[i].cmd;
  if ( i < 0) {
    decodedTelegram.error = 258; //not found
    return 0;
  } else {
    if (bus->Send(TYPE_QRV, c, msg, tx_msg) != BUS_OK) {
      decodedTelegram.error = 261; //query failed
      return 0;
    } else {
      // Decode the xmit telegram and send it to the debug interface
      if (verbose) {
        printTelegram(tx_msg, line);
        LogTelegram(tx_msg);
      }

      // Decode the rcv telegram and send it to the debug interface
      printTelegram(msg, line);   // send to debug interface
      LogTelegram(msg);
    }
  }
  return 1;
}

const char* printError(uint16_t error) {
  const char *errormsgptr;
  switch (error) {
    case 0: errormsgptr =  ""; break;
    case 7: errormsgptr = " (parameter not supported)"; break;
    case 256: errormsgptr = " - decoding error"; break;
    case 257: errormsgptr =  " unknown command"; break;
    case 258: errormsgptr = " - not found"; break;
    case 259: errormsgptr = " no enum str"; break;
    case 260: errormsgptr = " - unknown type"; break;
    case 261: errormsgptr =  " query failed"; break;
    default: if (error < 256) errormsgptr = " (bus error)"; else errormsgptr = " (??? error)"; break;
  }
  return errormsgptr;
}

/**  *****************************************************************
 *  Function: build_pvalstr()
 *  Does:     Legacy. Function for compatibility.
 *            Build pvalstr from decodedTelegram structure.
 *            format like in old query() function
 * Pass parameters:
 *  bool extended
 *
 * Parameters passed back:
 *
 * Function value returned:
 *  char  * pvalstr      pointer to string
 *
 * Global resources used:
 *  outBuf
 ** *************************************************************** */
char *build_pvalstr(bool extended) {
  int len = 0;
  outBuf[len] = 0;
  if (extended && decodedTelegram.error != 257 && decodedTelegram.prognr >= 0) {
    len+=sprintf_P(outBuf, "%g ", decodedTelegram.prognr);

    len+=strlen(strcpy(outBuf + len, decodedTelegram.catdescaddr));
    len+=strlen(strcpy(outBuf + len, " - "));
    if (decodedTelegram.prognr >= (float)BSP_AVERAGES && decodedTelegram.prognr < (float)BSP_AVERAGES + numAverages) {
      len+=strlen(strcpy(outBuf + len, STR_24A_TEXT));
      len+=strlen(strcpy(outBuf + len, ". "));
    }
    len+=strlen(strcpy(outBuf + len, decodedTelegram.prognrdescaddr));
    if (decodedTelegram.sensorid) {
      len+=sprintf_P(outBuf + len, " #%d", decodedTelegram.sensorid);
    }
    len+=strlen(strcpy(outBuf + len, ": "));
  }
  if (decodedTelegram.value[0] != 0 && decodedTelegram.error != 260) {
    len+=strlen(strcpy(outBuf + len, decodedTelegram.value));
  }
  if (decodedTelegram.data_type == DT_ENUM || decodedTelegram.data_type == DT_BITS) {
    if (decodedTelegram.enumdescaddr) {
      strcpy(outBuf + len, " - ");
      strcat(outBuf + len, decodedTelegram.enumdescaddr);
      len+=strlen(outBuf + len);
     }
  } else {
    if (decodedTelegram.unit[0] != 0 && decodedTelegram.error != 7) {
      strcpy(outBuf + len, " ");
      strcat(outBuf + len, decodedTelegram.unit);
      len+=strlen(outBuf + len);
    }
  }
  if (decodedTelegram.telegramDump) {
    strcpy(outBuf + len, " ");
    strcat(outBuf + len, decodedTelegram.telegramDump);
    len+=strlen(outBuf + len);
  }

  strcpy(outBuf + len, printError(decodedTelegram.error));
  return outBuf;
}

void query_program_and_print_result(int line, const char* prefix, const char* suffix) {
  if (prefix) printToWebClient(prefix);
  query(line);
  if (decodedTelegram.prognr < 0) return;
  printToWebClient_prognrdescaddr();
  if (suffix) {
    printToWebClient(suffix);
  } else {
    printToWebClient(": ");
  }
  printToWebClient(build_pvalstr(0));
}

/** *****************************************************************
 *  Function:  query_printHTML()
 *  Does:      print HTML after query() call
 *  Pass parameters:
 *
 * Parameters passed back:
 *   none
 * Function value returned:
 *
 * Global resources used:
 *   Serial instance
 *   bus    instance
 *   client instance
 *   decodedTelegram   error status, r/o flag
 * *************************************************************** */
void query_printHTML() {
  if (decodedTelegram.msg_type == TYPE_ERR) {
    if (decodedTelegram.error == 7 && !show_unknown) return;
    printToWebClient("<tr style='color: #7f7f7f'><td>");
  } else {
    printToWebClient("<tr><td>");
  }
  printToWebClient(build_pvalstr(1));

/*
      // dump data payload for unknown types
      if (type == VT_UNKNOWN && msg[4+(bus->offset)] != TYPE_ERR) {
        int data_len;
        if (bus_type == BUS_LPB) {
          data_len=msg[len_idx]-14;     // get packet length, then subtract
        } else {
          data_len=msg[len_idx]-11;     // get packet length, then subtract
        }
        for (i=0;i<=data_len-1;i++) {
          if (msg[pl_start+i] < 16) client.print("0");  // add a leading zero to single-digit values
          client.print(msg[pl_start+i], HEX);
        }
      }
*/

    const char fieldDelimiter[] = "</td><td>";
      printToWebClient(fieldDelimiter);
      if (decodedTelegram.msg_type != TYPE_ERR && decodedTelegram.type != VT_UNKNOWN) {
        if (decodedTelegram.data_type == DT_ENUM || decodedTelegram.data_type == DT_BITS) {
          printToWebClient("<select ");
          if (decodedTelegram.data_type == DT_BITS) {
            printToWebClient("multiple ");
          }
          printFmtToWebClient("id='value%g-%d'>\r\n", decodedTelegram.prognr, bus->getBusDest());
          uint16_t value = 0;
          if (decodedTelegram.data_type == DT_BITS) {
            for (int i = 0; i < 8; i++) {
              if (decodedTelegram.value[i] == '1') value+=1<<(7-i);
            }
          } else {
            value = strtod(decodedTelegram.value, NULL);
            if (decodedTelegram.readwrite == FL_WONLY) value = 65535;
          }
          listEnumValues(decodedTelegram.enumstr, decodedTelegram.enumstr_len, STR_OPTION_VALUE, "'>", STR_SELECTED, STR_CLOSE_OPTION, NULL, value,
            decodedTelegram.data_type == DT_BITS?(PRINT_VALUE|PRINT_DESCRIPTION|PRINT_VALUE_FIRST|PRINT_ENUM_AS_DT_BITS):
            (PRINT_VALUE|PRINT_DESCRIPTION|PRINT_VALUE_FIRST));
          printToWebClient("</select>");
          printToWebClient(fieldDelimiter);
          if (decodedTelegram.readwrite != FL_RONLY) { //not "read only"
            printToWebClient("<input type=button value='Set' onclick=\"set");
            if (decodedTelegram.type == VT_BIT) {
              printToWebClient("bit");
            }
            printFmtToWebClient("(%g,%d)\">", decodedTelegram.prognr, bus->getBusDest());
          }
        } else {
          printFmtToWebClient("<input type=text id='value%g-%d' VALUE='%s'>", decodedTelegram.prognr, bus->getBusDest(), decodedTelegram.value);
          printToWebClient(fieldDelimiter);
          if (decodedTelegram.readwrite != FL_RONLY) { //not "read only"
            printFmtToWebClient("<input type=button value='Set' onclick=\"set(%g,%d)\">", decodedTelegram.prognr, bus->getBusDest());
          }
        }
      }
      printToWebClient("</td></tr>\r\n");

// TODO: check at least for data length (only used for temperature values)
/*
int data_len=msg[3]-11;
if (data_len==3) {
  returnval = printFIXPOINT(msg,data_len,64.0,1,"");
}
*/
  flushToWebClient();
}

void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCA9548A_ADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

/** *****************************************************************
 *  Function:  queryVirtualPrognr(int line)
 *  Does:      query values from virtual programs which correspond to One wire, DHT and MAX sensors.
 *  Pass parameters:
 *
 * Parameters passed back:
 *   none
 * Function value returned:
 *
 * Global resources used:
 *   decodedTelegram   error status, r/o flag
 * *************************************************************** */
void queryVirtualPrognr(float line, int table_line) {
  loadCategoryDescAddr(); //Get current value from decodedTelegram.cat and load description address to decodedTelegram.catdescaddr
  printFmtToDebug("\r\nVirtual parameter %g queried. Table line %d\r\n", line, table_line);
  decodedTelegram.msg_type = TYPE_ANS;
  decodedTelegram.prognr = line;
  switch (recognizeVirtualFunctionGroup(line)) {
    case 1: {
      uint32_t val = 0;
      switch ((uint16_t)line) {
        case BSP_INTERNAL + 0: val = brenner_duration; break;
        case BSP_INTERNAL + 1: val = brenner_count; break;
        case BSP_INTERNAL + 2: val = brenner_duration_2; break;
        case BSP_INTERNAL + 3: val = brenner_count_2; break;
        case BSP_INTERNAL + 4: val = TWW_duration; break;
        case BSP_INTERNAL + 5: val = TWW_count; break;
        case BSP_INTERNAL + 6: val = 0; break;
      }
      sprintf_P(decodedTelegram.value, "%ld", val);
      return;
    }
    case 2: {
      size_t tempLine = roundf(line - (float)BSP_AVERAGES);
      _printFIXPOINT(decodedTelegram.value, avgValues[tempLine], 1);
      return;
      break;
    }
    case 3: {
      size_t log_sensor = roundf(line - (float)BSP_DHT22);
      int tempLine = (int)roundf((line - (float)BSP_DHT22) * 10) % 10;
      if (tempLine == 0) { //print sensor ID
        sprintf_P(decodedTelegram.value, "%d", DHT_Pins[log_sensor]);
        return;
      }
      unsigned long temp_timer = millis();
      if (DHT_Timer + 2000 < temp_timer || DHT_Timer > temp_timer) last_DHT_pin = 0;
      if (last_DHT_pin != DHT_Pins[log_sensor]) {
        last_DHT_pin = DHT_Pins[log_sensor];
        DHT_Timer = millis();
#if defined(ESP32)
        dht.setup(last_DHT_pin, DHTesp::DHT22);
#else
        dht.setup(last_DHT_pin, DHTesp::AUTO_DETECT);
#endif
      }

      printFmtToDebug("DHT22 sensor: %d - ", last_DHT_pin);
      switch (dht.getStatus()) {
        case DHTesp::ERROR_CHECKSUM:
          decodedTelegram.error = 256;
          printlnToDebug("Checksum error");
          break;
          case DHTesp::ERROR_TIMEOUT:
          decodedTelegram.error = 261;
          printlnToDebug("Time out error");
         break;
        default:
          printlnToDebug("OK");
          break;
      }

      float hum = dht.getHumidity();
      float temp = dht.getTemperature();
      if (hum > 0 && hum < 101) {
        printFmtToDebug("#dht_temp[%d]: %.2f, hum[%d]:  %.2f\r\n", log_sensor, temp, log_sensor, hum);
        switch (tempLine) {
          case 1: //print sensor Current temperature
            _printFIXPOINT(decodedTelegram.value, temp, 2);
            break;
          case 2: //print sensor Humidity
            _printFIXPOINT(decodedTelegram.value, hum, 2);
            break;
          case 3: //print sensor Abs Humidity
            _printFIXPOINT(decodedTelegram.value, (216.7*(hum/100.0*6.112*exp(17.62*temp/(243.12+temp))/(273.15+temp))), 2);
            break;
        }
      } else {
        undefinedValueToBuffer(decodedTelegram.value);
      }
      return;
      break;
    }
    case 4: {
      size_t log_sensor = roundf(line - (float)BSP_ONEWIRE);
      if (One_Wire_Pin >= 0 && numSensors) {
        switch (((int)roundf((line - (float)BSP_ONEWIRE) * 10)) % 10) {
          case 0: //print sensor ID
            DeviceAddress device_address;
            sensors->getAddress(device_address, log_sensor);
            bin2hex(decodedTelegram.value, device_address, 8, 0);
            break;
          case 1: {
            float t=sensors->getTempCByIndex(log_sensor);
            if (t == DEVICE_DISCONNECTED_C) { //device disconnected
              decodedTelegram.error = 261;
              undefinedValueToBuffer(decodedTelegram.value);
              return;
            }
            _printFIXPOINT(decodedTelegram.value, t, 2);
            break;
          }
          default: break;
        }
        return;
      }
      break;
    }
    case 5: {
      size_t log_sensor = roundf(line - (float)BSP_MAX);
      if (enable_max_cul) {
        if (max_devices[log_sensor]) {
          switch (((int)roundf((line - (float)BSP_MAX) * 10)) % 10){ //print sensor values
            case 0:  //print sensor ID
              strcpy(decodedTelegram.value, max_device_list[log_sensor]);
              break;
            case 1:
              if (max_dst_temp[log_sensor] > 0) {
                sprintf_P(decodedTelegram.value, "%.2f", ((float)max_cur_temp[log_sensor] / 10));
              } else {
                decodedTelegram.error = 261;
                undefinedValueToBuffer(decodedTelegram.value);
              }
              break;
            case 2:
              if (max_dst_temp[log_sensor] > 0) {
                sprintf_P(decodedTelegram.value, "%.2f", ((float)max_dst_temp[log_sensor] / 2));
              } else {
                decodedTelegram.error = 261;
                undefinedValueToBuffer(decodedTelegram.value);
              }
              break;
            case 3:
              if (max_valve[log_sensor] > -1) {
                sprintf_P(decodedTelegram.value, "%d", max_valve[log_sensor]);
              } else {
                decodedTelegram.error = 261;
                undefinedValueToBuffer(decodedTelegram.value);
              }
              break;
          }
          return;
        }
      }
    break;
    }
    case 6: {
      sprintf_P(decodedTelegram.value, "%.2f", custom_floats[((uint16_t)line) - BSP_FLOAT]);
      return;
    }
    case 7: {
      sprintf_P(decodedTelegram.value, "%ld", custom_longs[((uint16_t)line) - BSP_LONG]);
      return;
    }
    case 8: {
      size_t log_sensor = roundf(line - (float)BSP_BME280);
      uint8_t selector = ((int)roundf((line - (float)BSP_BME280) * 10)) % 10;
      if (selector == 0) {
        if(BME_Sensors > 2){
          sprintf_P(decodedTelegram.value, "%02X-%02X", log_sensor & 0x07, 0x76 + log_sensor / 8);
        } else {
          sprintf_P(decodedTelegram.value, "%02X", 0x76 + log_sensor);
        }
        return;
      }
      if(BME_Sensors > 2){
        tcaselect(log_sensor & 0x07);
      }
      switch(bme[log_sensor].checkID()) {
        case 0x58: if(selector == 2 || selector == 5) selector = 6; break; //BMP280. Set error value for humidity measurement
        case 0x60: break; //BME280
        default: selector = 6; break; //set error value
      }
      switch (selector) {
        case 1: _printFIXPOINT(decodedTelegram.value, bme[log_sensor].readTempC(), 2); break;
        case 2: _printFIXPOINT(decodedTelegram.value, bme[log_sensor].readHumidity(), 2); break;
        case 3: _printFIXPOINT(decodedTelegram.value, bme[log_sensor].readPressure(), 2); break;
        case 4: _printFIXPOINT(decodedTelegram.value, bme[log_sensor].readAltitudeMeter(), 2); break;
        case 5: {float temp = bme[log_sensor].readTempC(); _printFIXPOINT(decodedTelegram.value, (216.7*(bme[log_sensor].readHumidity()/100.0*6.112*exp(17.62*temp/(243.12+temp))/(273.15+temp))), 2);} break;
        case 6: decodedTelegram.error = 261; undefinedValueToBuffer(decodedTelegram.value); break;
      }
      return;
      break;
    }
  }
  decodedTelegram.error = 7;
  decodedTelegram.msg_type = TYPE_ERR;
  return;
}
/** *****************************************************************
 *  Function:  query()
 *  Does:      Retrieves parameter from the heater controller.
 *             Addresses the controller parameters by line (ProgNr).
 *             The query() function can interrogate a whole range
 *             of ProgNrs, delimited by line_start and line_end
 *             inclusive.
 *  Pass parameters:
 *   uint16 line  retrieve this progNr
 * Parameters passed back:
 *   none
 * Function value returned:
 *   result string
 * Global resources used:
 *   char outBuf[]
 *   Serial instance
 *   bus    instance
 *   client instance
 *   decodedTelegram   error status, r/o flag
 * *************************************************************** */
void query(float line) {  // line (ProgNr)
  byte msg[33] = { 0 };      // response buffer
  byte tx_msg[33] = { 0 };   // xmit buffer
  int i=0;
  int retry;
  resetDecodedTelegram();
#if defined(ESP32)
  esp_task_wdt_reset();
#endif

  i=findLine(line);
  uint32_t c = cmdtbl[i].cmd;
  uint8_t query_type = TYPE_QUR;
  uint16_t dev_flags = cmdtbl[i].flags;
  if (dev_flags & FL_QINF_ONLY) {
    query_type = TYPE_QINF;
  }
  if (dev_flags & FL_NOSWAP_QUR) {
    c=((c & 0xFF000000) >> 8) | ((c & 0x00FF0000) << 8) | (c & 0x0000FFFF); // Bytes 1+2 of CoID will be swapped for QUR command, but need to remain as-is for FL_NOSWAP_QUR parameters, so swap here again.
  }
  if (i>=0) {
    loadPrognrElementsFromTable(line, i);
    if (decodedTelegram.readwrite == FL_WONLY) { //"write only"
      printFmtToDebug("%g ", line);
      loadCategoryDescAddr();
      printToDebug(" - ");
      printToDebug(decodedTelegram.prognrdescaddr);
      printToDebug(" - write-only\r\n");
      return;
    }

// virtual programs
    if ((line >= (float)BSP_INTERNAL && line < (float)BSP_END)) {
      queryVirtualPrognr(line, i);
      if ((LoggingMode & CF_LOGMODE_MQTT) && !(LoggingMode & CF_LOGMODE_MQTT_ONLY_LOG_PARAMS)) {
        LogToMQTT(line);
      }
      return;
    }
    //printlnToDebug("found");
    if (c!=CMD_UNKNOWN && (dev_flags & FL_NO_CMD) != FL_NO_CMD) {     // send only valid command codes
      if (bus->getBusType() != BUS_PPS) {  // bus type is not PPS
        retry=QUERY_RETRIES;
        while (retry) {
          if (bus->Send(query_type, c, msg, tx_msg) == BUS_OK) {
            // Decode the xmit telegram and send it to the PC serial interface
            if (verbose) {
              printTelegram(tx_msg, line);
              LogTelegram(tx_msg);
            }

            // Decode the rcv telegram and send it to the PC serial interface
            printTelegram(msg, line);
            printFmtToDebug("#%g: ", line);
            printlnToDebug(build_pvalstr(0));
            SerialOutput->flush();
            LogTelegram(msg);
            if ((LoggingMode & CF_LOGMODE_MQTT) && !(LoggingMode & CF_LOGMODE_MQTT_ONLY_LOG_PARAMS)) {
              LogToMQTT(line);
            }
            break;   // success, break out of while loop
          } else {
            printlnToDebug(printError(261)); //query failed
            retry--;          // decrement number of attempts
          }
        } // endwhile, maximum number of retries reached
        if (retry==0) {
          if (bus->getBusType() == BUS_LPB && msg[8] == TYPE_ERR) {    // only for BSB because some LPB systems do not really send proper error messages
            printFmtToDebug("error %d\r\n", msg[9]); //%d
          } else {
            printFmtToDebug("%g\r\n", line);
          }
          decodedTelegram.error = 261;
        }
      } else { // bus type is PPS
        if (line < 15000) return;
        uint32_t cmd = cmdtbl[i].cmd;
        uint16_t temp_val = 0;
        switch (decodedTelegram.type) {
//          case VT_TEMP: temp_val = pps_values[(c & 0xFF)] * 64; break:
//          case VT_BYTE: temp_val = pps_values[((uint16_t)line)-15000] * 256; break;
//          case VT_YESNO: temp_val = pps_values[((uint16_t)line)-15000] * 256; decodedTelegram.isswitch = 1; break;
          case VT_ONOFF:
          case VT_YESNO: temp_val = pps_values[((uint16_t)line)-15000]; decodedTelegram.isswitch = 1; break;
//          case VT_HOUR_MINUTES: temp_val = ((pps_values[(uint16_t)line)-15000] / 6) * 256) + ((pps_values[(uint16_t)line)-15000] % 6) * 10); break;
//          case VT_HOUR_MINUTES: temp_val = (pps_values[(uint16_t)line)-15000] / 6) + ((pps_values[(uint16_t)line)-15000] % 6) * 10); break;
          default: temp_val = pps_values[((uint16_t)line)-15000]; break;
        }

        if (decodedTelegram.type == VT_TIMEPROG) {
          msg[bus->getPl_start()+1]= pps_values[((uint16_t)line)-15000];
          msg[bus->getPl_start()+0]= pps_values[((uint16_t)line)-15000+1];
          msg[bus->getPl_start()-1]= pps_values[((uint16_t)line)-15000+2];
          msg[bus->getPl_start()-2]= pps_values[((uint16_t)line)-15000+3];
          msg[bus->getPl_start()-3]= pps_values[((uint16_t)line)-15000+4];
          msg[bus->getPl_start()-4]= pps_values[((uint16_t)line)-15000+5];
        } else {
          msg[1] = ((cmd & 0x00FF0000) >> 16);
          msg[4+bus->offset]=TYPE_ANS;
          msg[bus->getPl_start()]=temp_val >> 8;
          msg[bus->getPl_start()+1]=temp_val & 0xFF;
        }
/*
        msg[5] = c >> 24;
        msg[6] = c >> 16 & 0xFF;
        msg[7] = c >> 8 & 0xFF;
        msg[8] = c & 0xFF;
*/
        printTelegram(msg, line);

        printFmtToDebug("#%g: ", line);
        printlnToDebug(build_pvalstr(0));
        if ((LoggingMode & CF_LOGMODE_MQTT) && !(LoggingMode & CF_LOGMODE_MQTT_ONLY_LOG_PARAMS)) {
          LogToMQTT(line);
        }
        SerialOutput->flush();
      }
    } else {
      //printlnToDebug("unknown command");
      //if (line_start==line_end) outBufLen+=sprintf(outBuf+outBufLen,"%.1f unknown command",line);
    } // endelse, valid / invalid command codes
  } else {
    //printlnToDebug("line not found");
    //if (line_start==line_end) outBufLen+=sprintf(outBuf+outBufLen,"%.1f line not found",line);
  } // endelse, line (ProgNr) found / not found
} // --- query() ---

/** *****************************************************************
 *  Function:  query()
 *  Does:      Retrieves parameters from the heater controller.
 *             Addresses the controller parameters by line (ProgNr).
 *             The query() function can interrogate a whole range
 *             of ProgNrs, delimited by line_start and line_end
 *             inclusive.
 *  Pass parameters:
 *   uint16 linestart  begin to retrieve at this RogNr
 *   uint16 lineend    stop at this ProgNr
 *   bool   noprint    True:  do not display results in the web client
 *                     False: display results in the web client
 * Parameters passed back:
 *   none
 * Function value returned:
 *   result string
 * Global resources used:
 *   char outBuf[]
 *   Serial instance
 *   bus    instance
 *   client instance
 *   decodedTelegram   error status, r/o flag
 * *************************************************************** */
void query(float line_start  // begin at this line (ProgNr)
          , float line_end    // end with this line (ProgNr)
          , bool no_print)    // display in web client?
{
  float line = line_start;     // ProgNr
  do {
    query(line);
    if (decodedTelegram.prognr != -1) {
      if (!no_print) {         // display in web client?
        if (!client.connected()) {
          printToDebug("Client no longer connected, aborting query...\r\n");
          return;  // no need to waste time here when client is gone
        }
        query_printHTML();
      }
    }
    line = get_next_prognr(line);
  } while(line >= line_start && line < line_end+1); // endfor, for each valid line (ProgNr) command within selected range
}

void GetDevId() {
  if (bus->getBusType() != BUS_PPS) {
    if (dev_lookup[0].dev_id == 0xFF) {
      byte  msg[33] = { 0 };
      byte  tx_msg[33] = { 0 };
      uint8_t save_destAddr = bus->getBusDest();

      // count number of different device families/variants in category list (if any)
      const char* enumstr = ENUM_CAT;
      const uint16_t enumstr_len = sizeof(ENUM_CAT);
      uint16_t cat_dev = 0;
      uint16_t c=0;
      uint16_t dev_array[100] = { 0 };
      uint8_t arr_counter = 0;
      uint8_t anz_dev = 0;
      while (c<enumstr_len) {
        if (*(enumstr+c+3)==' ') {
          cat_dev = *(enumstr+c+1);
          c+=2;
          bool found = false;
          for (int i=0;i<sizeof(dev_array);i++) {
            if (dev_array[i] == 0) break;
            if (dev_array[i] == cat_dev) found = true; 
          }
          if (found == false) {
            dev_array[arr_counter] = cat_dev;
            arr_counter++;
            anz_dev++;
          }
        }
        //skip leading space
        c+=2;
        while (*(enumstr+c)!=0) c++;
        c++;
      }
      printFmtToDebug("Found %d devices in category list.\r\n", anz_dev);
      printlnToDebug("Scanning devices on the bus...");

      switch (bus->getBusType()) {
        case BUS_BSB: bus->setBusType(BUS_BSB, bus->getBusAddr(), 0x7F); break;
        case BUS_LPB: bus->setBusType(BUS_LPB, bus->getBusAddr(), 0xFF); break;
      }
    
      if (bus->Send(TYPE_QINF, 0x053D0064, msg, tx_msg, NULL, 0, false) == BUS_OK) {
        printTelegram(tx_msg, -1);
        unsigned long startquery = millis();
        while (millis() - startquery < 10000) {
          if (bus->GetMessage(msg)) {
            printTelegram(msg, -1);
//            uint8_t found_id = 0;
//            bool found = false;
            if (decodedTelegram.msg_type != TYPE_INF || decodedTelegram.dest_addr != bus->getBusAddr()) {
              break;
            }
            for (uint i=0;i<sizeof(dev_lookup)/sizeof(dev_lookup[0]);i++) {
              if (dev_lookup[i].dev_id == decodedTelegram.src_addr) {
//                found = true;
                break;
              }
              if (dev_lookup[i].dev_id == 0xFF) {
                dev_lookup[i].dev_id = decodedTelegram.src_addr;
                dev_lookup[i].dev_fam = msg[10+bus->offset];
                dev_lookup[i].dev_var = msg[12+bus->offset];
                dev_lookup[i].dev_serial = (msg[15+bus->offset] << 24) + (msg[16+bus->offset] << 16) + (msg[17+bus->offset] << 8) + (msg[18+bus->offset]);
                dev_lookup[i].name[0] = '\0';
                break;
              }
            }
          }
          delay(1);
        }
        for (uint i=0;i<sizeof(dev_lookup)/sizeof(dev_lookup[0]);i++) {
          if (dev_lookup[i].dev_id == 0xFF) break;
          bus->setBusType(bus->getBusType(), bus->getBusAddr(), dev_lookup[i].dev_id);
          if (bus->Send(TYPE_QUR, 0x053D0001, msg, tx_msg, NULL, 0, true) == BUS_OK) {
            printTelegram(tx_msg, -1);
            printTelegram(msg, -1);
            memcpy(dev_lookup[i].name, &msg[bus->getPl_start()], 17);
          } 
        }
        printlnToDebug("Bus devices found:");
        for (uint i=0;i<sizeof(dev_lookup)/sizeof(dev_lookup[0]);i++) {
          if (dev_lookup[i].dev_id == 0xFF) {
            if (i < anz_dev-1) {
              printFmtToDebug("Only %d out of %d devices have responded, will run device detection again next time.\r\n", i+1, anz_dev);
              dev_lookup[0].dev_id = 0xFF;
            }
            break;
          }
          printFmtToDebug("%d/%d/%d/%s\r\n", dev_lookup[i].dev_id, dev_lookup[i].dev_fam, dev_lookup[i].dev_var, dev_lookup[i].name);
        }
      }
      bus->setBusType(bus->getBusType(), bus->getBusAddr(), save_destAddr);
    }
    for (uint i=0;i<sizeof(dev_lookup)/sizeof(dev_lookup[0]);i++) {
      if (dev_lookup[i].dev_id == bus->getBusDest()) {
        my_dev_fam = dev_lookup[i].dev_fam;
        my_dev_var = dev_lookup[i].dev_var;
        my_dev_serial = dev_lookup[i].dev_serial;
      }
    }
  }
  return;
}

/** *****************************************************************
 *  Function:  SetDevId()
 *  Does:      Sets my_dev_fam and my_dev_var
 *
 * Pass parameters:
 *   none
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   none
 * *************************************************************** */

void SetDevId() {
  GetDevId();
  printFmtToDebug("Device family: %d\r\nDevice variant: %d\r\n", my_dev_fam, my_dev_var);
}

/** *****************************************************************
 *  Function:  SetDateTime()
 *  Does:      Sets date/time based on heating system's clock
 *
 * Pass parameters:
 *   none
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   TimeLib
 * *************************************************************** */
void SetDateTime() {
  byte rx_msg[33];      // response buffer
  byte tx_msg[33];   // xmit buffer

#if defined(ESP32)
  if (ntp_server[0]) {
    printlnToDebug("Trying to get NTP time...");
    struct tm timeinfo;
    configTime(0, 0, ntp_server);
    setenv("TZ",local_timezone,1);
    tzset();

    if(getLocalTime(&timeinfo)){
      printFmtToDebug("Date and time acquired: %02d.%02d.%02d %02d:%02d:%02d\r\n", timeinfo.tm_mday, timeinfo.tm_mon+1, timeinfo.tm_year-100, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
//      setTime(timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, timeinfo.tm_mday, timeinfo.tm_mon, timeinfo.tm_year); // not sure if setTime is necessary here or if configTime already takes care of that?
      return;
    } else {
      printlnToDebug("Acquisition failed, trying again in one minute...");
    }
  }
#endif

  if (bus->getBusType() != BUS_PPS) {
    printlnToDebug("Trying to get date and time from heater...");
    uint32_t c = cmdtbl[findLine(0)].cmd;
    if (c!=CMD_UNKNOWN) {     // send only valid command codes
      if (bus->Send(TYPE_QUR, c, rx_msg, tx_msg) == BUS_OK) {
        if (bus->getBusType() == BUS_LPB) {
          setTime(rx_msg[18], rx_msg[19], rx_msg[20], rx_msg[16], rx_msg[15], rx_msg[14]+1900);
        } else {
          setTime(rx_msg[14], rx_msg[15], rx_msg[16], rx_msg[12], rx_msg[11], rx_msg[10]+1900);
        }
      }
    }
  }
}

#include "include/print_ipwe.h"

/** *****************************************************************
 *  Function: setPPS()
 *  Does:     stores a PPS parameter received from the heater
 * Pass parameters:
 *  PPS parameter index, value
 * Parameters passed back:
 *  value_has_changed
 * Function value returned:
 *  1 (value has changed) or 0 (has not changed)
 * Global resources used:
 *  pps_values[]
 * *************************************************************** */

uint16_t setPPS(uint8_t pps_index, int16_t value) {
  uint16_t log_parameter = 0;
  if (pps_values[pps_index] != value) {
    if (LoggingMode & CF_LOGMODE_SD_CARD) {
      for (int i=0; i < numLogValues; i++) {
        if (log_parameters[i].number == 15000 + pps_index) {
          log_parameter = log_parameters[i].number;
        }
      }
    }
    pps_values[pps_index] = value;
  }
  return log_parameter;
}

/** *****************************************************************
 *  Function: transmitFile
 *  Does: transmit file from SD card to network client
 *  Pass parameters:
 *  File dataFile - opened file
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   client instance
 * *************************************************************** */
void transmitFile(File dataFile) {
  int logbuflen = (OUTBUF_USEFUL_LEN + OUTBUF_LEN > 1024)?1024:(OUTBUF_USEFUL_LEN + OUTBUF_LEN);
  byte *buf = 0;
#ifdef ESP32 // Arduino seems to have problems with the bigger, malloc'ed buffer
  buf = (byte*)malloc(4096);  // try to use 4 KB buffer, for improved transfer rates
#endif
  if (buf) logbuflen=4096; else buf=(byte*)bigBuff;  // fall back to static buffer, if necessary
  flushToWebClient();
  int chars_read = dataFile.read(buf, logbuflen);
  if (chars_read < 0) {
   printToWebClient("Error: Failed to read from SD card - if problem remains after reformatting, card may be incompatible.");
   forcedflushToWebClient();
  }
  while (chars_read == logbuflen && client.connected()) {
    client.write(buf, logbuflen);
    chars_read = dataFile.read(buf, logbuflen);
#if defined(ESP32)
    esp_task_wdt_reset();
#endif
    }
  if (chars_read > 0 && client.connected()) client.write(buf, chars_read);
  if (buf != (byte*)bigBuff) free(buf);
}

/** *****************************************************************
 *  Function: resetBoard
 *  Does: restart Arduino, will disconnect from MQTT if connected,
 *        required to send update the WILL topic correctly.
 *  Pass parameters:
 *   none
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   MQTT instance
 * *************************************************************** */
void resetBoard() {
  mqtt_disconnect();
  forcedflushToWebClient();
  delay(10);
  client.stop();
  delay(300);
#if defined(__SAM3X8E__)
// Reset function from https://forum.arduino.cc/index.php?topic=345209.0
  rstc_start_software_reset(RSTC);
  while (1==1) {}
#elif defined(ESP32)
  ESP.restart();
#else
  printlnToDebug("Reset function not implementing");
#endif

}

void resetAverageCalculation() {
  for (int i=0;i<numAverages;i++) {
    avgValues[i] = 0;
    avgValues_Old[i] = -9999;
    avgValues_Current[i] = 0;
  }
  avgCounter = 1;
  if (LoggingMode & CF_LOGMODE_SD_CARD) {
    SDCard.remove(averagesFileName);
  }
}

const char* datalogFileHeader = "Milliseconds;Date;Parameter;Description;Value;Unit\r\n";

const char *cleanupDatalog(unsigned nDays) {
  // keep most recent nDays only in datalog:
  // copy back of files to temporary files, remove old files, rename temporary files
  unsigned long spaceRequired=minimum_SD_size, spaceAvailable =
#ifdef ESP32
    totalBytes()-usedBytes();
#else
    SDCard.vol()->freeClusterCount() * SDCard.vol()->bytesPerCluster();
#endif
  { // Files opened within this scope will be automatically closed upon leaving it
    File indexFile = SDCard.open(datalogIndexFileName);
    if (!indexFile) return "Cannot open datalog index";
    unsigned long nBytes = nDays * datalogIndexEntrySize;
    spaceRequired += nBytes;
    long indexOffset = indexFile.size() - nBytes;
    if (indexOffset <= 0) return "Nothing to do (not that many days in the datalog)";
    //-- transfer index:
    File dataFile = SDCard.open(datalogFileName);
    if (!dataFile) return "Cannot open datalog";
    File indexTmpFile = SDCard.open(datalogIndexTemporaryFileName, FILE_WRITE);
    if (!indexTmpFile) return "Cannot open temporary index";
    compactDate_t date;
    unsigned long pos, dataStart=0, dataOffset=0, nDataBytes=0;
    indexFile.seek(indexOffset);
    while (nDays--) {
      if (indexFile.read((byte*)&date,sizeof(date)) != sizeof(date) ||
          indexFile.read((byte*)&pos ,sizeof(pos )) != sizeof(pos ))
        return "Error reading index file";
      if (!dataStart) {
        dataStart = pos;
        dataOffset = pos - strlen(datalogFileHeader);
        nDataBytes = dataFile.size() - dataStart;
        spaceRequired += nDataBytes;
        if (spaceRequired > spaceAvailable) return "Not enough space on device";
      }//if (!dataStart)
      pos -= dataOffset;
      if (indexTmpFile.write((byte*)&date,sizeof(date)) != sizeof(date) ||
          indexTmpFile.write((byte*)&pos ,sizeof(pos )) != sizeof(pos ))
        return "Error writing index file";
    }//while (nDays--)
    //-- transfer data:
    File dataTmpFile = SDCard.open(datalogTemporaryFileName, FILE_WRITE);
    if (!dataTmpFile) return "Cannot open temporary datalog";
    // we want to use a buffer size that's a power of 2:
    unsigned bufSize=1, maxSize=sizeof(bigBuff);
    while (bufSize <= maxSize) bufSize <<= 1;
    bufSize >>= 1;
    // write dataTmpFile:
    dataTmpFile.print(datalogFileHeader);
    dataFile.seek(dataStart);
    unsigned long i=0;
    while (nDataBytes) {
#ifdef ESP32
      esp_task_wdt_reset();
#endif
      if (++i % 10 == 0) { // busy indicator
        client.write('.');
        if (i % 100 == 0) client.write(' ');
        if (i % 500 == 0) client.write('\r'), client.write('\n');
//        client.flush();     // check if substitute for flush() is available since it is now deprecated. clear() only clears the RX buffer, but we want to flush the TX buffer.
      }
      unsigned nBytesToDo = nDataBytes<bufSize ? nDataBytes : bufSize;
      if (dataFile.read((byte*)bigBuff, nBytesToDo) != (int)nBytesToDo)
        return "Error reading datalog";
      if (dataTmpFile.write((byte*)bigBuff, nBytesToDo) != nBytesToDo)
        return "Error writing datalog";
      nDataBytes -= nBytesToDo;
    }//while (nDataBytes)
  }// Files go out of scope and are automatically closed
  //-- replace original files:
  SDCard.remove(datalogFileName);
  SDCard.rename(datalogTemporaryFileName, datalogFileName);
  SDCard.remove(datalogIndexFileName);
  SDCard.rename(datalogIndexTemporaryFileName, datalogIndexFileName);
  return "Success";
}

void readFirstAndPreviousDatalogDateFromFile() {
  firstDatalogDate.combined = previousDatalogDate.combined = 0;
  File indexFile = SDCard.open(datalogIndexFileName, FILE_READ);
  if (indexFile) {
    unsigned long indexFileSize = indexFile.size();
    if (indexFileSize >= datalogIndexEntrySize) {
      indexFile.read((byte*)&firstDatalogDate, sizeof(firstDatalogDate));
      indexFile.seek(indexFileSize - datalogIndexEntrySize);
      indexFile.read((byte*)&previousDatalogDate, sizeof(previousDatalogDate));
    }
    indexFile.close();
  }
}

void createDatalogIndexFile() {
  SDCard.remove(datalogIndexFileName);
  File indexFile = SDCard.open(datalogIndexFileName, FILE_WRITE);
  if (indexFile) indexFile.close();
  firstDatalogDate.combined = previousDatalogDate.combined = 0;
}

bool createdatalogFileAndWriteHeader() {
  File dataFile = SDCard.open(datalogFileName, FILE_WRITE);
  if (dataFile) {
    dataFile.print(datalogFileHeader);
    dataFile.close();
    outBuf[0] = 0;
    createDatalogIndexFile();
    return true;
  }
  return false;
}

#ifdef ESP32
uint64_t usedBytes() {
  if (LogDestination == SDCARD) {
  #if (BOARD == ESP32_NODEMCU && !defined(FORCE_SD_MMC_ON_NODEMCU))   // NodeMCU
    return SD.usedBytes();
  #else                           // Olimex or NodeMCU with SD_MMC
    return SD_MMC.usedBytes();
  #endif
  } else {
    return LittleFS.usedBytes();
  }
}

uint64_t totalBytes() {
  if (LogDestination == SDCARD) {
  #if (BOARD == ESP32_NODEMCU && !defined(FORCE_SD_MMC_ON_NODEMCU))   // NodeMCU
    return SD.totalBytes();
  #else                           // Olimex or NodeMCU with SD_MMC
    return SD_MMC.totalBytes();
  #endif
  } else {
    return LittleFS.totalBytes();
  }
}
#endif

void connectToMaxCul() {
  if (max_cul) {
    max_cul->stop();
    delete max_cul;
    max_cul = NULL;
    if (!enable_max_cul) return;
  }

  max_cul = new ComClient();
  printToDebug("Connection to max_cul: ");
  if (max_cul->connect(IPAddress(max_cul_ip_addr[0], max_cul_ip_addr[1], max_cul_ip_addr[2], max_cul_ip_addr[3]), 2323)) {
    printlnToDebug("established");
  } else {
    printlnToDebug("failed");
  }
}

void clearEEPROM(void) {
  printlnToDebug("Clearing EEPROM...");
#if defined(ESP32)
  for (uint16_t x=0; x<EEPROM_SIZE; x++) {
    EEPROM.write(x, 0xFF);
  }
  EEPROM.commit();
#else
  uint8_t empty_block[4096] = { 0xFF };
  EEPROM.fastBlockWrite(0, empty_block, 4096);
#endif
  printlnToDebug("Cleared EEPROM");
}

void internalLEDBlinking(uint16_t period, uint16_t count) {
  for (uint16_t i=0; i<count; i++) {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(period);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(period);
  }
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
}

#include "include/pps_handling.h"
#include "include/broadcast_msg_handling.h"

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *   none
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   char   outBuf[]
 *   bus    instance
 *   Serial instance
 *   client instance
 *   server instance
 * *************************************************************** */
void loop() {
  byte  msg[33] = { 0 };                       // response buffer
  byte  tx_msg[33] = { 0 };                    // xmit buffer
  char c = '\0';
  const byte MaxArrayElement=252;
  char  cLineBuffer[MaxArrayElement];  //
  byte  bPlaceInBuffer;                // index into buffer
  uint16_t log_now = 0;

  if (network_type == LAN) {
    if (ip_addr[0] == 0 || useDHCP) {
      switch (Ethernet.maintain()) {
        case 1:
          //renewed fail
          printlnToDebug("Error: renewed fail");
          break;
        case 2:
          //renewed success
          printlnToDebug("Renewed success");
          //print your local IP address:
          printToDebug("My IP address: ");
          {IPAddress t = Ethernet.localIP();
          printFmtToDebug("%d.%d.%d.%d\r\n", t[0], t[1], t[2], t[3]);}
          break;
        case 3:
          //rebind fail
          printlnToDebug("Error: rebind fail");
          break;
        case 4:
          //rebind success
          printlnToDebug("Rebind success");
          //print your local IP address:
          printToDebug("My IP address: ");
          {IPAddress t = Ethernet.localIP();
          printFmtToDebug("%d.%d.%d.%d\r\n", t[0], t[1], t[2], t[3]);}
        break;
  
        default:
          //nothing happened
          break;
      }
    }
  }
  // Monitor the bus and send incoming data to the PC hardware serial
  // interface.
  // Separate telegrams after a pause of more than one character time.
  bool busmsg = false;
  if (monitor) {
    busmsg=bus->Monitor(msg);
    if (busmsg==true) {
      LogTelegram(msg);
    }
  }
  if (!monitor || busmsg == true) {
    // Listen for incoming messages, identified them by their magic byte.
    // Method GetMessage() validates length byte and CRC.
    if (bus->GetMessage(msg) || busmsg == true) { // message was syntactically correct
       // Decode the rcv telegram and send it to the PC serial interface
      if (verbose && bus->getBusType() != BUS_PPS && !monitor) {  // verbose output for PPS comes later
        printTelegram(msg, -1);
        LogTelegram(msg);
      }

      // Is this a broadcast message?
      broadcast_msg_handling(msg);

// PPS-Bus handling
      if (bus->getBusType() == BUS_PPS) {
        log_now = pps_bus_handling(msg);
      } // End PPS-bus handling

    } // endif, GetMessage() returned True

   // At this point drop possible GetMessage() failures silently

    // Handle PPS MCBA heaters where BSB-LAN has to act as a master and treat the heater as a room unit %-/
    if (pps_values[PPS_QTP] == 0x58 && pps_write == 1) {
      if (millis() - pps_mcba_timer > 500) {
        pps_query_mcba();
        pps_mcba_timer = millis();
      }
    }

  } // endelse, NOT in monitor mode

  // Listen for incoming clients
  client = server->accept();
  if ((client || SerialOutput->available()) && client_flag == false) {
    client_flag = true;

    IPAddress remoteIP = client.remoteIP();
    // Use the overriden operater for a safe comparison, note, that != is not overriden.
    if ((trusted_ip_addr[0] != 0 && ! (remoteIP == trusted_ip_addr))
       && (trusted_ip_addr2[0] != 0 && ! (remoteIP == trusted_ip_addr2))) {
          // reject clients from unauthorized IP addresses;
      printFmtToDebug("Rejected access from %d.%d.%d.%d (Trusted 1: %d.%d.%d.%d, Trusted 2: %d.%d.%d.%d.\r\n",
        remoteIP[0], remoteIP[1], remoteIP[2], remoteIP[3],
        trusted_ip_addr[0], trusted_ip_addr[1], trusted_ip_addr[2], trusted_ip_addr[3],
        trusted_ip_addr2[0], trusted_ip_addr2[1], trusted_ip_addr2[2], trusted_ip_addr2[3]);
      client.stop();
    }

    loopCount = 0;
   // Read characters from client and assemble them in cLineBuffer
    bPlaceInBuffer=0;            // index into cLineBuffer
    boolean isSerial = false;
    while (client.connected() || SerialOutput->available()) {
      if (client.available() || SerialOutput->available()) {

        loopCount = 0;
        if (client.available()) {
          c = client.read();       // read one character
          printFmtToDebug("%c", c);         // and send it to hardware UART
        }
        if (SerialOutput->available()) {
          isSerial = true;
          c = SerialOutput->read();
          printFmtToDebug("%c", c);         // and send it to hardware UART
          int timeout = 0;
          while (SerialOutput->available() == 0 && c!='\r' && c!='\n') {
            delay(1);
            timeout++;
            if (timeout > 2000) {
              printlnToDebug("Serial input timeout");
              break;
            }
          }
        }

        if ((c!='\n') && (c!='\r') && (bPlaceInBuffer<MaxArrayElement)) {
          cLineBuffer[bPlaceInBuffer++]=c;
          continue;
        }
        // Got an EOL character
        writelnToDebug();

        // perform HTTP-Authentification by reading the remaining client data and look for credentials
        // Parsing headers
        static int buffershift = 48;
        size_t charcount=buffershift;  //Reserve space in buffer for ETag (Max 32 chars)
        uint8_t httpflags = 0; //bit 0 - authenticated: 0 - no, 1 - yes
                               //bit 1 - client browser accept gzip: 0 - no, 2 - yes
                               //bit 2 - HEAD request received from client: 0 - no, 4 - yes
                               //bit 3 - ETag header received : 0 - no, 8 - yes
                               //...
                               //bit 7 - send HTML fragment only, without header and footer. For external webserver. 0 - full HTML, 128 - fragment
        memset(outBuf,0,sizeof(outBuf));
        bool currentLineIsBlank = false;
        while (client.connected()) {
          if (client.available()) {
            char c = client.read();
            outBuf[charcount]=c;
            if (charcount < sizeof(outBuf)-1-buffershift) charcount++; //Minus reserverd space for ETag
            if (c == '\n' && currentLineIsBlank) {
              break;
            }
            if (c == '\n') {
              // you're starting a new line
              currentLineIsBlank = true;
              //Execute only if flag not set because strstr more expensive than bitwise operation
              if (!(httpflags & HTTP_GZIP) && strstr(outBuf + buffershift,"Accept-Encoding") != 0 && strstr(outBuf+16 + buffershift, "gzip") != 0) {
                httpflags |= HTTP_GZIP;
              }
              if (!(httpflags & HTTP_ETAG)) {
                char *ptr = strstr(outBuf + buffershift, "If-None-Match:");
                if (ptr != 0) {
                  httpflags |= HTTP_ETAG;
                  ptr = strchr(ptr, ':');
                  do{
                    ptr++;
                  } while (ptr[0] == ' ');
                  strcpy(outBuf, ptr); //Copy ETag to buffer. Note: '\r\n' present at end
//                  printFmtToDebug("ETag string: %s\r\n", outBuf);
                }
              }
              //Execute only if flag not set because strstr more expensive than bitwise operation
              char base64_user_pass[88] = { 0 };
              int user_pass_len = strlen(USER_PASS);
              Base64.encode(base64_user_pass, USER_PASS, user_pass_len);
              if (!(httpflags & HTTP_AUTH) && USER_PASS[0] && strstr(outBuf + buffershift,"uthorization: Basic")!=0 && strstr(outBuf + buffershift,base64_user_pass)!=0) { // HTML headers seem to be case-insensitive, some clients send "authorization" instead of "Authorization". Here this can be covered by just removing the first letter, but with other HTTP header tests above, this might be more complicated...
                httpflags |= HTTP_AUTH;
              }
              memset(outBuf + buffershift,0, charcount);
              charcount=buffershift; //Reserve space in buffer for ETag
            } else if (c != '\r') {
              // you've gotten a character on the current line
              currentLineIsBlank = false;
            }
          }
        }
        cLineBuffer[bPlaceInBuffer++]=0;
        // if no credentials found in HTTP header, send 401 Authorization Required
        if (USER_PASS[0] && !(httpflags & HTTP_AUTH) && isSerial == false) {
          printHTTPheader(HTTP_AUTH_REQUIRED, MIME_TYPE_TEXT_HTML, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_NO_DOWNLOAD, HTTP_DO_NOT_CACHE);
          printPStr(auth_req_html, sizeof(auth_req_html));
          forcedflushToWebClient();
          client.stop();
          break;
        }
        // otherwise continue like normal
        // Flush any remaining bytes from the client buffer
//        client.flush();
        // GET / HTTP/1.1 (anforderung website)
        // GET /710 HTTP/1.0 (befehlseingabe)
        // Check for HEAD request (for file caching)
        if (!strncmp(cLineBuffer, "HEAD", 4))
          httpflags |= HTTP_HEAD_REQ;
        char *u_s = strchr(cLineBuffer,' ');
        if (!u_s) u_s = cLineBuffer;
        char *u_e = strchr(u_s + 1,' ');
        if (u_e) u_e[0] = 0;
        if (u_s != cLineBuffer) strcpy(cLineBuffer, u_s + 1);
// IPWE START
        if (enable_ipwe && !strcmp(cLineBuffer, "/ipwe.cgi")) {
          Ipwe();
          break;
        }
// IPWE END

        if (!strcmp(cLineBuffer, "/favicon.ico")) {
          printHTTPheader(HTTP_OK, MIME_TYPE_IMAGE_ICON, HTTP_DO_NOT_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_NO_DOWNLOAD, HTTP_AUTO_CACHE_AGE);
          printToWebClient("\r\n");
          printPStr(favicon, 1+sizeof(favicon));
          flushToWebClient();
          break;
        }

        if (!strcmp(cLineBuffer, "/favicon.svg")) {
          printHTTPheader(HTTP_OK, MIME_TYPE_IMAGE_SVG, HTTP_DO_NOT_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_NO_DOWNLOAD, HTTP_AUTO_CACHE_AGE);
          printToWebClient("\r\n");
          printPStr(svg_favicon, sizeof(svg_favicon));
          flushToWebClient();
          break;
        }

        // Set up a pointer to cLineBuffer
        char *p=cLineBuffer;
        if (PASSKEY[0]) {
        // check for valid passkey
          p=strchr(cLineBuffer+1,'/');
          if (p==NULL) {    // no match
            break;
          }
          *p='\0';     // mark end of string
          if (strncmp(cLineBuffer+1, PASSKEY, strlen(PASSKEY))) {
            printlnToDebug("no matching passkey");
            while(client.available()) client.read();
            client.stop();
            //do not print header and footer. It is security breach
            break;
          }
          *p='/';
        }

        if (webserver) {
          printToDebug("URL: ");
          if (!strcmp(p, "/")) {
            httpflags |= HTTP_GET_ROOT;
            strcpy(p + 1, "index.html");
          }
          printlnToDebug(p);
          char *dot = strchr(p, '.');
          char *dot_t = NULL;
          while (dot) {
            dot_t = ++dot;//next symbol after dot
            dot = strchr(dot, '.');
          }
          dot = dot_t;

          int mimetype = recognize_mime(dot); //0 = unknown MIME type

          if (mimetype)  {
            File dataFile;

            // client browser accept gzip
            int suffix = 0;
            if ((httpflags & HTTP_GZIP)) {
              suffix = strlen(p);
              strcpy(p + suffix, ".gz");
              dataFile = SDCard.open(p);
            }
            if (!dataFile) {
              // reuse httpflags
              if (suffix) p[suffix] = 0;
              httpflags &= ~HTTP_GZIP; //can't use gzip because no gzipped file
              dataFile = SDCard.open(p);
            }
            // if the file is available, read from it:
            if (dataFile) {
              unsigned long filesize = dataFile.size();
              uint16_t lastWrtYr = 0;
              byte monthval = 0;
              byte dayval = 0;
              byte hourval = 0;
              byte minval = 0;
              byte secval = 0;
#if !defined(ESP32)
              {uint16_t pdate;
              uint16_t ptime;
              dataFile.getModifyDateTime(&pdate, &ptime);
              lastWrtYr = FS_YEAR(pdate);
              monthval = FS_MONTH(pdate);
              dayval = FS_DAY(pdate);
              hourval = FS_HOUR(ptime);
              minval = FS_MINUTE(ptime);
              secval = FS_SECOND(ptime);
              }
#else
              {struct stat st;
              if(stat(p, &st) == 0){
                struct tm tm;
                time_t mtime = st.st_mtime;
                localtime_r(&mtime, &tm);
                lastWrtYr = tm.tm_year + 1900;
                monthval = tm.tm_mon + 1;
                dayval = tm.tm_mday;
                hourval = tm.tm_hour;
                minval = tm.tm_min;
                secval = tm.tm_sec ;
              }}
#endif
              if ((httpflags & HTTP_ETAG))  { //Compare ETag if presented
                if (memcmp(outBuf, outBuf + buffershift, sprintf_P(outBuf + buffershift, "\"%02d%02d%d%02d%02d%02d%lu\"", dayval, monthval, lastWrtYr, hourval, minval, secval, filesize))) {
                  // reuse httpflags
                  httpflags &= ~HTTP_ETAG; //ETag not match
                }
              }

              printToDebug("File opened from SD: ");
              printlnToDebug(p);

              uint16_t code = 0;
              if ((httpflags & HTTP_ETAG)) {
                code = HTTP_NOT_MODIFIED;
              } else {
                code = HTTP_OK;
              }
              printHTTPheader(code, mimetype, HTTP_DO_NOT_ADD_CHARSET_TO_HEADER, (httpflags & HTTP_GZIP), HTTP_NO_DOWNLOAD, HTTP_AUTO_CACHE_AGE);
              if (lastWrtYr) {
                char monthname[4];
                char downame[4];
                uint8_t dowval =  dayofweek((uint8_t)dayval, (uint8_t)monthval, lastWrtYr);
                if (dowval < 1 && dowval > 7) dowval = 8;
                memcpy_P(downame, "MonTueWedThuFriSatSunERR" + dowval * 3 - 3, 3);
                downame[3] = 0;

                if (monthval < 1 && monthval > 12) monthval = 13;
                memcpy_P(monthname, "JanFebMarAprMayJunJulAugSepOctNovDecERR" + monthval * 3 - 3, 3);
                monthname[3] = 0;
                printFmtToWebClient("Last-Modified: %s, %02d %s %d %02d:%02d:%02d GMT\r\n", downame, dayval, monthname, lastWrtYr, hourval, minval, secval);
              }
              //max-age=84400 = one day, max-age=2592000 = 30 days. Last string in header, double \r\n
              printFmtToWebClient("ETag: \"%02d%02d%d%02d%02d%02d%lu\"\r\nContent-Length: %lu\r\n\r\n", dayval, monthval, lastWrtYr, hourval, minval, secval, filesize, filesize);
              flushToWebClient();
              //Send file if !HEAD request received or ETag not match
              if (!(httpflags & HTTP_ETAG) && !(httpflags & HTTP_HEAD_REQ)) {
                transmitFile(dataFile);
              }
              printToDebug((httpflags & HTTP_HEAD_REQ)?"HEAD":"GET"); printlnToDebug(" request received");

              dataFile.close();
            } else {
            // simply print the website if no index.html on SD card
              if ((httpflags & HTTP_GET_ROOT)) {
                webPrintSite();
                break;
              }
              printHTTPheader(HTTP_NOT_FOUND, MIME_TYPE_TEXT_HTML, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_NO_DOWNLOAD, HTTP_DO_NOT_CACHE);
              printToWebClient("\r\n<h2>File not found!</h2><br>File name: ");
              printToWebClient(p);
              flushToWebClient();
            }
//            client.flush();     // check if substitute for flush() is available since it is now deprecated. clear() only clears the RX buffer, but we want to flush the TX buffer.
            break;
          }
        }
        if (p[1] != 'J' && p[1] != 'C') {
          while (client.available()) client.read();
        } else {
          if ((httpflags & HTTP_ETAG))  { //Compare ETag if presented
            strcpy(outBuf + buffershift, "\"");
            strcat(outBuf + buffershift, BSB_VERSION);
            strcat(outBuf + buffershift, "\"");
            if (memcmp(outBuf, outBuf + buffershift, strlen(outBuf + buffershift))) {
              // reuse httpflags
              httpflags &= ~HTTP_ETAG; //ETag not match
            }
          }
        }
        // simply print the website
        if (!webserver && !strcmp(p, "/")) {
          webPrintSite();
          break;
        }

        // Answer to unknown requests
        if (!isdigit(p[1]) && strchr("ABCDEGIJKLMNPQRSUVWXY", p[1])==NULL) {
          webPrintHeader();
          webPrintFooter();
          break;
        }

        //Send HTML pages without header and footer (For external interface)
        if (webserver && p[1]=='W') {
          p++;
          httpflags |= HTTP_FRAG;
        }

        // setting verbosity level
        if (p[1]=='V') {
          p+=2;
          verbose=atoi(p);
          webPrintHeader();
          if (verbose>0) {
            printToWebClient(MENU_TEXT_VB1 "<BR>");
          } else {
            printToWebClient(MENU_TEXT_VB2 "<BR>");
          }
          printToWebClient("\r\n" MENU_TEXT_VB3 "\r\n");
          webPrintFooter();
          break;
        }
        // Starting MQTT auto discovery
        if (p[1]=='M') {
          p+=2;               // hopefully finds a digit there ...
          boolean create=atoi(p);    // .. to convert
          uint8_t save_my_dev_fam = my_dev_fam;
          uint8_t save_my_dev_var = my_dev_var;
          uint32_t save_my_dev_serial = my_dev_serial;
          uint8_t destAddr = bus->getBusDest();
          uint8_t tempDestAddr = destAddr;
          if (p[1]=='!') {
            set_temp_destination(atoi(&p[2]));
            tempDestAddr = bus->getBusDest();
          }
          webPrintHeader();
          if (create == true) {
            printlnToWebClient(MENU_TEXT_MAS);
          } else {
            printlnToWebClient(MENU_TEXT_MAR);
          }
          flushToWebClient();
          mqtt_connect();
          boolean mqtt_success = mqtt_send_discovery(create);
          if (tempDestAddr != destAddr) {
            return_to_default_destination(destAddr);
            my_dev_fam = save_my_dev_fam;
            my_dev_var = save_my_dev_var;
            my_dev_serial = save_my_dev_serial;
          }
          if (mqtt_success) {
            printToWebClient("\r\n" MENU_TEXT_QFE "\r\n");
          } else {
            printToWebClient("\r\n" MENU_TEXT_QFF "\r\n");
          }
          webPrintFooter();
          break;
        }

        // Send a SET command or an information message
        // char * cLineBuffer has the following structure:
        // p[1]          'S' | 'I'
        // p[3]          ProgNr (digits, any (!) length)
        // p[3+length]   '='
        // p[3+length+1] Value, any (!) length
        // There is only the buffer size which limits to the
        // permissible lengths, no sanity checks
        if ( p[1]=='S'        // SET command
          || p[1]=='I')       // INF information message
        {
          float line;
          bool setcmd= (p[1]=='S'); // True if SET command
          uint8_t destAddr = bus->getBusDest();
          p+=2;               // third position in cLineBuffer
          if (!(httpflags & HTTP_FRAG)) webPrintHeader();

          if (!isdigit(*p)) {   // now we check for digits - nice
            printToWebClient(MENU_TEXT_ER1 "\r\n");
          } else {
            uint8_t save_my_dev_fam = my_dev_fam;
            uint8_t save_my_dev_var = my_dev_var;
            uint32_t save_my_dev_serial = my_dev_serial;
            parameter param = parsingStringToParameter(p);
            line = param.number;

            if (param.dest_addr > -1) {
              set_temp_destination(param.dest_addr);
/*
              query(6225);
              my_dev_fam = strtod(decodedTelegram.value,NULL);
              query(6226);
              my_dev_var = strtod(decodedTelegram.value,NULL);
*/
            }

            p=strchr(p,'=');    // search for '=' sign
            if (p==NULL) {        // no match
                printToWebClient(MENU_TEXT_ER2 "\r\n");
            } else {
              p++;                   // position pointer past the '=' sign

              printFmtToDebug("set ProgNr %g = %s", line, p);
              writelnToDebug();
              // Now send it out to the bus
              int setresult = 0;
              setresult = set(line,p,setcmd);

              if (setresult!=1) {
                printToWebClient(MENU_TEXT_ER3 "\r\n");
                if (setresult == 2) {
                  printToWebClient(" - " MENU_TEXT_ER4 "\r\n");
                  if ((default_flag & FL_SW_CTL_RONLY) == FL_SW_CTL_RONLY && programWriteMode == 0) {
                    printToWebClient(" " MENU_TEXT_ER8 "\r\n");
                  }
                }
              } else {
                if (setcmd) {            // was this a SET command?
                  // Query controller for this value
                  query(line);  // read value back
                  query_printHTML();
                } else { // INF command

                }
              }
              if (bus->getBusDest() != destAddr) {
                return_to_default_destination(destAddr);
                my_dev_fam = save_my_dev_fam;
                my_dev_var = save_my_dev_var;
                my_dev_serial = save_my_dev_serial;
              }
            }
          }
          if (!(httpflags & HTTP_FRAG)) webPrintFooter();
          flushToWebClient();
          break;
        }
        // list categories
        if (p[1]=='K' && !isdigit(p[2])) {
          uint8_t save_my_dev_fam = my_dev_fam;
          uint8_t save_my_dev_var = my_dev_var;
          uint32_t save_my_dev_serial = my_dev_serial;
          uint8_t destAddr = bus->getBusDest();
          if (p[2]=='!') {
            set_temp_destination(atoi(&p[3]));
          }
          //list categories
          webPrintHeader();
          printToWebClient("<table><tr><td>&nbsp;</td><td>&nbsp;</td></tr>\r\n");
          float  cat_min = -1, cat_max = -1;
          for (int cat=0;cat<CAT_UNKNOWN;cat++) {
            if ((bus->getBusType() != BUS_PPS) || (bus->getBusType() == BUS_PPS && (cat == CAT_PPS || cat == CAT_USERSENSORS))) {
              printKat(cat,1);
              if (decodedTelegram.error != 258 && decodedTelegram.error != 263) {
                printFmtToWebClient("<tr><td><a href='K%d!%d'>", cat, bus->getBusDest());
                cat_min = ENUM_CAT_NR[cat*2];
                cat_max = ENUM_CAT_NR[cat*2+1];
                printToWebClient(decodedTelegram.enumdescaddr); //copy Category name to buffer
                printFmtToWebClient("</a></td><td>%g - %g</td></tr>\r\n", cat_min, cat_max);
              }
              writelnToDebug();
            }
          }
          printToWebClient("</table>");
          webPrintFooter();
          flushToWebClient();
          if (bus->getBusDest() != destAddr) {
            return_to_default_destination(destAddr);
            my_dev_fam = save_my_dev_fam;
            my_dev_var = save_my_dev_var;
            my_dev_serial = save_my_dev_serial;
          }
          break;
        }
        // list enum values
        if (p[1]=='E') {
          webPrintHeader();
          uint16_t line = atof(&p[2]);
          int i=findLine(line);
          if (i>=0) {
            loadPrognrElementsFromTable(line, i);
            // check type
            switch (decodedTelegram.type) {
              case VT_ENUM:
              case VT_WEEKDAY:
              case VT_CUSTOM_ENUM:
              case VT_CUSTOM_BIT:
              case VT_BINARY_ENUM:
              case VT_BIT:
                listEnumValues(decodedTelegram.enumstr, decodedTelegram.enumstr_len, NULL, " - ", NULL, "<br>\r\n", NULL, 0, PRINT_VALUE|PRINT_DESCRIPTION|PRINT_VALUE_FIRST);
                break;
              default: 
                printToWebClient(MENU_TEXT_ER6);
                break;
            }
          }
          webPrintFooter();
          break;
        }
        // query reset value
        if (p[1]=='R') {
          webPrintHeader();
          if (!queryDefaultValue(atof(&p[2]), msg, tx_msg)) {
            if (decodedTelegram.error == 258) {
              printToWebClient(MENU_TEXT_ER6 "\r\n");
            } else if (decodedTelegram.error == 261) {
              printlnToDebug(printError(decodedTelegram.error));  // to PC hardware serial I/F
              printToWebClient(MENU_TEXT_ER3 "\r\n");
            }
          } else {
// TODO: replace pvalstr with data from decodedTelegram structure
            build_pvalstr(0);
            if (outBuf[0]>0) {
              printToWebClient(outBuf);
              printToWebClient("<br>");
            }
          }
          webPrintFooter();
          break;
        }
        if (p[1]=='Q' && p[2] !='D') {
          webPrintHeader();
          if (bus_type > 1) {
            printToWebClient(MENU_TEXT_NOQ "\r\n\r\n");
          } else {
            if (my_dev_fam == 0) {
              printToWebClient(MENU_TEXT_QNC "<BR>\r\n");
            } else {
              printToWebClient(MENU_TEXT_QIN "<BR><BR>\r\n");
              printToWebClient("<A HREF='/");
              printPassKey();
              printToWebClient("QD'>" MENU_TEXT_QDL "</A><BR>\r\n");
            }
          }
          webPrintFooter();
          break;
        }
        if (p[1]=='Q' && p[2]=='D') {
//          if (!(httpflags & HTTP_FRAG)) webPrintHeader();
          if (bus_type > 1) {
            printHTTPheader(HTTP_OK, MIME_TYPE_TEXT_PLAIN, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_NO_DOWNLOAD, HTTP_AUTO_CACHE_AGE);
            printToWebClient(MENU_TEXT_NOQ "\r\n\r\n");
            break;
          }

          printHTTPheader(HTTP_OK, MIME_TYPE_FORCE_DOWNLOAD, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_IS_DOWNLOAD, HTTP_AUTO_CACHE_AGE);
          printToWebClient("\r\n");
          flushToWebClient();

          if (bus_type > 1) {
            printToWebClient(MENU_TEXT_NOQ "\r\n\r\n");
            break;
          }

          uint8_t myAddr = bus->getBusAddr();
          uint8_t destAddr = bus->getBusDest();
          printToWebClient(MENU_TEXT_QIN "\r\n\r\n");
          printToWebClient(MENU_TEXT_VER ": ");
          printToWebClient(BSB_VERSION);
          printToWebClient("\r\n");
          printToWebClient(MENU_TEXT_QSC "...\r\n");
          flushToWebClient();

          for (uint x=0; x<sizeof(dev_lookup)/sizeof(dev_lookup[0]) && client.connected(); x++) {
            if (dev_lookup[x].dev_id==0xFF) {
              continue;
            }
            bus->setBusType(bus->getBusType(), myAddr, dev_lookup[x].dev_id);
            printFmtToWebClient(MENU_TEXT_QRT " %hu...", dev_lookup[x].dev_id);
            flushToWebClient();

            uint32_t c=0;
            float l;
            int orig_dev_fam = my_dev_fam;
            int orig_dev_var = my_dev_var;
            query_program_and_print_result(6224, "\r\n", NULL);
            query_program_and_print_result(6225, "\r\n", NULL);
            int temp_dev_fam = strtod(decodedTelegram.value,NULL);
            query_program_and_print_result(6226, "\r\n", NULL);
            int temp_dev_var = strtod(decodedTelegram.value,NULL);
            my_dev_fam = temp_dev_fam;
            my_dev_var = temp_dev_var;
            if (temp_dev_fam == 97) temp_dev_fam = 64;
/*
            for (uint16_t q = 0; q < sizeof(proglist4q)/sizeof(proglist4q[0]); q++) {
              query_program_and_print_result(proglist4q[q], "\r\n", NULL);
              forcedflushToWebClient();
            }
            query_program_and_print_result(10003, "\r\n", " (10003): ");
            query_program_and_print_result(10004, "\r\n", " (10004): ");
            printToWebClient("\r\n");
            flushToWebClient();

            for (uint16_t i=0; i<sizeof(params4q)/sizeof(params4q[0]); i++) {
              printFmtToWebClient("%.1f;", params4q[i]);
            }
            printToWebClient("\r\n");
            for (uint16_t i=0; i<sizeof(params4q)/sizeof(float); i++) {
              query(params4q[i]); printToWebClient(decodedTelegram.value);
              printToWebClient(";");
            }

            printToWebClient("\r\n\r\n");
*/
            my_dev_fam = orig_dev_fam;
            my_dev_var = orig_dev_var;

            if (p[3] == 'F') {
              printToWebClient("\r\n" MENU_TEXT_QST "...\r\n");
              flushToWebClient();
              for (int j=0; cmdtbl[j].line < 15000 && client.connected(); j++) {
                uint32_t cc = cmdtbl[j].cmd;
                if (cc == c) {
                  continue;
                } else {
                  c = cc;
                }
                if (c==CMD_END) break;
                l=cmdtbl[j].line;
                uint8_t dev_fam = cmdtbl[j].dev_fam;
                uint8_t dev_var = cmdtbl[j].dev_var;
#if defined(ESP32)
                esp_task_wdt_reset();
#endif
                if (((dev_fam != temp_dev_fam && dev_fam != DEV_FAM(DEV_ALL)) || (dev_var != temp_dev_var && dev_var != DEV_VAR(DEV_ALL))) && c!=CMD_UNKNOWN) {
                  printFmtToDebug("%02X\r\n", c);
                  if (bus->Send(TYPE_QUR, c, msg, tx_msg) != BUS_OK) {
                    printlnToDebug("bus send failed");  // to PC hardware serial I/F
                  } else {
                    if (msg[4+bus->offset]!=TYPE_ERR) {
                      // Decode the xmit telegram and send it to the PC serial interface
                      printTelegram(tx_msg, -1);
                      LogTelegram(tx_msg);
                      // Decode the rcv telegram and send it to the PC serial interface
                      printTelegram(msg, -1);   // send to hardware serial interface
                      LogTelegram(msg);
                      if (decodedTelegram.msg_type != TYPE_ERR) { //pvalstr[0]<1 - unknown command
                        my_dev_fam = temp_dev_fam;
                        my_dev_var = temp_dev_var;
                        query(l);
                        my_dev_fam = orig_dev_fam;
                        my_dev_var = orig_dev_var;
                        if (decodedTelegram.msg_type == TYPE_ERR) { //pvalstr[0]<1 - unknown command
                          printFmtToWebClient("\r\n%g - ", l);
                          printToWebClient(decodedTelegram.catdescaddr);
                          printToWebClient(" - ");
                          printToWebClient_prognrdescaddr();
                          printFmtToWebClient("\r\n0x%08X\r\n", c);
                          int outBufLen = strlen(outBuf);
                          bin2hex(outBuf + outBufLen, tx_msg, tx_msg[bus->getLen_idx()]+bus->getBusType(), ' ');
                          printToWebClient(outBuf + outBufLen);
                          printToWebClient("\r\n");
                          bin2hex(outBuf + outBufLen, msg, msg[bus->getLen_idx()]+bus->getBusType(), ' ');
                          printToWebClient(outBuf + outBufLen);
                          outBuf[outBufLen] = 0;
                          printToWebClient("\r\n");
                        }
                        forcedflushToWebClient(); //browser will build page immediately
                      }
                    }
                  }
                }
              }
              printToWebClient("\r\n" MENU_TEXT_QTE ".\r\n");
              flushToWebClient();
            }
            printToWebClient("\r\nComplete dump:\r\n");
            c = 0;
            int outBufLen = strlen(outBuf);
            unsigned long timeout = millis() + 6000;
            while (bus->Send(TYPE_QUR, 0x053D0001, msg, tx_msg) != BUS_OK && (millis() < timeout)) {
              printTelegram(tx_msg, -1);
              printTelegram(msg, -1);
              delay(500);
            }
            printTelegram(tx_msg, -1);
            printTelegram(msg, -1);
            bin2hex(outBuf + outBufLen, msg, msg[bus->getLen_idx()]+bus->getBusType(), ' ');
            printToWebClient(outBuf + outBufLen);
            printToWebClient("\r\n");
            timeout = millis() + 6000;
            while (bus->Send(TYPE_QUR, 0x053D0064, msg, tx_msg) != BUS_OK && (millis() < timeout)) {
              printTelegram(tx_msg, -1);
              printTelegram(msg, -1);
              delay(500);
            }
            printTelegram(tx_msg, -1);
            printTelegram(msg, -1);
            bin2hex(outBuf + outBufLen, msg, msg[bus->getLen_idx()]+bus->getBusType(), ' ');
            printToWebClient(outBuf + outBufLen);
            printToWebClient("\r\n");
            flushToWebClient();
            timeout = millis() + 6000;
            while (bus->Send(TYPE_IQ1, c, msg, tx_msg) != BUS_OK && (millis() < timeout)) {
              printTelegram(tx_msg, -1);
              printTelegram(msg, -1);
              printlnToDebug("Didn't receive matching telegram, resending...");
              delay(500);
            }
            printTelegram(tx_msg, -1);
            printTelegram(msg, -1);
            int IA1_max = (msg[7+bus->offset] << 8) + msg[8+bus->offset];
            if (msg[4+bus->offset] == 0x13 && IA1_max > 0) {
              timeout = millis() + 6000;
              while (bus->Send(TYPE_IQ2, c, msg, tx_msg) != BUS_OK && (millis() < timeout)) {
                printToWebClient("Didn't receive matching telegram, resending...\r\n");
                delay(500);
              }
              int IA2_max = (msg[5+bus->offset] << 8) + msg[6+bus->offset];
              int outBufLen = strlen(outBuf);

              for (int IA1_counter = 1; IA1_counter <= IA1_max && client.connected(); IA1_counter++) {
#if defined(ESP32)
                esp_task_wdt_reset();
#endif
                timeout = millis() + 6000;
                while (bus->Send(TYPE_IQ1, IA1_counter, msg, tx_msg) != BUS_OK && (millis() < timeout)) {
                  printToWebClient("Didn't receive matching telegram, resending...\r\n");
                  delay(500);
                }
                bin2hex(outBuf + outBufLen, msg, msg[bus->getLen_idx()]+bus->getBusType(), ' ');
                printToWebClient(outBuf + outBufLen);
                printToWebClient("\r\n");
                flushToWebClient();
              }
              for (int IA2_counter = 1; IA2_counter <= IA2_max && client.connected(); IA2_counter++) {
#if defined(ESP32)
                esp_task_wdt_reset();
#endif
                timeout = millis() + 6000;
                while (bus->Send(TYPE_IQ2, IA2_counter, msg, tx_msg) != BUS_OK && (millis() < timeout)) {
                  printToWebClient("Didn't receive matching telegram, resending...\r\n");
                  delay(500);
                }
                bin2hex(outBuf + outBufLen, msg, msg[bus->getLen_idx()]+bus->getBusType(), ' ');
                printToWebClient(outBuf + outBufLen);
                printToWebClient("\r\n");
                flushToWebClient();
              }
              outBuf[outBufLen] = 0;
            } else {
              printlnToDebug("No response to dump request:");
              bus->print(tx_msg);
              bus->print(msg);
              printToWebClient("\r\nNot supported by this device. No problem.\r\n");
            }
          }
          bus->setBusType(bus->getBusType(), myAddr, destAddr);   // return to original destination address
          printToWebClient("\r\n" MENU_TEXT_QFE ".\r\n");
//            if (!(httpflags & HTTP_FRAG)) webPrintFooter();
          forcedflushToWebClient();
          break;
        }
        if (p[1]=='Y') {
          webPrintHeader();
          if (debug_mode) {
            uint8_t destAddr = bus->getBusDest();
            uint8_t tempDestAddr = destAddr;
            uint8_t save_my_dev_fam = my_dev_fam;
            uint8_t save_my_dev_var = my_dev_var;
            uint32_t save_my_dev_serial = my_dev_serial;
            uint8_t type = strtol(&p[2],NULL,16);
            uint32_t c = (uint32_t)strtoul(&p[5],NULL,16);
            uint8_t param[MAX_PARAM_LEN] = { 0 };
            uint8_t param_len = 0;
            uint8_t counter = 13;
            if (p[counter] == ',') {
              counter++;
              while (p[counter] && p[counter+1] && p[counter] != '!') {
                param[param_len] = char2int(p[counter])*16 + char2int(p[counter+1]);
                param_len++;
                counter = counter + 2;
              }
            }
            if (p[counter] == '!') {
              tempDestAddr = atoi(&p[counter+1]);
              set_temp_destination(tempDestAddr);
            }
            int8_t return_value = bus->Send(type, c, msg, tx_msg, param, param_len, true);
            if (return_value != BUS_OK) {
              printlnToDebug("bus send failed");  // to PC hardware serial I/F
            } else {
              // Decode the xmit telegram and send it to the PC serial interface
              printTelegram(tx_msg, -1);
              LogTelegram(tx_msg);
            }
            // Decode the rcv telegram and send it to the PC serial interface
            printTelegram(msg, -1);   // send to hardware serial interface
            LogTelegram(msg);
  // TODO: replace pvalstr with data from decodedTelegram structure
            build_pvalstr(1);
            if (outBuf[0]>0) {
              printToWebClient(outBuf);
              printToWebClient("<br>");
            }
            bin2hex(outBuf, tx_msg, tx_msg[bus->getLen_idx()]+bus->getBusType(), ' ');
            printToWebClient(outBuf);
            printToWebClient("\r\n<br>\r\n");
            bin2hex(outBuf, msg, msg[bus->getLen_idx()]+bus->getBusType(), ' ');
            printToWebClient(outBuf);
            outBuf[0] = 0;
            writelnToWebClient();
            if (destAddr != tempDestAddr) {
              return_to_default_destination(destAddr);
              my_dev_fam = save_my_dev_fam;
              my_dev_var = save_my_dev_var;
              my_dev_serial = save_my_dev_serial;
            }
          } else {
            printToWebClient("Activate debug mode in configuration in order to use /Y command!<BR>\r\n");
          }
          webPrintFooter();
          break;
        }
        if (p[1]=='J') {
          uint32_t cmd=0;
          // Parse potential JSON payload
          char json_value_string[52];
          float json_parameter = -1, cat_min = -1, cat_max = -1, cat_param = -1;
          bool json_type = 0;
          bool p_flag = false;
          bool v_flag = false;
          bool t_flag = false;
          bool d_flag = false;
          bool output = false;
          bool been_here = false;
          int16_t destAddr = bus->getBusDest();
          int16_t tempDestAddr = 0;
          int16_t tempDestAddrOnPrevIteration = 0;
          uint8_t save_my_dev_fam = my_dev_fam;
          uint8_t save_my_dev_var = my_dev_var;
          uint32_t save_my_dev_serial = my_dev_serial;
          uint8_t opening_brackets = 0;
          char* json_token = strtok(p, "=,"); // drop everything before "="
          json_token = strtok(NULL, ",");
          {//local variable scope
            int16_t http_code = HTTP_OK;
            long cache_time = HTTP_DO_NOT_CACHE;

            if (json_token!=NULL && (p[2] == 'C' || (p[2] == 'K' && atoi(json_token) != CAT_USERSENSORS))) {
              cache_time = 300; //5 min
              if ((httpflags & HTTP_ETAG))
                http_code = HTTP_NOT_MODIFIED;
            }

            printHTTPheader(http_code, MIME_TYPE_APP_JSON, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_NO_DOWNLOAD, cache_time);
            if (cache_time != HTTP_DO_NOT_CACHE) {
              printToWebClient("ETag: \"");
              printToWebClient(BSB_VERSION);
              printToWebClient("\"\r\n");
            }
            printToWebClient("\r\n");
            if (http_code == HTTP_NOT_MODIFIED) {
              forcedflushToWebClient();
              break;
            }
          }
          printToWebClient("{\r\n");
          if (strchr("BCIKLQRSVW", p[2]) == NULL) {  // ignoring unknown JSON commands
            printToWebClient("}");
            forcedflushToWebClient();
            break;
          }

// JSON URL-commands that do not require a POST body

          if (p[2] == 'V'){ // JSON API version
            printFmtToWebClient("\"api_version\": \"" JSON_MAJOR "." JSON_MINOR "\"\r\n}");
            forcedflushToWebClient();
            break;
          }

          if (p[2] == 'I'){ // dump configuration in JSON
            bool not_first = false;
            int i;
            printToWebClient("  \"name\": \"BSB-LAN\",\r\n  \"version\": \"");
            printToWebClient(BSB_VERSION);
            printToWebClient("\",\r\n  \"hardware\": \"");
            printDeviceArchToWebClient();
            printFmtToWebClient("\",\r\n  \"freeram\": %d,\r\n  \"uptime\": %lu,\r\n  \"MAC\": \"%02hX:%02hX:%02hX:%02hX:%02hX:%02hX\",\r\n  \"freespace\": ", freeRam(), millis(), mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
            if (LoggingMode & CF_LOGMODE_SD_CARD) {
#if !defined(ESP32)
              uint32_t freespace = SDCard.vol()->freeClusterCount();
              freespace = (uint32_t)(freespace*SDCard.vol()->sectorsPerCluster()/2048);
              printFmtToWebClient("%d", freespace);
#else
              uint64_t freespace = totalBytes()-usedBytes();
              printFmtToWebClient("%llu", freespace);
#endif
            } else {
              printFmtToWebClient("0");
            }

// Bus info
            json_parameter = 0; //reuse json_parameter  for lesser memory usage
            i = bus->getBusType();
            if (i != BUS_PPS) {
              if ((default_flag & FL_RONLY) != FL_RONLY || ((default_flag & FL_SW_CTL_RONLY) == FL_SW_CTL_RONLY && programWriteMode)) json_parameter = 1;
            } else {
              if (pps_write == 1)  json_parameter = 1;
            }

            switch (i) {
              case 0: strcpy(json_value_string, "BSB"); break; //reuse json_value_string for lesser memory usage
              case 1: strcpy(json_value_string, "LPB"); break;
              case 2: strcpy(json_value_string, "PPS"); break;
            }
            printFmtToWebClient(",\r\n  \"bus\": \"%s\",\r\n  \"buswritable\": %d,\r\n", json_value_string, json_parameter);
            printFmtToWebClient("  \"busaddr\": %d,\r\n  \"busdest\": %d,\r\n", bus->getBusAddr(), bus->getBusDest());
            printToWebClient("  \"busdevices\": [\r\n");
            not_first = false;
            int numDevices = sizeof(dev_lookup) / sizeof(dev_lookup[0]);
            for (i=0;i<numDevices;i++) {
              if (dev_lookup[i].dev_id < 0xFF) {
                if (not_first) {
                  printToWebClient(",\r\n");
                } else {
                  not_first = true;
                }
                printFmtToWebClient("    { \"dev_id\": %d,  \"dev_fam\": %d, \"dev_var\": %d, \"dev_serial\": %d, \"dev_name\": \"%s\" }", dev_lookup[i].dev_id, dev_lookup[i].dev_fam, dev_lookup[i].dev_var, dev_lookup[i].dev_serial, dev_lookup[i].name);
              }
            }
            printToWebClient("\r\n  ],\r\n");

//enabled options
            printFmtToWebClient("  \"monitor\": %d,\r\n  \"verbose\": %d", monitor, verbose);

            printFmtToWebClient(",\r\n  \"onewirebus\": %d", One_Wire_Pin);
            printFmtToWebClient(",\r\n  \"onewiresensors\": %d", numSensors);
            printToWebClient(",\r\n  \"dhtbus\": [\r\n");
            not_first = false;
            int numDHTSensors = sizeof(DHT_Pins) / sizeof(DHT_Pins[0]);
            for (i=0;i<numDHTSensors;i++) {
              if (DHT_Pins[i] >= -1) {
                if (not_first) {
                  printToWebClient(",\r\n");
                } else {
                  not_first = true;
                }
                printFmtToWebClient("    { \"pin\": %d }", DHT_Pins[i]);
              }
            }
            printToWebClient("\r\n  ]");

//averages
            printToWebClient(",\r\n  \"averages\": [\r\n");
            not_first = false;
            for (i = 0; i < numAverages; i++) {
              if (avg_parameters[i].number > 0) {
                if (not_first) {
                  printToWebClient(",\r\n");
                } else {
                  not_first = true;
                }
                printParameterInJSON_ToWebClient(avg_parameters[i]);
              }
            }
            printToWebClient("\r\n  ]");

// logged parameters
            printFmtToWebClient(",\r\n  \"loggingmode\": %d,\r\n  \"loginterval\": %d,\r\n  \"logged\": [\r\n", LoggingMode, log_interval);
            not_first = false;
            for (i=0; i<numLogValues; i++) {
              if (log_parameters[i].number > 0)  {
                if (not_first) {
                  printToWebClient(",\r\n");
                } else {
                  not_first = true;
                }
                printParameterInJSON_ToWebClient(log_parameters[i]);
              }
            }
            printToWebClient("\r\n  ]");
            printToWebClient("\r\n}\r\n");
            forcedflushToWebClient();
            break;
          }
          if (p[2] == 'L') {
            generateJSONwithConfig();
            printToWebClient("\r\n}\r\n");
            forcedflushToWebClient();
            break;
          }
          if (p[2] == 'B'){ // backup settings to file
            uint8_t save_my_dev_fam = my_dev_fam;
            uint8_t save_my_dev_var = my_dev_var;
            uint32_t save_my_dev_serial = my_dev_serial;
            int16_t destAddr = bus->getBusDest();
            int16_t tempDestAddr = destAddr;
            if (p[3]=='!') {
              set_temp_destination(atoi(&p[4]));
              tempDestAddr = bus->getBusDest();
            }

            bool notfirst = false;
            for (uint cat = 1; cat < CAT_UNKNOWN; cat++) { //Ignore date/time category

              printKat(cat,1);
              if ((bus->getBusType() != BUS_PPS && decodedTelegram.error != 258 && decodedTelegram.error != 263) || (bus->getBusType() == BUS_PPS && (cat == CAT_PPS || cat == CAT_USERSENSORS))) {

                cat_min = ENUM_CAT_NR[cat * 2];
                cat_max = ENUM_CAT_NR[cat * 2 + 1];
/*
                if (cat*2+2 < sizeof(ENUM_CAT_NR)/sizeof(*ENUM_CAT_NR)) { // only perform category boundary check if there is a higher category present
                  if (cat_max > ENUM_CAT_NR[cat*2+2]) {
                    cat_max = ENUM_CAT_NR[cat*2+2]-1;
                  }
                }
*/
                float j = cat_min;
//WARNING: simple increment of j was changed because some prognr have decimal part.
                do{
                  int i_line = findLine(j);
                  cmd = cmdtbl[i_line].cmd;
                  if (i_line < 0 || (cmd == CMD_UNKNOWN && json_parameter < (float)BSP_INTERNAL)) {//CMD_UNKNOWN except virtual programs
                    goto next_parameter;
                  }
                  loadPrognrElementsFromTable(j, i_line);
                  if (decodedTelegram.readwrite == FL_WRITEABLE) {//Do not save "read only" or "write only" parameters
                    query(j);
                    if (decodedTelegram.error == 0) {//Do not save parameters with errors
                      if (notfirst) {printToWebClient(",\r\n");} else {notfirst = true;}
                      printFmtToWebClient("  \"%g - %s - %s\":{\"parameter\":\"%g\", \"value\":\"%s\", \"type\":\"%d\", \"destination\":%d}", j, decodedTelegram.catdescaddr, decodedTelegram.prognrdescaddr, j, decodedTelegram.value, 1, tempDestAddr);
                    }
                  }
next_parameter:
                  j = get_next_prognr(j);
                }while(j >= cat_min && j <= cat_max);
              }
            }

            if (tempDestAddr != destAddr) {
              return_to_default_destination(destAddr);
              my_dev_fam = save_my_dev_fam;
              my_dev_var = save_my_dev_var;
              my_dev_serial = save_my_dev_serial;
            }

            printToWebClient("\r\n}\r\n");
            forcedflushToWebClient();
            break;
          }

// JSON commands that parse the POST body
          char c = ' ';
          char old_c = ' ';

          while (client.available()) {  // drop everything until the first opening bracket
            c = client.read();
            if (c == '{' || c == '[') {
              opening_brackets++;
              break;
            }
          }
          tempDestAddr = destAddr;
          tempDestAddrOnPrevIteration = destAddr;
          while ((client.available() && opening_brackets > 0) || json_token!=NULL) {
            json_value_string[0] = 0;
            if (client.available()) {
              bool opening_quotation = false;
              tempDestAddr = destAddr;
              while (client.available()) {
                old_c = c;
                c = client.read();
                if (c == '{' || c == '[') {
                  opening_brackets++;
                  if (opening_brackets > 2) {//JSON too complex. Broken JSON?
                    opening_brackets = 0;
                    break;
                  }
                }
                if (c == '}' || c == ']') { output = true; opening_brackets--;}
                if (c == '\"') {opening_quotation = opening_quotation?false:true;} //XOR (switch from false to true and vice versa)
                if (opening_quotation && old_c == '\"') {       // JSON key needs to be directly preceded by a quotation mark (such as "Parameter", not " Parameter")
                  if (c == 'P' || c == 'p') { p_flag = true; }  //Parameter
                  if (c == 'V' || c == 'v') { v_flag = true; }  //Value
                  if (c == 'T' || c == 't') { t_flag = true; }  //Type
                  if (c == 'D' || c == 'd') { d_flag = true; }  //Destination
                  if ( p_flag || v_flag || t_flag || d_flag) {
                    uint8_t stage_f = 0; //field name
                    bool stage_v = 0; //field value
                    uint8_t j_char_idx = 0;
                    char json_temp[sizeof(json_value_string)];
                    while (client.available()){ //rewind to \":
                      c = client.read();
                      if (c == '\"') stage_f++;
                      if (stage_f == 1 && c == ':') stage_f+=16;
                      if (stage_f > 1) break; //quotation marks or/and colons found
                    }
                    if (stage_f != 17) { //Unexpected end of JSON or broken JSON: multiple quotation marks or colons or wrong order in field name
                      while (client.available()){client.read();} //drop broken JSON
                      break;
                    } else {
                      opening_quotation = false;
                    }
                    char *jptr = NULL;
                    size_t jsize = 0;
                    if (v_flag) {
                      if (p[2] == 'W') {
                        jptr = outBuf;
                        jsize = sizeof(outBuf);
                      } else {
                        jptr = json_value_string;
                        jsize = sizeof(json_value_string);
                      }
                    } else {
                      jptr = json_temp;
                      jsize = sizeof(json_temp);
                    }
                    while (client.available() && j_char_idx < jsize - 1) {
                      c = client.read();
                      if (!stage_v && (c == ' ' || c == ',' || c == '}' || c == ']' || c == '\n' || c == '\r')) { //if it not a string value then we try to find end markers and drop spaces
                        if (c == ' ') continue;
                        if (c == '}' || c == ']') { output = true; opening_brackets--;}
                        break;
                      }
                      if (c == '\"') { //It is string value?
                        if (!stage_v) { //start read from next char after quotation mark if it found
                          stage_v = true;
                          j_char_idx = 0;
                          continue;
                        } else { //read until quotation mark
                          break;
                        }
                      }
                      jptr[j_char_idx] = c;
                      j_char_idx++;
                    }
                    jptr[j_char_idx] = '\0';
                    if (p_flag == true) {
                      json_parameter = ((float)roundf(atof(jptr) * 10)) / 10;
                      p_flag = false;
                    }
                    if (v_flag == true) {
//                      strcpy(json_value_string, jptr);
                      v_flag = false;
                    }
                    if (t_flag == true) {
                      json_type = atoi(jptr);
                      t_flag = false;
                    }
                    if (d_flag == true) {
                      tempDestAddr = atoi(jptr);
                      d_flag = false;
                    }
                  }
                }
                if (output) break;
              }
            } else {
              if (p[2] == 'S' || p[2] == 'W') {
                json_token = NULL; //  /JS command can't handle program id from URL. It allow JSON only.
              } else {
                parameter param = parsingStringToParameter(json_token);
                json_parameter = param.number;
                if(param.dest_addr > -1) tempDestAddr = param.dest_addr;
              }
            }
            if (tempDestAddr != tempDestAddrOnPrevIteration) {
              set_temp_destination(tempDestAddr);
            }
            if (output || json_token != NULL) {
              if (p[2] != 'K' && p[2] != 'W') {
                int i_line=findLine(json_parameter);
                cmd = cmdtbl[i_line].cmd;
                if ((p[2] == 'Q' || p[2] == 'C') && (i_line<0 || (cmd == CMD_UNKNOWN && json_parameter < (float)BSP_INTERNAL))) { //CMD_UNKNOWN except virtual programs
                  json_token = strtok(NULL,",");
                  continue;
                }
              }

              output = false;
              if (json_parameter == -1) continue;

              if (p[2]=='K' && !isdigit(p[4])) {
                bool notfirst = false;
                for (uint cat=0;cat<CAT_UNKNOWN;cat++) {
                  uint32_t cat_dev_fam_var = printKat(cat,1);
                  uint16_t cat_dev_fam = cat_dev_fam_var >> 8;
                  uint16_t cat_dev_var = cat_dev_fam_var & 0xFF;
                  writelnToDebug();
                  if ((bus->getBusType() != BUS_PPS && decodedTelegram.error != 258) || (bus->getBusType() == BUS_PPS && (cat == CAT_PPS || cat == CAT_USERSENSORS))) {
                    if (notfirst) {printToWebClient(",\r\n");} else {notfirst = true;}
                    printFmtToWebClient("\"%d\": { \"name\": \"", cat);
                    cat_min = ENUM_CAT_NR[cat*2];
                    cat_max = ENUM_CAT_NR[cat*2+1];
                    uint8_t cat_dev_id = 0;
                    char* cat_dev_name = NULL;
                    for (uint x=0; x < sizeof(dev_lookup)/sizeof(dev_lookup[0]); x++) {
                      if (dev_lookup[x].dev_fam == cat_dev_fam && dev_lookup[x].dev_var == cat_dev_var) {
                        cat_dev_id = dev_lookup[x].dev_id;
                        cat_dev_name = dev_lookup[x].name;
                        break;
                      } 
                    }
/*
                    if (cat*2+2 < sizeof(ENUM_CAT_NR)/sizeof(*ENUM_CAT_NR)) { // only perform category boundary check if there is a higher category present
                      if (cat_max > ENUM_CAT_NR[cat*2+2]) {
                        cat_max = ENUM_CAT_NR[cat*2+2]-1;
                      }
                    }
*/
                    printToWebClient(decodedTelegram.enumdescaddr); //copy Category name to buffer
                    printFmtToWebClient("\", \"min\": %g, \"max\": %g, \"dev_fam\": %d, \"dev_var\": %d, \"dev_id\": %d, \"dev_name\": \"%s\" }", cat_min, cat_max, cat_dev_fam, cat_dev_var, cat_dev_id, cat_dev_name);
                  }
                }
                json_token = NULL;
              }

              if (p[2]=='K' && isdigit(p[4])) {
                if (cat_min < 0) {
                  uint search_cat = atoi(&p[4]) * 2;
// Check the category number to be within allowed range
                  if(search_cat > sizeof(ENUM_CAT_NR)/sizeof(ENUM_CAT_NR[0])) {
                    search_cat = 0; // if we got an invalid category, just use 0
                  }
                  cat_min = ENUM_CAT_NR[search_cat];
                  cat_max = ENUM_CAT_NR[search_cat+1];
/*
                  if (search_cat+2 < sizeof(ENUM_CAT_NR)/sizeof(*ENUM_CAT_NR)) { // only perform category boundary check if there is a higher category present
                    if (cat_max > ENUM_CAT_NR[search_cat+2]) {
                      cat_max = ENUM_CAT_NR[search_cat+2]-1;
                    }
                  }
*/
                  cat_param = cat_min;
                } else {
//WARNING: simple increment of cat_param was changed because some prognr have decimal part.
                  cat_param = get_next_prognr(cat_param);
                }
                if (cat_param <= cat_max) {
                  json_parameter = cat_param; // we still have work to do
                }
                if (cat_param >= cat_max) {
                  json_token = NULL;        // but this is the last round
                }
              }

              if (p[2]=='Q' || p[2]=='C' || (p[2]=='K' && isdigit(p[4]))) {
                int i_line=findLine(json_parameter);
                cmd = cmdtbl[i_line].cmd;
                if (i_line<0 || (cmd == CMD_UNKNOWN && json_parameter < (float)BSP_INTERNAL)) {//CMD_UNKNOWN except virtual programs
                  continue;
                }

                if (!been_here) been_here = true; else printToWebClient(",\r\n");
                if (p[2]=='Q') {
                  query(json_parameter);
                } else {
                  loadPrognrElementsFromTable(json_parameter, i_line);
                  decodedTelegram.prognr = json_parameter;
                }
                printFmtToWebClient("  \"%g\": {\r\n    \"name\": \"", json_parameter);
                printToWebClient_prognrdescaddr();
                printToWebClient("\",\r\n    \"dataType_name\": \"");
                printToWebClient(decodedTelegram.progtypedescaddr);
                printToWebClient("\",\r\n    \"dataType_family\": \"");
                printToWebClient(decodedTelegram.data_type_descaddr);
                printFmtToWebClient("\",\r\n    \"destination\": %d,\r\n", tempDestAddr);

                if (p[2]=='Q') {
                  printFmtToWebClient("    \"error\": %d,\r\n    \"value\": \"%s\",\r\n    \"desc\": \"", decodedTelegram.error, decodedTelegram.value);
                  if (decodedTelegram.data_type == DT_ENUM && decodedTelegram.enumdescaddr)
                    printToWebClient(decodedTelegram.enumdescaddr);
                  printToWebClient("\",\r\n");
                }

                if (p[2] != 'Q') {
                  printToWebClient("    \"possibleValues\": [\r\n");
                    if (decodedTelegram.enumstr_len > 0) {
                      listEnumValues(decodedTelegram.enumstr, decodedTelegram.enumstr_len, "      { \"enumValue\": ", ", \"desc\": \"", NULL, "\" }", ",\r\n", 0, PRINT_VALUE|PRINT_DESCRIPTION|PRINT_VALUE_FIRST);
                    }

                  printFmtToWebClient("\r\n    ],\r\n    \"isswitch\": %d,\r\n", decodedTelegram.isswitch);
                }
                if (decodedTelegram.data_type == DT_VALS) {
                  char pre_buf[10];
                  pre_buf[0] = 0;
                  if (decodedTelegram.precision != 0) {
                    strcpy(pre_buf, "0.");
                    for (uint8_t j = 1; j < decodedTelegram.precision; j ++) {
                      strcat(pre_buf, "0");
                    }
                  }
                  strcat(pre_buf, "1");
                  printFmtToWebClient("    \"precision\": %s,\r\n", pre_buf);
                }
                printFmtToWebClient("    \"dataType\": %d,\r\n    \"readwrite\": %d,\r\n    \"unit\": \"%s\"\r\n  }", decodedTelegram.data_type, decodedTelegram.readwrite, decodedTelegram.unit);
              }

              if (p[2]=='S') {
                if (!been_here) been_here = true; else printToWebClient(",\r\n");
                int status = set(json_parameter, json_value_string, json_type);
                strcpy(decodedTelegram.value, json_value_string);
                if ((LoggingMode & CF_LOGMODE_MQTT) && !(LoggingMode & CF_LOGMODE_MQTT_ONLY_LOG_PARAMS)) {   // If not only log parameters are sent to MQTT broker, we need to send it here due to lack of a query() call.
                  LogToMQTT(json_parameter);
                }
                printFmtToWebClient("  \"%g\": {\r\n    \"status\": %d\r\n  }", json_parameter, status);

                printFmtToDebug("Setting parameter %g to \"%s\" with type %d to destination %d\r\n", json_parameter, json_value_string, json_type, tempDestAddr);
              }

              if (p[2]=='R') {
                if (!been_here) been_here = true; else printToWebClient(",\r\n");
                queryDefaultValue(json_parameter, msg, tx_msg);
                printFmtToWebClient("  \"%g\": {\r\n    \"error\": %d,\r\n    \"value\": \"%s\",\r\n    \"destination\": %d\r\n  }", json_parameter, decodedTelegram.error, decodedTelegram.value, tempDestAddr);

                printFmtToDebug("Default value of parameter %g for destination %d is \"%s\"\r\n", json_parameter, tempDestAddr, decodedTelegram.value);
              }

              if (p[2]=='W') {
                if (!been_here) been_here = true; else printToWebClient(",\r\n");
                int status = takeNewConfigValueFromUI_andWriteToRAM(json_parameter, outBuf);
                printFmtToWebClient("  \"%g\": {\r\n    \"status\": %d\r\n  }", json_parameter, status);

                printFmtToDebug("Setting parameter %g to \"%s\"\r\n", json_parameter, outBuf);
              }

              if (json_token != NULL && ((p[2] != 'K' && !isdigit(p[4])) || p[2] == 'Q' || p[2] == 'C' || p[2] == 'R')) {
                json_token = strtok(NULL,",");
              }
            }
            tempDestAddrOnPrevIteration = tempDestAddr;
            json_parameter = -1;
          }
          if (tempDestAddr != destAddr) {
            return_to_default_destination(destAddr);
            my_dev_fam = save_my_dev_fam;
            my_dev_var = save_my_dev_var;
            my_dev_serial = save_my_dev_serial;
          }
          bool needReboot = false;
          if (p[2]=='W') {
            needReboot = SaveConfigFromRAMtoEEPROM();
            UpdateMaxDeviceList(); //Update list MAX! devices
          }
          printFmtToWebClient("\r\n}\r\n");
          forcedflushToWebClient();
          if (needReboot) {
            resetBoard();
          }
          break;
        }

        if (p[1]=='D') { // access datalog file
  #if defined(ESP32)
          if (esp32_save_energy == true && network_type != WLAN) {
            bus->disableInterface();
            setCpuFrequencyMhz(240);
            bus->enableInterface();
          }
  #endif
          if (p[2]=='0' || ((p[2]=='D' || p[2]=='J') && p[3]=='0')) {  // remove datalog file
            webPrintHeader();
            File dataFile;
            bool filewasrecreated = false;
//recreate journal file for telegram logging
            if (p[2]=='J' || p[2]=='0') {
              SDCard.remove(journalFileName);
              dataFile = SDCard.open(journalFileName, FILE_WRITE);
              if (dataFile) {
                dataFile.close();
                filewasrecreated = true;
                printToDebug(journalFileName);
                printToWebClient(journalFileName);
              }
            }
//recreate datalog file for programs values logging
              if (p[2]=='D' || p[2]=='0') {
                if (p[2]=='0') {
                  printToDebug(", ");
                  printToWebClient(", ");
                }
              SDCard.remove(datalogFileName);
              if (createdatalogFileAndWriteHeader()) {
                filewasrecreated = true;
                printToDebug(datalogFileName);
                printToWebClient(datalogFileName);
              }
            }
            if (filewasrecreated) {
              printToWebClient(MENU_TEXT_DTR "\r\n");
              printToDebug(": file(s) was removed and recreated.");
            } else {
              printToWebClient(MENU_TEXT_DTF "\r\n");
            }
            webPrintFooter();
          } else if (p[2]=='G') {
            webPrintHeader();
            printToWebClient("<A HREF='D'>" MENU_TEXT_DTD "</A><div align=center></div>\r\n");
            printPStr(graph_html, sizeof(graph_html));
            webPrintFooter();
          } else {  //--- dump datalog or journal or datalog index file, or print min/max date in datalog, or clean up datalog
            printHTTPheader(HTTP_OK, MIME_TYPE_TEXT_PLAIN, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_NO_DOWNLOAD, HTTP_AUTO_CACHE_AGE);
            printToWebClient("\r\n");
            flushToWebClient();  // some of the following code uses the same bigBuffer as the ...ToWebClient functions => deliver any remaining content to the client now
            File dataFile;
            if (p[2]=='J') { //journal
              dataFile = SDCard.open(journalFileName);
              // if the file is available, read from it:
              if (dataFile) {
                unsigned long startdump = millis();
                transmitFile(dataFile);
                dataFile.close();
                printFmtToDebug("Duration: %lu\r\n", millis()-startdump);
              } else printToWebClient(MENU_TEXT_DTO "\r\n");
            } else if (p[2]=='A') { //--- datalog min date, for the javascript code in /DG to access
              printFmtToWebClient("%04d-%02d-%02d", firstDatalogDate.elements.year, firstDatalogDate.elements.month, firstDatalogDate.elements.day);
            } else if (p[2]=='B') { //--- datalog max date, for the javascript code in /DG to access
              printFmtToWebClient("%04d-%02d-%02d", previousDatalogDate.elements.year, previousDatalogDate.elements.month, previousDatalogDate.elements.day);
            } else if (p[2]=='I') { //--- datalog index
              File indexFile = SDCard.open(datalogIndexFileName);
              if (indexFile) {
                compactDate_t date;
                unsigned long pos;
                printToWebClient("Date;DatalogPosition\r\n");
                while (indexFile.read((byte*)&date,sizeof(date)) > 0 &&
                       indexFile.read((byte*)&pos ,sizeof(pos )) > 0)
                  printFmtToWebClient("%04d-%02d-%02d;%lu\r\n", date.elements.year, date.elements.month, date.elements.day, pos);
                indexFile.close();
              }//if (indexFile)
            } else if (p[2]=='K') { //--- clean up datalog, keeping only the most recent n days
              int nDays;
              if (sscanf(p+3,"%d",&nDays)==1 && nDays>0) {
                // We should flush all characters to client and use errormsgptr
                // beacuse cleanupDatalog() and printFmtToWebClient() use same buffer;
                flushToWebClient();
                const char *errormsgptr = cleanupDatalog(nDays);
                printFmtToWebClient("\r\n%s\r\n", errormsgptr);
                // cleanup after failed cleanupDatalog(), if necessary:
                SDCard.remove(datalogTemporaryFileName);
                SDCard.remove(datalogIndexTemporaryFileName);
                // set markers, according to current/new index file:
                readFirstAndPreviousDatalogDateFromFile();
              }
            } else { //--- datalog
              dataFile = SDCard.open(datalogFileName);
              // if the file is available, read from it:
              if (dataFile) {
                unsigned long startdump = millis();
                // /D may be followed by a either an a..b date range (yyyy-mm-dd,yyyy-mm-dd) or a number of days to read from the file's end only:
                int ay, am, ad, by, bm, bd, n;
                n = sscanf(p+2, "%d-%d-%d,%d-%d-%d", &ay,&am,&ad, &by,&bm,&bd);
                if (n<1 || ay<1) transmitFile(dataFile);  // no or zero limit?
                else { // limited datalog requested
                  // transfer header (no error message in case of read() error => handled in subsequent reading of the actual data, anyway):
                  client.write((byte*)datalogFileHeader,strlen(datalogFileHeader));
                  File indexFile = SDCard.open(datalogIndexFileName);
                  if (!indexFile) transmitFile(dataFile);  // no index??
                  else {
                    unsigned long datalogTargetPosition;
                    if (n==6) { // date range requested
                      compactDate_t a, b, date, prevDate;
                      a.elements.year = ay;
                      a.elements.month = am;
                      a.elements.day = ad;
                      b.elements.year = by;
                      b.elements.month = bm;
                      b.elements.day = bd;
                      prevDate.combined = 0;
                      unsigned long datalogFromPosition=0, datalogToPosition=0;
                      // read index file backwards (why? => https://github.com/fredlcore/BSB-LAN/issues/539#issuecomment-1464885147):
                      for (unsigned long pos=indexFile.size(); pos>=datalogIndexEntrySize; pos-=datalogIndexEntrySize) {
                        indexFile.seek(pos-datalogIndexEntrySize);
                        if (indexFile.read((byte*)&date,sizeof(date)) <= 0 ||
                            indexFile.read((byte*)&datalogTargetPosition,sizeof(datalogTargetPosition)) <= 0)
                          break; // nothing could be read!
                        if (prevDate.combined && prevDate.combined < date.combined) break; // dates running backwards?
                        if (date.combined >  b.combined) datalogToPosition = datalogTargetPosition;
                        if (date.combined >= a.combined) datalogFromPosition = datalogTargetPosition;
                        else break; // we're already before date a in the index
                        prevDate = date;
                      }
                      if (datalogFromPosition) {
                        dataFile.seek(datalogFromPosition);
                        if (!datalogToPosition) datalogToPosition = dataFile.size();
                        unsigned long nBytesToDo = datalogToPosition - datalogFromPosition;
                        // the following re-uses code fragments from transmitFile():
                        unsigned logbuflen = (OUTBUF_USEFUL_LEN + OUTBUF_LEN > 1024)?1024:(OUTBUF_USEFUL_LEN + OUTBUF_LEN);
                        byte *buf = 0;
#ifdef ESP32 // Arduino seems to have problems with the bigger, malloc'ed buffer
                        buf = (byte*)malloc(4096);  // try to use 4 KB buffer, for improved transfer rates
#endif
                        if (buf) logbuflen=4096; else buf=(byte*)bigBuff;  // fall back to static buffer, if necessary
                        while (nBytesToDo && client.connected()) {
                          int n = dataFile.read(buf, nBytesToDo<logbuflen ?nBytesToDo :logbuflen);
                          if (n < 0) {
                            printToWebClient("Error: Failed to read from SD card - if problem remains after reformatting, card may be incompatible.");
                            forcedflushToWebClient();
                          }
                          if (n <= 0) break;
                          client.write(buf, n);
#ifdef ESP32
                          esp_task_wdt_reset();
#endif
                          nBytesToDo -= n;
                        }//while (nBytesToDo)
                        if (buf != (byte*)bigBuff) free(buf);
                      }//if (datalogFromPosition)
                    }//if (n==6)
                    else { // most recent days requested
                      unsigned long bytesToBackup = ay * datalogIndexEntrySize;
                      unsigned long indexFileSize = indexFile.size();
                      if (indexFileSize >= bytesToBackup) {  // enough index entries available?
                        indexFile.seek(indexFileSize - bytesToBackup + sizeof(compactDate_t));
                        indexFile.read((byte*)&datalogTargetPosition, sizeof(datalogTargetPosition));
                        dataFile.seek(datalogTargetPosition);  // skip older data
                      }
                      transmitFile(dataFile);
                    }//most recent days requested
                    indexFile.close();
                  }//else (!indexFile)
                }//limited datalog
                dataFile.close();
                printFmtToDebug("Duration: %lu\r\n", millis()-startdump);
              } else printToWebClient(MENU_TEXT_DTO "\r\n");
            }//datalog
          }//datalog or journal or min/max datalog date
          flushToWebClient();
  #if defined(ESP32)
          if (esp32_save_energy == true && network_type != WLAN) {
            bus->disableInterface();
            setCpuFrequencyMhz(80);
            bus->enableInterface();
          }
  #endif
          break;
        }

        if (p[1]=='C'){ // dump configuration
          if (!(httpflags & HTTP_FRAG)) webPrintHeader();

          switch (p[2]) {
            case 'E':
              if (p[3]=='=') {
                if (p[4]=='1') { //Use EEPROM
                  UseEEPROM = 0x96;
                } else {   //Use _config.h
                  UseEEPROM = 0x69;
                }
              }
//                printToWebClient(MENU_TEXT_LBO ": ");
              if (UseEEPROM == 0x96) {
                printyesno(1) ;
              } else {
                printyesno(0) ;
              }
              break;
            case 'S': //save config to EEPROM
                for (uint8_t i = 0; i < CF_LAST_OPTION; i++) {
                  writeToEEPROM(i);
                }
//                printToWebClient(MENU_TEXT_LBO ": ");
//                printyesno(UseEEPROM) ;
              break;
            case 'I': {//Parse HTTP form and implement changes
              applyingConfig();
              generateWebConfigPage(false);
              generateConfigPage(); 
              UpdateMaxDeviceList(); //Update list MAX! devices
              if (!(httpflags & HTTP_FRAG)) webPrintFooter();
              flushToWebClient();
              if (SaveConfigFromRAMtoEEPROM() == true) {
                resetBoard();
              }
            }
            break;
              //no break here.
            case 'O': {//Just print current configuration (for debug purposes)
              generateConfigPage();
              generateWebConfigPage(true);
              if (!(httpflags & HTTP_FRAG)) webPrintFooter();
              flushToWebClient();
            }
            break;
            default:
              generateWebConfigPage(false);
              generateConfigPage();
              if (!(httpflags & HTTP_FRAG)) webPrintFooter();
              flushToWebClient();
// EEPROM dump require ~3 sec so let it be last operation.
// Dump when serial debug active or have telnet client
              EEPROM_dump();
              break;
            }
          break;
        }
        if (p[1]=='L') {
          webPrintHeader();
          switch (p[2]) {
            case 'C':
              if (p[3]=='=') {
                if (p[4]=='1') {
                  LoggingMode |= CF_LOGMODE_SD_CARD;
                } else {
                  LoggingMode &= ~CF_LOGMODE_SD_CARD;
                }
//                printToWebClient(MENU_TEXT_LBO ": ");
                printyesno(LoggingMode & CF_LOGMODE_SD_CARD) ;
              }
              break;
            case 'B':
              if (p[3]=='=') {
                if (p[4]=='1') {
                  logTelegram |= LOGTELEGRAM_BROADCAST_ONLY;
                } else {
                  if (logTelegram & LOGTELEGRAM_BROADCAST_ONLY)
                    logTelegram -= LOGTELEGRAM_BROADCAST_ONLY;
                }
                printToWebClient(MENU_TEXT_LBO ": ");
                printyesno(logTelegram & LOGTELEGRAM_BROADCAST_ONLY) ;
              }
              break;
            case 'N':     // log now
              log_now = 1;
              printToWebClient(MENU_TEXT_LIR);
              break;
            case 'U':
              if (p[3]=='=') {
                if (p[4]=='1') {
                  logTelegram |= LOGTELEGRAM_UNKNOWN_ONLY;
                } else {
                  if (logTelegram & LOGTELEGRAM_UNKNOWN_ONLY)
                    logTelegram -= LOGTELEGRAM_UNKNOWN_ONLY; //clear bit
                }
                printToWebClient(MENU_TEXT_BUT ": ");
                printyesno(logTelegram & LOGTELEGRAM_UNKNOWN_ONLY);
              }
              break;
            // note: no use case recognized for temporary UDP logging on/off
            case '=': // logging configuration: L=<interval>,<parameter 1>,<parameter 2>,...,<parameter20>
            {
              char* log_token = strtok(p,"=,");  // drop everything before "="
              log_token = strtok(NULL, "=,");   // first token: interval

              if (log_token != 0) {
                log_interval = atoi(log_token);
//                if (log_interval < 10) {log_interval = 10;}
                lastLogTime = millis();
                lastMQTTTime = millis();
                printFmtToWebClient(MENU_TEXT_LGI ": %d", log_interval);
                printToWebClient(" " MENU_TEXT_SEC "<BR>\r\n");
              }
              log_token = strtok(NULL,"=,");    // subsequent tokens: logging parameters
              int token_counter = 0;
              if (log_token != 0) {
                for (int i = 0; i < numLogValues; i++) {
                  log_parameters[i].number = 0;
                  log_parameters[i].dest_addr = -1;
                }
              printToWebClient(MENU_TEXT_LGN ": ");
              }
              while (log_token!=0) {
                log_parameters[token_counter] = parsingStringToParameter(log_token);

                if (token_counter < numLogValues) {
                  printFmtToWebClient("%g", log_parameters[token_counter].number);
                  if (log_parameters[token_counter].dest_addr > -1) {
                    printFmtToWebClient("!%d", log_parameters[token_counter].dest_addr);
                  }
                  printToWebClient(" \r\n");
                  token_counter++;
                }
                log_token = strtok(NULL,"=,");
              }
            }
            break;
          case 'E': //enable telegrams logging to journal.txt
          case 'D': //disable telegrams logging
            if (p[2]=='E') {
              logTelegram |= LOGTELEGRAM_ON;
            } else {
              if (logTelegram & LOGTELEGRAM_ON) logTelegram -= LOGTELEGRAM_ON; //clear bit
            }
            printToWebClient(MENU_TEXT_LOT ": ");
            printyesno(logTelegram);
            break;
          default:
            printToWebClient(MENU_TEXT_ER1);
            break;
          }
        webPrintFooter();
        break;
        }
        if (p[1]=='P') {
          webPrintHeader();
          uint8_t myAddr = 0;
          uint8_t destAddr = 0;
          char* token = strtok(p,",");  // drop everything before ","
          token = strtok(NULL, ",");   // first token: myAddr
          if (token != 0) {
            int val = atoi(token);
            myAddr = (uint8_t)val;
          }
          token = strtok(NULL, ",");   // second token: destAddr
          if (token != 0) {
            int val = atoi(token);
            destAddr = (uint8_t)val;
          }

          printToWebClient(MENU_TEXT_BUS ": ");
          uint8_t savedbus = bus_type;
          bus_type = p[2] - '0';
          switch (bus_type) {
            case 0:
              own_address = myAddr;
              dest_address = destAddr;
              printToWebClient("BSB");
              break;
            case 1:
              own_address = myAddr;
              dest_address = destAddr;
              printToWebClient("LPB");
              break;
            case 2:
              pps_write = myAddr;
              printToWebClient("PPS");
              break;
            default:
              bus_type = savedbus;
              break;
          }
          setBusType(); //Apply changes
          printToWebClient("\r\n");
          if (bus->getBusType() != BUS_PPS) {
            printFmtToWebClient(" (%d, %d)", myAddr, destAddr);
          } else {
            if (pps_write == 1) {
              printToWebClient(" " MENU_TEXT_BRW);
            } else {
              printToWebClient(" " MENU_TEXT_BRO);
            }
            printToWebClient("\r\n");
          }

          SetDevId();
          webPrintFooter();
          break;
        }
        if (p[1]=='N'){           // Reset Arduino...
          webPrintHeader();
          if (p[2]=='E') {
            printToWebClient("Clearing EEPROM (affects MAX! devices and PPS-Bus settings)...<BR>\r\n");
            forcedflushToWebClient();
          }

          if (LoggingMode & CF_LOGMODE_SD_CARD) {
            // what doing this fragment? Just opened and closed file? We really need it?
            // FH: Before, it seemed to be necessary to have the file properly closed. And since I thought you can only properly close it when it's opened before, I was opening it.
            File dataFile = SDCard.open(datalogFileName, FILE_APPEND);
            if (dataFile) {
              dataFile.close();
            }
          }

          if (p[2]=='E' && EEPROM_ready) { //...and clear EEPROM
            clearEEPROM();
          }
          printToWebClient("Restarting micro-controller...\r\n");
          webPrintFooter();
          resetBoard();
          break;
        }
        // print queries
        webPrintHeader();
        char* range;
        range = strtok(p,"/");
        while (range!=0) {
          if (range[0]=='A') { // handle average command
            if (range[1]=='C' && range[2]=='=') { // 24h average calculation on/off
              if (range[3]=='1') {                // Enable 24h average calculation temporarily
                LoggingMode |= CF_LOGMODE_24AVG;
              } else {                            // Disable 24h average calculation temporarily
                LoggingMode &= ~CF_LOGMODE_24AVG;
              }
            }
            if (LoggingMode & CF_LOGMODE_24AVG) {
              if (range[1]=='=') {
                char* avg_token = strtok(range,"=,");  // drop everything before "="
                avg_token = strtok(NULL,"=,");    // subsequent tokens: average parameters
                int token_counter = 0;
                if (avg_token != 0) {
                  resetAverageCalculation();
                  for (int i = 0; i < numAverages; i++) {
                    avg_parameters[i].number = 0;
                    avg_parameters[i].dest_addr = -1;
                  }
                  printToWebClient(MENU_TEXT_24N ": ");
                }
                while (avg_token!=0) {
                  avg_parameters[token_counter] = parsingStringToParameter(avg_token);

                  if (token_counter < numAverages*2) {
                    printFmtToWebClient("%g", avg_parameters[token_counter].number);
                    if (avg_parameters[token_counter].dest_addr > -1) {
                      printFmtToWebClient("!%d", avg_parameters[token_counter].dest_addr);
                    }
                    printToWebClient(" \r\n");
                    token_counter++;
                  }
                  avg_token = strtok(NULL,"=,");
                }
                avgCounter = 1;
              }
            }
          } else if (range[0]=='G') { // handle gpio command
            uint8_t val;
            uint8_t pin;
//            bool error = false;
            p=range+1;
            if (!isdigit(*p)) {   // now we check for digits
              printToWebClient(MENU_TEXT_ER1 "\r\n");
              break;
            }
            pin=(uint8_t)atoi(p);       // convert until non-digit char is found

            char* dir_token = strchr(range,',');
            if (dir_token!=NULL) {
              dir_token++;
            }
            p=strchr(p,'=');    // search for '=' sign
            if (p==NULL) {        // no match -> query value
              pinMode(pin, INPUT);
              val=digitalRead(pin);
            } else { // set value
              p++;
              uint16_t i = 0;
              while (p[i]) {
                p[i] |= 0x20; //to lower case
                i++;
              }
              if (!strncmp(p, "on", 2) || !strncmp(p, "high", 2) || *p=='1') {
                val=HIGH;
              } else {
                val=LOW;
              }
              pinMode(pin, OUTPUT); // TODO: does this case a problem if already set as output?
              digitalWrite(pin, val);
            }
            printFmtToWebClient("GPIO%hu: %d", pin, val!=LOW?1:0);
          } else if (range[0]=='B') {
            if (range[1]=='0') { // reset furnace duration
              printToWebClient(STR20006);
              printToWebClient(".<br>\r\n");
              resetDurations();
            }
          } else {
            char* line_start;
            char* line_end;
            float start=-1;
            float end=-1;
            uint8_t save_my_dev_fam = my_dev_fam;
            uint8_t save_my_dev_var = my_dev_var;
            uint32_t save_my_dev_serial = my_dev_serial;
            uint8_t destAddr = bus->getBusDest();
            if (range[0]=='K') {
              //Here will be parsing category number not parameter
              parameter param = parsingStringToParameter(range+1);
              if (param.dest_addr > -1) {
                set_temp_destination(param.dest_addr);
              }
              printKat(param.number,1);
              writelnToDebug();
              uint cat = param.number * 2; // * 2 - two columns in ENUM_CAT_NR table
              if (cat >= sizeof(ENUM_CAT_NR)/sizeof(*ENUM_CAT_NR)) {  // set category to highest category if selected category is out of range
                cat = (sizeof(ENUM_CAT_NR)/sizeof(*ENUM_CAT_NR))-2;
              }
              start = ENUM_CAT_NR[cat];
              end = ENUM_CAT_NR[cat+1];
/*
              if (cat+2 < sizeof(ENUM_CAT_NR)/sizeof(*ENUM_CAT_NR)) { // only perform category boundary check if there is a higher category present
                if (end > ENUM_CAT_NR[cat+2]) {
                  end = ENUM_CAT_NR[cat+2]-1;
                }
              }
*/
            } else {
              // split range
              line_start=range;
              line_end=strchr(range,'-');
              if (line_end==NULL) {
                line_end=line_start;
              } else {
                *line_end='\0';
                line_end++;
              }
              parameter param = parsingStringToParameter(line_end);
              end = param.number;
              if (param.dest_addr > -1) {
                set_temp_destination(param.dest_addr);
/*
                query(6225);
                my_dev_fam = strtod(decodedTelegram.value,NULL);
                query(6226);
                my_dev_var = strtod(decodedTelegram.value,NULL);
*/
              }

              start=atof(line_start);
            }
            if (decodedTelegram.error == 263) {
              printlnToWebClient(MENU_TEXT_CNV);
            } else {
              query(start,end,0);
            }
            if (bus->getBusDest() != destAddr) {
              return_to_default_destination(destAddr);
              my_dev_fam = save_my_dev_fam;
              my_dev_var = save_my_dev_var;
              my_dev_serial = save_my_dev_serial;
            }
          }
          range = strtok(NULL,"/");
        } // endwhile
        webPrintFooter();
        break;
      } // endif, client available

      delay(1);
      loopCount++;
      if (loopCount > 1000) {
        client.stop();
        printlnToDebug("\r\nBrowser keeps connection open without sending data, so we're closing now...");
      }

    }

/*
#ifdef ESP32
    esp_task_wdt_deinit();
#endif
*/
    client_flag = false;
    if (client.available()) {
      printToDebug("\r\nClient buffer gets discarded:\r\n");
      while (client.available()) Serial.print((char)client.read());
    }

    // give the web browser time to receive the data
    delay(1);
    // close the connection:
//    client.flush();     // check if substitute for flush() is available since it is now deprecated. clear() only clears the RX buffer, but we want to flush the TX buffer.
    client.stop();
  } // endif, client

  if(!localAP){
    if (mqtt_broker_addr[0] && (LoggingMode & CF_LOGMODE_MQTT)) { //Address was set and MQTT was enabled

      mqtt_connect();        //Luposoft, connect to mqtt
      MQTTPubSubClient->loop();    //Luposoft: listen to incoming messages

      if ((((millis() - lastMQTTTime >= (log_interval * 1000)) && log_interval > 0) || log_now > 0) && numLogValues > 0) {
        lastMQTTTime = millis();
        uint8_t destAddr = bus->getBusDest();
        uint8_t d_addr = destAddr;
        uint8_t save_my_dev_fam = my_dev_fam;
        uint8_t save_my_dev_var = my_dev_var;
        uint32_t save_my_dev_serial = my_dev_serial;
        for (int i=0; i < numLogValues; i++) {
          if (log_parameters[i].number > 0) {
            if (log_parameters[i].dest_addr > -1){
              if(log_parameters[i].dest_addr != d_addr) {
                d_addr = log_parameters[i].dest_addr;
                set_temp_destination(log_parameters[i].dest_addr);
              }
            } else {
              if (destAddr != d_addr) {
                d_addr = destAddr;
                return_to_default_destination(destAddr);
                my_dev_fam = save_my_dev_fam;
                my_dev_var = save_my_dev_var;
                my_dev_serial = save_my_dev_serial;
              }
            }
            parameter param = log_parameters[i];
            query(param.number);
            if ((LoggingMode & CF_LOGMODE_MQTT) && (LoggingMode & CF_LOGMODE_MQTT_ONLY_LOG_PARAMS)) {   // If only log parameters are sent to MQTT broker, we need an exemption here. Otherwise, query() will publish the parameter anyway.
              mqtt_sendtoBroker(log_parameters[i]);  //Luposoft, put whole unchanged code in new function mqtt_sendtoBroker to use it at other points as well
            }
          }
        }
        if (destAddr != d_addr) {
          return_to_default_destination(destAddr);
          my_dev_fam = save_my_dev_fam;
          my_dev_var = save_my_dev_var;
          my_dev_serial = save_my_dev_serial;

        }
        if (MQTTPubSubClient != NULL && !(LoggingMode & CF_LOGMODE_MQTT)) { //Luposoft: user may disable MQTT through web interface
          // Actual disconnect will be handled a few lines below through mqtt_disconnect().
          printlnToDebug("MQTT will be disconnected on order through web interface");
        }
      }
    }
    if (!(LoggingMode & CF_LOGMODE_MQTT)) {
      mqtt_disconnect();
    }
  }

  if ((LoggingMode & (CF_LOGMODE_SD_CARD|CF_LOGMODE_UDP))) {
    if (((millis() - lastLogTime >= (log_interval * 1000)) && log_interval > 0) || log_now > 0) {
//    SetDateTime(); // receive inital date/time from heating system
      log_now = 0;
      File dataFile;
      if (LoggingMode & CF_LOGMODE_SD_CARD) {
#if defined(ESP32)
        uint64_t freespace = totalBytes()-usedBytes();
#else
        int32_t freespace = SDCard.vol()->freeClusterCount();
#endif
        if (freespace > minimum_SD_size) {
          dataFile = SDCard.open(datalogFileName, FILE_APPEND);
          if (!dataFile) {
            // if the file isn't open, pop up an error:
            printToWebClient(MENU_TEXT_DTO "\r\n");
            printFmtToDebug("Error opening %s!\r\n", datalogFileName);
          }
        }
      }
      IPAddress broadcast_ip;
      if (LoggingMode & CF_LOGMODE_UDP) {
        IPAddress local_ip;
        if (network_type == WLAN) {
#if defined(ESP32) || defined(WIFISPI)
          local_ip = WiFi.localIP();
#endif
        } else {
          local_ip = Ethernet.localIP();
        }
        broadcast_ip = IPAddress(local_ip[0], local_ip[1], local_ip[2], 0xFF);
      }
      uint8_t destAddr = bus->getBusDest();
      uint8_t d_addr = destAddr;
      uint8_t save_my_dev_fam = my_dev_fam;
      uint8_t save_my_dev_var = my_dev_var;
      uint32_t save_my_dev_serial = my_dev_serial;
      for (int i = 0; i < numLogValues; i++) {
        int outBufLen = 0;
        if (log_parameters[i].number > 0) {
          if (log_parameters[i].dest_addr > -1){
            if (log_parameters[i].dest_addr != d_addr) {
              d_addr = log_parameters[i].dest_addr;
              set_temp_destination(log_parameters[i].dest_addr);
            }
          } else {
            if (destAddr != d_addr) {
              d_addr = destAddr;
              return_to_default_destination(destAddr);
              my_dev_fam = save_my_dev_fam;
              my_dev_var = save_my_dev_var;
              my_dev_serial = save_my_dev_serial;
            }
          }
          query(log_parameters[i].number);
          if (decodedTelegram.prognr < 0) continue;
          if (LoggingMode & CF_LOGMODE_UDP) udp_log.beginPacket(broadcast_ip, UDP_LOG_PORT);
          outBufLen += sprintf_P(outBuf + outBufLen, "%lu;%s;%g;", millis(), GetDateTime(outBuf + outBufLen + 80), log_parameters[i].number);

          if ((log_parameters[i].number >= (float)BSP_AVERAGES && log_parameters[i].number < (float)BSP_AVERAGES + numAverages)) {
            //averages
            outBufLen += strlen(strcpy(outBuf + outBufLen, STR_24A_TEXT ". "));
          }
          if (dataFile) {
            if (previousDatalogDate.combined != currentDate.combined) {
              File indexFile = SDCard.open(datalogIndexFileName, FILE_APPEND);
              if (indexFile) {
                previousDatalogDate.combined = currentDate.combined;
                long currentDatalogPosition = dataFile.size();
                indexFile.write((byte*)&currentDate, sizeof(currentDate));
                indexFile.write((byte*)&currentDatalogPosition, sizeof(currentDatalogPosition));
                indexFile.close();
                if (!firstDatalogDate.combined) firstDatalogDate.combined = currentDate.combined;
              }
              else printFmtToDebug("Error opening %s for writing!\r\n", datalogIndexFileName);
            }
            dataFile.print(outBuf);
          }
          if (LoggingMode & CF_LOGMODE_UDP) udp_log.print(outBuf);
          outBufLen = 0;
          strcpy(outBuf + outBufLen, decodedTelegram.prognrdescaddr);
          if (dataFile) dataFile.print(outBuf);
          if (LoggingMode & CF_LOGMODE_UDP) udp_log.print(outBuf);
          outBufLen = 0;
          if (decodedTelegram.sensorid) {
            outBufLen += sprintf_P(outBuf + outBufLen, "#%d", decodedTelegram.sensorid);
          }
          outBufLen += sprintf_P(outBuf + outBufLen, ";%s;%s\r\n", decodedTelegram.value, decodedTelegram.unit);
          if (dataFile) dataFile.print(outBuf);
          if (LoggingMode & CF_LOGMODE_UDP) udp_log.print(outBuf);
          if (LoggingMode & CF_LOGMODE_UDP) udp_log.endPacket();
        }
      }
      if (dataFile) dataFile.close();
      lastLogTime = millis();
      if (destAddr != d_addr) {
        return_to_default_destination(destAddr);
        my_dev_fam = save_my_dev_fam;
        my_dev_var = save_my_dev_var;
        my_dev_serial = save_my_dev_serial;
      }
    }
  }

// Calculate 24h averages
  if (LoggingMode & CF_LOGMODE_24AVG) {
    if (millis() / 60000 != lastAvgTime) {
      if (avgCounter == 1441) {
        for (int i=0; i<numAverages; i++) {
          avgValues_Old[i] = avgValues[i];
          avgValues_Current[i] = 0;
        }
        avgCounter = 1;
      }

      uint8_t destAddr = bus->getBusDest();
      uint8_t d_addr = destAddr;
      uint8_t save_my_dev_fam = my_dev_fam;
      uint8_t save_my_dev_var = my_dev_var;
      uint32_t save_my_dev_serial = my_dev_serial;
      for (int i = 0; i < numAverages; i++) {
        if (avg_parameters[i].number > 0) {
          if (avg_parameters[i].dest_addr > -1){
            if (avg_parameters[i].dest_addr != d_addr) {
              d_addr = avg_parameters[i].dest_addr;
              set_temp_destination(d_addr);
              GetDevId();
            }
          } else {
            if (destAddr != d_addr) {
              d_addr = destAddr;
              return_to_default_destination(destAddr);
              my_dev_fam = save_my_dev_fam;
              my_dev_var = save_my_dev_var;
              my_dev_serial = save_my_dev_serial;
            }
          }
          query(avg_parameters[i].number);
          float reading = strtod(decodedTelegram.value,NULL);
          printFmtToDebug("%f\r\n", reading);
          if (isnan(reading)) {} else {
            avgValues_Current[i] = (avgValues_Current[i] * (avgCounter-1) + reading) / avgCounter;
            if (avgValues_Old[i] == -9999) {
              avgValues[i] = avgValues_Current[i];
            } else {
              avgValues[i] = ((avgValues_Old[i]*(1440-avgCounter))+(avgValues_Current[i]*avgCounter)) / 1440;
            }
          }
          printFmtToDebug("%f\r\n", avgValues[i]);
        }
      }
      if (destAddr != d_addr) {
        return_to_default_destination(destAddr);
        my_dev_fam = save_my_dev_fam;
        my_dev_var = save_my_dev_var;
        my_dev_serial = save_my_dev_serial;
      }

      avgCounter++;
      lastAvgTime = millis() / 60000;

      // write averages to SD card to protect from power off
      if ((LoggingMode & CF_LOGMODE_SD_CARD) && avg_parameters[0].number > 0) { //write averages if at least one value is set
        File avgfile = SDCard.open(averagesFileName, FILE_WRITE);
        if (avgfile) {
          avgfile.seek(0);
          for (int i = 0; i < numAverages; i++) {
            sprintf_P(outBuf, "%f\r\n%f\r\n%f\r\n", avgValues[i], avgValues_Old[i], avgValues_Current[i]);
            avgfile.print(outBuf);
          }
          avgfile.println(avgCounter);
          avgfile.close();
        }
      }
    }
  } else {
    avgCounter = 1;
  }

  {
    if (One_Wire_Pin >= 0) {
      unsigned long tempTime = millis() / ONE_WIRE_REQUESTS_PERIOD;
      if (tempTime != lastOneWireRequestTime) {
        sensors->requestTemperatures(); //call it outside of here for more faster answers
        lastOneWireRequestTime = tempTime;
      }
    }
  }

#ifdef WATCH_SOCKETS
  ShowSockStatus();
  checkSockStatus();
#endif

// while we are here, update date/time as well...
//    SetDateTime();
// end calculate averages

#ifdef CUSTOM_COMMANDS
  {
    custom_timer = millis();
    #include "BSB_LAN_custom.h"
  }
#endif

  if (enable_max_cul) {
    byte max_str_index = 0;
#if OUTBUF_LEN < 60
#error "OUTBUF_LEN must be at least 60. In other case MAX! will not work."
#endif

    while (max_cul->available() && EEPROM_ready) {
      c = max_cul->read();
      printFmtToDebug("%c", c);
      if ((c!='\n') && (c!='\r') && (max_str_index<60)) {
        outBuf[max_str_index++]=c;
      } else {
        outBuf[max_str_index++]= '\0';
        if (verbose == DEVELOPER_DEBUG) writelnToDebug();
        break;
      }
    }
    if (max_str_index > 0) {
      if (outBuf[0] == 'Z') {
        char max_hex_str[9];
        char max_id[sizeof(max_device_list[0])] = { 0 };
        bool known_addr = false;
        bool known_eeprom = false;
  
        strncpy(max_hex_str, outBuf+7, 2);
        max_hex_str[2]='\0';
        uint8_t max_msg_type = (uint8_t)strtoul(max_hex_str, NULL, 16);
        strncpy(max_hex_str, outBuf+1, 2);
        max_hex_str[2]='\0';
        uint8_t max_msg_len = (uint8_t)strtoul(max_hex_str, NULL, 16);
        if (max_msg_type == 0x02) {
          strncpy(max_hex_str, outBuf+15, 6);
        } else {
          strncpy(max_hex_str, outBuf+9, 6);
        }
        max_hex_str[6]='\0';
        int32_t max_addr = (int32_t)strtoul(max_hex_str,NULL,16);
        uint16_t max_idx=0;
        for (max_idx=0;max_idx < MAX_CUL_DEVICES;max_idx++) {
          if (max_addr == max_devices[max_idx]) {
            known_addr = true;
            break;
          }
        }
        if (max_msg_type != 0x00 && known_addr == false) {
          printFmtToDebug("Message from unpaired MAX device address %08lX.\r\n", max_addr);
          if (verbose == DEVELOPER_DEBUG) printFmtToDebug("Raw message: %s\r\n", outBuf);
        }
  
        if (max_msg_type == 0x00) {     // Device info after pressing pairing button
          for (int x=0;x<10;x++) {
            strncpy(max_hex_str, outBuf+29+(x*2), 2);
            max_hex_str[2]='\0';
            max_id[x] = (char)strtoul(max_hex_str,NULL,16);
          }
          max_id[sizeof(max_device_list[0]) - 1] = '\0';
          printFmtToDebug("MAX device info received:\r\n%08lX\r\n%s\r\n", max_addr, max_id);
  
          for (uint16_t x=0;x<MAX_CUL_DEVICES;x++) {
            if (max_devices[x] == max_addr) {
              printlnToDebug("Device already in EEPROM");
              known_eeprom = true;
              break;
            }
          }
  
          if (!known_eeprom) {
            for (uint16_t x=0;x<MAX_CUL_DEVICES;x++) {
              if (max_devices[x] < 1) {
                strcpy(max_device_list[x], max_id);
                max_devices[x] = max_addr;
  
                writeToEEPROM(CF_MAX_DEVICES);
                writeToEEPROM(CF_MAX_DEVADDR);
                printlnToDebug("Device stored in EEPROM");
                break;
              }
            }
          }
        }
  
        if (max_msg_type == 0x02 && known_addr == true) {
          strncpy(max_hex_str, outBuf+27, 2);
          max_hex_str[2]='\0';
          max_valve[max_idx] = (uint32_t)strtoul(max_hex_str,NULL,16);
          printFmtToDebug("Valve position from thermostat received:\r\n%08lX\r\n%lu\r\n", max_addr, max_valve[max_idx]);
        }
  
        if ((max_msg_type == 0x42 || max_msg_type == 0x60) && known_addr == true) {   // Temperature from thermostats
          uint8_t temp_str_offset;
          uint32_t max_temp_status;
          uint8_t str_len;
  
          switch (max_msg_len) {
            case 0x0C: temp_str_offset = 23; str_len = 4; break;
            case 0x0E: temp_str_offset = 25; str_len = 8; break;
            default: temp_str_offset = 0; str_len = 8; break;
          }
          strncpy(max_hex_str, outBuf+temp_str_offset, str_len);
          max_hex_str[str_len]='\0';
          max_temp_status = (uint32_t)strtoul(max_hex_str,NULL,16);
          if (verbose == DEVELOPER_DEBUG) printFmtToDebug("%d\r\n%08lX\r\n", max_msg_len, max_temp_status);
          if (max_msg_type == 0x42) {
            max_cur_temp[max_idx] = (((max_temp_status & 0x8000) >> 7) + ((max_temp_status & 0xFF)));
            max_dst_temp[max_idx] = (max_temp_status & 0x7F00) >> 8;
          }
          if (max_msg_type == 0x60) {
            max_cur_temp[max_idx] = (max_temp_status & 0x0100) + (max_temp_status & 0xFF);
            max_dst_temp[max_idx] = (max_temp_status & 0xFF0000) >> 16;
            max_valve[max_idx] = (max_temp_status & 0xFF000000) >> 24;
          }
  
          printlnToDebug("MAX temperature message received:");
          printFmtToDebug("%08lX\r\n%f\r\n%f\r\n%lu\r\n", max_addr, ((float)max_cur_temp[max_idx] / 10), (float)(max_dst_temp[max_idx] / 2), max_valve[max_idx]);
        }
      }
    }
  }

  if (debug_mode == 2) {
    if (haveTelnetClient == false) {
      telnetClient = telnetServer->accept();
    }
    if (telnetClient && haveTelnetClient == false) {
//      telnetClient.flush();     // check if substitute for flush() is available since it is now deprecated. clear() only clears the RX buffer, but we want to flush the TX buffer.
      haveTelnetClient = true;
      printToDebug("Version: ");
      printlnToDebug(BSB_VERSION);
    }
    if (!telnetClient.connected()) {
      haveTelnetClient = false;
      telnetClient.stop();
    }
  }
#if !defined(ESP32)
  if(mDNS_hostname[0]) {
    mdns.run();
  }
#endif
#if defined(ESP32)
 if(enable_ota_update)
  update_server.handleClient();
#endif

#if defined(ESP32)
  if (network_type == WLAN && (localAP == true && millis() - localAPtimeout > 30 * 60 * 1000)) {    // Reboot after 30 minutes running local AP
    resetBoard();
  }
#endif

  if (millis() - maintenance_timer > 60000) {
    printFmtToDebug("%lu Ping!\r\n", millis());
    maintenance_timer = millis();
    //If device family and type was not detected at startup we will try recognize it every minute
    if (bus->getBusType() != BUS_PPS && !my_dev_fam) {
      SetDevId();
    }
#if defined(ESP32)
    struct tm now;
    getLocalTime(&now,100);
    if (now.tm_year < 100) {
      SetDateTime();
    }
#endif

#if defined(ESP32)
    if (network_type == WLAN) {
  // if WiFi is down, try reconnecting every minute
      bool not_preferred_bssid = false;
      if (WiFi.BSSID() != NULL) {
        for (int x=0;x<6;x++) {
          if (WiFi.BSSID()[x] != bssid[x] && bssid[x] > 0) {
            not_preferred_bssid = true;
          }
        }
      }
  
      if ((WiFi.status() != WL_CONNECTED || not_preferred_bssid == true) && localAP == false) {
        printFmtToDebug("Reconnecting to WiFi...\r\n");
        scanAndConnectToStrongestNetwork();
      }
    }
#endif
  }
  if (bus->getBusDest() != dest_address) { // just in case temporary reset doesn't (always) work, reset detination ID back to default.
    printFmtToDebug("Current destination ID %d does not match default destination ID %d, fixing...\r\n", bus->getBusDest(), dest_address);
    bus->setBusType(bus->getBusType(), own_address, dest_address);
    GetDevId();
  }
#if defined(ESP32)
  esp_task_wdt_reset();
#endif
} // --- loop () ---

#if defined(ESP32)

void scanAndConnectToStrongestNetwork() {
  int sum_bssid = 0;
  for (int x=0;x<6;x++) {
    sum_bssid += bssid[x];
  }
  if (sum_bssid > 0) {
    printToDebug("Using default BSSID to connect to WiFi...");
    esp_wifi_disconnect(); // W.Bra. 04.03.23 mandatory because of interrupts of AP; replaces WiFi.disconnect(x, y) - no arguments necessary
    WiFi.begin(wifi_ssid, wifi_pass, 0, bssid);
    unsigned long timeout = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - timeout < 5000) {
      delay(100);
      printFmtToDebug(".");
    }
    printlnToDebug("");
    if (WiFi.status() == WL_CONNECTED) {
      printlnToDebug("Connection successful using default BSSID.");
    } else {
      printlnToDebug("Connection with default BSSID failed, trying to scan...");
    }
  }
  esp_wifi_disconnect(); // W.Bra. 04.03.23 mandatory because of interrupts of AP; replaces WiFi.disconnect(x, y) - no arguments necessary
  int i_strongest = -1;
  int32_t rssi_strongest = -100;
  printFmtToDebug("Start scanning for SSID %s\r\n", wifi_ssid);

  int n = WiFi.scanNetworks(false, false); // WiFi.scanNetworks will return the number of networks found

  printToDebug("Scan done.");

  if (n == 0) {
    printlnToDebug("No networks found!");
  } else {
    printFmtToDebug("%d networks found:\r\n", n);
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      printFmtToDebug("%d: BSSID: %s  %2ddBm, %3d%%  %9s  %s\r\n", i, WiFi.BSSIDstr(i).c_str(), WiFi.RSSI(i), constrain(2 * (WiFi.RSSI(i) + 100), 0, 100), (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "open" : "encrypted", WiFi.SSID(i).c_str());
      if (strcmp(wifi_ssid, WiFi.SSID(i).c_str()) == 0 && (WiFi.RSSI(i) > rssi_strongest)) {
        rssi_strongest = WiFi.RSSI(i);
        i_strongest = i;
      }
    }
  }

  if (i_strongest < 0) {
    printFmtToDebug("No network with SSID %s found!\r\n", wifi_ssid);
  }
  printFmtToDebug("SSID match found at %d. Connecting...\r\n", i_strongest);
  WiFi.begin(wifi_ssid, wifi_pass, 0, WiFi.BSSID(i_strongest));
}

void printWifiStatus()
{
  if (WiFi.SSID() != NULL) {
    // print the SSID of the network you're attached to
    printFmtToDebug("SSID: %s\r\n", WiFi.SSID().c_str());
    printFmtToDebug("BSSID: %02X:%02X:%02X:%02X:%02X:%02X\r\n", WiFi.BSSID()[0], WiFi.BSSID()[1], WiFi.BSSID()[2], WiFi.BSSID()[3], WiFi.BSSID()[4], WiFi.BSSID()[5]);
    // print your WiFi shield's IP address
    IPAddress t = WiFi.localIP();
    printFmtToDebug("IP Address: %d.%d.%d.%d\r\n", t[0], t[1], t[2], t[3]);
  
    // print the received signal strength
    long rssi = WiFi.RSSI();
    printFmtToDebug("Signal strength (RSSI): %l dBm\r\n", rssi);
  }
}

void netEvent(WiFiEvent_t event) {
  switch (event) {
    case ARDUINO_EVENT_WIFI_READY:
    case ARDUINO_EVENT_WIFI_AP_START:
    case ARDUINO_EVENT_WIFI_AP_STOP:
    case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
    case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
    case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
      break;
    case ARDUINO_EVENT_ETH_START:
      SerialOutput->println("Ethernet Started.");
      // Set hostname here if needed
      Ethernet.setHostname(mDNS_hostname);
      break;
    case ARDUINO_EVENT_ETH_CONNECTED:
      SerialOutput->println("Ethernet connected.");
      if (localAP == true) {
        removeTemporaryAP();
      }
      break;
    case ARDUINO_EVENT_ETH_GOT_IP:
      SerialOutput->print("Ethernet got IP: ");
      SerialOutput->println(Ethernet.localIP());
      break;
    case ARDUINO_EVENT_ETH_DISCONNECTED:
      SerialOutput->println("Ethernet disconnected.");
      if (localAP == true) {
        removeTemporaryAP();
      }
      if (localAP == false) {
        createTemporaryAP();
      }
      break;
    case ARDUINO_EVENT_ETH_STOP:
      SerialOutput->println("ETH stopped.");
      if (localAP == true) {
        removeTemporaryAP();
      }
      if (localAP == false) {
        createTemporaryAP();
      }
      break;
    default:
/*
      SerialOutput->print("Network-Event ");
      SerialOutput->println(event);
*/
      break;
  }
}
#endif


// Call back for file timestamps.  Only called for file create and sync().
#if !defined(ESP32)
void dateTime(uint16_t* date, uint16_t* time) {
  // Return date using FS_DATE macro to format fields.
  *date = FS_DATE(year(), month(), day());

  // Return time using FS_TIME macro to format fields.
  *time = FS_TIME(hour(), minute(), second());

}
#endif

void startLoggingDevice() {
  Serial.print("LogDestination: ");
  Serial.println(LogDestination);
  printToDebug("Starting storage device...\r\n");
  #ifndef ESP32
  // disable w5100 while setting up SD
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
  if (!SDCard.begin(4, SPI_DIV3_SPEED)) {
    printToDebug("SD card failed.\r\n"); // change SPI_DIV3_SPEED to SPI_HALF_SPEED if you are still having problems getting your SD card detected
  } else {
    printToDebug("SD card mounted ok.\r\n");
  }
  #else
  if (LogDestination == SDCARD) {
#if (BOARD == ESP32_NODEMCU && !defined(FORCE_SD_MMC_ON_NODEMCU))   // NodeMCU
    SPI.begin(SD_SCK, SD_MISO, SD_MOSI);
    SD.end();
    if(!SD.begin(SD_CS)){
#else                               // Olimex or Joy-It NodeMCU with SD_MMC
    SD_MMC.end();
    if(!SD_MMC.begin("", true)){
#endif
      printToDebug("SD card failed\r\n");
    } else {
      printToDebug("SD card mounted ok\r\n");
    }
//    pinMode(TX1, OUTPUT);  // temporary workaround until most recent version of SD_MMC.cpp with slot.width = 1 is part of Arduino installation (should be release 1.0.5)
  } else {
    LittleFS.end();
    LittleFS.begin(true); // format on fail active
    printToDebug("Internal flash memory (LittleFS) mounted ok\r\n");
  }
  #endif
  #ifdef ESP32
  if (LogDestination == SDCARD) {
#if (BOARD == ESP32_NODEMCU && !defined(FORCE_SD_MMC_ON_NODEMCU))   // NodeMCU
    SDCard = SD;
#else
    SDCard = SD_MMC;
#endif
    minimum_SD_size = 100000;
  } else {
    SDCard = LittleFS;
    minimum_SD_size = 10000;
  }
  #else
  minimum_SD_size = 100;
  #endif
}

void createTemporaryAP () {
#if defined (ESP32)
  esp_wifi_disconnect(); // W.Bra. 04.03.23 mandatory because of interrupts of AP; replaces WiFi.disconnect(x, y) - no arguments necessary
  printlnToDebug("Setting up AP 'BSB-LAN'");
  WiFi.softAP("BSB-LAN", "BSB-LPB-PPS-LAN");
  IPAddress t = WiFi.softAPIP();
  localAP = true;
  localAPtimeout = millis();
  esp_wifi_set_bandwidth(WIFI_IF_AP, WIFI_BW_HT20); // W.Bra. 23.03.23 HT20
  printFmtToDebug("IP address of BSB-LAN: %d.%d.%d.%d\r\n", t[0], t[1], t[2], t[3]);
  printlnToDebug("Connect to access point 'BSB-LAN' with password 'BSB-LPB-PPS-LAN' and open the IP address.");
#endif
}

void removeTemporaryAP() {
#if defined (ESP32)
//  esp_wifi_disconnect(); // W.Bra. 04.03.23 mandatory because of interrupts of AP; replaces WiFi.disconnect(x, y) - no arguments necessary
  WiFi.softAPdisconnect(false);
  localAP = false;
//  WiFi.enableAP(false);
  printlnToDebug("Temporary AP 'BSB-LAN' deactivated.");
#endif
}

/** *****************************************************************
 *  Function: setup()
 *  Does:     Sets up the Arduino including its Ethernet shield.
 * Pass parameters:
 *  none
 * Parameters passed back:
 *  none
 * Function value returned:
 *  none
 * Global resources used:
 *  numSensors
 *  server instance
 *  sensors instance
 *  Serial instance
 *  Ethernet instance
 * *************************************************************** */
void setup() {

for (uint i=0; i<sizeof(dev_lookup)/sizeof(dev_lookup[0]); i++) {
  dev_lookup[i].dev_fam = 0xFF;
  dev_lookup[i].dev_var = 0xFF;
  dev_lookup[i].dev_id = 0xFF;
  dev_lookup[i].name[0] = '\0';
}

#ifdef BtSerial
  SerialOutput = &Serial2;
  Serial2.begin(115200, SERIAL_8N1); // hardware serial interface #2
#else
  SerialOutput = &Serial;
  Serial.begin(115200); // hardware serial interface #0
#endif

  decodedTelegram.telegramDump = NULL;
  pinMode(EEPROM_ERASING_PIN, INPUT_PULLUP);
#if defined(EEPROM_ERASING_GND_PIN)
  pinMode(EEPROM_ERASING_GND_PIN, OUTPUT);
#endif

  SerialOutput->println("READY");

#if defined(__arm__)
  Wire.begin();
  if (!EEPROM.ready()) {
    EEPROM_ready = false;
    SerialOutput->println("EEPROM not ready");
  }
#endif

  pinMode(LED_BUILTIN, OUTPUT);

#ifdef ESP32
  EEPROM.begin(EEPROM_SIZE); // size in Byte
#endif
//EEPROM erasing when button on pin EEPROM_ERASING_PIN is pressed
  if (!digitalRead(EEPROM_ERASING_PIN)) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    clearEEPROM();
    internalLEDBlinking(125, 16); //pause 4 sec for user informing and button release
  }

  //Read config parameters from EEPROM

  //Read "Header"
  initConfigTable(0);
  registerConfigVariable(CF_MAX_DEVICES, (byte *)max_device_list);
  registerConfigVariable(CF_MAX_DEVADDR, (byte *)max_devices);
  registerConfigVariable(CF_PPS_VALUES, (byte *)pps_values);
  uint8_t EEPROMversion = 0;
  registerConfigVariable(CF_USEEEPROM, (byte *)&UseEEPROM);
  registerConfigVariable(CF_VERSION, (byte *)&EEPROMversion);
  uint32_t crc;
  registerConfigVariable(CF_CRC32, (byte *)&crc);
  //link parameters
  registerConfigVariable(CF_BUSTYPE, (byte *)&bus_type);
  registerConfigVariable(CF_OWN_BSBLPBADDR, (byte *)&own_address);
  registerConfigVariable(CF_DEST_BSBLPBADDR, (byte *)&dest_address);
  registerConfigVariable(CF_PPS_MODE, (byte *)&pps_write);
  registerConfigVariable(CF_LOGTELEGRAM, (byte *)&logTelegram);
  registerConfigVariable(CF_AVERAGESLIST, (byte *)avg_parameters);
  registerConfigVariable(CF_LOGCURRINTERVAL, (byte *)&log_interval);
  registerConfigVariable(CF_CURRVALUESLIST, (byte *)log_parameters);
  registerConfigVariable(CF_ESP32_ENERGY_SAVE, (byte *)&esp32_save_energy);
  registerConfigVariable(CF_ROOM_DEVICE, (byte *)&pps_values[PPS_QTP]);
  registerConfigVariable(CF_NETWORK_TYPE, (byte *)&network_type);
  registerConfigVariable(CF_MAC, (byte *)mac);
  registerConfigVariable(CF_DHCP, (byte *)&useDHCP);
  registerConfigVariable(CF_IPADDRESS, (byte *)ip_addr);
  registerConfigVariable(CF_MASK, (byte *)subnet_addr);
  registerConfigVariable(CF_GATEWAY, (byte *)gateway_addr);
  registerConfigVariable(CF_DNS, (byte *)dns_addr);
  registerConfigVariable(CF_WWWPORT, (byte *)&HTTPPort);
  registerConfigVariable(CF_TRUSTEDIPADDRESS, (byte *)trusted_ip_addr);
  registerConfigVariable(CF_TRUSTEDIPADDRESS2, (byte *)trusted_ip_addr2);
  registerConfigVariable(CF_WIFI_SSID, (byte *)wifi_ssid);
  registerConfigVariable(CF_WIFI_PASSWORD, (byte *)wifi_pass);
  registerConfigVariable(CF_PASSKEY, (byte *)PASSKEY);
  registerConfigVariable(CF_BASICAUTH, (byte *)USER_PASS);
  registerConfigVariable(CF_ONEWIREBUS, (byte *)&One_Wire_Pin);
  registerConfigVariable(CF_DHTBUS, (byte *)DHT_Pins);
  registerConfigVariable(CF_BMEBUS, (byte *)&BME_Sensors);
  registerConfigVariable(CF_OTA_UPDATE, (byte *)&enable_ota_update);
  registerConfigVariable(CF_MDNS_HOSTNAME, (byte *)mDNS_hostname);
  registerConfigVariable(CF_IPWE, (byte *)&enable_ipwe);
  registerConfigVariable(CF_IPWEVALUESLIST, (byte *)ipwe_parameters);
  registerConfigVariable(CF_MAX, (byte *)&enable_max_cul);
  registerConfigVariable(CF_MAX_IPADDRESS, (byte *)max_cul_ip_addr);
  registerConfigVariable(CF_MQTT, (byte *)&mqtt_mode);
  registerConfigVariable(CF_MQTT_SERVER, (byte *)mqtt_broker_addr);
  registerConfigVariable(CF_MQTT_USERNAME, (byte *)MQTTUsername);
  registerConfigVariable(CF_MQTT_PASSWORD, (byte *)MQTTPassword);
  registerConfigVariable(CF_MQTT_TOPIC, (byte *)MQTTTopicPrefix);
  registerConfigVariable(CF_MQTT_DEVICE, (byte *)MQTTDeviceID);
  registerConfigVariable(CF_LOG_DEST, (byte *)&LogDestination);
  registerConfigVariable(CF_LOGMODE, (byte *)&LoggingMode);
  if (default_flag & FL_SW_CTL_RONLY) {
    registerConfigVariable(CF_WRITEMODE, (byte *)&programWriteMode);
  }
  registerConfigVariable(CF_DEBUG, (byte *)&debug_mode);
  registerConfigVariable(CF_VERBOSE, (byte *)&verbose);
  registerConfigVariable(CF_SHOW_UNKNOWN, (byte *)&show_unknown);
  registerConfigVariable(CF_CHECKUPDATE, (byte *)&enable_version_check);
  registerConfigVariable(CF_WEBSERVER, (byte *)&webserver);
  registerConfigVariable(CF_RX_PIN, (byte *)&bus_pins[0]);
  registerConfigVariable(CF_TX_PIN, (byte *)&bus_pins[1]);
  registerConfigVariable(CF_CONFIG_LEVEL, (byte *)&config_level);

  readFromEEPROM(CF_PPS_VALUES);
  byte UseEEPROM_in_config_h = UseEEPROM;
  if (UseEEPROM) { //Read EEPROM when it allowed from config file
    SerialOutput->println("Reading EEPROM");
    readFromEEPROM(CF_USEEEPROM);
    readFromEEPROM(CF_VERSION);
  }
    bool crc_correct = true;
  if (UseEEPROM == 0x96) {//Read EEPROM when EEPROM contain magic byte (stored configuration)
    readFromEEPROM(CF_CRC32);
    if (crc == initConfigTable(EEPROMversion)) {
  //read parameters
      for (uint8_t i = 0; i < sizeof(config)/sizeof(config[0]); i++) {
        if (verbose == DEVELOPER_DEBUG) SerialOutput->print(" Read parameter # "); SerialOutput->println(i);
  //read parameter if it version is non-zero
        if (config[i].version > 0 && config[i].version <= EEPROMversion) readFromEEPROM(config[i].id);
      }
    } else {
      SerialOutput->println("EEPROM schema CRC mismatch");
      crc_correct = false;
    }
  } else {
    SerialOutput->println("Using settings from config file");
    initConfigTable(EEPROMversion); //Need to init config table in any case because we can change opinion and can enable store config in EEPROM.
  }
  SerialOutput->println("Reading done.");

  //calculate maximal version
  uint8_t maxconfversion = 0;
  for (uint8_t i = 0; i < sizeof(config)/sizeof(config[0]); i++) {
    if (config[i].version > maxconfversion) maxconfversion = config[i].version;
  }
  SerialOutput->print("EEPROM schema v.");
  SerialOutput->print(EEPROMversion);
  SerialOutput->print(" Program schema v.");
  SerialOutput->println(maxconfversion);

  if (maxconfversion != EEPROMversion || !crc_correct) { //Update config "Schema" in EEPROM
    crc = initConfigTable(maxconfversion); //store new CRC32
    EEPROMversion = maxconfversion; //store new version
    if (UseEEPROM_in_config_h == 0x01) {//Update EEPROM when config file contain UseEEPROM = 1
      if (UseEEPROM != 0x69 && UseEEPROM != 0x96) UseEEPROM = 0x96;
      SerialOutput->println("Update EEPROM schema");
      for (uint8_t i = 0; i < CF_LAST_OPTION; i++) {
        //do not write here MAX! settings
        if (i != CF_MAX_DEVICES && i != CF_MAX_DEVADDR) {
          writeToEEPROM(i);
          if (verbose == DEVELOPER_DEBUG) SerialOutput->print("Write option # "); SerialOutput->println(i);
        }
      }
    }
  }

  unregisterConfigVariable(CF_VERSION);
  unregisterConfigVariable(CF_CRC32);

  byte save_debug_mode = debug_mode; //save debug_mode until setup is end.
  debug_mode = 1; //force using Serial debug until setup is end.

  for (uint8_t i = 0; i < CF_LAST_OPTION; i++) {
    printFmtToDebug("Address EEPROM option %d: %d\r\n", i, getEEPROMaddress(i));
  }

  if (save_debug_mode == 2) printToDebug("Logging output to Telnet\r\n");
  printFmtToDebug("Size of cmdtbl: %d\r\n",sizeof(cmdtbl));
  printFmtToDebug("free RAM: %d\r\n", freeRam());

  while (SerialOutput->available()) { // UART buffer often still contains characters after reset if power is not cut
    printFmtToDebug("%c", SerialOutput->read());
  }
  printFmtToDebug("BSB-LAN version: %s\r\n", BSB_VERSION);
#if defined(ESP32)
  printFmtToDebug("Microcontroller: %s\r\n", ARDUINO_BOARD);
#else
  printFmtToDebug("Microcontroller: %s\r\n", USB_PRODUCT);
#endif
// BSB/LPB/PPS bus init
  byte temp_bus_pins[2];
  if (bus_pins[0] && bus_pins[1]) {
    temp_bus_pins[0] = bus_pins[0];   // RX
    temp_bus_pins[1] = bus_pins[1];   // TX
  } else {
#if defined(ARDUINO_ESP32_EVB)
      pinMode(4, INPUT);
      temp_bus_pins[0] = 36;          // RX1
      if (digitalRead(4) == 0) {      // Dirty hack to test if BSB-LAN ESP32 board version is 4.2 and above
        temp_bus_pins[1] = 17;        // use GPIO17 / UEXT pin 10 for TX1 on Olime ESP32 EVB
      } else {
        temp_bus_pins[1] = 4;         // otherwise use standard TX1 pin, but Olimex EVB will not boot upon power on (you need to press reset to eventuall boot the Olimex EVB)
      }
#elif (defined(ARDUINO_ESP32_POE) || defined(ARDUINO_ESP32_POE_ISO))
      pinMode(4, INPUT);
      temp_bus_pins[0] = 36;        // RX1
      if (digitalRead(4) == 0) {      // Dirty hack to test if BSB-LAN ESP32 board version is 4.2 and above
        temp_bus_pins[1] = 5;         // use GPIO5 / UEXT pin 10 for TX1 on Olimex ESP32 PoE
      } else {
        temp_bus_pins[1] = 4;         // otherwise use standard TX1 pin, but Olimex EVB will not boot upon power on (you need to press reset to eventuall boot the Olimex EVB)
      }
#elif defined(ARDUINO_SAM_DUE)
      temp_bus_pins[0] = 19;          // RX2
      temp_bus_pins[1] = 18;          // TX2
#else
      temp_bus_pins[0] = 16;          // NodeMCU ESP32 RX2
      temp_bus_pins[1] = 17;          // TX2
#endif
  }

#if defined(__arm__)
  pinMode(temp_bus_pins[0], INPUT); //RX-pin of hardware serial on Due
#endif

  printFmtToDebug("Using RX/TX pins %d, %d\r\n", temp_bus_pins[0], temp_bus_pins[1]);
  bus = new BSB(temp_bus_pins[0], temp_bus_pins[1]);
  setBusType(); //set BSB/LPB/PPS mode

  printToDebug("Bus type defined in config: ");
  switch (bus_type) {
    case BUS_BSB:  printlnToDebug("BSB"); break;
    case BUS_LPB:  printlnToDebug("LPB"); break;
    case BUS_PPS:  printlnToDebug("PPS"); break;
    default: printlnToDebug("unknown!");
  }

  bus->enableInterface();
#if defined(ESP32)
  printFmtToDebug("ESP Arduino version: %d.%d.%d\r\n", ESP_ARDUINO_VERSION_MAJOR, ESP_ARDUINO_VERSION_MINOR, ESP_ARDUINO_VERSION_PATCH);
  if (esp32_save_energy == true) {
    bus->disableInterface();
    setCpuFrequencyMhz(80);
    bus->enableInterface();
    printToDebug("Power-saving activated.\r\n");
  }
  #ifndef WDT_TIMEOUT
  //set watchdog timeout 150 seconds
    #define WDT_TIMEOUT 150
  #endif
//    esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
  esp_task_wdt_config_t config = {
    .timeout_ms = WDT_TIMEOUT * 1000,  //  60 seconds
    .trigger_panic = true,     // Trigger panic if watchdog timer is not reset
  };
  esp_task_wdt_reconfigure(&config);
  esp_task_wdt_add(NULL); //add current thread to WDT watch
#endif

  if (One_Wire_Pin >= 0) {
    printToDebug("Init One Wire bus...\r\n");
    // Setup a oneWire instance to communicate with any OneWire devices
    oneWire = new OneWire(One_Wire_Pin);
    // Pass our oneWire reference to Dallas Temperature.
    sensors = new DallasTemperature(oneWire);
    // check ds18b20 sensors
    sensors->begin();
    numSensors=sensors->getDeviceCount();
    printFmtToDebug("numSensors: %d\r\n", numSensors);
  }

  if(BME_Sensors) {
    printToDebug("Init BMx280 sensor(s)...\r\n");
    if(BME_Sensors > 16) BME_Sensors = 16;
    bme = new BlueDot_BME280[BME_Sensors];
    for (uint8_t f = 0; f < BME_Sensors; f++) {
      bme[f].parameter.communication = 0;                     //I2C communication for Sensor
      //TCA9548A 1-to-8 I2C Multiplexer allow to manage 16 BME280.
      if(BME_Sensors > 2){
      // fill ports 1-8 on multiplexor first with devices with address 0x76.
      // if we need 9-16 sensors then 0x77 address will be used for these additional sensors.
        bme[f].parameter.I2CAddress = 0x76 + f / 8;           //I2C Address for Sensor.
        tcaselect(f & 0x07);                                  //Select channel on multiplexor
      } else {
        bme[f].parameter.I2CAddress = 0x76 + f;               //I2C Address for Sensor
      }
      bme[f].parameter.sensorMode = 0b11;                     //Setup Sensor mode
      bme[f].parameter.IIRfilter = 0b100;                     //IIR Filter for Sensor
      bme[f].parameter.humidOversampling = 0b101;             //Humidity Oversampling for Sensor
      bme[f].parameter.tempOversampling = 0b101;              //Temperature Oversampling for Sensor
      bme[f].parameter.pressOversampling = 0b101;             //Pressure Oversampling for Sensor
      bme[f].parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa
      bme[f].parameter.tempOutsideCelsius = 15;               //default value of 15°C
      bme[f].parameter.tempOutsideFahrenheit = 59;            //default value of 59°F
      bool sensor_found = true;
      switch(bme[f].init()){
        case 0x58: printToDebug("BMP280"); break;
        case 0x60: printToDebug("BME280"); break;
        default: printToDebug("Sensor"); sensor_found = false; break;
      }
      printFmtToDebug(" with address 0x%x ", bme[f].parameter.I2CAddress);
      if (!sensor_found) {
        printToDebug("NOT ");
      }
      printToDebug("found\r\n");
    }
  }

  printToDebug("PPS settings:\r\n");
  for (int i=0; i<PPS_ANZ; i++) {
    int l = findLine(15000+i);
    if (l==-1) continue;
    // fill bitwise array with flags
    uint16_t flags=cmdtbl[l].flags;
    if ((flags & FL_EEPROM) == FL_EEPROM) {
      allow_write_pps_values[i / 8] |= (1 << (i % 8));
      if (cmdtbl[l].type == VT_TIMEPROG) {      // On PPS bus, VT_TIMEPROG occupies six "slots" in pps_values[], five of which are "invisible", so we have to give these the same writing rights as well
        for (int j=1; j<6; j++) {
          allow_write_pps_values[(i+j) / 8] |= (1 << ((i+j) % 8));
        }
      }
    }
//    if ((flags & FL_EEPROM) == FL_EEPROM) {   // Testing for FL_EEPROM is not enough because volatile parameters would still be set to 0xFFFF upon reading from EEPROM. FL_VOLATILE flag would help, but in the end, there is no case where any of these values could/should be 0xFFFF, so we can safely assume that all 0xFFFF values should be set to 0.
      if (pps_values[i] == (int16_t)0xFFFF) {
        pps_values[i] = 0;
      }
      if (pps_values[i] > 0 && pps_values[i]< (int16_t)0xFFFF) {
        printFmtToDebug("Slot %d, value: %u\r\n", i, pps_values[i]);
      }
//    }
  }
  if (pps_values[PPS_QTP] == 0 || UseEEPROM != 0x96) {
    pps_values[PPS_QTP] = QAA_TYPE;
    writeToEEPROM(CF_ROOM_DEVICE);
  }
/*
  if (pps_values[PPS_RTI] != 0) { // should not be necessary to clear room temperature after reboot, as it is not written to EEPROM
    pps_values[PPS_RTI] = 0;
  }
*/

  if (LoggingMode & CF_LOGMODE_SD_CARD) {
    startLoggingDevice();
  } else {
#ifndef ESP32
    // enable w5100 SPI / LAN
    pinMode(10,OUTPUT);
    digitalWrite(10,LOW);

    // disable SD Card
    pinMode(4,OUTPUT);
    digitalWrite(4,HIGH);
#endif
  }

  printToDebug("Starting network connection via ");
  switch (network_type) {
    case LAN:  printToDebug("Ethernet/LAN"); break;
    case WLAN: printToDebug("WiFi/WLAN"); break;
  }
  printlnToDebug("...");
#if defined(ESP32)
  WiFi.onEvent(netEvent);
#endif

#ifdef WIFISPI
  WiFi.init(WIFI_SPI_SS_PIN);     // SS signal is on Due pin 12

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    printToDebug("WiFi shield not present. Cannot continue.\r\n");
    // don't continue
    while (true);
  }

  if (!WiFi.checkProtocolVersion()) {
    printToDebug("Protocol version mismatch. Please upgrade the WiFiSpiESP firmware of the ESP.\r\n");
    // don't continue:
    while (true);
  }
#endif

  // setup IP addresses
  if (!useDHCP && ip_addr[0]) {
    IPAddress ip(ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
    IPAddress subnet;
    IPAddress gateway;
    IPAddress dnsserver;
    if (subnet_addr[0]) {
      subnet = IPAddress(subnet_addr[0], subnet_addr[1], subnet_addr[2], subnet_addr[3]);
    } else {
      subnet = IPAddress(255, 255, 255, 0);
    }
    if (gateway_addr[0]) {
      gateway = IPAddress(gateway_addr[0], gateway_addr[1], gateway_addr[2], gateway_addr[3]);
    } else {
      gateway = IPAddress(ip_addr[0], ip_addr[1], ip_addr[2], 1);
    }
    if (dns_addr[0]) {
      dnsserver = IPAddress(dns_addr[0], dns_addr[1], dns_addr[2], dns_addr[3]);
    } else {
      dnsserver = IPAddress(ip_addr[0], ip_addr[1], ip_addr[2], 1);
    }
    if (network_type == LAN) {
      Ethernet.begin(mac, ip, dnsserver, gateway, subnet); //Static IP
    } else {
#if defined(ESP32)
      WiFi.config(ip, gateway, subnet, dnsserver);
#elif defined(WIFISPI)
      WiFi.config(ip, dnsserver, gateway, subnet);
#endif
    }
  } else {
    if (network_type == LAN) {
      if (Ethernet.begin(mac)) {  // DHCP
        if (!Ethernet.localIP()) {
          printToDebug("Waiting for DHCP address");
          unsigned long timeout = millis();
          while (!Ethernet.localIP() && millis() - timeout < 20000) {
              printToDebug(".");
              delay(100);
          }
          writelnToDebug();
        }
      }
    }
  }
#if defined(ESP32)
  if (network_type == LAN && !Ethernet.connected()) {
    createTemporaryAP();
  }
#endif
  if (network_type == LAN) {
    SerialOutput->print("IP: ");
    SerialOutput->print(Ethernet.localIP());
    SerialOutput->print(" netmask: ");
    SerialOutput->print(Ethernet.subnetMask());
    SerialOutput->print(" gateway: ");
    SerialOutput->println(Ethernet.gatewayIP());
  } else {
#if defined(ESP32) || defined(WIFISPI)
    unsigned long timeout;
    #ifdef ESP32
    // Workaround for problems connecting to wireless network on some ESP32, see here: https://github.com/espressif/arduino-esp32/issues/2501#issuecomment-731618196
    esp_wifi_disconnect(); //disconnect form wifi to set new wifi connection
    WiFi.mode(WIFI_STA); //init wifi mode
    esp_wifi_set_bandwidth(WIFI_IF_STA, WIFI_BW_HT20);  // W.Bra. 23.03.23 HT20 - reduce bandwidth from 40 to 20 MHz. In 2.4MHz networks, this will increase speed and stability most of the time, or will at worst result in a roughly 10% decrease in transmission speed.
  
    printToDebug("Setting up WiFi interface");
    WiFi.begin();
    timeout = millis();
    while (WiFi.status() == WL_DISCONNECTED && millis() - timeout < 5000) {
      delay(100);
      printToDebug(".");
    }
    writelnToDebug();
    scanAndConnectToStrongestNetwork();
    #endif
  
    // attempt to connect to WiFi network
    printFmtToDebug("Attempting to connect to WPA SSID: %s", wifi_ssid);
    timeout = millis();
    delay(1000);
    while (WiFi.status() != WL_CONNECTED && millis() - timeout < 10000) {
      printToDebug(".");
      delay(1000);
    }
    if (WiFi.status() != WL_CONNECTED) {
      printlnToDebug("Connecting to WiFi network failed.");
      createTemporaryAP();      // only effective on ESP32
    } else {
    // you're connected now, so print out the data
      printToDebug("\r\nYou're connected to the network:\r\n");
    #if defined(__arm__) || defined(ESP32)
      WiFi.macAddress(mac);  // overwrite mac[] with actual MAC address of ESP32 or WiFiSpi connected ESP
    #endif
    #if defined(ESP32)
      printWifiStatus();
    #endif
    }
#endif
  }

  server = new ComServer(HTTPPort);
  if (save_debug_mode == 2) telnetServer = new ComServer(23);

#ifndef ESP32
  if (!(LoggingMode & CF_LOGMODE_SD_CARD)) {
    digitalWrite(10,HIGH);
  }
#endif

  printlnToDebug("Waiting 3 seconds to give Ethernet shield time to get ready...");
  // turn the LED on until Ethernet shield is ready and other initial procedures are over
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)

  long diff = 3000;

// receive inital date/time either from NTP server or from heating system
  SetDateTime();

  if (bus->getBusType() != BUS_PPS) {

// receive device family (Gerätefamilie) and device variant (Gerätevariant) from heating system
    SetDevId();
    if (my_dev_fam != 0) {
      //decoration: double blink by LED to signal succesful detection of device family. effectively wait for a second
      internalLEDBlinking(250, 2);
      //end of decoration
    }
  } else {
    if (pps_values[PPS_QTP] == 0x58) {
      my_dev_fam = DEV_FAM(DEV_PPS_MCBA);
      my_dev_var = DEV_VAR(DEV_PPS_MCBA);
    } else {
      my_dev_fam = DEV_FAM(DEV_PPS);
      my_dev_var = DEV_VAR(DEV_PPS);
    }
  }

  if (LoggingMode & CF_LOGMODE_SD_CARD) {
    printToDebug("Calculating free space on SDCard...");
    uint32_t m = millis();
#if !defined(ESP32)
    uint32_t freespace = SDCard.vol()->freeClusterCount();
    freespace = (uint32_t)(freespace*SDCard.vol()->sectorsPerCluster()/2048);
    printFmtToDebug("%d MB free\r\n", freespace);
#else
    uint64_t freespace = totalBytes()-usedBytes();
    printFmtToDebug("%llu Bytes free\r\n", freespace);
#endif
    diff -= (millis() - m); //3 sec - delay
  }
  if (diff > 0) delay(diff);
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW

  printlnToDebug("Start network services");
  server->begin();

  if (save_debug_mode == 2)
  telnetServer->begin();

/*
// figure out which ENUM string has a lower memory address: The first one or the last one (hard coded to ENUM20 and LAST_ENUM_NR).
// Then use this as refernce to later determine if a page boundary >64kb has occurred.

  uint32_t c;
  int index_first_enum = 0;
  int index_last_enum = 0;
  uint32_t temp_offset1=0;
  uint32_t temp_offset2=0;

  index_first_enum = findLine(20, 0, &c);
  index_last_enum = findLine(LAST_ENUM_NR, 0, &c);
  temp_offset1 = pgm_read_word_far(pgm_get_far_address(cmdtbl[0].enumstr) + index_first_enum * sizeof(cmdtbl[0]));
  temp_offset2 = pgm_read_word_far(pgm_get_far_address(cmdtbl[0].enumstr) + index_last_enum * sizeof(cmdtbl[0]));

  if (temp_offset1 > temp_offset2) {
    enumstr_offset = temp_offset1;
    enum_page = (pgm_get_far_address(ENUM20) & 0xF0000) - 0x10000;
  } else {
    enumstr_offset = temp_offset2;
    enum_page = (pgm_get_far_address(LAST_ENUM) & 0xF0000) - 0x10000;
  }

//  enumstr_offset = temp_offset2;  // It seems that the compiler always starts at the end, so the last ENUM variable is put into (lower) memory first, so this is our point of reference.
*/

/*
  DebugOutput.println(enum_page, HEX);
  DebugOutput.println(temp_offset1, HEX);
  DebugOutput.println(temp_offset2, HEX);
  DebugOutput.println(pgm_get_far_address(LAST_ENUM), HEX);
  DebugOutput.println(pgm_get_far_address(ENUM10513), HEX);
  DebugOutput.println(pgm_get_far_address(ENUM10510), HEX);
  DebugOutput.println(pgm_get_far_address(ENUM8008), HEX);
  DebugOutput.println(pgm_get_far_address(ENUM8007), HEX);
  DebugOutput.println(pgm_get_far_address(ENUM8006), HEX);
  DebugOutput.println(pgm_get_far_address(ENUM20), HEX);

  DebugOutput.println((uint32_t)&ENUM20, HEX);
  DebugOutput.println(pgm_get_far_address(ENUM20), HEX);
  DebugOutput.println((uint32_t)&LAST_ENUM, HEX);
  DebugOutput.println(pgm_get_far_address(ENUMLASTENUM), HEX);
  //DebugOutput.println(temp_offset1, HEX);
  DebugOutput.println(temp_offset2, HEX);

  index_first_enum = 0;
  for (int i=0; i<=LAST_ENUM_NR; i++) {
    index_first_enum=findLine(i, 0, &c);
    temp_offset1 = pgm_read_word_far(pgm_get_far_address(cmdtbl[0].enumstr) + index_first_enum * sizeof(cmdtbl[0]));
    if (temp_offset1 > 0 && temp_offset1 < 65535) {
      DebugOutput.print(i);
      DebugOutput.print("\t");
      DebugOutput.println(temp_offset1, HEX);
    }
  }
*/

// initialize average calculation
  resetAverageCalculation();

#ifdef WATCH_SOCKETS
  unsigned long thisTime = millis();

  for (int i=0;i<MAX_SOCK_NUM;i++) {
    connectTime[i] = thisTime;
  }
#endif

// restore average
  if (LoggingMode & CF_LOGMODE_24AVG || LoggingMode & CF_LOGMODE_SD_CARD) {
    if (SDCard.exists(averagesFileName)) {
      File avgfile = SDCard.open(averagesFileName, FILE_READ);
      if (avgfile) {
        char c;
        char num[15];
        uint8_t x;
        for (int i=0; i<numAverages; i++) {
          c = avgfile.read();
          x = 0;
          while (avgfile.available() && c != '\n' && x < sizeof(num)-1) {
            if (x < sizeof(num)-1) {
              num[x] = c;
            }
            x++;
            c = avgfile.read();
          }
          num[x]='\0';
          avgValues[i] = atof(num);
          c = avgfile.read();
          x = 0;
          while (avgfile.available() && c != '\n' && x < sizeof(num)-1) {
            if (x < sizeof(num)-1) {
              num[x] = c;
            }
            x++;
            c = avgfile.read();
          }
          num[x]='\0';
          avgValues_Old[i] = atof(num);
          if (isnan(avgValues_Old[i])) {
            avgValues_Old[i] = -9999;
          }
  
          c = avgfile.read();
          x = 0;
          while (avgfile.available() && c != '\n' && x < sizeof(num)-1) {
            if (x < sizeof(num)-1) {
              num[x] = c;
            }
            x++;
            c = avgfile.read();
          }
          num[x]='\0';
          avgValues_Current[i] = atof(num);
        }
  
        c = avgfile.read();
        x = 0;
        while (avgfile.available() && c != '\n' && x < sizeof(num)-1) {
          if (x < sizeof(num)-1) {
            num[x] = c;
          }
          x++;
          c = avgfile.read();
        }
        num[x]='\0';
        avgCounter = atoi(num);
      }
      avgfile.close();
    }

    if (!SDCard.exists(datalogFileName)) {
      createdatalogFileAndWriteHeader();
    }
    else readFirstAndPreviousDatalogDateFromFile();
  }

  if (enable_max_cul) {
    UpdateMaxDeviceList();
    connectToMaxCul();
  }

  if(mDNS_hostname[0]) {
#if defined(ESP32)
    MDNS.begin(mDNS_hostname);
    MDNS.addService("http", "tcp", 80);
    MDNS.addService("BSB-LAN web service._http", "tcp", 80);
#else
    if (network_type==WLAN) {
#if defined(WIFISPI)
      mdns.begin(WiFi.localIP(), mDNS_hostname);
#endif
    } else {
      mdns.begin(Ethernet.localIP(), mDNS_hostname);
    }
    mdns.addServiceRecord("BSB-LAN web service._http", HTTPPort, MDNSServiceTCP);
#endif
    printFmtToDebug("Starting MDNS service with hostname %s\r\n", mDNS_hostname);
  }

// Set up web-based over-the-air updates for ESP32
#if defined(ESP32)
  init_ota_update();
#endif

#ifdef CUSTOM_COMMANDS
#include "BSB_LAN_custom_setup.h"
#endif

#if !defined(ESP32)
  FsDateTime::setCallback(dateTime);
#endif
  printlnToDebug("Setup complete");
  debug_mode = save_debug_mode; //restore actual debug mode
}
