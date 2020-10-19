/************************************************************************************/
/************************************************************************************/
/* Settings -   BEGIN                                                               */
/************************************************************************************/
/************************************************************************************/

// Upon first installation, rename this file from BSB_lan_config.h.default to BSB_lan_config.h and adjust settings accordingly

/*
 * Initialize the Ethernet server library
 * with the IP address and port you want to use
 * (port 80 is default for HTTP):
*/

#define Port 80
#define IPAddr 192,168,178,88   // please note the commas instead of dots!!! Remove this line when you want DHCP
//#define GatewayIP 192,168,178,1 // Optional: this is usually your router's IP address. Please note the commas instead of dots!!!
//#define DNSIP 192,168,178,1 // Only set this variable if your DNS server is different from your router's IP address (GatewayIP). Please note the commas instead of dots!!!
//#define SubnetIP 255,255,255,0  // Please use commas instead of dots!!!

/* Select language; so far German is the most complete, with English following.
 * Available languages are: Czech (CS), German (DE), Danish (DA), English (EN), Spanish (ES), Finnish (FI),
 * French (FR), Greek (EL), Hungarian (HU), Italian (IT), Dutch (NL), Polish (PL), Russian (RU), Swedish (SV),
 * Slovenian (SI) and Turkish (TR).
 * Incomplete languages will automatically be filled up with English translations first, and if no English translation
 * is available, fallback will take place to German.
*/
#define LANG DE

/* SECURITY OPTIONS
 * There are several options to control and protect access to your heating system. However, keep
 * in mind, that even activating all three options are no guarantee that a versatile intruder with
 * access to your (W)LAN won't be able to gain access. In any case, no encryption of data streams
 * is provided from the Arduino itself. Use VPN or a SSL proxy if that is a must for you and connect
 * the Arduino wired to the VPN server or SSL proxy. On the other hand, someone with this amount
 * of criminal activity will probably have it easier just to access your heating system face-to-face ;)
*/

/*
 * if PASSKEY is defined, the URL has to contain the defined passkey as first element
 * e.g.
 * http://192.168.178.88/1234/                - to view the main website (don't forget the trailing slash!)
 * http://192.168.178.88/1234/K               - to list all categories
 * http://192.168.178.88/1234/8700/8740/8741  - to list parameters 8700, 8740 and 8741 in one request
*/
//#define PASSKEY "1234"

/* activate IP-address-based access. Only the last segment of the client's IP address is matched, as it is assumed that
 * requests are made from the same subnet only. So if your trusted client's IP is 192.168.178.20, you have to set
 * TRUSTED_IP to 20.
*/
//#define TRUSTED_IP 20
//#define TRUSTED_IP2 30

/* activate HTTP-Auth authentication to provide username/password based access. No encryption!
 * Default sets username to "atari" and password to "800xl". Visit a website like
 * https://www.base64encode.org/
 * to encode your own username/password combination in the format username:password
 * and replace the YXRhcmk6ODAweGw= string below accordingly.
*/
//#define USER_PASS_B64 "YXRhcmk6ODAweGw="

/* select your heating system (default may work for other systems)
 * Set fixed_device_family and fixed_device_variant to your device family and variant (parameters 6225 and 6226) here
 * if auto-detect does not work or heating system is not running when Arduino is powered on
 * You may use other device family numbers to test commands from other heating systems at your own risk
*/
static const int fixed_device_family = 0;
static const int fixed_device_variant = 0;

// Hide unknown parameters from web display (parameters will still be queried!)
//#define HIDE_UNKNOWN

/*
 * Define the pin for one wire temperature sensors
*/
//#define ONE_WIRE_BUS 3

// Define the pins for DHT temperature/humidity sensors
//#define DHT_BUS 2,3

// Create 24h averages from these parameters
int avg_parameters[20] = {
  8700,                   // Außentemperatur
  8326                    // Brenner-Modulation
};

/* activate logging on SD-card. Requires a FAT32-formatted Micro-SD card inserted into the Ethernet-Shield's card slot */
#define LOGGER
// Logging von "rohen" Bus-Datentelegrammen
// Telegrams logging. False - disabled on start, true - enabled on start.
#define LOGTELEGRAM false
// You can enable logging with URL /LE command or disable it with /LD command when run time.
// Data will be write to "journal.txt"
boolean log_unknown_only = 1;         // should we log only unknown commands when logging bus telegrams?
boolean log_bc_only = 0;              // should we log only broadcast commands (dest = 0x7f) when logging bus telegrams?


// Logging data from parameters
// Interval and list of parameters can be redefined through /L command when run time
// Data will be write to "datalog.txt"
int log_parameters[20] = {
  8700,                   // Außentemperatur
  8743,                   // Vorlauftemperatur
  8314,                   // Rücklauftemperatur
//  20000,                  // Spezialparameter: Brenner-Laufzeit Stufe 1(/B)
//  20001,                  // Spezialparameter: Brenner-Takte Stufe 1 (/B)
//  20002,                  // Spezialparameter: Brenner-Laufzeit Stufe 2(/B)
//  20003,                  // Spezialparameter: Brenner-Takte Stufe 2 (/B)
//  20004,                  // Spezialparameter: TWW-Laufzeit (/B)
//  20005,                  // Spezialparameter: TWW-Takte (/B)
//  20006,                  // Spezialparameter: 24h-Durchschnittswerte (/A)
//  20101,                  // Spezialparameter 20100-20199: DHT22-Sensoren 1-100 (/T)
//  20200                   // Spezialparameter 20200-20299: DS18B20-Sensoren 1-100 (/T)
};
unsigned long log_interval = 3600;    // logging interval in seconds

// Activate sending log_parameters to MQTT broker every log_interval seconds
//#define MQTTBrokerIP 192,168,1,20	// Please use commas instead of dots!!!
//#define MQTTUsername "User" // Set username for MQTT broker here or comment out if no username/password is used.
//#define MQTTPassword "Pass" // Set password for MQTT broker here or comment out if no password is used.
//#define MQTTTopicPrefix "BSB-LAN" 	// Optional: Choose the "topic" for MQTT messages here
//#define MQTT_JSON 					// Optional: Use this if you want a json package of your logging information printed to the mqtt topic
//#define MQTTDeviceID "MyHeater"	// Optional: Define a device name to use as header in json payload. If not defined, BSB-LAN will be used.
// Payload will be of the structure: {"MQTTDeviceID": {"status":{"log_param1":"value1","log_param2":"value2"}, ...}}


// Activate IPWE extension (http://xxx.xxx.xxx.xxx/ipwe.cgi)
#define IPWE

// Parameters to be displayed in IPWE extension
const int ipwe_parameters[] = {
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

//#define MAX_CUL 192,168,178,5                  // IP of CUNO/CUNX/modified MAX!Cube

const char max_device_list[] PROGMEM = {        // list of MAX! wall/heating thermostats that should be polled
  "KEQ0502326"                                  // use MAX! serial numbers here which have to have exactly 10 characters
  "KEQ0505080"
};

// defines the number of retries for the query command
#define QUERY_RETRIES  3

/* enable /N URL command to reset Arduino - might not work on older boards */
//#define RESET

/*
 *  Enter a MAC address, found either on the EthernetShield or use the one below.
*/
static byte mac[] = { 0x00, 0x80, 0x41, 0x19, 0x69, 0x90 };

// Setting bus pins and bus type
// Bus bus (RX pin, TX pin, parameter 3, parameter 4)
// Hardware Serial is always pin 19 (RX) and pin 18 (TX). On the Arduino Due this is the only way to connect to the bus.
// Software Serial needs special pins for RX (68) and TX (69); this is now deprecated and should only be used on older installations running on the Arduino Mega.
// BSB:
// - optional third parameter sets own address, defaults to 0x42 (LAN in serial monitor)
// - use BSB bus(68,69,6) to define device as RGT1
// LPB:
// - optional third and fourth parameter set own and destination address (high nibble = segment, low nibble = device minus 1)
// - defaults to 0x42 for own address and 0x00 for destination address, i.e. segment 4, device 3 for Arduino/BSB-LAN and segment 0, device 1 for heating system
// PPS:
// - optional third parameter set to "1" enables writing to heater - only use this if there is no other room controller (such as QAA50/QAA70) active. Fourth parameter does not have any effect.
BSB bus(19,18); // BSB bus(68,69); // pin 68,69 = SoftwareSerial
constexpr uint8_t bus_type = 0;  // set bus system at boot: 0 = BSB, 1 = LPB, 2 = PPS
//#define QAA_TYPE  0x53  // 0x53 = QAA70, 0x52 = QAA50

// Protect these pins from accidental GPIO access
constexpr byte exclude_GPIO[] = {0, 1, 4, 10, 11, 12, 13, 18, 19, 20, 21, 22, 23, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69};

// If set to 1, all messages on the bus are printed to the PC
// hardware serial interface
byte verbose = 1;
byte monitor = 0;

// defines default flag for parameters (use "#define DEFAULT_FLAG 0" to make (almost) all parameters writeable)
#define DEFAULT_FLAG FL_RONLY

// include commands from BSB_lan_custom.h to be executed at the end of each main loop
//#define CUSTOM_COMMANDS

// Check for new versions when accessing BSB-LAN's main page
#define VERSION_CHECK 1

//#define DEBUG
//#define DebugTelnet 1   // Uncomment this to send debug messages to telnet client instead of serial port

//"External" web server. Read files from SD-card. Only static content: html, js, css, jpg, etc.
//#define WEBSERVER

/************************************************************************************/
/************************************************************************************/
/* Settings -   END                                                                 */
/************************************************************************************/
/************************************************************************************/
