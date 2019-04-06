char version[] = "0.42";

/*
 * 
 * BSB Boiler-System-Bus LAN Interface
 *
 * ATTENION:
 *       There is no waranty that this system will not damage your heating system!
 *
 * Authors Gero Schumacher (gero.schumacher@gmail.com) (up to version 0.16)
 *         Frederik Holst (bsb@code-it.de) (from version 0.17 onwards)
 *         (based on the code and work from many other developers. Many thanks!)
 *
 * see README and HOWTO files for more information
 *
 * Version:
 *       0.1  - 21.01.2015 - initial version
 *       0.5  - 02.02.2015
 *       0.6  - 02.02.2015
 *       0.7  - 06.02.2015
 *       0.8  - 05.03.2015
 *       0.9  - 09.03.2015
 *       0.10  - 15.03.2015
 *       0.11  - 07.04.2015
 *       0.12  - 09.04.2015
 *       0.13  - 31.03.2016
 *       0.14  - 04.04.2016
 *       0.15  - 21.04.2016
 *       0.15a - 25.07.2016
 *       0.16  - 20.11.2016
 *       0.17  - 20.12.2016
 *       0.17a - 20.12.2016
 *       0.18  - 22.12.2016
 *       0.19  - 01.01.2017
 *       0.20  - 27.01.2017
 *       0.21  - 06.02.2017
 *       0.22  - 07.02.2017
 *       0.23  - 12.02.2017
 *       0.24  - 14.02.2017
 *       0.25  - 21.02.20172
 *       0.26  - 27.02.2017
 *       0.27  - 01.03.2017
 *       0.28  - 05.03.2017
 *       0.29  - 07.03.2017
 *       0.30  - 22.03.2017
 *       0.31  - 10.04.2017
 *       0.32  - 18.04.2017
 *       0.33  - 09.05.2017
 *       0.34  - 29.05.2017
 *       0.35  - 25.06.2017
 *       0.36  - 23.08.2017
 *       0.37  - 08.09.2017
 *       0.38  - 22.11.2017
 *       0.39  - 02.01.2018
 *       0.40  - 21.01.2018
 *       0.41  - 17.03.2019
 *       0.42  - 21.03.2019
 *       0.43  - 02.04.2019
 *
 * Changelog:
 *       version 0.43
 *        - Moved all sensors to /T , /H is now no longer used
 *        - New virtual parameters 702/703 for Weishaupt room controller
 *        - New data types VT_CUSTOM_ENUM and VT_CUSTOM_BYTE to extract information from non-standard telegrams (such as 702/703)
 *        - Added text descriptions for error phases (6706 ff.)
 *       version 0.42
 *        - Added localization! Now you can help translate BSB-LAN into your language! Simply copy one of the language files from the localization folder (LANG_DE.h is the most complete) and translate whatever you can. Non-translated items will be displayed in German.
 *          Attention: Language definition in BSB_lan_config.h is now #define LANG <ISO-CODE> 
 *          For example: #define LANG DE
 *        - Added export to MQTT broker, use log_parameters[] in BSB_lan_config.h to define parameters and activate MQTTBrokerIP definement.
 *        - Added support for WiFi modules such as an ESP8266 or a Wemos Mega connected to Serial3 (RX:15/TX:14) of the Arduino. 
 *          The ESP8266 has to be flashed with the AT firmware from Espressif to work.
 *          Please take note that WiFi over serial is by design much slower (only 115kpbs) than "pure" TCP/IP connections.
 *        - Added new category "34 - Konfiguration / Erweiterungsmodule". All subsequent categories move one number up!
 *        - Lots of new parameters coming from device family 123, please run /Q to see if some parameters also work for your heater!
 *        - Lots of new yet unknown parameters through brute force querying :) (parameter numbers 10200 and above)
 *        - Added further PPS-Bus commands, moved parameter numbers to 15000 and above
 *        - Default PPS mode now "listening". 
 *          Use third parameter of bus definition to switch between listening and controlling, 1 stands for controlling, everything else for listening, 
 *          i.e. BSB bus(68,67,1) sends data to the heater, BSB bus(68,67) only receives data from heater / room controller.
 *          You can switch between modes at run-time with URL command /P2,x where x is either 1 (for controlling) or not 1 (for listening only)
 *        - Fixed bug that crashed PPS bus queries
 *        - Stability improvements for PPS bus
 *        - Improved graph legend when plotting several parameters
 *        - Added JSON export; query with /JQ=a,b,c,d... or push queries to /JQ or push set commands to /JS
 *        - Logging of MAX! parameters now possible with logging parameter 20007
 *        - Added Waterstage WP device family (119)
 *        - Added WHG Procon device family (195)
 *        - Added unit to log file as well as average output
 *        - Rewrote device matching in cmd_tbl to accomodate also device variant (Gerätevariante). Run /Q to see if transition has worked for your device!
 *        - Added BSB_lan_custom_setup.h and BSB_lan_custom_global.h for you to add individual code (best used in conjunction with BSB_lan_custom.h)
 *        - Marked all (known) OEM parameters with flag FL_OEM. OEM parameters are set by default as read-only. To make them writeable, change FL_OEM from 5 to 4 in BSB_lan_defs.h
 *        - Increased performance for querying several parameters at once (similar to category query)
 *        - Added config option to define subnet.
 *        - /Q no longer needs #define DEBUG
 *        - Bugfix ENUM memory adressing
 *        - Bugfix in reset function (/N), clear EEPROM during reset with /NE
 *        - Added favicon.ico
 *        - Split of cmdtbl into cmdtbl1 and cmdtbl2 due to Arduino's(?) limit of 32kB size of struct, opening up more space for new parameters.
 *       version 0.41
 *        - Interim release containing all changes from 0.42 above, except locaization, i.e. all text fragments are still part of the main code.
 *       version 0.40
 *        - Implemented polling of MAX! heating thermostats, display with URL command /X.
 *          See BSB_lan_custom.h for an example to transmit average room temperature to heating system.
 *        - Added new category "22 - Energiezähler" - please note that all subsequent categories move one up!
 *        - New virtual parameter 1601 (manual TWW push)
 *        - Added Fujitsu Waterstage WSYP100DG6 device family (211)
 *        - Added CTC device family (103)
 *        - New definement "#define TRUSTED_IP2" to grant access to a second local IP address
 *        - Added optional definement "#define GatewayIP" in BSB_lan_config.h to enable setting router address different from x.x.x.1
 *        - Removed parameter 10109 because it is the same as 10000
 *        - Added function to check all known CommandIDs on your own heating system. Use /Q after enabling definement "#define DEBUG" in BSB_lan_config.h
 *        - Added parameter numbers to category menu
 *        - Updated analyze.sh
 *        - hopefully fixing the memory issue
 *        - Moved HTML strings to html_strings.h
 *       version 0.39
 *        - Implemntation of PPS-Bus protocol. 
 *          See /K40 for the limited commands available for this bus. 
 *          Use setBusType(2) to set to PPS upon boot or /P2 to switch temporarily.
 *        - Set GPIOs to input by using /Gxx,I
 *        - Definement "#define CUSTOM_COMMANDS" added. 
 *          Use this in your configuration to include individual code from "BSB_lan_custom.h"
 *          (needs to be created by you!) which is executed at the end of each main loop.
 *          Variables "custom_timer" and "custom_timer_compare" have been added to execute
 *          code at arbitrary intervals.
 *        - Added LogoBloc Unit L-UB 25C device family (95)
 *        - several new parameters added
 *        - Bugfix for logging Brennerlaufzeit Stufe 2
 *       version 0.38
 *        - ATTENTION: New BSB_lan_config.h configurations! You need to adjust your configuration when upgrading to this version!
 *          Webserver port is now defined in #define Port xx
 *          IP address is now defined in #define IPAddr 88,88,88,88 form - note the commas instead of dots!
 *          Special log parameters 20002 to 20006 have changed, see BSB_lan_config.h for their new meaning
 *        - Added new virtual parameter 701 (Präsenztaste) which enters reduced temperature mode until next timed switch
 *        - Added Brötje BOB device family (138), including many new parameters!
 *        - Added Brötje SOB26 device family (28)
 *        - Added Elco Aquatop 8es device family (85)
 *        - Added Elco Thision 13 Plus device family (203)
 *        - Added Weishaupt WTU 25-G familiy (50)
 *        - Added output for absolute humidity (g/m3) for DHT22 sensors
 *        - New schematics for Arduino/Raspberry board layout
 *        - Included support for W5500 Ethernet2 shields. Activate definement ETHERNET_W5500 in BSB_lan_config.h
 *        - Including two-stage oil furnaces BC-counters and logging - please note that logging parameters have been adjusted, see BSB_lan_config.h for new values!
 *        - Added new options for commands /P and /S to allow specifying a different destination device during runtime
 *        - Added new configuration definement CUSTOM_COMMANDS which includes BSB_lan_custom.h at the end of each main loop. You may use custom_timer (set to current millis()) and custom_timer_compare to execute only every x milliseconds.
 *        - Bugfixing SD-card logging in monitor mode
 *        - Bugfix for setting hour:time parameters via webinterface 
 *       version 0.37
 *        - LPB implementation! More than 450 parameters supported! Switch temporarily between LPB and BSB with the Px command (0=BSB, 1=LPB) or use the setBusType config option to set bus-type at boot-time. Parameter numbers are the same as for BSB.
 *       version 0.36
 *        - bugfix: brought back VT_BIT list of options which were erroneously deleted :(, fixed/freed several memory issues
 *       version 0.35
 *        - new category "Sitherm Pro"; caution: category numbers all move up by one, starting from category "Wärmepumpe" (from 20 to 21) onwards.
 *        - graph display of logging data now comes with crosshair and shows detailed values as tooltip
 *        - improved SD-card output by factor 3 (from 16 to 45 kbps), switching SD-card library from from SD.h to SdFat.h (https://github.com/greiman/SdFat) brings another 10% performance boost
 *        - adjusted paths and directory layout of SdFat to enable compiling from sketch directory.
 *        - new data type vt_sint for signed int data, currently only used in some Sitherm Pro parameters
 *       version 0.34
 *        - Log data can now be displayed as graph
 *        - Webinterface can now display and set vt_bit type parameters in human-readable form
 *        - added KonfigRGx descriptions; caution: various sources used, no guarantee that descriptions match your individual heating system!
 *        - vt_bit is generally read-only in the webinterface. To set, use URL command /S with decimal representation of value
 *        - fixed a bug with vt_seconds_short5, affecting parameters 9500 and 9540.
 *        - fixed bug regarding Fujitsu's device family (from 127 to 170)
 *        - moved libraries from folder libraries to src so they can be included without copying them to the Arduino libraries folder
 *        - modified DallasTemperature.h's include path for OneWire.h
 *       version 0.33
 *        - no more heating system definements anymore due to new autodetect function based on device family (parameter 6225), or set device_id variable to parameter value directly
 *        - two more security options: TRUSTED_IP to limit access to one IP address only, and HTTP authentication with username and password
 *        - Average values are saved on SD-card if present and LOGGER definement is activated
 *        - deactivate logging by setting /L0=0 - this way you can enable LOGGER definement without filling up SD card but still save average values
 *        - new error codes for THISION
 *        - added dump of data payload on website for commands of unknown type, greyed out unsopported parameters
 *        - enable logging of telegrams (log parameter 30000) also in monitor mode (bsb.cpp and bsb.h updated)
 *        - time from heating system is now retreived periodically from broadcast telegrams, further reducing bus activity
 *        - new data type vt_bit for parameters that set individual bits. Display as binary digits, setting still using decimal representation
 *        - new data type vt_temp_short5_us for unsigned one byte temperatures divided by 2 (so far only 887 Vorlaufsoll NormAussentemp)
 *        - new data type vt_percent5 for unsigned one byte temperatures divided by 2 (so far only 885 Pumpe-PWM Minimum)
 *        - new data type vt_seconds_word5 for two byte seconds divided by 2 (so far only 2232, 9500 and 9540)
 *        - new data type vt_seconds_short4 for (signed?) one byte seconds divided by 4 (so far only 2235)
 *        - new data type vt_seconds_short5 for (signed?) one byte seconds divided by 5 (so far only 9500, 9540)
 *        - new data type vt_speed2 for two byte rpm (so far only 7050)
 *        - cleaned up set() function from apparent duplicate cases
 *        - added cases for vt_temp_word, vt_seconds_word5, vt_temp_short, vt_temp_short5, vt_seconds_short4 to set() function
 *       version 0.32
 *        - lots of new parameters suppoerted
 *        - newly designed webinterface allows control over heating system without any additional software or cryptic URL commands. URL commands of course are still available, so no need to change anything when using FHEM etc.
 *        - German webinterface available with definement LANG_DE
 *        - new URL-command /LB=x to log only broadcast messages (x=1) or all bus messages (x=0)
 *        - new URL-command /X to reset the Arduino (need to enable RESET definement in BSB_lan_config.h)
 *        - new logging parameters 20002 and 20003 for hot water loading times and cycles
 *        - moved DS18B20 logging parameters from 20010-20019 to 20200-20299 and DHT22 logging parameters from 20020-20029 to 20100 to 20199
 *        - moved average logging parameter from 20002 to 20004
 *        - set numerous parameters to read-only because that's what they obviously are (K33-36)
 *        - various bugfixes
 *       version 0.31
 *        - increased dumping of logfile by factor 5 / as long as we still have memory left, you can increase logbuflen from 100 to 1000 to increase transfer speed from approx. 16 to 18 kB/s
 *        - adjusted burner activity monitoring based on broadcast messages for Brötje systems
 *        - removed definement PROGNR_5895 because so far, it has only disabled an ENUM definition.
 *        - removed definement PROGNR_6030 because double command ID could be resolved via BROETJE / non-BROETJE definements
 *        - renamed BROETJE_SOB to BROETJE in order to allow for fine-grained distinction between different BROETJE cases (e.g. 6800ff)
 *          This means you have to activate TWO definements when using a Brötje system now: The general BROETJE as well as BROETJE_SOB or BROETJE_BSW.
 *          Have a look at your serial log for parameters 6800 to see which command IDs fit your system and activate one of both accordingly.
 *        - changed 16-Bit addressing of flash memory to 32-Bit to address crashes due to ever growing PROGMEM tables - now we have lots of air to breathe again for new command IDs :)
 *        - removed trailing \0 string from several ENUMs that led to wrong ENUM listings. Please keep in mind not to end ENUMs with a trailing \0 !
 *       version 0.30
 *        - Time library by Paul Stoffregen (https://github.com/PaulStoffregen/Time) is now required and included in the library folder.
 *        - adds logging of raw telegram data to SD card with logging parameter 30000. Logging telegram data is affected by commands /V and /LU
 *        - adds command /LU=x to log only known (x=0) or unknown (x=1) command IDs when logging telegram data
 *        - removed define USE_BROADCAST, broadcast data is now always processed
 *        - new internal functions GetDateTime, TranslateAddr, TranslateType
 *       version 0.29
 *        - adds command /C to display current configuration
 *        - adds command /L to configure logging interval and parameters
 *        - adds option for command /A to set 24h average parameters during runtime
 *        - adds special parameter 20002 for logging /A command (24h averages, only makes sense for long logging intervals)
 *        - bugfixes for logging DS18B20 sensors
 *       version 0.28
 *        - adds special parameters 20000++ for SD card logging of /B, /T and /H commands (see BSB_lan_config.h for examples)
 *        - adds version info to BSB_LAN web interface
 *       version 0.27
 *        - adds date field to log file (requires exact time to be sent by heating system)
 *        - /D0 recreates datalog.txt file with table header
 *        - added "flags" field to command table structure. Currently, only FL_RONLY is supported to make a parameter read-only
 *        - added DEFAULT_FLAG in config. Defaults to NULL, i.e. all fields are read/writeable. 
 *          Setting it to FL_RONLY makes all parameters read-only, e.g. for added level of security. 
 *          Individual parameters can be set to NULL/FL_RONLY to make only these parameters writable/read-only.
 *       version 0.26
 *        - added functionality for logging on micro SD card, using the slot of the w5100 Ethernet shield
 *        - more parameters added (e.g. 8009)
 *       version 0.25
 *        - more FUJITSU parameters added
 *       version 0.24
 *        - updated README with added functions
 *        - added German translations of FAQ and README, courtesy of Ulf Dieckmann
 *       version 0.23
 *        - minor bugfix
 *       version 0.22
 *        - more FUJITSU parameters
 *        - (hopefully) correct implementation of VT_VOLTAGE readings
 *        - minor bugfixes
 *       version 0.21
 *        - added numerous parameters for Fujitsu Wärmepumpe, including new #define FUJITSU directive to activate these parameters due to different parameter numbers
 *        - minor bugfixes
 *       version 0.20
 *        - added more parameters for Feststoffkessel
 *        - minor bugfixes
 *       version 0.19
 *        - added humidity command "H", currently for DHT22 sensors
 *        - added 24h average command "A", define parameters in BSB_lan_config.h
 *        - removed trailing whitespace from menu strings
 *        - fixed command id 0x053D04A2 for THISION heaters
 *        - included Rob Tillaart's DHT library because there are various libraries implementing the protocol and this one is used in the code for its ability to address multiple sensors with one object.
 *        - removed /temp URL parameter as it is a duplicate of /T
 *        - included loop to display DHT22 sensors in IPWE
 *        - making compiling IPWE extensions optional (#define IPWE)
 *       version 0.18
 *        - split off configuration into bsb_lan_config.h
 *        - split off command definitions into bsb_lan_defs.h
 *        - changed GPIO return values from LOW/HIGH to 1/0
 *        - reactivated and updated IPWE (define parameters in config)
 *        - check for protected pins when accessing GPIO (define in config)
 *        - added schematics and PCB files to new subfolder "schematics"
 *       version 0.17a
 *        - minor errors corrected
 *       version 0.17
 *	      - merged v0.16 with FHEM user miwi's changes 
 *       version 0.16
 *        - removed IPWE and EthRly interface
 *        - added GPIO interface
 *        - merged parameters from J.Weber
 *        - resolved duplicate command IDs
 *       version 0.15a
 *        - collated the commands from a Python project and this project,
 *          merged the two versions, corrected obvious errors.
 *          Inserted hypothetical numerical values in ENUM definitions
 *          where Broetje manuals documented only the message texts.
 *        - added information from traces in a Broetje installation with
 *          an ISR-SSR controller and a WOB 25C oil furnace.
 *       version 0.15
 *        - added Solar and Pufferspeicher from Elco Logon B & Logon B MM
 *       version 0.14
 *        - minor bugfixes for Broetje SOB
 *        - extended broadcast handling (experimental)
 *       version 0.13
 *        - change resistor value in receiving path from 4k7 to 1k5
 *        - added values 0x0f and 0x10 to Enum8005
 *        - fixed strings for Zeitprogramme
 *        - added timeout for sending a message (1 second)
 *        - added option T for querying one wire temperature sensors in mixed querys
 *        - added special handling for Broetje SOB
 *        - simplified settings
 *       version 0.12
 *        - added ONEWIRE_SENSORS to ipwe
 *        - fixed parameter decoding for ELCO Thision heating system
 *       version 0.11
 *        - fixed parameter decoding for ELCO Thision heating system
 *       version 0.10
 *        - added more parameters for ELCO Thision heating system
 *       version 0.9
 *        - added more parameters for ELCO Thision heating system
 *        - printTelegramm returns value string for further processing
 *       version 0.8
 *        - added parameters for ELCO Thision heating system
 *        - added IPWE extension
 *        - minor bugfixes
 *       version 0.7
 *        - added bus monitor functionality
 *       version 0.6
 *        - renamed SoftwareSerial to BSBSoftwareSerial
 *        - changed folder structure to enable simple build with arduino sdk
 *       version 0.5
 *        - bugfixes
 *        - added documentation (README)
 *        - added passkey feature
 *        - added R feature (query reset value)
 *        - added E feature (list enum values)
 *        - added setter for almost all value types
 *        - fixed indentation
 *        - added V feature to set verbosity for serial output
 *        - set baudrate to 115200 for serial output
 *        - redirecting favicon request
 *        - added some images of the BSB adapter
 *
 */

#include "src/BSB/BSBSoftwareSerial.h"
#include "src/BSB/bsb.h"
#include "BSB_lan_config.h"
#include "BSB_lan_defs.h"

#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>
#include <util/crc16.h>
#include "src/Time/TimeLib.h"
#include "src/PubSubClient/src/PubSubClient.h"
#include "html_strings.h"

#include <Ethernet.h>
#ifdef WIFI
#include "src/WiFiEsp/src/WiFiEsp.h"
#endif

#ifdef IPAddr
IPAddress ip(IPAddr);
#endif
#ifdef WIFI
WiFiEspServer server(Port);
#else
EthernetServer server(Port);
#endif
#ifdef GatewayIP
IPAddress gateway(GatewayIP);
#endif
#ifdef SubnetIP
IPAddress subnet(SubnetIP);
#endif
#ifdef MQTTBrokerIP
IPAddress MQTTBroker(MQTTBrokerIP);
#endif
uint8_t len_idx, pl_start;
uint8_t myAddr = bus.getBusAddr();
uint8_t* PPS_write_enabled = &myAddr;
uint8_t destAddr = bus.getBusDest();

/* buffer to load PROGMEM values in RAM */
#define BUFLEN 100
char buffer[BUFLEN] = { 0 };

/* buffer to print output lines*/
#define OUTBUF_LEN  300
char outBuf[OUTBUF_LEN] = { 0 };
byte outBufLen=0;

char div_unit[10];

#ifdef WIFI
WiFiEspClient client;
#else
EthernetClient client;
#endif

#ifdef WIFI
WiFiEspClient max_cul;
#else
EthernetClient max_cul;
#endif

PubSubClient MQTTClient(client);

#ifdef MAX_CUL
uint16_t max_cur_temp[20] = { 0 };
uint8_t max_dst_temp[20] = { 0 };
int8_t max_valve[20] = { -1 , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int32_t max_devices[20] = { 0 };
#endif
/*
int16_t json_parameters[20] = { -1 , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
double json_values[20] = { 0 };
uint8_t json_types[20] = { 0 }; 
*/

// char _ipstr[INET6_ADDRSTRLEN];    // addr in format xxx.yyy.zzz.aaa
// char _ipstr[20];    // addr in format xxx.yyy.zzz.aaa
// byte __remoteIP[4] = {0,0,0,0};   // IP address in bin format  

#ifdef LOGGER
//  #include <SD.h>   // if you run into troubles with SdFat.h, just remove the following two lines and uncomment this line.
  #include "src/SdFat/SdFat.h"
  SdFat SD;
  File Logfile;
#endif

#ifdef ONE_WIRE_BUS
  #include "src/OneWire/OneWire.h"
  #include "src/DallasTemperature/DallasTemperature.h"
  #define TEMPERATURE_PRECISION 9
  // Setup a oneWire instance to communicate with any OneWire devices
  OneWire oneWire(ONE_WIRE_BUS);
  // Pass our oneWire reference to Dallas Temperature.
  DallasTemperature sensors(&oneWire);

  int numSensors;
#endif

#ifdef DHT_BUS
  #include "src/DHT/dht.h"
  int DHT_Pins[] = {DHT_BUS};
  dht DHT;
#endif

char date[20];

unsigned long lastAvgTime = millis();
unsigned long lastLogTime = millis();
unsigned long lastMQTTTime = millis();
unsigned long custom_timer = millis();
unsigned long custom_timer_compare = 0;
int numAverages = sizeof(avg_parameters) / sizeof(int);
int anz_ex_gpio = sizeof(exclude_GPIO) / sizeof(byte);
int numLogValues = sizeof(log_parameters) / sizeof(int);
double *avgValues = new double[numAverages];
double *avgValues_Old = new double[numAverages];
double *avgValues_Current = new double[numAverages];
int avgCounter = 1;
int loopCount = 0;

// uint_farptr_t enumstr_offset = 0;

uint8_t my_dev_fam = 0;
uint8_t my_dev_var = 0;

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
uint16_t pps_values[PPS_ANZ] = { 0 };
boolean time_set = false;
uint8_t current_switchday = 0;

#include "BSB_lan_custom_global.h"

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
    Serial.print(F("Socket#"));
    Serial.print(i);
    SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
    uint8_t s = W5100.readSnSR(i);
    SPI.endTransaction();
    socketStat[i] = s;
    Serial.print(F(":0x"));
    Serial.print(s,16);
    Serial.print(F(" "));
    Serial.print(W5100.readSnPORT(i));
    Serial.print(F(" D:"));
    uint8_t dip[4];
    SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
    W5100.readSnDIPR(i, dip);
    SPI.endTransaction();
    for (int j=0; j<4; j++) {
      Serial.print(dip[j],10);
      if (j<3) Serial.print(".");
    }
    Serial.print(F("("));
    SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
    Serial.print(W5100.readSnDPORT(i));
    SPI.endTransaction();
    Serial.println(F(")"));
  }
}

void checkSockStatus()
{
  unsigned long thisTime = millis();

  for (int i = 0; i < MAX_SOCK_NUM; i++) {
    SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
    uint8_t s = W5100.readSnSR(i);
    SPI.endTransaction();

    if((s == 0x14) || (s == 0x1C)) {
        if(thisTime - connectTime[i] > 30000UL) {
          Serial.print(F("\r\nSocket frozen: "));
          Serial.println(i);

          SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
          W5100.execCmdSn(s, Sock_DISCON);
          SPI.endTransaction();

          Serial.println(F("Socket freed."));
          ShowSockStatus();
        }
    }
    else connectTime[i] = thisTime;

    SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
    socketStat[i] = W5100.readSnSR(i);
    SPI.endTransaction();
  }
}

#endif

/** *****************************************************************
 *  Function: calc_enum_offset()
 *  Does:     Takes the 16-Bit char pointer and calculate (or rather estimate) the address in PROGMEM beyond 64kB
 * Pass parameters:
 *  enum_addr
 * Parameters passed back:
 *  enum_addr
 * Function value returned:
 *  24 bit char pointer address
 * Global resources used:
 *  enumstr_offset
 * *************************************************************** */
uint_farptr_t calc_enum_offset(uint_farptr_t enum_addr, uint16_t enumstr_len) {

  uint_farptr_t page = 0x10000;
  while (page < 0x40000) {
    uint8_t second_char = pgm_read_byte_far(enum_addr + page + 1);
    uint8_t third_char = pgm_read_byte_far(enum_addr + page + 2);
    uint8_t last_char = pgm_read_byte_far(enum_addr + page + enumstr_len-1);
    
    if ((second_char == 0x20 || third_char == 0x20) && (last_char == 0x00)) {
      break;
    }
    page = page + 0x10000;
  }

  enum_addr = enum_addr + page;

/*
  enum_addr = enum_addr & 0xFFFF;     // no longer relevant as strings are currently no longer stored as uint_farptr_t but char pointer)
  if (enum_addr < enumstr_offset) {   // if address is smaller than lowest enum address, then a new page needs to be addressed
    enum_addr = enum_addr + 0x10000;  // therefore add 0x10000 - will only work for a maximum of 128kB, but that should suffice here
  }
  enum_addr = enum_addr + enum_page;  // add enum_offset as calculated during setup()
*/
  return enum_addr;
}

/**  ****************************************************************
 *  Function: outBufclear()
 *  Does:     Sets ouBufLen = 0 and puts the end-of-string character
 *            into the first buffer position.
 *  Pass parameters:
 *   none
 *  Parameters passed back:
 *   none
 *  Function value returned:
 *   none
 * Global resources used:
 *   char outBuf[]
 * *************************************************************** */
void outBufclear(void){
  outBufLen=0;
  outBuf[0]='\0';
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

uint32_t get_cmdtbl_cmd(int i) {
  uint32_t c = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  if (i < entries1) {
//  c=pgm_read_dword(&cmdtbl[i].cmd);  // command code
    c = pgm_read_dword_far(pgm_get_far_address(cmdtbl1[0].cmd) + i * sizeof(cmdtbl1[0]));
  } else {
    c = pgm_read_dword_far(pgm_get_far_address(cmdtbl2[0].cmd) + (i - entries1) * sizeof(cmdtbl2[0]));    
  }
  return c;
}

uint16_t get_cmdtbl_line(int i) {
  uint16_t l = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  if (i < entries1) {
//  l=pgm_read_word(&cmdtbl[i].line);  // ProgNr
    l = pgm_read_word_far(pgm_get_far_address(cmdtbl1[0].line) + i * sizeof(cmdtbl1[0]));
  } else {
    l = pgm_read_word_far(pgm_get_far_address(cmdtbl2[0].line) + (i - entries1) * sizeof(cmdtbl2[0]));    
  }
  return l;
}

uint16_t get_cmdtbl_desc(int i) {
  uint16_t desc = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  if (i < entries1) {
    desc = pgm_read_word_far(pgm_get_far_address(cmdtbl1[0].desc) + i * sizeof(cmdtbl1[0]));
  } else {
    desc = pgm_read_word_far(pgm_get_far_address(cmdtbl2[0].desc) + (i - entries1) * sizeof(cmdtbl2[0]));    
  }
  return desc;
}

uint16_t get_cmdtbl_enumstr(int i) {
  uint16_t enumstr = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  if (i < entries1) {
    enumstr = pgm_read_word_far(pgm_get_far_address(cmdtbl1[0].enumstr) + i * sizeof(cmdtbl1[0]));
  } else {
    enumstr = pgm_read_word_far(pgm_get_far_address(cmdtbl2[0].enumstr) + (i - entries1) * sizeof(cmdtbl2[0]));    
  }
  return enumstr;
}

uint16_t get_cmdtbl_enumstr_len(int i) {
  uint16_t enumstr_len = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  if (i < entries1) {
    enumstr_len = pgm_read_word_far(pgm_get_far_address(cmdtbl1[0].enumstr_len) + i * sizeof(cmdtbl1[0]));
  } else {
    enumstr_len = pgm_read_word_far(pgm_get_far_address(cmdtbl2[0].enumstr_len) + (i - entries1) * sizeof(cmdtbl2[0]));    
  }
  return enumstr_len;
}


uint8_t get_cmdtbl_category(int i) {
  uint8_t cat = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  if (i < entries1) {
//   cat=pgm_read_byte(&cmdtbl[i].category);
    cat = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].category) + i * sizeof(cmdtbl1[0]));
  } else {
    cat = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].category) + (i - entries1) * sizeof(cmdtbl2[0]));
  }
  return cat;
}

uint8_t get_cmdtbl_type(int i) {
  uint8_t type = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  if (i < entries1) {
    type = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].type) + i * sizeof(cmdtbl1[0]));
  } else {
    type = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].type) + (i - entries1) * sizeof(cmdtbl2[0]));
  }
  return type;
}

uint8_t get_cmdtbl_dev_fam(int i) {
  uint8_t dev_fam = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  if (i < entries1) {
    dev_fam = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].dev_fam) + i * sizeof(cmdtbl1[0]));
  } else {
    dev_fam = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].dev_fam) + (i - entries1) * sizeof(cmdtbl2[0]));
  }
  return dev_fam;
}

uint8_t get_cmdtbl_dev_var(int i) {
  uint8_t dev_var = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  if (i < entries1) {
    dev_var = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].dev_var) + i * sizeof(cmdtbl1[0]));
  } else {
    dev_var = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].dev_var) + (i - entries1) * sizeof(cmdtbl2[0]));
  }
  return dev_var;
}

uint8_t get_cmdtbl_flags(int i) {
  uint8_t flags = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  if (i < entries1) {
    flags = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].flags) + i * sizeof(cmdtbl1[0]));
  } else {
    flags = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].flags) + (i - entries1) * sizeof(cmdtbl2[0]));
  }
  return flags;
}


/** *****************************************************************
 *  Function: findLine()
 *  Does:     Scans the command table struct for a matching line
 *            number (ProgNr) and returns the command code.
 * Pass parameters:
 *  uint16  line     the requested match (ProgNr)
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
int findLine(uint16_t line
           , uint16_t start_idx  //
           , uint32_t *cmd)      // 32-bit command code
{
  int found;
  int i = 0;
  int save_i;
  uint32_t c, save_c;
  uint16_t l;

  // search for the line in cmdtbl
  if (start_idx == 0) {
    if (get_cmdtbl_line(i) < line) {
      while (i+100 < (int)(sizeof(cmdtbl1)/sizeof(cmdtbl1[0])-1 + sizeof(cmdtbl2)/sizeof(cmdtbl2[0])-1)) {
        if (get_cmdtbl_line(i+100) < line) {
          i = i + 100;
        } else {
          break;
        }
      }
    }
  } else {
    i=start_idx;
  }
  found=0;
  do{
    c=get_cmdtbl_cmd(i);
    if(c==CMD_END) break;
    l=get_cmdtbl_line(i);
    if(l==line){
      uint8_t dev_fam = get_cmdtbl_dev_fam(i);
      uint8_t dev_var = get_cmdtbl_dev_var(i);
      uint8_t dev_flags = get_cmdtbl_flags(i);
      
      if ((dev_fam == my_dev_fam || dev_fam == 255) && (dev_var == my_dev_var || dev_var == 255)) {
        if (dev_fam == my_dev_fam && dev_var == my_dev_var) {
          if ((dev_flags & FL_NO_CMD) == FL_NO_CMD) {
            while (c==get_cmdtbl_cmd(i)) {
              i++;
            }
            found=0;
            i--;
          } else {
            found=1;
            break;
          }
        } else if ((!found && dev_fam!=my_dev_fam) || (dev_fam==my_dev_fam)) { // wider match has hit -> store in case of best match
          if ((dev_flags & FL_NO_CMD) == FL_NO_CMD) {
            while (c==get_cmdtbl_cmd(i)) {
              i++;
            }
            found=0;
            i--;
          } else {
            found=1;
            save_i=i;
            save_c=c;
          }
        }
      }
    }
    if(l>line){
      if (found) {
        i=save_i;
        c=save_c;
      }
      break;
    }
    i++;
  }while(1);

  if(!found){
    return -1;
  }
  if(cmd!=NULL) *cmd=c;
  return i;
}


/** *****************************************************************
 *  Function: freeRam()
 *  Does:     Returns the amount of available RAM
 *
 * *************************************************************** */
int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}


/** *****************************************************************
 *  Function:  SerialPrintHex()
 *  Does:      Sends the hex representation of one byte to the PC
 *             hardware serial interface. Adds a leading zero if
 *             it is a one-digit hex value.
 *  Pass parameters:
 *   byte      the value to convert and send
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *    Serial  instance
 * *************************************************************** */
void SerialPrintHex(byte val) {
  if (val < 16) Serial.print(F("0"));  // add a leading zero to single-digit values
  Serial.print(val, HEX);
}

/** *****************************************************************
 *  Function:  SerialPrintHex32()
 *  Does:      Sends the hex representation of a 32-bit value to the
 *             PC hardware serial interface.  Pad with leading zeroes
 *             to get an eight-character hex representation.
 *  Pass parameters:
 *   uint32 val The value to convert and send
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *    Serial  instance
 * *************************************************************** */
void SerialPrintHex32(uint32_t val) {
  if (val <= 0x0fffffff) Serial.print(F("0"));
  if (val <= 0x00ffffff) Serial.print(F("0"));
  if (val <= 0x000fffff) Serial.print(F("0"));
  if (val <= 0x0000ffff) Serial.print(F("0"));
  if (val <= 0x00000fff) Serial.print(F("0"));
  if (val <= 0x000000ff) Serial.print(F("0"));
  if (val <= 0x0000000f) Serial.print(F("0"));
  Serial.print(val, HEX);
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
void SerialPrintData(byte* msg){
  // Calculate pure data length without housekeeping info
  int data_len=0;
  if (bus_type == BUS_BSB) {
    data_len=msg[len_idx]-11;     // get packet length, then subtract
  }
  if (bus_type == BUS_LPB) {
    data_len=msg[len_idx]-14;     // get packet length, then subtract
  }
  if (bus_type == BUS_PPS) {
    data_len=9;
  }
  // Start indexing where the payload begins
  for(int i=0;i<data_len;i++){
    SerialPrintHex(msg[pl_start+i]);
    Serial.print(F(" "));
  }
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
void SerialPrintRAW(byte* msg, byte len){
  for(int i=0;i<len;i++){
    SerialPrintHex(msg[i]);
    Serial.print(F(" "));
  }
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
char *TranslateAddr(byte addr, char *device){
  switch(addr&0x7F){
    case ADDR_HEIZ: strncpy(device, "HEIZ", 4); break;
    case ADDR_EM1: strncpy(device, "EM1", 4); break;
    case ADDR_EM2: strncpy(device, "EM2", 4); break;
    case ADDR_RGT1: strncpy(device, "RGT1", 4); break;
    case ADDR_RGT2: strncpy(device, "RGT2", 4); break;
    case ADDR_CNTR: strncpy(device, "CNTR", 4); break;
    case ADDR_LAN: strncpy(device, "LAN", 4); break;
    case ADDR_DISP: strncpy(device, "DISP", 4); break;
    case ADDR_SRVC: strncpy(device, "SRVC", 4); break;
    case ADDR_OZW: strncpy(device, "OZW", 4); break;
    case ADDR_ALL: strncpy(device, "ALL ", 4); break;
    default: sprintf(device, "%02X", addr); break;
  }
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
void SerialPrintAddr(byte addr){
  switch(addr&0x7F){
    case ADDR_HEIZ: Serial.print(F("HEIZ")); break;
    case ADDR_EM1: Serial.print(F("EM1")); break;
    case ADDR_EM2: Serial.print(F("EM2")); break;
    case ADDR_RGT1: Serial.print(F("RGT1")); break;
    case ADDR_RGT2: Serial.print(F("RGT2")); break;
    case ADDR_CNTR: Serial.print(F("CNTR")); break;
    case ADDR_SRVC: Serial.print(F("SRVC")); break;
    case ADDR_LAN: Serial.print(F("LAN")); break;
    case ADDR_DISP: Serial.print(F("DISP")); break;
    case ADDR_OZW: Serial.print(F("OZW")); break;
    case ADDR_ALL: Serial.print(F("ALL ")); break;
    default: SerialPrintHex(addr); break;
  }
}

/** *****************************************************************
 *  Function:  TranslateAddr()
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
char *TranslateType(byte type, char *mtype){
  switch(type){
    case TYPE_QINF: strncpy(mtype, "QINF", 4); break;
    case TYPE_INF: strncpy(mtype, "INF", 4); break;
    case TYPE_SET: strncpy(mtype, "SET", 4); break;
    case TYPE_ACK: strncpy(mtype, "ACK", 4); break;
    case TYPE_NACK: strncpy(mtype, "NACK", 4); break;
    case TYPE_QUR: strncpy(mtype, "QUR", 4); break;
    case TYPE_ANS: strncpy(mtype, "ANS", 4); break;
    case TYPE_QRV: strncpy(mtype, "QRV", 4); break;
    case TYPE_ARV: strncpy(mtype, "ARV", 4); break;
    case TYPE_ERR: strncpy(mtype, "ERR", 4); break;
    // If no match found: print the hex value
    default: sprintf(mtype, "%02X", type); break;
  } // endswitch
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
void SerialPrintType(byte type){
  switch(type){
    case TYPE_QINF: Serial.print(F("QINF")); break;
    case TYPE_INF: Serial.print(F("INF")); break;
    case TYPE_SET: Serial.print(F("SET")); break;
    case TYPE_ACK: Serial.print(F("ACK")); break;
    case TYPE_NACK: Serial.print(F("NACK")); break;
    case TYPE_QUR: Serial.print(F("QUR")); break;
    case TYPE_ANS: Serial.print(F("ANS")); break;
    case TYPE_QRV: Serial.print(F("QRV")); break;
    case TYPE_ARV: Serial.print(F("ARV")); break;
    case TYPE_ERR:
    Serial.print(F("ERR"));
    //outBufLen+=sprintf(outBuf+outBufLen,"ERR");
    break;
    // If no match found: print the hex value
    default: SerialPrintHex(type); break;
  } // endswitch
} // --- SerialPrintType() ---

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printLineNumber(uint32_t val) {
    char *p=outBuf+outBufLen;
    outBufLen+=sprintf(outBuf+outBufLen,"%4ld",val);
    Serial.print(p);
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printBIT(byte *msg,byte data_len){
  char *p=outBuf+outBufLen;
  if(data_len == 2 || data_len == 3){
    if(msg[pl_start]==0 || data_len == 3){
      for (int i=7;i>=0;i--) {
        outBufLen+=sprintf(outBuf+outBufLen,"%d",msg[pl_start+1+data_len-2] >> i & 1);
      }
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    Serial.print(p);
  }else{
    Serial.print(F("BYTE len error len!=2: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printBYTE(byte *msg,byte data_len,const char *postfix){
  char *p=outBuf+outBufLen;
  uint8_t pps_offset = (msg[0] == 0x17 && *PPS_write_enabled != 1 && bus_type == BUS_PPS);

  if(data_len == 2 || bus_type == BUS_PPS){
    if(msg[pl_start]==0 || bus_type == BUS_PPS){
      outBufLen+=sprintf(outBuf+outBufLen,"%d",msg[pl_start+1+pps_offset]);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    if(postfix!=NULL){
      outBufLen+=sprintf(outBuf+outBufLen," %s",postfix);
    }
    Serial.print(p);
  }else{
    Serial.print(F("BYTE len error len!=2: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printWORD(byte *msg,byte data_len, long divisor, const char *postfix){
  long lval;
  char *p=outBuf+outBufLen;

  if(data_len == 3){
    if(msg[pl_start]==0){
      lval=((long(msg[pl_start+1])<<8)+long(msg[pl_start+2])) / divisor;
      outBufLen+=sprintf(outBuf+outBufLen,"%ld",lval);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    if(postfix!=NULL){
      outBufLen+=sprintf(outBuf+outBufLen," %s",postfix);
    }
    Serial.print(p);
  }else{
    Serial.print(F("WORD len error len!=3: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printSINT(byte *msg,byte data_len, long multiplier, const char *postfix){
  int16_t lval;
  char *p=outBuf+outBufLen;

  if(data_len == 3){
    if(msg[pl_start]==0){
      lval=(((int16_t)(msg[pl_start+1])<<8) + (int16_t)(msg[pl_start+2])) * multiplier;
      outBufLen+=sprintf(outBuf+outBufLen,"%d",lval);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    if(postfix!=NULL){
      outBufLen+=sprintf(outBuf+outBufLen," %s",postfix);
    }
    Serial.print(p);
  }else{
    Serial.print(F("WORD len error len!=3: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printDWORD(byte *msg,byte data_len,long divider, const char *postfix){
  long lval;
  char *p=outBuf+outBufLen;

  if(data_len == 5){
    if(msg[pl_start]==0){
      lval=((long(msg[pl_start+1])<<24)+(long(msg[pl_start+2])<<16)+(long(msg[pl_start+3])<<8)+long(msg[pl_start+4]))/divider;
      outBufLen+=sprintf(outBuf+outBufLen,"%ld",lval);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    if(postfix!=NULL){
      outBufLen+=sprintf(outBuf+outBufLen," %s",postfix);
    }
    Serial.print(p);
  }else{
    Serial.print(F("DWORD len error len!=5: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void _printFIXPOINT(double dval, int precision){
  int a,b,i;
  if(dval<0){
    outBufLen+=sprintf(outBuf+outBufLen,"-");
    dval*=-1.0;
  }
  double rval=10.0;
  for(i=0;i<precision;i++) rval*=10.0;
  dval+=5.0/rval;
  a=(int)(dval);
  rval/=10.0;
  b=(int)(dval*rval - a*rval);
  if(precision==0){
    outBufLen+=sprintf(outBuf+outBufLen,"%d",a);
  }else{
    char formatstr[8]="%d.%01d";
    formatstr[5]='0'+precision;
    outBufLen+=sprintf(outBuf+outBufLen,formatstr,a,b);
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printFIXPOINT(byte *msg,byte data_len,double divider,int precision,const char *postfix){
  double dval;
  char *p=outBuf+outBufLen;
  int8_t pps_offset = (((*PPS_write_enabled == 1 && msg[0] != 0x00) || (*PPS_write_enabled != 1 && msg[0] != 0x17 && msg[0] != 0x00)) && bus_type == BUS_PPS);

  if(data_len == 3 || data_len == 5){
    if(msg[pl_start]==0 || bus_type == BUS_PPS){
      if (data_len == 3) {
        dval=double((msg[pl_start+1-pps_offset] << 8) + msg[pl_start+2-pps_offset]) / divider;
      } else {
        dval=double((msg[pl_start+3-pps_offset] << 8) + msg[pl_start+4-pps_offset]) / divider;
      }
      _printFIXPOINT(dval,precision);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    if(postfix!=NULL){
      outBufLen+=sprintf(outBuf+outBufLen," %s",postfix);
    }
    Serial.print(p);
  }else{
    Serial.print(F("FIXPOINT len !=3: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printFIXPOINT_DWORD(byte *msg,byte data_len,double divider,int precision,const char *postfix){
  double dval;
  char *p=outBuf+outBufLen;

  if(data_len == 5){
    if(msg[pl_start]==0){
      dval=double((long(msg[pl_start+1])<<24)+(long(msg[pl_start+2])<<16)+(long(msg[pl_start+3])<<8)+long(msg[pl_start+4])) / divider;
      _printFIXPOINT(dval,precision);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    if(postfix!=NULL){
      outBufLen+=sprintf(outBuf+outBufLen," %s",postfix);
    }
    Serial.print(p);
  }else{
    Serial.print(F("FIXPOINT_DWORD len !=5: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printFIXPOINT_BYTE(byte *msg,byte data_len,double divider,int precision,const char *postfix){
  double dval;
  char *p=outBuf+outBufLen;

  if(data_len == 2 || (data_len == 3 && (my_dev_fam == 107 || my_dev_fam == 123 || my_dev_fam == 163))){
    if(msg[pl_start]==0){
      dval=double((signed char)msg[pl_start+1+(data_len==3)]) / divider;
      _printFIXPOINT(dval,precision);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    if(postfix!=NULL){
      outBufLen+=sprintf(outBuf+outBufLen," %s",postfix);
    }
    Serial.print(p);
  }else{
    Serial.print(F("FIXPOINT_BYTE len !=2: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printFIXPOINT_BYTE_US(byte *msg,byte data_len,double divider,int precision,const char *postfix){
  double dval;
  char *p=outBuf+outBufLen;

  if(data_len == 2){
    if(msg[pl_start]==0){
      dval=double(msg[pl_start+1]) / divider;
      _printFIXPOINT(dval,precision);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    if(postfix!=NULL){
      outBufLen+=sprintf(outBuf+outBufLen," %s",postfix);
    }
    Serial.print(p);
  }else{
    Serial.print(F("FIXPOINT_BYTE len !=2: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printCHOICE(byte *msg,byte data_len,const char *val0,const char *val1){
  char *p=outBuf+outBufLen;
  uint8_t pps_offset = ((*PPS_write_enabled != 1 && msg[0] == 0x17) && bus_type == BUS_PPS);
  if (data_len == 2 || bus_type == BUS_PPS) {
    if (msg[pl_start]==0 || bus_type == BUS_PPS) {
      if(msg[pl_start+1+pps_offset]==0){
        outBufLen+=sprintf(outBuf+outBufLen,"%d - %s",msg[pl_start+1+pps_offset],val0);
      } else {
        outBufLen+=sprintf(outBuf+outBufLen,"%d - %s",msg[pl_start+1+pps_offset],val1);
      }
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    Serial.print(p);
  } else {
    Serial.print(F("CHOICE len !=2: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printENUM(uint_farptr_t enumstr,uint16_t enumstr_len,uint16_t search_val, int print_val){
  uint16_t val;
  char *p=outBuf+outBufLen;

  if(enumstr!=0){
    uint16_t c=0;
    while(c<enumstr_len){
      if((byte)(pgm_read_byte_far(enumstr+c+1))!=' '){
        val=uint16_t((pgm_read_byte_far(enumstr+c) << 8)) | uint16_t(pgm_read_byte_far(enumstr+c+1));
        c++;
      }else{
        val=uint16_t(pgm_read_byte_far(enumstr+c));
      }
      //skip leading space
      c+=2;
      if(val==search_val){
       // enum value found
       break;
      }
      while(pgm_read_byte_far(enumstr+c)!=0) c++;
      c++;
    }
    if(c<enumstr_len){
      if(print_val){
        strncpy_PF(buffer, enumstr+c, sizeof(buffer));
        buffer[sizeof(buffer)-1] = 0;
        outBufLen+=sprintf(outBuf+outBufLen,"%d - %s",val,buffer);
      }else{
        strncpy_PF(buffer, enumstr+c, sizeof(buffer));
        buffer[sizeof(buffer)-1] = 0;
        outBufLen+=sprintf(outBuf+outBufLen,"%s",buffer);
      }
    }else{
      outBufLen+=sprintf(outBuf+outBufLen,"%d - not found",search_val);
    }
    Serial.print(p);
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printCustomENUM(uint_farptr_t enumstr,uint16_t enumstr_len,uint16_t search_val, int print_val){
  uint8_t val;
  char *p=outBuf+outBufLen;

  if(enumstr!=0){
    uint16_t c=0;
    while(c<enumstr_len){
      val=pgm_read_byte_far(enumstr+c+1);
      //skip leading space
      c+=3;
      if(val==search_val){
       // enum value found
       break;
      }
      while(pgm_read_byte_far(enumstr+c)!=0) c++;
      c++;
    }
    if(c<enumstr_len){
      if(print_val){
        strncpy_PF(buffer, enumstr+c, sizeof(buffer));
        buffer[sizeof(buffer)-1] = 0;
        outBufLen+=sprintf(outBuf+outBufLen,"%d - %s",val,buffer);
      }else{
        strncpy_PF(buffer, enumstr+c, sizeof(buffer));
        buffer[sizeof(buffer)-1] = 0;
        outBufLen+=sprintf(outBuf+outBufLen,"%s",buffer);
      }
    }else{
      outBufLen+=sprintf(outBuf+outBufLen,"%d - not found",search_val);
    }
    Serial.print(p);
  }
}


/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printDateTime(byte *msg,byte data_len){
  char *p=outBuf+outBufLen;

  if(data_len == 9){
    if(msg[pl_start]==0){
      outBufLen+=sprintf(outBuf+outBufLen,"%02d.%02d.%d %02d:%02d:%02d",msg[pl_start+3],msg[pl_start+2],msg[pl_start+1]+1900,msg[pl_start+5],msg[pl_start+6],msg[pl_start+7]);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    Serial.print(p);
  }else{
    Serial.print(F(" VT_DATETIME len !=9: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printDate(byte *msg,byte data_len){
  char *p=outBuf+outBufLen;

  if(data_len == 9){
    if(msg[pl_start]==0){
      outBufLen+=sprintf(outBuf+outBufLen,"%02d.%02d",msg[pl_start+3],msg[pl_start+2]);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    Serial.print(p);
  }else{
    Serial.print(F(" VT_DATE len !=9: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printTimeProg(byte *msg,byte data_len){
  char *p=outBuf+outBufLen;

  if(data_len == 12){
    outBufLen+=sprintf(outBuf+outBufLen,"1. ");
    if(msg[pl_start]<24){
      outBufLen+=sprintf(outBuf+outBufLen,"%02d:%02d - %02d:%02d",msg[pl_start],msg[pl_start+1],msg[pl_start+2],msg[pl_start+3]);
    }else{
      outBufLen+=sprintf(outBuf+outBufLen,"--:-- - --:--");
    }
    outBufLen+=sprintf(outBuf+outBufLen," 2. ");
    if(msg[pl_start+4]<24){
      outBufLen+=sprintf(outBuf+outBufLen,"%02d:%02d - %02d:%02d",msg[pl_start+4],msg[pl_start+5],msg[pl_start+6],msg[pl_start+7]);
    }else{
      outBufLen+=sprintf(outBuf+outBufLen,"--:-- - --:--");
    }
    outBufLen+=sprintf(outBuf+outBufLen," 3. ");
    if(msg[pl_start+8]<24){
      outBufLen+=sprintf(outBuf+outBufLen,"%02d:%02d - %02d:%02d",msg[pl_start+8],msg[pl_start+9],msg[pl_start+10],msg[pl_start+11]);
    }else{
      outBufLen+=sprintf(outBuf+outBufLen,"--:-- - --:--");
    }
    Serial.print(p);
  }else{
    Serial.print(F(" VT_TIMEPROG len !=12: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *
 * Parameters passed back:
 *
 * Function value returned:
 *
 * Global resources used:
 *
 * *************************************************************** */
void printTime(byte *msg,byte data_len){
  char *p=outBuf+outBufLen;

  if(data_len == 3){
    if(msg[pl_start]==0){
      outBufLen+=sprintf(outBuf+outBufLen,"%02d:%02d",msg[pl_start+1],msg[pl_start+2]);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"--:--");
    }
    Serial.print(p);
  }else{
    Serial.print(F("VT_HOUR_MINUTES len !=3: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

/** *****************************************************************
 *  Function:
 *  Does:
 *  Pass parameters:
 *   byte * msg
 *   byte len
 *  Parameters passed back:
 *   byte *msg    unchanged
 *  Function value returned:
 *   none
 *  Global resources used:
 *    outBuf
 * *************************************************************** */
void printLPBAddr(byte *msg,byte data_len){
  char *p=outBuf+outBufLen;

  if(data_len == 2){
    if(msg[pl_start]==0){   // payload Int8 value
    outBufLen+=sprintf(outBuf+outBufLen,"%02d.%02d",msg[pl_start+1]>>4,(msg[pl_start+1] & 0x0f)+1);
  }else{
    outBufLen+=sprintf(outBuf+outBufLen,"---");
  }
  Serial.print(p);
  }else{
    Serial.print(F(" VT_LPBADDR len !=2: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
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

/** *****************************************************************
 *  Function:  printTelegram()
 *  Does:      Send the decoded telegram content to the hardware
 *             serial interface.
 *  Pass parameters:
 *   char* msg    the BS bus telegram
 *  Parameters passed back:
 *   char * pvalstr
 *  Function value returned:
 *   char*
 *  Global resources used:
 *   Serial    hardware serial interface to a PC
 *   outBuf[]
 * *************************************************************** */
char *printTelegram(byte* msg, int query_line) {
  char *pvalstr=NULL;

  outBufclear();

/*
#if !DEBUG
  // suppress DE telegrams
  if(msg[0]==0xDE) return;

  // suppress QUERY telegrams
  if(msg[4]==TYPE_QUR) return;
#endif
*/

  if (bus_type != BUS_PPS) {
    // source
    SerialPrintAddr(msg[1+(bus_type*2)]); // source address
    Serial.print(F("->"));
    SerialPrintAddr(msg[2]); // destination address
    Serial.print(F(" "));
    // msg[3] contains the message length, not handled here
    SerialPrintType(msg[4+(bus_type*4)]); // message type, human readable
    Serial.print(F(" "));
  } else {
    if (!monitor) {
      switch (msg[0]) {
        case 0x1D: Serial.print(F("INF HEIZ->QAA ")); break;
        case 0x1E: Serial.print(F("REQ HEIZ->QAA ")); break;
        case 0x17: Serial.print(F("RTS HEIZ->QAA ")); break;
        case 0xFD: Serial.print(F("ANS QAA->HEIZ ")); break;
        default: break;
      }
    }
  }

  uint32_t cmd = 0;
  if (bus_type == BUS_BSB) {
    if(msg[4]==TYPE_QUR || msg[4]==TYPE_SET){ //QUERY and SET: byte 5 and 6 are in reversed order
      cmd=(uint32_t)msg[6]<<24 | (uint32_t)msg[5]<<16 | (uint32_t)msg[7] << 8 | (uint32_t)msg[8];
    }else{
      cmd=(uint32_t)msg[5]<<24 | (uint32_t)msg[6]<<16 | (uint32_t)msg[7] << 8 | (uint32_t)msg[8];
    }
  }
  if (bus_type == BUS_LPB) {
    if(msg[8]==TYPE_QUR || msg[8]==TYPE_SET){ //QUERY and SET: byte 9 and 10 are in reversed order
      cmd=(uint32_t)msg[10]<<24 | (uint32_t)msg[9]<<16 | (uint32_t)msg[11] << 8 | (uint32_t)msg[12];
    }else{
      cmd=(uint32_t)msg[9]<<24 | (uint32_t)msg[10]<<16 | (uint32_t)msg[11] << 8 | (uint32_t)msg[12];
    }
  }
  uint8_t pps_cmd = msg[1 + (msg[0] == 0x17 && *PPS_write_enabled != 1)];
  if (bus_type == BUS_PPS) {
    cmd = 0x2D000000 + query_line - 15000;
    cmd = cmd + (msg[1] * 0x10000);
  }
  // search for the command code in cmdtbl
  int i=0;        // begin with line 0
  int save_i=0;
  boolean known=0;
  uint8_t score = 0;
  uint32_t c;     // command code
  int line = 0, match_line = 0;
  c=get_cmdtbl_cmd(i);
  line = get_cmdtbl_line(i);

  while(c!=CMD_END){
    if((c == cmd || (line >= 15000 && ((c & 0x00FF0000) >> 16) == pps_cmd && bus_type == BUS_PPS && msg[0] != 0x1E)) && (query_line == -1 || line == query_line)){
      uint8_t dev_fam = get_cmdtbl_dev_fam(i);
      uint8_t dev_var = get_cmdtbl_dev_var(i);
      uint8_t dev_flags = get_cmdtbl_flags(i);
      match_line = get_cmdtbl_line(i);
      if ((dev_fam == my_dev_fam || dev_fam == 255) && (dev_var == my_dev_var || dev_var == 255)) {
        if (dev_fam == my_dev_fam && dev_var == my_dev_var) {
          if ((dev_flags & FL_NO_CMD) == FL_NO_CMD) {
            known = false;
            score = 5;
          } else {
            known = true;
            save_i = i;
            score = 6;
            break;
          }
        } 
        if (dev_fam!=my_dev_fam) {
          if ((dev_flags & FL_NO_CMD) == FL_NO_CMD && score < 1) {
            known = false;
            score = 1;
          } else if (score < 2) {
            known = true;
            save_i = i;
            score = 2;
          }
        }
        if (dev_fam==my_dev_fam) {
          if ((dev_flags & FL_NO_CMD) == FL_NO_CMD && score < 3) {
            known = false;
            score = 3;
          } else if (score < 4) {
            known = true;
            save_i = i;
            score = 4;
          }
        }
      }
    }

/*
    if (known && c!=cmd) {
      i=save_i;
      break;
    }
*/
    i++;
    line = get_cmdtbl_line(i);
    c=get_cmdtbl_cmd(i);
    if (line > match_line && known == false) {
      score = 0;
    }
  }
  if(!known){                          // no hex code match
    // Entry in command table is "UNKNOWN" (0x00000000)
    if (bus_type != BUS_PPS) {
      Serial.print(F("     "));
      SerialPrintHex32(cmd);             // print what we have got
      Serial.print(F(" "));
    }
  }else{
    i = save_i;
    // Entry in command table is a documented command code
    uint16_t line=get_cmdtbl_line(i);
    printLineNumber(line);             // the ProgNr
    Serial.print(F(" "));
    outBufLen+=sprintf(outBuf+outBufLen," ");

    // print category
    int cat=get_cmdtbl_category(i);
    int len=sizeof(ENUM_CAT);
//    memcpy_PF(buffer, pgm_get_far_address(ENUM_CAT), len);
//    memcpy_P(buffer, &ENUM_CAT,len);
//    buffer[len]=0;
    printENUM(pgm_get_far_address(ENUM_CAT),len,cat,0);
    Serial.print(F(" - "));
    outBufLen+=sprintf(outBuf+outBufLen," - ");

    // print menue text
    strcpy_PF(buffer, get_cmdtbl_desc(i));
//    strcpy_P(buffer, (char*)pgm_read_word(&(cmdtbl[i].desc)));
    char *p=outBuf+outBufLen;
    outBufLen+=sprintf(outBuf+outBufLen," %s: ", buffer);
    Serial.print(p);
  }

  // decode parameter
  int data_len=0;
  if (bus_type == BUS_BSB) {
    data_len=msg[len_idx]-11;     // get packet length, then subtract
  }
  if (bus_type == BUS_LPB) {
    data_len=msg[len_idx]-14;     // get packet length, then subtract
  } 
  if (bus_type == BUS_PPS) {
    data_len = 3;
  }

  if(data_len < 0){
    Serial.print(F("len ERROR "));
    Serial.print(msg[len_idx]);
  }else{
    if(data_len > 0){
      if(known){
        if(msg[4+(bus_type*4)]==TYPE_ERR){
          char *p=outBuf+outBufLen;
//          outBufLen+=sprintf(outBuf+outBufLen,"error %d",msg[9]); For truncated error message LPB bus systems
//          if((msg[9]==0x07 && bus_type==0) || (msg[9]==0x05 && bus_type==1)){
          outBufLen+=sprintf(outBuf+outBufLen,"error %d",msg[pl_start]);
          if(msg[pl_start]==0x07){
            outBufLen+=sprintf(outBuf+outBufLen," (parameter not supported)");
          }
          Serial.print(p);
        }else{
          pvalstr=outBuf+outBufLen;
          uint8_t type=get_cmdtbl_type(i);
          uint8_t div_type=1;
          uint8_t div_precision=1;
          float div_operand=1;
          uint8_t div_unit_len=0;
          int k=0;
          while(div_type!=VT_UNKNOWN){
            div_type=pgm_read_byte_far(pgm_get_far_address(optbl[0].type) + k * sizeof(optbl[0]));
            div_operand=pgm_read_float_far(pgm_get_far_address(optbl[0].operand) + k * sizeof(optbl[0]));
            div_precision=pgm_read_byte_far(pgm_get_far_address(optbl[0].precision) + k * sizeof(optbl[0]));
            div_unit_len=pgm_read_byte_far(pgm_get_far_address(optbl[0].unit_len) + k * sizeof(optbl[0]));
            memcpy_PF(div_unit, pgm_read_word_far(pgm_get_far_address(optbl[0].unit) + k * sizeof(optbl[0])),div_unit_len);
            if(type == div_type){
              break;
            }
            k++;
          }

          switch(type) {
//          switch(pgm_read_byte(&cmdtbl[i].type)){
            case VT_BIT: // u8
              printBIT(msg,data_len);
              break;
            case VT_MONTHS: // u8 Monate
            case VT_DAYS: // u8 Tage
            case VT_GRADIENT_SHORT: //u8 min
            case VT_HOURS_SHORT: // u8 h
            case VT_MINUTES_SHORT: //u8 min
            case VT_SECONDS_SHORT: //u8 s
            case VT_PERCENT: // u8 %
            case VT_BYTE: // u8
//            case VT_VOLTAGE: // u16 - 0.0 -> 00 00 //FUJITSU
              printBYTE(msg,data_len,div_unit);
              break;
            case VT_DAYS_WORD: // u16 Tage
            case VT_HOURS_WORD: // u16 h
            case VT_MINUTES_WORD: //u16 min
            case VT_SECONDS_WORD: //u16 s
            case VT_GRADIENT: // u16
            case VT_UINT: //  s16
            case VT_UINT5: //  s16 / 5
            case VT_UINT10: //  s16 / 10
            case VT_UINT100:  // u32 / 100
//              printWORD(msg,data_len,div_operand,div_unit);
              printFIXPOINT(msg,data_len,div_operand,div_precision,div_unit);
              break;
            case VT_MINUTES: // u32 min
            case VT_HOURS: // u32 h
            case VT_DWORD: // s32
              printDWORD(msg,data_len,div_operand,div_unit);
              break;
            case VT_SINT: //  s16
              printSINT(msg,data_len,div_operand,div_unit);
              break;
            case VT_SECONDS_SHORT4: // s8 / 4 (signed)
            case VT_SECONDS_SHORT5: // s8 / 5 (signed)
            case VT_TEMP_SHORT64: // s8 / 64 (signed)
            case VT_TEMP_SHORT5: // s8 / 2 (signed)
            case VT_TEMP_SHORT: // s8
              printFIXPOINT_BYTE(msg,data_len,div_operand,div_precision,div_unit);
              break;
            case VT_PRESSURE: // u8 / 10.0 bar
            case VT_PERCENT5: // u8 %
            case VT_TEMP_SHORT5_US: // u8 / 2 (unsigned)
            case VT_VOLTAGE: // u16 - 0.0 -> 00 00 //FUJITSU -- is this really u16 (two byte) or just enable/disable flag + 1 byte to be divided by 10?
              printFIXPOINT_BYTE_US(msg,data_len,div_operand,div_precision,div_unit);
              break;
            case VT_TEMP: // s16 / 64.0 - Wert als Temperatur interpretiert (RAW / 64)
            case VT_SECONDS_WORD5: // u16  - Wert als Temperatur interpretiert (RAW / 2)
            case VT_TEMP_WORD: // s16  - Wert als Temperatur interpretiert (RAW)
            case VT_TEMP_WORD5_US: // s16  - Wert als Temperatur interpretiert (RAW / 2)
            case VT_LITERPERHOUR: // u16 / l/h
            case VT_LITERPERMIN: // u16 / 0.1 l/min
            case VT_PRESSURE_WORD: // u16 / 10.0 bar
            case VT_POWER_WORD: // u16 / 10.0 kW
            case VT_ENERGY_WORD: // u16 / 10.0 kWh
            case VT_CURRENT: // u16 / 100 uA
            case VT_PROPVAL: // u16 / 16
            case VT_SPEED: // u16
            case VT_SPEED2: // u16
            case VT_FP1: // s16 / 10.0 Wert als Festkommazahl mit 1/10 Schritten interpretiert (RAW / 10)
            case VT_FP02: // u16 / 50.0 - Wert als Festkommazahl mit 2/100 Schritten interpretiert (RAW / 50)
            case VT_PERCENT_WORD1: // u16 %
            case VT_PERCENT_WORD: // u16 / 2 %
            case VT_PERCENT_100: // u16 / 100 %
            case VT_SINT1000: // s16 / 1000
              printFIXPOINT(msg,data_len,div_operand,div_precision,div_unit);
              break;
            case VT_POWER: // u32 / 10.0 kW
            case VT_ENERGY10: // u32 / 10.0 kWh
            case VT_ENERGY: // u32 / 1.0 kWh
              printFIXPOINT_DWORD(msg,data_len,div_operand,div_precision,div_unit);
              break;
            case VT_ONOFF:
              printCHOICE(msg,data_len,"Aus","Ein");
              break;
            case VT_YESNO:
              printCHOICE(msg,data_len,"Nein","Ja");
              break;
            case VT_CLOSEDOPEN:
              printCHOICE(msg,data_len,"Offen","Geschlossen");
              break;
            case VT_VOLTAGEONOFF:
              printCHOICE(msg,data_len,"0 Volt","230 Volt");
              break;
            case VT_LPBADDR: //decoding unklar 00 f0 -> 15.01
              printLPBAddr(msg,data_len);
              break;
            case VT_HOUR_MINUTES: // u8:u8
              printTime(msg,data_len);
              break;
            case VT_DATETIME: // special
              printDateTime(msg,data_len);
              break;
            case VT_SUMMERPERIOD:
            case VT_VACATIONPROG:
              printDate(msg,data_len);
              break;
            case VT_TIMEPROG:
              printTimeProg(msg,data_len);
              break;
            case VT_WEEKDAY: // enum
              if(data_len == 2){
                if(msg[pl_start]==0){
                  int len=sizeof(ENUM_WEEKDAY);
//                  memcpy_PF(buffer, pgm_get_far_address(ENUM_WEEKDAY), len);
//                  memcpy_P(buffer, &ENUM_WEEKDAY,len);
//                  buffer[len]=0;
                  printENUM(pgm_get_far_address(ENUM_WEEKDAY),len,msg[pl_start+1],0);
                }else{
                  Serial.print(F("---"));
                  outBufLen+=sprintf(outBuf+outBufLen,"---");
                }
              }else{
                Serial.print(F(" VT_WEEKDAY !=2: "));
                SerialPrintData(msg);
                outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
              }
              break;
            case VT_ENUM: // enum
              if(data_len == 2 || data_len == 3 || bus_type == 2) {
                if((msg[pl_start]==0 && data_len==2) || (msg[pl_start]==0 && data_len==3) || (bus_type == BUS_PPS)) {
                  uint16_t enumstr_len=get_cmdtbl_enumstr_len(i);
                  if(calc_enum_offset(get_cmdtbl_enumstr(i), enumstr_len)!=0) {
//                    memcpy_PF(buffer, calc_enum_offset(get_cmdtbl_enumstr(i)),len);
//                    buffer[len]=0;
                    if (data_len == 2) {
                      printENUM(calc_enum_offset(get_cmdtbl_enumstr(i), enumstr_len),enumstr_len,msg[pl_start+1],1);
                    } else {                            // Fujitsu: data_len == 3
                      int8_t pps_offset = 0;
                      if (*PPS_write_enabled == 1 && msg[0] != 0x00 && bus_type == BUS_PPS) pps_offset = -1;
                      printENUM(calc_enum_offset(get_cmdtbl_enumstr(i), enumstr_len),enumstr_len,msg[pl_start+2+pps_offset],1);
                    }
                  }else{
                    Serial.print(F("no enum str "));
                    SerialPrintData(msg);
                    outBufLen+=sprintf(outBuf+outBufLen,"no enum str");
                  }
                }else{
                  Serial.print(F("---"));
                  outBufLen+=sprintf(outBuf+outBufLen,"---");
                }
              } else {
                Serial.print(F(" VT_ENUM len !=2 && len != 3: "));
                SerialPrintData(msg);
                outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
              }
              break;
            case VT_CUSTOM_ENUM: // custom enum
            {
              uint16_t enumstr_len=get_cmdtbl_enumstr_len(i);
              uint_farptr_t enumstr_ptr = calc_enum_offset(get_cmdtbl_enumstr(i), enumstr_len);
              if(enumstr_ptr!=0) {
                uint8_t idx = pgm_read_byte_far(enumstr_ptr+0);
                printCustomENUM(enumstr_ptr,enumstr_len,msg[pl_start+idx],1);
              }else{
                Serial.print(F("no enum str "));
                SerialPrintData(msg);
                outBufLen+=sprintf(outBuf+outBufLen,"no enum str");
              }
              break;
            }
            case VT_CUSTOM_BYTE: // custom byte
            {
              char *p=outBuf+outBufLen;
              uint16_t enumstr_len=get_cmdtbl_enumstr_len(i);
              uint_farptr_t enumstr_ptr = calc_enum_offset(get_cmdtbl_enumstr(i), enumstr_len);
              if(enumstr_ptr!=0) {
                uint8_t idx = pgm_read_byte_far(enumstr_ptr+0);
                uint8_t len = pgm_read_byte_far(enumstr_ptr+1);
                uint32_t val = 0;
                for (int x=0; x<len; x++) {
                  val = val + ((uint32_t)msg[pl_start+idx+x] << (8*(len-1-x)));
                }

                outBufLen+=sprintf(outBuf+outBufLen,"%lu",val);
                Serial.println(p);
              }else{
                Serial.print(F("no enum str "));
                SerialPrintData(msg);
                outBufLen+=sprintf(outBuf+outBufLen,"no enum str");
              }
              break;
            }
            case VT_STRING: // string
              if(data_len > 0){
                if(msg[pl_start]!=0){
                  msg[pl_start + data_len]='\0'; // write terminating zero
                  Serial.print((char*)&msg[pl_start]);
                  outBufLen+=sprintf(outBuf+outBufLen,"%s",(char*)&msg[pl_start]);
                  remove_char(outBuf, '\'');
                } else {
                  Serial.print(F("-"));
                  outBufLen+=sprintf(outBuf+outBufLen,"-");
                }
              }else{
                Serial.print(F(" VT_STRING len ==0: "));
                SerialPrintData(msg);
                outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
              }
              break;
            case VT_PPS_TIME: // PPS: Time and day of week
            {
              switch(weekday()) {
                case 7: outBufLen+=sprintf(outBuf+outBufLen,"Sa"); break;
                case 1: outBufLen+=sprintf(outBuf+outBufLen,"So"); break;
                case 2: outBufLen+=sprintf(outBuf+outBufLen,"Mo"); break;
                case 3: outBufLen+=sprintf(outBuf+outBufLen,"Di"); break;
                case 4: outBufLen+=sprintf(outBuf+outBufLen,"Mi"); break;
                case 5: outBufLen+=sprintf(outBuf+outBufLen,"Do"); break;
                case 6: outBufLen+=sprintf(outBuf+outBufLen,"Fr"); break;
                default: break;
              }
              outBufLen+=sprintf(outBuf+outBufLen,", ");
              outBufLen+=sprintf(outBuf+outBufLen,"%02d",hour());
              outBufLen+=sprintf(outBuf+outBufLen,":");
              outBufLen+=sprintf(outBuf+outBufLen,"%02d",minute());
              outBufLen+=sprintf(outBuf+outBufLen,":");
              outBufLen+=sprintf(outBuf+outBufLen,"%02d",second());
              break;
            }
            case VT_ERRORCODE: //  u16 or u8 (via OCI420)
              if(data_len == 3 || data_len == 2) {
                if(msg[pl_start]==0){
                  long lval;
                  if (data_len == 3) {
                    lval=(long(msg[pl_start+1])<<8)+long(msg[pl_start+2]);
                  } else {
                    lval=long(msg[pl_start+1]);
                  }
                  uint16_t len=0;
                  uint16_t enumstr_len=get_cmdtbl_enumstr_len(i);
                  if(enumstr_len!=0) {
                    len=enumstr_len;
                    printENUM(calc_enum_offset(get_cmdtbl_enumstr(i), enumstr_len),enumstr_len,lval,1);
                  } else {
                    len=sizeof(ENUM_ERROR);
                    printENUM(pgm_get_far_address(ENUM_ERROR),len,lval,1);
                  }
//                  memcpy_PF(buffer, pgm_get_far_address(ENUM_ERROR), len);
//                  memcpy_P(buffer, &ENUM_ERROR,len);
//                  buffer[len]=0;
//                  printENUM(buffer,len,lval,1);
                } else {
                  Serial.print(F("---"));
                  outBufLen+=sprintf(outBuf+outBufLen,"---");
                }
              }else{
                Serial.print(F(" VT_ERRORCODE len ==0: "));
                SerialPrintData(msg);
                outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
              }
              break;
            case VT_UNKNOWN:
            default:
              SerialPrintData(msg);
              for (int i=0; i < data_len; i++) {
                outBufLen+=sprintf(outBuf+outBufLen,"%02X",msg[pl_start+i]);
              }
              outBufLen+=sprintf(outBuf+outBufLen," - unknown type");
              break;
          }
        }
      }else{
        if (bus_type != BUS_PPS) {
          SerialPrintData(msg);        
        }
//        Serial.println();
//        SerialPrintRAW(msg,msg[len_idx]+bus_type);
        outBufLen+=sprintf(outBuf+outBufLen,"unknown command");
      }
    }
  }
  if (bus_type != BUS_PPS || (bus_type == BUS_PPS && !monitor)) {
    Serial.println();
  }
  if(verbose){
    if (bus_type != BUS_PPS) {
      SerialPrintRAW(msg,msg[len_idx]+bus_type);      
    } else {
      if (msg[0] == 0x17) {
        SerialPrintRAW(msg, 10);
      } else {
        SerialPrintRAW(msg, 9);
      }
    }
    Serial.println();
  }
  return pvalstr;
}

void printPStr(uint32_t outstr, uint16_t outstr_len) {
  int htmlbuflen = 100;
  byte htmllineBuf[htmlbuflen];
  int i = 0;
  for (unsigned int x=0;x<outstr_len-1;x++) {
    htmllineBuf[i] = pgm_read_byte_far(outstr+x);
    i++;
    if (i==htmlbuflen) {
      i=0;
      client.write(htmllineBuf, htmlbuflen);
    }
  }
  //final packet
  if (i > 0) client.write(htmllineBuf, i);
}

/** *****************************************************************
 *  Function:  webPrintHeader()
 *  Does:      Sets up the HTML code to start a web page
 *  Pass parameters:
 *   none
 *  Parameters passed back:
 *   none
 *  Function value returned:
 *   none
 *  Global resources used:
 *   client object
 * *************************************************************** */
void webPrintHeader(void){

  printPStr(pgm_get_far_address(header_html), sizeof(header_html));

#ifdef PASSKEY
  client.print(PASSKEY);
  client.print(F("/"));
#endif
  client.println(F("'>BSB-LAN Web</A></h1></center>"));
  client.print(F("<table width=80% align=center><tr bgcolor=#f0f0f0><td width=20% align=center><a href='/"));
#ifdef PASSKEY
  client.print(PASSKEY);
  client.print(F("/"));
#endif
  client.print(F("K'>" MENU_TEXT_HFK));

  client.print(F("</a></td><td width=20% align=center>"));

  client.print(F("<a href='/"));
#ifdef PASSKEY
  client.print(PASSKEY);
  client.print(F("/"));
#endif
  client.print(F("T'>" MENU_TEXT_SNS "</a>"));

  client.print(F("</td><td width=20% align=center>"));

#ifndef LOGGER
  client.print(F("<font color=#000000>" MENU_TEXT_DLG "</font>"));
#else
  client.print(F("<a href='/"));
#ifdef PASSKEY
  client.print(PASSKEY);
  client.print(F("/"));
#endif
  client.print(F("DG'>" MENU_TEXT_SLG "</a>"));
#endif

  client.print(F("</td><td width=20% align=center>"));

  client.print(F("<a href='/"));
#ifdef PASSKEY
  client.print(PASSKEY);
  client.print(F("/"));
#endif
  client.print(F("Q'>" MENU_TEXT_CHK "</a>"));

  client.println(F("</td></tr>"));
  client.print(F("<tr bgcolor=#f0f0f0><td width=20% align=center>"));

  client.print(F("<a href='/"));
#ifdef PASSKEY
  client.print(PASSKEY);
  client.print(F("/"));
#endif
  client.print(F("C'>" MENU_TEXT_CFG));

  client.print(F("</a></td><td width=20% align=center><a href='http://github.com/fredlcore/bsb_lan/blob/master/command_ref/command_ref_" str(LANG) ".md'>" MENU_TEXT_URL));
  client.print(F("</a></td><td width=20% align=center>"));

  client.print(F("<a href='http://github.com/fredlcore/bsb_lan/blob/master/HOWTO.md' target='new'>" MENU_TEXT_HWT "</a></td><td width=20% align=center><a href='http://github.com/fredlcore/bsb_lan/blob/master/FAQ.md' target='_new'>" MENU_TEXT_FAQ "</a></td>"));
//  client.println(F("<td width=20% align=center><a href='http://github.com/fredlcore/bsb_lan' target='new'>GitHub Repo</a></td>"));
  client.println(F("</tr></table><p></p><table align=center width=80%><tr><td>"));

} // --- webPrintHeader() ---

/** *****************************************************************
 *  Function:  webPrintFooter()
 *  Does:      Sets up the closing HTML code of a web page.
 *  Pass parameters:
 *   none
 *  Parameters passed back:
 *   none
 *  Function value returned:
 *   none
 *  Global resources used:
 *   client object
 * *************************************************************** */
void webPrintFooter(void){
  client.println(F("</td></tr></table>"));
  client.println(F("</body>"));
  client.println(F("</html>"));
  client.println();

} // --- webPrintFooter() ---

/** *****************************************************************
 *  Function:  webPrintSite()
 *  Does:      Sets up HTML code to display a help page.
 *  Pass parameters:
 *   none
 *  Parameters passed back:
 *   none
 *  Function value returned:
 *   none
 *  Global resources used:
 *   client object
 * *************************************************************** */
void webPrintSite() {
  webPrintHeader();

  client.println(F("<p>"));
  client.print(F("BSB-LAN Web, Version "));
  client.print(version);
  client.println(F("<p><b>" MENU_TEXT_HFK ":</b> " MENU_DESC_HFK));
  client.println(F("<p><b>" MENU_TEXT_CFG ":</b> " MENU_DESC_CFG));
  client.println(F("<p><b>" MENU_TEXT_URL ":</b> " MENU_DESC_URL));
  webPrintFooter();
} // --- webPrintSite() ---

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
char *GetDateTime(char date[]){
  sprintf(date,"%02d.%02d.%d %02d:%02d:%02d",day(),month(),year(),hour(),minute(),second());
  date[20] = 0;
  return date;
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
#ifdef LOGGER
void LogTelegram(byte* msg){
  File dataFile;
  char device[5];
  uint32_t cmd;
  int i=0;        // begin with line 0
  int save_i=0;
  boolean known=0;
  uint32_t c;     // command code
  uint8_t type=0;
  uint8_t cmd_type=0;
  double operand=1;
  uint8_t precision=0;
  int data_len;
  double dval;
  uint16_t line = 0;

  if (log_parameters[0] == 30000) {

    if (bus_type != BUS_PPS) {
      if(msg[4+(bus_type*4)]==TYPE_QUR || msg[4+(bus_type*4)]==TYPE_SET || (((msg[2]!=ADDR_ALL && bus_type==BUS_BSB) || (msg[2]<0xF0 && bus_type==BUS_LPB)) && msg[4+(bus_type*4)]==TYPE_INF)) { //QUERY and SET: byte 5 and 6 are in reversed order
        cmd=(uint32_t)msg[6+(bus_type*4)]<<24 | (uint32_t)msg[5+(bus_type*4)]<<16 | (uint32_t)msg[7+(bus_type*4)] << 8 | (uint32_t)msg[8+(bus_type*4)];
      }else{
        cmd=(uint32_t)msg[5+(bus_type*4)]<<24 | (uint32_t)msg[6+(bus_type*4)]<<16 | (uint32_t)msg[7+(bus_type*4)] << 8 | (uint32_t)msg[8+(bus_type*4)];
      }
    } else {
      cmd=msg[1+(msg[0]==0x17 && *PPS_write_enabled != 1)];
    }
    // search for the command code in cmdtbl
    c=get_cmdtbl_cmd(i);
//    c=pgm_read_dword(&cmdtbl[i].cmd);    // extract the command code from line i
    while(c!=CMD_END){
      line=get_cmdtbl_line(i);
      if((bus_type != BUS_PPS && c == cmd) || (bus_type == BUS_PPS && line >= 15000 && (cmd == ((c & 0x00FF0000) >> 16)))) {   // one-byte command code of PPS is stored in bitmask 0x00FF0000 of command ID
        uint8_t dev_fam = get_cmdtbl_dev_fam(i);
        uint8_t dev_var = get_cmdtbl_dev_var(i);
        if ((dev_fam == my_dev_fam || dev_fam == 255) && (dev_var == my_dev_var || dev_var == 255)) {
          if (dev_fam == my_dev_fam && dev_var == my_dev_var) {
            break;
          } else if ((!known && dev_fam!=my_dev_fam) || (dev_fam==my_dev_fam)) { // wider match has hit -> store in case of best match
            known=1;
            save_i=i;
          }
        }
      }
      if (known && c!=cmd) {
        i=save_i;
        break;
      }
      i++;
      c=get_cmdtbl_cmd(i);
//      c=pgm_read_dword(&cmdtbl[i].cmd);
    }

    if ((log_unknown_only == 0 || (log_unknown_only == 1 && known == 0)) && cmd > 0) {
      if (log_bc_only == 0 || (log_bc_only == 1 && ((msg[2]==ADDR_ALL && bus_type==BUS_BSB) || (msg[2]>=0xF0 && bus_type==BUS_LPB)))) {
        dataFile = SD.open("datalog.txt", FILE_WRITE);
        if (dataFile) {
          dataFile.print(millis());
          dataFile.print(F(";"));
          dataFile.print(GetDateTime(date));
          dataFile.print(F(";"));

          if(!known){                          // no hex code match
          // Entry in command table is "UNKNOWN" (0x00000000)
            dataFile.print(F("UNKNOWN"));
          }else{
            // Entry in command table is a documented command code
            line=get_cmdtbl_line(i);
            cmd_type=get_cmdtbl_type(i);
//            uint16_t line=pgm_read_word(&cmdtbl[i].line);
            dataFile.print(line);             // the ProgNr
          }

          uint8_t msg_len = 0;
          if (bus_type != BUS_PPS) {
            dataFile.print(F(";"));
            dataFile.print(TranslateAddr(msg[1+(bus_type*2)], device));
            dataFile.print(F("->"));
            dataFile.print(TranslateAddr(msg[2], device));
            dataFile.print(F(" "));
            dataFile.print(TranslateType(msg[4+(bus_type*4)], device));
            dataFile.print(F(";"));
            msg_len = msg[len_idx]+bus_type;
          } else {
            dataFile.print(F(";"));
            switch (msg[0]) {
              case 0x1D: dataFile.print(F("HEIZ->QAA INF")); break;
              case 0x1E: dataFile.print(F("HEIZ->QAA REQ")); break;
              case 0x17: dataFile.print(F("HEIZ->QAA RTS")); break;
              case 0xFD: dataFile.print(F("QAA->HEIZ ANS")); break;
              default: break;
            }
            dataFile.print(F(";"));
            msg_len = 9+(msg[0]==0x17 && *PPS_write_enabled != 1);
          }

          for(int i=0;i<msg_len;i++){
            if (i > 0) {
              dataFile.print(F(" "));
            }
            if (msg[i] < 16) dataFile.print(F("0"));  // add a leading zero to single-digit values
            dataFile.print(msg[i], HEX);
          }

          // additionally log data payload in addition to raw messages when data payload is max. 32 Bit

          if (bus_type != BUS_PPS && (msg[4+(bus_type*4)] == TYPE_INF || msg[4+(bus_type*4)] == TYPE_SET || msg[4+(bus_type*4)] == TYPE_ANS) && msg[len_idx] < 17+bus_type) {
            dataFile.print(F(";"));
            i=0;
            while(type!=VT_UNKNOWN){
              if(type == cmd_type){
                break;
              }
              i++;
              type=pgm_read_byte_far(pgm_get_far_address(optbl[0].type) + i * sizeof(optbl[0]));
            }
            if (bus_type == BUS_LPB) {
              data_len=msg[1]-14;
            } else {
              data_len=msg[3]-11;
            }
            dval = 0;
            operand=pgm_read_float_far(pgm_get_far_address(optbl[0].operand) + i * sizeof(optbl[0]));
            precision=pgm_read_byte_far(pgm_get_far_address(optbl[0].precision) + i * sizeof(optbl[0]));
            for (i=0;i<data_len-1+bus_type;i++) {
              if (bus_type == BUS_LPB) {
                dval = dval + long(msg[14+i-(msg[8]==TYPE_INF)]<<((data_len-2-i)*8));
              } else {
                dval = dval + long(msg[10+i-(msg[4]==TYPE_INF)]<<((data_len-2-i)*8));
              }
            }
            dval = dval / operand;
/*
            if (precision==0) {
              dataFile.print(int(round(dval)));
            } else {
              char formatstr[6]="%0.0f";
              formatstr[3]=precision;
              dataFile.print(printf("%0.1f",dval));
            }
*/
            int a,b,i;
            if(dval<0){
              dval*=-1.0;
            }
            double rval=10.0;
            for(i=0;i<precision;i++) rval*=10.0;
            dval+=5.0/rval;
            a=(int)(dval);
            rval/=10.0;
            b=(int)(dval*rval - a*rval);
            if(precision==0){
              dataFile.print(a);
            }else{
//              char formatstr[8]="%d.%01d";
//              formatstr[5]='0'+precision;
              dataFile.print(a);
              dataFile.print(",");
              dataFile.print(b);
            }

          }
          dataFile.println();
          dataFile.close();
        }
      }
    }
  }
}
#endif

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
int set(int line      // the ProgNr of the heater parameter
      , const char *val          // the value to set
      , bool setcmd)       // true: SET msg; false: INF msg
{
  byte msg[33];            // we know the maximum length
  byte tx_msg[33];
  int i;
  uint32_t c;              // command code
  uint8_t param[MAX_PARAM_LEN]; // 33 -9 - 2
  uint8_t param_len;

  // Search the command table from the start for a matching line nbr.
  i=findLine(line,0,&c);   // find the ProgNr and get the command code
  if(i<0) return 0;        // no match

  // Check for readonly parameter
  if((get_cmdtbl_flags(i) & FL_RONLY) == FL_RONLY) {
//  if (pgm_read_byte(&cmdtbl[i].flags) == 1) {
    Serial.println(F("Parameter is readonly!"));
    return 2;   // return value for trying to set a readonly parameter
  }

  if (bus_type == BUS_PPS && line >= 15000) {  // PPS-Bus set parameter
    int cmd_no = line - 15000;
    uint8_t type=get_cmdtbl_type(i);

    switch (type) {
      case VT_TEMP: pps_values[cmd_no] = atof(val) * 64; break;
      case VT_HOUR_MINUTES:
      {
        uint8_t h=atoi(val);
        uint8_t m=0;
        while(*val!='\0' && *val!=':' && *val!='.') val++;
        if(*val==':' || *val=='.'){
          val++;
          m=atoi(val);
        }
        pps_values[cmd_no] = h * 6 + m / 10;
        break;
      }
      default: pps_values[cmd_no] = atoi(val); break;
    }
//    if (atof(p) != pps_values[cmd_no] && cmd_no >= PPS_TWS && cmd_no <= PPS_BRS && cmd_no != PPS_RTI) {
    if (cmd_no >= PPS_TWS && cmd_no <= PPS_BRS && cmd_no != PPS_RTI) {
      Serial.print(F("Writing EEPROM slot "));
      Serial.print(cmd_no);
      Serial.print(F(" with value "));
      Serial.println(pps_values[cmd_no]);
      EEPROM.put(sizeof(uint16_t)*cmd_no, pps_values[cmd_no]);
    }
    return 1;
  }

  // Get the parameter type from the table row[i]
  switch(get_cmdtbl_type(i)) {
//  switch(pgm_read_byte(&cmdtbl[i].type)){
    // ---------------------------------------------
    // 8-bit unsigned integer representation
    // Months or minutes
    // No input values sanity check
    case VT_MONTHS: //(Wartungsintervall)
    case VT_MINUTES_SHORT: // ( Fehler - Alarm)
    case VT_PERCENT:
      {
      if(val[0]!='\0'){
        uint8_t t=atoi(val);
        param[0]=0x06;  //enable
        param[1]=t;
      }else{
        param[0]=0x05;  // disable
        param[1]=0x00;
      }
      param_len=2;
      }
      break;

    // ---------------------------------------------
    // 8-bit unsigned integer representation
    // All enumeration (list) types
    // No input values sanity check
    case VT_ENUM:          // enumeration types
    case VT_ONOFF: // 1 = On                      // on = Bit 0 = 1 (i.e. 1=on, 3=on... 0=off, 2=off etc.)
    case VT_CLOSEDOPEN: // 1 = geschlossen
    case VT_YESNO: // 1 = Ja
    case VT_WEEKDAY: // (1=Mo..7=So)
    case VT_DAYS: // (Legionellenfkt. Periodisch)
    case VT_HOURS_SHORT: // (Zeitkonstante Gebäude)
    case VT_BIT:
    case VT_BYTE:
    case VT_TEMP_SHORT:
      {
      uint8_t t=atoi(val);
      param[0]=0x01;  //enable
      param[1]= t;
      param_len=2;
      }
      break;

    // ---------------------------------------------
    // 16-bit unsigned integer representation
    // Example: Brennerstarts Intervall/Brennerstarts seit Wartung
    // No input values sanity check
    case VT_UINT:
    case VT_SINT:
    case VT_PERCENT_WORD1:
    case VT_HOURS_WORD: // (Brennerstunden Intervall - nur durch 100 teilbare Werte)
    case VT_MINUTES_WORD: // (Legionellenfunktion Verweildauer)
      {
      if(val[0]!='\0'){
        uint16_t t=atoi(val);
        param[0]=0x06;  //enable
        param[1]=(t >> 8);
        param[2]= t & 0xff;
      }else{
        param[0]=0x05;  // disable
        param[1]=0x00;
        param[2]=0x00;
      }
      param_len=3;
      }
      break;

    case VT_UINT5:
      {
      if(val[0]!='\0'){
        uint16_t t=atoi(val)/5;
        param[0]=0x06;  //enable
        param[1]=(t >> 8);
        param[2]= t & 0xff;
      }else{
        param[0]=0x05;  // disable
        param[1]=0x00;
        param[2]=0x00;
      }
      param_len=3;
      }
      break;

    case VT_UINT10:
      {
      if(val[0]!='\0'){
        uint16_t t=atoi(val)*10;
        param[0]=0x06;  //enable
        param[1]=(t >> 8);
        param[2]= t & 0xff;
      }else{
        param[0]=0x05;  // disable
        param[1]=0x00;
        param[2]=0x00;
      }
      param_len=3;
      }
      break;

    // ---------------------------------------------
    // 16-bit unsigned integer representation
    // Temperature values
    case VT_TEMP_WORD:
      {
      uint16_t t=atoi(val);     // TODO: Isn't VT_TEMP_WORD a signed number?
      if(val[0]!='\0'){
        param[0]=0x01;
        param[1]=(t >> 8);
        param[2]= t & 0xff;
      }                         // TODO: Do we need a disable section here as well?
      param_len=3;
      }
      break;

    // ---------------------------------------------
    // 32-bit unsigned integer representation
    case VT_DWORD:
      {
      if(val[0]!='\0'){
        uint32_t t = (uint32_t)strtoul(val, NULL, 10);
        param[0]=0x06;  //enable
        param[1]=(t >> 24) & 0xff;
        param[2]=(t >> 16) & 0xff;
        param[3]=(t >> 8) & 0xff;
        param[4]= t & 0xff;
      }else{
        param[0]=0x05;  // disable
        param[1]=0x00;
        param[2]=0x00;
        param[3]=0x00;
        param[4]=0x00;
      }
      param_len=5;
      }
      break;

    case VT_UINT100:
      {
      if(val[0]!='\0'){
        uint32_t t=atoi(val) * 100;
        param[0]=0x06;  //enable
        param[1]=(t >> 24) & 0xff;
        param[2]=(t >> 16) & 0xff;
        param[3]=(t >> 8) & 0xff;
        param[4]= t & 0xff;
      }else{
        param[0]=0x05;  // disable
        param[1]=0x00;
        param[2]=0x00;
        param[3]=0x00;
        param[4]=0x00;
      }
      param_len=5;
      }
      break;

    // ---------------------------------------------
    // 8-bit unsigned integer representation
    // No input values sanity check
    case VT_HOUR_MINUTES: //TODO test it
      {
      if(val[0]!='\0'){
        uint8_t h=atoi(val);
        uint8_t m=0;
        while(*val!='\0' && *val!=':' && *val!='.') val++;
        if(*val==':' || *val=='.'){
          val++;
          m=atoi(val);
        }
        param[0]=0x06;  //enable
        param[1]= h;
        param[2]= m;
      }else{
        param[0]=0x05;  // disable
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
      if(setcmd){
        param[0]=0x01;
        param[1]=(t >> 8);
        param[2]= t & 0xff;
      }else{ // INF message type (e.g. for room temperature)
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
      {
      uint16_t t=atof(val)*64.0;
      if(setcmd){
        param[0]=0x01;
        param[1]=(t >> 8);
        param[2]= t & 0xff;
      }else{ // INF message type (e.g. for room temperature)
        param[0]=(t >> 8);
        param[1]= t & 0xff;
        param[2]=0x00;
      }
      param_len=3;
      }
      break;
    case VT_TEMP_SHORT5_US:
    case VT_TEMP_SHORT5:
    case VT_PERCENT5:
      {
      if(val[0]!='\0'){
        uint8_t t=atof(val);
        param[0]=0x01;  //enable
        param[1]=t*2;
      }
      param_len=2;
      }
      break;
    case VT_TEMP_SHORT64:
      {
      if(val[0]!='\0'){
        uint8_t t=atof(val);
        param[0]=0x01;  //enable
        param[1]=t*64;
      }
      param_len=2;
      }
      break;

    case VT_PERCENT_100:
      {
      uint16_t t=atof(val)*100.0;
      param[0]=0x01;
      param[1]=(t >> 8);
      param[2]= t & 0xff;
      param_len=3;
      }
      break;

    case VT_PERCENT_WORD:
      {
      uint16_t t=atof(val)*2.0;
      param[0]=0x01;
      param[1]=(t >> 8);
      param[2]= t & 0xff;
      param_len=3;
      }
      break;

    // ---------------------------------------------
    // 2-byte floating point representation
    // Example: Kennlinie Steilheit, mult=50
    // No input values sanity check
    case VT_FP02:
      {
      uint16_t t=atof(val)*50.0;
      param[0]=0x01;
      param[1]=(t >> 8);
      param[2]= t & 0xff;
      param_len=3;
      }
      break;
    // ---------------------------------------------
    // 8-bit unsigned integer representation
    // Example: pressure value, mult=10
    // No input values sanity check
    case VT_PRESSURE:
      {
      uint8_t t=atof(val)*10.0;
      param[0]=0x01;
      param[1]= t;
      param_len=2;
      }
      break;

    // ---------------------------------------------
    // 32-bit unsigned integer representation
    // Minutes, mult=60
    // Example: HK1 - Einschaltoptimierung
    // No input values sanity check
    case VT_MINUTES:
      {
      uint32_t t=atoi(val)*60;
      param[0]=0x01;
      param[1]=(t >> 24) & 0xff;
      param[2]=(t >> 16) & 0xff;
      param[3]=(t >> 8) & 0xff;
      param[4]= t & 0xff;
      param_len=5;
      }
      break;

    case VT_SECONDS_WORD5:
    case VT_TEMP_WORD5_US:
      {
      uint16_t t=atoi(val)*2;
      if(val[0]!='\0'){
        param[0]=0x01;
        param[1]=(t >> 8);
        param[2]= t & 0xff;
      }                         // TODO: Do we need a disable section here as well?
      param_len=3;
      }
      break;

    case VT_SECONDS_SHORT4:
      {
      if(val[0]!='\0'){
        uint8_t t=atof(val);
        param[0]=0x01;  //enable
        param[1]=t*4;
      }
      param_len=2;
      }
      break;

    case VT_SECONDS_SHORT5:
      {
      if(val[0]!='\0'){
        uint8_t t=atof(val);
        param[0]=0x01;  //enable
        param[1]=t*5;
      }
      param_len=2;
      }
      break;

    // ---------------------------------------------
    // Schedule data
    case VT_DATETIME: // Has to be sent as INF command as well as a broadcast (destination 127 / 0x7F)
      {
      // I0=dd.mm.yyyy_mm:hh:ss!127
      // date and time are transmitted as INF message by the display unit
      // DISP->ALL  INF    0 Uhrzeit und Datum -  Datum/Zeit: 30.01.2015 23:17:00
      // DC 8A 7F 14 02 05 00 00 6C 00 73 01 1E 05 17 11 00 00 A1 AB
      int d,m,y,min,hour,sec;
      // The caller MUST provide six values for an event
      if(6!=sscanf(val,"%d.%d.%d_%d:%d:%d",&d,&m,&y,&hour,&min,&sec)) {
        Serial.println(F("Too few/many arguments for date/time!"));
        return 0;
      }

      // Send to the PC hardware serial interface (DEBUG)
      Serial.print(F("date time: "));
      Serial.print(d);
      Serial.print(F("."));
      Serial.print(m);
      Serial.print(F("."));
      Serial.print(y);
      Serial.print(F(" "));
      Serial.print(hour);
      Serial.print(F(":"));
      Serial.print(min);
      Serial.print(F(":"));
      Serial.println(sec);

      // Set up the command payload
      //outBufLen+=sprintf(outBuf+outBufLen,"%02d.%02d.%d %02d:%02d:%02d",msg[12],msg[11],msg[10]+1900,msg[14],msg[15],msg[16]);
      param[0]=0x01;
      param[1]=y-1900;
      param[2]=m;
      param[3]=d;
      param[4]=dayofweek(d,m,y);
      param[5]=hour;
      param[6]=min;
      param[7]=sec;
      param[8]=0;
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
      int ret;
      ret=sscanf(val,"%d:%d-%d:%d_%d:%d-%d:%d_%d:%d-%d:%d",&h1s,&m1s,&h1e,&m1e,&h2s,&m2s,&h2e,&m2e,&h3s,&m3s,&h3e,&m3e);
      // we need at least the first period
      if(ret<4)      // BEGIN hour/minute and END hour/minute
        return 0;
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
    // Define day/month BEGIN and END dates for vacation periods
    case VT_VACATIONPROG:
      //DISP->HEIZ SET      3D0509C6 06 00 02 0A 00 00 00 00 17
      //outBufLen+=sprintf(outBuf+outBufLen,"%02d.%02d",msg[12],msg[11]);
      param[1]=0;
      param[2]=0;
      param[3]=0;
      param[4]=0;
      param[5]=0;
      param[6]=0;
      param[7]=0;
      param[8]=0x17; //?
      param_len=9;
      if(val[0]!='\0'){
          int d,m;
          if(2!=sscanf(val,"%d.%d.",&d,&m))
            return 0;      // incomplete input data
          param[0]=0x06;   // flag = enabled
          param[2]=m;
          param[3]=d;
      }else{
          param[0]=0x05;   // flag = disabled
      }
      break;
    // ---------------------------------------------
    case VT_SUMMERPERIOD: // TODO do we have to send INF or SET command?
      {
    // Sommerzeit scheint im DISP gehandelt zu werden
    // Bei Anzeige werden keine Werte abgefragt. Bei Änderung wird ein INF geschickt.
    // Sommerzeit Beginn 25.3. DISP->ALL  INF      0500009E 00 FF 03 19 FF FF FF FF 16
    // Sommerzeit Ende 25.11. DISP->ALL  INF      0500009D 00 FF 0B 19 FF FF FF FF 16
      int d,m;
      if(2!=sscanf(val,"%d.%d",&d,&m))
        return 0;
      param[0]=0;
      param[1]=0xff;
      param[2]=m;
      param[3]=d;
      param[4]=0xff;
      param[5]=0xff;
      param[6]=0xff;
      param[7]=0xff;
      param[8]=0x17; //?
      param_len=9;
      }
      break;

    case VT_CUSTOM_ENUM:
    {
      uint8_t t=atoi(val);
      bus.Send(TYPE_QINF, c, msg, tx_msg);
      int data_len;
      if (bus_type == BUS_LPB) {
        data_len=msg[len_idx]-14;     // get packet length, then subtract
      } else {
        data_len=msg[len_idx]-11;     // get packet length, then subtract
      }

      if (data_len > 18) {
        Serial.print(F("Set failed, invalid data length: "));
        Serial.println(data_len);
        return 0;
      }

      uint16_t enumstr_len=get_cmdtbl_enumstr_len(i);
      uint_farptr_t enumstr_ptr = calc_enum_offset(get_cmdtbl_enumstr(i), enumstr_len);
      uint8_t idx = pgm_read_byte_far(enumstr_ptr+0);

      for (int x=pl_start;x<pl_start+data_len;x++) {
        param[x-pl_start] = msg[x];
      }
      param[idx] = t;
      param_len = data_len;
      break;
    }
    // ---------------------------------------------
    case VT_HOURS: // (read only)
    case VT_VOLTAGE: // read only (Ein-/Ausgangstest)
    case VT_LPBADDR: // read only (LPB-System - Aussentemperaturlieferant)
    case VT_PRESSURE_WORD: // read only (Diagnose Verbraucher)
    case VT_FP1: // read only (SW-Version)
    case VT_ERRORCODE: // read only
    case VT_UNKNOWN:
    default:
      Serial.println(F("Unknown type or read-only parameter"));
      return 2;
    break;
  } // endswitch

  // Send a message to PC hardware serial port
  Serial.print(F("setting line: "));
  Serial.print(line);
  Serial.print(F(" val: "));
  SerialPrintRAW(param,param_len);
  Serial.println();

  uint8_t t=setcmd?TYPE_SET:TYPE_INF;

  // Send telegram to the bus
  if(!bus.Send(t           // message type
             , c           // command code
             , msg         // receive buffer
             , tx_msg      // xmit buffer
             , param       // payload
             , param_len   // payload length
             , setcmd))    // wait_for_reply
  {
    Serial.println(F("set failed"));
    return 0;
  }

  // Decode the xmit telegram and send it to the PC serial interface
  if(verbose) {
    printTelegram(tx_msg, line);
#ifdef LOGGER
    LogTelegram(tx_msg);
#endif
  }

  // no answer for TYPE_INF
  if(t!=TYPE_SET) return 1;

  // Decode the rcv telegram and send it to the PC serial interface
  printTelegram(msg, line);
#ifdef LOGGER
  LogTelegram(msg);
#endif

  // Expect an acknowledgement to our SET telegram
  if(msg[4+(bus_type*4)]!=TYPE_ACK){      // msg type at 4 (BSB) or 8 (LPB)
    Serial.println(F("set failed NACK"));
    return 0;
  }

  return 1;
} // --- set() ---

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
 * *************************************************************** */
char* query(int line_start  // begin at this line (ProgNr)
          , int line_end    // end with this line (ProgNr)
          , boolean no_print)    // display in web client?
{
  byte msg[33] = { 0 };      // response buffer
  byte tx_msg[33] = { 0 };   // xmit buffer
  uint32_t c;        // command code
  int line;     // ProgNr
  int i=0;
  int idx=0;
  int retry;
  char *pvalstr=NULL;

  if (!no_print) {         // display in web client?
//    client.println(F("<p><form><table>")); // yes, begin HTML paragraph
  }
  for(line=line_start;line<=line_end;line++){
    outBufclear();
    i=findLine(line,idx,&c);

    if(i>=0){
      idx=i;
      uint8_t flags = get_cmdtbl_flags(i);
      uint8_t type = get_cmdtbl_type(i);
      //Serial.println(F("found"));
      if(c!=CMD_UNKNOWN && (flags & FL_NO_CMD) != FL_NO_CMD) {     // send only valid command codes
        if (bus_type != BUS_PPS) {  // bus type is not PPS
          retry=QUERY_RETRIES;
          while(retry){
            uint8_t query_type = TYPE_QUR;
            if (type == VT_CUSTOM_ENUM) {
              query_type = TYPE_QINF;
            }
            if(bus.Send(query_type, c, msg, tx_msg)){

              // Decode the xmit telegram and send it to the PC serial interface
              if(verbose) {
                printTelegram(tx_msg, line);
#ifdef LOGGER
                LogTelegram(tx_msg);
#endif
              }

              // Decode the rcv telegram and send it to the PC serial interface
              pvalstr=printTelegram(msg, line);
#ifdef LOGGER
              LogTelegram(msg);
#endif
              break;   // success, break out of while loop
            }else{
              Serial.println(F("query failed"));
              retry--;          // decrement number of attempts
            }
          } // endwhile, maximum number of retries reached
          if(retry==0) {
            if (bus_type == 1 && msg[8] == TYPE_ERR) {    // only for BSB because some LPB systems do not really send proper error messages
              outBufLen+=sprintf(outBuf+outBufLen,"error %d",msg[9]);
            } else {
              outBufLen+=sprintf(outBuf+outBufLen,"%d query failed",line);
            }
          }
        } else { // bus type is PPS

          uint32_t cmd = get_cmdtbl_cmd(i);
//          uint8_t type = get_cmdtbl_type(i);
          uint16_t temp_val = 0;
          switch (type) {
//            case VT_TEMP: temp_val = pps_values[(c & 0xFF)] * 64; break:
            case VT_BYTE: temp_val = pps_values[(line-15000)] * 256; break;
            case VT_ONOFF: temp_val = pps_values[(line-15000)] * 256; break;
            case VT_HOUR_MINUTES: temp_val = ((pps_values[line-15000] / 6) * 256) + ((pps_values[line-15000] % 6) * 10); break;
            default: temp_val = pps_values[(line-15000)]; break;
          }

          msg[1] = ((cmd & 0x00FF0000) >> 16);
          msg[4+(bus_type*4)]=TYPE_ANS;
          msg[pl_start+1]=temp_val >> 8;
          msg[pl_start+2]=temp_val & 0xFF;
/*
          msg[5] = c >> 24;
          msg[6] = c >> 16 & 0xFF;
          msg[7] = c >> 8 & 0xFF;
          msg[8] = c & 0xFF;
*/
          pvalstr = printTelegram(msg, line);
        }
      }else{
        //Serial.println(F("unknown command"));
        //if(line_start==line_end) outBufLen+=sprintf(outBuf+outBufLen,"%d unknown command",line);
      } // endelse, valid / invalid command codes
    }else{
      //Serial.println(F("line not found"));
      //if(line_start==line_end) outBufLen+=sprintf(outBuf+outBufLen,"%d line not found",line);
    } // endelse, line (ProgNr) found / not found
    
    if(outBufLen>0){
      if (!no_print) {  // display result in web client
        if (msg[4+(bus_type*4)] == TYPE_ERR) {
#ifdef HIDE_UNKNOWN
          continue;
#endif
          client.println(F("<tr style='color: #7f7f7f'><td>"));
        } else {
          client.println(F("<tr><td>"));
        }
        client.println(outBuf);

        double num_pvalstr = strtod(pvalstr, NULL);
        uint8_t flags = get_cmdtbl_flags(i);
        uint8_t type = get_cmdtbl_type(i);
        uint16_t enumstr_len = get_cmdtbl_enumstr_len(i);
        uint32_t enumstr = calc_enum_offset(get_cmdtbl_enumstr(i), enumstr_len);
        int data_len;
        if (bus_type == BUS_LPB) {
          data_len=msg[len_idx]-14;     // get packet length, then subtract
        } else {
          data_len=msg[len_idx]-11;     // get packet length, then subtract
        }

/*
        // dump data payload for unknown types
        if (type == VT_UNKNOWN && msg[4+(bus_type*4)] != TYPE_ERR) {
          int data_len;
          if (bus_type == BUS_LPB) {
            data_len=msg[len_idx]-14;     // get packet length, then subtract
          } else {
            data_len=msg[len_idx]-11;     // get packet length, then subtract
          }
          for (i=0;i<=data_len-1;i++) {
            if (msg[pl_start+i] < 16) client.print(F("0"));  // add a leading zero to single-digit values
            client.print(msg[pl_start+i], HEX);
          }
        }
*/
        client.println(F("</td><td>"));
        if (msg[4+(bus_type*4)] != TYPE_ERR && type != VT_UNKNOWN) {
          if(type == VT_ENUM || type == VT_CUSTOM_ENUM || type == VT_BIT || type == VT_ONOFF) {

            client.print(F("<select "));
            if (type == VT_BIT) {
              client.print(F("multiple "));
            }
            client.print(F("id='value"));
            client.print(line);
            client.println(F("'>"));
            if (type == VT_ONOFF) {
              uint8_t pps_offset = (bus_type == BUS_PPS && *PPS_write_enabled != 1 && msg[0] != 0);
              int val=msg[pl_start+1+pps_offset];
              client.print(F("<option value='0'"));
              if (val==0) {
                client.print(F(" selected"));
              }
              client.println(F(">" MENU_TEXT_OFF "</option>"));
              client.print(F("<option value='1'"));
              if (val>0) {
                client.print(F(" selected"));
              }
              client.println(F(">" MENU_TEXT_ON "</option>"));
            } else {
//              memcpy_PF(buffer, enumstr, enumstr_len);
//              buffer[enumstr_len]=0;
              uint16_t val;
              uint16_t c=0;
              uint8_t bitmask=0;
              while(c<enumstr_len){
                if((byte)(pgm_read_byte_far(enumstr+c+1))!=' ' || type == VT_BIT){         // ENUMs must not contain two consecutive spaces! Necessary because VT_BIT bitmask may be 0x20 which equals space
                  val=uint16_t((pgm_read_byte_far(enumstr+c) << 8)) | uint16_t(pgm_read_byte_far(enumstr+c+1));
                  if (type == VT_BIT) {
                    bitmask = val & 0xff;
                    val = val >> 8 & 0xff;
                  }
                  if (type == VT_CUSTOM_ENUM) {
                    val=uint16_t(pgm_read_byte_far(enumstr+c+1));
                  }
                  c++;
                }else{
                  val=uint16_t(pgm_read_byte_far(enumstr+c));
                }
                //skip leading space
                c+=2;

                sprintf(outBuf,"%s",strcpy_PF(buffer, enumstr+c));
                client.print(F("<option value='"));
                client.print(val);
                if ( ((type == VT_ENUM || type == VT_CUSTOM_ENUM) && num_pvalstr == val) || (type == VT_BIT && (msg[10+(bus_type*3)+data_len-2] & bitmask) == (val & bitmask)) ) {
                  client.print(F("' SELECTED>"));
                } else {
                  client.print(F("'>"));
                }
                client.print(outBuf);
                client.println(F("</option>"));
  
                while(pgm_read_byte_far(enumstr+c)!=0) c++;
                c++;
              }
            }

            client.print(F("</select></td><td>"));
            if ((flags & FL_RONLY) != FL_RONLY) {
              client.print(F("<input type=button value='Set' onclick=\"set"));
              if (type == VT_BIT) {
                client.print(F("bit"));
              }
              client.print(F("("));
              client.print(line);
              client.print(F(")\">"));
            }
          } else {
            client.print(F("<input type=text id='value"));
            client.print(line);
            client.print(F("' VALUE='"));

/*
            char* colon_pos = strchr(pvalstr,':');
            if (colon_pos!=0) {
              *colon_pos = '.';
            }
*/
            if (type == VT_HOUR_MINUTES) {
              client.print(pvalstr);              
            } else {
              client.print(strtod(pvalstr,NULL));
            }
            client.print(F("'></td><td>"));
            if ((flags & FL_RONLY) != FL_RONLY) {
              client.print(F("<input type=button value='Set' onclick=\"set("));
              client.print(line);
              client.print(F(")\">"));
            }
          }
        }
        client.println(F("</td></tr>"));
      }
    } // endif, outBufLen > 0
  } // endfor, for each valid line (ProgNr) command within selected range

  // TODO: check at least for data length (only used for temperature values)
  /*
  int data_len=msg[3]-11;
  if(data_len==3){
    returnval = printFIXPOINT(msg,data_len,64.0,1,"");
  }
  */
  return pvalstr;
} // --- query() ---

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
  if (fixed_device_family < 1) {
    my_dev_fam = strtod(query(6225,6225,1),NULL);
    my_dev_var = strtod(query(6226,6226,1),NULL);
  } else {
    my_dev_fam = fixed_device_family;
    my_dev_var = fixed_device_variant;
  }
/*
  int i=0;
  family=pgm_read_byte_far(pgm_get_far_address(dev_tbl[0].dev_family) + i * sizeof(dev_tbl[0]));
  while(family!=DEV_NONE){
    if(family == device_id){
      known=1;
      break;
    }
    i++;
    family=pgm_read_byte_far(pgm_get_far_address(dev_tbl[0].dev_family) + i * sizeof(dev_tbl[0]));
  }
  if (!known){
    Serial.print(F("Your device family no. "));
    Serial.print(device_id);
    Serial.println(F(" is not yet known to BSB-LAN. Certain parameters will be disabled."));
    Serial.println(F("Please inform the maintainers of this software about your device family by sending your device family no. as well as the exact name of your heating system, so your system can be added to the list of known systems."));
    dev_id=DEV_ALL;
  } else {
    dev_id=pgm_read_dword_far(pgm_get_far_address(dev_tbl[0].dev_bit_id) + i * sizeof(dev_tbl[0]));
  }
*/
  Serial.print(F("Device family: "));
  Serial.println(my_dev_fam);
  Serial.print(F("Device variant: "));
  Serial.println(my_dev_var);
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
void SetDateTime(){
  byte rx_msg[33];      // response buffer
  byte tx_msg[33];   // xmit buffer
  uint32_t c;        // command code

  findLine(0,0,&c);
  if(c!=CMD_UNKNOWN){     // send only valid command codes
    if(bus.Send(TYPE_QUR, c, rx_msg, tx_msg)){
      if (bus_type == BUS_LPB) {
        setTime(rx_msg[18], rx_msg[19], rx_msg[20], rx_msg[16], rx_msg[15], rx_msg[14]+1900);
      } else {
        setTime(rx_msg[14], rx_msg[15], rx_msg[16], rx_msg[12], rx_msg[11], rx_msg[10]+1900);
      }
    }
  }
}

#ifdef DHT_BUS

/** *****************************************************************
 *  Function:  dht22()
 *  Does:      Reads a DHT22 sensor
 *  Pass parameters:
 *   none
 *  Parameters passed back:
 *   none
 *  Function value returned:
 *   none
 *  Global resources used:
 *    DHT_Pins  array with pins to use
 *    outBuf[]
 *    Serial   the hardware serial interface to a PC
 *    DHT  class which handles sensors
 *    client object
 * *************************************************************** */
void dht22(void) {
  int i;
  Serial.println(F("start request values"));
  int numDHTSensors = sizeof(DHT_Pins) / sizeof(int);
  Serial.print(F("DHT22 sensors: "));
  Serial.println(numDHTSensors);
    outBufclear();
    for(i=0;i<numDHTSensors;i++){

    int chk = DHT.read22(DHT_Pins[i]);
    switch (chk) {
      case DHTLIB_OK:  
      Serial.print(F("OK,\t")); 
      break;
      case DHTLIB_ERROR_CHECKSUM: 
      Serial.print(F("Checksum error,\t")); 
      break;
      case DHTLIB_ERROR_TIMEOUT: 
      Serial.print(F("Time out error,\t")); 
      break;
      default: 
      Serial.print(F("Unknown error,\t")); 
      break;
    }

    double hum = DHT.humidity;
    double temp = DHT.temperature;
    Serial.println(F("end request values"));
    Serial.print(F("temp["));
    Serial.print(i);
    Serial.print(F("]: "));
    Serial.print(temp);
    Serial.print(F(", hum["));
    Serial.print(i);
    Serial.print(F("]: "));
    Serial.println(hum);
    if (hum > 0 && hum < 101) {
      outBufLen+=sprintf(outBuf+outBufLen,"<tr><td>\ntemp[%d]: ",i);
      _printFIXPOINT(temp,2);
      outBufLen+=sprintf(outBuf+outBufLen," &deg;C\n</td></tr>\n<tr><td>\n");
      outBufLen+=sprintf(outBuf+outBufLen,"hum[%d]: ",i);
      _printFIXPOINT(hum,2);
      outBufLen+=sprintf(outBuf+outBufLen," &#037;\n</td></tr>\n<tr><td>\n");
      outBufLen+=sprintf(outBuf+outBufLen,"abs_hum[%d]: ",i);
      _printFIXPOINT((216.7*(hum/100.0*6.112*exp(17.62*temp/(243.12+temp))/(273.15+temp))),2);
      outBufLen+=sprintf(outBuf+outBufLen," g/m<sup>3</sup>\n</td></tr>\n");
    }
  }
  client.println(outBuf);  
}
#endif  //ifdef DHT_BUS

#ifdef ONE_WIRE_BUS

/** *****************************************************************
 *  Function:  ds18b20()
 *  Does:      Reads a DS18B20 temperature sensor
 *  Pass parameters:
 *   none
 *  Parameters passed back:
 *   none
 *  Function value returned:
 *   none
 *  Global resources used:
 *    int numSensors
 *    outBuf[]
 *    Serial   the hardware serial interface to a PC
 *    sensors  class which handles sensors
 *    client object
 * *************************************************************** */
void ds18b20(void) {
  int i;
  //webPrintHeader();
  Serial.println(F("start requestTemperatures"));
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println(F("end requestTemperatures"));
  Serial.println(F("start getTempCByIndex"));
  outBufclear();
  for(i=0;i<numSensors;i++){
    float t=sensors.getTempCByIndex(i);
    Serial.print(F("temp["));
    Serial.print(i);
    Serial.print(F("]: "));
    Serial.print(t);
    Serial.println();

    outBufLen+=sprintf(outBuf+outBufLen,"<tr><td>\ntemp[%d]: ",i);
    _printFIXPOINT(t,2);
    outBufLen+=sprintf(outBuf+outBufLen," &deg;C\n</td></tr>\n");
  }
  client.println(outBuf);
  //webPrintFooter();
} // --- ds18b20() ---
#endif   // ifdef ONE_WIRE_BUS

char *lookup_descr(uint16_t line) {
  int i=findLine(line,0,NULL);
  if (i<0) {                    // Not found (for this heating system)?
    strcpy_P(buffer, STR99999); // Unknown command has line no. 10999
  } else {
    strcpy_PF(buffer, get_cmdtbl_desc(i));
//  strcpy_P(buffer, (char*)pgm_read_word(&(cmdtbl[i].desc)));
  }
  return buffer;
}

#ifdef IPWE

/*************************** IPWE Extension **************************************/
/** *****************************************************************
 *  Function:  Ipwe()
 *  Does:      Sets up HTML code to display a table with sensor readings.
 *             Queries several controller parameters addressed by their
 *             line (ProgNr) and the LED0 output pin.
 *  Pass parameters:
 *   none
 *  Parameters passed back:
 *   none
 *  Function value returned:
 *   none
 *  Global resources used:
 *    numSensors
 *    client object
 *    led0   output pin 3
 * *************************************************************** */
void Ipwe() {
  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: text/html"));
  client.println();

  int i;
  int counter = 0;
  int numIPWESensors = sizeof(ipwe_parameters) / sizeof(int);
  Serial.print(F("IPWE sensors: "));
  Serial.println(numIPWESensors);
  double ipwe_sensors[numIPWESensors];
  for (i=0; i < numIPWESensors; i++) {
    ipwe_sensors[i] = strtod(query(ipwe_parameters[i],ipwe_parameters[i],1),NULL);
  }

  client.print(F("<html><body><form><table border=1><tbody><tr><td>Sensortyp</td><td>Adresse</td><td>Beschreibung</td><td>Temperatur</td><td>Luftfeuchtigkeit</td><td>Windgeschwindigkeit</td><td>Regenmenge</td></tr>"));
  for (i=0; i < numIPWESensors; i++) {
    counter++;
    client.print(F("<tr><td>T<br></td><td>"));
    client.print(counter);
    client.print(F("<br></td><td>"));
    client.print(lookup_descr(ipwe_parameters[i]));
    client.print(F("<br></td><td>"));
    client.print(ipwe_sensors[i]);
    client.print(F("<br></td><td>0<br></td><td>0<br></td><td>0<br></td></tr>"));
  }

  for (int i=0; i<numAverages; i++) {
    if (avg_parameters[i] > 0) {
      counter++;
      client.print(F("<tr><td>T<br></td><td>"));
      client.print(counter);
      client.print(F("<br></td><td>"));
      client.print(F("Avg"));
      client.print(lookup_descr(avg_parameters[i]));            
      client.print(F("<br></td><td>"));
      double rounded = round(avgValues[i]*10);
      client.println(rounded/10);
// TODO: extract and display unit text from cmdtbl.type
      client.print(F("<br></td><td>0<br></td><td>0<br></td><td>0<br></td></tr>"));
    }
  }

#ifdef ONE_WIRE_BUS
  // output of one wire sensors
  sensors.requestTemperatures();
  DeviceAddress device_address;
  char device_ascii[17];
  for(i=0;i<numSensors;i++){
    counter++;
    double t=sensors.getTempCByIndex(i);
    sensors.getAddress(device_address, i);
    sprintf(device_ascii, "%02x%02x%02x%02x%02x%02x%02x%02x",device_address[0],device_address[1],device_address[2],device_address[3],device_address[4],device_address[5],device_address[6],device_address[7]);

    client.print(F("<tr><td>T<br></td><td>"));
    client.print(counter);
    client.print(F("<br></td><td>"));
    client.print(device_ascii);
    client.print(F("<br></td><td>"));
    client.print(t);
    client.print(F("<br></td><td>0<br></td><td>0<br></td><td>0<br></td></tr>"));
  }
#endif

#ifdef DHT_BUS
  // output of DHT sensors
  int numDHTSensors = sizeof(DHT_Pins) / sizeof(int);
  for(i=0;i<numDHTSensors;i++){
    DHT.read22(DHT_Pins[i]);
    
    double hum = DHT.humidity;
    double temp = DHT.temperature;
    if (hum > 0 && hum < 101) {
      counter++;
      client.print(F("<tr><td>T<br></td><td>"));
      client.print(counter);
      client.print(F("<br></td><td>"));
      client.print(F("DHT sensor "));
      client.print(i+1);
      client.print(F(" temperature"));
      client.print(F("<br></td><td>"));
      client.print(temp);
      client.print(F("<br></td><td>0<br></td><td>0<br></td><td>0<br></td></tr>"));
      counter++;
      client.print(F("<tr><td>F<br></td><td>"));
      client.print(counter);
      client.print(F("<br></td><td>"));
      client.print(F("DHT sensor "));
      client.print(i+1);
      client.print(F(" humidity"));
      client.print(F("<br></td><td>0<br></td><td>"));
      client.print(hum);
      client.print(F("<br></td><td>0<br></td><td>0<br></td></tr>"));
    }
  }
#endif

  client.print(F("</tbody></table></form>"));
} 

#endif    // --- Ipwe() ---

/** *****************************************************************
 *  Function: InitMaxDeviceList()
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

#ifdef MAX_CUL
void InitMaxDeviceList() {
  
  char max_id[11] = { 0 };
  char max_id_eeprom[11] = { 0 };
  int32_t max_addr = 0;
  for (uint32_t x=0;x<(sizeof(max_device_list)/10);x++) {
    for (int y=0;y<10;y++) {
      max_id[y] = pgm_read_byte_far(pgm_get_far_address(max_device_list)+(x*10)+y);
    }
    for (int z=0;z<20;z++) {
      EEPROM.get(500 + 15 * z + 4, max_id_eeprom);
      if (!strcmp(max_id, max_id_eeprom)) {
        EEPROM.get(500 + 15 * z, max_addr);
        max_devices[x] = max_addr;
        Serial.println(F("Adding known Max ID to list:"));
        Serial.println(max_devices[x], HEX);
        break;
      }
    }
  }
}
#endif

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

uint16_t setPPS(uint8_t pps_index, uint16_t value) {
  uint16_t log_parameter = 0;
  if (pps_values[pps_index] != value) {
    for (int i=0; i < numLogValues; i++) {
      if (log_parameters[i] == 15000 + pps_index) {
        log_parameter = log_parameters[i];
      }
    }
    pps_values[pps_index] = value;
  }
  return log_parameter;
}


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
  char c;
  const byte MaxArrayElement=252;
  char  cLineBuffer[MaxArrayElement];  //
  byte  bPlaceInBuffer;                // index into buffer
  uint16_t log_now = 0;

  // Monitor the bus and send incoming data to the PC hardware serial
  // interface.
  // Separate telegrams after a pause of more than one character time.
  boolean busmsg = false;
  if(monitor){
    busmsg=bus.Monitor(msg);
#ifdef LOGGER
    if (busmsg==true) {
      LogTelegram(msg);
    }
#endif
//  }else{
  }
  if (!monitor || busmsg == true) {  
    // Listen for incoming messages, identified them by their magic byte.
    // Method GetMessage() validates length byte and CRC.
    if (bus.GetMessage(msg) || busmsg == true) { // message was syntactically correct
       // Decode the rcv telegram and send it to the PC serial interface
      if(verbose && bus_type != BUS_PPS && !monitor) {  // verbose output for PPS comes later
        printTelegram(msg, -1);
#ifdef LOGGER
        LogTelegram(msg);
#endif
      }
      // Is this a broadcast message?
      if(((msg[2]==ADDR_ALL && bus_type==BUS_BSB) || (msg[2]>=0xF0 && bus_type==BUS_LPB)) && msg[4+(bus_type*4)]==TYPE_INF){ // handle broadcast messages
      // Decode the rcv telegram and send it to the PC serial interface
        if (!verbose && !monitor) {        // don't log twice if in verbose mode, but log broadcast messages also in non-verbose mode
          printTelegram(msg, -1);
#ifdef LOGGER
          LogTelegram(msg);
#endif
        }

        // Filter Brenner Status messages (attention: partially undocumented enum values)

        uint32_t cmd;
        cmd=(uint32_t)msg[5+(bus_type*4)]<<24 | (uint32_t)msg[6+(bus_type*4)]<<16 | (uint32_t)msg[7+(bus_type*4)] << 8 | (uint32_t)msg[8+(bus_type*4)];
        if(cmd==0x0500006C) {   // set Time from BC, same CommandID for BSB and LPB
          setTime(msg[pl_start+5], msg[pl_start+6], msg[pl_start+7], msg[pl_start+3], msg[pl_start+2], msg[pl_start+1]+1900);
        }

        if(cmd==0x31000212) {    // TWW Status Elco / Brötje SOB
          Serial.print(F("INF: TWW-Status: "));
          Serial.println(msg[11]);      // assumed info byte

          if( (msg[11]==0x4D && my_dev_fam != 97) || (msg[11]==0xCD && my_dev_fam == 97)) {  // TWW Ladung on BROETJE_SOB and THISION
            if(TWW_start==0){        // has not been timed
              TWW_start=millis();   // keep current timestamp
              TWW_count++;          // increment number of starts
            }
          }else{             // TWW Ladung aus
            if(TWW_start!=0){        // start has been timed
              unsigned long TWW_end;
              TWW_end=millis();      // timestamp the end
              if(TWW_end >= TWW_start){
                TWW_duration+=(TWW_end-TWW_start)/1000;
              }else{ // overflow
                TWW_duration+=(0xffffffff-TWW_start+TWW_end)/1000;
              }
                TWW_start=0;
            } // endif, a previous start has been timed
          } // endif, TWW is off
        } // endif, Status TWW command code

        if(cmd==0x05000213) {     // Brennerstatus; CommandID 0x053d0f66 was suggested at some point as well, but so far has not been identified in one of the heating systems
          unsigned long brenner_end;
          boolean reset_brenner_timer = 0;
          Serial.print(F("INF: Brennerstatus: "));
          Serial.println(msg[pl_start]);      // first payload byte

          if(msg[pl_start]==0x04) {       // Stufe 1
            if(brenner_start==0){        // has not been timed
              brenner_start=millis();   // keep current timestamp
              brenner_count++;          // increment number of starts
            }
            if (brenner_stufe == 2) {
              reset_brenner_timer = 1;
            }
            brenner_stufe=1;
          }
          if(msg[pl_start]==0x14) {       // Stufe 2 (only oil furnace)
            if(brenner_start_2==0){        // has not been timed
              brenner_start_2=millis();   // keep current timestamp
              brenner_count_2++;          // increment number of starts
            }
            if (brenner_stufe == 1) {
              reset_brenner_timer = 1;
            }
            brenner_stufe=2;
          }
          if (reset_brenner_timer == 1) {   // Stufenwechsel bei mehrstufigem Ölbrenner
            brenner_end=millis();      // timestamp the end
            if (brenner_stufe == 2) {    // Stufe jetzt 2, war also vorher 1
              if(brenner_end >= brenner_start){
                brenner_duration+=(brenner_end-brenner_start)/1000;
              }else{ // overflow
                brenner_duration+=(0xffffffff-brenner_start+brenner_end)/1000;
              }
              brenner_start=0;              
            }
            if (brenner_stufe == 1) {   // Stufe jetzt 1, war also vorher 2
              if(brenner_end >= brenner_start_2){
                brenner_duration_2+=(brenner_end-brenner_start_2)/1000;
              }else{ // overflow
                brenner_duration_2+=(0xffffffff-brenner_start_2+brenner_end)/1000;
              }
              brenner_start_2=0;
            }
            reset_brenner_timer = 0;
          }
          if (msg[pl_start]==0x00) {    // brenner off
            brenner_end=millis();      // timestamp the end
            brenner_stufe=0;
            if(brenner_start!=0){        // start has been timed
              if(brenner_end >= brenner_start){
                brenner_duration+=(brenner_end-brenner_start)/1000;
              }else{ // overflow
                brenner_duration+=(0xffffffff-brenner_start+brenner_end)/1000;
              }
              brenner_start=0;
            } // endif, a previous start has been timed
            if(brenner_start_2!=0){        // start has been timed
              if(brenner_end >= brenner_start_2){
                brenner_duration_2+=(brenner_end-brenner_start_2)/1000;
              }else{ // overflow
                brenner_duration_2+=(0xffffffff-brenner_start_2+brenner_end)/1000;
              }
              brenner_start_2=0;
            } // endif, a previous start has been timed
          } // endif, brenner is off
        } // endif, Status Brenner command code
      } // endif, broadcasts

// PPS-Bus handling
      if (bus_type == BUS_PPS) {
        if (msg[0] == 0x17 && *PPS_write_enabled == 1) { // Send client data
          byte tx_msg[] = {0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
          byte rx_msg[10] = { 0 };
          switch (msg_cycle) {
            case 0:
              tx_msg[1] = 0x38; // Typ
#ifdef QAA_TYPE
              if (pps_values[PPS_QTP] == 0) pps_values[PPS_QTP] = QAA_TYPE;
#else
              pps_values[PPS_QTP] = 0x53;                // QAA70 as default
#endif
              tx_msg[7] = pps_values[PPS_QTP];
              break;
            case 1:
              tx_msg[1] = 0x18; // Position Drehknopf
              tx_msg[6] = pps_values[PPS_PDK] >> 8;
              tx_msg[7] = pps_values[PPS_PDK] & 0xFF;
              break;
            case 2:
              tx_msg[1] = 0x28; // Raumtemperatur Ist
              tx_msg[6] = pps_values[PPS_RTI] >> 8;
              tx_msg[7] = pps_values[PPS_RTI] & 0xFF;
              break;
            case 3:
              tx_msg[1] = 0x19; // Raumtepmeratur Soll
              tx_msg[6] = pps_values[PPS_RTZ] >> 8;
              tx_msg[7] = pps_values[PPS_RTZ] & 0xFF;
              break;
            case 4:
              tx_msg[1] = 0x4E;
              tx_msg[7] = 0x00;
              break;
            case 5:
              tx_msg[1] = 0x49;     // Betriebsart
              tx_msg[7] = pps_values[PPS_BA];
              break;
            case 6:
              tx_msg[1] = 0x56;
              tx_msg[7] = 0x00;
              break;
            case 7:
            {
              if (time_set == true) {
                boolean found = false;
                boolean next_active = true;
                uint16_t current_time = hour() * 6 + minute() / 10;
                int8_t PPS_weekday = weekday() - 1;
                uint8_t next_switchday = 0;
                uint8_t next_switchtime = 0;
                if (PPS_weekday == 0) PPS_weekday = 7;
                uint8_t index = PPS_S11 + ((PPS_weekday - 1) * 6);
                while (!found) {
                  if (current_time < pps_values[index] || (index >= PPS_S11 + ((PPS_weekday - 1 ) * 6) + 6)  || index < PPS_S11 + ((PPS_weekday - 1) * 6)) {
                    if (pps_values[index] == 0x90) {
                      if (PPS_weekday == 7) PPS_weekday = 0;
                      index = PPS_S11 + PPS_weekday * 6;
                    }
                    next_switchtime = pps_values[index];
                    next_switchday = ((index - PPS_S11) / 6) + 1;
                    next_switchday = next_switchday + (0x10 * next_active);
                    found = true;
                  } else {
                    index++;
                    next_active = !next_active;
                  }
                  if (index > PPS_E73) index = PPS_S11;
                }
                tx_msg[1] = 0x69;
                tx_msg[6] = next_switchday;     // high nibble: current heating program (0x10 = reduced, 0x00 = comfort), low nibble: day of week
                tx_msg[7] = next_switchtime;    // next heating program time (encoded as one increment translates to one 10 minute block)

                if (current_switchday != next_switchday) {    // Set presence parameter to on or off at the beginning of (non-)heating timeslot
                  pps_values[PPS_AW] = !next_active;
                  current_switchday = next_switchday;
                }

                if (pps_values[PPS_AW] == 0) {                 // Set destination temperature (comfort + knob for heating period, otherwise reduced temperature)
                  pps_values[PPS_RTZ] = pps_values[PPS_RTA];
                } else {
                  pps_values[PPS_RTZ] = pps_values[PPS_RTS] + pps_values[PPS_PDK];
                }
              }
              break;
            }
            case 8:
              tx_msg[1] = 0x08;     // Raumtemperatur Soll
              tx_msg[6] = pps_values[PPS_RTS] >> 8;
              tx_msg[7] = pps_values[PPS_RTS] & 0xFF;
              break;
            case 9:
              tx_msg[1] = 0x09;     // Raumtemperatur Abwesenheit Soll
              tx_msg[6] = pps_values[PPS_RTA] >> 8;
              tx_msg[7] = pps_values[PPS_RTA] & 0xFF;
              break;
            case 10:
              tx_msg[1] = 0x0B; // Trinkwassertemperatur Soll
              tx_msg[6] = pps_values[PPS_TWS] >> 8;
              tx_msg[7] = pps_values[PPS_TWS] & 0xFF;
              break;
            case 11:
              tx_msg[1] = 0x4C; // Präsenz
              tx_msg[7] = pps_values[PPS_AW];
              break;
            case 12:
              tx_msg[1] = 0x1E; // Trinkwassertemperatur Reduziert Soll
              tx_msg[6] = pps_values[PPS_TWR] >> 8;
              tx_msg[7] = pps_values[PPS_TWR] & 0xFF;
              break;
            case 13:
              tx_msg[1] = 0x60;
              tx_msg[2] = pps_values[PPS_E13];
              tx_msg[3] = pps_values[PPS_S13];
              tx_msg[4] = pps_values[PPS_E12];
              tx_msg[5] = pps_values[PPS_S12];
              tx_msg[6] = pps_values[PPS_E11];
              tx_msg[7] = pps_values[PPS_S11];
              break;
            case 14:
              tx_msg[1] = 0x61;
              tx_msg[2] = pps_values[PPS_E23];
              tx_msg[3] = pps_values[PPS_S23];
              tx_msg[4] = pps_values[PPS_E22];
              tx_msg[5] = pps_values[PPS_S22];
              tx_msg[6] = pps_values[PPS_E21];
              tx_msg[7] = pps_values[PPS_S21];
              break;
            case 15:
              tx_msg[1] = 0x62;
              tx_msg[2] = pps_values[PPS_E33];
              tx_msg[3] = pps_values[PPS_S33];
              tx_msg[4] = pps_values[PPS_E32];
              tx_msg[5] = pps_values[PPS_S32];
              tx_msg[6] = pps_values[PPS_E31];
              tx_msg[7] = pps_values[PPS_S31];
              break;
            case 16:
              tx_msg[1] = 0x63;
              tx_msg[2] = pps_values[PPS_E43];
              tx_msg[3] = pps_values[PPS_S43];
              tx_msg[4] = pps_values[PPS_E42];
              tx_msg[5] = pps_values[PPS_S42];
              tx_msg[6] = pps_values[PPS_E41];
              tx_msg[7] = pps_values[PPS_S41];
              break;
            case 17:
              tx_msg[1] = 0x64;
              tx_msg[2] = pps_values[PPS_E53];
              tx_msg[3] = pps_values[PPS_S53];
              tx_msg[4] = pps_values[PPS_E52];
              tx_msg[5] = pps_values[PPS_S52];
              tx_msg[6] = pps_values[PPS_E51];
              tx_msg[7] = pps_values[PPS_S51];
              break;
            case 18:
              tx_msg[1] = 0x65;
              tx_msg[2] = pps_values[PPS_E63];
              tx_msg[3] = pps_values[PPS_S63];
              tx_msg[4] = pps_values[PPS_E62];
              tx_msg[5] = pps_values[PPS_S62];
              tx_msg[6] = pps_values[PPS_E61];
              tx_msg[7] = pps_values[PPS_S61];
              break;
            case 19:
              tx_msg[1] = 0x66;
              tx_msg[2] = pps_values[PPS_E73];
              tx_msg[3] = pps_values[PPS_S73];
              tx_msg[4] = pps_values[PPS_E72];
              tx_msg[5] = pps_values[PPS_S72];
              tx_msg[6] = pps_values[PPS_E71];
              tx_msg[7] = pps_values[PPS_S71];
              break;
            case 20:
              tx_msg[1] = 0x7C;
              tx_msg[7] = pps_values[PPS_FDT];     // Verbleibende Feriendauer in Tagen
              break;
            case 21:
              tx_msg[1] = 0x1B;                    // Frostschutz- und Maximaltemperatur
              tx_msg[4] = pps_values[PPS_SMX] >> 8;
              tx_msg[5] = pps_values[PPS_SMX] & 0xFF;
              tx_msg[6] = pps_values[PPS_FRS] >> 8;
              tx_msg[7] = pps_values[PPS_FRS] & 0xFF;
          }
          msg_cycle++;
          if (msg_cycle > 21) {
            msg_cycle = 0;
          }
          if (saved_msg_cycle > 0) {
            msg_cycle = saved_msg_cycle;
            saved_msg_cycle = 0;
          }
          if (tx_msg[1] != 0xFF &&  *PPS_write_enabled == 1) {
            bus.Send(0, 0, rx_msg, tx_msg);
          }

          if(verbose) {     // verbose output for PPS after time-critical sending procedure
            if (!monitor) {
              printTelegram(msg, -1);
            } else {
              Serial.print(millis());
              Serial.print(F(" "));
            }
            printTelegram(tx_msg, -1);
#ifdef LOGGER
            if (!monitor) {
              LogTelegram(msg);
              LogTelegram(tx_msg);
            }
#endif
          } 
        
        } else {    // parse heating system data

          if (msg[0] == 0x1E) {   // Anfragen der Therme nach bestimmten Parametern
            saved_msg_cycle = msg_cycle;
            switch(msg[1]) {
              case 0x08: msg_cycle = 8; break;
              case 0x09: msg_cycle = 9; break;
              case 0x0B: msg_cycle = 10; break;
              case 0x48: msg_cycle = 1; break;
              case 0x49: msg_cycle = 5; break;
              case 0x4C: msg_cycle = 11; break;
              case 0x4D: msg_cycle = 2; break;
              case 0x4F: msg_cycle = 3; break;
              case 0x60: msg_cycle = 13; break;
              case 0x61: msg_cycle = 14; break;
              case 0x62: msg_cycle = 15; break;
              case 0x63: msg_cycle = 16; break;
              case 0x64: msg_cycle = 17; break;
              case 0x65: msg_cycle = 18; break;
              case 0x66: msg_cycle = 19; break;
              case 0x7C: msg_cycle = 20; break;
              default:
                 Serial.print("Unknown request: ");
                for (int c=0;c<9;c++) {
                  if (msg[c]<16) Serial.print("0");
                  Serial.print(msg[c], HEX);
                  Serial.print(" ");
                }
                Serial.println();
#ifdef LOGGER
/*
                File dataFile = SD.open("datalog.txt", FILE_WRITE);
                if (dataFile) {
                  dataFile.print(millis());
                  dataFile.print(F(";"));
                  dataFile.print(GetDateTime(date));
                  dataFile.print(F(";Unknown PPS telegram;"));
                  for(int i=0;i<9+(*PPS_write_enabled!=1 && msg[0] == 0x17);i++){
                    if (i > 0) {
                      dataFile.print(F(" "));
                    }
                    if (msg[i] < 16) dataFile.print(F("0"));  // add a leading zero to single-digit values
                    dataFile.print(msg[i], HEX);
                  }
                  dataFile.println();
                }
                dataFile.close();
*/
#endif
                break;


/*
Weitere noch zu überprüfende Telegramme:
https://www.mikrocontroller.net/topic/218643#3517035
 17 FD 4A 00 3B 00 0B 0F 00 64
-> 0x3B = 59 % Brennerleistung
-> 0x000B = wahrscheinlich Status 11 (es gibt noch 7, 19 usw, sicher bin 
ich mir da nicht)
-> 0x0F00 = 3840 / 64 = 60 °C Ist-Kesseltemperatur

*/

            }
          } else {    // Info-Telegramme von der Therme (0x1D)

            uint8_t pps_offset = (msg[0] == 0x17 && *PPS_write_enabled != 1);
            uint16_t temp = (msg[6+pps_offset] << 8) + msg[7+pps_offset];

            uint16_t i = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) - 1 + sizeof(cmdtbl2)/sizeof(cmdtbl2[0]) - 1;
            while (i > 0 && get_cmdtbl_line(i) >= 15000) {
              uint32_t cmd = get_cmdtbl_cmd(i);
              cmd = (cmd & 0x00FF0000) >> 16;
              if (cmd == msg[1+pps_offset]) {
                break;
              }
              i--;
            }
            uint8_t flags=get_cmdtbl_flags(i);

            if ((flags & FL_RONLY) == FL_RONLY || *PPS_write_enabled != 1) {

              switch (msg[1+pps_offset]) {
                case 0x4F: log_now = setPPS(PPS_CON, msg[7+pps_offset]); msg_cycle = 0; break;  // Gerät an der Therme angemeldet? 0 = ja, 1 = nein

                case 0x08: pps_values[PPS_RTS] = temp; break; // Raumtemperatur Soll
                case 0x09: pps_values[PPS_RTA] = temp; break; // Raumtemperatur Abwesenheit Soll
                case 0x0B: pps_values[PPS_TWS] = temp; break; // Trinkwassertemperatur Soll
                case 0x0C: pps_values[PPS_TWS] = temp; break; // Trinkwassertemperatur Soll (?)
                case 0x0E: pps_values[PPS_KVS] = temp; break; // Vorlauftemperatur Soll (?)
                case 0x18: pps_values[PPS_PDK] = temp; break; // Position Drehknopf
                case 0x19: log_now = setPPS(PPS_RTZ, temp); break; // Raumtemperatur Zieltemperatur (nur bei Komforttemperatur, dann zzgl. Einstellung am Drehknopf)
                case 0x1E: pps_values[PPS_TWR] = temp; break; // Trinkwasser-Soll Reduziert
                case 0x28: pps_values[PPS_RTI] = temp; break; // Raumtemperatur Ist
                case 0x29: pps_values[PPS_AT] = temp; break; // Außentemperatur
                case 0x2B: pps_values[PPS_TWI] = temp; break; // Trinkwassertemperatur Ist
                case 0x2C: pps_values[PPS_MVT] = temp; break; // Mischervorlauftemperatur
                case 0x2E: pps_values[PPS_KVT] = temp; break; // Vorlauftemperatur
                case 0x38: pps_values[PPS_QTP] = msg[7+pps_offset]; break; // QAA type
                case 0x49: log_now = setPPS(PPS_BA, msg[7+pps_offset]); break; // Betriebsart
                case 0x4C: log_now = setPPS(PPS_AW, msg[7+pps_offset]); break; // Komfort-/Eco-Modus
                case 0x4D: log_now = setPPS(PPS_BRS, msg[7+pps_offset]); break; // Brennerstatus
                case 0x57: pps_values[PPS_ATG] = temp; log_now = setPPS(PPS_TWB, msg[2+pps_offset]); break; // gemischte Außentemperatur / Trinkwasserbetrieb
                case 0x60: 
                  pps_values[PPS_S11] = msg[7+pps_offset]; 
                  pps_values[PPS_E11] = msg[6+pps_offset]; 
                  pps_values[PPS_S12] = msg[5+pps_offset]; 
                  pps_values[PPS_E12] = msg[4+pps_offset]; 
                  pps_values[PPS_S13] = msg[3+pps_offset]; 
                  pps_values[PPS_E13] = msg[2+pps_offset];
                  break;
                case 0x61:
                  pps_values[PPS_S21] = msg[7+pps_offset]; 
                  pps_values[PPS_E21] = msg[6+pps_offset]; 
                  pps_values[PPS_S22] = msg[5+pps_offset];
                  pps_values[PPS_E22] = msg[4+pps_offset];
                  pps_values[PPS_S23] = msg[3+pps_offset]; 
                  pps_values[PPS_E23] = msg[2+pps_offset];
                  break;
                case 0x62:
                  pps_values[PPS_S31] = msg[7+pps_offset];
                  pps_values[PPS_E31] = msg[6+pps_offset];
                  pps_values[PPS_S32] = msg[5+pps_offset];
                  pps_values[PPS_E32] = msg[4+pps_offset];
                  pps_values[PPS_S33] = msg[3+pps_offset];
                  pps_values[PPS_E33] = msg[2+pps_offset];
                  break;
                case 0x63:
                  pps_values[PPS_S41] = msg[7+pps_offset];
                  pps_values[PPS_E41] = msg[6+pps_offset];
                  pps_values[PPS_S42] = msg[5+pps_offset];
                  pps_values[PPS_E42] = msg[4+pps_offset];
                  pps_values[PPS_S43] = msg[3+pps_offset];
                  pps_values[PPS_E43] = msg[2+pps_offset];
                  break;
                case 0x64:
                  pps_values[PPS_S51] = msg[7+pps_offset];
                  pps_values[PPS_E51] = msg[6+pps_offset];
                  pps_values[PPS_S52] = msg[5+pps_offset];
                  pps_values[PPS_E52] = msg[4+pps_offset];
                  pps_values[PPS_S53] = msg[3+pps_offset];
                  pps_values[PPS_E53] = msg[2+pps_offset];
                  break;
                case 0x65:
                  pps_values[PPS_S61] = msg[7+pps_offset];
                  pps_values[PPS_E61] = msg[6+pps_offset];
                  pps_values[PPS_S62] = msg[5+pps_offset];
                  pps_values[PPS_E62] = msg[4+pps_offset];
                  pps_values[PPS_S63] = msg[3+pps_offset];
                  pps_values[PPS_E63] = msg[2+pps_offset];
                  break;
                case 0x66:
                  pps_values[PPS_S71] = msg[7+pps_offset];
                  pps_values[PPS_E71] = msg[6+pps_offset];
                  pps_values[PPS_S72] = msg[5+pps_offset];
                  pps_values[PPS_E72] = msg[4+pps_offset];
                  pps_values[PPS_S73] = msg[3+pps_offset];
                  pps_values[PPS_E73] = msg[2+pps_offset];
                  break;
                case 0x69: break;                             // Nächste Schaltzeit
                case 0x79: setTime(msg[5+pps_offset], msg[6+pps_offset], msg[7+pps_offset], msg[4+pps_offset], 1, 2018); time_set = true; break;  // Datum (msg[4] Wochentag)
                case 0x48: log_now = setPPS(PPS_HP, msg[7+pps_offset]); break;   // Heizprogramm manuell/automatisch (0 = Auto, 1 = Manuell)
                case 0x1B:                                    // Frostschutz-Temperatur 
                  pps_values[PPS_FRS] = temp;
                  pps_values[PPS_SMX] = (msg[4+pps_offset] << 8) + msg[5+pps_offset];
                  break;
                case 0x00: break;
                default:
                  Serial.print("Unknown telegram: ");
                  for (int c=0;c<9+pps_offset;c++) {
                    if (msg[c]<16) Serial.print("0");
                    Serial.print(msg[c], HEX);
                    Serial.print(" ");
                  }
                  Serial.println();
                  break;
              }
            }

/*
            Serial.print(F("Outside Temperature: "));
            Serial.println(outside_temp);
            Serial.print(F("Boiler Temperature: "));
            Serial.println(boiler_temp);
            Serial.print(F("Mixer Flow Temperature: "));
            Serial.println(mixer_flow_temp);
            Serial.print(F("Flow Temperature: "));
            Serial.println(flow_temp);
            Serial.print(F("Weighted Temperature: "));
            Serial.println(weighted_temp);
            Serial.print(F("Boiler active: "));
            if (boiler_active) {
              Serial.println(F("yes"));
            } else {
              Serial.println(F("no"));
            }
            Serial.print(F("Time: ")); Serial.print(d); Serial.print(", "); Serial.print(h); Serial.print(":"); Serial.print(m); Serial.print(":"); Serial.println(s);
*/
          } // End parsing 0x1D heater telegrams
    
          if(verbose && !monitor) {     // verbose output for PPS after time-critical sending procedure
            printTelegram(msg, -1);
#ifdef LOGGER
            LogTelegram(msg);
#endif
          } 
                
        } // End parse PPS heating data

      } // End PPS-bus handling
      
    } // endif, GetMessage() returned True

   // At this point drop possible GetMessage() failures silently

  } // endelse, NOT in monitor mode

  // Listen for incoming clients
  client = server.available();
  if (client) {

#ifdef TRUSTED_IP
#ifndef TRUSTED_IP2
#define TRUSTED_IP2 0
#endif
    IPAddress remoteIP = client.remoteIP();
    if (remoteIP[3] != TRUSTED_IP && remoteIP[3] != TRUSTED_IP2) {      // reject clients from unauthorized IP addresses; replace != with > to block access from all IPs greater than TRUSTED_IP segment
      Serial.print(F("Rejected access from "));
      for (int i=0; i<4; i++) {
        Serial.print(remoteIP[i]);
        if (i<3) {
          Serial.print(F("."));
        }
      }
      Serial.println(F("."));
      client.stop();
    }
#endif

    loopCount = 0;
   // Read characters from client and assemble them in cLineBuffer
    bPlaceInBuffer=0;            // index into cLineBuffer
    while (client.connected()) {
      if (client.available()) {
        loopCount = 0;
        c = client.read();       // read one character
        Serial.print(c);         // and send it to hardware UART

        if ((c!='\n') && (c!='\r') && (bPlaceInBuffer<MaxArrayElement)){
          cLineBuffer[bPlaceInBuffer++]=c;
          continue;
        }
        // Got an EOL character
        Serial.println();

        // perform HTTP-Authentification by reading the remaining client data and look for credentials
#ifdef USER_PASS_B64
        char linebuf[80];
        uint8_t charcount=0;
        boolean authenticated=false;
        memset(linebuf,0,sizeof(linebuf));
        boolean currentLineIsBlank = false;
        while (client.connected()) {
          if (client.available()) {
            char c = client.read();
            linebuf[charcount]=c;
            if (charcount<sizeof(linebuf)-1) charcount++;
            if (c == '\n' && currentLineIsBlank) {
              break;
            }
            if (c == '\n') {
              // you're starting a new line
              currentLineIsBlank = true;
              if (strstr(linebuf,"Authorization: Basic")!=0 && strstr(linebuf,USER_PASS_B64)!=0) {
                authenticated=true;
              }
              memset(linebuf,0,sizeof(linebuf));
              charcount=0;
            } else if (c != '\r') {
              // you've gotten a character on the current line
              currentLineIsBlank = false;
            }            
          }
        }
        // if no credentials found in HTTP header, send 401 Authorization Required
        if (!authenticated) {
          client.println(F("HTTP/1.1 401 Authorization Required"));
          client.println(F("WWW-Authenticate: Basic realm=\"Secure Area\""));
          client.println(F("Content-Type: text/html"));
          client.println(F("Connnection: close"));
          client.println();
          client.println(F("<!DOCTYPE HTML>"));
          client.println(F("<HTML>  <HEAD>   <TITLE>Error</TITLE>"));
          client.println(F(" </HEAD> <BODY><H1>401 Unauthorized.</H1></BODY> </HTML>"));
          client.stop();
        }
        // otherwise continue like normal
#endif

        // Flush any remaining bytes from the client buffer
//        client.flush();
        // GET / HTTP/1.1 (anforderung website)
        // GET /710 HTTP/1.0 (befehlseingabe)
        String urlString = String(cLineBuffer);
        urlString = urlString.substring(urlString.indexOf('/'), urlString.indexOf(' ', urlString.indexOf('/')));
                Serial.println(urlString);
        urlString.toCharArray(cLineBuffer, MaxArrayElement);

// IPWE START
#ifdef IPWE
        if (urlString == "/ipwe.cgi") {
          client.flush();
          Ipwe();
          break;
        }
#endif
// IPWE END

        if (urlString == "/favicon.ico") {
          client.println(F("HTTP/1.1 200 OK"));
          client.println(F("Content-Type: image/x-icon"));
          client.println();
          printPStr(pgm_get_far_address(favicon), sizeof(favicon));
          break;
        }

        // Set up a pointer to cLineBuffer
        char *p=cLineBuffer;
#ifdef PASSKEY
        // check for valid passkey
        p=strchr(cLineBuffer+1,'/');
        if(p==NULL){    // no match
          break;
        }
        *p='\0';     // mark end of string
        if(strcmp(cLineBuffer+1, PASSKEY)){
          Serial.println(F("no matching passkey"));
          client.flush();
          webPrintHeader();
          webPrintFooter();
          break;
        }
        *p='/';
#endif
        if (p[1] != 'J') {
          client.flush();
        }
        // simply print the website
        if(!strcmp(p,"/")){
          webPrintSite();
          break;
        }

        // Answer to unknown requests
        if(!isdigit(p[1]) && strchr("ABCDEGHIJKLMNOPQRSTVXY",p[1])==NULL){
          webPrintHeader();
          webPrintFooter();
          break;
        }
        // setting verbosity level
        if(p[1]=='V'){
          p+=2;
          verbose=atoi(p);
          webPrintHeader();
          if(verbose>0){
            client.println(F(MENU_TEXT_VB1 "<BR>"));
          }else{
            client.println(F(MENU_TEXT_VB2 "<BR>"));
          }
          client.println(F(MENU_TEXT_VB3));
          webPrintFooter();
          break;
        }
        // switching monitor on/off
        if(p[1]=='M'){
          p+=2;               // hopefully finds a digit there ...
          monitor=atoi(p);    // .. to convert
          webPrintHeader();
          if(monitor>0){
            client.println(F(MENU_TEXT_SR1));
          }else{
            client.println(F(MENU_TEXT_SR2));
          }
      	  client.println(F(MENU_TEXT_SR3));
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
          int line;
          bool setcmd= (p[1]=='S'); // True if SET command

          p+=2;               // third position in cLineBuffer
          if(!isdigit(*p)){   // now we check for digits - nice
            webPrintHeader();
            client.println(F(MENU_TEXT_ER1));
            webPrintFooter();
            break;
          }
          line=atoi(p);       // convert until non-digit char is found
          p=strchr(p,'=');    // search for '=' sign
          if(p==NULL){        // no match
            webPrintHeader();
            client.println(F(MENU_TEXT_ER2));
            webPrintFooter();
            break;
          }
          p++;                   // position pointer past the '=' sign
          char* token = strchr(p, '!');
          token++;
          if (token[0] > 0) {
            int d_addr = atoi(token);
            Serial.print(F("Setting temporary destination to "));
            Serial.println(d_addr);
            bus_type=bus.setBusType(bus_type, myAddr, d_addr);
          }
          
          Serial.print(F("set ProgNr "));
          Serial.print(line);    // the ProgNr
          Serial.print(F(" = "));
//          Serial.println(atof(p));     // the value
          Serial.println(p);     // the value
          // Now send it out to the bus
          int setresult = 0;
          setresult = set(line,p,setcmd);

          if(setresult!=1){
            webPrintHeader();
            client.println(F(MENU_TEXT_ER3));
            if (setresult == 2) {
              client.println(F(" - " MENU_TEXT_ER4));
            }
            webPrintFooter();
            break;
          }
          if(setcmd){            // was this a SET command?
            webPrintHeader();
            // Query controller for this value
            query(line,line,0);  // read value back
            webPrintFooter();
          }else{
            webPrintHeader();
            webPrintFooter();
          }
          if (token[0] > 0) {
            bus_type=bus.setBusType(bus_type, myAddr, destAddr);
          }
          break;
        }
        // list categories
        if(p[1]=='K' && !isdigit(p[2])){
          //list categories
          webPrintHeader();
          int len=sizeof(ENUM_CAT);
//          memcpy_PF(buffer, pgm_get_far_address(ENUM_CAT), len);
//          memcpy_P(buffer, &ENUM_CAT,len);
//          buffer[len]=0;
          client.print(F("<table><tr><td><a href='/"));
          #ifdef PASSKEY
            client.print(PASSKEY);
            client.print(F("/"));
          #endif
          client.println(F("B'>" MENU_TEXT_BST "</A><BR></td><td></td></tr>"));
          client.print(F("<tr><td><a href='/"));
          #ifdef PASSKEY
            client.print(PASSKEY);
            client.print(F("/"));
          #endif
          client.println(F("A'>" MENU_TEXT_24A "</A></td><td></td></tr>"));
          client.println(F("<tr><td>&nbsp;</td><td>&nbsp;</td></tr>"));
          for(int cat=0;cat<CAT_UNKNOWN;cat++){
            outBufclear();
            if ((bus_type != BUS_PPS) || (bus_type == BUS_PPS && cat == CAT_PPS)) {
              printENUM(pgm_get_far_address(ENUM_CAT),len,cat,1);
              Serial.println();
              client.print(F("<tr><td><A HREF='K"));
              client.print(cat);
              client.print(F("'>"));
              client.print(outBuf);
              client.println(F("</A></td><td>"));
              client.print(pgm_read_word_far(pgm_get_far_address(ENUM_CAT_NR) + (cat*2) * sizeof(ENUM_CAT_NR[0])));
              client.print(F(" - "));
              client.print(pgm_read_word_far(pgm_get_far_address(ENUM_CAT_NR) + (cat*2+1) * sizeof(ENUM_CAT_NR[0])));
              client.println(F("</td></tr>"));
            }
          }
          client.println(F("</table>"));
          webPrintFooter();
          break;
        }
        // list enum values
        if(p[1]=='E'){
          webPrintHeader();
          uint16_t line = atoi(&p[2]);
          int i=findLine(line,0,NULL);
          if(i>=0){
            // check type
              if(get_cmdtbl_type(i)==VT_ENUM) {
//            if(pgm_read_byte(&cmdtbl[i].type)==VT_ENUM){
              uint16_t enumstr_len=get_cmdtbl_enumstr_len(i);
              uint32_t enumstr = calc_enum_offset(get_cmdtbl_enumstr(i), enumstr_len);
//              uint16_t enumstr_len=pgm_read_word(&cmdtbl[i].enumstr_len);
//              memcpy_PF(buffer, calc_enum_offset(get_cmdtbl_enumstr(i)),enumstr_len);
//              memcpy_P(buffer, (char*)pgm_read_word(&(cmdtbl[i].enumstr)),enumstr_len);
//              buffer[enumstr_len]=0;

              uint16_t val;
              uint16_t c=0;
              while(c<enumstr_len){
                if((byte)(pgm_read_byte_far(enumstr+c+1))!=' '){
                  val=uint16_t((pgm_read_byte_far(enumstr+c) << 8)) | uint16_t(pgm_read_byte_far(enumstr+c+1));
                  c++;
                }else{
                  val=uint16_t(pgm_read_byte_far(enumstr+c));
                }
                //skip leading space
                c+=2;

                sprintf(outBuf,"%d - %s",val,strcpy_PF(buffer, enumstr+c));
                client.println(outBuf);
                client.println(F("<br>"));

                while(pgm_read_byte_far(enumstr+c)!=0) c++;
                c++;
              }
            
            }else{
              client.println(F(MENU_TEXT_ER5));
            }
          }else{
            client.println(F(MENU_TEXT_ER6));
          }
          webPrintFooter();
          break;
        }
        // query reset value
        if(p[1]=='R'){
          uint32_t c;
          webPrintHeader();
          int line = atoi(&p[2]);
          int i=findLine(line,0,&c);
          if(i<0){
            client.println(F(MENU_TEXT_ER6));
          }else{
            if(!bus.Send(TYPE_QRV, c, msg, tx_msg)){
              Serial.println(F("set failed"));  // to PC hardware serial I/F
              client.println(F(MENU_TEXT_ER3));
            }else{

              // Decode the xmit telegram and send it to the PC serial interface
              if(verbose) {
                printTelegram(tx_msg, line);
#ifdef LOGGER
                LogTelegram(tx_msg);
#endif
              }

              // Decode the rcv telegram and send it to the PC serial interface
              printTelegram(msg, line);   // send to hardware serial interface
#ifdef LOGGER
              LogTelegram(msg);
#endif
              if(outBufLen>0){
                client.println(outBuf);
                client.println(F("<br>"));
              }
            }
          }
          webPrintFooter();
          break;
        }

        if(p[1]=='Q') {
          webPrintHeader();

          client.print(F(MENU_TEXT_QSC "...<BR>"));
          if (bus_type == 0) {
            bus.setBusType(bus_type, myAddr, 0x7F);
          }
          if (bus_type == 1) {
            bus.setBusType(bus_type, myAddr, 0xFF);
          }

          uint8_t found_ids[10] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
          if (bus.Send(TYPE_QINF, 0x053D0002, msg, tx_msg)) {
            unsigned long startquery = millis();
            while (millis() < startquery + 10000) {
              if (bus.GetMessage(msg)) {
                uint8_t found_id = 0;
                boolean found = false;
                if (bus_type == 0) {
                  found_id = msg[1] & 0x7F;
                }
                if (bus_type == 1) {
                  found_id = msg[3];
                }
                for (int i=0;i<10;i++) {
                  if (found_ids[i] == found_id) {
                    found = true;
                    break;
                  }
                  if (found_ids[i] == 0xFF) {
                    found_ids[i] = found_id;
                    break;
                  }
                }
                if (!found) {
                  client.print(F(MENU_TEXT_QFD ": "));
                  client.print(found_id);
                  client.println(F("<BR>"));
                }
              }
              delay(1);
            }
          } else {
            client.println(F(MENU_TEXT_QFA "!<BR>"));
          }

          for (int x=0;x<10;x++) {
            if (found_ids[x]==0xFF) {
              continue;
            }
            bus.setBusType(bus_type, myAddr, found_ids[x]);
            client.print(F("<BR>" MENU_TEXT_QRT " "));
            client.print(found_ids[x]);
            client.println(F(":<BR>"));

            uint32_t c=0;
            uint16_t l;
            int orig_dev_fam = my_dev_fam;
            int orig_dev_var = my_dev_var;
            char* pvalstr=NULL;
            int temp_dev_fam = strtod(query(6225,6225,1),NULL);
            int temp_dev_var = strtod(query(6226,6226,1),NULL);
            my_dev_fam = temp_dev_fam;
            my_dev_var = temp_dev_var;
            client.print(F(STR6225_TEXT ": "));
            client.println(temp_dev_fam);
            client.print(F("<BR>" STR6226_TEXT ": "));
            client.println(temp_dev_var);
            client.print(F("<BR>" STR6224_TEXT ": "));
            client.println(query(6224,6224,1));
            client.print(F("<BR>" STR6220_TEXT ": "));
            client.println(query(6220,6220,1));
            client.print(F("<BR>" STR6221_TEXT ": "));
            client.println(query(6221,6221,1));
            client.print(F("<BR>" STR6227_TEXT ": "));
            client.println(query(6227,6227,1));
            client.print(F("<BR>" STR6228_TEXT ": "));
            client.println(query(6228,6228,1));
            client.print(F("<BR>" STR6229_TEXT ": "));
            client.println(query(6229,6229,1));
            client.print(F("<BR>" STR6231_TEXT ": "));
            client.println(query(6231,6231,1));
            client.print(F("<BR>" STR6232_TEXT ": "));
            client.println(query(6232,6232,1));
            client.print(F("<BR>" STR6233_TEXT ": "));
            client.println(query(6233,6233,1));
            client.print(F("<BR>" STR6234_TEXT ": "));
            client.println(query(6234,6234,1));
            client.print(F("<BR>" STR6235_TEXT ": "));
            client.println(query(6235,6235,1));
            client.print(F("<BR>" STR6223_TEXT ": "));
            client.println(query(6223,6223,1));
            client.print(F("<BR>" STR6236_TEXT ": "));
            client.println(query(6236,6236,1));
            client.print(F("<BR>" STR6223_TEXT ": "));
            client.println(query(6237,6237,1));
            my_dev_fam = orig_dev_fam;
            my_dev_var = orig_dev_var;

            client.println(F("<BR>" MENU_TEXT_QST "...<BR>"));
            for (int j=0;j<10000;j++) {
              if (get_cmdtbl_cmd(j) == c) {
                continue;
              }
              c=get_cmdtbl_cmd(j);
              if(c==CMD_END) break;
              l=get_cmdtbl_line(j);
              uint8_t dev_fam = get_cmdtbl_dev_fam(j);
              uint8_t dev_var = get_cmdtbl_dev_var(j);
              if (((dev_fam != temp_dev_fam && dev_fam != 255) || (dev_var != temp_dev_var && dev_var != 255)) && c!=CMD_UNKNOWN) {
                Serial.println(c, HEX);
                if(!bus.Send(TYPE_QUR, c, msg, tx_msg)){
                  Serial.println(F("bus send failed"));  // to PC hardware serial I/F
                } else {
                  if (msg[4+(bus_type*4)]!=TYPE_ERR) {
                    // Decode the xmit telegram and send it to the PC serial interface
                    printTelegram(tx_msg, -1);
#ifdef LOGGER
                    LogTelegram(tx_msg);
#endif
                    // Decode the rcv telegram and send it to the PC serial interface
                    pvalstr=printTelegram(msg, -1);   // send to hardware serial interface
#ifdef LOGGER
                    LogTelegram(msg);
#endif
                    if (pvalstr[0]<1) {
                      my_dev_fam = temp_dev_fam;
                      my_dev_var = temp_dev_var;
                      pvalstr=query(l,l, true);
                      my_dev_fam = orig_dev_fam;
                      my_dev_var = orig_dev_var;
                      if (pvalstr[0]<1) {
                        client.println(F("<BR>"));
                        client.print(l);
                        client.println(F("<BR>"));
                        if(outBufLen>0){
                          client.println(outBuf);
                          client.println(F("<br>"));
                        }
                        for (int i=0;i<tx_msg[len_idx]+bus_type;i++) {
                          if (tx_msg[i] < 16) client.print(F("0"));  // add a leading zero to single-digit values
                          client.print(tx_msg[i], HEX);
                          client.print(F(" "));
                        }
                        client.println(F("<br>"));
                        for (int i=0;i<msg[len_idx]+bus_type;i++) {
                          if (msg[i] < 16) client.print(F("0"));  // add a leading zero to single-digit values
                          client.print(msg[i], HEX);
                          client.print(F(" "));
                        }
                      }
                    }
                  }
                }
              }
            }
            client.println(F("<BR>"));
          }

          client.println(F("<BR>" MENU_TEXT_QTE ".<BR>"));
          bus.setBusType(bus_type, myAddr, destAddr);   // return to original destination address
          webPrintFooter();
          break;
        }

        if(p[1]=='Y'){
#ifdef DEBUG
          webPrintHeader();
          uint8_t type = strtol(&p[2],NULL,16);
          uint32_t c = (uint32_t)strtoul(&p[5],NULL,16);
          if(!bus.Send(type, c, msg, tx_msg)){
            Serial.println(F("bus send failed"));  // to PC hardware serial I/F
          }else{
            // Decode the xmit telegram and send it to the PC serial interface
            printTelegram(tx_msg, -1);
#ifdef LOGGER
            LogTelegram(tx_msg);
#endif
          }
          // Decode the rcv telegram and send it to the PC serial interface
          printTelegram(msg, -1);   // send to hardware serial interface
#ifdef LOGGER
          LogTelegram(msg);
#endif
          if(outBufLen>0){
            client.println(outBuf);
            client.println(F("<br>"));
          }
          for (int i=0;i<tx_msg[len_idx]+bus_type;i++) {
            if (tx_msg[i] < 16) client.print(F("0"));  // add a leading zero to single-digit values
            client.print(tx_msg[i], HEX);
            client.print(F(" "));
          }
          client.println();
          client.println(F("<br>"));
          for (int i=0;i<msg[len_idx]+bus_type;i++) {
            if (msg[i] < 16) client.print(F("0"));  // add a leading zero to single-digit values
            client.print(msg[i], HEX);
            client.print(F(" "));
          }
          client.println();
          webPrintFooter();
#endif
          break;
        }

        if (p[1]=='J') {
          client.println(F("HTTP/1.1 200 OK"));
          client.println(F("Content-Type: application/json; charset=utf-8"));
          client.println();
          client.println(F("{"));

          int i=0;
          uint32_t cmd=0;
            
          // Parse potential JSON payload

          char json_temp[11];
          char json_value_string[11];
          uint8_t j_char_idx = 0;
          int json_parameter = 0;
          double json_value = 0; json_value = json_value;   // to disable irrelevant compiler warning despite variable being used below
          boolean json_type = 0;
          boolean p_flag = false;
          boolean v_flag = false;
          boolean t_flag = false;
          boolean output = false;
          boolean been_here = false;
          boolean been_here2 = false;
          int8_t search_cat = -1;
          int16_t cat_min = -1, cat_max = -1, cat_param=0;
          char* json_token = strtok(p, "=,"); // drop everything before "="
          json_token = strtok(NULL, ",");
          if (json_token!=NULL) {
            client.flush();
          }
          while (client.available()) {
            if (client.read()=='{') {
              break;
            }
          }
          while (client.available() || json_token!=NULL) {
            if (client.available()) {
              char c = client.read();
              if ((c == 'P' || c == 'p') && t_flag != true) { p_flag = true; }
              if (c == 'V' || c == 'v') { v_flag = true; }
              if (c == 'T' || c == 't') { t_flag = true; }
              if (c == '}') { output = true; }
              if (isdigit(c)) {
                while (client.available() && j_char_idx < 10 && (isdigit(c) || c=='.')) {
                  json_temp[j_char_idx] = c;
                  c = client.read();
                  j_char_idx++;
                }
                json_temp[j_char_idx] = '\0';
                j_char_idx = 0;
                if (p_flag == true) {
                  json_parameter = atoi(json_temp);
                  p_flag = false;
                }
                if (v_flag == true) {
                  json_value = strtod(json_temp, NULL);
                  strcpy(json_value_string, json_temp);
                  v_flag = false;
                }
                if (t_flag == true) {
                  json_type = atoi(json_temp);
                  t_flag = false;
                }
              }
            } else {
              json_parameter = atoi(json_token);
            }
            if (output || json_token != NULL) {
              int temp_i=findLine(json_parameter,0,&cmd);
              if (p[2] == 'Q' && (temp_i<0 || cmd == CMD_UNKNOWN)) {
                json_token = strtok(NULL,",");
                continue;
              }

              output = false;
              if (!been_here || (p[2]=='K' && isdigit(p[4]))) {
                been_here = true;
              } else {
                client.println(F(","));
              }
              if (p[2]=='K' && !isdigit(p[4])) {
                uint16_t x=2;
                uint8_t cat=0;
                client.print(F("\"0\": { \"name\": \""));
                while (x<sizeof(ENUM_CAT)) {
                  char z = pgm_read_byte_far(pgm_get_far_address(ENUM_CAT)+x);
                  if (z == '\0') {
                    cat_min = pgm_read_word_far(pgm_get_far_address(ENUM_CAT_NR) + (cat*2) * sizeof(ENUM_CAT_NR[0]));
                    cat_max = pgm_read_word_far(pgm_get_far_address(ENUM_CAT_NR) + (cat*2+1) * sizeof(ENUM_CAT_NR[0]));
                    client.print(F("\", \"min\": "));
                    client.print(cat_min);
                    client.print(F(", \"max\": "));
                    client.print(cat_max);
                    if (x < sizeof(ENUM_CAT)-1 && cat < 42) {
                      cat++;
                      client.println(F(" },"));
                      client.print(F("\""));
                      client.print(cat);
                      client.print(F("\": { \"name\": \""));
                      x = x + 3;
                      continue;
                    } else {
                      client.print(F(" }"));
                      json_token = NULL;
                      break;
                    }
                  }
                  client.print(z);
                  x++;
                }
                json_token = NULL;
              }

              if (p[2]=='K' && isdigit(p[4])) {
                cat_param++;
                if (cat_min<0) {
                  search_cat = atoi(&p[4]);
                  cat_min = pgm_read_word_far(pgm_get_far_address(ENUM_CAT_NR) + (search_cat*2) * sizeof(ENUM_CAT_NR[0]));
                  cat_max = pgm_read_word_far(pgm_get_far_address(ENUM_CAT_NR) + (search_cat*2+1) * sizeof(ENUM_CAT_NR[0]));
                  cat_param = cat_min;
                }
                if (cat_param <= cat_max) {
                  json_parameter = cat_param;
                  if (cat_param == cat_max) {
                    json_token = NULL;
                  }
                } else {
                  json_token = NULL;
                }
              }

              if (p[2]=='Q' || (p[2]=='K' && isdigit(p[4]))) {
                i=findLine(json_parameter,0,&cmd);
                if (i<0 || cmd == CMD_UNKNOWN) {
                  continue;
                }
                int k=0;
                uint8_t type=get_cmdtbl_type(i);
                uint16_t enumstr_len = get_cmdtbl_enumstr_len(i);
                uint32_t enumstr = calc_enum_offset(get_cmdtbl_enumstr(i), enumstr_len);

                strcpy_PF(buffer, get_cmdtbl_desc(i));

                if (!been_here2 || p[2] == 'Q') {
                  been_here2=true;
                } else {
                  client.println(F(","));
                }

                client.print(F("  \""));
                client.print(json_parameter);
                client.println(F("\": {"));

                client.print(F("    \"name\": \""));
                client.print(buffer);
                client.println(F("\","));

                uint8_t div_unit_len=0;
                uint8_t div_data_type=0;
                uint8_t div_type=0;
                while(div_type!=VT_UNKNOWN){
                  div_type=pgm_read_byte_far(pgm_get_far_address(optbl[0].type) + k * sizeof(optbl[0]));
                  div_data_type=pgm_read_byte_far(pgm_get_far_address(optbl[0].data_type) + k * sizeof(optbl[0]));
                  div_unit_len=pgm_read_byte_far(pgm_get_far_address(optbl[0].unit_len) + k * sizeof(optbl[0]));
                  memcpy_PF(div_unit, pgm_read_word_far(pgm_get_far_address(optbl[0].unit) + k * sizeof(optbl[0])),div_unit_len);

                  if(type == div_type){
                    break;
                  }
                  k++;
                }

                if (p[2]=='Q') {
                  char* ret_val_str = query(json_parameter,json_parameter,1);
                  char* unit_str = NULL;
                  char* desc_str = NULL;
//                  if (ret_val_str == NULL) { i=-1; continue; }
                  if (div_data_type == DT_ENUM) {
                    unit_str = strstr(ret_val_str, "- ");
                    if (unit_str != NULL) {
                      desc_str = unit_str + 2;
                      // Terminate the value string one character before the found "- " string.
                      // -> the space between the value and "-" gets overwritten by "\0".
                      *(unit_str - 1) = '\0';
                      // Also terminate the unit string (there is no unit in ENUMs).
                      // -> the "-" gets overwritten by "\0"
                      *unit_str = '\0';
                    }
                  // If the unit just contains "\0", so the unit is U_NONE (this is also the case for
                  // VT_STRING, which has a unit, but it is already included at the end of the string).
                  } else if (div_unit_len <= 1) {
                    unit_str = strstr(ret_val_str, " ");
                    if (unit_str != NULL) {
                      // Terminate the value sring at the position of the found space.
                      *unit_str = '\0';
                      // If there is no unit at the end of the string, after an increment the pointer
                      // will point to the terminator of the original "ret_val_str" string.
                      // If there is a unit at the end of the string (for VT_STRING), after an increment
                      // the pointer will point to the first character of the unit in "ret_val_str".
                      unit_str++;
                    }
                  // For all other values, where a unit string is given in "optbl[]", we use the one from the
                  // string "ret_val_str". Instead we could also set the pointer to the address of "div_unit".
                  } else {
                    unit_str = strstr(ret_val_str, div_unit);
                    if (unit_str != NULL) {
                      // Terminate the value string 1 char before the found "div_unit" string.
                      // -> the space between the value and the unit gets overwritten by "\0".
                      *(unit_str - 1) = '\0';
                      // There is no need to do anything with the pointer unit_str,
                      // as it already points to the unit in "ret_val_str".
                    }
                  }

                  client.print(F("    \"value\": \""));
                  client.print(ret_val_str);
                  client.println(F("\","));

                  client.print(F("    \"unit\": \""));
                  client.print(unit_str);
                  client.println(F("\","));

                  client.print(F("    \"desc\": \""));
                  if (div_data_type == DT_ENUM) {
                    client.print(desc_str);
                  }
                  client.println(F("\","));
                }

                if (p[2] != 'Q') {
                  client.println(F("    \"possibleValues\": ["));
                  if (enumstr_len > 0) {
                    uint16_t x = 0;
                    uint16_t val = 0;
                    been_here=false;
                    while (x < enumstr_len) {
                      if (!been_here) {
                        been_here = true;
                      } else {
                        client.println(F(","));
                      }
                      client.print(F("      { \"enumValue\": \"")); 
                      if((byte)(pgm_read_byte_far(enumstr+x+1))!=' ' || type == VT_BIT) {         // ENUMs must not contain two consecutive spaces! Necessary because VT_BIT bitmask may be 0x20 which equals space
                        val=uint16_t((pgm_read_byte_far(enumstr+x) << 8)) | uint16_t(pgm_read_byte_far(enumstr+x+1));
                        x++;
                      }else{
                        val=uint16_t(pgm_read_byte_far(enumstr+x));
                      }
                      client.print(val);
                      client.print(F("\", \"desc\": \""));
                      //skip leading space
                      x = x + 2;
                      char z = pgm_read_byte_far(enumstr+x);
                      while (z != '\0') {
                        client.print(z);
                        x++;
                        z = pgm_read_byte_far(enumstr+x);
                      }
                      client.print(F("\" }"));
                      x++;
                    }
                  }
                  client.println();
                  client.println(F("    ],"));
                }

                client.print(F("    \"dataType\": "));
                client.print(div_data_type);
                client.println();

                client.print(F("  }"));
              }

              if (p[2]=='S') {
                Serial.print(F("Setting parameter "));
                Serial.print(json_parameter);
                Serial.print(F(" to "));
                Serial.print(json_value_string);
                Serial.print(F(" with type "));
                Serial.println(json_type);
                int status = set(json_parameter, json_value_string, json_type);
                client.print(F("  \""));
                client.print(json_parameter);
                client.println(F("\": {"));
                client.print(F("    \"status\": "));
                client.print(status);
                client.println();
                client.print(F("  }"));
              }
              if (json_token != NULL && ((p[2] != 'K' && !isdigit(p[4])) || p[2] == 'Q')) {
                json_token = strtok(NULL,",");
              }
            }
          }
          client.println();
          client.println(F("}"));
          client.flush();
          break;
        }

#ifdef LOGGER            
        if(p[1]=='D'){ // access datalog file
          if (p[2]=='0') {  // remove datalog file
            webPrintHeader();
            SD.remove("datalog.txt");
            File dataFile = SD.open("datalog.txt", FILE_WRITE);
            if (dataFile) {
              dataFile.println(F("Milliseconds;Date;Parameter;Description;Value;Unit"));
              dataFile.close();
              client.println(F(MENU_TEXT_DTR));
              Serial.println(F("File datalog.txt removed and recreated."));
            } else {
              client.println(F(MENU_TEXT_DTF));
            }
            webPrintFooter();
          } else if (p[2]=='G') {
            webPrintHeader();
      	    client.println(F("<A HREF='D'>" MENU_TEXT_DTD "</A><div align=center></div>"));

            printPStr(pgm_get_far_address(graph_html), sizeof(graph_html));

            webPrintFooter();
          } else {  // dump datalog file
            client.println(F("HTTP/1.1 200 OK"));
            client.println(F("Content-Type: text/plain"));
            client.println();

            File dataFile = SD.open("datalog.txt");
            // if the file is available, read from it:
            if (dataFile) {

              unsigned long startdump = millis();
              int logbuflen = 512;
              byte loglineBuf[logbuflen];
              int chars_read = 0;

              chars_read = dataFile.read(&loglineBuf , logbuflen);
              while (chars_read == logbuflen) {
                client.write(loglineBuf,logbuflen);
                chars_read = dataFile.read(&loglineBuf , logbuflen);
              }
              //final packet
              if (chars_read > 0) client.write(loglineBuf, chars_read);
              dataFile.close();

              Serial.print(F("Duration: "));
              Serial.println(millis()-startdump);
            } else {
              client.println(F(MENU_TEXT_DTO));
            }
          }
          break;
        }
#endif
        if (p[1]=='C'){ // dump configuration
          webPrintHeader();
          client.println(F(MENU_TEXT_CFG "<BR><BR>"));
//          client.println(F("BSB pins: "));
//          client.println(bus);
//          client.println(F("<BR><BR>"));

          client.print(F(MENU_TEXT_RAM ": "));
          client.print(freeRam());
          client.println(F(" Bytes <BR>"));

          myAddr = bus.getBusAddr();
          destAddr = bus.getBusDest();
          client.print(F(MENU_TEXT_BUS ": "));
          switch (bus_type) {
            case 0: client.print(F("BSB")); break;
            case 1: client.print(F("LPB")); break;
            case 2: client.print(F("PPS")); break;
          }
          if (bus_type != BUS_PPS) {
            client.print(F(" ("));
            client.print(myAddr);
            client.print(F(", "));
            client.print(destAddr);
            client.print(F(")"));
          } else {
            if (*PPS_write_enabled == 1) {
              client.print(F(" (" MENU_TEXT_BRW ")"));
            } else {
              client.print(F(" (" MENU_TEXT_BRO ")"));
            }
          }
          client.println(F("<BR>"));
          client.print(F(MENU_TEXT_MMD " "));
          client.println(monitor);
          client.print(F("<BR>" MENU_TEXT_VBL " "));
          client.print(verbose);
          client.println(F("<BR>"));
          
          #ifdef ONE_WIRE_BUS
          client.println(F(MENU_TEXT_OWP ": "));
          client.println(ONE_WIRE_BUS);
          client.println(F("<BR>"));
          #endif

          #ifdef DHT_BUS
          client.println(F(MENU_TEXT_DHP ": "));
          client.println(DHT_BUS);
          client.println(F("<BR>"));
          #endif

          client.println(F(MENU_TEXT_EXP ": "));
          for (int i=0; i<anz_ex_gpio; i++) {
            client.print (exclude_GPIO[i]);
            client.print(F(" "));
          }
          client.println(F("<BR>"));
          
          client.println(F(MENU_TEXT_MAC ": "));
          for (int i=0; i<=5; i++) {
            if (mac[i] < 10) {
              client.print(F("0"));
            }
            client.print(mac[i], HEX);
            client.print(F(" "));
          }
          client.println(F("<BR>"));

/*
          client.println(F("IP address: "));
          client.println(ip);
          client.println(F("<BR>"));
*/

          client.println(F(MENU_TEXT_AVT ": <BR>"));
          for (int i=0; i<numAverages; i++) {
            if (avg_parameters[i] > 0) {
              client.print (avg_parameters[i]);
              client.print(F(" - "));
              client.print(lookup_descr(avg_parameters[i])); 
              client.println(F("<BR>"));
            }
          }
          client.println(F("<BR>"));

          #ifdef LOGGER
          client.println(F(MENU_TEXT_LGP " "));
          client.print(log_interval);
          client.println(F(" " MENU_TEXT_SEC ": <BR>"));
          for (int i=0; i<numLogValues; i++) {
            if (log_parameters[i] > 0) {
              client.print (log_parameters[i]);
              client.print(F(" - "));
              if (log_parameters[i] < 20000) {
                client.print(lookup_descr(log_parameters[i])); 
              } else {
                if (log_parameters[i] == 20000) {
                  client.print(F(MENU_TEXT_BZ1));
                }
                if (log_parameters[i] == 20001) {
                  client.print(F(MENU_TEXT_BT1));
                }
                if (log_parameters[i] == 20002) {
                  client.print(F(MENU_TEXT_BZ2));
                }
                if (log_parameters[i] == 20003) {
                  client.print(F(MENU_TEXT_BT2));
                }
                if (log_parameters[i] == 20004) {
                  client.print(F(MENU_TEXT_TZ1));
                }
                if (log_parameters[i] == 20005) {
                  client.print(F(MENU_TEXT_TT1));
                }
                if (log_parameters[i] == 20006) {
                  client.println(F(MENU_TEXT_24A));
                }
                if (log_parameters[i] == 20007) {
                  client.print(F(MENU_TEXT_MXI));
                }
                if (log_parameters[i] == 20008) {
                  client.print(F(MENU_TEXT_MXS));
                }
                if (log_parameters[i] == 20009) {
                  client.print(F(MENU_TEXT_MXV));
                }
                if (log_parameters[i] >= 20100 && log_parameters[i] < 20200) {
                  client.print(F(MENU_TEXT_SN2));
                }
                if (log_parameters[i] >= 20200 && log_parameters[i] < 20300) {
                  client.print(F(MENU_TEXT_SN1));
                }
                if (log_parameters[i] == 30000) {
                  client.println(F(MENU_TEXT_BDT "<BR>"));
                  client.println(F(MENU_TEXT_BUT ": "));
                  if (log_unknown_only) {
                    client.println(F(MENU_TEXT_YES "<BR>"));
                  } else {
                    client.println(F(MENU_TEXT_NO "<BR>"));
                  }
                  client.println(F(MENU_TEXT_LBO ": "));
                  if (log_bc_only) {
                    client.println(F(MENU_TEXT_YES "BR>"));
                  } else {
                    client.println(F(MENU_TEXT_NO "<BR>"));
                  }
                }
              }
              client.println(F("<BR>"));
            }
          }
          #endif

          client.println(F("<BR>"));
          webPrintFooter();

          Serial.println(F("EEPROM dump:"));
          for (uint16_t x=0; x<EEPROM.length(); x++) {
            uint8_t i = EEPROM.read(x);
            if (i < 16) {
              Serial.print(F("0"));
            }
            Serial.print(i, HEX);
            Serial.print(F(" "));
          }
          
          break;
        }
        if (p[1]=='L' && p[2]=='B' && p[3]=='='){
          if (p[4]=='1') {
            log_bc_only=1;
          } else {
            log_bc_only=0;
          }
          webPrintHeader();
          client.print(F(MENU_TEXT_LBO ": "));
          if (log_bc_only) {
            client.println(F(MENU_TEXT_YES "<BR>"));
          } else {
            client.println(F(MENU_TEXT_NO "<BR>"));
          }
          webPrintFooter();
          break;
        }
        if (p[1]=='L' && p[2]=='U' && p[3]=='='){
          if (p[4]=='1') {
            log_unknown_only=1;
          } else {
            log_unknown_only=0;
          }
          webPrintHeader();
          client.print(F(MENU_TEXT_BUT ": "));
          if (log_unknown_only) {
            client.println(F(MENU_TEXT_YES "<BR>"));
          } else {
            client.println(F(MENU_TEXT_NO "<BR>"));
          }
          webPrintFooter();
          break;
        }
        if (p[1]=='L' && p[2]=='='){ // logging configuration: L=<interval>,<parameter 1>,<parameter 2>,...,<parameter20>
          webPrintHeader();
          char* log_token = strtok(p,"=,");  // drop everything before "="
          log_token = strtok(NULL, "=,");   // first token: interval
          if (log_token != 0) {
            log_interval = atoi(log_token);
//            if (log_interval < 10) {log_interval = 10;}
            lastLogTime = millis();
            lastMQTTTime = millis();
            client.print(F(MENU_TEXT_LGI ": "));
            client.print(log_interval);
            client.println(F(" " MENU_TEXT_SEC "<BR>"));
          }
          log_token = strtok(NULL,"=,");    // subsequent tokens: logging parameters
          int token_counter = 0;
          if (log_token != 0) {
            for (int i=0;i<numLogValues;i++) {
              log_parameters[i] = 0;
            }
            client.println(F(MENU_TEXT_LGN ": "));
          }
          while (log_token!=0) {
            int log_parameter = atoi(log_token);
            if (token_counter < numLogValues) {
              log_parameters[token_counter] = log_parameter; 
              client.print(log_parameters[token_counter]);
              client.println(F(" "));
              token_counter++;
            }
            log_token = strtok(NULL,"=,");
          }
          webPrintFooter();
          break;
        }
        if (p[1]=='P') {
          webPrintHeader();

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

          client.print(F(MENU_TEXT_BUS ": "));
          if (p[2]=='0') {
            bus_type=bus.setBusType(BUS_BSB, myAddr, destAddr);
            len_idx = 3;
            pl_start = 9;
            client.println(F("BSB"));
          }
          if (p[2]=='1') {
            bus_type=bus.setBusType(BUS_LPB, myAddr, destAddr);
            len_idx = 1;
            pl_start = 13;
            client.println(F("LPB"));
          } 
          if (p[2]=='2') {
            bus_type=bus.setBusType(BUS_PPS, myAddr);
            len_idx = 9;
            pl_start = 6;
            client.println(F("PPS"));
          }           
          if (bus_type != BUS_PPS) {
            client.print(F(" ("));
            client.print(myAddr);
            client.print(F(", "));
            client.print(destAddr);
            client.print(F(")"));
          } else {
            if (*PPS_write_enabled == 1) {
              client.print(F(" " MENU_TEXT_BRW));
            } else {
              client.print(F(" " MENU_TEXT_BRO));
            }
          }

          SetDevId();
          webPrintFooter();
          break;
        }
        if (p[1]=='N'){           // Reset Arduino and clear EEPROM
#ifdef RESET
          webPrintHeader();
          if (p[2]=='E') {
            client.println(F("Clearing EEPROM (affects MAX! devices and PPS-Bus settings)...<BR>"));
          }
          webPrintFooter();
          client.stop();
#ifdef LOGGER
          File dataFile = SD.open("datalog.txt", FILE_WRITE);
          if (dataFile) {
            dataFile.close();
          }
#endif
          if (p[2]=='E') {
            for (uint16_t x=0; x<EEPROM.length(); x++) {
              EEPROM.write(x, 0);
            }
            Serial.println(F("Cleared EEPROM"));
          }
          client.println(F("Restarting Arduino..."));
          asm volatile ("  jmp 0");
          while (1==1) {}
#endif
          break;
        }
        // print queries
        webPrintHeader();
        char* range;
        char* line_start;
        char* line_end;
        int start=-1;
        int end=-1;
        range = strtok(p,"/");
        while(range!=0){
          if(range[0]=='T'){
#ifdef ONE_WIRE_BUS
            ds18b20();
#endif
#ifdef DHT_BUS
            dht22();
#endif
          }else if(range[0]=='X'){ // handle MAX command
#ifdef MAX_CUL
            int max_avg_count = 0;
            float max_avg = 0;
            char max_id[11];
            for (int x=0;x<20;x++) {
              if (max_cur_temp[x] > 0) {
                max_avg += (float)(max_cur_temp[x] & 0x1FF) / 10;
                max_avg_count++;
                for (int y=0;y<10;y++) {
                  max_id[y] = pgm_read_byte_far(pgm_get_far_address(max_device_list)+(x*10)+y);
                }
                max_id[10] = '\0';
                client.print(F("<tr><td>"));
                client.print(max_id);
                client.print(F(" ("));
                client.print(max_devices[x], HEX);
                client.print(F("): "));
                client.print((float)max_cur_temp[x] / 10);
                client.print(F(" / "));
                client.print((float)max_dst_temp[x] / 2);
                if (max_valve[x] > -1) {
                  client.print(F(" ("));
                  client.print(max_valve[x]);
                  client.print(F("%)"));
                }
                client.println(F("</td></tr>"));
              }
            }
            if (max_avg_count > 0) {
              client.print(F("<tr><td>"));
              client.print(F("AvgMax: "));
              client.print(max_avg / max_avg_count);
              client.println(F("</td></tr>"));
            } else {
              client.println(F("<tr><td>" MENU_TEXT_MXN "</td></tr>"));
            }
#endif
          }else if(range[0]=='A') { // handle average command
            if (range[1]=='=') {
              char* avg_token = strtok(range,"=,");  // drop everything before "="
              avg_token = strtok(NULL,"=,");    // subsequent tokens: average parameters
              int token_counter = 0;
              if (avg_token != 0) {
                for (int i=0;i<numAverages;i++) {
                  avg_parameters[i] = 0;
                  avgValues[i] = 0;
                  avgValues_Old[i] = -9999;
                  avgValues_Current[i] = 0;
                }
                avgCounter = 1;
#ifdef LOGGER
                SD.remove("averages.txt");
#endif
                client.println(F(MENU_TEXT_24N ": "));
              }
              while (avg_token!=0) {
                int avg_parameter = atoi(avg_token);
                if (token_counter < numAverages) {
                  avg_parameters[token_counter] = avg_parameter; 
                  client.print(avg_parameters[token_counter]);
                  client.println(F(" "));
                  token_counter++;
                }
                avg_token = strtok(NULL,"=,");
              }
            } else {
              for (int i=0; i<numAverages; i++) {
                if (avg_parameters[i] > 0) {
                  client.print(F("<tr><td>\n"));
                  client.print(avg_parameters[i]);
                  client.print(F(" Avg"));
                  client.print(lookup_descr(avg_parameters[i]));            
                  client.print(F(": "));
                  double rounded = round(avgValues[i]*10);
                  client.print(rounded/10);
                  client.print(F(" "));

                  uint32_t c=0;
                  int line=findLine(avg_parameters[i],0,&c);
                  int k=0;
                  uint8_t type=get_cmdtbl_type(line);
                  uint8_t div_unit_len=0;
                  uint8_t div_type=0;
                  while(div_type!=VT_UNKNOWN){
                    div_type=pgm_read_byte_far(pgm_get_far_address(optbl[0].type) + k * sizeof(optbl[0]));
                    div_unit_len=pgm_read_byte_far(pgm_get_far_address(optbl[0].unit_len) + k * sizeof(optbl[0]));
                    memcpy_PF(div_unit, pgm_read_word_far(pgm_get_far_address(optbl[0].unit) + k * sizeof(optbl[0])),div_unit_len);
                    if(type == div_type){
                      break;
                    }
                    k++;
                  }
                  client.println(div_unit);

                  client.println(F("</td></tr>"));
                }
              }
            }
          }else if(range[0]=='G'){ // handle gpio command
            uint8_t val;
            uint8_t pin;
            bool error = false;
            p=range+1;
            if(!isdigit(*p)){   // now we check for digits
              client.println(F(MENU_TEXT_ER1));
              break;
            }
            pin=(uint8_t)atoi(p);       // convert until non-digit char is found
            for (int i=0; i < anz_ex_gpio; i++) {
              if (pin==exclude_GPIO[i]) {
                error = true;
              }
            }
            if (error==true) {
              client.println(F(MENU_TEXT_ER7));
              break;
            }

            char* dir_token = strchr(range,',');
            dir_token++;
            p=strchr(p,'=');    // search for '=' sign
            if(p==NULL){        // no match -> query value
              if (dir_token!=NULL) {
                if (*dir_token=='I') {
                  pinMode(pin, INPUT);
                  Serial.print(F("Pin "));
                  Serial.print(pin);
                  Serial.println(F(" set to input."));
                }
              }
              val=digitalRead(pin);
            }else{ // set value
              p++;
              if(!strncasecmp(p,"on",2) || !strncasecmp(p,"high",2) || *p=='1'){
                val=HIGH;
              }else{
                val=LOW;
              }
              pinMode(pin, OUTPUT); // TODO: does this case a problem if already set as output?
              digitalWrite(pin, val);
            }
            client.print(F("GPIO"));
            client.print(pin);
            client.print(F(": "));
            client.print(val!=LOW?F("1"):F("0"));
          }else if(range[0]=='B'){
            if(range[1]=='0'){ // reset furnace duration
              client.println(F(MENU_TEXT_BRS ".<br>"));
              brenner_duration=0;
              brenner_count=0;
              brenner_duration_2=0;
              brenner_count_2=0;
              TWW_duration=0;
              TWW_count=0;
            }else{
              // query brenner duration
              client.print(F("<tr><td>Brenner Laufzeit Stufe 1: "));
              client.print(brenner_duration);
              client.println(F("</td></tr><tr><td>"));
              client.print(F("Brenner Takte Stufe 1: "));
              client.print(brenner_count);
              client.println(F("</td></tr>"));
              client.print(F("<tr><td>Brenner Laufzeit Stufe 2: "));
              client.print(brenner_duration_2);
              client.println(F("</td></tr><tr><td>"));
              client.print(F("Brenner Takte Stufe 2: "));
              client.print(brenner_count_2);
              client.println(F("</td></tr>"));
              client.print(F("<tr><td>TWW Laufzeit: "));
              client.print(TWW_duration);
              client.println(F("</td></tr><tr><td>"));
              client.print(F("TWW Takte: "));
              client.print(TWW_count);
              client.println(F("</td></tr>"));
            }
          }else{
            if(range[0]=='K'){
              uint8_t cat,search_cat;
              uint16_t line;
              int i;
              uint32_t c;
              i=0;
              start=-1;
              end=-1;
              search_cat=atoi(&range[1]);
              c=get_cmdtbl_cmd(i);
              while(c!=CMD_END){
                cat=get_cmdtbl_category(i);
                if(cat==search_cat){
                  if(start<0){
                    line=get_cmdtbl_line(i);
                    start=line;
                  }
                }else{
                  if(start>=0){
                    line=get_cmdtbl_line(i-1);
                    end=line;
                    break;
                  }
                }
                i++;
                c=get_cmdtbl_cmd(i);
              }
              if(end<start){
                end=start;
              }
            }else{
              // split range
              line_start=range;
              line_end=strchr(range,'-');
              if(line_end==NULL){
                line_end=line_start;
              }else{
                *line_end='\0';
                line_end++;
              }
              start=atoi(line_start);
              end=atoi(line_end);
            }
            query(start,end,0);
          }

          range = strtok(NULL,"/");
        } // endwhile
        webPrintFooter();
        break;
      } // endif, client available

      delay(1);
      loopCount++;
      if(loopCount > 1000) {
        client.stop();
        Serial.println("\r\nTimeout");
      }

    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  } // endif, client

#ifdef MQTTBrokerIP

#ifdef MQTTUsername
  const char MQTTUser[] = MQTTUsername;
#else
  const char* MQTTUser = NULL;
#endif
#ifdef MQTTPassword
  const char MQTTPass[] = MQTTPassword;
#else
  const char* MQTTPass = NULL;
#endif

  if ((((millis() - lastMQTTTime >= (log_interval * 1000)) && log_interval > 0) || log_now > 0) && numLogValues > 0) {
    if (!MQTTClient.connected()) {
      MQTTClient.setServer(MQTTBroker, 1883);
      int retries = 0;
      while (!MQTTClient.connected() && retries < 3) {
        MQTTClient.connect("BSB-LAN", MQTTUser, MQTTPass);
        retries++;
        if (!MQTTClient.connected()) {
          delay(1000);
          Serial.println(F("Failed to connect to MQTT broker, retrying..."));
        }
      }
    }
    for (int i=0; i < numLogValues; i++) {
      if (log_parameters[i] > 0 && log_parameters[i] < 20000) {
        if (MQTTClient.connected()) {
/*
          String MQTTPayload = "";
          MQTTPayload.concat(F("{\""));
          MQTTPayload.concat(lookup_descr(log_parameters[i]));
          MQTTPayload.concat(F("\":\""));
          MQTTPayload.concat(strtok(query(log_parameters[i],log_parameters[i],1)," "));
          MQTTPayload.concat(F("\"}"));
*/

#ifdef MQTTTopicPrefix
          String MQTTTopic = MQTTTopicPrefix;
          MQTTTopic.concat(F("/"));
#else
          String MQTTTopic = "BSB-LAN/";
#endif
          MQTTTopic.concat(String(log_parameters[i]));

          MQTTClient.publish(MQTTTopic.c_str(), strtok(query(log_parameters[i],log_parameters[i],1)," "));
        }
      }
    }
    MQTTClient.disconnect();
    lastMQTTTime = millis();
  }
#endif


#ifdef LOGGER

  if (((millis() - lastLogTime >= (log_interval * 1000)) && log_interval > 0) || log_now > 0) {
//    SetDateTime(); // receive inital date/time from heating system

    log_now = 0;
    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    if (dataFile) {
      for (int i=0; i < numLogValues; i++) {
        if (log_parameters[i] > 0 && (log_parameters[i] < 20006 || log_parameters[i] > 20009) && log_parameters[i] != 30000) {
          dataFile.print(millis());
          dataFile.print(F(";"));
          dataFile.print(GetDateTime(date)); // get current time from heating system
          dataFile.print(F(";"));
          dataFile.print(log_parameters[i]);
          dataFile.print(F(";"));
        }
        if (log_parameters[i] > 0 && log_parameters[i] < 20000) {
          dataFile.print(lookup_descr(log_parameters[i]));
          dataFile.print(F(";"));
          dataFile.print(strtok(query(log_parameters[i],log_parameters[i],1)," "));
          dataFile.print(F(";"));
          uint32_t c=0;
          int line=findLine(log_parameters[i],0,&c);
          int k=0;
          uint8_t type=get_cmdtbl_type(line);
          uint8_t div_unit_len=0;
          uint8_t div_type=0;
          while(div_type!=VT_UNKNOWN){
            div_type=pgm_read_byte_far(pgm_get_far_address(optbl[0].type) + k * sizeof(optbl[0]));
            div_unit_len=pgm_read_byte_far(pgm_get_far_address(optbl[0].unit_len) + k * sizeof(optbl[0]));
            memcpy_PF(div_unit, pgm_read_word_far(pgm_get_far_address(optbl[0].unit) + k * sizeof(optbl[0])),div_unit_len);
            if(type == div_type){
              break;
            }
            k++;
          }
          dataFile.println(div_unit);
        } else {
          if (log_parameters[i] == 20000) {
            dataFile.print(F(MENU_TEXT_BZ1));
            dataFile.print(F(";"));
            dataFile.println(brenner_duration);
          }
          if (log_parameters[i] == 20001) {
            dataFile.print(F(MENU_TEXT_BT1));
            dataFile.print(F(";"));
            dataFile.println(brenner_count);
          }
          if (log_parameters[i] == 20002) {
            dataFile.print(F(MENU_TEXT_BZ2));
            dataFile.print(F(";"));
            dataFile.println(brenner_duration_2);
          }
          if (log_parameters[i] == 20003) {
            dataFile.print(F(MENU_TEXT_BT2));
            dataFile.print(F(";"));
            dataFile.println(brenner_count_2);
          }
          if (log_parameters[i] == 20004) {
            dataFile.print(F(MENU_TEXT_TZ1));
            dataFile.print(F(";"));
            dataFile.println(TWW_duration);
          }
          if (log_parameters[i] == 20005) {
            dataFile.print(F(MENU_TEXT_TT1));
            dataFile.print(F(";"));
            dataFile.println(TWW_count);
          }
          if (log_parameters[i] == 20006) {
            for (int i=0; i<numAverages; i++) {
              if (avg_parameters[i] > 0) {
                dataFile.print(millis());
                dataFile.print(F(";"));
                dataFile.print(GetDateTime(date)); // get current time from heating system
                dataFile.print(F(";"));
                dataFile.print(avg_parameters[i]);
                dataFile.print(F(";"));
                dataFile.print(F("Avg_"));
                dataFile.print(lookup_descr(avg_parameters[i]));            
                dataFile.print(F(";"));
                double rounded = round(avgValues[i]*10);
                dataFile.print(rounded/10);
                dataFile.print(F(";"));

                uint32_t c=0;
                int line=findLine(avg_parameters[i],0,&c);
                int k=0;
                uint8_t type=get_cmdtbl_type(line);
                uint8_t div_unit_len=0;
                uint8_t div_type=0;
                while(div_type!=VT_UNKNOWN){
                  div_type=pgm_read_byte_far(pgm_get_far_address(optbl[0].type) + k * sizeof(optbl[0]));
                  div_unit_len=pgm_read_byte_far(pgm_get_far_address(optbl[0].unit_len) + k * sizeof(optbl[0]));
                  memcpy_PF(div_unit, pgm_read_word_far(pgm_get_far_address(optbl[0].unit) + k * sizeof(optbl[0])),div_unit_len);
                  if(type == div_type){
                    break;
                  }
                  k++;
                }
                dataFile.println(div_unit);
              }
            }
          }
#ifdef MAX_CUL
          if (log_parameters[i] > 20006 && log_parameters[i] < 20010) {
            int max_idx = 0;
            while (max_devices[max_idx] > 0) {
              if ((log_parameters[i]<20009 && max_dst_temp[max_idx] > 0) || (log_parameters[i]==20009 && max_valve[max_idx] > -1)) {
                char max_id[11];
                for (int y=0;y<10;y++) {
                  max_id[y] = pgm_read_byte_far(pgm_get_far_address(max_device_list)+(max_idx*10)+y);
                }
                max_id[10] = '\0';

                dataFile.print(millis());
                dataFile.print(F(";"));
                dataFile.print(GetDateTime(date)); // get current time from heating system
                dataFile.print(F(";"));
                dataFile.print(log_parameters[i]);
                dataFile.print(F(";"));
                switch (log_parameters[i]) {
                  case 20007: dataFile.print(F("MaxCurTemp_")); break;
                  case 20008: dataFile.print(F("MaxDstTemp_")); break;
                  case 20009: dataFile.print(F("MaxValvePc_")); break;
                }
                dataFile.print(max_id);
                dataFile.print(F(";"));
                switch (log_parameters[i]) {
                  case 20007: dataFile.println((float)max_cur_temp[max_idx]/10); break;
                  case 20008: dataFile.println((float)max_dst_temp[max_idx]/2); break;
                  case 20009: dataFile.println(max_valve[max_idx]); break;
                }
              }
              max_idx++;
            }
          }
#endif
#ifdef DHT_BUS
          if (log_parameters[i] >= 20100 && log_parameters[i] < 20200) {
            int log_sensor = log_parameters[i] - 20100;
            int chk = DHT.read22(DHT_Pins[log_sensor]);
            Serial.println(chk);
            double hum = DHT.humidity;
            double temp = DHT.temperature;
            if (hum > 0 && hum < 101) {
              dataFile.print(F("Temperature "));
              dataFile.print(log_sensor);
              dataFile.print(F(";"));
              dataFile.println(temp);

              dataFile.print(millis());
              dataFile.print(F(";"));
              dataFile.print(GetDateTime(date)); // get current time from heating system
              dataFile.print(F(";"));
              dataFile.print(log_parameters[i]);
              dataFile.print(F(";"));
              dataFile.print(F("Humidity "));
              dataFile.print(log_sensor);
              dataFile.print(F(";"));
              dataFile.println(hum);
             }
          }
#endif
#ifdef ONE_WIRE_BUS
          if (log_parameters[i] >= 20200 && log_parameters[i] < 20300) {
            int log_sensor = log_parameters[i] - 20200;
            sensors.requestTemperatures(); // Send the command to get temperatures
            float t=sensors.getTempCByIndex(log_sensor);
            dataFile.print(F("Temperature "));
            dataFile.print(log_sensor);
            dataFile.print(F(";"));
            dataFile.println(t);
          }
#endif
        }
      } 
      dataFile.close();
   } else {
    // if the file isn't open, pop up an error:
      client.println(F(MENU_TEXT_DTO));
      Serial.println(F("Error opening datalog.txt!"));
    }
    lastLogTime = millis();
  }
#endif

// Calculate 24h averages
  if (millis() - lastAvgTime >= 60000) {
    if (avgCounter == 1441) {
      for (int i=0; i<numAverages; i++) {
        avgValues_Old[i] = avgValues[i];
        avgValues_Current[i] = 0;
      }
      avgCounter = 1;
    }
    for (int i=0; i<numAverages; i++) {
      if (avg_parameters[i] > 0) {
        double reading = strtod(query(avg_parameters[i],avg_parameters[i],1),NULL);
        if (isnan(reading)) {} else {
          avgValues_Current[i] = (avgValues_Current[i] * (avgCounter-1) + reading) / avgCounter;
          if (avgValues_Old[i] == -9999) {
            avgValues[i] = avgValues_Current[i];
          } else {
            avgValues[i] = ((avgValues_Old[i]*(1440-avgCounter))+(avgValues_Current[i]*avgCounter)) / 1440;
          }
        }
      }
    }

    avgCounter++;
    lastAvgTime += 60000;

#ifdef LOGGER

// write averages to SD card to protect from power off

    if (SD.exists("averages.txt")) {
      SD.remove("averages.txt");
    }
    File avgfile = SD.open("averages.txt", FILE_WRITE);
    if (avgfile) {
      for (int i=0; i<numAverages; i++) {
        avgfile.println(avgValues[i]);
        avgfile.println(avgValues_Old[i]);
        avgfile.println(avgValues_Current[i]);
      }
      avgfile.println(avgCounter);
      avgfile.close();
    }

#endif

#ifdef WATCH_SOCKETS
    ShowSockStatus();
    checkSockStatus();
#endif

// while we are here, update date/time as well...
//    SetDateTime();
  }
// end calculate averages

#ifdef CUSTOM_COMMANDS
{
custom_timer = millis();
#include "BSB_lan_custom.h"
}
#endif

#ifdef MAX_CUL
  byte max_str_index = 0;
  while (max_cul.available()) {
    c = max_cul.read();
//    Serial.print(c);
    if ((c!='\n') && (c!='\r') && (max_str_index<60)){
      buffer[max_str_index++]=c;
    } else {
//      Serial.println();
      break;
    }
  }
  if (max_str_index > 0) {
    if (buffer[0] == 'Z') {
      char* max_hex_str = (char*)malloc(9);
      char max_id[11] = { 0 };
      boolean known_addr = false;
      boolean known_eeprom = false;

      strncpy(max_hex_str, buffer+7, 2);
      max_hex_str[2]='\0';
      uint8_t max_msg_type = (uint8_t)strtoul(max_hex_str, NULL, 16);
      strncpy(max_hex_str, buffer+1, 2);
      max_hex_str[2]='\0';
      uint8_t max_msg_len = (uint8_t)strtoul(max_hex_str, NULL, 16);

      if (max_msg_type == 0x02) {
        strncpy(max_hex_str, buffer+15, 6);        
      } else {
        strncpy(max_hex_str, buffer+9, 6);
      }
      max_hex_str[6]='\0';
      int32_t max_addr = (int32_t)strtoul(max_hex_str,NULL,16);
      int max_idx=0;
      for (max_idx=0;max_idx<20;max_idx++) {
        if (max_addr == max_devices[max_idx]) {
          known_addr = true;
          break;
        }
      }

      if (max_msg_type == 0x00) {     // Device info after pressing pairing button
        for (int x=0;x<10;x++) {
          strncpy(max_hex_str, buffer+29+(x*2), 2);
          max_hex_str[2]='\0';
          max_id[x] = (char)strtoul(max_hex_str,NULL,16);
        }
        max_id[10] = '\0';
        Serial.println(F("MAX device info received: "));
        Serial.println(max_addr, HEX);
        Serial.println(max_id);

        int32_t max_addr_temp=0;
        for (int x=0;x<20;x++) {
          EEPROM.get(500 + 15 * x, max_addr_temp);
          if (max_addr_temp == max_addr) {
            Serial.println(F("Device already in EEPROM"));
            known_eeprom = true;
            break;
          }
        }

        if (!known_eeprom) {
          for (int x=0;x<20;x++) {
            EEPROM.get(500+15*x, max_addr_temp);
            if (max_addr_temp < 1) {
              EEPROM.put(500+15*x, max_addr);
              EEPROM.put(500+15*x+4, max_id);
/*
              int32_t temp1;
              char temp2[11] = { 0 };
              EEPROM.get(500+15*x, temp1);
              EEPROM.get(500+15*x+4, temp2);
              Serial.println(temp1, HEX);
              Serial.println(temp2);
*/
              Serial.println(F("Device stored in EEPROM"));
              InitMaxDeviceList();
              break;
            }
          }
        }
      }

      if (max_msg_type == 0x02) {
        strncpy(max_hex_str, buffer+27, 2);        
        max_hex_str[2]='\0';
        max_valve[max_idx] = (uint32_t)strtoul(max_hex_str,NULL,16);
        Serial.println(F("Valve position from associated thermostat received:"));
        Serial.println(max_addr, HEX);
        Serial.println((max_valve[max_idx]));
      }

      if ((max_msg_type == 0x42 || max_msg_type == 0x60) && known_addr == true) {   // Temperature from thermostats
        uint8_t temp_str_offset;
        uint32_t max_temp_status;
        uint8_t str_len;

        switch(max_msg_len) {
          case 0x0C: temp_str_offset = 23; str_len = 4; break;
          case 0x0E: temp_str_offset = 25; str_len = 8; break;
          default: temp_str_offset = 0; str_len = 8; break;
        }
        strncpy(max_hex_str, buffer+temp_str_offset, str_len);
        max_hex_str[str_len]='\0';
        max_temp_status = (uint32_t)strtoul(max_hex_str,NULL,16);
        Serial.println(max_msg_len);
        Serial.println(max_temp_status, HEX);
        if (max_msg_type == 0x42) {
          max_cur_temp[max_idx] = (((max_temp_status & 0x8000) >> 7) + ((max_temp_status & 0xFF)));
          max_dst_temp[max_idx] = (max_temp_status & 0x7F00) >> 8;
        }
        if (max_msg_type == 0x60) {
          max_cur_temp[max_idx] = (max_temp_status & 0x0100) + (max_temp_status & 0xFF);
          max_dst_temp[max_idx] = (max_temp_status & 0xFF0000) >> 16;
          max_valve[max_idx] = (max_temp_status & 0xFF000000) >> 24;
        }

        Serial.println(F("MAX temperature message received: "));
        Serial.println(max_addr, HEX);
        Serial.println(((float)max_cur_temp[max_idx] / 10));
        Serial.println((float)(max_dst_temp[max_idx] / 2));
        Serial.println((max_valve[max_idx]));
      }
      free(max_hex_str);
    }
  }
#endif

} // --- loop () ---

#ifdef WIFI
void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
#endif

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

  switch (bus_type) {
    case 0:
      len_idx = 3;
      pl_start = 9;
      break;
    case 1:
      len_idx = 1;
      pl_start = 13;
      break;
    case 2:
      len_idx = 9;
      pl_start = 6;
      break;
  }

  // The computer hardware serial interface #0:
  //   115,800 bps, 8 data bits, no parity
  Serial.begin(115200, SERIAL_8N1); // hardware serial interface #0
  Serial.println(F("READY"));
  Serial.print(F("Size of cmdtbl1: "));
  Serial.println(sizeof(cmdtbl1));
  Serial.print(F("Size of cmdtbl2: "));
  Serial.println(sizeof(cmdtbl2));
  Serial.print(F("free RAM:"));
  Serial.println(freeRam());
#ifndef IPAddr
#ifdef WIFI
  IPAddress ip = WiFi.localIP();
#else
  IPAddress ip = Ethernet.localIP();
#endif
#endif
  Serial.println(ip);

#ifdef WIFI
  int status = WL_IDLE_STATUS;
  // initialize serial for ESP module
  Serial3.begin(115200);
/*
  delay(500);
  Serial3.println(F("AT+UART_CUR=230400,8,1,0,0"));
  Serial3.begin(223400);
*/
  // initialize ESP module
  WiFi.init(&Serial3);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

#ifdef IPAddr
  WiFi.config(ip);
#endif

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  
  printWifiStatus();
#endif

  for (int i=PPS_TWS;i<=PPS_BRS;i++) {
    uint16_t f=0;
    EEPROM.get(sizeof(uint16_t)*i, f);
    if (f > 0 && f < 0xFFFF && i != PPS_RTI) {
      Serial.print(F("Reading "));
      Serial.print(f);
      Serial.print(F(" from EEPROM slot "));
      Serial.println(i);
      pps_values[i] = f;
    }
  }


#ifdef LOGGER
  // disable w5100 while setting up SD
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
  Serial.print(F("Starting SD.."));
  if(!SD.begin(4)) Serial.println(F("failed"));
  else Serial.println(F("ok"));

#else
  // enable w5100 SPI
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);

  // disable SD Card
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
#endif

  // start the Ethernet connection and the server:
#ifndef WIFI
#ifdef GatewayIP        // assume that DNS is equal to gateway
#ifdef SubnetIP
  Ethernet.begin(mac, ip, gateway, gateway, subnet);
#else
  Ethernet.begin(mac, ip, gateway, gateway);
#endif
#else
  Ethernet.begin(mac, ip);
#endif 
#endif

#ifdef LOGGER
  digitalWrite(10,HIGH);
#endif

  Serial.println(F("Waiting 3 seconds to give Ethernet shield time to get ready..."));  // ...and flash the LED during that time...

  pinMode(LED_BUILTIN, OUTPUT);
  for (int i=0; i<3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(500);                       // wait for a second
  }
  server.begin();

#ifdef ONE_WIRE_BUS
  // check ds18b20 sensors
  sensors.begin();
  numSensors=sensors.getDeviceCount();
  Serial.print(F("numSensors: "));
  Serial.println(numSensors);
#endif

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
Serial.println(enum_page, HEX);
Serial.println(temp_offset1, HEX);
Serial.println(temp_offset2, HEX);
Serial.println(pgm_get_far_address(LAST_ENUM), HEX);
Serial.println(pgm_get_far_address(ENUM10513), HEX);
Serial.println(pgm_get_far_address(ENUM10510), HEX);
Serial.println(pgm_get_far_address(ENUM8008), HEX);
Serial.println(pgm_get_far_address(ENUM8007), HEX);
Serial.println(pgm_get_far_address(ENUM8006), HEX);
Serial.println(pgm_get_far_address(ENUM20), HEX);

Serial.println((uint32_t)&ENUM20, HEX);
Serial.println(pgm_get_far_address(ENUM20), HEX);
Serial.println((uint32_t)&LAST_ENUM, HEX);
Serial.println(pgm_get_far_address(ENUMLASTENUM), HEX);
//Serial.println(temp_offset1, HEX);
Serial.println(temp_offset2, HEX);

index_first_enum = 0;
for (int i=0; i<=LAST_ENUM_NR; i++) {
  index_first_enum=findLine(i, 0, &c);
  temp_offset1 = pgm_read_word_far(pgm_get_far_address(cmdtbl[0].enumstr) + index_first_enum * sizeof(cmdtbl[0]));
  if (temp_offset1 > 0 && temp_offset1 < 65535) {
    Serial.print(i);
    Serial.print(F("\t"));
    Serial.println(temp_offset1, HEX);
  }
}
*/

// initialize average calculation

  for (int i=0; i<numAverages; i++) {
    avgValues[i] = 0;
    avgValues_Old[i] = -9999;
    avgValues_Current[i] = 0;
  }

#ifdef WATCH_SOCKETS
  unsigned long thisTime = millis();

  for(int i=0;i<MAX_SOCK_NUM;i++) {
    connectTime[i] = thisTime;
  }
#endif

#ifdef LOGGER

// restore average 

  if (SD.exists("averages.txt")) {
    File avgfile = SD.open("averages.txt", FILE_READ);
    if (avgfile) {
      char c;
      char num[10];
      int x;
      for (int i=0; i<numAverages; i++) {
        c = avgfile.read();
        x = 0;
        while (avgfile.available() && c != '\n') {
          num[x] = c;
          x++;
          c = avgfile.read();
        }
        num[x]='\0';
        avgValues[i] = atof(num);

        c = avgfile.read();
        x = 0;
        while (avgfile.available() && c != '\n') {
          num[x] = c;
          x++;
          c = avgfile.read();
        }
        num[x]='\0';
        avgValues_Old[i] = atof(num);

        c = avgfile.read();
        x = 0;
        while (avgfile.available() && c != '\n') {
          num[x] = c;
          x++;
          c = avgfile.read();
        }
        num[x]='\0';
        avgValues_Current[i] = atof(num);
      }

      c = avgfile.read();
      x = 0;
      while (avgfile.available() && c != '\n') {
        num[x] = c;
        x++;
        c = avgfile.read();
      }
      num[x]='\0';
      avgCounter = atoi(num);
    }
    avgfile.close();
  }

#endif

  if (bus_type != BUS_PPS) {
// receive inital date/time from heating system
    SetDateTime();
  
// receive device family (Gerätefamilie) and device variant (Gerätevariant) from heating system
    SetDevId();
  }

#ifdef MAX_CUL
  if (max_cul.connect({MAX_CUL}, 2323)) {
    Serial.println(F("Connected to max_cul"));
  } else {
    Serial.println(F("Connection to max_cul failed"));
  }

  InitMaxDeviceList();
  
#endif

#include "BSB_lan_custom_setup.h"

}
