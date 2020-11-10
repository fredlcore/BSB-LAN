/************************************************************************************/
/************************************************************************************/
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
 *  Enter a MAC address, found either on the EthernetShield or use the one below.
*/
byte mac[] = { 0x00, 0x80, 0x41, 0x19, 0x69, 0x90 };

/*
 * Initialize the Ethernet server library
 * with the IP address and port you want to use
 * (port 80 is default for HTTP):
*/

uint16_t HTTPPort = 80;
boolean useDHCP = true;
byte ip_addr[4] = {192,168,178,88}; // please note the commas instead of dots!!!  Set useDHCP to true when you want DHCP
byte gateway_addr[4] = {192,168,178,1}; // this is usually your router's IP address. Please note the commas instead of dots!!! Ignored, when first value is 0
byte dns_addr[4] = {192,168,178,1}; //  DNS server. Please note the commas instead of dots!!! Ignored, when first value is 0
byte subnet_addr[4] = {255,255,255,0}; // Please use commas instead of dots!!! Ignored, when first value is 0


#define DEBUG //Compile verbose DEBUG module if defined
byte debug_mode = 2; //Debug: 0 - disabled, 1 - send debug messages to serial interface, 2 - send debug messages to telnet client
byte verbose = 1; // If set to 1, all messages on the bus are printed to debug interface
byte monitor = 0; //bus monitor mode
boolean show_unknown = true; // true - show all parameters, false - hide unknown parameters from web display (parameters will still be queried!)

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
Not used when first byte is 0
*/
byte trusted_ip_addr[4] = {0,0,0,0};
byte trusted_ip_addr2[4] = {0,0,0,0};

/* activate HTTP-Auth authentication to provide username/password based access. No encryption!
 * Default sets username to "atari" and password to "800xl". Visit a website like
 * https://www.base64encode.org/
 * to encode your own username/password combination in the format username:password
 * and replace the YXRhcmk6ODAweGw= string below accordingly.
*/
//char USER_PASS_B64[64] = "YXRhcmk6ODAweGw=";
char USER_PASS_B64[64] = ""; // HTTP-Auth will be disabled if USER_PASS_B64 string length is zero


// Compile module with one wire bus support.
#define ONE_WIRE_BUS
boolean enableOneWireBus = true; //true - enable oneWire bus, false - disable
byte One_Wire_Pin = 3; //Define the pin for one wire temperature sensors

// Compile module with DHT temperature/humidity sensors support
#define DHT_BUS
// Define the pins for DHT temperature/humidity sensors (Up to 10)
byte DHT_Pins[10] = {2, 3};

// Compile module for calculation 24h averages for selected programs
#define AVERAGES
boolean logAverageValues = true;      // calculate and save data into averages.txt on SD-card.
// Create 24h averages from these parameters
int avg_parameters[40] = {
  8700,                   // Außentemperatur
  8326                    // Brenner-Modulation
};

/* Compile module for logging on SD-card.
Requires a FAT32-formatted Micro-SD card inserted
into the Ethernet-Shield's card slot
Does: log telegram to file
      Log selected values to file
      store to SD and load selected 24h averages*/
#define LOGGER

// Logging von "rohen" Bus-Datentelegrammen
// data saved into journal.txt on SD-card.
// Telegrams logging on start:
// int logTelegram = LOGTELEGRAM_OFF; // nothing to log,
// int logTelegram = LOGTELEGRAM_ON; // log all telegrams,
// int logTelegram = LOGTELEGRAM_ON + LOGTELEGRAM_UNKNOWN_ONLY; // log unknown telegrams,
// int logTelegram = LOGTELEGRAM_ON + LOGTELEGRAM_BROADCAST_ONLY; // log broadcast telegrams,
// int logTelegram = LOGTELEGRAM_ON + LOGTELEGRAM_UNKNOWNBROADCAST_ONLY; // log unknown broadcast telegrams only;
int logTelegram = LOGTELEGRAM_OFF;

// Logging data from parameters
// Interval and list of parameters can be redefined through /L command when run time
// Data will be write to "datalog.txt"
boolean logCurrentValues = true;      // save data into datalog.txt on SD-card.
unsigned long log_interval = 3600;    // logging interval (to SD card and MQTT broker) in seconds
int log_parameters[40] = {
  8700,                   // Außentemperatur
  8743,                   // Vorlauftemperatur
  8314,                   // Rücklauftemperatur
//  20000,                  // Spezialparameter: Brenner-Laufzeit Stufe 1(/B)
//  20001,                  // Spezialparameter: Brenner-Takte Stufe 1 (/B)
//  20002,                  // Spezialparameter: Brenner-Laufzeit Stufe 2(/B)
//  20003,                  // Spezialparameter: Brenner-Takte Stufe 2 (/B)
//  20004,                  // Spezialparameter: TWW-Laufzeit (/B)
//  20005,                  // Spezialparameter: TWW-Takte (/B)
//  20050,                  // Spezialparameter 20050-20099: 24h-Durchschnittswerte (/A)
//  20100,                  // Spezialparameter 20100-20299: DHT22-Sensoren 1-50 (/T)
//  20300                   // Spezialparameter 20300-20499: DS18B20-Sensoren 1-100 (/T)
//  20500                   // Spezialparameter 20500-20699: MAX!-Sensoren 1-50 (/T)
};

// Compile MQTT extension: activate sending log_parameters to MQTT broker every log_interval seconds
//#define MQTT
byte mqtt_mode = 0; //MQTT: 0 - disabled, 1 - send messages in plain text format, 2 - send messages in JSON format. Use this if you want a json package of your logging information printed to the mqtt topic
// JSON payload will be of the structure: {"MQTTDeviceID": {"status":{"log_param1":"value1","log_param2":"value2"}, ...}}
byte mqtt_broker_ip_addr[4] = {192,168,1,20};// Please use commas instead of dots!!!
char MQTTUsername[32] = "User"; // Set username for MQTT broker here or set zero-length string if no username/password is used.
char MQTTPassword[32] = "Pass"; // Set password for MQTT broker here or set zero-length string if no password is used.
char MQTTTopicPrefix[32] = "BSB-LAN"; 	// Optional: Choose the "topic" for MQTT messages here. If zero-length string here, default topic name used
char MQTTDeviceID[32] = "MyHeater";	// Optional: Define a device name to use as header in json payload. If zero-length string here, "BSB-LAN" will be used.

// Compile IPWE extension
#define IPWE
boolean enable_ipwe = false; //true - activate IPWE extension (http://xxx.xxx.xxx.xxx/ipwe.cgi)
// Parameters to be displayed in IPWE extension
int ipwe_parameters[40] = {
  8700,                   // Außentemperatur
  8743,                   // Vorlauftemperatur
  8314,                   // Rücklauftemperatur
  8750,                   // Gebläsedrehzahl
  8830,                   // Warmwassertemperatur
  8740,                   // Raumtemperatur Ist
  8741,                   // Raumtemperatur Soll
  8326,                   // Brenner-Modulation
  8337,                   // Startzähler Brenner
  8703,                   // Aussentemperatur gedämpft
  8704                    // Aussentemperatur gemischt
};


// Compile CUNO/CUNX/modified MAX!Cube extension.
//#define MAX_CUL
boolean enable_max_cul = false;                //enable or disable connection to CUNO/CUNX/modified MAX!Cube;
byte max_cul_ip_addr[4] = {192,168,178,5};     //  IP of CUNO/CUNX/modified MAX!Cube. Please use commas instead of dots!!!
char max_device_list[20][11] = {               // list of MAX! wall/heating thermostats that should be polled
  "KEQ0502326",                                // use MAX! serial numbers here which have to have exactly 10 characters
  "KEQ0505080"
};


// defines the number of retries for the query command
#define QUERY_RETRIES  3

/* enable /N URL command to reset Arduino - might not work on older boards */
//#define RESET

// Setting bus pins and bus type
// Bus bus (RX pin, TX pin, parameter 3, parameter 4)
// Software Serial needs special pins for RX: 10-13, 50-53, 62(A8)-69(A15)
// W5100 ethernet shield uses the following pins: 10, 50-53

byte bus_pins[2] = {0,0}; //First value - RX pin, second - TX pin. 0,0 - auto select (19,18 for Duo and 68,69 for Mega)
uint8_t bus_type = 0;  // set bus system at boot: 0 = BSB, 1 = LPB, 2 = PPS
// BSB:
// - 'own_bsb_address' sets own address, defaults to 0x42 (LAN in serial monitor)
// - use own_bsb_address = 6; to define device as RGT1
byte own_bsb_address = 0x42; // parameter 3
// LPB:
// - 'own_lpb_address and 'dest_lpb_address' set own and destination address (high nibble = segment, low nibble = device minus 1)
// - defaults to 0x42 for own address and 0x00 for destination address, i.e. segment 4, device 3 for Arduino/BSB-LAN and segment 0, device 1 for heating system
byte own_lpb_address = 0x42; // parameter 3
byte dest_lpb_address = 0x00; // parameter 4
// PPS:
// - set 'pps_write' to "1" enables writing to heater - only use this if there is no other room controller (such as QAA50/QAA70) active.
boolean pps_write = 0; // parameter 3
byte QAA_TYPE = 0x53;  // 0x53 = QAA70, 0x52 = QAA50


#if defined(__AVR__) // Mega2560
// Protect these pins from accidental GPIO access
// bit-coded list of protected GPIO pins. 0 - pin unprotected, 1 - pin protected
//              pins list:   7  --  0,  15 --  8,  23 -- 16,  31 -- 24,  39 -- 32,  47 -- 40,  55 -- 48,  63 -- 56,  71 -- 64,  79 -- 72,
byte protected_GPIO[10] = {0b00000000,0b00111100,0b00000000,0b00000000,0b00000000,0b00000000,0b00111100,0b11000000,0b00111111,0b00000000};
//byte exclude_GPIO[70] = {10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69};
#else  // Duo
// Protect these pins from accidental GPIO access
// bit-coded list of protected GPIO pins. 0 - pin unprotected, 1 - pin protected
//              pins list:   7  --  0,  15 --  8,  23 -- 16,  31 -- 24,  39 -- 32,  47 -- 40,  55 -- 48,  63 -- 56,  71 -- 64,  79 -- 72,
byte protected_GPIO[10] = {0b00001011,0b00111100,0b11111100,0b00000000,0b00000000,0b00000000,0b00111100,0b11000000,0b00111111,0b00000000};
//byte exclude_GPIO[70] = {0, 1, 4, 10, 11, 12, 13, 18, 19, 20, 21, 22, 23, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69};
#endif



/* select your heating system (default may work for other systems)
 * Set fixed_device_family and fixed_device_variant to your device family and variant (parameters 6225 and 6226) here
 * if auto-detect does not work or heating system is not running when Arduino is powered on
 * You may use other device family numbers to test commands from other heating systems at your own risk
*/
static const int fixed_device_family = 0;
static const int fixed_device_variant = 0;

// defines default flag for parameters (use "#define DEFAULT_FLAG 0" to make (almost) all parameters writeable)
#define DEFAULT_FLAG FL_RONLY

// include commands from BSB_lan_custom.h to be executed at the end of each main loop
//#define CUSTOM_COMMANDS

// Check for new versions when accessing BSB-LAN's main page
#define VERSION_CHECK
boolean enable_version_check = true;

//"External" web server. Read files from SD-card. Only static content: html, js, css, jpg, etc.
//#define WEBSERVER
// Configuration will be store in EEPROM
#define CONFIG_IN_EEPROM
// Compile web-based configuration and EEPROM config store module extension.
//#define WEBCONFIG

//Variables for future use:
//Compile room unit replacement extension
#define ROOM_UNIT
byte UdpIP[4] = {0,0,0,0}; //(destination IP address for sending UDP packets to, the room unit replacement of FHEM user @fabulous uses that)
uint16_t UdpDelay = 15; //(seconds interval to send UDP packets)

//Compile off-site logger extension
#define OFF_SITE_LOGGER
byte destinationServer[128] = ""; //URL string to periodically send values to an off-site logger
uint16_t destinationPort = 80; //port number for abovementioned server
uint32_t destinationDelay = 84600; //seconds interval to send values

//All modules are compiled on Duo by default.
#if ! defined(__AVR__)
#define CONFIG_IN_EEPROM
#define WEBCONFIG
#define AVERAGES
#define DEBUG
#define IPWE
#define MQTT
#define OFF_SITE_LOGGER
#define RESET
#define ROOM_UNIT
#define VERSION_CHECK
#define WEBCONFIG
#define WEBSERVER

#endif
/************************************************************************************/
/************************************************************************************/
/* Settings -   END                                                                 */
/************************************************************************************/
/************************************************************************************/
