/************************************************************************************/
/************************************************************************************/
/* Settings -   BEGIN                                                               */
/************************************************************************************/
/************************************************************************************/
/*
 * if defined the URL has to contain the defined passkey as first element
 * e.g.
 * http://192.168.1,50/1234/     - to view the help
 * http://192.168.1.50/1234/K    - to list all categories
*/

#define PASSKEY  "4444"

/* select your heating system (default may work for other systems) */

#define THISION
//#define FUJITSU          // for FUJITSU Wärmepumpe
//#define BROETJE_SOB
//#define PROGNR_5895      // if we know more about this command
//#define PROGNR_6030      // if we know more about this command

/*
 * Define the pin for one wire temperature sensors
*/
//#define ONE_WIRE_BUS 3

// Activate DHT temperature/humidity sensors
#define DHT_BUS 2,3

/*
 *  Enter a MAC address and IP address for your controller below.
 *  The IP address will be dependent on your local network:
*/
byte mac[] = { 0x64, 0x66, 0xB3, 0x2A, 0xA7, 0xC3 };

/*
 * Initialize the Ethernet server library
 * with the IP address and port you want to use
 * (port 80 is default for HTTP):
*/
IPAddress ip(192,168,1,50);
EthernetServer server(80);

// Software Serial needs special pins for RX: 10-13, 50-53, 62(A8)-69(A15)
// W5100 ethernet shield uses the following pins: 10, 50-53
BSB bus(68,69);

// Protect these pins from accidental GPIO access
byte exclude_GPIO[] = {10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69};

// EXPERIMENTAL:
// If defined, the heating burner ON time is accumulated using broadcast messages
// sent from the heating system.
#define USE_BROADCAST

// If set to 1, all messages on the bus are printed to the PC
// hardware serial interface
byte verbose = 0;
byte monitor = 0;

// Create 24h averages from these parameters
int avg_parameters[] = {
  8700,                   // Außentemperatur
  8326                    // Brenner-Modulation
};

// Activate IPWE extension (http://xxx.xxx.xxx.xxx/ipwe.cgi)
#define IPWE

// Parameters to be displayed in IPWE extension
int bsb_parameters[] = {
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

/************************************************************************************/
/************************************************************************************/
/* Settings -   END                                                                 */
/************************************************************************************/
/************************************************************************************/
