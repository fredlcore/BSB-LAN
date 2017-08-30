/************************************************************************************/
/************************************************************************************/
/* Settings -   BEGIN                                                               */
/************************************************************************************/
/************************************************************************************/

/*
 * Initialize the Ethernet server library
 * with the IP address and port you want to use
 * (port 80 is default for HTTP):
*/
IPAddress ip(192,168,178,88);
EthernetServer server(80);

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
 * http://192.168.1,50/1234/                - to view the main website (don't forget the trailing slash!)
 * http://192.168.1.50/1234/K               - to list all categories
 * http://192.168.1.50/1234/8700/8740/8741  - to list parameters 8700, 8740 and 8741 in one request
*/
//#define PASSKEY "1234"

/* activate IP-address-based access. Only the last segment of the client's IP address is matched, as it is assumed that
 * requests are made from the same subnet only. So if your trusted client's IP is 192.168.178.20, you have to set
 * TRUSTED_IP to 20. 
 * Configured for W5100-based Ethernet Shields. For W5500 types you have to search and replace w5100 with w5500 in the .ino source.
*/
//#define TRUSTED_IP 20

/* activate HTTP-Auth authentification to provide username/password based access. No encryption!
 * Default sets username to "atari" and password to "800xl". Visit a website like
 * https://www.base64encode.org/
 * to encode your own username/password combination in the format username:password
 * and replace the YXRhcmk6ODAweGw= string below accordingly.
*/
//#define USER_PASS_B64 "YXRhcmk6ODAweGw="

/* select your heating system (default may work for other systems)
 * Set fixed_device_id to your device family (parameter 6225) here if autodetect does not work or heating system is not running when Arduino is powered on
 * You may use other device family numbers to test commands from other heating systems at your own risk
*/
int fixed_device_id = 0;

/* display web interface in German language; remove definement for English */
#define LANG_DE

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

int log_parameters[20] = {
//  30000,                  // Logging von "rohen" Bus-Datentelegrammen (macht nur als alleiniger Parameter Sinn)
  8700,                   // Außentemperatur
  8743,                   // Vorlauftemperatur
  8314,                   // Rücklauftemperatur
//  20000,                  // Spezialparameter: Brenner-Laufzeit (/B)
//  20001,                  // Spezialparameter: Brenner-Takte (/B)
//  20002,                  // Spezialparameter: TWW-Laufzeit (/B)
//  20003,                  // Spezialparameter: TWW-Takte (/B)
//  20004,                  // Spezialparameter: 24h-Durchschnittswerte (/A)
//  20101,                  // Spezialparameter 20100-20099: DHT22-Sensoren 1-100 (/H)
//  20200                   // Spezialparameter 20200-20299: DS18B20-Sensoren 1-100 (/T)
};

unsigned long log_interval = 3600;    // logging interval in seconds
boolean log_unknown_only = 1;         // should we log only unknown commands when logging bus telegrams?
boolean log_bc_only = 0;              // should we log only broadcast commands (dest = 0x7f) when logging bus telegrams?

// Activate IPWE extension (http://xxx.xxx.xxx.xxx/ipwe.cgi)
#define IPWE

// Parameters to be displayed in IPWE extension
int ipwe_parameters[] = {
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

// defines the number of retries for the query command
#define QUERY_RETRIES  3

/* enable /X URL command to reset Arduino - might not work on older boards */
//#define RESET

/*
 *  Enter a MAC address, found either on the EthernetShield or use the one below.
*/
byte mac[] = { 0x00, 0x80, 0x41, 0x19, 0x69, 0x90 };

// Software Serial needs special pins for RX: 10-13, 50-53, 62(A8)-69(A15)
// W5100 ethernet shield uses the following pins: 10, 50-53
// use BSB bus(68,69,7) to define device as RGT2
BSB bus(68,69);
uint8_t bus_type = bus.setBusType(0);  // 0 = BSB, 1 = LPB

// Protect these pins from accidental GPIO access
byte exclude_GPIO[] = {10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69};

// If set to 1, all messages on the bus are printed to the PC
// hardware serial interface
byte verbose = 0;
byte monitor = 0;

// defines default flag for parameters (use "#define DEFAULT_FLAG 0" to make (almost) all parameters writeable)
#define DEFAULT_FLAG FL_RONLY

/************************************************************************************/
/************************************************************************************/
/* Settings -   END                                                                 */
/************************************************************************************/
/************************************************************************************/
