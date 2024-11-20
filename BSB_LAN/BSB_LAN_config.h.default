/************************************************************************************/
/**********************************************<**************************************/
/* Settings -   BEGIN                                                               */
/************************************************************************************/
/************************************************************************************/

// Upon first installation, rename this file from BSB_lan_config.h.default to BSB_lan_config.h and adjust settings accordingly

/* Select language; so far German is the most complete, with English following.
 * Available languages are: Czech (CS), German (DE), Danish (DA), English (EN), Spanish (ES), Finnish (FI),
 * French (FR), Greek (EL), Hungarian (HU), Italian (IT), Dutch (NL), Polish (PL), Russian (RU), Swedish (SV),
 * Slovenian (SI) and Turkish (TR).
 * Incomplete languages will automatically be filled up with English translations first, and if no English translation
 * is available, fallback will take place to German.
*/
#define LANG DE

/*
Allow to initialize program configuration by reading settings from EEPROM
byte UseEEPROM = 0; // Configuration is read from this config file.
                    // Configuration can be stored in EEPROM but will not be used while UseEEPROM is zero.
                    // Set zero for fallback startup in case EEPROM configuration is broken or you cannot access BSB-LAN anymore.
byte UseEEPROM = 1; // Configuration will be read from EEPROM. This is the default.
*/
byte UseEEPROM = 1;

/*
 * Configuration of the network settings
*/
uint8_t network_type = LAN;             // Set to LAN (0) when using Ethernet connection. Set to WLAN (1) when using WiFi. Arduino users using WiFiSpi have to activate the definement below as well.
uint16_t HTTPPort = 80;
bool useDHCP = true;                    // Set to false if you want to use a fixed IP.
byte ip_addr[4] = {192,168,178,88};     // Please note the commas instead of dots!!!  Set useDHCP (above) to false if you want to use a fixed IP.
byte gateway_addr[4] = {192,168,178,1}; // Gateway address. This is usually your router's IP address. Please note the commas instead of dots!!! Ignored if first value is 0.
byte dns_addr[4] = {192,168,178,1};     // DNS server. Please note the commas instead of dots!!! Ignored if first value is 0.
byte subnet_addr[4] = {255,255,255,0};  // Subnet address. Please use commas instead of dots!!! Ignored if first value is 0.

char wifi_ssid[32] = "YourWiFiNetwork"; // enter your WiFi network name (SSID) here
char wifi_pass[64] = "YourWiFiPassword";// enter your WiFi password here
uint8_t bssid[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};  // enter specific BSSID address here to ensure connecting to a specific access point. Set to all zeros under normal circumstances.

//#define WIFISPI                         // Activate this on the Arduino to enable WiFi via WiFiSpi. DO NOT enable this on an ESP32.
#define WIFI_SPI_SS_PIN 12              // defines SPI-SS pin for Arduino-ESP8266 connection

char mDNS_hostname[32] = "BSB-LAN";     // Advertises the hostname in the local network. Set this to an empty string if you don't want your device to be found under this name in your network.

/* NTP settings to acquire exact date and time via network.
 * Attention: This only works with ESP32 microcontrollers so far!
 * Set to empty string to disable (or generally on Arduino Due) and receive time from heater instead.
 * Use pool.ntp.org if your BSB-LAN installation can access the internet.
 * Otherwise you may also use your router's address if it can act as a NTP server.
 * The default timezone "CET-1CEST,M3.5.0,M10.5.0/3" covers most Central European countries (GMT+1) and takes care of daylight saving.
 * Use "EET-2EEST,M3.5.0/3,M10.5.0/4" for Eastern European countries (GMT+2), or 
 * use "WET0WEST,M3.5.0/1,M10.5.0" for Western European countries (GMT+0).
 * See here for a full list of timezones for places all over the world:
 * https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
*/
const char ntp_server[20] = "pool.ntp.org"; // Set to empty string in case you don't want to use NTP
const char local_timezone[30] = "CET-1CEST,M3.5.0,M10.5.0/3";

/* SECURITY OPTIONS
 * There are several options to control and protect access to your heating system. However, keep
 * in mind, that even activating all three options are no guarantee that a versatile intruder with
 * access to your (W)LAN won't be able to gain access. In any case, no encryption of data streams
 * is provided from the Arduino itself. Use VPN or a SSL proxy if that is a must for you and connect
 * the Arduino wired to the VPN server or SSL proxy. On the other hand, someone with this amount
 * of criminal activity will probably have it easier just to access your heating system face-to-face ;)
*/

/*
 * if PASSKEY length is non-zero, the URL has to contain the defined passkey as first element
 * e.g.
 * char PASSKEY[64] = "1234";
 * http://192.168.178.88/1234/                - to view the main website (don't forget the trailing slash!)
 * http://192.168.178.88/1234/K               - to list all categories
 * http://192.168.178.88/1234/8700/8740/8741  - to list parameters 8700, 8740 and 8741 in one request
*/
char PASSKEY[64] = "";

/* activate IP-address-based access.
You can set any ip address as trusted.
Not used if first byte is 0
*/
byte trusted_ip_addr[4] = {0,0,0,0};
byte trusted_ip_addr2[4] = {0,0,0,0};

/* Activate HTTP-Auth authentication to provide username/password based access. No encryption!
 * Credentials have to be entered in the form
 * User:Password
 */
//char USER_PASS[64] = "User:Password";
char USER_PASS[64] = "";      // HTTP-Auth will be disabled if USER_PASS string length is zero

/*
 *  Enter a MAC address, found either on the EthernetShield or use the one below.
 *  Change this if you have more than one BSB-LAN adapter in your LAN, so that there aren't any address conflicts.
 *  MAC address here only affects the LAN shield, it doesn't apply to the WiFi-ESP-solution.
*/
byte mac[6] = { 0x00, 0x80, 0x41, 0x19, 0x69, 0x90 };

// Setting bus type
uint8_t bus_type = 0;  // set bus system at boot: 0 = BSB, 1 = LPB, 2 = PPS
// BSB:
// - 'own_address' sets own address, defaults to 0x42 (LAN in serial monitor)
// - 'dest_address' sets destination address, defaults to 0 for heating system.
// LPB:
// - 'own_address and 'dest_address' set own and destination address (high nibble = segment, low nibble = device minus 1)
// - defaults to 0x42 for own address and 0x00 for destination address, i.e. segment 4, device 3 for BSB-LAN and segment 0, device 1 for heating system
byte own_address = 0x42;
byte dest_address = 0x00;
// PPS:
// - set 'pps_write' to "1" to enable writing to heater - only use this if there is no other room controller (such as QAA50/QAA70) active.
bool pps_write = 0;
byte QAA_TYPE = 0x53;  // 0x53 = QAA70, 0x52 = QAA50, 0x37 = QAA95, 0x4D = QAW10, 0x4E = QAW20, 0x58 = MCBA/REA70/DC225, 0x5A = QAA10, 0x5B = QAA20, 0x5D = QAA12/13, 0x66 = BMU, 0x43 = RVD130
// Setting bus pins
byte bus_pins[2] = {0,0}; //First value - RX pin, second value - TX pin. 0,0 - auto select (19,18 for Due, 16,17 for NodeMCU, 36,17 for Olimex EVB, 36,5 for Olimex POE and 68,69 for Mega).

// defines default flag for parameters
// use "#define DEFAULT_FLAG FL_SW_CTL_RONLY" to control read/write functionality via configuration in web interface.
// use "#define DEFAULT_FLAG 0" to make (almost) all parameters writeable
// use #define DEFAULT_FLAG FL_RONLY to run the program always in read-only mode.
#define DEFAULT_FLAG FL_SW_CTL_RONLY

// Setting to determine on ESP32 whether to use SD card adapter (if present) or ESP32's internal flash.
// SD card should always be preferred to protect the ESP32's flash from wearing down.
uint8_t LogDestination = SDCARD;  // Possible logging devices: SDCARD (0) = SD card, FLASH (1) = ESP32's flash memory
// If you use an SD card reader on the Joy-It ESP32 NodeMCU, you can configure the SPI pins here:
#define SD_SCK 18
#define SD_MISO 19
#define SD_MOSI 23
#define SD_CS 5
//#define FORCE_SD_MMC_ON_NODEMCU   // enable this definement if you want to force using the SD_MMC library instead of SPI on an ESP32 NodeMCU


// Log "raw" bus telegrams. Data saved in journal.txt on SD-card.
// Telegrams logged upon boot:
// uint8_t logTelegram = LOGTELEGRAM_OFF;                                       // nothing to log,
// uint8_t logTelegram = LOGTELEGRAM_ON;                                        // log all telegrams,
// uint8_t logTelegram = LOGTELEGRAM_UNKNOWN_ONLY;                              // log unknown telegrams,
// uint8_t logTelegram = LOGTELEGRAM_BROADCAST_ONLY;                            // log broadcast telegrams,
// uint8_t logTelegram = LOGTELEGRAM_UNKNOWN_ONLY + LOGTELEGRAM_BROADCAST_ONLY; // log unknown broadcast telegrams only;
uint8_t logTelegram = LOGTELEGRAM_OFF;

// Logging data from parameters
// Interval and list of parameters can be redefined through /L command during runtime
// Data will be written to "datalog.txt"
unsigned long log_interval = 300;  // Logging interval (to SD card, UDP and MQTT broker) in seconds
parameter log_parameters[40] = {
// parameter, destination (as in dest_address below, -1 means "default (dest_address) address")
  {8700, -1},                   // Außentemperatur
  {8743, -1},                  // Vorlauftemperatur
  {8314, -1},                  // Rücklauftemperatur
//  {20000, -1},                 // Spezialparameter: Brenner-Laufzeit Stufe 1
//  {20001, -1},                 // Spezialparameter: Brenner-Takte Stufe 1
//  {20002, -1},                 // Spezialparameter: Brenner-Laufzeit Stufe 2
//  {20003, -1},                 // Spezialparameter: Brenner-Takte Stufe 2
//  {20004, -1},                 // Spezialparameter: TWW-Laufzeit
//  {20005, -1},                 // Spezialparameter: TWW-Takte
//  {20050, -1},                 // Spezialparameter 20050-20099: 24h-Durchschnittswerte
//  {20100, -1},                 // Spezialparameter 20100-20299: DHT22-Sensoren 1-50
//  {20300, -1},                 // Spezialparameter 20300-20499: DS18B20-Sensoren 1-100
//  {20500, -1}                  // Spezialparameter 20500-20699: MAX!-Sensoren 1-50
};

// Compile MQTT extension: activate sending log_parameters to MQTT broker every log_interval seconds
char mqtt_broker_addr[33] = "192.168.178.20:1883";    // MQTT broker. Adjust LoggingMode to activate. Can be IP address or hostname. Optional port can be specified after trailing colon. If omitted, port defaults to 1883.
char MQTTUsername[65] = "User";                 // Set username for MQTT broker here or set empty string if no username/password is used.
char MQTTPassword[65] = "Pass";                 // Set password for MQTT broker here or set empty string if no password is used.
char MQTTTopicPrefix[65] = "BSB-LAN"; 	        // Mandatory: Choose the "topic" for MQTT messages here.
byte mqtt_mode = 1; // MQTT: 1 - send messages in plain text format, 2 - send messages in JSON format, 3 - send messages in rich JSON format. Use this if you want a json package of your logging information printed to the mqtt topic
// JSON payload will be of the structure: {"MQTTDeviceID": {"status":{"log_param1":"value1"}}}
// rich JSON payload will be of the structure: {"MQTTDeviceID": {"id": "parmeter number from log values", "name": "parameter name from logvalues", "value": "query result", "desc": "enum value description", "unit": "unit of measurement", "error", error code}}

// Optional: Define a device name to use as header in json payload. In case of empty string, "BSB-LAN" will be used.
// This value is also used as a client ID towards the MQTT broker, change it if you have more than one BSB-LAN on your broker.
char MQTTDeviceID[32] = "BSB-LAN";

// Logging mode: 0 - disabled, 1 - write values to SD card, 2 - write 24h averages to SD card, 4 - send values to MQTT, 8 -  send values to UDP. Can be any sum of these values.
byte LoggingMode = 0; //CF_LOGMODE_SD_CARD | CF_LOGMODE_24AVG | CF_LOGMODE_MQTT | CF_LOGMODE_MQTT_ONLY_LOG_PARAMS | CF_LOGMODE_UDP

// Create 24h averages from these parameters and save data into averages.txt on SD-card.
parameter avg_parameters[40] = {
// parameter, destination (as in dest_address below, -1 means "default (dest_address) address")
  {8700, -1},                         // Außentemperatur
  {8326, -1}                          // Brenner-Modulation
};

// Define the pin for one wire temperature sensors. -1 = disable oneWire bus.
int8_t One_Wire_Pin = -1;

// Define the pins for DHT temperature/humidity sensors (Up to 10). -1 = disable DHT sensor.
int8_t DHT_Pins[10] =  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

// Define the number of BME280 temperature/humidity/pressure sensors on the I2C bus. 0 = disable BME280 sensors.
// Up to two sensors with 0x76 and 0x77 addresses, up to 16 when using a TCA9548A I2C mulitplexer.
byte BME_Sensors = 0;

bool enable_ipwe = false;  // true - activate IPWE extension (http://xxx.xxx.xxx.xxx/ipwe.cgi)
// Parameters to be displayed in IPWE extension
parameter ipwe_parameters[40] = {
// parameter, destination (as in dest_address below, -1 means "default (dest_address) address")
  {8700, -1},                  // Außentemperatur
  {8743, -1},                  // Vorlauftemperatur
  {8314, -1},                  // Rücklauftemperatur
//  {8750, -1},                  // Gebläsedrehzahl
//  {8830, -1},                  // Warmwassertemperatur
//  {8740, -1},                  // Raumtemperatur Ist
//  {8741, -1},                  // Raumtemperatur Soll
//  {8326, -1},                  // Brenner-Modulation
//  {8337, -1},                  // Startzähler Brenner
//  {8703, -1},                  // Aussentemperatur gedämpft
//  {8704, -1}                   // Aussentemperatur gemischt
};

// If you prefer to use the log file plotting (/DG) used in BSB-LAN 2.1.3, disable the following #define.
// Otherwise a newer implementation will be used that does require (automated) loading of an additional
// Javascript library off the internet (currently 204 KB), but offers the following improvements:
// - better legibility for value numbers with plot lines close to each other (mouseover on plot)
// - user can interactively highlight plot lines for improved overview (mouseover on legend entries)
// - user can interactively disable plot lines for improved overview and vertical scaling (click on legend entries)
// - added zoom (mousewheel/pinch on plot) and pan capability (drag zoomed-in plot)
// - selective plotting of data from big logs
#define USE_ADVANCED_PLOT_LOG_FILE
#define DEFAULT_DAYS_TO_PLOT "3" // must be a positive integer value in double quotes!
// Log file plotting uses two JavaScript libraries, which are usually loaded from the web.
// Should you prefer to use local copies instead, put the files from the data subdirectory onto your
// bsb-lan unit's SD card (*), and provide their path names here. For browsers that support gzip
// compression (what browser doesn't?), it is sufficient to copy the *.gz file versions to your
// bsb-lan unit, but omit the ".gz" from the path names you put into the following lines!
// (*) In case you're using an ESP32's internal memory instead of an SD card, use
// https://github.com/lorol/arduino-esp32littlefs-plugin to upload the files.
// For local use of these libraries to work, enabling webserver functionality is also required!
//#define D3_LIBRARY_PATH "/d3.js"
//#define C3_LIBRARY_PATH "/c3.js"

bool enable_max_cul = false;                // enable or disable connection to CUNO/CUNX/modified MAX!Cube;
byte max_cul_ip_addr[4] = {192,168,178,5};     // IP of CUNO/CUNX/modified MAX!Cube. Please use commas instead of dots!!!
char max_device_list[20][11] = {               // list of MAX! wall/heating thermostats that should be polled
  "KEQ0502326",                                // use MAX! serial numbers here which have to have exactly 10 characters
  "KEQ0505080"
};

// include commands from BSB_lan_custom.h to be executed at the end of each main loop
//#define CUSTOM_COMMANDS

/*
 * Check for new versions when accessing BSB-LAN's main page.
 * Doing so will poll the most recent version number from the BSB-LAN server.
 * In this process, it is unavoidable that your IP address will be transferred to the server, obviously.
 * We nevertheless mention this here because this constitutes as 'personal data' and this feature is therefore disabled by default.
 * Activating this feature means you are consenting to transmitting your IP address to the BSB-LAN server where it will be stored
 * for up to two weeks in the server's log files to allow for technical as well as abuse analaysis.
 * No other data (such as anything related to your heating system) is transmitted in this process, as you can see in the source code.
*/
bool enable_version_check = false;

// Enable ESP32 over-the-air updates. 
// Pro: You don't need to physically connect your PC to the ESP32 in order to update BSB-LAN.
// Contra: Someone who has access to your network and finds out about BSB-LAN's username and password can install their own software on the ESP32.
boolean enable_ota_update = false;

// Reduce clock speed of ESP32 from 240 MHz to 80MHz, saving ca. 20% energy.
// Works well when connecting via LAN, but since it reduces WiFi range and log file display times when using WiFi, it is disabled by default.
boolean esp32_save_energy = false;

// "External" web server. Read files from SD-card / flash memory. Only static content: html, js, css, jpg, etc.
boolean webserver = false;

// Debug options
byte debug_mode = 1;  // Debug mode: 0 - disabled, 1 - send debug messages to serial interface, 2 - send debug messages to telnet client
byte verbose = 1;     // If set to 1, all messages on the bus are printed to debug interface. Set to 2 only if you are asked by the developers as the extensive output will significantly slow down the microcontroller.
bool show_unknown = true; // true - show all parameters, false - hide unknown parameters from web display (parameters will still be queried and therefore take time!)

#define CONFIG_VERSION 39

/************************************************************************************/
/************************************************************************************/
/* Settings -   END                                                                 */
/************************************************************************************/
/************************************************************************************/
