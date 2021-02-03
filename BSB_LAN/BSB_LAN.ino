/*
 *
 * BSB Boiler-System-Bus LAN Interface
 *
 * ATTENTION:
 *       There is no warranty that this system will not damage your heating system!
 *
 * Authors Gero Schumacher (gero.schumacher@gmail.com) (up to version 0.16)
 *         Frederik Holst (bsb@code-it.de) (from version 0.17 onwards)
 *         (based on the code and work from many other developers. Many thanks!)
 *         Special thanks to Sergey Dukachev for lots of helpful code optimizations and restructurings as well as providing a profound Russian localization since version 0.43
 *         Manual by Ulf Dieckmann (adapter@quantentunnel.de):
 *         German: https://1coderookie.github.io/BSB-LPB-LAN/
 *         English: https://1coderookie.github.io/BSB-LPB-LAN_EN/
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
 *       0.25  - 21.02.2017
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
 *       0.43  - 20.02.2020
 *       0.44  - 11.05.2020
 *       1.0   - 03.08.2020
 *       1.1   - 10.11.2020
 *       2.0   -
 *
 * Changelog:
 *       version 2.0
 *        - ATTENTION: LOTS of new functionalities, some of which break compatibility with previous versions, so be careful and read all the docs if you make the upgrade!
 *        - ATTENTION: Added and reorganized PPS parameters, almost all parameter numbers have changed!
 *        - ATTENTION: Change of EEPROM layout will lead to loading of default values from BSB_LAN_config.h! You need to write settings to EEPROM in configuration menu again!
 *        - ATTENTION: Folder locations and filenames have been adjusted for easier installation! If you update your installation, please take note that the configuration is now in BSB_LAN_config.h (LAN in caps), and no longer in BSB_lan_config.h (lower-caps "lan")
 *        - Webinterface allows for configuration of most settings without the need to re-flash
 *        - Added better WiFi option through Jiri Bilek's WiFiSpi library, using an ESP8266-based microcontroller like Wemos D1 mini or LoLin NodeMCU. Older WiFi-via-Serial approach no longer supported.
 *        - Added MDNS_HOSTNAME definement in config so that BSB-LAN can be discovered through mDNS
 *        - Setting a temporary destination address for querying parameters by adding !x (where x is the destination id), e.g. /6224!10 to query the identification of the display unit
 *        - URL commands /A, /B, /T and /JA have been removed as all sensors can now be accessed via parameter numbers 20000 and above as well as (currently) under new category K49.
 *        - New categories added, subsequent categories have been shifted up
 *        - Lots of new parameters added
 *        - URL command /JR allows for querying the standard (reset) value of a parameter in JSON format
 *        - Thanks to GitHub user do13, this code now also compiles on a ESP32, tested on an Olimex ESP32-POE board. Not all features are/will be working, so try it at your own risk!
 *       version 1.1
 *        - ATTENTION: DHW Push ("Trinkwasser Push") parameter had to be moved from 1601 to 1603 because 1601 has a different "official" meaning on some heaters. Please check and change your configuration if necessary
 *        - ATTENTION: New categories added, most category numbers (using /K) will be shifted up by a few numbers.
 *        - /JA URL command outputs average values
 *        - Many new parameters decoded
 *        - New parameters for device families 25, 44, 51, 59, 68, 85, 88, 90, 96, 97, 108, 134, 162, 163, 170, 195, 209, 211
 *        - Improved mobile display of webinterface
 *        - Added definement "BtSerial" for diverting serial output to Serial2 where a Bluetooth adapter can be connected (5V->5V, GND->GND, RX->TX2, TX->RX2). Adapter has to be in slave mode and configured to 115200 bps, 8N1.
 *        - Lots of added Polish translations
 *        - New data types VT_BYTE10, VT_SPF
 *        - Bugfix for PPS bus regarding display of heating time programs
 *        - Bugfix for MQTT
 *       version 1.0
 *        - /JI URL command outputs configuration in JSON structure
 *        - /JC URL command gets list of possible values from user-defined list of functions. Example: /JC=505,700,701,702,711,1600,1602
 *        - Logging telegrams (log parameter 30000) now writes to separate file (journal.txt). It can be reset with /D0 (same time with datalog.txt) command and dumped with /DJ command.
 *        - removed WIFI configuration as it is no longer applicable for the Due
 *        - lots of new parameters for various device families
 *        - Code optimization and restructuring, general increase of speed
 *        - new schemativs for board layout V3
 *        - lots of bugfixes
 *       version 0.44
 *        - Added webserver functionality via SD card and various other improvements from GitHub user dukess
 *        - Added JSON output for MQTT
 *        - mobile friendlier web interface
 *        - more parameters and device families
 *        - last version completely tested on Mega 2560. Future versions may still run on the Mega, but will only be tested on the Arduino Due.
 *       version 0.43
 *        - Added support for HardwareSerial (Serial1) connection of the adapter. Use RX pin 19 in bus() definition to activate. See manual/forum for hardware details.
 *        - Added definement DebugTelnet to divert serial output to telnet client (port 23, no password) in BSB_LAN_config.h
 *        - Added possibility to control BSB-LAN (almost?) completely via USB-serial port. Most commands supported like their URL-counterparts, i.e. /<passcode>/xxx to query parameter xxx or /<passcode>/N to restart Arduino.
 *        - Changed default device ID from 6 (room controller "RGT1") to unused ID 66 ("LAN")
 *        - Many new parameters, please run /Q to see any possible changes for your device family and report back to us!
 *        - Added global variables (arrays of 20 bytes) custom_floats[] and custom_longs[] for use with BSB_LAN_custom.h, for example to read sensors etc.
 *          Output of these variables is done via new URL command /U
 *        - Added device families 23 and 29 (Grünenwald heaters)
 *        - Added device families 49, 52, 59 (Weishaupt heaters)
 *        - Added device fmilies 91, 92, 94, 118, 133, 136, 137, 165, 184, 188 (various controllers like QAA75 or AVS37)
 *        - Added device family 171 (Bösch wood pellet system)
 *        - Added device family 172 (SensoTherm BLW Split B (RVS21.826F/200))
 *        - Added device families 186 and 164 (Olymp WHS-500)
 *        - Added device family 195 variant 2 (Thision 19 Plus / LMS14.111B109)
 *        - Including DHT, 1Wire and burner status parameters (>20000) to MQTT
 *        - English is now default language
 *        - Updated various translations
 *        - Added STL files to print a case with a 3D printer (thanks to FHEM user EPo!)
 *        - Moved all sensors to /T , /H is now no longer used
 *        - New virtual parameters 702/703 for Weishaupt room controller
 *        - New virtual parameter 10003 to set outside temperature on newer systems
 *        - Added text descriptions for error phases (6706 ff.)
 *        - /Q is now more comprehensive
 *        - New data types VT_CUSTOM_ENUM and VT_CUSTOM_BYTE to extract information from non-standard telegrams (such as 702/703)
 *        - Bugfix: DHCP (ethernet) implementation
 *       version 0.42
 *        - Added localization! Now you can help translate BSB-LAN into your language! Simply copy one of the language files from the localization folder (LANG_DE.h is the most complete) and translate whatever you can. Non-translated items will be displayed in German.
 *          Attention: Language definition in BSB_LAN_config.h is now #define LANG <ISO-CODE>
 *          For example: #define LANG DE
 *        - Added export to MQTT broker, use log_parameters[] in BSB_LAN_config.h to define parameters and activate MQTTBrokerIP definement.
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
 *        - Added BSB_LAN_custom_setup.h and BSB_LAN_custom_global.h for you to add individual code (best used in conjunction with BSB_LAN_custom.h)
 *        - Marked all (known) OEM parameters with flag FL_OEM. OEM parameters are set by default as read-only. To make them writeable, change FL_OEM from 5 to 4 in BSB_LAN_defs.h
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
 *          See BSB_LAN_custom.h for an example to transmit average room temperature to heating system.
 *        - Added new category "22 - Energiezähler" - please note that all subsequent categories move one up!
 *        - New virtual parameter 1601 (manual TWW push)
 *        - Added Fujitsu Waterstage WSYP100DG6 device family (211)
 *        - Added CTC device family (103)
 *        - New definement "#define TRUSTED_IP2" to grant access to a second local IP address
 *        - Added optional definement "#define GatewayIP" in BSB_LAN_config.h to enable setting router address different from x.x.x.1
 *        - Removed parameter 10109 because it is the same as 10000
 *        - Added function to check all known CommandIDs on your own heating system. Use /Q after enabling definement "#define DEBUG" in BSB_LAN_config.h
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
 *          Use this in your configuration to include individual code from "BSB_LAN_custom.h"
 *          (needs to be created by you!) which is executed at the end of each main loop.
 *          Variables "custom_timer" and "custom_timer_compare" have been added to execute
 *          code at arbitrary intervals.
 *        - Added LogoBloc Unit L-UB 25C device family (95)
 *        - several new parameters added
 *        - Bugfix for logging Brennerlaufzeit Stufe 2
 *       version 0.38
 *        - ATTENTION: New BSB_LAN_config.h configurations! You need to adjust your configuration when upgrading to this version!
 *          Webserver port is now defined in #define Port xx
 *          IP address is now defined in #define IPAddr 88,88,88,88 form - note the commas instead of dots!
 *          Special log parameters 20002 to 20006 have changed, see BSB_LAN_config.h for their new meaning
 *        - Added new virtual parameter 701 (Präsenztaste) which enters reduced temperature mode until next timed switch
 *        - Added Brötje BOB device family (138), including many new parameters!
 *        - Added Brötje SOB26 device family (28)
 *        - Added Elco Aquatop 8es device family (85)
 *        - Added Elco Thision 13 Plus device family (203)
 *        - Added Weishaupt WTU 25-G familiy (50)
 *        - Added output for absolute humidity (g/m3) for DHT22 sensors
 *        - New schematics for Arduino/Raspberry board layout
 *        - Included support for W5500 Ethernet2 shields. Activate definement ETHERNET_W5500 in BSB_LAN_config.h
 *        - Including two-stage oil furnaces BC-counters and logging - please note that logging parameters have been adjusted, see BSB_LAN_config.h for new values!
 *        - Added new options for commands /P and /S to allow specifying a different destination device during runtime
 *        - Added new configuration definement CUSTOM_COMMANDS which includes BSB_LAN_custom.h at the end of each main loop. You may use custom_timer (set to current millis()) and custom_timer_compare to execute only every x milliseconds.
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
 *        - new URL-command /X to reset the Arduino (need to enable RESET definement in BSB_LAN_config.h)
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
 *        - adds special parameters 20000++ for SD card logging of /B, /T and /H commands (see BSB_LAN_config.h for examples)
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
 *        - added 24h average command "A", define parameters in BSB_LAN_config.h
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
 *            - merged v0.16 with FHEM user miwi's changes
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

#define LOGTELEGRAM_OFF 0
#define LOGTELEGRAM_ON 1
#define LOGTELEGRAM_UNKNOWN_ONLY 2
#define LOGTELEGRAM_BROADCAST_ONLY 4
#define LOGTELEGRAM_UNKNOWNBROADCAST_ONLY 6

#define HTTP_AUTH 1
#define HTTP_GZIP 2
#define HTTP_HEAD_REQ 4
#define HTTP_ETAG 8
#define HTTP_GET_ROOT 16
#define HTTP_FRAG 128

#define HTTP_FILE_NOT_GZIPPED false
#define HTTP_FILE_GZIPPED true

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

#define DO_NOT_PRINT_DISABLED_VALUE false
#define PRINT_DISABLED_VALUE true
#define PRINT_VALUE_FIRST false
#define PRINT_DESCRIPTION_FIRST true

#if defined(ESP32)
void loop();
#endif

#include <Arduino.h>

//#include "src/BSB/BSBSoftwareSerial.h"
#include "src/BSB/bsb.h"
#include "BSB_LAN_config.h"
#include "BSB_LAN_defs.h"

#if !defined(EEPROM_ERASING_PIN)
#if defined(ESP32)
#define EEPROM_ERASING_PIN 14
#else
#define EEPROM_ERASING_PIN 31
#endif
#endif
#if !defined(EEPROM_ERASING_GND_PIN) && !defined(ESP32)
#define EEPROM_ERASING_GND_PIN 33
#endif
#if !defined(LED_BUILTIN)
#define LED_BUILTIN 2
#endif

#if defined(__AVR__)
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include <SPI.h>
#endif

#if defined(__arm__) || defined(ESP32)
#include <SPI.h>
#include <Wire.h>
#include "src/I2C_EEPROM/I2C_EEPROM.h"
template<uint8_t I2CADDRESS=0x50> class UserDefinedEEP : public  eephandler<I2CADDRESS, 4096U,2,32>{};
// EEPROM 24LC32: Size 4096 Byte, 2-Byte address mode, 32 byte page size
// EEPROM 24LC16: Size 2048 Byte, 1-Byte address mode, 16 byte page size
UserDefinedEEP<> EEPROM; // default Adresse 0x50 (80)
#endif

#if defined(ESP32)
// #include <EEPROM.h>
#include <ESPmDNS.h>
#if defined(ENABLE_ESP32_OTA)
#include <WebServer.h>
#include <Update.h>
WebServer update_server(8080);
#endif
#define strcpy_PF strcpy
#define strcat_PF strcat
#define strchr_P strchr
#endif

//#include <CRC32.h>
#include "src/CRC32/CRC32.h"
//#include <util/crc16.h>
#include "src/Time/TimeLib.h"

#ifdef MQTT
#include "src/PubSubClient/src/PubSubClient.h"
#endif
#include "html_strings.h"

#ifdef BME280
//BME280 library was modified. Definitions for SDA1/SCL1 on Due added:
//#if defined(__SAM3X8E__)
//#define Wire Wire1
//#endif

#include <Wire.h>
#include "src/BlueDot_BME280/BlueDot_BME280.h"
BlueDot_BME280 bme[BME280];  //Set 2 if you need two sensors.
#endif

#ifdef WIFI
#ifdef ESP32
#include <WiFi.h>
#else
#include "src/WiFiSpi/src/WiFiSpi.h"
using ComServer = WiFiSpiServer;
using ComClient = WiFiSpiClient;
#define WiFi WiFiSpi
#endif
#else

#ifdef ESP32
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER 12
#include <ETH.h>

class Eth : public ETHClass {
public:
    int maintain(void) const { return 0;} ; // handled internally
    void begin(uint8_t *mac, IPAddress ip, IPAddress dnsserver, IPAddress gateway, IPAddress subnet) {
      ETHClass::begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLK_MODE);
      config(ip, dnsserver, gateway, subnet); //Static

    }
    void begin(uint8_t *mac) {
      ETHClass::begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLK_MODE);
    }
};

Eth Ethernet;
#else
#include <Ethernet.h>
using ComServer = EthernetServer;
using ComClient = EthernetClient;
#endif
#endif

#ifdef ESP32
using ComServer = WiFiServer;
using ComClient = WiFiClient;
#endif

#if defined(MDNS_HOSTNAME) && !defined(ESP32)
#ifdef WIFI
#include "src/WiFiSpi/src/WiFiSpiUdp.h"
WiFiSpiUdp udp;
#else
#include <EthernetUdp.h>
EthernetUDP udp;
#endif
#include "src/ArduinoMDNS/ArduinoMDNS.h"
MDNS mdns(udp);
#endif

bool EEPROM_ready = true;
byte programWriteMode = 0; //0 - read only, 1 - write ordinary programs, 2 - write ordinary + OEM programs

ComServer *server;
ComServer *telnetServer;
Stream* SerialOutput;

//BSB bus definitions
BSB *bus;
//end BSB bus definitions

/* buffer to print output lines and to load PROGMEM values in RAM*/
#define OUTBUF_LEN  450
char outBuf[OUTBUF_LEN] = { 0 };

// big output buffer with automatic flushing. Do not do direct access
#if defined(__AVR__)
#undef OUTBUF_USEFUL_LEN
#define OUTBUF_USEFUL_LEN (OUTBUF_LEN)
#else
#undef OUTBUF_USEFUL_LEN
#define OUTBUF_USEFUL_LEN (OUTBUF_LEN * 2)
#endif
char bigBuff[OUTBUF_USEFUL_LEN + OUTBUF_LEN] = { 0 };
int bigBuffPos=0;

// buffer for debug output
char DebugBuff[OUTBUF_LEN] = { 0 };

const char averagesFileName[] PROGMEM = "averages.txt";
const char datalogFileName[] PROGMEM = "datalog.txt";
const char journalFileName[] PROGMEM = "journal.txt";

ComClient client;
ComClient *mqtt_client;   //Luposoft: own instance
#ifdef VERSION_CHECK
ComClient httpclient;
#endif
ComClient telnetClient;

#ifdef MAX_CUL
ComClient *max_cul;
#endif

#ifdef MQTT
PubSubClient *MQTTPubSubClient;
#endif
bool haveTelnetClient = false;

#define MAX_CUL_DEVICES (sizeof(max_device_list)/sizeof(max_device_list[0]))
#ifdef MAX_CUL
uint16_t max_cur_temp[MAX_CUL_DEVICES] = { 0 };
uint8_t max_dst_temp[MAX_CUL_DEVICES] = { 0 };
int8_t max_valve[MAX_CUL_DEVICES] = { -1 };
int32_t max_devices[MAX_CUL_DEVICES] = { 0 };
#endif

// char _ipstr[INET6_ADDRSTRLEN];    // addr in format xxx.yyy.zzz.aaa
// char _ipstr[20];    // addr in format xxx.yyy.zzz.aaa
// byte __remoteIP[4] = {0,0,0,0};   // IP address in bin format

#if defined LOGGER || defined WEBSERVER
//leave at least MINIMUM_FREE_SPACE_ON_SD free blocks on SD
#define MINIMUM_FREE_SPACE_ON_SD 100
// set MAINTAIN_FREE_CLUSTER_COUNT to 1 in SdFatConfig.h if you want increase speed of free space calculation
// do not forget set it up after SdFat upgrading
  #include "src/SdFat/SdFat.h"
  SdFat SD;
#endif

#ifdef ONE_WIRE_BUS
  #include "src/OneWire/OneWire.h"
  #include "src/DallasTemperature/DallasTemperature.h"
  #define TEMPERATURE_PRECISION 9 //9 bit. Time to calculation: 94 ms
//  #define TEMPERATURE_PRECISION 10 //10 bit. Time to calculation: 188 ms
  OneWire *oneWire;
  DallasTemperature *sensors;
  uint8_t numSensors;
  unsigned long lastOneWireRequestTime = 0;
  #define ONE_WIRE_REQUESTS_PERIOD 25000 //sensors->requestTemperatures() calling period
#endif

#ifdef DHT_BUS
  #include "src/DHT/dht.h"
  dht DHT;
//Save state between queries
  unsigned long DHT_Timer = 0;
  int last_DHT_State = 0;
  uint8_t last_DHT_pin = 0;
#endif

unsigned long lastAvgTime = 0;
unsigned long lastLogTime = millis();
#ifdef MQTT
unsigned long lastMQTTTime = millis();
#endif
unsigned long custom_timer = millis();
unsigned long custom_timer_compare = 0;
float custom_floats[20] = { 0 };
long custom_longs[20] = { 0 };

#ifdef RGT_EMULATOR
byte newMinuteValue = 99;
#endif

#ifdef BUTTONS
volatile byte PressedButtons = 0;
#define TWW_PUSH_BUTTON_PRESSED 1
#define ROOM1_PRESENCE_BUTTON_PRESSED 2
#define ROOM2_PRESENCE_BUTTON_PRESSED 4
#define ROOM3_PRESENCE_BUTTON_PRESSED 8
#endif

static const int anz_ex_gpio = sizeof(protected_GPIO) / sizeof(byte) * 8;
static const int numLogValues = sizeof(log_parameters) / sizeof(log_parameters[0]);
static const int numCustomFloats = sizeof(custom_floats) / sizeof(custom_floats[0]);
static const int numCustomLongs = sizeof(custom_longs) / sizeof(custom_longs[0]);

#ifdef AVERAGES
static const int numAverages = sizeof(avg_parameters) / sizeof(avg_parameters[0]);
float *avgValues_Old = new float[numAverages];
float *avgValues = new float[numAverages];
float *avgValues_Current = new float[numAverages];
int avgCounter = 1;
#endif
int loopCount = 0;

struct decodedTelegram_t {
//Commented fields for future use
int cat; //category number
int32_t prognr; //program number
uint_farptr_t catdescaddr; //category description string address
uint_farptr_t prognrdescaddr; //prognr description string address
uint_farptr_t enumdescaddr; //enum description string address
uint_farptr_t enumstr; //address of first element of enum
uint_farptr_t progtypedescaddr; //program type description string address
uint_farptr_t data_type_descaddr; //data type description DT_*, dt_types_text[?].type_text
uint16_t enumstr_len;  //enum length
uint16_t error; //0 - ok, 7 - parameter not supported, 1-255 - LPB/BSB bus errors, 256 - decoding error, 257 - unknown command, 258 - not found, 259 - no enum str, 260 - unknown type, 261 - query failed
uint8_t msg_type; //telegram type
uint8_t tlg_addr; //telegram address
uint8_t readonly; // 0 - read/write, 1 - read only
uint8_t isswitch; // 0 - Any type, 1 - ONOFF or YESNO type
uint8_t type; //prog type (get_cmdtbl_type()). VT_*
uint8_t data_type; //data type DT_*, optbl[?].data_type
uint8_t precision;//optbl[?].precision
uint8_t enable_byte;//optbl[?].enable_byte
uint8_t payload_length;//optbl[?].payload_length
uint8_t sensorid; //id of external (OneWire, DHT, MAX!) sensor for virtual programs. Must be zero for real program numbers.
// uint8_t unit_len;//optbl[?].unit_len. internal variable
float operand; //optbl[?].operand
char value[64]; //decoded value from telegram to string
char unit[32]; //unit of measurement. former char div_unit[32];
char *telegramDump; //Telegram dump for debugging in case of error. Dynamic allocation is big evil for MCU but allow to save RAM
} decodedTelegram;

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
int16_t pps_values[PPS_ANZ] = { 0 };
bool time_set = false;
uint8_t current_switchday = 0;

#include "BSB_LAN_EEPROMconfig.h"

static uint16_t baseConfigAddrInEEPROM = 0; //offset from start address
void mqtt_callback(char* topic, byte* payload, unsigned int length);  //Luposoft: predefintion

#ifdef BUTTONS
void interruptHandlerTWWPush(){
  PressedButtons |= TWW_PUSH_BUTTON_PRESSED;
}
void interruptHandlerPresenceROOM1(){
  PressedButtons |= ROOM1_PRESENCE_BUTTON_PRESSED;
}
void interruptHandlerPresenceROOM2(){
  PressedButtons |= ROOM2_PRESENCE_BUTTON_PRESSED;
}
void interruptHandlerPresenceROOM3(){
  PressedButtons |= ROOM3_PRESENCE_BUTTON_PRESSED;
}
#endif

/** *****************************************************************
 *  Function: initConfigTable(uint8_t)
 *  Does: creating config parameters address table.
 *  result table is sorted by parameters versions
 *  Pass parameters:
 *
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 * *************************************************************** */


uint32_t initConfigTable(uint8_t version) {
  CRC32 crc;
  if(version == 0xFF) version--; //protection fromm infinite loop
  // look for parameters vith selected version
  for (uint8_t v = 0; v <= version; v++){
    //select config parameter
    for(uint8_t i = 0; i < CF_LAST_OPTION; i++){
      bool allowedversion = false;
      uint16_t addr = baseConfigAddrInEEPROM;
      //look for config parameter in parameters table
      for(uint8_t j = 0; j < sizeof(config)/sizeof(config[0]); j++){
  #if defined(__AVR__)
        uint8_t temp_id = pgm_read_byte_far(pgm_get_far_address(config[0].id) + j * sizeof(config[0]));
        uint8_t temp_version = pgm_read_byte_far(pgm_get_far_address(config[0].version) + j * sizeof(config[0]));
        if (i == temp_id) {
          if(temp_version <= v) allowedversion = true;
        } else
          if(temp_version <= v && i > temp_id) {addr += (uint16_t)pgm_read_word_far(pgm_get_far_address(config[0].size) + j * sizeof(config[0]));}
  #else
        if (i == config[j].id) {
          if(config[j].version <= v) allowedversion = true;
        } else
          if(config[j].version <= v && i > config[j].id) {addr += config[j].size;}
  #endif
      }
      if(allowedversion) {
        options[i].eeprom_address = addr;
        for(uint8_t k = 0; k < sizeof(addr); k++){
          crc.update(((byte *)&addr)[k]);
        }
      }
    }
  }
  return crc.finalize();
}

//register pointer to variable of selected config option in config parameters address table
void registerConfigVariable(uint8_t id, byte *ptr){
  options[id].option_address = ptr;
}

//remove variable address of selected config option from config parameters address table
void unregisterConfigVariable(uint8_t id){
  options[id].option_address = NULL;
}

byte *getConfigVariableAddress(uint8_t id){
  return options[id].option_address;
}
//return EEPROM address for selected config option
uint16_t getEEPROMaddress(uint8_t id){
  return options[id].eeprom_address;
}

uint16_t getVariableSize(uint8_t id){
  uint16_t len = 0;
  for(uint8_t j = 0; j < sizeof(config)/sizeof(config[0]); j++){
#if defined(__AVR__)
    if (id == pgm_read_byte_far(pgm_get_far_address(config[0].id) + j * sizeof(config[0]))) {
      len = pgm_read_word_far(pgm_get_far_address(config[0].size) + j * sizeof(config[0]));
      break;
    }
#else
    if (id == config[j].id) {
      len = config[j].size;
      break;
    }
#endif
  }
return len;
}

//copy config option data from EEPROM to variable
bool readFromEEPROM(uint8_t id){
  return readFromEEPROM(id, options[id].option_address);
}

//copy config option data from EEPROM to variable
bool readFromEEPROM(uint8_t id, byte *ptr){
  if (!EEPROM_ready) return false;
  if(!ptr) return false;
  uint16_t len = getVariableSize(id);
  if(!len) return false;
  for(uint16_t i = 0; i < len; i++)
    ptr[i] = EEPROM.read(i + options[id].eeprom_address);
  return true;
}

//copy config option data from variable to EEPROM
//return true if EEPROM was updated with new value
bool writeToEEPROM(uint8_t id){
  if (!EEPROM_ready) return false;
  bool EEPROMwasChanged = false;
  if(!options[id].option_address) return false;
//  printFmtToDebug(PSTR("Option %d, EEPROM Address %04X, set value: "), id, options[id].eeprom_address);
  for(uint16_t i = 0; i < getVariableSize(id); i++){
    if (options[id].option_address[i] != EEPROM.read(i + options[id].eeprom_address)) {
      EEPROM.write(i + options[id].eeprom_address, options[id].option_address[i]);
//      printFmtToDebug(PSTR("%02X "), options[id].option_address[i]);
      EEPROMwasChanged = true;
    }
  }

//  printToDebug(PSTR("\r\n"));
  return EEPROMwasChanged;
}

bool writeToConfigVariable(uint8_t id, byte *ptr){
  if(!options[id].option_address) return false;
  memcpy(options[id].option_address, ptr, getVariableSize(id));
  return true;
}

bool readFromConfigVariable(uint8_t id, byte *ptr){
  if(!options[id].option_address) return false;
  memcpy(ptr, options[id].option_address, getVariableSize(id));
  return true;
}

#include "json-api-version.h"
#include "bsb-version.h"
const char BSB_VERSION[] PROGMEM = MAJOR "." MINOR "." PATCH "-" COMPILETIME;

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
    printFmtToDebug(PSTR("Socket#%d"), i);
    SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
    uint8_t s = W5100.readSnSR(i);
    SPI.endTransaction();
    socketStat[i] = s;
    printFmtToDebug(PSTR(":0x%02X %d D:"), s, W5100.readSnPORT(i));
    uint8_t dip[4];
    SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
    W5100.readSnDIPR(i, dip);
    SPI.endTransaction();
    SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
    printFmtToDebug(PSTR("%d.%d.%d.%d(%d)\r\n"), dip[0], dip[1], dip[2], dip[3], W5100.readSnDPORT(i));
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

    if((s == 0x14) || (s == 0x1C)) {
        if(thisTime - connectTime[i] > 30000UL) {
          printFmtToDebug(PSTR("\r\nSocket frozen: %d\r\n"), i);
          SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
          W5100.execCmdSn(s, Sock_DISCON);
          SPI.endTransaction();

          printlnToDebug(PSTR("Socket freed."));
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

/* Functions for management "Ring" debug buffer */
/** *****************************************************************
 *  Function: printToDebug(char *), printToDebug(const char *), printToDebug(uint_farptr_t), printFmtToDebug()
 *  Does: do buffered print to network client. Increasing net perfomance 2~50 times
 *
 *  Pass parameters:
 *  WiFiSpiClient/EthernetClient telnetClient
 *  Serial
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   DebugBuff variable
 * *************************************************************** */
 int printFmtToDebug(const char *format, ...){
  va_list args;
  va_start(args, format);
#if defined(__AVR__)
  int len = vsnprintf_P(DebugBuff, sizeof(DebugBuff), format, args);
#else
  int len = vsnprintf(DebugBuff, sizeof(DebugBuff), format, args);
#endif
  va_end(args);
  switch(debug_mode){
    case 1: SerialOutput->print(DebugBuff); break;
    case 2: if(haveTelnetClient)telnetClient.print(DebugBuff); break;
  }
  return len;
}

void writelnToDebug(){
#if defined(__AVR__)
  strcpy_P(DebugBuff, PSTR("\r\n"));
#else
  strcpy(DebugBuff, PSTR("\r\n"));
#endif
  switch(debug_mode){
    case 1: SerialOutput->print(DebugBuff); break;
    case 2: if(haveTelnetClient)telnetClient.print(DebugBuff); break;
  }
}

void printToDebug(char *format){
  switch(debug_mode){
    case 1: SerialOutput->print(format); break;
    case 2: if(haveTelnetClient)telnetClient.print(format); break;
  }
  return;
}

void printToDebug(const char *format){
  #if defined(__AVR__)
  strcpy_P(DebugBuff, format);
  switch(debug_mode){
    case 1: SerialOutput->print(DebugBuff); break;
    case 2: if(haveTelnetClient)telnetClient.print(DebugBuff); break;
  }
  #else
  switch(debug_mode){
    case 1: SerialOutput->print(format); break;
    case 2: if(haveTelnetClient)telnetClient.print(format); break;
  }
  #endif
  return;
}

#if defined(__AVR__)
void printToDebug(uint_farptr_t src){
  strcpy_PF(DebugBuff, src);
  switch(debug_mode){
    case 1: SerialOutput->print(DebugBuff); break;
    case 2: if(haveTelnetClient)telnetClient.print(DebugBuff); break;
  }
  return;
}
#endif

#define printlnToDebug(format) {printToDebug(format); writelnToDebug();}


/* Functions for management "Ring" output buffer */
/** *****************************************************************
 *  Function: printToWebClient(char *), printToWebClient(const char *), printToWebClient(uint_farptr_t), printFmtToWebClient()
 *  Does: do buffered print to network client. Increasing net perfomance 2~50 times
 *         flushToWebClient() can be called when you want.
 *         forcedflushToWebClient() must be called before end of connection
 *  Pass parameters:
 *  WiFiSpiClient/EthernetClient &cl
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   bigBuffPos and bigBuff variable
 * *************************************************************** */

void flushToWebClient(){
  if (bigBuffPos > 0) {
    // for debug purposes
    //if(bigBuffPos > sizeof(bigBuff)) printlnToDebug(PSTR("bigBuffPos > bigBuff size"));
    client.write(bigBuff, bigBuffPos);
    bigBuffPos = 0;
    return;
  }
// for debug purposes
//  if(bigBuffPos < 0)  printlnToDebug(PSTR("bigBuffPos is negative"));
}

void forcedflushToWebClient(){
  if (bigBuffPos > 0) {
    client.write(bigBuff, bigBuffPos);
    bigBuffPos = 0;
  }
  client.flush();
}

int writelnToWebClient(){
#if defined(__AVR__)
  int len = strlen(strcpy_P(bigBuff + bigBuffPos, PSTR("\r\n")));
#else
  int len = strlen(strcpy(bigBuff + bigBuffPos, PSTR("\r\n")));
#endif
  bigBuffPos += len;
  return len;
}

int printToWebClient(char *format){
  int len = strlen(strcpy(bigBuff + bigBuffPos, format));
  bigBuffPos += len;
  if (bigBuffPos > OUTBUF_USEFUL_LEN) {
    flushToWebClient();
  }
  return len;
}

int printToWebClient(const char *format){
  #if defined(__AVR__)
  int len = strlen(strcpy_P(bigBuff + bigBuffPos, format));
  #else
  int len = strlen(strcpy(bigBuff + bigBuffPos, format));
  #endif
  bigBuffPos += len;
  if (bigBuffPos > OUTBUF_USEFUL_LEN) {
    flushToWebClient();
  }
  return len;
}

#if defined(__AVR__)
int printToWebClient(uint_farptr_t src){
  int len = strlen(strcpy_PF(bigBuff + bigBuffPos, src));
  bigBuffPos += len;
  if (bigBuffPos > OUTBUF_USEFUL_LEN) {
    flushToWebClient();
  }
  return len;
}
#endif

#define printlnToWebClient(format) (printToWebClient(format) + writelnToWebClient())

int printFmtToWebClient(const char *format, ...){
  va_list args;
  va_start(args, format);
#if defined(__AVR__)
  int len = vsprintf_P(bigBuff + bigBuffPos, format, args);
#else
  int len = vsprintf(bigBuff + bigBuffPos, format, args);
#endif
  bigBuffPos += len;
  va_end(args);
  if (bigBuffPos > OUTBUF_USEFUL_LEN) {
    flushToWebClient();
  }
  return len;
}

void printHTTPheader(uint16_t code, int mimetype, bool addcharset, bool isGzip, long cachingTime){
  const char *getfarstrings;
  long autoDetectCachingTime = 590800; // 590800 = 7 days. If -1 then no-cache, no-store etc.
  printFmtToWebClient(PSTR("HTTP/1.1 %d "), code);
  switch(code){
    case HTTP_OK: printToWebClient(PSTR("OK")); break;
    case HTTP_NOT_MODIFIED: printToWebClient(PSTR("Not Modified")); break;
    case HTTP_AUTH_REQUIRED: printToWebClient(PSTR("Authorization Required")); break;
    case HTTP_NOT_FOUND: printToWebClient(PSTR("Not Found")); break;
    default: break;
  }
  printToWebClient(PSTR("\r\nContent-Type: ")); // 17 bytes with zero
  switch(mimetype){
    case MIME_TYPE_TEXT_HTML: getfarstrings = PSTR("text/html"); break;
    case MIME_TYPE_TEXT_CSS: getfarstrings = PSTR("text/css"); break;
    case MIME_TYPE_APP_JS: getfarstrings = PSTR("application/x-javascript"); break;
    case MIME_TYPE_APP_XML: getfarstrings = PSTR("application/xml"); autoDetectCachingTime = HTTP_DO_NOT_CACHE; break;
    // case 5 below
    case MIME_TYPE_APP_JSON: getfarstrings = PSTR("application/json"); autoDetectCachingTime = HTTP_DO_NOT_CACHE; break;
    case MIME_TYPE_TEXT_PLAIN: getfarstrings = PSTR("text/plain"); autoDetectCachingTime = 60; break;
    case MIME_TYPE_IMAGE_JPEG: getfarstrings = PSTR("image/jpeg"); break;
    case MIME_TYPE_IMAGE_GIF: getfarstrings = PSTR("image/gif"); break;
    case MIME_TYPE_IMAGE_SVG: getfarstrings = PSTR("image/svg"); break;
    case MIME_TYPE_IMAGE_PNG: getfarstrings = PSTR("image/png"); break;
    case MIME_TYPE_IMAGE_ICON: getfarstrings = PSTR("image/x-icon"); autoDetectCachingTime = 2592000; break; // 30 days
    case MIME_TYPE_APP_GZ: getfarstrings = PSTR("application/x-gzip"); break;
    case MIME_TYPE_TEXT_TEXT:
    default: getfarstrings = PSTR("text"); autoDetectCachingTime = 60; break;
  }
  printToWebClient(getfarstrings);
  if(cachingTime == HTTP_AUTO_CACHE_AGE)cachingTime = autoDetectCachingTime;
  if(addcharset)printToWebClient(PSTR("; charset=utf-8"));
  printToWebClient(PSTR("\r\n"));
if(isGzip) printToWebClient(PSTR("Content-Encoding: gzip\r\n"));
printToWebClient(PSTR("Cache-Control: "));
if (cachingTime > 0) {
  //max-age=84400 = one day, max-age=590800 = 7 days, max-age=2592000 = 30 days.
  printFmtToWebClient(PSTR("max-age=%ld, public"), cachingTime);
} else {
  printToWebClient(PSTR("no-cache, no-store, must-revalidate\r\nPragma: no-cache\r\nExpires: 0"));
}
printToWebClient(PSTR("\r\n"));
}

int recognize_mime(char *str) {
//        if(strlen(dot)) {
  char mimebuf[32];
  int i = 0;
  int mimetype = 0;
  if(!str) return mimetype;

  strncpy(mimebuf, str, sizeof(mimebuf));

  while(mimebuf[i]){
    mimebuf[i] |= 0x20; //to lower case
    i++;
  }

  if (!strcmp_P(mimebuf, PSTR("html")) || !strcmp_P(mimebuf, PSTR("htm"))) mimetype = MIME_TYPE_TEXT_HTML;
  else if(!strcmp_P(mimebuf, PSTR("css"))) mimetype = MIME_TYPE_TEXT_CSS;
  else if(!strcmp_P(mimebuf, PSTR("js"))) mimetype = MIME_TYPE_APP_JS;
  else if(!strcmp_P(mimebuf, PSTR("xml"))) mimetype = MIME_TYPE_APP_XML;
  else if(!strcmp_P(mimebuf, PSTR("txt"))) mimetype = MIME_TYPE_TEXT_TEXT;
  else if(!strcmp_P(mimebuf, PSTR("jpg"))) mimetype = MIME_TYPE_IMAGE_JPEG;
  else if(!strcmp_P(mimebuf, PSTR("gif"))) mimetype = MIME_TYPE_IMAGE_GIF;
  else if(!strcmp_P(mimebuf, PSTR("svg"))) mimetype = MIME_TYPE_IMAGE_SVG;
  else if(!strcmp_P(mimebuf, PSTR("png"))) mimetype = MIME_TYPE_IMAGE_PNG;
  else if(!strcmp_P(mimebuf, PSTR("ico"))) mimetype = MIME_TYPE_IMAGE_ICON;
  else if(!strcmp_P(mimebuf, PSTR("gz"))) mimetype = MIME_TYPE_APP_GZ;
//          else mimetype = 0;
  // You can add more MIME types here
  return mimetype;
  }

/** *****************************************************************
 *  Function: calc_enum_offset()
 *  Does:     Takes the 16-Bit char pointer and calculate (or rather estimate) the address in PROGMEM beyond 64kB
 * Pass parameters:
 *  enum_addr
 *  enumstr_len
 *  shift . 0 for normal operation, 1 for VT_CUSTOM_BIT
 * Parameters passed back:
 *  enum_addr
 * Function value returned:
 *  24 bit char pointer address
 * Global resources used:
 *  enumstr_offset
 * *************************************************************** */

uint_farptr_t calc_enum_offset(uint_farptr_t enum_addr, uint16_t enumstr_len, int shift) {
#if defined(__AVR__)
  uint_farptr_t page = 0x10000;
  while (page < 0x40000) {
    uint8_t second_char = pgm_read_byte_far(enum_addr + page + 1 + shift);
    uint8_t third_char = pgm_read_byte_far(enum_addr + page + 2 + shift);
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
#else
  return enum_addr;
#endif
}

inline uint_farptr_t calc_enum_offset(uint_farptr_t enum_addr, uint16_t enumstr_len) {
  return calc_enum_offset(enum_addr, enumstr_len, 0);
}

void setBusType(){
  switch(bus_type){
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
 bool desc_first - if true, then description will be print first; if false, then value print first
 bool canBeDisabled - if true, then "---" value will be print

 * Parameters passed back:
 *  none
 * Function value returned:
 *  none
 * Global resources used:
 *  none
 * *************************************************************** */
void listEnumValues(uint_farptr_t enumstr, uint16_t enumstr_len, const char *prefix, const char *delimiter, const char *alt_delimiter, const char *suffix, const char *string_delimiter, uint16_t value, bool desc_first, bool canBeDisabled){
  uint16_t val = 0;
  uint16_t c=0;
  bool isFirst = true;
  if(decodedTelegram.type == VT_CUSTOM_BIT) c++;

  while(c<enumstr_len){
    if ((byte)(pgm_read_byte_far(enumstr+c+2))==' ') {
      val = uint16_t(pgm_read_byte_far(enumstr+c+1));
      if(decodedTelegram.type != VT_CUSTOM_ENUM) val |= uint16_t((pgm_read_byte_far(enumstr+c) << 8));
      c++;
    }else if ((byte)(pgm_read_byte_far(enumstr+c+1))==' ') {
      val=uint16_t(pgm_read_byte_far(enumstr+c));
    }
    //skip leading space
    c+=2;

    if (isFirst) {isFirst = false;} else{if(string_delimiter) printToWebClient(string_delimiter);}
    if(prefix) printToWebClient(prefix);
    uint_farptr_t descAddr;
    if (canBeDisabled) {
      val = 65535;
#if defined(__AVR__)
      descAddr = pgm_get_far_address(STR_DISABLED);
#else
      descAddr = STR_DISABLED;
#endif
    } else{
      descAddr = enumstr + c;
    }
    if (desc_first) {
      c += printToWebClient(descAddr) + 1;
      if(alt_delimiter && value == val) {
        printToWebClient(alt_delimiter);
      }else {
        if(delimiter) printToWebClient(delimiter);
      }
    }
    printFmtToWebClient(PSTR("%u"), val);
    if (!desc_first) {
      if(alt_delimiter && value == val) {
        printToWebClient(alt_delimiter);
      } else {
        if(delimiter) printToWebClient(delimiter);
      }
      c += printToWebClient(descAddr) + 1;
    }
    if(suffix) printToWebClient(suffix);
    if(canBeDisabled) {canBeDisabled = false; c = 0;}

  }
}

uint32_t get_cmdtbl_cmd(int i) {
  uint32_t c = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
//  c=pgm_read_dword(&cmdtbl[i].cmd);  // command code
#if defined(__AVR__)
    c = pgm_read_dword_far(pgm_get_far_address(cmdtbl1[0].cmd) + i * sizeof(cmdtbl1[0]));
#else
    c = cmdtbl1[i].cmd;
#endif
} else if (i < entries2) {
#if defined(__AVR__)
    c = pgm_read_dword_far(pgm_get_far_address(cmdtbl2[0].cmd) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    c = cmdtbl2[i-entries1].cmd;
#endif
  } else {
#if defined(__AVR__)
    c = pgm_read_dword_far(pgm_get_far_address(cmdtbl3[0].cmd) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    c = cmdtbl3[i-entries2].cmd;
#endif
  }
  return c;
}

uint16_t get_cmdtbl_line(int i) {
  uint16_t l = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
//  l=pgm_read_word(&cmdtbl[i].line);  // ProgNr
#if defined(__AVR__)
    l = pgm_read_word_far(pgm_get_far_address(cmdtbl1[0].line) + i * sizeof(cmdtbl1[0]));
#else
    l = cmdtbl1[i].line;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    l = pgm_read_word_far(pgm_get_far_address(cmdtbl2[0].line) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    l = cmdtbl2[i-entries1].line;
#endif
  } else {
#if defined(__AVR__)
    l = pgm_read_word_far(pgm_get_far_address(cmdtbl3[0].line) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    l = cmdtbl3[i-entries2].line;
#endif
  }
  return l;
}

uint_farptr_t get_cmdtbl_desc(int i) {
  uint_farptr_t desc = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
#if defined(__AVR__)
    desc = pgm_read_word_far(pgm_get_far_address(cmdtbl1[0].desc) + i * sizeof(cmdtbl1[0]));
#else
    desc = cmdtbl1[i].desc;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    desc = pgm_read_word_far(pgm_get_far_address(cmdtbl2[0].desc) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    desc = cmdtbl2[i-entries1].desc;
#endif
  } else {
#if defined(__AVR__)
    desc = pgm_read_word_far(pgm_get_far_address(cmdtbl3[0].desc) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    desc = cmdtbl3[i-entries2].desc;
#endif
  }
  return desc;
}

uint_farptr_t get_cmdtbl_enumstr(int i) {
  uint_farptr_t enumstr = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
#if defined(__AVR__)
    enumstr = pgm_read_word_far(pgm_get_far_address(cmdtbl1[0].enumstr) + i * sizeof(cmdtbl1[0]));
#else
    enumstr = cmdtbl1[i].enumstr;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    enumstr = pgm_read_word_far(pgm_get_far_address(cmdtbl2[0].enumstr) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    enumstr = cmdtbl2[i-entries1].enumstr;
#endif
  } else {
#if defined(__AVR__)
    enumstr = pgm_read_word_far(pgm_get_far_address(cmdtbl3[0].enumstr) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    enumstr = cmdtbl3[i-entries2].enumstr;
#endif
  }
  return enumstr;
}

uint16_t get_cmdtbl_enumstr_len(int i) {
  uint16_t enumstr_len = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
#if defined(__AVR__)
    enumstr_len = pgm_read_word_far(pgm_get_far_address(cmdtbl1[0].enumstr_len) + i * sizeof(cmdtbl1[0]));
#else
    enumstr_len = cmdtbl1[i].enumstr_len;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    enumstr_len = pgm_read_word_far(pgm_get_far_address(cmdtbl2[0].enumstr_len) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    enumstr_len = cmdtbl2[i-entries1].enumstr_len;
#endif
  } else {
#if defined(__AVR__)
    enumstr_len = pgm_read_word_far(pgm_get_far_address(cmdtbl3[0].enumstr_len) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    enumstr_len = cmdtbl3[i-entries2].enumstr_len;
#endif
  }
  return enumstr_len;
}


uint8_t get_cmdtbl_category(int i) {
  uint8_t cat = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
//   cat=pgm_read_byte(&cmdtbl[i].category);
#if defined(__AVR__)
    cat = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].category) + i * sizeof(cmdtbl1[0]));
#else
    cat = cmdtbl1[i].category;
#endif
  } else if (i < entries2){
#if defined(__AVR__)
    cat = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].category) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    cat = cmdtbl2[i-entries1].category;
#endif
  } else {
#if defined(__AVR__)
    cat = pgm_read_byte_far(pgm_get_far_address(cmdtbl3[0].category) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    cat = cmdtbl3[i-entries2].category;
#endif
  }
  return cat;
}

uint8_t get_cmdtbl_type(int i) {
  uint8_t type = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
#if defined(__AVR__)
    type = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].type) + i * sizeof(cmdtbl1[0]));
#else
    type = cmdtbl1[i].type;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    type = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].type) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    type = cmdtbl2[i-entries1].type;
#endif
  } else {
#if defined(__AVR__)
    type = pgm_read_byte_far(pgm_get_far_address(cmdtbl3[0].type) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    type = cmdtbl3[i-entries2].type;
#endif
  }
  return type;
}

uint8_t get_cmdtbl_dev_fam(int i) {
  uint8_t dev_fam = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
#if defined(__AVR__)
    dev_fam = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].dev_fam) + i * sizeof(cmdtbl1[0]));
#else
    dev_fam = cmdtbl1[i].dev_fam;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    dev_fam = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].dev_fam) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    dev_fam = cmdtbl2[i-entries1].dev_fam;
#endif
  } else {
#if defined(__AVR__)
    dev_fam = pgm_read_byte_far(pgm_get_far_address(cmdtbl3[0].dev_fam) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    dev_fam = cmdtbl3[i-entries2].dev_fam;
#endif
  }
  return dev_fam;
}

uint8_t get_cmdtbl_dev_var(int i) {
  uint8_t dev_var = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
#if defined(__AVR__)
    dev_var = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].dev_var) + i * sizeof(cmdtbl1[0]));
#else
    dev_var = cmdtbl1[i].dev_var;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    dev_var = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].dev_var) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    dev_var = cmdtbl2[i-entries1].dev_var;
#endif
  } else {
#if defined(__AVR__)
    dev_var = pgm_read_byte_far(pgm_get_far_address(cmdtbl3[0].dev_var) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    dev_var = cmdtbl3[i-entries2].dev_var;
#endif
  }
  return dev_var;
}

uint8_t get_cmdtbl_flags(int i) {
  uint8_t flags = 0;
  int entries1 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]);
  int entries2 = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) +  sizeof(cmdtbl2)/sizeof(cmdtbl2[0]);
  if (i < entries1) {
#if defined(__AVR__)
    flags = pgm_read_byte_far(pgm_get_far_address(cmdtbl1[0].flags) + i * sizeof(cmdtbl1[0]));
#else
    flags = cmdtbl1[i].flags;
#endif
  } else if (i < entries2) {
#if defined(__AVR__)
    flags = pgm_read_byte_far(pgm_get_far_address(cmdtbl2[0].flags) + (i - entries1) * sizeof(cmdtbl2[0]));
#else
    flags = cmdtbl2[i-entries1].flags;
#endif
  } else {
#if defined(__AVR__)
    flags = pgm_read_byte_far(pgm_get_far_address(cmdtbl3[0].flags) + (i - entries2) * sizeof(cmdtbl3[0]));
#else
    flags = cmdtbl3[i-entries2].flags;
#endif
  }
  return flags;
}

void printcantalloc(void){
  printlnToDebug(PSTR("Can't alloc memory"));
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
uint8_t recognizeVirtualFunctionGroup(uint16_t nr){
  if (nr >= 20000 && nr < 20007) { return 1;}
#ifdef AVERAGES
  else if (nr >= 20050 && nr < 20050 + numAverages) {return 2;} //20050 - 20099
#endif
#ifdef DHT_BUS
  else if (nr >= 20100 && nr < 20100 + sizeof(DHT_Pins) / sizeof(DHT_Pins[0]) * 4) {return 3;} //20100 - 20199
#endif
#ifdef BME280
  else if (nr >= 20200 && nr < 20200 + sizeof(bme)/sizeof(bme[0]) * 6) {return 8;} //20100 - 20199
#endif
#ifdef ONE_WIRE_BUS
  else if (nr >= 20300 && nr < 20300 + (uint16_t)numSensors * 2) {return 4;} //20300 - 20499
#endif
  else if (nr >= 20500 && nr < 20500 + MAX_CUL_DEVICES * 4) {return 5;} //20500 - 20699
  else if (nr >= 20700 && nr < 20700 + numCustomFloats) {return 6;} //20700 - 20799
  else if (nr >= 20800 && nr < 20800 + numCustomLongs) {return 7;} //20800 - 20899
  return 0;
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
  uint8_t found = 0;
  int i = -1;
  int save_i = 0;
  uint32_t c, save_c = 0;
  uint16_t l;
//  printFmtToDebug(PSTR("line = %d\r\n"), line);

  //Virtual programs. do not forget sync changes with loadPrognrElementsFromTable()
  if (line >= 20000 && line < 20900) {
    switch(recognizeVirtualFunctionGroup(line)){
      case 1: break;
      case 2:  line = avg_parameters[line - 20050]; if(line == 0) return -1; else break;
      case 3: {
        if(DHT_Pins[(line - 20100) / 4 ] == 0) //pin not assigned to DHT sensor
          return -1;
        else
          line = 20100 + ((line - 20100) % 4);
        break;
      }
      case 4: line = 20300 + ((line - 20300) % 2); break;
      case 5:{
        if(max_device_list[(line - 20500) / 4][0] == 0) //device not set
          return -1;
        else
          line = 20500 + ((line - 20500) % 4);
        break;
      }
      case 6: line = 20700; break;
      case 7: line = 20800; break;
      case 8: {
#ifdef BME280
        if(line - 20200 < sizeof(bme)/sizeof(bme[0]) * 6) //
          line = 20200 + ((line - 20200) % 6);
        else
          return -1;
#else
        return -1;
#endif
        break;
      }
      default: return -1;
    }
  }

  // binary search for the line in cmdtbl

  int left = start_idx;
  int right = (int)(sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) + sizeof(cmdtbl2)/sizeof(cmdtbl2[0]) + sizeof(cmdtbl3)/sizeof(cmdtbl3[0]) - 1);
  int mid = 0;
  while (!(left >= right))
    {
    if (get_cmdtbl_line(left) == line){ i = left; break; }
    mid = left + (right - left) / 2;
    uint16_t temp = get_cmdtbl_line(mid);
//    printFmtToDebug(PSTR("get_cmdtbl_line: left = %d, mid = %d\r\n"), get_cmdtbl_line(left), get_cmdtbl_line(mid));
    if (temp == line)
      {
      if (mid == left + 1)
        {i = mid; break; }
      else
        right = mid + 1;
      }
    else if (temp > line)
      right = mid;
    else
      left = mid + 1;
//    printFmtToDebug(PSTR("left = %d, mid = %d, right = %d\r\n"), left, mid, right);
    }
//  printFmtToDebug(PSTR("i = %d\r\n"), i);
  if(i == -1) return i;

  l = get_cmdtbl_line(i);
  while(l == line){
    c = get_cmdtbl_cmd(i);
    uint8_t dev_fam = get_cmdtbl_dev_fam(i);
    uint8_t dev_var = get_cmdtbl_dev_var(i);
    uint8_t dev_flags = get_cmdtbl_flags(i);
//    printFmtToDebug(PSTR("l = %d, dev_fam = %d,  dev_var = %d, dev_flags = %d\r\n"), l, dev_fam, dev_var, dev_flags);

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
          save_i=i;
          save_c=c;
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
    i++;
    l = get_cmdtbl_line(i);
  }

  if (!found) {
    return -1;
  }
  if(cmd!=NULL) *cmd=save_c;
  return save_i;
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
#elif defined (__AVR__)
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
#else
  char top;
  return &top - reinterpret_cast<char*>(sbrk(0));
#endif
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
  printFmtToDebug(PSTR("%02X"), val);  // add a leading zero to single-digit values
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
  printFmtToDebug(PSTR("%08lX"), val);
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
  byte offset = 0;
  byte msg_type = msg[4+(bus->getBusType()*1)];
  if (bus_type != BUS_PPS) {
    if (msg_type >= 0x12) {
      offset = 4;
    }
  }
  switch(bus->getBusType()){
  case BUS_BSB: data_len=msg[bus->getLen_idx()]-11+offset; break;    // get packet length, then subtract
  case BUS_LPB: data_len=msg[bus->getLen_idx()]-14+offset; break;    // get packet length, then subtract
  case BUS_PPS: data_len=9; break;
  }
  // Start indexing where the payload begins
  for(int i=0;i<data_len;i++){
    SerialPrintHex(msg[bus->getPl_start()-offset+i]);
    printFmtToDebug(PSTR(" "));
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
    printFmtToDebug(PSTR(" "));
  }
}

void EEPROM_dump() {
  if ((debug_mode == 1 || haveTelnetClient) && EEPROM_ready) {
    printlnToDebug(PSTR("EEPROM dump:"));
    for (uint16_t x=0; x<EEPROM.length(); x++) {
      printFmtToDebug(PSTR("%02X "), EEPROM.read(x));
    }
  }
}

#ifdef BUTTONS
void switchPresenceState(uint16_t set_mode, uint16_t current_state){
  //RGT1 701, 10102
  //RGT2 1001, 10103
  //RGT3 1301, 10104
  int state = 0;
  char buf[9];
  unsigned int i0, i1;
  query(current_state);
  strcpy_P(buf, PSTR("%02x%02x"));
  if(2 != sscanf(decodedTelegram.value, buf, &i0, &i1)) return;
  if(i0 != 0x01) return; // 1 = Automatic
  switch(i1){
    case 0x01: state = 0x02; break; //Automatic in Reduced mode -> Automatic Reduced pushed into Comfort
    case 0x02: state = 0x01; break; //Automatic in Comfort mode -> Automatic Comfort pushed into Reduced
    case 0x03: state = 0x02; break; //Automatic Comfort mode, but pushed into Reduced -> Automatic Comfort
    case 0x04: state = 0x01; break; //Automatic Reduced mode, but pushed into Comfort -> Automatic Reduced
    default: return;
  }
  sprintf_P(buf, PSTR("%d"), state);
  set(set_mode, buf, true);
}
#endif

bool programIsreadOnly(uint8_t param_len){
  if ((DEFAULT_FLAG & FL_SW_CTL_RONLY) == FL_SW_CTL_RONLY) { //software-controlled
    switch(programWriteMode) {
      case 0: return true; //All read-only.
      case 1: if((param_len & FL_OEM) == FL_OEM || ((param_len & FL_RONLY) == FL_RONLY && (DEFAULT_FLAG & FL_RONLY) != FL_RONLY)) return true; else return false; //All writable except read-only and OEM
      case 2: if((param_len & FL_RONLY) == FL_RONLY && (param_len & FL_OEM) != FL_OEM) return true; else return false; //All writable except read-only
    }
  } else{ //defs-controlled.
    if((param_len & FL_RONLY) == FL_RONLY) return true;
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
void loadPrognrElementsFromTable(int nr, int i){
  if (i<0) i = findLine(19999,0,NULL); // Using "Unknown command" if not found
  decodedTelegram.prognrdescaddr = get_cmdtbl_desc(i);
  decodedTelegram.type = get_cmdtbl_type(i);
  decodedTelegram.cat=get_cmdtbl_category(i);
  decodedTelegram.enumstr_len=get_cmdtbl_enumstr_len(i);
  //calc_enum_offset() MUST be after decodedTelegram.type = get_cmdtbl_type() because depend from it (VT_CUSTOM_BIT)
  decodedTelegram.enumstr = calc_enum_offset(get_cmdtbl_enumstr(i), decodedTelegram.enumstr_len, decodedTelegram.type == VT_CUSTOM_BIT?1:0);
  uint8_t flags=get_cmdtbl_flags(i);
  if (programIsreadOnly(flags))
    decodedTelegram.readonly = 1;
  else
    decodedTelegram.readonly = 0;
  #if defined(__AVR__)
  decodedTelegram.data_type=pgm_read_byte_far(pgm_get_far_address(optbl[0].data_type) + decodedTelegram.type * sizeof(optbl[0]));
  decodedTelegram.operand=pgm_read_float_far(pgm_get_far_address(optbl[0].operand) + decodedTelegram.type * sizeof(optbl[0]));
  decodedTelegram.precision=pgm_read_byte_far(pgm_get_far_address(optbl[0].precision) + decodedTelegram.type * sizeof(optbl[0]));
  decodedTelegram.enable_byte=pgm_read_byte_far(pgm_get_far_address(optbl[0].enable_byte) + decodedTelegram.type * sizeof(optbl[0]));
  decodedTelegram.payload_length=pgm_read_byte_far(pgm_get_far_address(optbl[0].payload_length) + decodedTelegram.type * sizeof(optbl[0]));
  strcpy_PF(decodedTelegram.unit, pgm_read_word_far(pgm_get_far_address(optbl[0].unit) + decodedTelegram.type * sizeof(optbl[0])));
  decodedTelegram.progtypedescaddr = pgm_read_word_far(pgm_get_far_address(optbl[0].type_text) + decodedTelegram.type * sizeof(optbl[0]));
  decodedTelegram.data_type_descaddr = pgm_read_word_far(pgm_get_far_address(dt_types_text[0].type_text) + decodedTelegram.data_type * sizeof(dt_types_text[0]));
  #else
  decodedTelegram.data_type=optbl[decodedTelegram.type].data_type;
  decodedTelegram.operand=optbl[decodedTelegram.type].operand;
  decodedTelegram.precision=optbl[decodedTelegram.type].precision;
  decodedTelegram.enable_byte=optbl[decodedTelegram.type].enable_byte;
  decodedTelegram.payload_length=optbl[decodedTelegram.type].payload_length;
  memcpy(decodedTelegram.unit, optbl[decodedTelegram.type].unit, optbl[decodedTelegram.type].unit_len);
  decodedTelegram.progtypedescaddr = optbl[decodedTelegram.type].type_text;
  decodedTelegram.data_type_descaddr = dt_types_text[decodedTelegram.data_type].type_text;
  #endif

  if (decodedTelegram.type == VT_ONOFF || decodedTelegram.type == VT_YESNO|| decodedTelegram.type == VT_CLOSEDOPEN || decodedTelegram.type == VT_VOLTAGEONOFF) {
    decodedTelegram.isswitch = 1;
  } else {
    decodedTelegram.isswitch = 0;
  }

  decodedTelegram.sensorid = 0;
  if (nr >= 20000) { //Virtual programs. do not forget sync changes with findline()
    decodedTelegram.prognr = nr;
    switch(recognizeVirtualFunctionGroup(nr)){
      case 1: break;
      case 2: decodedTelegram.cat = CAT_USERSENSORS; decodedTelegram.readonly = 1; break; //overwrite native program categories with CAT_USERSENSORS
      case 3: decodedTelegram.sensorid = (nr - 20100) / 4 + 1; break;
      case 4: decodedTelegram.sensorid = (nr - 20300) / 2 + 1; break;
      case 5: decodedTelegram.sensorid = (nr - 20500) / 4 + 1; break;
      case 6: decodedTelegram.sensorid = nr - 20700; break;
      case 7: decodedTelegram.sensorid = nr - 20800; break;
      case 8: decodedTelegram.sensorid = (nr - 20200) / 6 + 1; break;
    }
  }
}

// calling in every printTelegram()
void resetDecodedTelegram(){
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
  decodedTelegram.error = 0;
  decodedTelegram.readonly = 0;
  decodedTelegram.isswitch = 0;
  decodedTelegram.value[0] = 0;
  decodedTelegram.unit[0] = 0;
  decodedTelegram.enumstr_len = 0;
  decodedTelegram.enumstr = 0;
  decodedTelegram.msg_type = 0;
  decodedTelegram.tlg_addr = 0;
  decodedTelegram.operand = 1;
  decodedTelegram.sensorid = 0;
  if(decodedTelegram.telegramDump) {free(decodedTelegram.telegramDump); decodedTelegram.telegramDump = NULL;} //free memory before new telegram
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
  const char *p = NULL;
  switch(addr & 0x7F){
    case ADDR_HEIZ: p = PSTR("HEIZ"); break;
    case ADDR_EM1: p = PSTR("EM1"); break;
    case ADDR_EM2: p = PSTR("EM2"); break;
    case ADDR_RGT1: p = PSTR("RGT1"); break;
    case ADDR_RGT2: p = PSTR("RGT2"); break;
    case ADDR_CNTR: p = PSTR("CNTR"); break;
    case ADDR_SRVC: p = PSTR("SRVC"); break;
    case ADDR_LAN: p = PSTR("LAN"); break;
    case ADDR_DISP: p = PSTR("DISP"); break;
    case ADDR_OZW: p = PSTR("OZW"); break;
    case ADDR_FE: p = PSTR("FE"); break;
    case ADDR_RC: p = PSTR("REMO"); break;
    case ADDR_ALL: p = PSTR("ALL "); break;
    default: sprintf_P(device, PSTR("%02X"), addr); break;
  }
  if(p) strcpy_P(device, p);
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
  char device[5];
  printToDebug(TranslateAddr(addr, device));
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
char *TranslateType(byte type, char *mtype){
  const char *p = NULL;
  switch(type){
    case TYPE_QINF: p = PSTR("QINF"); break;
    case TYPE_INF: p = PSTR("INF"); break;
    case TYPE_SET: p = PSTR("SET"); break;
    case TYPE_ACK: p = PSTR("ACK"); break;
    case TYPE_NACK: p = PSTR("NACK"); break;
    case TYPE_QUR: p = PSTR("QUR"); break;
    case TYPE_ANS: p = PSTR("ANS"); break;
    case TYPE_QRV: p = PSTR("QRV"); break;
    case TYPE_ARV: p = PSTR("ARV"); break;
    case TYPE_ERR: p = PSTR("ERR"); break;
    case TYPE_QRE: p = PSTR("QRE"); break;
    case TYPE_IQ1: p = PSTR("IQ1"); break;
    case TYPE_IA1: p = PSTR("IA1"); break;
    case TYPE_IQ2: p = PSTR("IQ2"); break;
    case TYPE_IA2: p = PSTR("IA2"); break;
    // If no match found: print the hex value
    default: sprintf_P(mtype, PSTR("%02X"), type); break;
  } // endswitch
  if(p) strcpy_P(mtype, p);
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
void prepareToPrintHumanReadableTelegram(byte *msg, byte data_len, int shift){
  SerialPrintData(msg);
  int len = 0;
  decodedTelegram.telegramDump = (char *) malloc(data_len * 2 + 1); //two chars per telegram byte + zero
  if (decodedTelegram.telegramDump) {
    for (int i=0; i < data_len; i++) {
      len+=sprintf_P(decodedTelegram.telegramDump + len,PSTR("%02X"),msg[shift+i]);
    }
  }
  else
  {
    printcantalloc();
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
int undefinedValueToBuffer(char *p){
  #if defined(__AVR__)
                    strcpy_PF(p, pgm_get_far_address(STR_DISABLED));
  #else
                    strcpy(p, STR_DISABLED);
  #endif
  return 3;
}

void printPassKey(void){
  if (PASSKEY[0]) {
    printToWebClient(PASSKEY);
    printToWebClient(PSTR("/"));
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
void printyesno(bool i){
  if (i) {
    printToWebClient(PSTR(MENU_TEXT_YES "<BR>"));
  } else {
    printToWebClient(PSTR(MENU_TEXT_NO "<BR>"));
  }
  printToWebClient(PSTR("\r\n"));
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
 void printDebugValueAndUnit(char *p1, char *p2){
   printToDebug(p1);
   if (p2[0] != 0) {
     printFmtToDebug(PSTR(" %s"), p2);
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
void printBIT(byte *msg,byte data_len){
  int len = 0;
  if (data_len == 2 || data_len == 3) {
    if (msg[bus->getPl_start()]==0 || data_len == 3) {
      if (bus->getBusType() == BUS_PPS) {
        data_len = 2;
      }
      for (int i=7;i>=0;i--) {
        len += sprintf_P(decodedTelegram.value+len,PSTR("%d"),msg[bus->getPl_start()+1+data_len-2] >> i & 1);
      }
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printToDebug(decodedTelegram.value);
  } else {
    printFmtToDebug(PSTR("BYTE len error len!=2: "));
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
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
void printCustomBIT(byte *msg,byte idx){
  int len = 0;
  for (int i=7;i>=0;i--) {
    len += sprintf_P(decodedTelegram.value+len,PSTR("%d"),msg[bus->getPl_start()+idx] >> i & 1);
  }
  printToDebug(decodedTelegram.value);
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
void printBYTE(byte *msg,byte data_len){
//  uint8_t pps_offset = (msg[0] == 0x17 && pps_write != 1 && bus->getBusType() == BUS_PPS);

  if (data_len == 2 || bus->getBusType() == BUS_PPS) {
    if (msg[bus->getPl_start()]==0 || bus->getBusType() == BUS_PPS) {
//      sprintf_P(decodedTelegram.value,PSTR("%d"),msg[bus->getPl_start()+1+pps_offset]);
      sprintf_P(decodedTelegram.value,PSTR("%d"),msg[bus->getPl_start()+1]);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
  } else {
    printFmtToDebug(PSTR("BYTE len error len!=2: "));
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
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
void printWORD(byte *msg,byte data_len, long divisor){
  long lval;
  if (data_len == 3) {
    if (msg[bus->getPl_start()]==0) {
      lval=((long(msg[bus->getPl_start()+1])<<8)+long(msg[bus->getPl_start()+2])) / divisor;
      sprintf_P(decodedTelegram.value,PSTR("%ld"),lval);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
  } else {
    printFmtToDebug(PSTR("WORD len error len!=3: "));
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
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
void printSINT(byte *msg,byte data_len, long multiplier){
  int16_t lval;
  if (data_len == 3) {
    if (msg[bus->getPl_start()]==0) {
      lval=(((int16_t)(msg[bus->getPl_start()+1])<<8) + (int16_t)(msg[bus->getPl_start()+2])) * multiplier;
      sprintf_P(decodedTelegram.value,PSTR("%d"),lval);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
  } else {
    printFmtToDebug(PSTR("WORD len error len!=3: "));
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
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
 void printDWORD(byte *msg, byte data_len, long divider){
   long lval;
   if (data_len == 5) {
     if (msg[bus->getPl_start()]==0) {
       lval=((long(msg[bus->getPl_start()+1])<<24)+(long(msg[bus->getPl_start()+2])<<16)+(long(msg[bus->getPl_start()+3])<<8)+long(msg[bus->getPl_start()+4]))/divider;
       sprintf_P(decodedTelegram.value,PSTR("%ld"),lval);
     } else {
       undefinedValueToBuffer(decodedTelegram.value);
     }
     printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
   } else {
     printFmtToDebug(PSTR("DWORD len error len!=5: "));
     prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
     decodedTelegram.error = 256;
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
int _printFIXPOINT(char *p, float dval, int precision){
  int a,b,i;
  int len = 0;
  if (dval<0) {
    p[len++] = '-';
    dval*=-1.0;
  }
  float rval=10.0;
  for(i=0;i<precision;i++) rval*=10.0;
  dval+=5.0/rval; //rounding
  a=(int)(dval);
  if (precision==0) {
    len+=sprintf_P(p+len,PSTR("%d"),a);
  } else {
    rval/=10.0;
    b=(int)(dval*rval - a*rval);
    char formatstr[8]="%d.%01d";
    formatstr[5]='0'+precision;
    len+=sprintf(p+len,formatstr,a,b);
  }
  return len;
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
void printFIXPOINT(byte *msg,byte data_len,float divider,int precision){
  float dval;
//  int8_t pps_offset = (((pps_write == 1 && msg[0] != 0x00) || (pps_write != 1 && msg[0] != 0x17 && msg[0] != 0x00)) && bus->getBusType() == BUS_PPS);
  int8_t pps_offset = (bus->getBusType() == BUS_PPS);

  if (data_len == 3 || data_len == 5) {
    if (msg[bus->getPl_start()]==0 || bus->getBusType() == BUS_PPS) {
      if (data_len == 3) {
        dval=float((int16_t)(msg[bus->getPl_start()+1-pps_offset] << 8) + (int16_t)msg[bus->getPl_start()+2-pps_offset]) / divider;
      } else {
        dval=float((int16_t)(msg[bus->getPl_start()+3-pps_offset] << 8) + (int16_t)msg[bus->getPl_start()+4-pps_offset]) / divider;
      }
      _printFIXPOINT(decodedTelegram.value,dval,precision);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
  } else {
    printToDebug(PSTR("FIXPOINT len !=3: "));
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
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
void printFIXPOINT_DWORD(byte *msg,byte data_len,float divider,int precision){
  float dval;

  if (data_len == 5) {
    if (msg[bus->getPl_start()]==0) {
      dval=float((long(msg[bus->getPl_start()+1])<<24)+(long(msg[bus->getPl_start()+2])<<16)+(long(msg[bus->getPl_start()+3])<<8)+long(msg[bus->getPl_start()+4])) / divider;
      _printFIXPOINT(decodedTelegram.value,dval,precision);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
  } else {
    printToDebug(PSTR("FIXPOINT_DWORD len !=5: "));
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
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
void printFIXPOINT_BYTE(byte *msg,byte data_len,float divider,int precision){
  float dval;

  if (data_len == 2 || (data_len == 3 && (my_dev_fam == 107 || my_dev_fam == 123 || my_dev_fam == 163))) {
    if (msg[bus->getPl_start()]==0) {
      dval=float((signed char)msg[bus->getPl_start()+1+(data_len==3)]) / divider;
      _printFIXPOINT(decodedTelegram.value,dval,precision);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
  } else {
    printToDebug(PSTR("FIXPOINT_BYTE len !=2: "));
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
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
void printFIXPOINT_BYTE_US(byte *msg,byte data_len,float divider,int precision){
  float dval;

  if (data_len == 2) {
    if (msg[bus->getPl_start()]==0) {
      dval=float(msg[bus->getPl_start()+1]) / divider;
      _printFIXPOINT(decodedTelegram.value,dval,precision);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printDebugValueAndUnit(decodedTelegram.value, decodedTelegram.unit);
  } else {
    printToDebug(PSTR("FIXPOINT_BYTE len !=2: "));
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
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
  uint16_t val = 0;
  decodedTelegram.enumdescaddr = 0;
  if (enumstr!=0) {
    uint16_t c=0;
    while(c<enumstr_len){
      if ((byte)(pgm_read_byte_far(enumstr+c+2))==' ') {
        val=uint16_t((pgm_read_byte_far(enumstr+c) << 8)) | uint16_t(pgm_read_byte_far(enumstr+c+1));
        c++;
      }else if ((byte)(pgm_read_byte_far(enumstr+c+1))==' ') {
        val=uint16_t(pgm_read_byte_far(enumstr+c));
      }
      //skip leading space
      c+=2;
      if (val==search_val) {
       // enum value found
       break;
      }
      while(pgm_read_byte_far(enumstr+c)!=0) c++;
      c++;
    }
    if (c<enumstr_len) {
      decodedTelegram.enumdescaddr = enumstr+c;
      sprintf_P(decodedTelegram.value, PSTR("%d"), val);
      if (print_val) {
        printFmtToDebug(PSTR("%s - "), decodedTelegram.value);
      }
      printToDebug(decodedTelegram.enumdescaddr);
    } else {
      sprintf_P(decodedTelegram.value, PSTR("%d"), search_val);
      printToDebug(decodedTelegram.value);
      decodedTelegram.error = 258;
    }
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
void printCHOICE(byte *msg, byte data_len, uint_farptr_t enumstr, uint16_t enumstr_len){
  if (data_len == 2 || bus->getBusType() == BUS_PPS) {
    if (msg[bus->getPl_start()]==0 || bus->getBusType() == BUS_PPS) {
      printENUM(enumstr,enumstr_len,msg[bus->getPl_start()+1]?1:0,1);
      sprintf_P(decodedTelegram.value,PSTR("%d"),msg[bus->getPl_start()+1]); //store real value
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
      printToDebug(decodedTelegram.value);
    }
    } else {
    printToDebug(PSTR("CHOICE len !=2: "));
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
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
  decodedTelegram.enumdescaddr = 0;
  if (enumstr!=0) {
    uint16_t c=0;
    while(c<enumstr_len){
      val=pgm_read_byte_far(enumstr+c+1);
      //skip leading space
      c+=3;
      if (val==search_val) {
       // enum value found
       break;
      }
      while(pgm_read_byte_far(enumstr+c)!=0) c++;
      c++;
    }
    if (c<enumstr_len) {
      decodedTelegram.enumdescaddr = enumstr+c;
      sprintf_P(decodedTelegram.value, PSTR("%d"), val);
      if (print_val) {
        printFmtToDebug(PSTR("%s - "), decodedTelegram.value);
      }
      printToDebug(decodedTelegram.enumdescaddr);
    } else {
      sprintf_P(decodedTelegram.value, PSTR("%d"), search_val);
      printToDebug(decodedTelegram.value);
      decodedTelegram.error = 258;
    }
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
  if (data_len == 9) {
    if (msg[bus->getPl_start()]==0) {
      sprintf_P(decodedTelegram.value,PSTR("%02d.%02d.%d %02d:%02d:%02d"),msg[bus->getPl_start()+3],msg[bus->getPl_start()+2],msg[bus->getPl_start()+1]+1900,msg[bus->getPl_start()+5],msg[bus->getPl_start()+6],msg[bus->getPl_start()+7]);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printToDebug(decodedTelegram.value);
  } else {
    printToDebug(PSTR(" VT_DATETIME len !=9: "));
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
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

  if (data_len == 9) {
    if (msg[bus->getPl_start()]==0) {
      sprintf_P(decodedTelegram.value,PSTR("%02d.%02d."),msg[bus->getPl_start()+3],msg[bus->getPl_start()+2]);
    } else {
      undefinedValueToBuffer(decodedTelegram.value);
    }
    printToDebug(decodedTelegram.value);
  } else {
    printToDebug(PSTR(" VT_DATE len !=9: "));
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
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
  int len = 0;

  if (data_len == 12) {
    for(byte i = 0; i < 3; i++){
      if (i) {
        decodedTelegram.value[len] = ' ';
        len++;
      }
      len+=sprintf_P(decodedTelegram.value+len,PSTR("%d. "), i + 1);
      byte k = bus->getPl_start() + i * 4;
      if (msg[k]<24) {
        len+=sprintf_P(decodedTelegram.value+len,PSTR("%02d:%02d - %02d:%02d"),msg[k],msg[k + 1],msg[k + 2],msg[k + 3]);
      } else {
//        len += strlen(strcpy_P(decodedTelegram.value+len,PSTR("--:-- - --:--")));
        strcpy_P(decodedTelegram.value+len,PSTR("--:-- - --:--"));
        len += 13;
      }
    }
    decodedTelegram.value[len] = 0;
    printToDebug(decodedTelegram.value);
  } else {
    printToDebug(PSTR(" VT_TIMEPROG len !=12: "));
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
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

  if (data_len == 3) {
    if (bus->getBusType() == BUS_PPS) {
      sprintf_P(decodedTelegram.value,PSTR("%02d:%02d"),msg[bus->getPl_start()+1] / 6, (msg[bus->getPl_start()+1] % 6) * 10);
      printFmtToDebug(PSTR("%02d:%02d-%02d:%02d, %02d:%02d-%02d:%02d, %02d:%02d-%02d:%02d"), msg[bus->getPl_start()+1] / 6, (msg[bus->getPl_start()+1] % 6) * 10, msg[bus->getPl_start()] / 6, (msg[bus->getPl_start()] % 6) * 10, msg[bus->getPl_start()-1] / 6, (msg[bus->getPl_start()-1] % 6) * 10, msg[bus->getPl_start()-2] / 6, (msg[bus->getPl_start()-2] % 6) * 10, msg[bus->getPl_start()-3] / 6, (msg[bus->getPl_start()-3] % 6) * 10, msg[bus->getPl_start()-4] / 6, (msg[bus->getPl_start()-4] % 6) * 10);
    } else {
      if (msg[bus->getPl_start()]==0) {
        sprintf_P(decodedTelegram.value,PSTR("%02d:%02d"),msg[bus->getPl_start()+1],msg[bus->getPl_start()+2]);
      } else {
        strcpy_P(decodedTelegram.value,PSTR("--:--"));
      }
      printToDebug(decodedTelegram.value);
    }
  } else {
    printToDebug(PSTR("VT_HOUR_MINUTES len !=3: "));
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
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
 * *************************************************************** */
void printLPBAddr(byte *msg,byte data_len){

  if (data_len == 2) {
    if (msg[bus->getPl_start()]==0) {   // payload Int8 value
    sprintf_P(decodedTelegram.value,PSTR("%02d.%02d"),msg[bus->getPl_start()+1]>>4,(msg[bus->getPl_start()+1] & 0x0f)+1);
  } else {
    undefinedValueToBuffer(decodedTelegram.value);
  }
  printToDebug(decodedTelegram.value);
  } else {
    printToDebug(PSTR(" VT_LPBADDR len !=2: "));
    prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
    decodedTelegram.error = 256;
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

void resetDurations(){
  brenner_duration=0;
  brenner_count=0;
  brenner_duration_2=0;
  brenner_count_2=0;
  TWW_duration=0;
  TWW_count=0;
}

//Get current value from decodedTelegram.cat and load description address to decodedTelegram.catdescaddr
void loadCategoryDescAddr(){
#if defined(__AVR__)
  printENUM(pgm_get_far_address(ENUM_CAT), sizeof(ENUM_CAT), decodedTelegram.cat, 0);
#else
  printENUM(ENUM_CAT, sizeof(ENUM_CAT), decodedTelegram.cat, 0);
#endif
  decodedTelegram.catdescaddr = decodedTelegram.enumdescaddr;
  decodedTelegram.enumdescaddr = 0;
  decodedTelegram.value[0] = 0; //VERY IMPORTANT: reset result before decoding, in other case in case of error value from printENUM will be showed as correct value.
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
 *   decodedTelegram   error status, r/o flag
 *
 *
 *  NOTE: If you need pvalstr, you can call printTelegram() as
 *  printTelegram(msg, query_line);
 *  build_pvalstr(0);
 *  or, if You do not want every time decode pvalstr, you can use
 *  values from decodedTelegram structure after printTelegram() calling
 * *************************************************************** */
void printTelegram(byte* msg, int query_line) {
  resetDecodedTelegram();
/*
#if !DEBUG
  // suppress DE telegrams
  if(msg[0]==0xDE) return;

  // suppress QUERY telegrams
  if(msg[4]==TYPE_QUR) return;
#endif
*/

  decodedTelegram.msg_type = msg[4+(bus->getBusType()*4)];

  if (bus->getBusType() != BUS_PPS) {
    // source
    SerialPrintAddr(msg[1+(bus->getBusType()*2)]); // source address
    printToDebug(PSTR("->"));
    SerialPrintAddr(msg[2]); // destination address
    printToDebug(PSTR(" "));
    // msg[3] contains the message length, not handled here
    SerialPrintType(decodedTelegram.msg_type); // message type, human readable
    printFmtToDebug(PSTR(" "));
  } else {
    if (!monitor) {
      switch (msg[0]) {
        case 0x1D: printToDebug(PSTR("INF HEIZ->QAA ")); break;
        case 0x1E: printToDebug(PSTR("REQ HEIZ->QAA ")); break;
        case 0x17: printToDebug(PSTR("RTS HEIZ->QAA ")); break;
        case 0xF8:
        case 0xFB:
        case 0xFD:
        case 0xFE:
          printToDebug(PSTR("ANS QAA->HEIZ ")); break;
        default: break;
      }
    }
  }

  uint32_t cmd = 0;
  //  uint8_t pps_cmd = msg[1 + (msg[0] == 0x17 && pps_write != 1)];
  uint8_t pps_cmd = msg[1];
  switch(bus->getBusType()){
    case BUS_BSB:
      if (msg[4]==TYPE_QUR || msg[4]==TYPE_SET) { //QUERY and SET: byte 5 and 6 are in reversed order
        cmd=(uint32_t)msg[6]<<24 | (uint32_t)msg[5]<<16 | (uint32_t)msg[7] << 8 | (uint32_t)msg[8];
      } else {
        cmd=(uint32_t)msg[5]<<24 | (uint32_t)msg[6]<<16 | (uint32_t)msg[7] << 8 | (uint32_t)msg[8];
      }
      break;
    case BUS_LPB:
      if (msg[8]==TYPE_QUR || msg[8]==TYPE_SET) { //QUERY and SET: byte 9 and 10 are in reversed order
        cmd=(uint32_t)msg[10]<<24 | (uint32_t)msg[9]<<16 | (uint32_t)msg[11] << 8 | (uint32_t)msg[12];
      } else {
        cmd=(uint32_t)msg[9]<<24 | (uint32_t)msg[10]<<16 | (uint32_t)msg[11] << 8 | (uint32_t)msg[12];
      }
      break;
    case BUS_PPS:
      cmd = 0x2D000000 + query_line - 15000;    // PPS commands start at parameter no. 15000
      cmd = cmd + (pps_cmd * 0x10000);
      break;
  }
  // search for the command code in cmdtbl
  int i=0;        // begin with line 0
  int save_i=0;
  bool known=0;
  uint8_t score = 0;
  uint32_t c = 0;     // command code
  if (query_line != -1) {
    while(1){
      i = findLine(query_line,i,&c);
      if (i != -1) {
        if (c == cmd) {
          save_i = i;
          known = true;
          break;
        }
        i++;
      } else {
        known = false;
        break;
      }
    }

  } else {
    int line = 0, match_line = 0;
    c=get_cmdtbl_cmd(i);
    line = get_cmdtbl_line(i);
    while(c!=CMD_END){
      if (c == cmd || (bus->getBusType() == BUS_PPS && ((c & 0x00FF0000) >> 16 == pps_cmd))) {
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

      i++;
      line = get_cmdtbl_line(i);
      c=get_cmdtbl_cmd(i);
      if (line > match_line && known == false) {
        score = 0;
      }
    }
  }
  if (!known || msg[0] == 0x17) { // no hex code match or PPS RTS telegram type
    // Entry in command table is "UNKNOWN" (0x00000000)
    if (bus->getBusType() != BUS_PPS) {
      printToDebug(PSTR("     "));
      if (decodedTelegram.msg_type < 0x12) {
        SerialPrintHex32(cmd);             // print what we have got
        printToDebug(PSTR(" "));
      }
    }
  } else {
    i = save_i;
    // Entry in command table is a documented command code
    decodedTelegram.prognr=get_cmdtbl_line(i);

    printFmtToDebug(PSTR("%4ld "),decodedTelegram.prognr);

    // print category
    loadPrognrElementsFromTable(query_line, i);
    loadCategoryDescAddr(); //Get current value from decodedTelegram.cat and load description address to decodedTelegram.catdescaddr

    printToDebug(PSTR(" - "));
    // print menue text
    printToDebug(decodedTelegram.prognrdescaddr);
    printToDebug(PSTR(": "));
  }

  // decode parameter
  int data_len=0;
  switch(bus->getBusType()){
    case BUS_BSB:
    if (decodedTelegram.msg_type < 0x12) {
      data_len=msg[bus->getLen_idx()]-11;     // get packet length, then subtract
    } else {
      data_len=msg[bus->getLen_idx()]-7;      // for yet unknow telegram types 0x12 to 0x15
    }
    break;
    case BUS_LPB:
    if (decodedTelegram.msg_type < 0x12) {
      data_len=msg[bus->getLen_idx()]-14;     // get packet length, then subtract
    } else {
      data_len=msg[bus->getLen_idx()]-7;      // for yet unknow telegram types 0x12 to 0x15
    }
    break;
    case BUS_PPS:
    if (msg[0] != 0x17 && msg[0] != 0x1E) {
      data_len = 3;
    } else {
      data_len = 0; // Do not try to decode request telegrams coming from the heataer (0x1E)
    }
    break;
  }
  if (data_len < 0) {
    printFmtToDebug(PSTR("len ERROR %d"), msg[bus->getLen_idx()]);
  } else {
    if (data_len > 0) {
      if (known) {
        if (decodedTelegram.msg_type==TYPE_ERR) {
//          outBufLen+=sprintf(outBuf+outBufLen,"error %d",msg[9]); For truncated error message LPB bus systems
//          if ((msg[9]==0x07 && bus_type==0) || (msg[9]==0x05 && bus_type==1)) {
          decodedTelegram.error = msg[bus->getPl_start()]; //0x07 - parameter not supported
          printFmtToDebug(PSTR("error %d"), decodedTelegram.error);
        } else {
          switch(decodedTelegram.type) {
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
            case VT_PERCENT1: // u8 %
            case VT_BYTE: // u8
//            case VT_VOLTAGE: // u16 - 0.0 -> 00 00 //FUJITSU
              printBYTE(msg,data_len);
              break;
            case VT_MONTHS_WORD: // u16 Monate
            case VT_DAYS_WORD: // u16 Tage
            case VT_HOURS_WORD: // u16 h
            case VT_MINUTES_WORD: //u16 min
            case VT_SECONDS_WORD: //u16 s
            case VT_GRADIENT: // u16
            case VT_INTEGRAL: // u16
            case VT_UINT: //  u16
              printWORD(msg,data_len,decodedTelegram.operand);
              break;
            case VT_MINUTES: // u32 min
            case VT_HOURS: // u32 h
            case VT_DWORD: // s32
            case VT_ENERGY: // u32 / 1.0 kWh
            case VT_SECONDS_DWORD: //u32? s
              printDWORD(msg,data_len,decodedTelegram.operand);
              break;
            case VT_SINT: //  s16
              printSINT(msg,data_len,decodedTelegram.operand);
              break;
            case VT_SECONDS_SHORT4: // s8 / 4 (signed)
            case VT_SECONDS_SHORT5: // s8 / 5 (signed)
            case VT_TEMP_SHORT64: // s8 / 64 (signed)
            case VT_TEMP_SHORT5: // s8 / 2 (signed)
            case VT_TEMP_SHORT: // s8 (signed)
            case VT_TEMP_PER_MIN: // s8
              printFIXPOINT_BYTE(msg,data_len,decodedTelegram.operand,decodedTelegram.precision);
              break;
            case VT_BYTE10: // u8 / 10.0
            case VT_PRESSURE: // u8 / 10.0 bar
            case VT_PRESSURE50: // u8 / 50.0 bar
            case VT_PERCENT5: // u8 %
            case VT_TEMP_SHORT5_US: // u8 / 2 (unsigned)
            case VT_VOLTAGE: // u16 - 0.0 -> 00 00 //FUJITSU -- is this really u16 (two byte) or just enable/disable flag + 1 byte to be divided by 10?
            case VT_TEMP_SHORT_US: //u8 (unsigned)
              printFIXPOINT_BYTE_US(msg,data_len,decodedTelegram.operand,decodedTelegram.precision);
              break;
            case VT_TEMP: // s16 / 64.0 - Wert als Temperatur interpretiert (RAW / 64)
            case VT_SECONDS_WORD5: // u16  - Wert als Temperatur interpretiert (RAW / 2)
            case VT_TEMP_WORD: // s16  - Wert als Temperatur interpretiert (RAW)
            case VT_TEMP_WORD5_US: // s16  - Wert als Temperatur interpretiert (RAW / 2)
            case VT_TEMP_WORD60: //  u16 / 60
            case VT_VOLTAGE_WORD: //unsigned?
            case VT_CELMIN: // u16 / °Cmin
            case VT_LITERPERHOUR: // u16 / l/h
            case VT_LITERPERMIN: // u16 / 0.1 l/min
            case VT_PRESSURE_WORD: // u16 / 10.0 bar
            case VT_PRESSURE_1000: // u16 / 1000.0 bar
            case VT_POWER_WORD: // u16 / 10.0 kW
            case VT_POWER_WORD100: // u16 / 100.0 kW
            case VT_ENERGY_WORD: // u16 / 10.0 kWh
            case VT_SPF: // u16 / 100
            case VT_ENERGY_CONTENT: // u16 / 10.0 kWh/m³
            case VT_CURRENT: // u16 / 100 uA
            case VT_CURRENT1000:
            case VT_PROPVAL: // u16 / 16
            case VT_SPEED: // u16
            case VT_SPEED2: // u16
            case VT_FP1: // s16 / 10.0 Wert als Festkommazahl mit 1/10 Schritten interpretiert (RAW / 10)
            case VT_FP02: // u16 / 50.0 - Wert als Festkommazahl mit 2/100 Schritten interpretiert (RAW / 50)
            case VT_PERCENT_WORD1: // u16 %
            case VT_PERCENT_WORD: // u16 / 2 %
            case VT_PERCENT_100: // u16 / 100 %
            case VT_POWER100: //u32 / 100 kW
            case VT_SINT1000: // s16 / 1000
            case VT_UINT100:  // u32 / 100
            case VT_UINT5: //  u16 / 5
            case VT_UINT10: //  u16 / 10
            case VT_POWER: // u32 / 10.0 kW
            case VT_ENERGY10: // u32 / 10.0 kWh
              printFIXPOINT(msg,data_len,decodedTelegram.operand,decodedTelegram.precision);
              break;
            case VT_ONOFF:
            case VT_YESNO:
            case VT_CLOSEDOPEN:
            case VT_VOLTAGEONOFF:
              printCHOICE(msg,data_len, decodedTelegram.enumstr, decodedTelegram.enumstr_len);
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
/*
//VT_WEEKDAY is ENUM
// ENUM_WEEKDAY used in one program 1642 as enum
//VT_WEEKDAY defined as DT_WDAY but DT_WDAY nowhere used
            case VT_WEEKDAY: // enum
              if (data_len == 2) {
                if (msg[bus->getPl_start()]==0) {
                  int len=sizeof(ENUM_WEEKDAY);
#if defined(__AVR__)
                  printENUM(pgm_get_far_address(ENUM_WEEKDAY),len,msg[bus->getPl_start()+1],0);
#else
                  printENUM(ENUM_WEEKDAY,len,msg[bus->getPl_start()+1],0);
#endif
                } else {
                  undefinedValueToBuffer(decodedTelegram.value);
                  printToDebug(decodedTelegram.value);
                }
              } else {
                printToDebug(PSTR(" VT_WEEKDAY !=2: "));
                prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
                decodedTelegram.error = 256;
                }
              break;
*/
            case VT_ENUM: // enum
              if(data_len == 2 || data_len == 3 || bus->getBusType() == BUS_PPS) {
                if((msg[bus->getPl_start()]==0 && data_len==2) || (msg[bus->getPl_start()]==0 && data_len==3) || (bus->getBusType() == BUS_PPS)) {
                  if(decodedTelegram.enumstr!=0) {
                    if (data_len == 2) {
                      printENUM(decodedTelegram.enumstr,decodedTelegram.enumstr_len,msg[bus->getPl_start()+1],1);
                    } else {                            // Fujitsu: data_len == 3
                      uint8_t pps_offset = 0;
                      if (bus->getBusType() == BUS_PPS) pps_offset = 1;
                      printENUM(decodedTelegram.enumstr,decodedTelegram.enumstr_len,msg[bus->getPl_start()+2-pps_offset],1);
                    }
                  } else {
                    decodedTelegram.error = 259;
                    printToDebug(printError(decodedTelegram.error));
                    SerialPrintData(msg);
                  }
                } else {
                  strcpy_P(decodedTelegram.value, PSTR("65535"));
#if defined(__AVR__)
                  decodedTelegram.enumdescaddr = pgm_get_far_address(STR_DISABLED);
#else
                  decodedTelegram.enumdescaddr = STR_DISABLED;
#endif
//                  undefinedValueToBuffer(decodedTelegram.value);
                  printToDebug(decodedTelegram.value);
                }
              } else {
                printToDebug(PSTR(" VT_ENUM len !=2 && len != 3: "));
                prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
                decodedTelegram.error = 256;
                }
              break;
            case VT_CUSTOM_ENUM: // custom enum - extract information from a telegram that contains more than one kind of information/data. First byte of the ENUM is the index to the payload where the data is located. This will then be used as data to be displayed/evaluated.
            {
              if(decodedTelegram.enumstr!=0) {
                uint8_t idx = pgm_read_byte_far(decodedTelegram.enumstr+0);
                printCustomENUM(decodedTelegram.enumstr,decodedTelegram.enumstr_len,msg[bus->getPl_start()+idx],1);
              } else {
                decodedTelegram.error = 259;
                printToDebug(printError(decodedTelegram.error));
                SerialPrintData(msg);
              }
              break;
            }
            case VT_CUSTOM_BYTE: // custom byte
            {
              if(decodedTelegram.enumstr!=0) {
                uint8_t idx = pgm_read_byte_far(decodedTelegram.enumstr+0);
                uint8_t len = pgm_read_byte_far(decodedTelegram.enumstr+1);
                uint32_t val = 0;
                for (int x=0; x<len; x++) {
                  val = val + ((uint32_t)msg[bus->getPl_start()+idx+x] << (8*(len-1-x)));
                }
#if !defined(ESP32)
                sprintf_P(decodedTelegram.value,PSTR("%lu"),val);
#else
                sprintf_P(decodedTelegram.value,PSTR("%u"),val);
#endif
                printToDebug(decodedTelegram.value);
              } else {
                decodedTelegram.error = 259;
                printToDebug(printError(decodedTelegram.error));
                SerialPrintData(msg);
              }
              break;
            }
            case VT_CUSTOM_BIT: // u8
            {
              uint8_t bit_index = (byte)pgm_read_byte_far(decodedTelegram.enumstr);
              printCustomBIT(msg,bit_index);
              break;
            }
            case VT_STRING: // string
              if (data_len > 0) {
                if (msg[bus->getPl_start()]!=0) {
                  msg[bus->getPl_start() + data_len]='\0'; // write terminating zero
                  printToDebug((char*)&msg[bus->getPl_start()]);
                  strcpy(decodedTelegram.value,(char*)&msg[bus->getPl_start()]);
                  remove_char(decodedTelegram.value, '\'');
                } else {
                  strcpy_P(decodedTelegram.value,PSTR("-"));
                }
                 printToDebug(decodedTelegram.value);
              } else {
                printToDebug(PSTR(" VT_STRING len == 0: "));
                prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
                decodedTelegram.error = 256;
                }
              break;
            case VT_PPS_TIME: // PPS: Time and day of week
            {
              const char *getfarstrings;
              uint8_t q;
              switch(weekday()) {
                case 1: getfarstrings = PSTR(WEEKDAY_SUN_TEXT); break;
                case 2: getfarstrings = PSTR(WEEKDAY_MON_TEXT); break;
                case 3: getfarstrings = PSTR(WEEKDAY_TUE_TEXT); break;
                case 4: getfarstrings = PSTR(WEEKDAY_WED_TEXT); break;
                case 5: getfarstrings = PSTR(WEEKDAY_THU_TEXT); break;
                case 6: getfarstrings = PSTR(WEEKDAY_FRI_TEXT); break;
                case 7: getfarstrings = PSTR(WEEKDAY_SAT_TEXT); break;
                default: getfarstrings = PSTR(""); break;
              }
              q = strlen(strcpy_P(decodedTelegram.value, getfarstrings));
              sprintf_P(decodedTelegram.value + q, PSTR(", %02d:%02d:%02d"), hour(), minute(), second());
              printToDebug(decodedTelegram.value);
              break;
            }
            case VT_ERRORCODE: //  u16 or u8 (via OCI420)
              if(data_len == 3 || data_len == 2) {
                if (msg[bus->getPl_start()]==0) {
                  long lval;
                  if (data_len == 3) {
                    lval=(long(msg[bus->getPl_start()+1])<<8)+long(msg[bus->getPl_start()+2]);
                  } else {
                    lval=long(msg[bus->getPl_start()+1]);
                  }
                  printENUM(decodedTelegram.enumstr, decodedTelegram.enumstr_len,lval,1);
                } else {
                  undefinedValueToBuffer(decodedTelegram.value);
                  printToDebug(decodedTelegram.value);
                }
              } else {
                printToDebug(PSTR(" VT_ERRORCODE len == 0: "));
                prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
                decodedTelegram.error = 256;
                }
              break;
            case VT_UNKNOWN:
            default:
              prepareToPrintHumanReadableTelegram(msg, data_len, bus->getPl_start());
              if(decodedTelegram.telegramDump)
                strcpy(decodedTelegram.value, decodedTelegram.telegramDump);
              decodedTelegram.error = 260;
              break;
          }
        }
      } else {
        if (bus->getBusType() != BUS_PPS) {
          SerialPrintData(msg);
        }
//        writelnToDebug();
//        SerialPrintRAW(msg,msg[len_idx]+bus_type);
        decodedTelegram.error = 257;
      }
    }
  }
  if (bus->getBusType() != BUS_PPS || (bus->getBusType() == BUS_PPS && !monitor)) {
    writelnToDebug();
  }
  if (verbose) {
    if (bus->getBusType() != BUS_PPS) {
      SerialPrintRAW(msg,msg[bus->getLen_idx()]+bus->getBusType());
    } else {
      SerialPrintRAW(msg, 9);
    }
    writelnToDebug();
  }
}

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

#ifdef MAX_CUL

void UpdateMaxDeviceList() {
  char max_id_eeprom[sizeof(max_device_list[0])] = { 0 };
  int32_t max_addr = 0;
  for (uint16_t z = 0; z < MAX_CUL_DEVICES; z++) {
    max_devices[z] = 0; //clearing old MAX! device address for avoiding doublettes
  }

    for (uint16_t z = 0; z < MAX_CUL_DEVICES; z++) {
      if (EEPROM_ready) {
        for(uint16_t i = 0; i < sizeof(max_id_eeprom); i++){
          max_id_eeprom[i] = EEPROM.read(getEEPROMaddress(CF_MAX_DEVICES) + sizeof(max_id_eeprom) * z + i);
        }
      }
      for (uint16_t x = 0; x < MAX_CUL_DEVICES; x++) {
        if (!memcmp(max_device_list[x], max_id_eeprom, sizeof(max_id_eeprom))) {
          if (EEPROM_ready) {
            for(uint16_t i = 0; i < sizeof(max_addr); i++){
             ((char *)&max_addr)[i] = EEPROM.read(getEEPROMaddress(CF_MAX_DEVADDR) + sizeof(max_devices[0]) * z + i);
            }
            max_devices[x] = max_addr;
            printFmtToDebug(PSTR("Adding known Max ID to list: %08lX\r\n"), max_devices[x]);
          }
          break;
        }
      }
    }
  writeToEEPROM(CF_MAX_DEVICES);
  writeToEEPROM(CF_MAX_DEVADDR);
  }
#endif

void print_bus_send_failed(void){
  printlnToDebug(PSTR("bus send failed"));  // to PC hardware serial I/F
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
   flushToWebClient();
   printHTTPheader(HTTP_OK, MIME_TYPE_TEXT_HTML, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_DO_NOT_CACHE);
 #if defined(__AVR__)
   printPStr(pgm_get_far_address(header_html), sizeof(header_html));
 #if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
   printPStr(pgm_get_far_address(header_html2), sizeof(header_html2));
 #endif
   printPStr(pgm_get_far_address(header_html3), sizeof(header_html3));
 #else
   printPStr(header_html, sizeof(header_html));
 #if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
   printPStr(header_html2, sizeof(header_html2));
 #endif
   printPStr(header_html3, sizeof(header_html3));
 #endif
 #if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
   printToWebClient(PSTR("<a href='/"));
   printPassKey();
   printToWebClient(PSTR("' ID=main_link>BSB-LAN</A></h1></center>\r\n"));
   printToWebClient(PSTR("<table align=center><tr bgcolor=#f0f0f0>"));
   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));

   printToWebClient(PSTR("<a href='/"));
   printPassKey();
   printToWebClient(PSTR("K'>" MENU_TEXT_HFK));

   printToWebClient(PSTR("</a></td>"));
   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));
   printToWebClient(PSTR("<a href='/"));
   printPassKey();
   printToWebClient(PSTR("K49'>"));
   printToWebClient(STR_TEXT_SNS);

   printToWebClient(PSTR("</a></td>"));
   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));

   if(!logCurrentValues)
   printToWebClient(PSTR("<font color=#000000>" MENU_TEXT_DLG "</font></td>"));
   else{
     printToWebClient(PSTR("<a href='/"));
     printPassKey();
     printToWebClient(PSTR("DG'>" MENU_TEXT_SLG));
     printToWebClient(PSTR("</a></td>"));
   }

   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));

   printToWebClient(PSTR("<a href='/"));
   printPassKey();
   printToWebClient(PSTR("Q'>" MENU_TEXT_CHK));
   printToWebClient(PSTR("</a></td>"));

   printToWebClient(PSTR("</tr>\r\n<tr bgcolor=#f0f0f0>"));
   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));

   printToWebClient(PSTR("<a href='/"));
   printPassKey();
   printToWebClient(PSTR("C'>" MENU_TEXT_CFG));

   //  client.print(F("</a></td><td width=20% align=center><a href='http://github.com/fredlcore/bsb_lan/blob/master/command_ref/command_ref_" str(LANG) ".md'>" MENU_TEXT_URL));
   printToWebClient(PSTR("</a></td>"));
   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));

   printToWebClient(PSTR("<a href='"));
   printToWebClient(PSTR(MENU_LINK_URL "' target='_new'>" MENU_TEXT_URL));

   printToWebClient(PSTR("</a></td>"));
   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));

   printToWebClient(PSTR("<a href='"));
   printToWebClient(PSTR(MENU_LINK_TOC "' target='new'>" MENU_TEXT_TOC));
   printToWebClient(PSTR("</a></td>"));
   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));

   printToWebClient(PSTR("<a href='"));
   printToWebClient(PSTR(MENU_LINK_FAQ "' target='_new'>" MENU_TEXT_FAQ));
   printToWebClient(PSTR("</a></td>"));

 //  client.println(F("<td width=20% align=center><a href='http://github.com/fredlcore/bsb_lan' target='new'>GitHub Repo</a></td>"));
   printToWebClient(PSTR("</tr></table>"));
#endif
   printToWebClient(PSTR("<p></p><table align=center><tr><td class=\"header\">\r\n"));
   flushToWebClient();
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
  printToWebClient(PSTR("</td></tr></table>\r\n</body>\r\n</html>\r\n\r\n"));
  flushToWebClient();
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

  printlnToWebClient(PSTR("<p>"));
  printToWebClient(PSTR("BSB-LAN, Version "));
  printToWebClient(BSB_VERSION);
  printlnToWebClient(PSTR("<p><b>" MENU_TEXT_HFK ":</b> " MENU_DESC_HFK ));
  printlnToWebClient(PSTR("<p><b>" MENU_TEXT_CFG ":</b> " MENU_DESC_CFG ));
  printlnToWebClient(PSTR("<p><b>" MENU_TEXT_URL ":</b> " MENU_DESC_URL ));

#if !defined(__AVR__)
#ifdef VERSION_CHECK
  if (enable_version_check) {
    printlnToWebClient(PSTR("<BR><BR>" MENU_TEXT_NVS "...<BR>"));
    flushToWebClient();
    httpclient.connect("bsb-lan.de", 80);
    httpclient.println("GET /bsb-version.h\r\n");

    unsigned long timeout = millis();
    while (millis() - timeout < 3000 && !httpclient.available()) {
    }

    int major = -1;
    int minor = -1;
    int patch = -1;
    char version_number[15] = { 0 };
    while (httpclient.available()) {
      char c = httpclient.read();
      if (c == '\"') {
        int index = 0;
        do {
          c = httpclient.read();
          version_number[index] = c;
          index++;
        } while (c != '\"');
        if (index > 1) {
          version_number[index-1] = '\0';
          if (major < 0) {
            major = atoi(version_number);
          } else if (minor < 0) {
            minor = atoi(version_number);
          } else if (patch < 0) {
            patch = atoi(version_number);
          }
        }
      }
    }
    httpclient.stop();
    if ((major > atoi(MAJOR)) || (major == atoi(MAJOR) && minor > atoi(MINOR)) || (major == atoi(MAJOR) && minor == atoi(MINOR) && patch > atoi(PATCH))) {
      printToWebClient(PSTR(MENU_TEXT_NVA ": "));
      printFmtToWebClient(PSTR("<A HREF=\"https://github.com/fredlcore/bsb_lan/archive/master.zip\">%d.%d.%d</A><BR>\r\n"), major, minor, patch);
    } else {
      printlnToWebClient(PSTR(MENU_TEXT_NVN));
    }
  }
#endif
#endif

  webPrintFooter();
} // --- webPrintSite() ---

char *lookup_descr(uint16_t line) {
  int i=findLine(line,0,NULL);
  if (i<0) {                    // Not found (for this heating system)?
    strcpy_PF(outBuf, get_cmdtbl_desc(findLine(19999,0,NULL))); // Unknown command has line no. 19999
  } else {
    strcpy_PF(outBuf, get_cmdtbl_desc(i));
  }
  return outBuf;
}

void generateConfigPage(void){
#if !defined(WEBCONFIG)
  printlnToWebClient(PSTR(MENU_TEXT_CFG "<BR>"));
#endif
  printToWebClient(PSTR("<BR>Hardware: "));
#if defined(__AVR__)
  printToWebClient(PSTR("Mega 2560<BR>\r\n"));
#elif defined(ESP32)
  printToWebClient(PSTR("ESP32<BR>\r\n"));
#else
  printToWebClient(PSTR("Due<BR>\r\n"));
#endif
  printToWebClient(PSTR("" MENU_TEXT_VER ": "));
  printToWebClient(BSB_VERSION);
  printToWebClient(PSTR("<BR>\r\n" MENU_TEXT_RAM ": "));
#ifdef WEBCONFIG
  printFmtToWebClient(PSTR("%d Bytes <BR>\r\n" MENU_TEXT_UPT ": %lu<BR>\r\n"), freeRam(), millis());

#else
  printFmtToWebClient(PSTR("%d Bytes <BR>\r\n" MENU_TEXT_UPT ": %lu"), freeRam(), millis());
  printlnToWebClient(PSTR("<BR>\r\n" MENU_TEXT_BUS ": "));
  int bustype = bus->getBusType();

  switch (bustype) {
    case 0: printToWebClient(PSTR("BSB")); break;
    case 1: printToWebClient(PSTR("LPB")); break;
    case 2: printToWebClient(PSTR("PPS")); break;
  }
  if (bustype != BUS_PPS) {
    printFmtToWebClient(PSTR(" (%d, %d) "), bus->getBusAddr(), bus->getBusDest());

    if ((DEFAULT_FLAG & FL_RONLY) == FL_RONLY || ((DEFAULT_FLAG & FL_SW_CTL_RONLY) == FL_SW_CTL_RONLY && !programWriteMode)) {
      printToWebClient(PSTR(MENU_TEXT_BRO));
    } else {
      printToWebClient(PSTR(MENU_TEXT_BRW));
    }
  } else {
    if (pps_write == 1) {
      printToWebClient(PSTR(" (" MENU_TEXT_BRW ")"));
    } else {
      printToWebClient(PSTR(" (" MENU_TEXT_BRO ")"));
    }
  }
  printFmtToWebClient(PSTR("<BR>\r\n" MENU_TEXT_MMD ": %d"), monitor);
  printFmtToWebClient(PSTR("<BR>\r\n" MENU_TEXT_VBL ": %d<BR>\r\n"), verbose);

  printToWebClient(PSTR(MENU_TEXT_MAC ": \r\n"));
  for (int i=0; i<=5; i++) {
  printFmtToWebClient(PSTR("%02X"), mac[i]);
  if(i != 5) printToWebClient(PSTR(":"));
  }
  printToWebClient(PSTR("<BR>\r\n"));

  #ifdef DHT_BUS
  printlnToWebClient(PSTR(MENU_TEXT_DHP ": "));
  bool not_first = false;
  int numDHTSensors = sizeof(DHT_Pins) / sizeof(DHT_Pins[0]);
  for(int i=0;i<numDHTSensors;i++){
    if(DHT_Pins[i]) {
      if(not_first)
        printToWebClient(PSTR(", "));
      else
        not_first = true;
      printFmtToWebClient(PSTR("%d"), DHT_Pins[i]);
    }
  }
  printToWebClient(PSTR("\r\n<BR>\r\n"));
  #endif
  #endif

  #ifdef ONE_WIRE_BUS
  printFmtToWebClient(PSTR(MENU_TEXT_OWP ": \r\n%d, "), One_Wire_Pin);
  printToWebClient(STR_TEXT_SNS);
  printFmtToWebClient(PSTR(": %d\r\n<BR>\r\n"), numSensors);
  #endif
  printToWebClient(PSTR(MENU_TEXT_EXP ": \r\n"));
  for (int i=0; i<anz_ex_gpio; i++) {
    if (bitRead(protected_GPIO[i / 8], i % 8)) {
      printFmtToWebClient(PSTR("%d "), i);
    }
  }

  printToWebClient(PSTR("<BR><BR>\r\n"));
/*
  client.println(F("IP address: "));
  client.println(ip);
  client.println(F("<BR>"));
*/
// list of enabled modules
  printToWebClient(PSTR(MENU_TEXT_MOD ": <BR>\r\n"

  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  #ifdef DEBUG
  "Verbose "
  #endif
  "DEBUG"

  #ifdef WEBSERVER
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "WEBSERVER"
  #endif
  #ifdef IPWE
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "IPWE"
  #endif
  #ifdef CUSTOM_COMMANDS
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "CUSTOM_COMMANDS"
  #endif
  #ifdef MQTT
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "MQTT"
  #endif
  #ifdef LOGGER
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "LOGGER"
  #endif
  #ifdef VERSION_CHECK
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "VERSION_CHECK"
  #endif
  #ifdef AVERAGES
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "AVERAGES"
  #endif
  #ifdef MAX_CUL
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "MAX_CUL"
  #endif
  #ifdef ONE_WIRE_BUS
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "ONE_WIRE_BUS"
  #endif
  #ifdef DHT_BUS
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "DHT_BUS"
  #endif
  #ifdef BME280
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "BME280"
  #endif
  #ifdef CUSTOM_COMMANDS
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "CUSTOM_COMMANDS"
  #endif
  #ifdef CONFIG_IN_EEPROM
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "CONFIG_IN_EEPROM"
  #endif
  #ifdef WEBCONFIG
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "WEBCONFIG"
  #endif
  #ifdef JSONCONFIG
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "JSONCONFIG"
  #endif

  #ifdef URLCONFIG
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "URLCONFIG"
  #endif

  #ifdef MDNS_HOSTNAME
  #if defined (ANY_MODULE_COMPILED)
  ", "
  #else
  #define ANY_MODULE_COMPILED
  #endif
  "MDNS"
  #endif

  #if !defined (ANY_MODULE_COMPILED)
  "NONE"
  #endif
  "<BR><BR>\r\n"));

  // end of list of enabled modules

#if defined LOGGER || defined WEBSERVER
//  uint32_t m = micros();
  uint32_t volFree = SD.vol()->freeClusterCount();
  uint32_t fs = (uint32_t)(volFree*SD.vol()->blocksPerCluster()/2048);
  printToWebClient(STR_TEXT_FSP);
  printFmtToWebClient(PSTR(": %lu MB<br>\r\n"), fs);
//  printFmtToWebClient(PSTR("Free space: %lu MB<br>free clusters: %lu<BR>freeClusterCount() call time: %lu microseconds<BR><br>\r\n"), fs, volFree, micros() - m);
#endif
printToWebClient(PSTR("<BR>\r\n"));

#ifndef WEBCONFIG
#ifdef AVERAGES
  if (logAverageValues) {
    printToWebClient(CF_LOGAVERAGES_TXT);
/*
    printToWebClient(PSTR(": "));
#if defined(__AVR__)
    printENUM(pgm_get_far_address(ENUM_ONOFF),sizeof(ENUM_ONOFF),logAverageValues,0);
#else
    printENUM(ENUM_ONOFF,sizeof(ENUM_ONOFF),logAverageValues,0);
#endif
    printToWebClient(decodedTelegram.enumdescaddr);
*/
    printToWebClient(PSTR("<BR>\r\n"));
    printToWebClient(CF_AVERAGESLIST_TXT);
    printToWebClient(PSTR(": <BR>\r\n"));

    for (int i=0; i<numAverages; i++) {
      if (avg_parameters[i] > 0) {
        printFmtToWebClient(PSTR("%d - %s: %d<BR>\r\n"), avg_parameters[i], lookup_descr(avg_parameters[i]), 20050 + i);//outBuf will be overwrited here
      }
    }
    printToWebClient(PSTR("<BR>"));
  }
#endif
  #ifdef LOGGER
  printFmtToWebClient(PSTR("<BR>" MENU_TEXT_LGP " \r\n%d"), log_interval);
  printToWebClient(PSTR(" " MENU_TEXT_SEC ": "));
  printyesno(logCurrentValues);
  printToWebClient(PSTR("<BR>\r\n"));
  for (int i=0; i<numLogValues; i++) {
    if (log_parameters[i] > 0) {
      printFmtToWebClient(PSTR("%d - "), log_parameters[i]);
      printToWebClient(lookup_descr(log_parameters[i]));//outBuf will be overwrited here
      printToWebClient(PSTR("<BR>\r\n"));
    }
  }

if (logTelegram) {
  printToWebClient(PSTR(MENU_TEXT_BDT "<BR>\r\n" MENU_TEXT_BUT ": "));
  printyesno(logTelegram & (LOGTELEGRAM_ON + LOGTELEGRAM_UNKNOWN_ONLY)); //log_unknown_only
  printToWebClient(PSTR(MENU_TEXT_LBO ": "));
  printyesno(logTelegram & (LOGTELEGRAM_ON + LOGTELEGRAM_BROADCAST_ONLY)); //log_bc_only
  }
#endif
#endif
  printToWebClient(PSTR("<BR>\r\n"));
}

#if defined(WEBCONFIG) || defined(JSONCONFIG)
uint8_t takeNewConfigValueFromUI_andWriteToEEPROM(int option_id, char *buf){
  bool finded = false;
  configuration_struct cfg;
  char sscanf_buf[24];

  for(uint16_t f = 0; f < sizeof(config)/sizeof(config[0]); f++){
    #if defined(__AVR__)
        if(pgm_read_byte_far(pgm_get_far_address(config[0].var_type) + f * sizeof(config[0])) == CDT_VOID) continue;
        memcpy_PF(&cfg, pgm_get_far_address(config[0]) + f * sizeof(config[0]), sizeof(cfg));
    #else
        if(config[f].var_type == CDT_VOID) continue;
        memcpy(&cfg, &config[f], sizeof(cfg));
    #endif

    if(cfg.id == option_id) {finded = true; break;}
  }
  if (!finded) {
    return 2;
  }

  switch(cfg.var_type){
    case CDT_VOID: break;
    case CDT_BYTE:{
      byte variable = atoi(buf);
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
    case CDT_STRING:
      writeToConfigVariable(option_id, (byte *)buf);
      break;
    case CDT_MAC:{
      unsigned int i0, i1, i2, i3, i4, i5;
      strcpy_P(sscanf_buf, PSTR("%x:%x:%x:%x:%x:%x"));
      sscanf(buf, sscanf_buf, &i0, &i1, &i2, &i3, &i4, &i5);
      byte variable[6];
      variable[0] = (byte)(i0 & 0xFF);
      variable[1] = (byte)(i1 & 0xFF);
      variable[2] = (byte)(i2 & 0xFF);
      variable[3] = (byte)(i3 & 0xFF);
      variable[4] = (byte)(i4 & 0xFF);
      variable[5] = (byte)(i5 & 0xFF);
      writeToConfigVariable(option_id, variable);
      break;
    }
    case CDT_IPV4:{
      unsigned int i0, i1, i2, i3;
      strcpy_P(sscanf_buf, PSTR("%u.%u.%u.%u"));
      sscanf(buf, sscanf_buf, &i0, &i1, &i2, &i3);
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
        if(ptr) ptr[0] = 0;
        ((int *)variable)[j] = atoi(ptr_t);
        if(ptr) {ptr[0] = ','; ptr++;}
        j++;
      }while(ptr && j < cfg.size/sizeof(int));
      // writeToConfigVariable(option_id, variable); not needed here
      break;}
    case CDT_DHTBUS:{
      uint16_t j = 0;
      char *ptr = buf;
      byte *variable = getConfigVariableAddress(option_id);
      memset(variable, 0, cfg.size);
      do{
        char *ptr_t = ptr;
        ptr = strchr(ptr, ',');
        if(ptr) ptr[0] = 0;
        variable[j] = (byte)atoi(ptr_t);
        if(ptr) {ptr[0] = ','; ptr++;}

        j++;
      }while(ptr && j < cfg.size/sizeof(byte));
      // writeToConfigVariable(option_id, variable); not needed here
      break;}
#ifdef MAX_CUL
    case CDT_MAXDEVICELIST:{
      uint16_t j = 0;
      char *ptr = buf;
      byte *variable = getConfigVariableAddress(option_id);
      memset(variable, 0, cfg.size);
      do{
        char *ptr_t = ptr;
        ptr = strchr(ptr, ',');
        if(ptr) ptr[0] = 0;
        strncpy((char *)(variable + j * sizeof(max_device_list[0])), ptr_t, sizeof(max_device_list[0]));
        if(ptr) {ptr[0] = ','; ptr++;}
        j++;
      }while(ptr && j < cfg.size/sizeof(max_device_list[0]));
      // writeToConfigVariable(option_id, variable); not needed here
      UpdateMaxDeviceList();
      break;}
#endif
    default: break;
  }

return 1;
}

bool SaveConfigFromRAMtoEEPROM(){
  bool buschanged = false;
  bool needReboot = false;
  //save new values from RAM to EEPROM
  for(uint8_t i = 0; i < CF_LAST_OPTION; i++){
    if (writeToEEPROM(i)) {
      switch(i){
        case CF_BUSTYPE:
        case CF_OWN_BSBLPBADDR:
        case CF_DEST_BSBLPBADDR:
        case CF_PPS_MODE:
          buschanged = true;
          break;
        //Unfortunately Ethernet Shield not supported dynamic reconfiguration of EthernetServer(s)
        // so here no reason do dynamic reconfiguration.
        // Topic: Possible to STOP an ethernet server once started and release resources ?
        // https://forum.arduino.cc/index.php?topic=395827.0
        // Topic: Dynamically changing IP address of Ethernet Shield (not DHCP and without reboot)
        // https://forum.arduino.cc/index.php?topic=89469.0
        // Resume: it possible but can cause unpredicable effects
        case CF_MAC:
        case CF_DHCP:
        case CF_IPADDRESS:
        case CF_MASK:
        case CF_GATEWAY:
        case CF_DNS:
        case CF_ONEWIREBUS:
        case CF_WWWPORT:
        case CF_WIFI_SSID:
        case CF_WIFI_PASSWORD:
          needReboot = true;
          break;
        case CF_TWW_PUSH_PIN_ID: //How to do dynamic reconfiguration of interrupts?
        case CF_RGT1_PRES_PIN_ID:
        case CF_RGT2_PRES_PIN_ID:
        case CF_RGT3_PRES_PIN_ID:
          needReboot = true;
          break;
#ifdef AVERAGES
        case CF_AVERAGESLIST:
          resetAverageCalculation();
          break;
#endif
#ifdef MAX_CUL
        case CF_MAX:
        case CF_MAX_IPADDRESS:
          connectToMaxCul();
          break;
#endif
#ifdef MQTT
        case CF_MQTT:
        case CF_MQTT_IPADDRESS:
          if (MQTTPubSubClient) {
            delete MQTTPubSubClient;
            MQTTPubSubClient = NULL;
            mqtt_client->stop();
            delete mqtt_client;
          }
          break;
#endif
        default: break;
      }
    }
  }
  // EEPROM dump require ~3 sec so let it be last operation.
  // Dump when serial debug active or have telnet client
  EEPROM_dump();

  if(buschanged) {setBusType(); }
  return needReboot;
}
#endif

#ifdef WEBCONFIG
void implementConfig(){
  bool k_flag = false;
  int i = 0;
  int option_id = 0;

  while (client.available()) {
    char c = client.read();
    if(!k_flag && i == OUTBUF_LEN - 2) { //buffer filled. trash in buffer?
      for(int j = 0; j < 16; j++){
        outBuf[j] = outBuf[i - 16 + j];
      }
      i = 16;
    }

    if (c == '=') { //key/value delimiter
      char *ptr = strstr_P(outBuf, PSTR("option_"));
      if(!ptr) continue;
      ptr += 7; //len of "option_" string
      option_id = atoi(ptr) - 1;
      printFmtToDebug(PSTR("Option ID: %d\r\n"), option_id);
      k_flag = true;
      i = 0;
      outBuf[i] = 0;
      continue;
    }
    if(k_flag && (c == '&' || i == OUTBUF_LEN - 2 || !client.available())) { //new pair key=value or buffer filled or last symbol was reading
      if (!client.available()) { //copy last symbol to buffer
        outBuf[i++] = c;
        outBuf[i] = 0;
      }

      if(takeNewConfigValueFromUI_andWriteToEEPROM(option_id, outBuf)  == 1)
        printFmtToDebug(PSTR("Option value: %s\r\n"), outBuf);

      k_flag = false;
      i = 0;
      outBuf[i] = 0;
      continue;
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

void printConfigWebPossibleValues(int i, uint16_t temp_value){
  uint16_t enumstr_len=get_cmdtbl_enumstr_len(i);
  uint_farptr_t enumstr = calc_enum_offset(get_cmdtbl_enumstr(i), enumstr_len, 0);
  listEnumValues(enumstr, enumstr_len, STR_OPTION_VALUE, PSTR("'>"), STR_SELECTED, STR_CLOSE_OPTION, NULL, temp_value, PRINT_VALUE_FIRST, DO_NOT_PRINT_DISABLED_VALUE);

}

int returnENUMID4ConfigOption(uint8_t id){
  int i = 0;
  switch(id){
    case CF_BUSTYPE:
      i=findLine(65532,0,NULL); //return ENUM_BUSTYPE
      break;
    case CF_LOGTELEGRAM:
      i=findLine(65531,0,NULL); //return ENUM_LOGTELEGRAM
      break;
    case CF_DEBUG:
    i=findLine(65530,0,NULL); //return ENUM_DEBUG
      break;
    case CF_MQTT:
      i=findLine(65529,0,NULL); //return ENUM_MQTT
      break;
    case CF_WRITEMODE:
      i=findLine(65528,0,NULL); //return ENUM_WRITEMODE
      break;
    case CF_PPS_MODE:
      i=findLine(65527,0,NULL); //return ENUM_PPS_MODE
      break;
    default:
      i = -1;
      break;
  }
  return i;
}

void generateChangeConfigPage(){
  printlnToWebClient(PSTR(MENU_TEXT_CFG "<BR>"));
  printToWebClient(PSTR("<form id=\"config\" method=\"post\" action=\""));
  if (PASSKEY[0]) {printToWebClient(PSTR("/")); printToWebClient(PASSKEY);}
  printToWebClient(PSTR("/CI\"><table align=\"center\"><tbody>\r\n"));
  for(uint16_t i = 0; i < sizeof(config)/sizeof(config[0]); i++){
#if defined(__AVR__)
    if(pgm_read_byte_far(pgm_get_far_address(config[0].var_type) + i * sizeof(config[0])) == CDT_VOID) continue;
#else
    if(config[i].var_type == CDT_VOID) continue;
#endif

    configuration_struct cfg;

#if defined(__AVR__)
    memcpy_PF(&cfg, pgm_get_far_address(config[0].id) + i * sizeof(config[0]), sizeof(cfg));
#else
    memcpy(&cfg, &config[i], sizeof(cfg));
#endif
    byte *variable = getConfigVariableAddress(cfg.id);
    if(!variable) continue;

    printToWebClient(PSTR("<tr><td>"));
//Print param category
#if defined(__AVR__)
    printToWebClient(pgm_read_word_far(pgm_get_far_address(catalist[0].desc) + cfg.category * sizeof(catalist[0])));
#else
    printToWebClient(catalist[cfg.category].desc);
#endif

    printToWebClient(PSTR("</td><td>\r\n"));
//Param Name
    printToWebClient(cfg.desc);
    printToWebClient(PSTR("</td><td>\r\n"));
//Param Value

//Open tag
   switch(cfg.input_type){
     case CPI_TEXT:
     printFmtToWebClient(PSTR("<input type=text id='option_%d' name='option_%d' "), cfg.id + 1, cfg.id + 1);
     switch(cfg.var_type){
       case CDT_MAC:
         printToWebClient(PSTR("pattern='^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$'"));
         break;
       case CDT_IPV4:
         printToWebClient(PSTR("pattern='((^|\\.)((25[0-5])|(2[0-4]\\d)|(1\\d\\d)|([1-9]?\\d))){4}'"));
         break;
       case CDT_PROGNRLIST:
         printToWebClient(PSTR("pattern='(((^|,)((\\d){1,5})))*'"));
         break;
       }
     printToWebClient(PSTR(" VALUE='"));
     break;
     case CPI_SWITCH:
     case CPI_DROPDOWN:
     printFmtToWebClient(PSTR("<select id='option_%d' name='option_%d'>\r\n"), cfg.id + 1, cfg.id + 1);
     break;
     default: break;
   }


   switch(cfg.var_type){
     case CDT_VOID: break;
     case CDT_BYTE:
       switch(cfg.input_type){
         case CPI_TEXT: printFmtToWebClient(PSTR("%d"), (int)variable[0]); break;
         case CPI_SWITCH:{
           int i;
           switch(cfg.id){
             case CF_USEEEPROM:
               i=findLine(65534,0,NULL); //return ENUM_EEPROM_ONOFF
               break;
             default:
               i=findLine(65533,0,NULL); //return ENUM_ONOFF
               break;
           }
           printConfigWebPossibleValues(i, (uint16_t)variable[0]);
           break;}
         case CPI_DROPDOWN:{
           int i = returnENUMID4ConfigOption(cfg.id);
           if (i > 0) {
             printConfigWebPossibleValues(i, variable[0]);
           }
           break;}
         }
       break;
     case CDT_UINT16:
       switch(cfg.input_type){
         case CPI_TEXT: printFmtToWebClient(PSTR("%u"), ((uint16_t *)variable)[0]); break;
         case CPI_DROPDOWN:{
           int i;
           switch(cfg.id){
             case CF_ROOM_DEVICE:
               i=findLine(15000 + PPS_QTP,0,NULL); //return ENUM15062 (device type)
               break;
             default:
               i = -1;
               break;
           }
           if (i > 0) {
             printConfigWebPossibleValues(i, ((uint16_t *)variable)[0]);
           }
           break;}
         }
       break;
     case CDT_UINT32:
       printFmtToWebClient(PSTR("%lu"), ((uint32_t *)variable)[0]);
       break;
     case CDT_STRING:
       printFmtToWebClient(PSTR("%s"), (char *)variable);
       break;
     case CDT_MAC:
       {bool isFirst = true;
       for(uint8_t z = 0; z < 6; z++){
         if(isFirst) isFirst = false; else printToWebClient(PSTR(":"));
         printFmtToWebClient(PSTR("%02X"), (int)variable[z]);
       }}
  //       printFmtToWebClient(PSTR("%02X:%02X:%02X:%02X:%02X:%02X"), (int)variable[0], (int)variable[1], (int)variable[2], (int)variable[3], (int)variable[4], (int)variable[5]);
       break;
     case CDT_IPV4:
       printFmtToWebClient(PSTR("%u.%u.%u.%u"), (int)variable[0], (int)variable[1], (int)variable[2], (int)variable[3]);
       break;
     case CDT_PROGNRLIST:{
       bool isFirst = true;
       for(uint16_t j = 0; j < cfg.size/sizeof(int); j++){
         if (((int *)variable)[j]) {
           if(!isFirst) printToWebClient(PSTR(","));
           isFirst = false;
           printFmtToWebClient(PSTR("%d"), ((int *)variable)[j]);
         }
       }
       break;}
     case CDT_DHTBUS:{
       bool isFirst = true;
       for(uint16_t j = 0; j < cfg.size/sizeof(byte); j++){
         if (variable[j]) {
           if(!isFirst) printToWebClient(PSTR(","));
           isFirst = false;
           printFmtToWebClient(PSTR("%d"), variable[j]);
         }
       }
       break;}
     case CDT_MAXDEVICELIST:{
       bool isFirst = true;
       for(uint16_t j = 0; j < cfg.size/sizeof(byte); j += sizeof(max_device_list[0])){
         if (variable[j]) {
           if(!isFirst) printToWebClient(PSTR(","));
           isFirst = false;
           printFmtToWebClient(PSTR("%s"), variable + j);
         }
       }
       break;}
     default: break;
   }

//Closing tag
   switch(cfg.input_type){
     case CPI_TEXT: printToWebClient(PSTR("'>")); break;
     case CPI_SWITCH:
     case CPI_DROPDOWN: printToWebClient(PSTR("</select>")); break;
     default: break;
   }
    printToWebClient(PSTR("</td></td>\r\n"));
  }
  printToWebClient(PSTR("</tbody></table><p><input type=\"submit\" value=\""));
  printToWebClient(STR6204);
  printToWebClient(PSTR("\"></p>\r\n</form>\r\n"));
}
#endif  //WEBCONFIG


#if defined(JSONCONFIG)
void printConfigJSONPossibleValues(int i){
  printToWebClient(PSTR("    \"possibleValues\": [\r\n"));
  uint16_t enumstr_len=get_cmdtbl_enumstr_len(i);
  uint_farptr_t enumstr = calc_enum_offset(get_cmdtbl_enumstr(i), enumstr_len, 0);
  listEnumValues(enumstr, enumstr_len, PSTR("      { \"enumValue\": \""), PSTR("\", \"desc\": \""), NULL, PSTR("\" }"), PSTR(",\r\n"), 0, PRINT_VALUE_FIRST, DO_NOT_PRINT_DISABLED_VALUE);
  printToWebClient(PSTR("\r\n      ]"));
}

void generateJSONwithConfig(){
  bool notFirst = false;
  for(uint16_t i = 0; i < sizeof(config)/sizeof(config[0]); i++){
#if defined(__AVR__)
    if(pgm_read_byte_far(pgm_get_far_address(config[0].var_type) + i * sizeof(config[0])) == CDT_VOID) continue;
#else
    if(config[i].var_type == CDT_VOID) continue;
#endif

    configuration_struct cfg;

#if defined(__AVR__)
    memcpy_PF(&cfg, pgm_get_far_address(config[0].id) + i * sizeof(config[0]), sizeof(cfg));
#else
    memcpy(&cfg, &config[i], sizeof(cfg));
#endif
    byte *variable = getConfigVariableAddress(cfg.id);
    if(!variable) continue;
    if (notFirst) {printToWebClient(PSTR("\r\n    },\r\n"));} else notFirst = true;

    printFmtToWebClient(PSTR("  \"%d\": {\r\n    \"parameter\": %d,\r\n    \"type\": %d,\r\n    \"format\": %d,\r\n    \"category\": \""), i, cfg.id, cfg.var_type, cfg.input_type);
//Print param category
#if defined(__AVR__)
    printToWebClient(pgm_read_word_far(pgm_get_far_address(catalist[0].desc) + cfg.category * sizeof(catalist[0])));
#else
    printToWebClient(catalist[cfg.category].desc);
#endif

    printToWebClient(PSTR("\",\r\n    \"name\": \""));
//Param Name
    printToWebClient(cfg.desc);
    printToWebClient(PSTR("\",\r\n    \"value\": \""));
//Param Value

   switch(cfg.var_type){
     case CDT_VOID: break;
     case CDT_BYTE:
       switch(cfg.input_type){
         case CPI_TEXT: printFmtToWebClient(PSTR("%d\""), (int)variable[0]); break;
         case CPI_SWITCH:{
           int i;
           switch(cfg.id){
             case CF_USEEEPROM:
               i=findLine(65534,0,NULL); //return ENUM_EEPROM_ONOFF
               break;
             default:
               i=findLine(65533,0,NULL); //return ENUM_ONOFF
               break;
           }
           printFmtToWebClient(PSTR("%d\",\r\n"), (uint16_t)variable[0]);
           printConfigJSONPossibleValues(i);
           break;}
         case CPI_DROPDOWN:{
           int i = returnENUMID4ConfigOption(cfg.id);
           if (i > 0) {
             printFmtToWebClient(PSTR("%d\",\r\n"), (uint16_t)variable[0]);
             printConfigJSONPossibleValues(i);
           }
           break;}
         }
       break;
     case CDT_UINT16:
       switch(cfg.input_type){
         case CPI_TEXT: printFmtToWebClient(PSTR("%u\""), ((uint16_t *)variable)[0]); break;
         case CPI_DROPDOWN:{
           int i;
           switch(cfg.id){
             case CF_ROOM_DEVICE:
               i=findLine(15000 + PPS_QTP,0,NULL); //return ENUM15062 (device type)
               break;
             default:
               i = -1;
               break;
           }
           if (i > 0) {
             printFmtToWebClient(PSTR("%d\",\r\n"), ((uint16_t *)variable)[0]);
             printConfigJSONPossibleValues(i);
           }
           break;}
         }
       break;
     case CDT_UINT32:
       printFmtToWebClient(PSTR("%lu\""), ((uint32_t *)variable)[0]);
       break;
     case CDT_STRING:
       printFmtToWebClient(PSTR("%s\""), (char *)variable);
       break;
     case CDT_MAC:
       {bool isFirst = true;
       for(uint8_t z = 0; z < 6; z++){
         if(isFirst) isFirst = false; else printToWebClient(PSTR(":"));
         printFmtToWebClient(PSTR("%02X"), (int)variable[z]);
       }}
       printToWebClient(PSTR("\""));
  //       printFmtToWebClient(PSTR("%02X:%02X:%02X:%02X:%02X:%02X"), (int)variable[0], (int)variable[1], (int)variable[2], (int)variable[3], (int)variable[4], (int)variable[5]);
       break;
     case CDT_IPV4:
       printFmtToWebClient(PSTR("%u.%u.%u.%u\""), (int)variable[0], (int)variable[1], (int)variable[2], (int)variable[3]);
       break;
     case CDT_PROGNRLIST:{
       bool isFirst = true;
       for(uint16_t j = 0; j < cfg.size/sizeof(int); j++){
         if (((int *)variable)[j]) {
           if(!isFirst) printToWebClient(PSTR(","));
           isFirst = false;
           printFmtToWebClient(PSTR("%d"), ((int *)variable)[j]);
         }
       }
       printToWebClient(PSTR("\""));
       break;}
     case CDT_DHTBUS:{
       bool isFirst = true;
       for(uint16_t j = 0; j < cfg.size/sizeof(byte); j++){
         if (variable[j]) {
           if(!isFirst) printToWebClient(PSTR(","));
           isFirst = false;
           printFmtToWebClient(PSTR("%d"), variable[j]);
         }
       }
       printToWebClient(PSTR("\""));
       break;}
     case CDT_MAXDEVICELIST:{
       bool isFirst = true;
       for(uint16_t j = 0; j < cfg.size/sizeof(byte); j += sizeof(max_device_list[0])){
         if (variable[j]) {
           if(!isFirst) printToWebClient(PSTR(","));
           isFirst = false;
           printFmtToWebClient(PSTR("%s"), variable + j);
         }
       }
       printToWebClient(PSTR("\""));
       break;}
     default: break;
   }
  }
  printToWebClient(PSTR("\r\n    }\r\n"));
}
#endif //JSONCONFIG

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
char *GetDateTime(char *date){
  sprintf_P(date,PSTR("%02d.%02d.%d %02d:%02d:%02d"),day(),month(),year(),hour(),minute(),second());
  date[19] = 0;
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
  if(!(logTelegram & LOGTELEGRAM_ON)) return;
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
  uint16_t line = 0;
  if(SD.vol()->freeClusterCount() < MINIMUM_FREE_SPACE_ON_SD) return;

  if (bus->getBusType() != BUS_PPS) {
    if(msg[4+(bus->getBusType()*4)]==TYPE_QUR || msg[4+(bus->getBusType()*4)]==TYPE_SET || (((msg[2]!=ADDR_ALL && bus->getBusType()==BUS_BSB) || (msg[2]<0xF0 && bus->getBusType()==BUS_LPB)) && msg[4+(bus->getBusType()*4)]==TYPE_INF)) { //QUERY and SET: byte 5 and 6 are in reversed order
      cmd=(uint32_t)msg[6+(bus->getBusType()*4)]<<24 | (uint32_t)msg[5+(bus->getBusType()*4)]<<16 | (uint32_t)msg[7+(bus->getBusType()*4)] << 8 | (uint32_t)msg[8+(bus->getBusType()*4)];
    } else {
      cmd=(uint32_t)msg[5+(bus->getBusType()*4)]<<24 | (uint32_t)msg[6+(bus->getBusType()*4)]<<16 | (uint32_t)msg[7+(bus->getBusType()*4)] << 8 | (uint32_t)msg[8+(bus->getBusType()*4)];
    }
  } else {
//      cmd=msg[1+(msg[0]==0x17 && pps_write != 1)];
    cmd=msg[1];
  }
  // search for the command code in cmdtbl
  c=get_cmdtbl_cmd(i);
//    c=pgm_read_dword(&cmdtbl[i].cmd);    // extract the command code from line i
  while(c!=CMD_END){
    line=get_cmdtbl_line(i);
    if((bus->getBusType() != BUS_PPS && c == cmd) || (bus->getBusType() == BUS_PPS && line >= 15000 && (cmd == ((c & 0x00FF0000) >> 16)))) {   // one-byte command code of PPS is stored in bitmask 0x00FF0000 of command ID
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
  }
  if(cmd <= 0) return;
  bool logThis = false;
  switch(logTelegram){
    case LOGTELEGRAM_ON: logThis = true; break;
    case LOGTELEGRAM_ON + LOGTELEGRAM_UNKNOWN_ONLY: if(known == 0)  logThis = true; break;
    case LOGTELEGRAM_ON + LOGTELEGRAM_BROADCAST_ONLY: if((msg[2]==ADDR_ALL && bus->getBusType()==BUS_BSB) || (msg[2]>=0xF0 && bus->getBusType()==BUS_LPB))  logThis = true; break;
    case LOGTELEGRAM_ON + LOGTELEGRAM_UNKNOWNBROADCAST_ONLY: if(known == 0 && ((msg[2]==ADDR_ALL && bus->getBusType()==BUS_BSB) || (msg[2]>=0xF0 && bus->getBusType()==BUS_LPB))) logThis = true; break;
    default: logThis = false; break;
  }
  if (logThis) {
    dataFile = SD.open(journalFileName, FILE_WRITE);
    if (dataFile) {
      int outBufLen = 0;
      outBufLen += sprintf_P(outBuf, PSTR("%lu;%s;"), millis(), GetDateTime(outBuf + outBufLen + 80));
      if (!known) {                          // no hex code match
      // Entry in command table is "UNKNOWN" (0x00000000)
        outBufLen += strlen(strcpy_P(outBuf + outBufLen, PSTR("UNKNOWN")));
      } else {
        // Entry in command table is a documented command code
        line=get_cmdtbl_line(i);
        cmd_type=get_cmdtbl_type(i);
        outBufLen += sprintf_P(outBuf + outBufLen, PSTR("%d"), line);
        }

      uint8_t msg_len = 0;
      if (bus->getBusType() != BUS_PPS) {
        outBufLen += sprintf_P(outBuf + outBufLen, PSTR(";%s->%s %s;"), TranslateAddr(msg[1+(bus->getBusType()*2)], outBuf + outBufLen + 40), TranslateAddr(msg[2], outBuf + outBufLen + 50), TranslateType(msg[4+(bus->getBusType()*4)], outBuf + outBufLen + 60));
        msg_len = msg[bus->getLen_idx()]+bus->getBusType();
      } else {
        strcat_P(outBuf + outBufLen, PSTR(";"));
        const char *getfarstrings;
        switch (msg[0]) {
          case 0x1D: getfarstrings = PSTR("HEIZ->QAA INF"); break;
          case 0x1E: getfarstrings = PSTR("HEIZ->QAA REQ"); break;
          case 0x17: getfarstrings = PSTR("HEIZ->QAA RTS"); break;
          case 0xF8:
          case 0xFB:
          case 0xFD:
          case 0xFE:
            getfarstrings = PSTR("QAA->HEIZ ANS"); break;
          default: getfarstrings = PSTR(""); break;
        }
        strcat_P(outBuf + outBufLen, getfarstrings);
        strcat_P(outBuf + outBufLen, PSTR(";"));
        outBufLen += strlen(outBuf + outBufLen);
//            msg_len = 9+(msg[0]==0x17 && pps_write != 1);
        msg_len = 9;
      }

      for(int i=0;i<msg_len;i++){
        outBufLen += sprintf_P(outBuf + outBufLen, PSTR("%02X "), msg[i]);
      }
      outBuf[--outBufLen] = 0; //erase last space
      // additionally log data payload in addition to raw messages when data payload is max. 32 Bit

      if (bus->getBusType() != BUS_PPS && (msg[4+(bus->getBusType()*4)] == TYPE_INF || msg[4+(bus->getBusType()*4)] == TYPE_SET || msg[4+(bus->getBusType()*4)] == TYPE_ANS) && msg[bus->getLen_idx()] < 17+bus->getBusType()) {
        outBufLen += strlen(strcat_P(outBuf + outBufLen, PSTR(";")));
        if (bus->getBusType() == BUS_LPB) {
          data_len=msg[1]-14;
        } else {
          data_len=msg[3]-11;
        }
        dval = 0;
#if defined(__AVR__)
        operand=pgm_read_float_far(pgm_get_far_address(optbl[0].operand) + cmd_type * sizeof(optbl[0]));
        precision=pgm_read_byte_far(pgm_get_far_address(optbl[0].precision) + cmd_type * sizeof(optbl[0]));
#else
        operand=optbl[cmd_type].operand;
        precision=optbl[cmd_type].precision;
#endif
        for (i=0;i<data_len-1+bus->getBusType();i++) {
          if (bus->getBusType() == BUS_LPB) {
            dval = dval + long(msg[14+i-(msg[8]==TYPE_INF)]<<((data_len-2-i)*8));
          } else {
            dval = dval + long(msg[10+i-(msg[4]==TYPE_INF)]<<((data_len-2-i)*8));
          }
        }
        dval = dval / operand;
        _printFIXPOINT(outBuf + outBufLen, dval, precision);
        // print ',' instead '.'
        char *p = strchr(outBuf + outBufLen,'.');
        if (p != NULL) *p=',';
        outBufLen += strlen(outBuf + outBufLen);
      }
      strcat_P(outBuf + outBufLen, PSTR("\r\n"));
      dataFile.print(outBuf);
      dataFile.close();
    }
  }
}
#else
void LogTelegram(byte* msg){
  msg = msg; //disable compiler warning
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
  uint8_t param_len = 0;
  char sscanf_buf[36]; //Max format length is VT_TIMEPROG

  if (line < 0){
    return 0;
  }
  // Search the command table from the start for a matching line nbr.
  i=findLine(line,0,&c);   // find the ProgNr and get the command code
  if(i<0) return 0;        // no match

  // Check for readonly parameter
  if (programIsreadOnly(get_cmdtbl_flags(i))) {
    printlnToDebug(PSTR("Parameter is readonly!"));
    return 2;   // return value for trying to set a readonly parameter
  }

  loadPrognrElementsFromTable(line, i);

  if((line >= 20000 && line < 20900)) //virtual functions handler
    {
      switch(line){
        case 20006: if(atoi(val)) resetDurations(); return 1; // reset furnace duration
      }
      if((line >= 20700 && line < 20700 + numCustomFloats)) {// set custom_float
        custom_floats[line - 20700] = atof(val);
        return 1;
      }
      if((line >= 20800 && line < 20800 + numCustomLongs)) {// set custom_float
        char sscanf_buf[8]; //This parser looks bulky but it take space lesser than custom_longs[line - 20800] = atol(val);
        strcpy_P(sscanf_buf, PSTR("%ld"));
        sscanf(val, sscanf_buf, &custom_longs[line - 20800]);
        return 1;
      }

      return 2;
    }

  if (bus->getBusType() == BUS_PPS && line >= 15000 && line < 15000 + PPS_ANZ) { // PPS-Bus set parameter
    int cmd_no = line - 15000;
    switch (decodedTelegram.type) {
      case VT_TEMP: pps_values[cmd_no] = atof(val) * 64; break;
      case VT_HOUR_MINUTES:
      {
        uint8_t h=atoi(val);
        uint8_t m=0;
        while(*val!='\0' && *val!=':' && *val!='.') val++;
        if (*val==':' || *val=='.') {
          val++;
          m=atoi(val);
        }
        pps_values[cmd_no] = h * 6 + m / 10;
        break;
      }
      default: pps_values[cmd_no] = atoi(val); break;
    }
//    if (atof(p) != pps_values[cmd_no] && cmd_no >= PPS_TWS && cmd_no <= PPS_BRS && cmd_no != PPS_RTI) {
/*
    if (cmd_no >= PPS_TWS && cmd_no <= PPS_BRS && cmd_no != PPS_RTI && EEPROM_ready) {
      printFmtToDebug(PSTR("Writing EEPROM slot %d with value %u"), cmd_no, pps_values[cmd_no]);
      writelnToDebug();
      writeToEEPROM(CF_PPS_VALUES);
    }
*/

    uint8_t flags=get_cmdtbl_flags(i);
    if ((flags & FL_EEPROM) == FL_EEPROM && EEPROM_ready) {
      printFmtToDebug(PSTR("Writing EEPROM slot %d with value %u"), cmd_no, pps_values[cmd_no]);
      writelnToDebug();
      writeToEEPROM(CF_PPS_VALUES);
    }

    return 1;
  }

  // Get the parameter type from the table row[i]
  switch(decodedTelegram.type) {
    // ---------------------------------------------
    // No input values sanity check

    // 8-bit representations
    case VT_MONTHS: //(Wartungsintervall)
    case VT_MINUTES_SHORT: // ( Fehler - Alarm)
    case VT_PERCENT:
    case VT_PERCENT1:
    case VT_ENUM:          // enumeration types
    case VT_ONOFF: // 1 = On                      // on = Bit 0 = 1 (i.e. 1=on, 3=on... 0=off, 2=off etc.)
    case VT_CLOSEDOPEN: // 1 = geschlossen
    case VT_YESNO: // 1 = Ja
    case VT_DAYS: // (Legionellenfkt. Periodisch)
    case VT_HOURS_SHORT: // (Zeitkonstante Gebäude)
    case VT_BIT:
    case VT_BYTE:
    case VT_TEMP_SHORT:
    case VT_TEMP_SHORT_US:
    case VT_TEMP_PER_MIN:
    case VT_TEMP_SHORT5_US:
    case VT_TEMP_SHORT5:
    case VT_PERCENT5:
    case VT_TEMP_SHORT64:
    case VT_SECONDS_SHORT4:
    case VT_SECONDS_SHORT5:
    case VT_PRESSURE:
    case VT_GRADIENT_SHORT:
    case VT_LPBADDR:
    case VT_SECONDS_SHORT:
    case VT_VOLTAGE:

    // 16-bit representations
    case VT_UINT:
    case VT_SINT:
    case VT_PERCENT_WORD1:
    case VT_HOURS_WORD: // (Brennerstunden Intervall - nur durch 100 teilbare Werte)
    case VT_MINUTES_WORD: // (Legionellenfunktion Verweildauer)
    case VT_UINT5:
    case VT_UINT10:
    case VT_SECONDS_WORD:
    case VT_TEMP_WORD:
    case VT_CELMIN:
    case VT_PERCENT_100:
    case VT_PERCENT_WORD:
    case VT_FP02:
    case VT_SECONDS_WORD5:
    case VT_TEMP_WORD5_US:
    case VT_GRADIENT:
    case VT_POWER_WORD:
    case VT_MONTHS_WORD:
    case VT_DAYS_WORD:

    // 32-bit representations
    case VT_UINT100:
    case VT_ENERGY:
    case VT_MINUTES:
      {
      uint32_t t = 0;
      if (val[0] == '-') {
        t=((int)(atof(val)*decodedTelegram.operand));
      } else {
        t=atof(val)*decodedTelegram.operand;
      }
      for (int x=decodedTelegram.payload_length;x>0;x--) {
        param[decodedTelegram.payload_length-x+1] = (t >> ((x-1)*8)) & 0xff;
      }
      if (val[0] == '\0' || (decodedTelegram.type == VT_ENUM && t == 0xFFFF)) {
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
      {
      if (val[0]!='\0') {
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
      {
      if (val[0]!='\0') {
        uint8_t h=atoi(val);
        uint8_t m=0;
        while(*val!='\0' && *val!=':' && *val!='.') val++;
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
        param[0]=decodedTelegram.enable_byte;
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
      {
      uint32_t t=((int)(atof(val)*decodedTelegram.operand));
      if (setcmd) {
        param[0]=decodedTelegram.enable_byte;
        param[1]=(t >> 8);
        param[2]= t & 0xff;
      } else { // INF message type
        if((get_cmdtbl_flags(i) & FL_SPECIAL_INF) == FL_SPECIAL_INF) {  // Case for outside temperature
          param[0]=0;
          param[1]=(t >> 8);
          param[2]= t & 0xff;
        } else {  // Case for room temperature
          param[0]=(t >> 8);
          param[1]= t & 0xff;
          param[2]=0x00;
        }
      }
      param_len=3;
      }
      break;

    // ---------------------------------------------
    // Schedule data
    case VT_DATETIME:
      {
      // /S0=dd.mm.yyyy_mm:hh:ss
      int d,m,y,hour,min,sec;
      // The caller MUST provide six values for an event
      strcpy_P(sscanf_buf, PSTR("%d.%d.%d_%d:%d:%d"));
      if(6!=sscanf(val,sscanf_buf,&d,&m,&y,&hour,&min,&sec)) {
        printlnToDebug(PSTR("Too few/many arguments for date/time!"));
        return 0;
      }

      // Send to the PC hardware serial interface (DEBUG)
      printFmtToDebug(PSTR("date time: %d.%d.%d %d:%d:%d\r\n"), d,m,y,hour,min,sec);

      // Set up the command payload
      param[0]=decodedTelegram.enable_byte;
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
      strcpy_P(sscanf_buf, PSTR("%d:%d-%d:%d_%d:%d-%d:%d_%d:%d-%d:%d"));
      ret=sscanf(val,sscanf_buf,&h1s,&m1s,&h1e,&m1e,&h2s,&m2s,&h2e,&m2e,&h3s,&m3s,&h3e,&m3e);
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
      if (val[0]!='\0') {
          int d,m;
          strcpy_P(sscanf_buf, PSTR("%d.%d"));
          if(2!=sscanf(val,sscanf_buf,&d,&m))
            return 0;      // incomplete input data
          param[0]=decodedTelegram.enable_byte;   // flag = enabled
          param[2]=m;
          param[3]=d;
      } else {
          param[0]=decodedTelegram.enable_byte-1;   // flag = disabled
          param[2]=1;
          param[3]=1;
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
      strcpy_P(sscanf_buf, PSTR("%d.%d"));
      if(2!=sscanf(val,sscanf_buf,&d,&m))
        return 0;
      param[0]=decodedTelegram.enable_byte;
      param[1]=0xff;
      param[2]=m;
      param[3]=d;
      param[4]=0xff;
      param[5]=0xff;
      param[6]=0xff;
      param[7]=0xff;
      param[8]=0x16; //?
      param_len=9;
      }
      break;

    case VT_CUSTOM_ENUM:
    {
      uint8_t t=atoi(val);
      bus->Send(TYPE_QUR, c, msg, tx_msg);
      int data_len;
      if (bus->getBusType() == BUS_LPB) {
        data_len=msg[bus->getLen_idx()]-14;     // get packet length, then subtract
      } else {
        data_len=msg[bus->getLen_idx()]-11;     // get packet length, then subtract
      }

      if (data_len > 18) {
        printFmtToDebug(PSTR("Set failed, invalid data length: %d\r\n"), data_len);
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
    case VT_HOURS: // (read only)
    case VT_VOLTAGE: // read only (Ein-/Ausgangstest)
    case VT_LPBADDR: // read only (LPB-System - Aussentemperaturlieferant)
    case VT_PRESSURE_WORD: // read only (Diagnose Verbraucher)
    case VT_FP1: // read only (SW-Version)
    case VT_ERRORCODE: // read only
    case VT_UNKNOWN:
*/
    default:
      printlnToDebug(PSTR("Unknown type or read-only parameter"));
      return 2;
    break;
  } // endswitch

  // Send a message to PC hardware serial port
  printFmtToDebug(PSTR("setting line: %d val: "), line);
  SerialPrintRAW(param,param_len);
  writelnToDebug();

  uint8_t t=setcmd?TYPE_SET:TYPE_INF;

  if((get_cmdtbl_flags(i) & FL_SPECIAL_INF) == FL_SPECIAL_INF) {
    c=((c & 0xFF000000) >> 8) | ((c & 0x00FF0000) << 8) | (c & 0x0000FF00) | (c & 0x000000FF); // because send reverses first two bytes, reverse here already to take care of special inf telegrams that don't reverse first two bytes
  }

  // Send telegram to the bus
  if(!bus->Send(t           // message type
             , c           // command code
             , msg         // receive buffer
             , tx_msg      // xmit buffer
             , param       // payload
             , param_len   // payload length
             , setcmd))    // wait_for_reply
  {
    printFmtToDebug(PSTR("set failed\r\n"));
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
  if (msg[4+(bus->getBusType()*4)]!=TYPE_ACK) {      // msg type at 4 (BSB) or 8 (LPB)
    printlnToDebug(PSTR("set failed NACK"));
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
int queryDefaultValue(int line, byte *msg, byte *tx_msg){
  uint32_t c;
  resetDecodedTelegram();
  if (line < 0){
    decodedTelegram.error = 258; //not found
    return 0;
  }
  int i=findLine(line,0,&c);
  if ( i < 0) {
    decodedTelegram.error = 258; //not found
    return 0;
  } else {
    if (!bus->Send(TYPE_QRV, c, msg, tx_msg)) {
      decodedTelegram.error = 261; //query failed
      return 0;
    } else {
      // Decode the xmit telegram and send it to the debug interface
      if(verbose) {
        printTelegram(tx_msg, line);
#ifdef LOGGER
        LogTelegram(tx_msg);
#endif
      }

      // Decode the rcv telegram and send it to the debug interface
      printTelegram(msg, line);   // send to debug interface
#ifdef LOGGER
      LogTelegram(msg);
#endif
    }
  }
  return 1;
}

const char* printError(uint16_t error){
  const char *errormsgptr;
  switch(error){
    case 0: errormsgptr =  PSTR(""); break;
    case 7: errormsgptr = PSTR(" (parameter not supported)"); break;
    case 256: errormsgptr = PSTR(" - decoding error"); break;
    case 257: errormsgptr =  PSTR(" unknown command"); break;
    case 258: errormsgptr = PSTR(" - not found"); break;
    case 259: errormsgptr = PSTR(" no enum str"); break;
    case 260: errormsgptr = PSTR(" - unknown type"); break;
    case 261: errormsgptr =  PSTR(" query failed"); break;
    default: if(error < 256) errormsgptr = PSTR(" (bus error)"); else errormsgptr = PSTR(" (??? error)"); break;
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
char *build_pvalstr(bool extended){
  int len = 0;
  outBuf[len] = 0;
  if (extended) {
#if !(defined ESP32)
    len+=sprintf_P(outBuf, PSTR("%4ld "), decodedTelegram.prognr);
#else
    len+=sprintf_P(outBuf, PSTR("%4d "), decodedTelegram.prognr);
#endif
    len+=strlen(strcpy_PF(outBuf + len, decodedTelegram.catdescaddr));
    len+=strlen(strcpy_P(outBuf + len, PSTR(" - ")));
    if (decodedTelegram.prognr >= 20050 && decodedTelegram.prognr < 20100) {
      len+=strlen(strcpy_P(outBuf + len, PSTR(STR_24A_TEXT)));
      len+=strlen(strcpy_P(outBuf + len, PSTR(". ")));
    }
    len+=strlen(strcpy_PF(outBuf + len, decodedTelegram.prognrdescaddr));
    if (decodedTelegram.sensorid) {
      len+=sprintf_P(outBuf + len, PSTR(" #%d"), decodedTelegram.sensorid);
    }
    len+=strlen(strcpy_P(outBuf + len, PSTR(": ")));
  }
  if (decodedTelegram.value[0] != 0 && decodedTelegram.error != 260) {
    len+=strlen(strcpy(outBuf + len, decodedTelegram.value));
  }
  if(decodedTelegram.data_type == DT_ENUM || decodedTelegram.data_type == DT_BITS) {
    if (decodedTelegram.enumdescaddr) {
      strcpy_P(outBuf + len, PSTR(" - "));
      strcat_PF(outBuf + len, decodedTelegram.enumdescaddr);
      len+=strlen(outBuf + len);
     }
  } else{
    if (decodedTelegram.unit[0] != 0) {
      strcpy_P(outBuf + len, PSTR(" "));
      strcat(outBuf + len, decodedTelegram.unit);
      len+=strlen(outBuf + len);
    }
  }
  if (decodedTelegram.telegramDump) {
    strcpy_P(outBuf + len, PSTR(" "));
    strcat(outBuf + len, decodedTelegram.telegramDump);
    len+=strlen(outBuf + len);
  }

  strcpy_P(outBuf + len, printError(decodedTelegram.error));
  return outBuf;
}

void query_program_and_print_result(int line, const char* prefix, const char* suffix){
  if(prefix) printToWebClient(prefix);
  query(line);
  printToWebClient_prognrdescaddr();
  if(suffix)
    printToWebClient(suffix);
  else
    printToWebClient(PSTR(": "));
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
void query_printHTML(){
  if (decodedTelegram.msg_type == TYPE_ERR) {
    if (decodedTelegram.error == 7 && !show_unknown) return;
    printToWebClient(PSTR("<tr style='color: #7f7f7f'><td>"));
  } else {
    printToWebClient(PSTR("<tr><td>"));
  }
  printToWebClient(build_pvalstr(1));

  float num_pvalstr = strtod(decodedTelegram.value, NULL);


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
      printToWebClient(PSTR("</td><td>\r\n"));
      if (decodedTelegram.msg_type != TYPE_ERR && decodedTelegram.type != VT_UNKNOWN) {
        if(decodedTelegram.data_type == DT_ENUM || decodedTelegram.data_type == DT_BITS) {
          printToWebClient(PSTR("<select "));
          if (decodedTelegram.data_type == DT_BITS) {
            printToWebClient(PSTR("multiple "));
          }
          printFmtToWebClient(PSTR("id='value%ld'>\r\n"), decodedTelegram.prognr);
          if (decodedTelegram.data_type == DT_BITS) {
            uint16_t val = 0;
            uint16_t c=0;
            uint8_t bitmask=0;
            uint8_t bitvalue = 0;
            for (int i = 0; i < 8; i++){
              if(decodedTelegram.value[i] == '1') bitvalue+=1<<(7-i);
            }
            if (decodedTelegram.type == VT_CUSTOM_BIT) {
              c=1;  // first byte of VT_CUSTOM_BIT enumstr contains index to payload
            }
            while(c<decodedTelegram.enumstr_len){
              if ((byte)(pgm_read_byte_far(decodedTelegram.enumstr+c+2)) == ' ') {         // ENUMs must not contain two consecutive spaces! Necessary because VT_BIT bitmask may be 0x20 which equals space
                val=uint16_t((pgm_read_byte_far(decodedTelegram.enumstr+c) << 8)) | uint16_t(pgm_read_byte_far(decodedTelegram.enumstr+c+1));
                if (decodedTelegram.data_type == DT_BITS) {
                  bitmask = val & 0xff;
                  val = val >> 8 & 0xff;
                }
                c++;
              }
              //skip leading space
              c+=2;
              printToWebClient(STR_OPTION_VALUE);
              printFmtToWebClient(PSTR("%d"), val);
              if ((bitvalue & bitmask) == (val & bitmask)) {
                printToWebClient(STR_SELECTED);
              } else {
                printToWebClient(PSTR("'>"));
              }
              c += printToWebClient(decodedTelegram.enumstr+c);
              printToWebClient(STR_CLOSE_OPTION);
              c++;
            }
          } else {
            if ((decodedTelegram.type == VT_ONOFF || decodedTelegram.type == VT_YESNO|| decodedTelegram.type == VT_CLOSEDOPEN || decodedTelegram.type == VT_VOLTAGEONOFF) && num_pvalstr != 0) {
              num_pvalstr = 1;
            }
            listEnumValues(decodedTelegram.enumstr, decodedTelegram.enumstr_len, STR_OPTION_VALUE, PSTR("'>"), STR_SELECTED, STR_CLOSE_OPTION, NULL, (uint16_t)num_pvalstr, PRINT_VALUE_FIRST, decodedTelegram.type==VT_ENUM?PRINT_DISABLED_VALUE:DO_NOT_PRINT_DISABLED_VALUE);
          }
          printToWebClient(PSTR("</select></td><td>"));
          if (!decodedTelegram.readonly) {
            printToWebClient(PSTR("<input type=button value='Set' onclick=\"set"));
            if (decodedTelegram.type == VT_BIT) {
              printToWebClient(PSTR("bit"));
            }
            printFmtToWebClient(PSTR("(%ld)\">"), decodedTelegram.prognr);
          }
        } else {
          printFmtToWebClient(PSTR("<input type=text id='value%ld' VALUE='"), decodedTelegram.prognr);

/*
          char* colon_pos = strchr(pvalstr,':');
          if (colon_pos!=0) {
            *colon_pos = '.';
          }
*/
/*          if (decodedTelegram.type == VT_HOUR_MINUTES) {
            client.print(decodedTelegram.value);
          } else {
            if  (decodedTelegram.value[2] == '-') {   // do not run strtod on disabled parameters (---)
              printToWebClient(PSTR("---"));
            } else {
              client.print(strtod(decodedTelegram.value, NULL));
            }
          }*/
          printToWebClient(decodedTelegram.value);
          printToWebClient(PSTR("'></td><td>"));
          if (!decodedTelegram.readonly) {
            printFmtToWebClient(PSTR("<input type=button value='Set' onclick=\"set(%ld)\">"), decodedTelegram.prognr);
          }
        }
      }
      printToWebClient(PSTR("</td></tr>"));

// TODO: check at least for data length (only used for temperature values)
/*
int data_len=msg[3]-11;
if (data_len==3) {
  returnval = printFIXPOINT(msg,data_len,64.0,1,"");
}
*/
  flushToWebClient();
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
void queryVirtualPrognr(int line, int table_line){
   loadCategoryDescAddr(); //Get current value from decodedTelegram.cat and load description address to decodedTelegram.catdescaddr
   printFmtToDebug(PSTR("\r\nVirtual parameter %d queried. Table line %d\r\n"), line, table_line);
   decodedTelegram.msg_type = TYPE_ANS;
   decodedTelegram.prognr = line;
   switch(recognizeVirtualFunctionGroup(line)){
     case 1: {
       uint32_t val = 0;
       switch (line) {
         case 20000: val = brenner_duration; break;
         case 20001: val = brenner_count; break;
         case 20002: val = brenner_duration_2; break;
         case 20003: val = brenner_count_2; break;
         case 20004: val = TWW_duration; break;
         case 20005: val = TWW_count; break;
         case 20006: val = 0; break;
       }
#if !defined(ESP32)
       sprintf_P(decodedTelegram.value, PSTR("%ld"), val);
#else
       sprintf_P(decodedTelegram.value, PSTR("%d"), val);
#endif
       return;
     }
     case 2: {
  #ifdef AVERAGES
       size_t tempLine = line - 20050;
       _printFIXPOINT(decodedTelegram.value, avgValues[tempLine], 1);
       return;
   #endif
       break;
     }
     case 3: {
#ifdef DHT_BUS
       size_t tempLine = line - 20100;
       size_t log_sensor = tempLine / 4;
       if (tempLine % 4 == 0) { //print sensor ID
         sprintf_P(decodedTelegram.value, PSTR("%d"), DHT_Pins[log_sensor]);
         return;
       }
       unsigned long temp_timer = millis();
       if(DHT_Timer + 2000 < temp_timer || DHT_Timer > temp_timer)
          last_DHT_pin = 0;

       if(last_DHT_pin != DHT_Pins[log_sensor]) {
         last_DHT_pin = DHT_Pins[log_sensor];
         DHT_Timer = millis();
         last_DHT_State = DHT.read22(last_DHT_pin);
       }
       printFmtToDebug(PSTR("DHT22 sensor: %d\r\n"), last_DHT_pin);
       switch (last_DHT_State) {
         case DHTLIB_OK:
           printToDebug(PSTR("OK,\t"));
           break;
         case DHTLIB_ERROR_CHECKSUM:
           decodedTelegram.error = 256;
           printToDebug(PSTR("Checksum error,\t"));
           break;
         case DHTLIB_ERROR_TIMEOUT:
           decodedTelegram.error = 261;
           printToDebug(PSTR("Time out error,\t"));
          break;
         default:
           decodedTelegram.error = 1;
           printToDebug(PSTR("Unknown error,\t"));
         break;
       }

       float hum = DHT.humidity;
       float temp = DHT.temperature;
       if (hum > 0 && hum < 101) {
         printFmtToDebug(PSTR("#dht_temp[%d]: %.2f, hum[%d]:  %.2f\r\n"), log_sensor, temp, log_sensor, hum);
         switch (tempLine % 4) {
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
       }
       else
         undefinedValueToBuffer(decodedTelegram.value);
       return;
#endif
     break;
     }
     case 4: {
#ifdef ONE_WIRE_BUS
       size_t tempLine = line - 20300;
       int log_sensor = tempLine / 2;
       if (enableOneWireBus && numSensors) {
         switch (tempLine % 2) {
           case 0: //print sensor ID
             DeviceAddress device_address;
             sensors->getAddress(device_address, log_sensor);
             for(uint8_t z = 0; z < 8; z++){
               sprintf_P(&decodedTelegram.value[z*2], PSTR("%02X"), device_address[z]);
             }
//             sprintf_P(decodedTelegram.value, PSTR("%02X%02X%02X%02X%02X%02X%02X%02X"),device_address[0],device_address[1],device_address[2],device_address[3],device_address[4],device_address[5],device_address[6],device_address[7]);
             break;
           case 1: {
             float t=sensors->getTempCByIndex(log_sensor);
             if(t == DEVICE_DISCONNECTED_C) { //device disconnected
               decodedTelegram.error = 261;
               undefinedValueToBuffer(decodedTelegram.value);
               return;
             }
             _printFIXPOINT(decodedTelegram.value, t, 2);
             }
             break;
           default: break;
         }
         return;
       }
  #endif
     break;
     }
     case 5: {
#ifdef MAX_CUL
       size_t tempLine = line - 20500;
       size_t log_sensor = tempLine / 4;
        if (enable_max_cul) {
          if (max_devices[log_sensor]) {
            switch(tempLine % 4){ //print sensor values
              case 0:  //print sensor ID
                strcpy(decodedTelegram.value, max_device_list[log_sensor]);
                break;
              case 1:
                if (max_dst_temp[log_sensor] > 0)
                  sprintf_P(decodedTelegram.value, PSTR("%.2f"), ((float)max_cur_temp[log_sensor] / 10));
                else{
                  decodedTelegram.error = 261;
                  undefinedValueToBuffer(decodedTelegram.value);
                }
                break;
              case 2:
                if (max_dst_temp[log_sensor] > 0)
                  sprintf_P(decodedTelegram.value, PSTR("%.2f"), ((float)max_dst_temp[log_sensor] / 2));
                else{
                  decodedTelegram.error = 261;
                  undefinedValueToBuffer(decodedTelegram.value);
                }
                break;
              case 3:
                if (max_valve[log_sensor] > -1)
                  sprintf_P(decodedTelegram.value, PSTR("%d"), max_valve[log_sensor]);
                else{
                  decodedTelegram.error = 261;
                  undefinedValueToBuffer(decodedTelegram.value);
                }
                break;
            }
            return;
          }
        }
  #endif
      break;
     }
     case 6: {
       sprintf_P(decodedTelegram.value, PSTR("%.2f"), custom_floats[line - 20700]);
       return;
     }
     case 7: {
       sprintf_P(decodedTelegram.value, PSTR("%ld"), custom_longs[line - 20800]);
       return;
     }
     case 8: {
#ifdef BME280
       size_t tempLine = line - 20200;
       size_t log_sensor = tempLine / 6;
       if(tempLine % 6 == 0){
         sprintf_P(decodedTelegram.value, PSTR("%02X"), 0x76 + log_sensor);
         return;
       }
       if(bme[log_sensor].checkID() == 0x60){
         switch(tempLine % 6){
           case 1: _printFIXPOINT(decodedTelegram.value, bme[log_sensor].readTempC(), 2); break;
           case 2: _printFIXPOINT(decodedTelegram.value, bme[log_sensor].readHumidity(), 2); break;
           case 3: _printFIXPOINT(decodedTelegram.value, bme[log_sensor].readPressure(), 2); break;
           case 4: _printFIXPOINT(decodedTelegram.value, bme[log_sensor].readAltitudeMeter(), 2); break;
           case 5: {float temp = bme[log_sensor].readTempC(); _printFIXPOINT(decodedTelegram.value, (216.7*(bme[log_sensor].readHumidity()/100.0*6.112*exp(17.62*temp/(243.12+temp))/(273.15+temp))), 2);} break;
         }
       } else {
         decodedTelegram.error = 261;
         undefinedValueToBuffer(decodedTelegram.value);
       }
       return;
#endif
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
void query(int line)  // line (ProgNr)
{
  byte msg[33] = { 0 };      // response buffer
  byte tx_msg[33] = { 0 };   // xmit buffer
  uint32_t c;        // command code
  int i=0;
  int retry;
  resetDecodedTelegram();

    i=findLine(line,0,&c);

    if (i>=0) {
      loadPrognrElementsFromTable(line, i);

      uint8_t flags = get_cmdtbl_flags(i);

// virtual programs
      if((line >= 20000 && line < 20900))
        {
          queryVirtualPrognr(line, i);
          return;
        }

      //printlnToDebug(PSTR("found"));
      if(c!=CMD_UNKNOWN && (flags & FL_NO_CMD) != FL_NO_CMD) {     // send only valid command codes
        if (bus->getBusType() != BUS_PPS) {  // bus type is not PPS
          retry=QUERY_RETRIES;
          while(retry){
            uint8_t query_type = TYPE_QUR;
            if (bus->Send(query_type, c, msg, tx_msg)) {

              // Decode the xmit telegram and send it to the PC serial interface
              if(verbose) {
                printTelegram(tx_msg, line);
#ifdef LOGGER
                LogTelegram(tx_msg);
#endif
              }

              // Decode the rcv telegram and send it to the PC serial interface
              printTelegram(msg, line);
              printFmtToDebug(PSTR("#%d: "), line);
              printlnToDebug(build_pvalstr(0));
              SerialOutput->flush();
#ifdef LOGGER
              LogTelegram(msg);
#endif
              break;   // success, break out of while loop
            } else {
              printlnToDebug(printError(261)); //query failed
              retry--;          // decrement number of attempts

            }
          } // endwhile, maximum number of retries reached
          if(retry==0) {
            if (bus->getBusType() == BUS_LPB && msg[8] == TYPE_ERR) {    // only for BSB because some LPB systems do not really send proper error messages
              printFmtToDebug(PSTR("error %d\r\n"), msg[9]); //%d
            } else {
              printFmtToDebug(PSTR("%d\r\n"), line); //%d
            }
          decodedTelegram.error = 261;
          }
        } else { // bus type is PPS

          uint32_t cmd = get_cmdtbl_cmd(i);
          uint16_t temp_val = 0;
          switch (decodedTelegram.type) {
//            case VT_TEMP: temp_val = pps_values[(c & 0xFF)] * 64; break:
//            case VT_BYTE: temp_val = pps_values[(line-15000)] * 256; break;
//            case VT_YESNO: temp_val = pps_values[(line-15000)] * 256; decodedTelegram.isswitch = 1; break;
            case VT_ONOFF:
            case VT_YESNO: temp_val = pps_values[(line-15000)]; decodedTelegram.isswitch = 1; break;
//            case VT_HOUR_MINUTES: temp_val = ((pps_values[line-15000] / 6) * 256) + ((pps_values[line-15000] % 6) * 10); break;
//            case VT_HOUR_MINUTES: temp_val = (pps_values[line-15000] / 6) + ((pps_values[line-15000] % 6) * 10); break;
            default: temp_val = pps_values[(line-15000)]; break;
          }

          msg[1] = ((cmd & 0x00FF0000) >> 16);
          msg[4+(bus->getBusType()*4)]=TYPE_ANS;
          msg[bus->getPl_start()]=temp_val >> 8;
          msg[bus->getPl_start()+1]=temp_val & 0xFF;
/*
          msg[5] = c >> 24;
          msg[6] = c >> 16 & 0xFF;
          msg[7] = c >> 8 & 0xFF;
          msg[8] = c & 0xFF;
*/
          printTelegram(msg, line);

          printFmtToDebug(PSTR("#%d: "), line);
          printlnToDebug(build_pvalstr(0));
          SerialOutput->flush();
        }
      } else {
        //printlnToDebug(PSTR("unknown command"));
        //if(line_start==line_end) outBufLen+=sprintf(outBuf+outBufLen,"%d unknown command",line);
      } // endelse, valid / invalid command codes
    } else {
      //printlnToDebug(PSTR("line not found"));
      //if(line_start==line_end) outBufLen+=sprintf(outBuf+outBufLen,"%d line not found",line);
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
void query(int line_start  // begin at this line (ProgNr)
          , int line_end    // end with this line (ProgNr)
          , bool no_print)    // display in web client?
{
  int line;     // ProgNr
   for(line=line_start;line<=line_end;line++){
     query(line);
     if(decodedTelegram.prognr == -1) continue;
     if (!no_print) {         // display in web client?
        query_printHTML();
     }
   } // endfor, for each valid line (ProgNr) command within selected range
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
  if (fixed_device_family < 1) {
    query(6225);
    my_dev_fam = strtod(decodedTelegram.value,NULL);
    query(6226);
    my_dev_var = strtod(decodedTelegram.value,NULL);
  } else {
    my_dev_fam = fixed_device_family;
    my_dev_var = fixed_device_variant;
  }
/*
  int i=0;
  family=pgm_read_byte_far(pgm_get_far_address(dev_tbl[0].dev_family) + i * sizeof(dev_tbl[0]));
  while(family!=DEV_NONE){
    if (family == device_id) {
      known=1;
      break;
    }
    i++;
    family=pgm_read_byte_far(pgm_get_far_address(dev_tbl[0].dev_family) + i * sizeof(dev_tbl[0]));
  }
  if (!known){
    printToDebug(PSTR("Your device family no. "));
    DebugOutput.print(device_id);
    printlnToDebug(PSTR(" is not yet known to BSB-LAN. Certain parameters will be disabled."));
    printlnToDebug(PSTR("Please inform the maintainers of this software about your device family by sending your device family no. as well as the exact name of your heating system, so your system can be added to the list of known systems."));
    dev_id=DEV_ALL;
  } else {
    dev_id=pgm_read_dword_far(pgm_get_far_address(dev_tbl[0].dev_bit_id) + i * sizeof(dev_tbl[0]));
  }
*/
  printFmtToDebug(PSTR("Device family: %d\r\nDevice variant: %d\r\n"), my_dev_fam, my_dev_var);
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
  if (c!=CMD_UNKNOWN) {     // send only valid command codes
    if (bus->Send(TYPE_QUR, c, rx_msg, tx_msg)) {
      if (bus->getBusType() == BUS_LPB) {
        setTime(rx_msg[18], rx_msg[19], rx_msg[20], rx_msg[16], rx_msg[15], rx_msg[14]+1900);
      } else {
        setTime(rx_msg[14], rx_msg[15], rx_msg[16], rx_msg[12], rx_msg[11], rx_msg[10]+1900);
      }
    }
  }
}

void printToWebClient_prognrdescaddr(){
  if (decodedTelegram.prognr >= 20050 && decodedTelegram.prognr < 20100) {
    printToWebClient(PSTR(STR_24A_TEXT));
    printToWebClient(PSTR(". "));
  }
  printToWebClient(decodedTelegram.prognrdescaddr);
  if (decodedTelegram.sensorid) {
    printFmtToWebClient(PSTR(" #%d"), decodedTelegram.sensorid);
  }
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
   int i;
   int counter = 0;
   int numIPWESensors = sizeof(ipwe_parameters) / sizeof(ipwe_parameters[0]);
   printFmtToDebug(PSTR("IPWE sensors: %d\r\n"), numIPWESensors);
   printHTTPheader(HTTP_OK, MIME_TYPE_TEXT_HTML, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_DO_NOT_CACHE);
   printToWebClient(PSTR("\r\n<html><body><form><table border=1><tbody><tr><td>Sensortyp</td><td>Adresse</td><td>Beschreibung</td><td>Wert</td><td>Luftfeuchtigkeit</td><td>Windgeschwindigkeit</td><td>Regenmenge</td></tr>"));
   for (i=0; i < numIPWESensors; i++) {
     if(!ipwe_parameters[i]) continue;
     query(ipwe_parameters[i]);
     counter++;
     printFmtToWebClient(PSTR("<tr><td>T<br></td><td>%d<br></td><td>"), counter);
     printToWebClient_prognrdescaddr();
     printFmtToWebClient(PSTR("<br></td><td>%s&nbsp;%s<br></td>"), decodedTelegram.value, decodedTelegram.unit);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(PSTR("</tr>"));
   }

 #ifdef AVERAGES
   if (logAverageValues) {
     for (int i=0; i<numAverages; i++) {
       if (avg_parameters[i] > 0) {
         counter++;
         query(20050 + i);
         printFmtToWebClient(PSTR("<tr><td>T<br></td><td>%d"), counter);
         printToWebClient(PSTR("<br></td><td>"));
         printToWebClient_prognrdescaddr();
         printFmtToWebClient(PSTR("<br></td><td>%s&nbsp;%s<br></td>"), decodedTelegram.value, decodedTelegram.unit);
         printToWebClient(STR_IPWEZERO);
         printToWebClient(STR_IPWEZERO);
         printToWebClient(STR_IPWEZERO);
         printToWebClient(PSTR("</tr>"));
       }
     }
   }
 #endif

 #ifdef ONE_WIRE_BUS
   if (enableOneWireBus) {
     // output of one wire sensors
     for(i=0;i<numSensors * 2;i += 2){
       printFmtToWebClient(PSTR("<tr><td>T<br></td><td>%d<br></td><td>"), counter);
       query(i + 20300);
       printToWebClient(decodedTelegram.value);
       query(i + 20301);
       printFmtToWebClient(PSTR("<br></td><td>%s<br></td>"), decodedTelegram.value);
       printToWebClient(STR_IPWEZERO);
       printToWebClient(STR_IPWEZERO);
       printToWebClient(STR_IPWEZERO);
       printToWebClient(PSTR("</tr>"));
     }
   }
 #endif

 #ifdef DHT_BUS
   // output of DHT sensors
   int numDHTSensors = sizeof(DHT_Pins) / sizeof(DHT_Pins[0]);
   for(i=0;i<numDHTSensors;i++){
     if(!DHT_Pins[i]) continue;
     query(20101 + i * 4);
     counter++;
     printFmtToWebClient(PSTR("<tr><td>T<br></td><td>%d<br></td><td>"), counter);
     printFmtToWebClient(PSTR("DHT sensor %d temperature"), DHT_Pins[i]);
     printFmtToWebClient(PSTR("<br></td><td>%s<br></td>"), decodedTelegram.value);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(PSTR("</tr>"));
     counter++;
     query(20102 + i * 4);
     printFmtToWebClient(PSTR("<tr><td>F<br></td><td>%d<br></td><td>"), counter);
     printFmtToWebClient(PSTR("DHT sensor %d humidity<br></td>"), DHT_Pins[i]);
     printToWebClient(STR_IPWEZERO);
     printFmtToWebClient(PSTR("<td>%s<br></td>"), decodedTelegram.value);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(PSTR("</tr>"));
   }
 #endif

   printToWebClient(PSTR("</tbody></table></form></body></html>\r\n\r\n"));
   forcedflushToWebClient();
 }

 #endif    // --- Ipwe() ---

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
    if (logCurrentValues) {
      for (int i=0; i < numLogValues; i++) {
        if (log_parameters[i] == 15000 + pps_index) {
          log_parameter = log_parameters[i];
        }
      }
    }
    pps_values[pps_index] = value;
  }
  return log_parameter;
}

#if defined LOGGER || defined WEBSERVER
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
  flushToWebClient();
  int chars_read = dataFile.read(bigBuff , logbuflen);
  while (chars_read == logbuflen) {
    client.write(bigBuff, logbuflen);
    chars_read = dataFile.read(bigBuff , logbuflen);
    }
  if (chars_read > 0) client.write(bigBuff, chars_read);
}

#endif

/** *****************************************************************
 *  Function: resetBoard
 *  Does: restart Arduino
 *  Pass parameters:
 *   none
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   none
 * *************************************************************** */
void resetBoard(){
  forcedflushToWebClient();
  delay(10);
  client.stop();
  delay(300);
#if defined(__SAM3X8E__)
// Reset function from https://forum.arduino.cc/index.php?topic=345209.0
  rstc_start_software_reset(RSTC);
  while (1==1) {}
#elif defined(__AVR__)
  asm volatile ("  jmp 0");
  while (1==1) {}
#elif defined(ESP32)
  ESP.restart();
#else
  printlnToDebug(PSTR("Reset function not implementing"));
#endif

}

#ifdef AVERAGES
void resetAverageCalculation(){
  for (int i=0;i<numAverages;i++) {
    avg_parameters[i] = 0;
    avgValues[i] = 0;
    avgValues_Old[i] = -9999;
    avgValues_Current[i] = 0;
  }
  avgCounter = 1;
  #ifdef LOGGER
  SD.remove(averagesFileName);
  #endif
}
#endif


#ifdef LOGGER
bool createdatalogFileAndWriteHeader(){
  File dataFile = SD.open(datalogFileName, FILE_WRITE);
  if (dataFile) {
    strcpy_P(outBuf, PSTR("Milliseconds;Date;Parameter;Description;Value;Unit"));
    dataFile.println(outBuf);
    dataFile.close();
    outBuf[0] = 0;
    return true;
  }
  return false;
}
#endif

#ifdef MAX_CUL
void connectToMaxCul() {
  if (max_cul) {
    max_cul->stop();
    delete max_cul;
    max_cul = NULL;
    if(!enable_max_cul) return;
  }

  max_cul = new ComClient();
  printToDebug(PSTR("Connection to max_cul: "));
  if (max_cul->connect(IPAddress(max_cul_ip_addr[0], max_cul_ip_addr[1], max_cul_ip_addr[2], max_cul_ip_addr[3]), 2323)) {
    printlnToDebug(PSTR("established"));
  } else {
    printlnToDebug(PSTR("failed"));
  }
}
#endif

void clearEEPROM(void){
  printlnToDebug(PSTR("Clearing EEPROM..."));
#if defined(__AVR__)
  for (uint16_t x=0; x<EEPROM.length(); x++) {
    EEPROM.write(x, 0xFF);
  }
#else
  uint8_t empty_block[4097] = { 0xFF };
  EEPROM.fastBlockWrite(0, &empty_block, 4096);
#endif
  printlnToDebug(PSTR("Cleared EEPROM"));
}

void internalLEDBlinking(uint16_t period, uint16_t count){
  for (uint16_t i=0; i<count; i++) {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(period);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(period);
  }
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
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
  char c = '\0';
  const byte MaxArrayElement=252;
  char  cLineBuffer[MaxArrayElement];  //
  byte  bPlaceInBuffer;                // index into buffer
  uint16_t log_now = 0;

#ifndef WIFI
 if (ip_addr[0] == 0 || useDHCP) {
    switch (Ethernet.maintain()) {
      case 1:
        //renewed fail
        printlnToDebug(PSTR("Error: renewed fail"));
        break;
      case 2:
        //renewed success
        printlnToDebug(PSTR("Renewed success"));
        //print your local IP address:
        printToDebug(PSTR("My IP address: "));
        {IPAddress t = Ethernet.localIP();
        printFmtToDebug(PSTR("%d.%d.%d.%d\r\n"), t[0], t[1], t[2], t[3]);}
        break;
      case 3:
        //rebind fail
        printlnToDebug(PSTR("Error: rebind fail"));
        break;
      case 4:
        //rebind success
        printlnToDebug(PSTR("Rebind success"));
        //print your local IP address:
        printToDebug(PSTR("My IP address: "));
        {IPAddress t = Ethernet.localIP();
        printFmtToDebug(PSTR("%d.%d.%d.%d\r\n"), t[0], t[1], t[2], t[3]);}
      break;

      default:
        //nothing happened
        break;
    }
  }
#endif

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
      if(verbose && bus->getBusType() != BUS_PPS && !monitor) {  // verbose output for PPS comes later
        printTelegram(msg, -1);
        LogTelegram(msg);
      }
      // Is this a broadcast message?
      if (((msg[2]==ADDR_ALL && bus->getBusType()==BUS_BSB) || (msg[2]>=0xF0 && bus->getBusType()==BUS_LPB)) && msg[4+(bus->getBusType()*4)]==TYPE_INF) { // handle broadcast messages
      // Decode the rcv telegram and send it to the PC serial interface
        if (!verbose && !monitor) {        // don't log twice if in verbose mode, but log broadcast messages also in non-verbose mode
          printTelegram(msg, -1);
          LogTelegram(msg);
        }

        // Filter Brenner Status messages

        uint32_t cmd;
        cmd=(uint32_t)msg[5+(bus->getBusType()*4)]<<24 | (uint32_t)msg[6+(bus->getBusType()*4)]<<16 | (uint32_t)msg[7+(bus->getBusType()*4)] << 8 | (uint32_t)msg[8+(bus->getBusType()*4)];
        if(cmd==0x0500006C) {   // set Time from BC, same CommandID for BSB and LPB
          setTime(msg[bus->getPl_start()+5], msg[bus->getPl_start()+6], msg[bus->getPl_start()+7], msg[bus->getPl_start()+3], msg[bus->getPl_start()+2], msg[bus->getPl_start()+1]+1900);
        }

        if(cmd==0x31000212) {    // TWW Status
          printFmtToDebug(PSTR("INF: TWW-Status: %d\r\n"), msg[11]);

          if((msg[11] & 0x08) == 0x08) {  // See parameter 1602
            if (TWW_start==0) {        // has not been timed
              TWW_start=millis();   // keep current timestamp
              TWW_count++;          // increment number of starts
            }
          } else {             // TWW Ladung aus
            if (TWW_start!=0) {        // start has been timed
              unsigned long TWW_end;
              TWW_end=millis();      // timestamp the end
              if (TWW_end >= TWW_start) {
                TWW_duration+=(TWW_end-TWW_start)/1000;
              } else { // overflow
                TWW_duration+=(0xffffffff-TWW_start+TWW_end)/1000;
              }
                TWW_start=0;
            } // endif, a previous start has been timed
          } // endif, TWW is off
        } // endif, Status TWW command code

        if(cmd==0x05000213) {     // Brennerstatus; CommandID 0x053d0f66 was suggested at some point as well, but so far has not been identified in one of the heating systems
          unsigned long brenner_end;
          bool reset_brenner_timer = 0;
          printFmtToDebug(PSTR("INF: Brennerstatus: %d\r\n"), msg[bus->getPl_start()]);      // first payload byte

          if((msg[bus->getPl_start()] & 0x04) == 0x04) {       // Stufe 1
            if (brenner_start==0) {        // has not been timed
              brenner_start=millis();   // keep current timestamp
              brenner_count++;          // increment number of starts
            }
            if (brenner_stufe == 2) {
              reset_brenner_timer = 1;
            }
            brenner_stufe=1;
          }
          if((msg[bus->getPl_start()] & 0x10) == 0x10) {       // Stufe 2 (only oil furnace)
            if (brenner_start_2==0) {        // has not been timed
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
              if (brenner_end >= brenner_start) {
                brenner_duration+=(brenner_end-brenner_start)/1000;
              } else { // overflow
                brenner_duration+=(0xffffffff-brenner_start+brenner_end)/1000;
              }
              brenner_start=0;
            }
            if (brenner_stufe == 1) {   // Stufe jetzt 1, war also vorher 2
              if (brenner_end >= brenner_start_2) {
                brenner_duration_2+=(brenner_end-brenner_start_2)/1000;
              } else { // overflow
                brenner_duration_2+=(0xffffffff-brenner_start_2+brenner_end)/1000;
              }
              brenner_start_2=0;
            }
            reset_brenner_timer = 0;
          }
          if ((msg[bus->getPl_start()] & 0x04) != 0x04) {    // brenner off
            brenner_end=millis();      // timestamp the end
            brenner_stufe=0;
            if (brenner_start!=0) {        // start has been timed
              if (brenner_end >= brenner_start) {
                brenner_duration+=(brenner_end-brenner_start)/1000;
              } else { // overflow
                brenner_duration+=(0xffffffff-brenner_start+brenner_end)/1000;
              }
              brenner_start=0;
            } // endif, a previous start has been timed
            if (brenner_start_2!=0) {        // start has been timed
              if (brenner_end >= brenner_start_2) {
                brenner_duration_2+=(brenner_end-brenner_start_2)/1000;
              } else { // overflow
                brenner_duration_2+=(0xffffffff-brenner_start_2+brenner_end)/1000;
              }
              brenner_start_2=0;
            } // endif, a previous start has been timed
          } // endif, brenner is off
        } // endif, Status Brenner command code
      } // endif, broadcasts

// PPS-Bus handling
      if (bus->getBusType() == BUS_PPS) {
        if (msg[0] == 0x17 && pps_write == 1) { // Send client data
          byte tx_msg[] = {0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
          byte rx_msg[10] = { 0 };
          switch (msg_cycle) {
            case 0:
              tx_msg[1] = 0x38; // Typ
              if (pps_values[PPS_QTP] == 0) pps_values[PPS_QTP] = QAA_TYPE;
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
                bool found = false;
                bool next_active = true;
                int16_t current_time = hour() * 6 + minute() / 10;
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
                break;
              } else {
                msg_cycle++;  // If time is not yet set, above code is not executed, but following case will. Increase msg_cycle so that it is not run a second time in the next iteration.
              }
            }
//            break;
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
            {
              tx_msg[0] = 0xFB; // send time to heater
              tx_msg[1] = 0x79;
              tx_msg[4] = (weekday()>1?weekday()-1:7); // day of week
              tx_msg[5] = hour(); // hour
              tx_msg[6] = minute(); // minute
              tx_msg[7] = second(); // second
              break;
            }
            case 14:
            {
              tx_msg[0] = 0xFE; // unknown telegram
              tx_msg[1] = 0x79;
              break;
            }
            case 15:
              tx_msg[1] = 0x60;
              tx_msg[2] = pps_values[PPS_E13];
              tx_msg[3] = pps_values[PPS_S13];
              tx_msg[4] = pps_values[PPS_E12];
              tx_msg[5] = pps_values[PPS_S12];
              tx_msg[6] = pps_values[PPS_E11];
              tx_msg[7] = pps_values[PPS_S11];
              break;
            case 16:
              tx_msg[1] = 0x61;
              tx_msg[2] = pps_values[PPS_E23];
              tx_msg[3] = pps_values[PPS_S23];
              tx_msg[4] = pps_values[PPS_E22];
              tx_msg[5] = pps_values[PPS_S22];
              tx_msg[6] = pps_values[PPS_E21];
              tx_msg[7] = pps_values[PPS_S21];
              break;
            case 17:
              tx_msg[1] = 0x62;
              tx_msg[2] = pps_values[PPS_E33];
              tx_msg[3] = pps_values[PPS_S33];
              tx_msg[4] = pps_values[PPS_E32];
              tx_msg[5] = pps_values[PPS_S32];
              tx_msg[6] = pps_values[PPS_E31];
              tx_msg[7] = pps_values[PPS_S31];
              break;
            case 18:
              tx_msg[1] = 0x63;
              tx_msg[2] = pps_values[PPS_E43];
              tx_msg[3] = pps_values[PPS_S43];
              tx_msg[4] = pps_values[PPS_E42];
              tx_msg[5] = pps_values[PPS_S42];
              tx_msg[6] = pps_values[PPS_E41];
              tx_msg[7] = pps_values[PPS_S41];
              break;
            case 19:
              tx_msg[1] = 0x64;
              tx_msg[2] = pps_values[PPS_E53];
              tx_msg[3] = pps_values[PPS_S53];
              tx_msg[4] = pps_values[PPS_E52];
              tx_msg[5] = pps_values[PPS_S52];
              tx_msg[6] = pps_values[PPS_E51];
              tx_msg[7] = pps_values[PPS_S51];
              break;
            case 20:
              tx_msg[1] = 0x65;
              tx_msg[2] = pps_values[PPS_E63];
              tx_msg[3] = pps_values[PPS_S63];
              tx_msg[4] = pps_values[PPS_E62];
              tx_msg[5] = pps_values[PPS_S62];
              tx_msg[6] = pps_values[PPS_E61];
              tx_msg[7] = pps_values[PPS_S61];
              break;
            case 21:
              tx_msg[1] = 0x66;
              tx_msg[2] = pps_values[PPS_E73];
              tx_msg[3] = pps_values[PPS_S73];
              tx_msg[4] = pps_values[PPS_E72];
              tx_msg[5] = pps_values[PPS_S72];
              tx_msg[6] = pps_values[PPS_E71];
              tx_msg[7] = pps_values[PPS_S71];
              break;
            case 22:
              tx_msg[1] = 0x7C;
              tx_msg[7] = pps_values[PPS_FDT];     // Verbleibende Feriendauer in Tagen
              break;
            case 23:
              tx_msg[1] = 0x1B;                    // Frostschutz- und Maximaltemperatur
              tx_msg[4] = pps_values[PPS_SMX] >> 8;
              tx_msg[5] = pps_values[PPS_SMX] & 0xFF;
              tx_msg[6] = pps_values[PPS_FRS] >> 8;
              tx_msg[7] = pps_values[PPS_FRS] & 0xFF;
          }
          msg_cycle++;
          if (msg_cycle > 23) {
            msg_cycle = 0;
          }
          if (saved_msg_cycle > 0) {
            msg_cycle = saved_msg_cycle;
            saved_msg_cycle = 0;
          }
          if (tx_msg[1] != 0xFF &&  pps_write == 1) {
            bus->Send(0, 0, rx_msg, tx_msg);
          }

          if(verbose) {     // verbose output for PPS after time-critical sending procedure
            if (!monitor) {
              printTelegram(msg, -1);
            } else {
              printFmtToDebug(PSTR("%lu "), millis());
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
              case 0x38: msg_cycle = 0; break;
              case 0x48: msg_cycle = 1; break;
              case 0x49: msg_cycle = 5; break;
              case 0x4C: msg_cycle = 11; break;
              case 0x4D: msg_cycle = 2; break;
              case 0x4F: msg_cycle = 3; break;
              case 0x60: msg_cycle = 15; break;
              case 0x61: msg_cycle = 16; break;
              case 0x62: msg_cycle = 17; break;
              case 0x63: msg_cycle = 18; break;
              case 0x64: msg_cycle = 19; break;
              case 0x65: msg_cycle = 20; break;
              case 0x66: msg_cycle = 21; break;
              case 0x7C: msg_cycle = 22; break;
              default:
                 printToDebug(PSTR("Unknown request: "));
                for (int c=0;c<9;c++) {
                  printFmtToDebug(PSTR("%02X "), msg[c]);
                }
                writelnToDebug();
#ifdef LOGGER
/*
                File dataFile = SD.open(journalFileName, FILE_WRITE);
                if (dataFile) {
                  int outBufLen = 0;
                  outBufLen += sprintf_P(outBuf + outBufLen, PSTR("%lu;%s;Unknown PPS telegram;"), millis(), GetDateTime(outBuf + outBufLen + 80));
                  for(int i=0;i<9+(pps_write!=1 && msg[0] == 0x17);i++){
                    outBufLen += sprintf_P(outBuf + outBufLen, PSTR("%02X "), msg[i]);
                  }
                  outBuf[--outBufLen] = 0;
                  dataFile.println(outBuf);
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

//            uint8_t pps_offset = (msg[0] == 0x17 && pps_write != 1);
uint8_t pps_offset = 0;
//            uint16_t temp = (msg[6+pps_offset] << 8) + msg[7+pps_offset];
            uint16_t temp = (msg[6] << 8) + msg[7];
            uint16_t i = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) + sizeof(cmdtbl2)/sizeof(cmdtbl2[0]) + sizeof(cmdtbl3)/sizeof(cmdtbl3[0]) - 1;
            while (i > 0 && get_cmdtbl_line(i) >= 15000) {
              uint32_t cmd = get_cmdtbl_cmd(i);
              cmd = (cmd & 0x00FF0000) >> 16;
//              if (cmd == msg[1+pps_offset]) {
              if (cmd == msg[1]) {
                break;
              }
              i--;
            }
            uint8_t flags=get_cmdtbl_flags(i);
            if (programIsreadOnly(flags) || pps_write != 1) {
              switch (msg[1+pps_offset]) {
                case 0x4F: log_now = setPPS(PPS_CON, msg[7+pps_offset]); saved_msg_cycle = msg_cycle; msg_cycle = 0; break;  // Gerät an der Therme angemeldet? 0 = ja, 1 = nein

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
//                case 0x4A: pps_values[PPS_KVT] = temp; break; // Vorlauftemperatur, to be confirmed
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
                case 0x79: pps_values[PPS_DOW] = msg[4+pps_offset]; setTime(msg[5+pps_offset], msg[6+pps_offset], msg[7+pps_offset], msg[4+pps_offset], 1, 2018); time_set = true; break;  // Datum (msg[4] Wochentag)
                case 0x7C: pps_values[PPS_FDT] = temp & 0xFF; // Verbleibende Ferientage
                case 0x48: log_now = setPPS(PPS_HP, msg[7+pps_offset]); break;   // Heizprogramm manuell/automatisch (0 = Auto, 1 = Manuell)
                case 0x1B:                                    // Frostschutz-Temperatur
                  pps_values[PPS_FRS] = temp;
                  pps_values[PPS_SMX] = (msg[4+pps_offset] << 8) + msg[5+pps_offset];
                  break;
                case 0x00: break;
                default:
                  printToDebug(PSTR("Unknown telegram: "));
                  for (int c=0;c<9+pps_offset;c++) {
                    printFmtToDebug(PSTR("%02X "), msg[c]);
                  }
                  writelnToDebug();
                  break;
              }
            }

/*
            printToDebug(PSTR("Outside Temperature: "));
            DebugOutput.println(outside_temp);
            printToDebug(PSTR("Boiler Temperature: "));
            DebugOutput.println(boiler_temp);
            printToDebug(PSTR("Mixer Flow Temperature: "));
            DebugOutput.println(mixer_flow_temp);
            printToDebug(PSTR("Flow Temperature: "));
            DebugOutput.println(flow_temp);
            printToDebug(PSTR("Weighted Temperature: "));
            DebugOutput.println(weighted_temp);
            printToDebug(PSTR("Boiler active: "));
            if (boiler_active) {
              printlnToDebug(PSTR("yes"));
            } else {
              printlnToDebug(PSTR("no"));
            }
            printToDebug(PSTR("Time: ")); DebugOutput.print(d); DebugOutput.print(", "); DebugOutput.print(h); DebugOutput.print(":"); DebugOutput.print(m); DebugOutput.print(":"); DebugOutput.println(s);
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
  client = server->available();
  if (client || SerialOutput->available()) {
    IPAddress remoteIP = client.remoteIP();
    // Use the overriden operater for a safe comparison, note, that != is not overriden.
    if(   (trusted_ip_addr[0] != 0 && ! (remoteIP == trusted_ip_addr))
       && (trusted_ip_addr2[0] != 0 && ! (remoteIP == trusted_ip_addr2))) {
          // reject clients from unauthorized IP addresses;
      printFmtToDebug(PSTR("Rejected access from %d.%d.%d.%d (Trusted 1: %d.%d.%d.%d, Trusted 2: %d.%d.%d.%d.\r\n"),
        remoteIP[0], remoteIP[1], remoteIP[2], remoteIP[3],
        trusted_ip_addr[0], trusted_ip_addr[1], trusted_ip_addr[2], trusted_ip_addr[3],
        trusted_ip_addr2[0], trusted_ip_addr2[1], trusted_ip_addr2[2], trusted_ip_addr2[3]);
      client.stop();
    }

    loopCount = 0;
   // Read characters from client and assemble them in cLineBuffer
    bPlaceInBuffer=0;            // index into cLineBuffer
    while (client.connected() || SerialOutput->available()) {
      if (client.available() || SerialOutput->available()) {
        loopCount = 0;
        if (client.available()) {
          c = client.read();       // read one character
          printFmtToDebug(PSTR("%c"), c);         // and send it to hardware UART
        }
        if (SerialOutput->available()) {
          c = SerialOutput->read();
          printFmtToDebug(PSTR("%c"), c);         // and send it to hardware UART
          int timeout = 0;
          while (SerialOutput->available() == 0 && c!='\r' && c!='\n') {
            delay(1);
            timeout++;
            if (timeout > 2000) {
              printlnToDebug(PSTR("Serial input timeout"));
              break;
            }
          }
        }

        if ((c!='\n') && (c!='\r') && (bPlaceInBuffer<MaxArrayElement)){
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
#ifdef WEBSERVER
              //Execute only if flag not set because strstr more expensive than bitwise operation
              if (!(httpflags & HTTP_GZIP) && strstr_P(outBuf + buffershift,PSTR("Accept-Encoding")) != 0 && strstr_P(outBuf+16 + buffershift, PSTR("gzip")) != 0) {
                httpflags |= HTTP_GZIP;
              }
#endif
              if (!(httpflags & HTTP_ETAG)) {
                char *ptr = strstr_P(outBuf + buffershift, PSTR("If-None-Match:"));
                if (ptr != 0) {
                  httpflags |= HTTP_ETAG;
                  ptr = strchr(ptr, ':');
                  do{
                    ptr++;
                  } while (ptr[0] == ' ');
                  strcpy(outBuf, ptr); //Copy ETag to buffer. Note: '\r\n' present at end
//                  printFmtToDebug(PSTR("ETag string: %s\r\n"), outBuf);
                }
              }
              //Execute only if flag not set because strstr more expensive than bitwise operation
              if (!(httpflags & HTTP_AUTH) && USER_PASS_B64[0] && strstr_P(outBuf + buffershift,PSTR("Authorization: Basic"))!=0 && strstr(outBuf + buffershift,USER_PASS_B64)!=0) {
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
        // if no credentials found in HTTP header, send 401 Authorization Required
        if (USER_PASS_B64[0] && !(httpflags & HTTP_AUTH)) {
          printHTTPheader(HTTP_AUTH_REQUIRED, MIME_TYPE_TEXT_HTML, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_DO_NOT_CACHE);
#if defined(__AVR__)
          printPStr(pgm_get_far_address(auth_req_html), sizeof(auth_req_html));
#else
          printPStr(auth_req_html, sizeof(auth_req_html));
#endif
          forcedflushToWebClient();
          client.stop();
          break;
        }
        // otherwise continue like normal
        // Flush any remaining bytes from the client buffer
//        client.flush();
        // GET / HTTP/1.1 (anforderung website)
        // GET /710 HTTP/1.0 (befehlseingabe)
#ifdef WEBSERVER
        // Check for HEAD request (for file caching)
        if(!strncmp_P(cLineBuffer, PSTR("HEAD"), 4))
          httpflags |= HTTP_HEAD_REQ;
#endif
        char *u_s = strchr(cLineBuffer,' ');
        char *u_e = strchr(u_s + 1,' ');
        if(u_e) u_e[0] = 0;
        strcpy(cLineBuffer, u_s + 1);
        printlnToDebug(cLineBuffer);
// IPWE START
#ifdef IPWE
        if (enable_ipwe && !strcmp_P(cLineBuffer, PSTR("/ipwe.cgi"))) {
          Ipwe();
          break;
        }
#endif
// IPWE END

        if (!strcmp_P(cLineBuffer, PSTR("/favicon.ico"))) {
          printHTTPheader(HTTP_OK, MIME_TYPE_IMAGE_ICON, HTTP_DO_NOT_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_AUTO_CACHE_AGE);
          printToWebClient(PSTR("\r\n"));
#ifdef WEBSERVER
          File dataFile = SD.open(cLineBuffer + 1);
          if (dataFile) {
            flushToWebClient();
            transmitFile(dataFile);
            dataFile.close();
          } else {
#endif
#if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
#if defined(__AVR__)
            printPStr(pgm_get_far_address(favicon), sizeof(favicon));
#else
            printPStr(favicon, sizeof(favicon));
#endif
#endif
            flushToWebClient();
#ifdef WEBSERVER
            }
#endif
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
            printlnToDebug(PSTR("no matching passkey"));
            client.flush();
            client.stop();
            //do not print header and footer. It is security breach
            break;
          }
          *p='/';
        }

#ifdef WEBSERVER
        printToDebug(PSTR("URL: "));
        if (!strcmp_P(p, PSTR("/"))) {
          httpflags |= HTTP_GET_ROOT;
          strcpy_P(p + 1, PSTR("index.html"));
        }
          printlnToDebug(p);
        char *dot = strchr(p, '.');
        char *dot_t = NULL;
        while(dot){
          dot_t = ++dot;//next symbol after dot
          dot = strchr(dot, '.');
        }
        dot = dot_t;

        int mimetype = recognize_mime(dot); //0 = unknown MIME type

        if(mimetype)  {
          File dataFile;
          const char *getfarstrings;

          // client browser accept gzip
          int suffix = 0;
          if ((httpflags & HTTP_GZIP)) {
            suffix = strlen(p);
            strcpy_P(p + suffix, PSTR(".gz"));
            dataFile = SD.open(p);
          }
          if (!dataFile) {
            // reuse httpflags
            if(suffix) p[suffix] = 0;
            httpflags &= ~HTTP_GZIP; //can't use gzip because no gzipped file
            dataFile = SD.open(p);
          }
          // if the file is available, read from it:
          if (dataFile) {
            dir_t d;
            uint16_t lastWrtYr = 0;
            byte monthval = 0;
            byte dayval = 0;
            unsigned long filesize = dataFile.size();
            if (dataFile.dirEntry(&d)) {
              lastWrtYr = FAT_YEAR(d.lastWriteDate);
              monthval = FAT_MONTH(d.lastWriteDate);
              dayval = FAT_DAY(d.lastWriteDate);
              }

            if ((httpflags & HTTP_ETAG))  { //Compare ETag if presented
              if (memcmp(outBuf, outBuf + buffershift, sprintf_P(outBuf + buffershift, PSTR("\"%02d%02d%d%02d%02d%02d%lu\""), dayval, monthval, lastWrtYr, FAT_HOUR(d.lastWriteTime), FAT_MINUTE(d.lastWriteTime), FAT_SECOND(d.lastWriteTime), filesize))) {
                // reuse httpflags
                httpflags &= ~HTTP_ETAG; //ETag not match
              }
            }

            printToDebug(PSTR("File opened from SD: "));
            printlnToDebug(p);

            uint16_t code = 0;
            if((httpflags & HTTP_ETAG))
              code = HTTP_NOT_MODIFIED;
            else
              code = HTTP_OK;
            printHTTPheader(code, mimetype, HTTP_DO_NOT_ADD_CHARSET_TO_HEADER, (httpflags & HTTP_GZIP), HTTP_AUTO_CACHE_AGE);
            if (lastWrtYr) {
              char monthname[4];
              char downame[4];
              uint8_t dowval =  dayofweek((uint8_t)dayval, (uint8_t)monthval, lastWrtYr);
              if(dowval < 1 && dowval > 7) dowval = 8;
              memcpy_P(downame, PSTR("MonTueWedThuFriSatSunERR") + dowval * 3 - 3, 3);
              downame[3] = 0;

              if(monthval < 1 && monthval > 12) monthval = 13;
              memcpy_P(monthname, PSTR("JanFebMarAprMayJunJulAugSepOctNovDecERR") + monthval * 3 - 3, 3);
              monthname[3] = 0;
              printFmtToWebClient(PSTR("Last-Modified: %s, %02d %s %d %02d:%02d:%02d GMT\r\n"), downame, dayval, monthname, lastWrtYr, FAT_HOUR(d.lastWriteTime), FAT_MINUTE(d.lastWriteTime), FAT_SECOND(d.lastWriteTime));
            }
            //max-age=84400 = one day, max-age=2592000 = 30 days. Last string in header, double \r\n
            printFmtToWebClient(PSTR("ETag: \"%02d%02d%d%02d%02d%02d%lu\"\r\nContent-Length: %lu\r\n\r\n"), dayval, monthval, lastWrtYr, FAT_HOUR(d.lastWriteTime), FAT_MINUTE(d.lastWriteTime), FAT_SECOND(d.lastWriteTime), filesize, filesize);
            flushToWebClient();
            //Send file if !HEAD request received or ETag not match
            if (!(httpflags & HTTP_ETAG) && !(httpflags & HTTP_HEAD_REQ)) {
              transmitFile(dataFile);
            }
            printToDebug((httpflags & HTTP_HEAD_REQ)?PSTR("HEAD"):PSTR("GET")); printlnToDebug(PSTR(" request received"));

            dataFile.close();
          } else {
#if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
          // simply print the website if no index.html on SD card
            if ((httpflags & HTTP_GET_ROOT)) {
              webPrintSite();
              break;
            }
#endif
            printHTTPheader(HTTP_NOT_FOUND, MIME_TYPE_TEXT_HTML, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_DO_NOT_CACHE);
            printToWebClient(PSTR("\r\n<h2>File not found!</h2><br>File name: "));
            printToWebClient(p);
            flushToWebClient();
          }
          client.flush();
          break;
        }
#endif
        if (p[1] != 'J' && p[1] != 'C') {
          while (client.available()) client.read();
        } else {
          if ((httpflags & HTTP_ETAG))  { //Compare ETag if presented
            strcpy_P(outBuf + buffershift, PSTR("\""));
            strcat_P(outBuf + buffershift, BSB_VERSION);
            strcat_P(outBuf + buffershift, PSTR("\""));
            if (memcmp(outBuf, outBuf + buffershift, strlen(outBuf + buffershift))) {
              // reuse httpflags
              httpflags &= ~HTTP_ETAG; //ETag not match
            }
          }
        }
#ifndef WEBSERVER
#if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
        // simply print the website
        if (!strcmp_P(p, PSTR("/"))) {
          webPrintSite();
          break;
        }
#else
#endif
#endif

        // Answer to unknown requests
#if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
        if (!isdigit(p[1]) && strchr_P(PSTR("ABCDEGIJKLMNPQRSUVWXY"), p[1])==NULL) {
#else
        if (!isdigit(p[1]) && strchr_P(PSTR("CDGJNQUWX"), p[1])==NULL) {
#endif
          webPrintHeader();
          webPrintFooter();
          break;
        }

#ifdef WEBSERVER
        //Send HTML pages without header and footer (For external interface)
        if (p[1]=='W') {
          p++;
          httpflags |= HTTP_FRAG;
        }
#endif

#if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
        // setting verbosity level
        if (p[1]=='V') {
          p+=2;
          verbose=atoi(p);
          webPrintHeader();
          if (verbose>0) {
            printToWebClient(PSTR(MENU_TEXT_VB1 "<BR>"));
          } else {
            printToWebClient(PSTR(MENU_TEXT_VB2 "<BR>"));
          }
          printToWebClient(PSTR("\r\n" MENU_TEXT_VB3 "\r\n"));
          webPrintFooter();
          break;
        }
        // switching monitor on/off
        if (p[1]=='M') {
          p+=2;               // hopefully finds a digit there ...
          monitor=atoi(p);    // .. to convert
          webPrintHeader();
          if (monitor>0) {
            printToWebClient(PSTR(MENU_TEXT_SR1));
            monitor = 1;
          } else {
            printToWebClient(PSTR(MENU_TEXT_SR2));
          }
          printToWebClient(PSTR("\r\n" MENU_TEXT_SR3 "\r\n"));
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
          uint8_t destAddr = bus->getBusDest();
          p+=2;               // third position in cLineBuffer
          if(!(httpflags & HTTP_FRAG)) webPrintHeader();

          if (!isdigit(*p)) {   // now we check for digits - nice
            printToWebClient(PSTR(MENU_TEXT_ER1 "\r\n"));
          } else {
            line=atoi(p);       // convert until non-digit char is found
            p=strchr(p,'=');    // search for '=' sign
            if (p==NULL) {        // no match
                printToWebClient(PSTR(MENU_TEXT_ER2 "\r\n"));
            } else {
              p++;                   // position pointer past the '=' sign
              char* token = strchr(p, '!');
              if (token != NULL) {
                token++;
                if (token[0] > 0) {
                  int d_addr = atoi(token);
                  printFmtToDebug(PSTR("Setting temporary destination to %d\r\n"), d_addr);
                  bus->setBusType(bus->getBusType(), bus->getBusAddr(), d_addr);
                }
              }

              printFmtToDebug(PSTR("set ProgNr %d = %s"), line, p);
              writelnToDebug();
              // Now send it out to the bus
              int setresult = 0;
              setresult = set(line,p,setcmd);

              if (setresult!=1) {
                printToWebClient(PSTR(MENU_TEXT_ER3 "\r\n"));
                if (setresult == 2) {
                  printToWebClient(PSTR(" - " MENU_TEXT_ER4 "\r\n"));
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
                bus->setBusType(bus->getBusType(), bus->getBusAddr(), destAddr);
              }
            }
          }
          if(!(httpflags & HTTP_FRAG)) webPrintFooter();
          flushToWebClient();
          break;
        }
        // list categories
        if (p[1]=='K' && !isdigit(p[2])) {
          //list categories
          webPrintHeader();
          printToWebClient(PSTR("<table><tr><td>&nbsp;</td><td>&nbsp;</td></tr>\r\n"));
          int16_t cat_min = -1, cat_max = -1;
          for(int cat=0;cat<CAT_UNKNOWN;cat++){
            if ((bus->getBusType() != BUS_PPS) || (bus->getBusType() == BUS_PPS && (cat == CAT_PPS || cat == CAT_USERSENSORS))) {
              printFmtToWebClient(PSTR("<tr><td><a href='K%d'>"), cat);
#if defined(__AVR__)
              printENUM(pgm_get_far_address(ENUM_CAT),sizeof(ENUM_CAT),cat,1);
              uint_farptr_t tempAddr = pgm_get_far_address(ENUM_CAT_NR) + (cat * 2) * sizeof(ENUM_CAT_NR[0]);
              cat_min = pgm_read_word_far(tempAddr);
              cat_max = pgm_read_word_far(tempAddr + sizeof(ENUM_CAT_NR[0]));
#else
              printENUM(ENUM_CAT,sizeof(ENUM_CAT),cat,1);
              cat_min = ENUM_CAT_NR[cat*2];
              cat_max = ENUM_CAT_NR[cat*2+1];
#endif
              printToWebClient(decodedTelegram.enumdescaddr); //copy Category name to buffer
              writelnToDebug();
              printFmtToWebClient(PSTR("</a></td><td>%hd - %hd</td></tr>\r\n"), cat_min, cat_max);
            }
          }
          printToWebClient(PSTR("</table>"));
          webPrintFooter();
          flushToWebClient();
          break;
        }
        // list enum values
        if (p[1]=='E') {
          webPrintHeader();
          uint16_t line = atoi(&p[2]);
          int i=findLine(line,0,NULL);
          if (i>=0) {
            loadPrognrElementsFromTable(line, i);
            uint8_t flag = 0;
            // check type
            switch(decodedTelegram.type){
              case VT_ENUM: flag = PRINT_DISABLED_VALUE + 1; break;
              case VT_CUSTOM_ENUM:
              case VT_CUSTOM_BIT:
              case VT_BIT: flag = DO_NOT_PRINT_DISABLED_VALUE + 1; break;
            }
            if(flag) {
              listEnumValues(decodedTelegram.enumstr, decodedTelegram.enumstr_len, NULL, PSTR(" - "), NULL, PSTR("<br>\r\n"), NULL, 0, PRINT_VALUE_FIRST, flag - 1);
            } else {
              printToWebClient(PSTR(MENU_TEXT_ER5));
            }
          } else {
            printToWebClient(PSTR(MENU_TEXT_ER6));
          }
          webPrintFooter();
          break;
        }
        // query reset value
        if (p[1]=='R') {
          webPrintHeader();
          if (!queryDefaultValue(atoi(&p[2]), msg, tx_msg)) {
            if(decodedTelegram.error == 258)
              printToWebClient(PSTR(MENU_TEXT_ER6 "\r\n"));
            else if(decodedTelegram.error == 261) {
              printlnToDebug(printError(decodedTelegram.error));  // to PC hardware serial I/F
              printToWebClient(PSTR(MENU_TEXT_ER3 "\r\n"));
            }
          } else{
// TODO: replace pvalstr with data from decodedTelegram structure
            build_pvalstr(0);
            if (outBuf[0]>0) {
              printToWebClient(outBuf);
              printToWebClient(PSTR("<br>"));
            }
          }
          webPrintFooter();
          break;
        }
#endif

        if(p[1]=='Q') {
          if(!(httpflags & HTTP_FRAG)) webPrintHeader();
          uint8_t myAddr = bus->getBusAddr();
          uint8_t destAddr = bus->getBusDest();
          printToWebClient(PSTR(MENU_TEXT_VER ": "));
          printToWebClient(BSB_VERSION);
          printToWebClient(PSTR("<BR>\r\n"));
          printToWebClient(PSTR(MENU_TEXT_QSC "...<BR>"));
          switch(bus->getBusType()) {
            case BUS_BSB: bus->setBusType(BUS_BSB, myAddr, 0x7F); break;
            case BUS_LPB: bus->setBusType(BUS_LPB, myAddr, 0xFF); break;
          }

          flushToWebClient();

          uint8_t found_ids[10] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
          if (bus->Send(TYPE_QINF, 0x053D0002, msg, tx_msg, NULL, 0, false)) {
            unsigned long startquery = millis();
            while (millis() - startquery < 10000) {
              if (bus->GetMessage(msg)) {
                uint8_t found_id = 0;
                bool found = false;
                if (bus->getBusType() == BUS_BSB && msg[4] == 0x02) {
                  found_id = msg[1] & 0x7F;
                }
                if (bus->getBusType() == BUS_LPB && msg[8] == 0x02) {
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
                  printFmtToWebClient(PSTR(MENU_TEXT_QFD ": %hu<BR>\r\n"),found_id);
                  flushToWebClient();
                }
              }
              delay(1);
            }
          } else {
            printToWebClient(PSTR(MENU_TEXT_QFA "!<BR>"));
          }

          for (int x=0;x<10;x++) {
            if (found_ids[x]==0xFF) {
              continue;
            }
            bus->setBusType(bus->getBusType(), myAddr, found_ids[x]);
            printFmtToWebClient(PSTR("<BR>" MENU_TEXT_QRT " %hu..."), found_ids[x]);
            flushToWebClient();

            uint32_t c=0;
            uint16_t l;
            int orig_dev_fam = my_dev_fam;
            int orig_dev_var = my_dev_var;
            query_program_and_print_result(6225, PSTR("<BR>\r\n"), NULL);
            int temp_dev_fam = strtod(decodedTelegram.value,NULL);
            query_program_and_print_result(6226, PSTR("<BR>\r\n"), NULL);
            int temp_dev_var = strtod(decodedTelegram.value,NULL);
            my_dev_fam = temp_dev_fam;
            my_dev_var = temp_dev_var;

            for(uint16_t q = 0; q < sizeof(proglist4q)/sizeof(int); q++) {
              int prognr = 0;
#if defined(__AVR__)
              prognr = pgm_read_word_far(pgm_get_far_address(proglist4q) + (q) * sizeof(proglist4q[0]));
#else
              prognr = proglist4q[q];
#endif
              query_program_and_print_result(prognr, PSTR("<BR>\r\n"), NULL);
            }
            query_program_and_print_result(10003, PSTR("<BR>\r\n"), PSTR(" (10003): "));
            query_program_and_print_result(10004, PSTR("<BR>\r\n"), PSTR(" (10004): "));
            printToWebClient(PSTR("<BR>\r\n"));
            flushToWebClient();

            for (uint16_t i=0; i<sizeof(params4q)/sizeof(int); i++) {
              int prognr = 0;
#if defined(__AVR__)
              prognr = pgm_read_word_far(pgm_get_far_address(params4q) + (i) * sizeof(params4q[0]));
#else
              prognr = params4q[i];
#endif
              printFmtToWebClient(PSTR("%d;"), prognr);
            }
            printToWebClient(PSTR("<BR>\r\n"));
            for (uint16_t i=0; i<sizeof(params4q)/sizeof(int); i++) {
              int prognr = 0;
#if defined(__AVR__)
              prognr = pgm_read_word_far(pgm_get_far_address(params4q) + (i) * sizeof(params4q[0]));
#else
              prognr = params4q[i];
#endif
              query(prognr); printToWebClient(decodedTelegram.value);
              printToWebClient(PSTR(";"));
            }

            printToWebClient(PSTR("<BR><BR>\r\n"));
            my_dev_fam = orig_dev_fam;
            my_dev_var = orig_dev_var;

            printToWebClient(PSTR("<BR>" MENU_TEXT_QST "...<BR>\r\n"));
            flushToWebClient();
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
                printFmtToDebug(PSTR("%02X\r\n"), c);
                if (!bus->Send(TYPE_QUR, c, msg, tx_msg)) {
                  print_bus_send_failed();
                } else {
                  if (msg[4+(bus->getBusType()*4)]!=TYPE_ERR) {
                    // Decode the xmit telegram and send it to the PC serial interface
                    printTelegram(tx_msg, -1);
#ifdef LOGGER
                    LogTelegram(tx_msg);
#endif
                    // Decode the rcv telegram and send it to the PC serial interface
                    printTelegram(msg, -1);   // send to hardware serial interface
#ifdef LOGGER
                    LogTelegram(msg);
#endif
                    if (decodedTelegram.msg_type != TYPE_ERR) { //pvalstr[0]<1 - unknown command
                      my_dev_fam = temp_dev_fam;
                      my_dev_var = temp_dev_var;
                      query(l);
                      my_dev_fam = orig_dev_fam;
                      my_dev_var = orig_dev_var;
                      if (decodedTelegram.msg_type == TYPE_ERR) { //pvalstr[0]<1 - unknown command
                        printFmtToWebClient(PSTR("<BR>\r\n%hu - "), l);
                        printToWebClient(decodedTelegram.catdescaddr);
                        printToWebClient(PSTR(" - "));
                        printToWebClient_prognrdescaddr();
                        printFmtToWebClient(PSTR("<BR>\r\n0x%08X"), c);
                        printToWebClient(PSTR("\r\n<br>\r\n"));
                        for (int i=0;i<tx_msg[bus->getLen_idx()]+bus->getBusType();i++) {
                          printFmtToWebClient(PSTR("%02X "), tx_msg[i]);
                        }
                        printToWebClient(PSTR("<br>\r\n"));
                        for (int i=0;i<msg[bus->getLen_idx()]+bus->getBusType();i++) {
                          printFmtToWebClient(PSTR("%02X "), msg[i]);
                        }
                        printToWebClient(PSTR("<br>\r\n"));
                      }
                      forcedflushToWebClient(); //browser will build page immediately
                    }
                  }
                }
              }
            }
            printToWebClient(PSTR("<BR>\r\n" MENU_TEXT_QTE ".<BR>\r\n"));
            flushToWebClient();
          }

          printToWebClient(PSTR("<BR>" MENU_TEXT_QFE ".<BR>\r\n"));
          bus->setBusType(bus->getBusType(), myAddr, destAddr);   // return to original destination address
          if(!(httpflags & HTTP_FRAG)) webPrintFooter();
          forcedflushToWebClient();
          break;
        }
#if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
        if (p[1]=='Y') {
#ifdef DEBUG
          if (debug_mode) {
            webPrintHeader();
            uint8_t type = strtol(&p[2],NULL,16);
            uint32_t c = (uint32_t)strtoul(&p[5],NULL,16);
            if (!bus->Send(type, c, msg, tx_msg)) {
              print_bus_send_failed();
            } else {
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
  // TODO: replace pvalstr with data from decodedTelegram structure
            build_pvalstr(0);
            if (outBuf[0]>0) {
              printToWebClient(outBuf);
              printToWebClient(PSTR("<br>"));
            }

            for (int i=0;i<tx_msg[bus->getLen_idx()]+bus->getBusType();i++) {
              printFmtToWebClient(PSTR("%02X "), tx_msg[i]);
            }
            printToWebClient(PSTR("\r\n<br>\r\n"));
            for (int i=0;i<msg[bus->getLen_idx()]+bus->getBusType();i++) {
              printFmtToWebClient(PSTR("%02X "), msg[i]);
            }
            writelnToWebClient();
            webPrintFooter();
          }
#endif
          break;
        }
#endif

        if (p[1]=='J') {
          uint32_t cmd=0;
          // Parse potential JSON payload
          char json_value_string[52];
          int json_parameter = -1;
          bool json_type = 0;
          bool p_flag = false;
          bool v_flag = false;
          bool t_flag = false;
          bool d_flag = false;
          bool output = false;
          bool been_here = false;
          uint8_t destAddr = bus->getBusDest();
          uint8_t tempDestAddr = 0;
          uint8_t tempDestAddrOnPrevIteration = 0;
          int16_t cat_min = -1, cat_max = -1, cat_param=0;
          uint8_t opening_brackets = 0;
          char* json_token = strtok(p, "=,"); // drop everything before "="
          json_token = strtok(NULL, ",");
          {//local variable scope
            int16_t http_code = HTTP_OK;
            long cache_time = HTTP_DO_NOT_CACHE;

            if((p[2] == 'C' || p[2] == 'K') && json_token!=NULL) {
              cache_time = 300; //5 min
              if((httpflags & HTTP_ETAG))
                http_code = HTTP_NOT_MODIFIED;
            }

            printHTTPheader(http_code, MIME_TYPE_APP_JSON, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, cache_time);
            if (cache_time != HTTP_DO_NOT_CACHE) {
              printToWebClient(PSTR("ETag: \""));
              printToWebClient(BSB_VERSION);
              printToWebClient(PSTR("\"\r\n"));
            }
            printToWebClient(PSTR("\r\n"));
            if (http_code == HTTP_NOT_MODIFIED) {
              forcedflushToWebClient();
              break;
            }
          }
          printToWebClient(PSTR("{\r\n"));
          if(strchr_P(PSTR("CIKLQRSVW"), p[2]) == NULL) {  // ignoring unknown JSON commands
            printToWebClient(PSTR("}"));
            forcedflushToWebClient();
            break;
          }

          if (p[2] == 'V'){ // JSON API version
            printFmtToWebClient(PSTR("\"api_version\": \"" JSON_MAJOR "." JSON_MINOR "\"\r\n}"));
            forcedflushToWebClient();
            break;
          }

          if (p[2] == 'I'){ // dump configuration in JSON
            int32_t freespace = 0;
            bool not_first = false;
            int i;
#if defined LOGGER || defined WEBSERVER
            freespace = SD.vol()->freeClusterCount();
#endif
            printToWebClient(PSTR("  \"name\": \"BSB-LAN\",\r\n  \"version\": \""));
            printToWebClient(BSB_VERSION);
            printFmtToWebClient(PSTR("\",\r\n  \"freeram\": %d,\r\n  \"uptime\": %lu,\r\n  \"MAC\": \"%02hX:%02hX:%02hX:%02hX:%02hX:%02hX\",\r\n  \"freespace\": %ld,\r\n"), freeRam(), millis(), mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], freespace);
// Bus info
            json_parameter = 0; //reuse json_parameter  for lesser memory usage
            i = bus->getBusType();
            if (i != BUS_PPS) {
              if ((DEFAULT_FLAG & FL_RONLY) != FL_RONLY || ((DEFAULT_FLAG & FL_SW_CTL_RONLY) == FL_SW_CTL_RONLY && programWriteMode)) json_parameter = 1;
            } else {
              if (pps_write == 1)  json_parameter = 1;
            }

            switch (i) {
              case 0: strcpy_P(json_value_string, PSTR("BSB")); break; //reuse json_value_string for lesser memory usage
              case 1: strcpy_P(json_value_string, PSTR("LPB")); break;
              case 2: strcpy_P(json_value_string, PSTR("PPS")); break;
            }
            printFmtToWebClient(PSTR("  \"bus\": \"%s\",\r\n  \"buswritable\": %d,\r\n"), json_value_string, json_parameter);
            printFmtToWebClient(PSTR("  \"busaddr\": %d,\r\n  \"busdest\": %d,\r\n"), bus->getBusAddr(), bus->getBusDest());
//enabled options
            printFmtToWebClient(PSTR("  \"monitor\": %d,\r\n  \"verbose\": %d"), monitor, verbose);

            #ifdef ONE_WIRE_BUS
            printFmtToWebClient(PSTR(",\r\n  \"onewirebus\": %d"), One_Wire_Pin);
            printFmtToWebClient(PSTR(",\r\n  \"onewiresensors\": %d"), numSensors);
            #endif
            #ifdef DHT_BUS
            printToWebClient(PSTR(",\r\n  \"dhtbus\": [\r\n"));
            not_first = false;
            int numDHTSensors = sizeof(DHT_Pins) / sizeof(DHT_Pins[0]);
            for(i=0;i<numDHTSensors;i++){
              if(DHT_Pins[i]) {
                if(not_first)
                  printToWebClient(PSTR(",\r\n"));
                else
                  not_first = true;
                printFmtToWebClient(PSTR("    { \"pin\": %d }"), DHT_Pins[i]);
              }
            }
            printToWebClient(PSTR("\r\n  ]"));
            #endif
//protected GPIO
            printToWebClient(PSTR(",\r\n  \"protectedGPIO\": [\r\n"));
            not_first = false;
            for (i=0; i<anz_ex_gpio; i++) {
              if (bitRead(protected_GPIO[i / 8], i % 8)) {
                if(not_first)
                  printToWebClient(PSTR(",\r\n"));
                else
                  not_first = true;
              printFmtToWebClient(PSTR("    { \"pin\": %d }"), i);
              }
            }
            printToWebClient(PSTR("\r\n  ]"));

//averages
#ifdef AVERAGES
            if (logAverageValues) {
              printToWebClient(PSTR(",\r\n  \"averages\": [\r\n"));
              not_first = false;
              for (i=0; i<numAverages; i++) {
                if (avg_parameters[i] > 0) {
                  if(not_first)
                    printToWebClient(PSTR(",\r\n"));
                  else
                    not_first = true;
                  printFmtToWebClient(PSTR("    { \"parameter\": %d }"), avg_parameters[i]);
                }
              }
              printToWebClient(PSTR("\r\n  ]"));
            }
#endif
// logged parameters
          #ifdef LOGGER
            printFmtToWebClient(PSTR(",\r\n  \"logvalues\": %d,\r\n  \"loginterval\": %d,\r\n  \"logged\": [\r\n"), logCurrentValues, log_interval);
            not_first = false;
            for (i=0; i<numLogValues; i++) {
              if (log_parameters[i] > 0)  {
                if(not_first)
                  printToWebClient(PSTR(",\r\n"));
                else
                  not_first = true;
                printFmtToWebClient(PSTR("    { \"parameter\": %d }"), log_parameters[i]);
              }
            }
            printToWebClient(PSTR("\r\n  ]"));
          #endif
            printToWebClient(PSTR("\r\n}\r\n"));
            forcedflushToWebClient();
            break;
          }
#if defined(JSONCONFIG)
          if (p[2] == 'L'){
            generateJSONwithConfig();
            printToWebClient(PSTR("\r\n}\r\n"));
            forcedflushToWebClient();
            break;
          }
#endif
// really we need flushing before prognr parsing?
/*          if (json_token!=NULL) {
            client.flush();
          }*/
          while (client.available()) {
            if (client.read()=='{') {
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
              while (client.available()){
                char c = client.read();
                if (c == '{') {
                  opening_brackets++;
                  if(opening_brackets > 2) {//JSON too complex. Broken JSON?
                    opening_brackets = 0;
                    break;
                  }
                }
                if (c == '}') { output = true; opening_brackets--;}
                if (c == '\"') {opening_quotation = opening_quotation?false:true;} //XOR (switch from false to true and vice versa)
                if (opening_quotation) {
                  if ((c == 'P' || c == 'p') && t_flag != true) { p_flag = true; } //Parameter
                  if (c == 'V' || c == 'v') { v_flag = true; } //Value
                  if (c == 'T' || c == 't') { t_flag = true; } //Type
                  if ((c == 'D' || c == 'd') && t_flag != true) { d_flag = true; } //Destination
                  if ( p_flag || v_flag || t_flag || d_flag) {
                    uint8_t stage_f = 0; //field name
                    bool stage_v = 0; //field value
                    uint8_t j_char_idx = 0;
                    char json_temp[sizeof(json_value_string)];
                    while (client.available()){ //rewind to \":
                      c = client.read();
                      if(c == '\"') stage_f++;
                      if(stage_f == 1 && c == ':') stage_f+=16;
                      if(stage_f > 1) break; //quotation marks or/and colons found
                    }
                    if(stage_f != 17) { //Unexpected end of JSON or broken JSON: multiple quotation marks or colons or wrong order in field name
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
                      if(!stage_v && (c == ' ' || c == ',' || c == '}' || c == '\n' || c == '\r')) { //if it not a string value then we try to find end markers and drop spaces
                        if (c == ' ') continue;
                        if (c == '}') { output = true; opening_brackets--;}
                      break;
                      }
                      if (c == '\"') { //It is string value?
                        if(!stage_v) { //start read from next char after quotation mark if it found
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
                      json_parameter = atoi(jptr);
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
                json_parameter = atoi(json_token);
              }
            }
            if(tempDestAddr != tempDestAddrOnPrevIteration)
              bus->setBusType(bus->getBusType(), bus->getBusAddr(), tempDestAddr);
            if (output || json_token != NULL) {
              if (p[2] != 'K' && p[2] != 'W') {
                int i_line=findLine(json_parameter,0,&cmd);
                if ((p[2] == 'Q' || p[2] == 'C') && (i_line<0 || (cmd == CMD_UNKNOWN && json_parameter < 20000))) { //CMD_UNKNOWN except virtual programs
                  json_token = strtok(NULL,",");
                  continue;
                }
              }

              output = false;
              if(json_parameter == -1) continue;

              if (p[2]=='K' && !isdigit(p[4])) {
                bool notfirst = false;
                for(int cat=0;cat<CAT_UNKNOWN;cat++){
                  if ((bus->getBusType() != BUS_PPS) || (bus->getBusType() == BUS_PPS && (cat == CAT_PPS || cat == CAT_USERSENSORS))) {
                    if (notfirst) {printToWebClient(PSTR(",\r\n"));} else {notfirst = true;}
                    printFmtToWebClient(PSTR("\"%d\": { \"name\": \""), cat);
#if defined(__AVR__)
                    printENUM(pgm_get_far_address(ENUM_CAT),sizeof(ENUM_CAT),cat,1);
                    uint_farptr_t tempAddr = pgm_get_far_address(ENUM_CAT_NR) + (cat * 2) * sizeof(ENUM_CAT_NR[0]);
                    cat_min = pgm_read_word_far(tempAddr);
                    cat_max = pgm_read_word_far(tempAddr + sizeof(ENUM_CAT_NR[0]));
#else
                    printENUM(ENUM_CAT,sizeof(ENUM_CAT),cat,1);
                    cat_min = ENUM_CAT_NR[cat*2];
                    cat_max = ENUM_CAT_NR[cat*2+1];
#endif
                    printToWebClient(decodedTelegram.enumdescaddr); //copy Category name to buffer
                    printFmtToWebClient(PSTR("\", \"min\": %d, \"max\": %d }"), cat_min, cat_max);
                  }
                }
                json_token = NULL;
              }

              if (p[2]=='K' && isdigit(p[4])) {
                cat_param++;
                if (cat_min<0) {
                  int8_t search_cat = -1;
                  search_cat = atoi(&p[4]) * 2;
#if defined(__AVR__)
                  uint_farptr_t tempAddr = pgm_get_far_address(ENUM_CAT_NR) + (search_cat) * sizeof(ENUM_CAT_NR[0]);
                  cat_min = pgm_read_word_far(tempAddr);
                  cat_max = pgm_read_word_far(tempAddr + sizeof(ENUM_CAT_NR[0]));
#else
                  cat_min = ENUM_CAT_NR[search_cat];
                  cat_max = ENUM_CAT_NR[search_cat+1];
#endif
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

              if (p[2]=='Q' || p[2]=='C' || (p[2]=='K' && isdigit(p[4]))) {
                int i_line=findLine(json_parameter,0,&cmd);
                if (i_line<0 || (cmd == CMD_UNKNOWN && json_parameter < 20000)) {//CMD_UNKNOWN except virtual programs
                  continue;
                }

                if (!been_here) been_here = true; else printToWebClient(PSTR(",\r\n"));
                if (p[2]=='Q') {
                  query(json_parameter);
                } else {
                  loadPrognrElementsFromTable(json_parameter, i_line);
                }
                printFmtToWebClient(PSTR("  \"%d\": {\r\n    \"name\": \""), json_parameter);
                printToWebClient_prognrdescaddr();
                printToWebClient(PSTR("\",\r\n"));
                printToWebClient(PSTR("    \"dataType_name\": \""));
                printToWebClient(decodedTelegram.progtypedescaddr);
                printToWebClient(PSTR("\",\r\n"));
                printToWebClient(PSTR("    \"dataType_family\": \""));
                printToWebClient(decodedTelegram.data_type_descaddr);
                printToWebClient(PSTR("\",\r\n"));

                if (p[2]=='Q') {
                  printFmtToWebClient(PSTR("    \"error\": %d,\r\n    \"value\": \"%s\",\r\n    \"desc\": \""), decodedTelegram.error, decodedTelegram.value);
                  if(decodedTelegram.data_type == DT_ENUM && decodedTelegram.enumdescaddr)
                    printToWebClient(decodedTelegram.enumdescaddr);
                  printToWebClient(PSTR("\",\r\n"));
                }

                if (p[2] != 'Q') {
                  printToWebClient(PSTR("    \"possibleValues\": [\r\n"));
                    if (decodedTelegram.enumstr_len > 0) {
                      listEnumValues(decodedTelegram.enumstr, decodedTelegram.enumstr_len, PSTR("      { \"enumValue\": "), PSTR(", \"desc\": \""), NULL, PSTR("\" }"), PSTR(",\r\n"), 0, PRINT_VALUE_FIRST, decodedTelegram.type==VT_ENUM?PRINT_DISABLED_VALUE:DO_NOT_PRINT_DISABLED_VALUE);
                    }

                  printFmtToWebClient(PSTR("\r\n    ],\r\n    \"isswitch\": %d,\r\n"), decodedTelegram.isswitch);
                }
                if (decodedTelegram.data_type == DT_VALS) {
                  char pre_buf[10];
                  pre_buf[0] = 0;
                  if (decodedTelegram.precision != 0) {
                    strcpy_P(pre_buf, PSTR("0."));
                    for(uint8_t j = 1; j < decodedTelegram.precision; j ++){
                      strcat_P(pre_buf, PSTR("0"));
                    }
                  }
                  strcat_P(pre_buf, PSTR("1"));
                  printFmtToWebClient(PSTR("    \"precision\": %s,\r\n"), pre_buf);
                }
                printFmtToWebClient(PSTR("    \"dataType\": %d,\r\n    \"readonly\": %d,\r\n    \"unit\": \"%s\"\r\n  }"), decodedTelegram.data_type, decodedTelegram.readonly, decodedTelegram.unit);
              }

              if (p[2]=='S') {
                if (!been_here) been_here = true; else printToWebClient(PSTR(",\r\n"));
                int status = set(json_parameter, json_value_string, json_type);
                printFmtToWebClient(PSTR("  \"%d\": {\r\n    \"status\": %d\r\n  }"), json_parameter, status);

                printFmtToDebug(PSTR("Setting parameter %d to \"%s\" with type %d\r\n"), json_parameter, json_value_string, json_type);
              }

              if (p[2]=='R') {
                if (!been_here) been_here = true; else printToWebClient(PSTR(",\r\n"));
                queryDefaultValue(json_parameter, msg, tx_msg);
                printFmtToWebClient(PSTR("  \"%d\": {\r\n    \"error\": %d,\r\n    \"value\": \"%s\"\r\n  }"), json_parameter, decodedTelegram.error, decodedTelegram.value);

                printFmtToDebug(PSTR("Default value of parameter %d is \"%s\"\r\n"), json_parameter, decodedTelegram.value);
              }

#if defined(JSONCONFIG)
              if (p[2]=='W') {
                if (!been_here) been_here = true; else printToWebClient(PSTR(",\r\n"));
                int status = takeNewConfigValueFromUI_andWriteToEEPROM(json_parameter, outBuf);
                printFmtToWebClient(PSTR("  \"%d\": {\r\n    \"status\": %d\r\n  }"), json_parameter, status);

                printFmtToDebug(PSTR("Setting parameter %d to \"%s\"\r\n"), json_parameter, outBuf);
              }
#endif

              if (json_token != NULL && ((p[2] != 'K' && !isdigit(p[4])) || p[2] == 'Q' || p[2] == 'C' || p[2] == 'R')) {
                json_token = strtok(NULL,",");
              }
            }
            tempDestAddrOnPrevIteration = tempDestAddr;
            json_parameter = -1;
          }
          if(tempDestAddr != destAddr)
            bus->setBusType(bus->getBusType(), bus->getBusAddr(), destAddr);
#if defined(JSONCONFIG)
          bool needReboot = false;
          if (p[2]=='W') {
            needReboot = SaveConfigFromRAMtoEEPROM();
#ifdef MAX_CUL
            UpdateMaxDeviceList(); //Update list MAX! devices
#endif
          }
#endif
          printFmtToWebClient(PSTR("\r\n}\r\n"));
          forcedflushToWebClient();
#if defined(JSONCONFIG)
          if (needReboot) {
            resetBoard();
          }
#endif
          break;
        }

#ifdef LOGGER
        if (p[1]=='D') { // access datalog file
          if (p[2]=='0' || ((p[2]=='D' || p[2]=='J') && p[3]=='0')) {  // remove datalog file
            webPrintHeader();
            File dataFile;
            bool filewasrecreated = false;
//recreate journal file for telegram logging
            if (p[2]=='J' || p[2]=='0') {
              SD.remove(journalFileName);
              dataFile = SD.open(journalFileName, FILE_WRITE);
              if (dataFile) {
                dataFile.close();
                filewasrecreated = true;
                printToDebug(journalFileName);
                printToWebClient(journalFileName);
              }
            }
//recreate datalog file for programs values logging
              if (p[2]=='D' || p[2]=='0') {
                if(p[2]=='0') {
                  printToDebug(PSTR(", "));
                  printToWebClient(PSTR(", "));
                }
              SD.remove(datalogFileName);
              if (createdatalogFileAndWriteHeader()) {
                filewasrecreated = true;
                printToDebug(datalogFileName);
                printToWebClient(datalogFileName);
              }
            }
            if (filewasrecreated) {
              printToWebClient(PSTR(MENU_TEXT_DTR "\r\n"));
              printToDebug(PSTR(": file(s) was removed and recreated."));
            } else {
              printToWebClient(PSTR(MENU_TEXT_DTF "\r\n"));
            }
            webPrintFooter();
#if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
          } else if (p[2]=='G') {
            webPrintHeader();
#if !defined(I_WILL_USE_EXTERNAL_INTERFACE)
            printToWebClient(PSTR("<A HREF='D'>" MENU_TEXT_DTD "</A><div align=center></div>\r\n"));
#if defined(__AVR__)
            printPStr(pgm_get_far_address(graph_html), sizeof(graph_html));
#else
            printPStr(graph_html, sizeof(graph_html));
#endif
#else
            printToWebClient(PSTR("/DG command disabled because I_WILL_USE_EXTERNAL_INTERFACE defined<br>\r\n"));
#endif
            webPrintFooter();
#endif
          } else {  // dump datalog or journal file
            printHTTPheader(HTTP_OK, MIME_TYPE_TEXT_PLAIN, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_AUTO_CACHE_AGE);
            printToWebClient(PSTR("\r\n"));
            flushToWebClient();
            File dataFile;
            if (p[2]=='J') { //journal
              dataFile = SD.open(journalFileName);
            } else if (p[2]=='D') { //datalog
              dataFile = SD.open(datalogFileName);
            } else { //datalog
              dataFile = SD.open(datalogFileName);
            }
            // if the file is available, read from it:
            if (dataFile) {

              unsigned long startdump = millis();
              transmitFile(dataFile);
              dataFile.close();

              printFmtToDebug(PSTR("Duration: %lu\r\n"), millis()-startdump);
            } else {
              printToWebClient(PSTR(MENU_TEXT_DTO "\r\n"));
            }
          }
          flushToWebClient();
          break;
        }
#endif
#if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
        if (p[1]=='C'){ // dump configuration
          if(!(httpflags & HTTP_FRAG)) webPrintHeader();

          switch(p[2]){
#ifdef CONFIG_IN_EEPROM
            case 'E':
              if (p[3]=='='){
                if (p[4]=='1') { //Use EEPROM
                  UseEEPROM = 0x96;
                } else {   //Use _config.h
                  UseEEPROM = 0x69;
                }
              }
//                printToWebClient(PSTR(MENU_TEXT_LBO ": "));
              if(UseEEPROM == 0x96)
                printyesno(1) ;
              else
                printyesno(0) ;
              break;
            case 'S': //save config to EEPROM
                for(uint8_t i = 0; i < CF_LAST_OPTION; i++){
                  writeToEEPROM(i);
                }
//                printToWebClient(PSTR(MENU_TEXT_LBO ": "));
//                printyesno(UseEEPROM) ;
              break;
#endif
#ifdef WEBCONFIG
            case 'I': {//Parse HTTP form and implement changes
              implementConfig();
              generateChangeConfigPage();
              generateConfigPage();
#ifdef MAX_CUL
              UpdateMaxDeviceList(); //Update list MAX! devices
#endif
              if(!(httpflags & HTTP_FRAG)) webPrintFooter();
              flushToWebClient();
              if (SaveConfigFromRAMtoEEPROM() == true) {
                resetBoard();
              }
            }
            break;
              //no break here.
#endif
            default:
#ifdef WEBCONFIG
              generateChangeConfigPage();
#endif
              generateConfigPage();
              if(!(httpflags & HTTP_FRAG)) webPrintFooter();
              flushToWebClient();
// EEPROM dump require ~3 sec so let it be last operation.
// Dump when serial debug active or have telnet client
              EEPROM_dump();
              break;
            }
          break;
        }
#if !defined(I_DO_NOT_WANT_URL_CONFIG)
        if (p[1]=='L'){
          webPrintHeader();
          switch(p[2]){
            case 'C':
              if (p[3]=='='){
                if (p[4]=='1') {
                  logCurrentValues = true;
                } else {
                  logCurrentValues = false;
                }
//                printToWebClient(PSTR(MENU_TEXT_LBO ": "));
                printyesno(logCurrentValues) ;
              }
              break;
            case 'B':
              if (p[3]=='='){
                if (p[4]=='1') {
                  logTelegram |= LOGTELEGRAM_BROADCAST_ONLY;
                } else {
                  if(logTelegram & LOGTELEGRAM_BROADCAST_ONLY)
                    logTelegram -= LOGTELEGRAM_BROADCAST_ONLY;
                }
                printToWebClient(PSTR(MENU_TEXT_LBO ": "));
                printyesno(logTelegram & LOGTELEGRAM_BROADCAST_ONLY) ;
              }
              break;
            case 'U':
              if (p[3]=='='){
                if (p[4]=='1') {
                  logTelegram |= LOGTELEGRAM_UNKNOWN_ONLY;
                } else {
                  if(logTelegram & LOGTELEGRAM_UNKNOWN_ONLY)
                    logTelegram -= LOGTELEGRAM_UNKNOWN_ONLY; //clear bit
                }
                printToWebClient(PSTR(MENU_TEXT_BUT ": "));
                printyesno(logTelegram & LOGTELEGRAM_UNKNOWN_ONLY);
              }
              break;
            case '=': // logging configuration: L=<interval>,<parameter 1>,<parameter 2>,...,<parameter20>
              {char* log_token = strtok(p,"=,");  // drop everything before "="
              log_token = strtok(NULL, "=,");   // first token: interval
              if (log_token != 0) {
                log_interval = atoi(log_token);
//                if (log_interval < 10) {log_interval = 10;}
                lastLogTime = millis();
#ifdef MQTT
                lastMQTTTime = millis();
#endif
                printFmtToWebClient(PSTR(MENU_TEXT_LGI ": %d"), log_interval);
                printToWebClient(PSTR(" " MENU_TEXT_SEC "<BR>\r\n"));
              }
              log_token = strtok(NULL,"=,");    // subsequent tokens: logging parameters
              int token_counter = 0;
              if (log_token != 0) {
                for (int i=0;i<numLogValues;i++) {
                  log_parameters[i] = 0;
                }
              printToWebClient(PSTR(MENU_TEXT_LGN ": "));
              }
              while (log_token!=0) {
                int log_parameter = atoi(log_token);
                if (token_counter < numLogValues) {
                  log_parameters[token_counter] = log_parameter;
                  printFmtToWebClient(PSTR("%d \r\n"), log_parameters[token_counter]);
                  token_counter++;
                }
                log_token = strtok(NULL,"=,");
              }}
            break;
          case 'E': //enable telegrams logging to journal.txt
          case 'D': //disable telegrams logging
            if (p[2]=='E')
              logTelegram |= LOGTELEGRAM_ON;
            else {
              if(logTelegram & LOGTELEGRAM_ON)
                logTelegram -= LOGTELEGRAM_ON; //clear bit
              }
            printToWebClient(PSTR(MENU_TEXT_LOT ": "));
            printyesno(logTelegram);
            break;
          default:
            printToWebClient(PSTR(MENU_TEXT_ER1));
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

          printToWebClient(PSTR(MENU_TEXT_BUS ": "));
          uint8_t savedbus = bus_type;
          bus_type = p[2] - '0';
          switch (bus_type){
            case 0:
              own_address = myAddr;
              dest_address = destAddr;
              printToWebClient(PSTR("BSB"));
              break;
            case 1:
              own_address = myAddr;
              dest_address = destAddr;
              printToWebClient(PSTR("LPB"));
              break;
            case 2:
              pps_write = myAddr;
              printToWebClient(PSTR("PPS"));
              break;
            default:
              bus_type = savedbus;
              break;
          }
          setBusType(); //Apply changes
          printToWebClient(PSTR("\r\n"));
          if (bus->getBusType() != BUS_PPS) {
            printFmtToWebClient(PSTR(" (%d, %d)"), myAddr, destAddr);
          } else {
            if (pps_write == 1) {
              printToWebClient(PSTR(" " MENU_TEXT_BRW));
            } else {
              printToWebClient(PSTR(" " MENU_TEXT_BRO));
            }
            printToWebClient(PSTR("\r\n"));
          }

          SetDevId();
          webPrintFooter();
          break;
        }
#endif
#endif
        if (p[1]=='N'){           // Reset Arduino...
          webPrintHeader();
          if (p[2]=='E') {
            printToWebClient(PSTR("Clearing EEPROM (affects MAX! devices and PPS-Bus settings)...<BR>\r\n"));
            forcedflushToWebClient();
          }

#ifdef LOGGER
          // what doing this fragment? Just opened and closed file? We really need it?
          // FH: Before, it seemed to be necessary to have the file properly closed. And since I thought you can only properly close it when it's opened before, I was opening it.
          File dataFile = SD.open(datalogFileName, FILE_WRITE);
          if (dataFile) {
            dataFile.close();
          }
#endif
          if (p[2]=='E' && EEPROM_ready) { //...and clear EEPROM
            clearEEPROM();
          }
          printToWebClient(PSTR("Restarting Arduino...\r\n"));
          webPrintFooter();
          resetBoard();
          break;
        }
        // print queries
        webPrintHeader();
        char* range;
        range = strtok(p,"/");
        while(range!=0){
          if (range[0]=='U') { // output user-defined custom_array variable
            for(int i=0;i<numCustomFloats;i++){
              printFmtToWebClient(PSTR("<tr><td>\r\ncustom_float[%d]: %.2f\r\n</td></tr>\r\n"), i, custom_floats[i]);
            }
            for(int i=0;i<numCustomLongs;i++){
              printFmtToWebClient(PSTR("<tr><td>\r\ncustom_long[%d]: %ld\r\n</td></tr>\r\n"),i, custom_longs[i]);
            }
          }else if (range[0]=='X') { // handle MAX command
#ifdef MAX_CUL
            if (enable_max_cul) {
              int max_avg_count = 0;
              float max_avg = 0;
              for (uint16_t x=0;x<MAX_CUL_DEVICES;x++) {
                if (max_cur_temp[x] > 0) {
                  max_avg += (float)(max_cur_temp[x] & 0x1FF) / 10;
                  max_avg_count++;
                  printFmtToWebClient(PSTR("<tr><td>%s (%lx): %.2f / %.2f"), max_device_list[x], max_devices[x], ((float)max_cur_temp[x] / 10),((float)max_dst_temp[x] / 2));
                  if (max_valve[x] > -1) {
                    printFmtToWebClient(PSTR(" (%h%%)"), max_valve[x]);
                  }
                  printToWebClient(PSTR("</td></tr>"));
                }
              }
              if (max_avg_count > 0) {
                printFmtToWebClient(PSTR("<tr><td>AvgMax: %.2f</td></tr>\r\n"), max_avg / max_avg_count);
              } else {
                printToWebClient(PSTR("<tr><td>" MENU_TEXT_MXN "</td></tr>"));
              }
            }
#endif
#if !defined(I_DO_NOT_WANT_URL_CONFIG)
          }else if(range[0]=='A') { // handle average command
#ifdef AVERAGES
            if (range[1]=='C' && range[2]=='=') { //24h average calculation on/off
              if (range[3]=='1') //Enable 24h average calculation temporarily
                logAverageValues = true;
              else  //Disable 24h average calculation temporarily
                logAverageValues = false;
            }
            if (logAverageValues) {
              if (range[1]=='=') {
                char* avg_token = strtok(range,"=,");  // drop everything before "="
                avg_token = strtok(NULL,"=,");    // subsequent tokens: average parameters
                int token_counter = 0;
                if (avg_token != 0) {
                  resetAverageCalculation();
                  printToWebClient(PSTR(MENU_TEXT_24N ": "));
                }
                while (avg_token!=0) {
                  if (token_counter < numAverages) {
                    avg_parameters[token_counter] = atoi(avg_token);
                    printFmtToWebClient(PSTR("%d \r\n"), avg_parameters[token_counter]);
                    token_counter++;
                  }
                  avg_token = strtok(NULL,"=,");
                }
              }
            }
#else
            printToWebClient("AVERAGES module not compiled\r\n");
#endif
#endif
          }else if (range[0]=='G') { // handle gpio command
            uint8_t val;
            uint8_t pin;
//            bool error = false;
            p=range+1;
            if (!isdigit(*p)) {   // now we check for digits
              printToWebClient(PSTR(MENU_TEXT_ER1 "\r\n"));
              break;
            }
            pin=(uint8_t)atoi(p);       // convert until non-digit char is found
            if (bitRead(protected_GPIO[pin / 8], pin % 8)) {
              printToWebClient(PSTR(MENU_TEXT_ER7 "\r\n"));
              break;
            }

            char* dir_token = strchr(range,',');
            dir_token++;
            p=strchr(p,'=');    // search for '=' sign
            if (p==NULL) {        // no match -> query value
              if (dir_token!=NULL) {
                if (*dir_token=='I') {
                  pinMode(pin, INPUT);
                  printFmtToDebug(PSTR("Pin %d set to input.\r\n"), pin);
                }
              }
              val=digitalRead(pin);
            } else { // set value
              p++;
              uint16_t i = 0;
              while(p[i]){
                p[i] |= 0x20; //to lower case
                i++;
              }
              if (!strncmp_P(p, PSTR("on"), 2) || !strncmp_P(p, PSTR("high"), 2) || *p=='1') {
                val=HIGH;
              } else {
                val=LOW;
              }
              pinMode(pin, OUTPUT); // TODO: does this case a problem if already set as output?
              digitalWrite(pin, val);
            }
            printFmtToWebClient(PSTR("GPIO%hu: %d"), pin, val!=LOW?1:0);
#if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
          }else if (range[0]=='B') {
            if (range[1]=='0') { // reset furnace duration
              printToWebClient(STR20006);
              printToWebClient(PSTR(".<br>\r\n"));
              resetDurations();
            }
          } else {
            char* line_start;
            char* line_end;
            int start=-1;
            int end=-1;
            uint8_t destAddr = bus->getBusDest();
            if (range[0]=='K') {
              uint8_t cat = atoi(&range[1]) * 2; // * 2 - two columns in ENUM_CAT_NR table
  #if defined(__AVR__)
                uint_farptr_t tempAddr = pgm_get_far_address(ENUM_CAT_NR) + (cat) * sizeof(ENUM_CAT_NR[0]);
                start = pgm_read_word_far(tempAddr);
                end = pgm_read_word_far(tempAddr + sizeof(ENUM_CAT_NR[0]));
  #else
                start = ENUM_CAT_NR[cat];
                end = ENUM_CAT_NR[cat+1];
  #endif
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

              char* token = strchr(range, '!');
              if (token != NULL) {
                token++;
                if (token[0] > 0) {
                  int d_addr = atoi(token);
                  printFmtToDebug(PSTR("Setting temporary destination to %d\r\n"), d_addr);
                  bus->setBusType(bus->getBusType(), bus->getBusAddr(), d_addr);
                }
              }

              start=atoi(line_start);
              end=atoi(line_end);
            }
            query(start,end,0);
            if (bus->getBusDest() != destAddr) {
              bus->setBusType(bus->getBusType(), bus->getBusAddr(), destAddr);
            }
#endif
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
        printlnToDebug(PSTR("\r\nTimeout"));
      }

    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.flush();
    client.stop();
  } // endif, client


#ifdef MQTT
  if (mqtt_broker_ip_addr[0] && mqtt_mode) { //Address was set and MQTT was enabled
    

    mqtt_connect();        //Luposoft, connect to mqtt
    MQTTPubSubClient->loop();    //Luposoft: listen to incoming messages

    if ((((millis() - lastMQTTTime >= (log_interval * 1000)) && log_interval > 0) || log_now > 0) && numLogValues > 0) {
      lastMQTTTime = millis();
      for (int i=0; i < numLogValues; i++) {
        if (log_parameters[i] > 0) {
          mqtt_sendtoBroker(log_parameters[i]);  //Luposoft, put hole unchanged code in new function mqtt_sendtoBroker to use it at other points as well
        }
      }
      if(MQTTPubSubClient != NULL && !mqtt_mode)  //Luposoft: user may disable MQTT through web interface
      {
        if (MQTTPubSubClient->connected())
        {
          MQTTPubSubClient->disconnect();
          printlnToDebug(PSTR("MQTT was disconnected on order through web interface"));
        }
      }
    }
  }
  if (MQTTPubSubClient && mqtt_mode == 0) {
    delete MQTTPubSubClient;
    MQTTPubSubClient = NULL;
    mqtt_client->stop();
    delete mqtt_client;
  }
#endif


#ifdef LOGGER
  if(logCurrentValues && SD.vol()->freeClusterCount() >= MINIMUM_FREE_SPACE_ON_SD) {
    if (((millis() - lastLogTime >= (log_interval * 1000)) && log_interval > 0) || log_now > 0) {
//    SetDateTime(); // receive inital date/time from heating system
      log_now = 0;
      File dataFile = SD.open(datalogFileName, FILE_WRITE);

      if (dataFile) {
        for (int i=0; i < numLogValues; i++) {
          int outBufLen = 0;
          if (log_parameters[i] > 0) {
            outBufLen += sprintf_P(outBuf + outBufLen, PSTR("%lu;%s;%d;"), millis(), GetDateTime(outBuf + outBufLen + 80), log_parameters[i]);
            if ((log_parameters[i] >= 20050 && log_parameters[i] < 20100)) {
             //averages
              outBufLen += strlen(strcpy_P(outBuf + outBufLen, PSTR(STR_24A_TEXT ". ")));
            }
            dataFile.print(outBuf);
            query(log_parameters[i]);
            outBufLen = 0;
            strcpy_PF(outBuf + outBufLen, decodedTelegram.prognrdescaddr);
            dataFile.print(outBuf);
            outBufLen = 0;
            if (decodedTelegram.sensorid) {
              outBufLen += sprintf_P(outBuf + outBufLen, PSTR("#%d"), decodedTelegram.sensorid);
            }
            outBufLen += sprintf_P(outBuf + outBufLen, PSTR(";%s;%s\r\n"), decodedTelegram.value, decodedTelegram.unit);
            dataFile.print(outBuf);
          }
        }
        dataFile.close();
      } else {
    // if the file isn't open, pop up an error:
        printToWebClient(PSTR(MENU_TEXT_DTO "\r\n"));
        printFmtToDebug(PSTR("Error opening %s!\r\n"), datalogFileName);
      }
      lastLogTime = millis();
    }
  }
#endif

// Calculate 24h averages
#ifdef AVERAGES
  if (logAverageValues){
    if(millis() / 60000 != lastAvgTime) {
      if (avgCounter == 1441) {
        for (int i=0; i<numAverages; i++) {
          avgValues_Old[i] = avgValues[i];
          avgValues_Current[i] = 0;
        }
        avgCounter = 1;
      }
      for (int i=0; i<numAverages; i++) {
        if (avg_parameters[i] > 0) {
          query(avg_parameters[i]);
          float reading = strtod(decodedTelegram.value,NULL);
          printFmtToDebug(PSTR("%f\r\n"), reading);
          if (isnan(reading)) {} else {
            avgValues_Current[i] = (avgValues_Current[i] * (avgCounter-1) + reading) / avgCounter;
            if (avgValues_Old[i] == -9999) {
              avgValues[i] = avgValues_Current[i];
            } else {
              avgValues[i] = ((avgValues_Old[i]*(1440-avgCounter))+(avgValues_Current[i]*avgCounter)) / 1440;
            }
          }
          printFmtToDebug(PSTR("%f\r\n"), avgValues[i]);
        }
      }
      avgCounter++;
      lastAvgTime = millis() / 60000;

  #ifdef LOGGER

  // write averages to SD card to protect from power off
      if (avg_parameters[0] > 0) { //write averages if at least one value is set
        File avgfile = SD.open(averagesFileName, FILE_WRITE);
        if (avgfile) {
          avgfile.seek(0);
          for (int i=0; i<numAverages; i++) {
            sprintf_P(outBuf, PSTR("%f\r\n%f\r\n%f\r\n"), avgValues[i], avgValues_Old[i], avgValues_Current[i]);
            avgfile.print(outBuf);
          }
          avgfile.println(avgCounter);
          avgfile.close();
        }
      }
  #endif
  }
  } else {
    avgCounter = 0;
  }
#endif

#ifdef ONE_WIRE_BUS
  {
    unsigned long tempTime = millis() / ONE_WIRE_REQUESTS_PERIOD;
    if (tempTime != lastOneWireRequestTime) {
      sensors->requestTemperatures(); //call it outside of here for more faster answers
      lastOneWireRequestTime = tempTime;
    }
  }
#endif

#ifdef RGT_EMULATOR
  {
    byte tempTime = (millis() / 60000) % 60;
    if(newMinuteValue != tempTime){
      newMinuteValue = tempTime;
      for (uint8_t i = 0; i < 3; i++){
        if(rgte_sensorid[i][0] != 0){
          uint8_t z = 0;
          float value = 0;
          for(uint8_t j = 0; j < 5; j++){
            if(rgte_sensorid[i][j] != 0){
              query(rgte_sensorid[i][j]);
              if(decodedTelegram.type == VT_TEMP && decodedTelegram.error == 0){
                z++;
                value += atof(decodedTelegram.value);
              }
            }
          }
          if(z != 0){
            _printFIXPOINT(decodedTelegram.value, value / z, 2);
// if we want to substitute own address sometime to RGT1(2,3)
//            uint8_t saved_own_address = bus->getBusAddr();
//            bus->setBusType(bus->getBusType(), ADDR_RGT1 + i, bus->getBusDest());
            set(10000 + i, decodedTelegram.value, false); //send INF message like RGT1 - RGT3 devices
//            bus->setBusType(bus->getBusType(), saved_own_address, bus->getBusDest());
          }
        }
      }
    }
  }
#endif

#ifdef BUTTONS
  if(PressedButtons){
    for (uint8_t i = 0; i < 8; i++){
      switch(PressedButtons & (0x01 << i)){
        case TWW_PUSH_BUTTON_PRESSED:
          strcpy_P(decodedTelegram.value, PSTR("1"));
          set(1603, decodedTelegram.value, true);
          PressedButtons &= ~TWW_PUSH_BUTTON_PRESSED;
          break;
        case ROOM1_PRESENCE_BUTTON_PRESSED:
          switchPresenceState(701, 10102);
          PressedButtons &= ~ROOM1_PRESENCE_BUTTON_PRESSED;
          break;
        case ROOM2_PRESENCE_BUTTON_PRESSED:
          switchPresenceState(1001, 10103);
          PressedButtons &= ~ROOM2_PRESENCE_BUTTON_PRESSED;
          break;
        case ROOM3_PRESENCE_BUTTON_PRESSED:
          switchPresenceState(1301, 10104);
          PressedButtons &= ~ROOM3_PRESENCE_BUTTON_PRESSED;
          break;
        default: PressedButtons &= ~(0x01 << i); break; //clear unknown state
      }
    }
  }
#endif

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

#ifdef MAX_CUL
  if (enable_max_cul) {
  byte max_str_index = 0;
#if OUTBUF_LEN < 60
#error "OUTBUF_LEN must be at least 60. In other case MAX! will not work."
#endif

  while (max_cul->available() && EEPROM_ready) {
    c = max_cul->read();
//    printFmtToDebug(PSTR("%c"), c);
    if ((c!='\n') && (c!='\r') && (max_str_index<60)){
      outBuf[max_str_index++]=c;
    } else {
//      writelnToDebug();
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

      if (max_msg_type == 0x00) {     // Device info after pressing pairing button
        for (int x=0;x<10;x++) {
          strncpy(max_hex_str, outBuf+29+(x*2), 2);
          max_hex_str[2]='\0';
          max_id[x] = (char)strtoul(max_hex_str,NULL,16);
        }
        max_id[sizeof(max_device_list[0]) - 1] = '\0';
        printFmtToDebug(PSTR("MAX device info received:\r\n%08lX\r\n%s\r\n"), max_addr, max_id);

        for (uint16_t x=0;x<MAX_CUL_DEVICES;x++) {
          if (max_devices[x] == max_addr) {
            printlnToDebug(PSTR("Device already in EEPROM"));
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
              printlnToDebug(PSTR("Device stored in EEPROM"));
              break;
            }
          }
        }
      }

      if (max_msg_type == 0x02) {
        strncpy(max_hex_str, outBuf+27, 2);
        max_hex_str[2]='\0';
        max_valve[max_idx] = (uint32_t)strtoul(max_hex_str,NULL,16);
        printFmtToDebug(PSTR("Valve position from associated thermostat received:\r\n%08lX\r\n%lu\r\n"), max_addr, max_valve[max_idx]);
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
        strncpy(max_hex_str, outBuf+temp_str_offset, str_len);
        max_hex_str[str_len]='\0';
        max_temp_status = (uint32_t)strtoul(max_hex_str,NULL,16);
        printFmtToDebug(PSTR("%d\r\n%08lX\r\n"), max_msg_len, max_temp_status);
        if (max_msg_type == 0x42) {
          max_cur_temp[max_idx] = (((max_temp_status & 0x8000) >> 7) + ((max_temp_status & 0xFF)));
          max_dst_temp[max_idx] = (max_temp_status & 0x7F00) >> 8;
        }
        if (max_msg_type == 0x60) {
          max_cur_temp[max_idx] = (max_temp_status & 0x0100) + (max_temp_status & 0xFF);
          max_dst_temp[max_idx] = (max_temp_status & 0xFF0000) >> 16;
          max_valve[max_idx] = (max_temp_status & 0xFF000000) >> 24;
        }

        printlnToDebug(PSTR("MAX temperature message received:"));
        printFmtToDebug(PSTR("%08lX\r\n%f\r\n%f\r\n%lu\r\n"), max_addr, ((float)max_cur_temp[max_idx] / 10), (float)(max_dst_temp[max_idx] / 2), max_valve[max_idx]);
      }
    }
  }
}
#endif

  if (debug_mode == 2) {
    telnetClient = telnetServer->available();

    if (telnetClient && haveTelnetClient == false) {
      telnetClient.flush();
      haveTelnetClient = true;
      printToDebug(PSTR("Version: "));
      printlnToDebug(BSB_VERSION);
    }
    if (!telnetClient.connected()) {
      haveTelnetClient = false;
      telnetClient.stop();
    }
  }
#if defined(MDNS_HOSTNAME) && !defined(ESP32)
  mdns.run();
#endif
#if defined(ESP32) && defined(ENABLE_ESP32_OTA)
  update_server.handleClient();
#endif
} // --- loop () ---

//Luposoft: function mqtt_sendtoBroker
/*  Function: mqtt_sendtoBroker()
 *  Does:     send messages to mqtt-broker
 * Pass parameters:
 *  int param
 * Parameters passed back:
 *  none
 * Function value returned:
 *  none
 * Global resources used:
 *  Serial instance
 *  Ethernet instance
 *  MQTT instance
 * *************************************************************** */
#ifdef MQTT
void mqtt_sendtoBroker(int param) {
  // Declare local variables and start building json if enabled
  String MQTTPayload = "";
  String MQTTTopic = "";
  if (mqtt_mode == 2 || mqtt_mode == 3) {
    MQTTPayload = "";
    // Build the json heading
    MQTTPayload.concat(F("{\""));
    if(MQTTDeviceID[0])
      MQTTPayload.concat(MQTTDeviceID);
    else
    MQTTPayload.concat(F("BSB-LAN"));
    if(mqtt_mode == 2)
      MQTTPayload.concat(F("\":{\"status\":{"));
    if(mqtt_mode == 3)
      MQTTPayload.concat(F("\":{\"id\":"));
  }
  boolean is_first = true;
  if (mqtt_connect()) {              //Luposoft, new funct
    if (is_first) {is_first = false;} else {MQTTPayload.concat(F(","));}
    if (MQTTTopicPrefix[0]) {
      MQTTTopic = MQTTTopicPrefix;
      MQTTTopic.concat(F("/"));
    }
    else
      MQTTTopic = "BSB-LAN/";
// use the sub-topic "json" if json output is enabled
    if(mqtt_mode == 2 || mqtt_mode == 3)
      MQTTTopic.concat(F("json"));
    else
      MQTTTopic.concat(String(param));

    query(param);
    if (mqtt_mode == 3) { // Build the json doc on the fly
      int len = 0;
      outBuf[len] = 0;
      len += sprintf_P(outBuf + len, PSTR("%d,\"name\":\""), param);
      len += strlen(strcpy_PF(outBuf + len, decodedTelegram.prognrdescaddr));
      len += sprintf_P(outBuf + len, PSTR("\",\"value\": \"%s\",\"desc\": \""), decodedTelegram.value);
      if (decodedTelegram.data_type == DT_ENUM && decodedTelegram.enumdescaddr) {
        len += strlen(strcpy_PF(outBuf + len, decodedTelegram.enumdescaddr));
      }
      len += sprintf_P(outBuf + len, PSTR("\",\"unit\": \"%s\",\"error\": %d"), decodedTelegram.unit, decodedTelegram.error);
      MQTTPayload.concat(outBuf);
    } else if (mqtt_mode == 2) { // Build the json doc on the fly
      char tbuf[20];
      sprintf_P(tbuf, PSTR("\"%d\":\""), param);
      MQTTPayload.concat(tbuf);
      if (decodedTelegram.type == VT_ENUM || decodedTelegram.type == VT_BIT || decodedTelegram.type == VT_ERRORCODE || decodedTelegram.type == VT_DATETIME) {
//---- we really need build_pvalstr(0) or we need decodedTelegram.value or decodedTelegram.enumdescaddr ? ----
        MQTTPayload.concat(String(build_pvalstr(0)));
      } else {
        MQTTPayload.concat(String(decodedTelegram.value));
      }
      MQTTPayload.concat(F("\""));
    } else { //plain text
      if (decodedTelegram.type == VT_ENUM || decodedTelegram.type == VT_BIT || decodedTelegram.type == VT_ERRORCODE || decodedTelegram.type == VT_DATETIME){
//---- we really need build_pvalstr(0) or we need decodedTelegram.value or decodedTelegram.enumdescaddr ? ----
        MQTTPubSubClient->publish(MQTTTopic.c_str(), build_pvalstr(0));
      }
      else
        MQTTPubSubClient->publish(MQTTTopic.c_str(), decodedTelegram.value);
    }
  }
  // End of mqtt if loop so close off the json and publish
  if (mqtt_mode == 2 || mqtt_mode == 3) {
    // Close the json doc off
    if(mqtt_mode == 2)
      MQTTPayload.concat(F("}}}"));
    else
      MQTTPayload.concat(F("}}"));
    // debugging..
    printToDebug(PSTR("Output topic: "));
    printToDebug(MQTTTopic.c_str());
    printToDebug(PSTR("\r\nPayload Output : "));
    printToDebug(MQTTPayload.c_str());
    writelnToDebug();
    // Now publish the json payload only once
    MQTTPubSubClient->publish(MQTTTopic.c_str(), MQTTPayload.c_str());
  } 
}
#endif

//Luposoft: Funktionen mqtt_connect
/*  Function: mqtt_connect()
 *  Does:     connect to mqtt broker

 * Pass parameters:
 *  none
 * Parameters passed back:
 *  none
 * Function value returned:
 *  boolean
 * Global resources used:
 *  Serial instance
 *  Ethernet instance
 *  MQTT instance
 * *************************************************************** */
#ifdef MQTT
boolean mqtt_connect()
{
  char* MQTTUser = NULL;
  if(MQTTUsername[0])
    MQTTUser = MQTTUsername;
  const char* MQTTPass = NULL;
  if(MQTTPassword[0])
    MQTTPass = MQTTPassword;
  if(MQTTPubSubClient == NULL)
  {
    mqtt_client= new ComClient();
    uint16_t bufsize;
    MQTTPubSubClient = new PubSubClient(mqtt_client[0]);
    switch(mqtt_mode){
      case 3: bufsize = 1024; break;
      case 2: bufsize = 512; break;
      case 1: bufsize = 128; break;
      default: bufsize = 32; break;
    }
    MQTTPubSubClient->setBufferSize(bufsize);
  }
  if (!MQTTPubSubClient->connected())
  {
    IPAddress MQTTBroker(mqtt_broker_ip_addr[0], mqtt_broker_ip_addr[1], mqtt_broker_ip_addr[2], mqtt_broker_ip_addr[3]);
    MQTTPubSubClient->setServer(MQTTBroker, 1883);
    int retries = 0;
    while (!MQTTPubSubClient->connected() && retries < 3)
    {
      MQTTPubSubClient->connect(PSTR("BSB-LAN"), MQTTUser, MQTTPass);
      retries++;
      if (!MQTTPubSubClient->connected())
      {
        delay(1000);
        printlnToDebug(PSTR("Failed to connect to MQTT broker, retrying..."));
      }
      else
      {
        printlnToDebug(PSTR("Connect to MQTT broker"));
        const char* mqtt_subscr;
        if (MQTTTopicPrefix[0]) {mqtt_subscr = MQTTTopicPrefix;}else {mqtt_subscr="fromBroker";}
        MQTTPubSubClient->subscribe(mqtt_subscr);   //Luposoft: set the topic listen to
        MQTTPubSubClient->setKeepAlive(120);       //Luposoft: just for savety
        MQTTPubSubClient->setCallback(mqtt_callback);  //Luposoft: set to function is called when incoming message
        return true;
      }
    }
  }
  else
  {
    return true;
  }
return false;
}
#endif
//Luposoft: Funktionen mqtt_callback
/*  Function: mqtt_callback()
 *  Does:     will call by MQTTPubSubClient.loop() when incomming mqtt-message from broker
 *            Example: set <mqtt2Server> publish <MQTTTopicPrefix> S700=1
              send command to heater and return an acknowledge to broker
 * Pass parameters:
 *  topic,payload,length
 * Parameters passed back:
 *  none
 * Function value returned:
 *  none
 * Global resources used:
 *  Serial instance
 *  Ethernet instance
 * *************************************************************** */
#ifdef MQTT
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  //boolean setcmd;
  printlnToDebug(PSTR("##MQTT#############################"));
  printToDebug(PSTR("mqtt-message arrived ["));
  printToDebug(topic);
  printlnToDebug(PSTR("] "));
  char C_value[24];
  strcpy_P(C_value, PSTR("ACK_"));   //dukess
  char firstsign;
  firstsign=' ';
  switch ((char)payload[0]) {
    case 'I':{firstsign='I';printToDebug(PSTR("I"));break;}
    case 'S':{firstsign='S';printToDebug(PSTR("S"));break;}
  }
  //buffer overflow protection    //dukess
  if(length > sizeof(C_value) - 4) {
    length = sizeof(C_value) - 4;
    printlnToDebug(PSTR("payload too big"));
  }
  for (unsigned int i=0;i<length;i++) {
    C_value[i+4]=char(payload[i]);
  }
  C_value[length+4]='\0';
  char*C_payload=C_value+ 4;  //dukess
  if(firstsign!=' ') C_payload++; //skip I/S
  int I_line=atoi(C_payload);
  String mqtt_Topic;
  if(MQTTTopicPrefix[0]) {
    mqtt_Topic = MQTTTopicPrefix;
    mqtt_Topic.concat(F("/"));
  }
  else mqtt_Topic = "BSB-LAN/";
  mqtt_Topic.concat(F("MQTT"));
  MQTTPubSubClient->publish(mqtt_Topic.c_str(), C_value);
  
  if (firstsign==' ') { //query
    printFmtToDebug(PSTR("%d \r\n"), I_line);
    mqtt_sendtoBroker(I_line);  //send mqtt-message
  }
  else { //command to heater
    C_payload=strchr(C_payload,'=');
    C_payload++;
    printFmtToDebug(PSTR("%d=%s \r\n"), I_line, C_payload);
    set(I_line,C_payload,firstsign=='S');  //command to heater
    mqtt_sendtoBroker(I_line);  //send mqtt-message after command
  }
  printlnToDebug(PSTR("##MQTT#############################"));
}
#endif


#ifdef WIFI
void printWifiStatus()
{
  // print the SSID of the network you're attached to
//  printFmtToDebug(PSTR("SSID: %s\r\n"), WiFi.SSID());
  printFmtToDebug(PSTR("SSID: %s\r\n"), WiFi.SSID());
  // print your WiFi shield's IP address
  IPAddress t = WiFi.localIP();
  printFmtToDebug(PSTR("IP Address: %d.%d.%d.%d\r\n"), t[0], t[1], t[2], t[3]);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  printFmtToDebug(PSTR("Signal strength (RSSI): %l dBm\r\n"), rssi);
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
#ifdef BtSerial
  SerialOutput = &Serial2;
  Serial2.begin(115200, SERIAL_8N1); // hardware serial interface #2
#else
  SerialOutput = &Serial;
  Serial.begin(115200, SERIAL_8N1); // hardware serial interface #0
#endif

  decodedTelegram.telegramDump = NULL;
  pinMode(EEPROM_ERASING_PIN, INPUT_PULLUP);
#if defined(EEPROM_ERASING_GND_PIN)
  pinMode(EEPROM_ERASING_GND_PIN, OUTPUT);
#endif

  SerialOutput->println(F("READY"));

  #if defined(ARM) || defined(ESP32)
  Wire.begin();
  if (!EEPROM.ready()) {
    EEPROM_ready = false;
    SerialOutput->println(F("EEPROM not ready"));
  }
  pinMode(19, INPUT);
  #endif

  pinMode(LED_BUILTIN, OUTPUT);

//EEPROM erasing when button on pin EEPROM_ERASING_PIN is pressed
  if (!digitalRead(EEPROM_ERASING_PIN)) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    clearEEPROM();
    internalLEDBlinking(125, 16); //pause 4 sec for user informing and button release
  }

  //Read config parameters from EEPROM

  //Read "Header"
  initConfigTable(0);
#ifdef MAX_CUL
  registerConfigVariable(CF_MAX_DEVICES, (byte *)max_device_list);
  registerConfigVariable(CF_MAX_DEVADDR, (byte *)max_devices);
#endif
  registerConfigVariable(CF_PPS_VALUES, (byte *)pps_values);
#ifdef CONFIG_IN_EEPROM
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
  registerConfigVariable(CF_LOGAVERAGES, (byte *)&logAverageValues);
  registerConfigVariable(CF_AVERAGESLIST, (byte *)avg_parameters);
  registerConfigVariable(CF_LOGCURRVALUES, (byte *)&logCurrentValues);
  registerConfigVariable(CF_LOGCURRINTERVAL, (byte *)&log_interval);
  registerConfigVariable(CF_CURRVALUESLIST, (byte *)log_parameters);
#ifdef WEBCONFIG
  registerConfigVariable(CF_ROOM_DEVICE, (byte *)&pps_values[PPS_QTP]);
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
  registerConfigVariable(CF_BASICAUTH, (byte *)USER_PASS_B64);
  registerConfigVariable(CF_ONEWIREBUS, (byte *)&One_Wire_Pin);
  registerConfigVariable(CF_DHTBUS, (byte *)DHT_Pins);
  registerConfigVariable(CF_IPWE, (byte *)&enable_ipwe);
  registerConfigVariable(CF_IPWEVALUESLIST, (byte *)ipwe_parameters);
  registerConfigVariable(CF_MAX, (byte *)&enable_max_cul);
  registerConfigVariable(CF_MAX_IPADDRESS, (byte *)max_cul_ip_addr);
  registerConfigVariable(CF_MQTT, (byte *)&mqtt_mode);
  registerConfigVariable(CF_MQTT_IPADDRESS, (byte *)mqtt_broker_ip_addr);
  registerConfigVariable(CF_MQTT_USERNAME, (byte *)MQTTUsername);
  registerConfigVariable(CF_MQTT_PASSWORD, (byte *)MQTTPassword);
  registerConfigVariable(CF_MQTT_TOPIC, (byte *)MQTTTopicPrefix);
  registerConfigVariable(CF_MQTT_DEVICE, (byte *)MQTTDeviceID);
  if(DEFAULT_FLAG & FL_SW_CTL_RONLY) {
    registerConfigVariable(CF_WRITEMODE, (byte *)&programWriteMode);
  }
  registerConfigVariable(CF_DEBUG, (byte *)&debug_mode);
  registerConfigVariable(CF_VERBOSE, (byte *)&verbose);
  registerConfigVariable(CF_MONITOR, (byte *)&monitor);
  registerConfigVariable(CF_CHECKUPDATE, (byte *)&enable_version_check);
  registerConfigVariable(CF_RGT1_SENSOR_ID, (byte *)&rgte_sensorid[0][0]);
  registerConfigVariable(CF_RGT2_SENSOR_ID, (byte *)&rgte_sensorid[1][0]);
  registerConfigVariable(CF_RGT3_SENSOR_ID, (byte *)&rgte_sensorid[2][0]);
  registerConfigVariable(CF_TWW_PUSH_PIN_ID, (byte *)&button_on_pin[0]);
  registerConfigVariable(CF_RGT1_PRES_PIN_ID, (byte *)&button_on_pin[1]);
  registerConfigVariable(CF_RGT2_PRES_PIN_ID, (byte *)&button_on_pin[2]);
  registerConfigVariable(CF_RGT3_PRES_PIN_ID, (byte *)&button_on_pin[3]);

#endif

  readFromEEPROM(CF_PPS_VALUES);
  byte UseEEPROM_in_config_h = UseEEPROM;
  if (UseEEPROM) { //Read EEPROM when it allowed from config file
    SerialOutput->println(F("Reading EEPROM"));
    readFromEEPROM(CF_USEEEPROM);
    readFromEEPROM(CF_VERSION);
  }
  if (UseEEPROM == 0x96) {//Read EEPROM when EEPROM contain magic byte (stored configuration)
    readFromEEPROM(CF_CRC32);
    if (crc == initConfigTable(EEPROMversion)) {
  //read parameters
      for(uint8_t i = 0; i < sizeof(config)/sizeof(config[0]); i++){
//        SerialOutput->print(F(" Read parameter # ")); SerialOutput->println(i);
  //read parameter if it version is non-zero
#if defined(__AVR__)
        uint8_t version = pgm_read_byte_far(pgm_get_far_address(config[0].version) + i * sizeof(config[0]));
        if(version > 0 && version <= EEPROMversion)
          readFromEEPROM(pgm_read_byte_far(pgm_get_far_address(config[0].id) + i * sizeof(config[0])));
#else
        if(config[i].version > 0 && config[i].version <= EEPROMversion) readFromEEPROM(config[i].id);
#endif
      }
    } else SerialOutput->println(F("EEPROM schema CRC mismatch"));
  } else {
    SerialOutput->println(F("Using settings from config file"));
    initConfigTable(EEPROMversion); //Need to init config table in any case because we can change opinion and can enable store config in EEPROM.
  }
  SerialOutput->println(F("Reading done."));

  //calculate maximal version
  uint8_t maxconfversion = 0;
  for(uint8_t i = 0; i < sizeof(config)/sizeof(config[0]); i++){
  #if defined(__AVR__)
    uint8_t version = pgm_read_byte_far(pgm_get_far_address(config[0].version) + i * sizeof(config[0]));
    if(version > maxconfversion) maxconfversion = version;
  #else
    if(config[i].version > maxconfversion) maxconfversion = config[i].version;
  #endif
  }
  SerialOutput->print(F("EEPROM schema v."));
  SerialOutput->print(EEPROMversion);
  SerialOutput->print(F(" Program schema v."));
  SerialOutput->println(maxconfversion);

  if (maxconfversion != EEPROMversion) { //Update config "Schema" in EEPROM
    crc = initConfigTable(maxconfversion); //store new CRC32
    EEPROMversion = maxconfversion; //store new version
    if (UseEEPROM_in_config_h == 0x01) {//Update EEPROM when config file contain UseEEPROM = 1
      if(UseEEPROM != 0x69 && UseEEPROM != 0x96) UseEEPROM = 0x96;
      SerialOutput->println(F("Update EEPROM schema"));
      for(uint8_t i = 0; i < CF_LAST_OPTION; i++){
        //do not write here MAX! settings
        if(i != CF_MAX_DEVICES && i != CF_MAX_DEVADDR) {
          writeToEEPROM(i);
//          SerialOutput->print(F("Write option # ")); SerialOutput->println(i);
        }
      }
    }
  }

  unregisterConfigVariable(CF_VERSION);
  unregisterConfigVariable(CF_CRC32);
#endif

  byte save_debug_mode = debug_mode; //save debug_mode until setup is end.
  debug_mode = 1; //force using Serial debug until setup is end.

  for(uint8_t i = 0; i < CF_LAST_OPTION; i++){
    printFmtToDebug(PSTR("Address EEPROM option %d: %d\r\n"), i, getEEPROMaddress(i));
  }

  if(save_debug_mode == 2) printToDebug(PSTR("Logging output to Telnet\r\n"));
  printFmtToDebug(PSTR("Size of cmdtbl1: %d\r\n"),sizeof(cmdtbl1));
  printFmtToDebug(PSTR("Size of cmdtbl2: %d\r\n"),sizeof(cmdtbl2));
  printFmtToDebug(PSTR("Size of cmdtbl3: %d\r\n"),sizeof(cmdtbl3));
  printFmtToDebug(PSTR("free RAM: %d\r\n"), freeRam());

  while (SerialOutput->available()) { // UART buffer often still contains characters after reset if power is not cut
    printFmtToDebug(PSTR("%c"), SerialOutput->read());
  }

// BSB/LPB/PPS bus init
  byte temp_bus_pins[2];
  if (bus_pins[0] && bus_pins[1]) {
    temp_bus_pins[0] = bus_pins[0];
    temp_bus_pins[1] = bus_pins[1];
  } else {
#if defined(__AVR__) // Mega2560
    // SoftwareSerial
    temp_bus_pins[0] = 68;
    temp_bus_pins[1] = 69;
#elif defined(ESP32)
    temp_bus_pins[0] = 16;
    temp_bus_pins[1] = 17;
#else  // Due
    // HardwareSerial
    temp_bus_pins[0] = 19;
    temp_bus_pins[1] = 18;
#endif
  }
  bus = new BSB(temp_bus_pins[0], temp_bus_pins[1]);
  setBusType(); //set BSB/LPB/PPS mode
  bus->enableInterface();

#ifdef ONE_WIRE_BUS
  if (enableOneWireBus) {
    printToDebug(PSTR("Init One Wire bus...\r\n"));
    // Setup a oneWire instance to communicate with any OneWire devices
    oneWire = new OneWire(One_Wire_Pin);
    // Pass our oneWire reference to Dallas Temperature.
    sensors = new DallasTemperature(oneWire);
    // check ds18b20 sensors
    sensors->begin();
    numSensors=sensors->getDeviceCount();
    printFmtToDebug(PSTR("numSensors: %d\r\n"), numSensors);
  }
#endif

#ifdef BME280
    printToDebug(PSTR("Init BME280 sensor(s)...\r\n"));
    for(uint8_t f = 0; f < sizeof(bme)/sizeof(bme[0]); f++){
      bme[f].parameter.communication = 0;                    //I2C communication for Sensor
      bme[f].parameter.I2CAddress = 0x76 + f;                    //I2C Address for Sensor
      bme[f].parameter.sensorMode = 0b11;                    //Setup Sensor mode
      bme[f].parameter.IIRfilter = 0b100;                   //IIR Filter for Sensor
      bme[f].parameter.humidOversampling = 0b101;            //Humidity Oversampling for Sensor
      bme[f].parameter.tempOversampling = 0b101;              //Temperature Oversampling for Sensor
      bme[f].parameter.pressOversampling = 0b101;             //Pressure Oversampling for Sensor
      bme[f].parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa
      bme[f].parameter.tempOutsideCelsius = 15;               //default value of 15°C
      bme[f].parameter.tempOutsideFahrenheit = 59;            //default value of 59°F
      printFmtToDebug(PSTR("Sensor with address %x "), bme[f].parameter.I2CAddress);
      if(bme[f].init() != 0x60){
        printToDebug(PSTR("NOT "));
      }
      printToDebug(PSTR("found\r\n"));
    }
#endif

/*  printlnToDebug(PSTR("Reading EEPROM..."));
  for (int i=PPS_TWS;i<=PPS_BRS;i++) {
    uint16_t f=0;
    if (EEPROM_ready) {
      EEPROM.get(sizeof(uint16_t)*i, f);
    }
    if (f > 0 && f < 0xFFFF && i != PPS_RTI) {
      printFmtToDebug(PSTR("Reading %u from EEPROM slot %d\r\n"), f, i);

      pps_values[i] = f;
    }
  }
*/

/*
  for (int i=PPS_TWS;i<=PPS_BRS;i++) {
    if(pps_values[i] == (int16_t)0xFFFF) pps_values[i] = 0;
    if (pps_values[i] > 0 && pps_values[i]< (int16_t)0xFFFF && i != PPS_RTI) {
      printFmtToDebug(PSTR("Slot %d, value: %u\r\n"), i, pps_values[i]);
    }
  }
*/

  printToDebug(PSTR("PPS settings:\r\n"));
  uint32_t temp_c = 0;
  int temp_idx = findLine(15000,0,&temp_c);
  for (int i=0; i<PPS_ANZ; i++) {
    int l = findLine(15000+i,temp_idx+i,&temp_c);
    if (l==-1) continue;
//    uint8_t flags=get_cmdtbl_flags(l);
//    if ((flags & FL_EEPROM) == FL_EEPROM) {   // Testing for FL_EEPROM is not enough because volatile parameters would still be set to 0xFFFF upon reading from EEPROM. FL_VOLATILE flag would help, but in the end, there is no case where any of these values could/should be 0xFFFF, so we can safely assume that all 0xFFFF values should be set to 0.
      if(pps_values[i] == (int16_t)0xFFFF) {
        pps_values[i] = 0;
      }
      if (pps_values[i] > 0 && pps_values[i]< (int16_t)0xFFFF) {
        printFmtToDebug(PSTR("Slot %d, value: %u\r\n"), i, pps_values[i]);
      }
//    }
  }
  if(pps_values[PPS_QTP] == 0 || UseEEPROM != 0x96) {
    pps_values[PPS_QTP] = QAA_TYPE;
    writeToEEPROM(CF_ROOM_DEVICE);
  }
  if(pps_values[PPS_RTI] != 0) {
    pps_values[PPS_RTI] = 0;
  }

#if defined LOGGER || defined WEBSERVER
  // disable w5100 while setting up SD
#ifndef ESP32
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
#endif
  printToDebug(PSTR("Starting SD.."));
#if defined(__AVR__)
  if(!SD.begin(4)) printToDebug(PSTR("failed\r\n"));
#else
  if(!SD.begin(4, SPI_DIV3_SPEED)) printToDebug(PSTR("failed\r\n")); // change SPI_DIV3_SPEED to SPI_HALF_SPEED if you are still having problems getting your SD card detected
#endif
  else printToDebug(PSTR("ok\r\n"));

#else
  // enable w5100 SPI
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);

  // disable SD Card
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
#endif

#ifdef WIFI
  int status = WL_IDLE_STATUS;
  #ifndef ESP32
  WiFi.init(WIFI_SPI_SS_PIN);     // SS signal is on Due pin 12

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present. Cannot continue.\r\n"));
    // don't continue
    while (true);
  }

  if (!WiFi.checkProtocolVersion()) {
    Serial.println(F("Protocol version mismatch. Please upgrade the WiFiSpiESP firmware of the ESP."));
    // don't continue:
    while (true);
  }

  #endif
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
#ifndef WIFI
    Ethernet.begin(mac, ip, dnsserver, gateway, subnet); //Static
  } else {
    Ethernet.begin(mac); //DHCP
  }
  SerialOutput->println(Ethernet.localIP());
  SerialOutput->println(Ethernet.subnetMask());
  SerialOutput->println(Ethernet.gatewayIP());
#else
    WiFi.config(ip, dnsserver, gateway, subnet);
  }

#ifdef ESP32
  WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
  WiFi.mode(WIFI_STA); //init wifi mode
  // Workaround for problems connecting to wireless network on some ESP32, see here: https://github.com/espressif/arduino-esp32/issues/2501#issuecomment-731618196
  printToDebug(PSTR("Setting up WiFi interface"));
  WiFi.begin();
  while (WiFi.status() == WL_DISCONNECTED) {
    delay(100);
    printToDebug(PSTR("."));
  }
  writelnToDebug();
#endif
  WiFi.begin(wifi_ssid, wifi_pass);
  // attempt to connect to WiFi network
  printFmtToDebug(PSTR("Attempting to connect to WPA SSID: %s"), wifi_ssid);
  while ( status != WL_CONNECTED) {
    printToDebug(PSTR("."));
    // Connect to WPA/WPA2 network
    status = WiFi.status() ;
    delay(1000);
  }
  // you're connected now, so print out the data
  printToDebug(PSTR("\r\nYou're connected to the network:\r\n"));
#if defined(__arm__) || defined(ESP32)
  WiFi.macAddress(mac);  // overwrite mac[] with actual MAC address of ESP32 or WiFiSpi connected ESP
#endif
  printWifiStatus();
#endif

  server = new ComServer(HTTPPort);
  if(save_debug_mode == 2) telnetServer = new ComServer(23);

#if defined LOGGER || defined WEBSERVER
  digitalWrite(10,HIGH);
#endif

  printToDebug(PSTR("Waiting 3 seconds to give Ethernet shield time to get ready...\r\n"));
  // turn the LED on until Ethernet shield is ready and freeClusterCount is over
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)

  long diff = 2200; // + 1 sec with decoration
  #if defined LOGGER || defined WEBSERVER
  printToDebug(PSTR("Calculating free space on SD..."));
  uint32_t m = millis();
  uint32_t volFree = SD.vol()->freeClusterCount();
  uint32_t fs = (uint32_t)(volFree*SD.vol()->blocksPerCluster()/2048);
  printFmtToDebug(PSTR("%d MB free\r\n"), fs);
  diff -= (millis() - m); //3 sec - delay
  #endif
  if(diff > 0)  delay(diff);

  //decoration: double blink by LED before start. wait for a second
  internalLEDBlinking(250, 2);
  //end of decoration

  printlnToDebug(PSTR("Start network services"));
  server->begin();

  if(save_debug_mode == 2)
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
      DebugOutput.print(F("\t"));
      DebugOutput.println(temp_offset1, HEX);
    }
  }
*/

// initialize average calculation
#ifdef AVERAGES
  for (int i=0; i<numAverages; i++) {
    avgValues[i] = 0;
    avgValues_Old[i] = -9999;
    avgValues_Current[i] = 0;
  }
#endif

#ifdef WATCH_SOCKETS
  unsigned long thisTime = millis();

  for(int i=0;i<MAX_SOCK_NUM;i++) {
    connectTime[i] = thisTime;
  }
#endif

#ifdef LOGGER

// restore average
#ifdef AVERAGES
  if (SD.exists(averagesFileName)) {
    File avgfile = SD.open(averagesFileName, FILE_READ);
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
        if (isnan(avgValues_Old[i])) {
          avgValues_Old[i] = -9999;
        }

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

  if (!SD.exists(datalogFileName)) {
    createdatalogFileAndWriteHeader();
  }
#endif

  if (bus->getBusType() != BUS_PPS) {
// receive inital date/time from heating system
    SetDateTime();

// receive device family (Gerätefamilie) and device variant (Gerätevariant) from heating system
    SetDevId();
  }

#ifdef MAX_CUL
  if (enable_max_cul) {
    UpdateMaxDeviceList();
    connectToMaxCul();
  }
#endif

  printlnToDebug((char *)destinationServer); // delete it when destinationServer will be used

#ifdef MDNS_HOSTNAME
#if defined(ESP32)
  MDNS.begin(MDNS_HOSTNAME);
  MDNS.addService("http", "tcp", 80);
  MDNS.addService("BSB-LAN web service._http", "tcp", 80);
#else
#ifdef WIFI
  mdns.begin(WiFi.localIP(), PSTR(MDNS_HOSTNAME));
#else
  mdns.begin(Ethernet.localIP(), PSTR(MDNS_HOSTNAME));
#endif
  mdns.addServiceRecord(PSTR("BSB-LAN web service._http"), HTTPPort, MDNSServiceTCP);
#endif
#endif

// Set up web-based over-the-air updates for ESP32
#if defined(ESP32) && defined(ENABLE_ESP32_OTA)
  update_server.on("/", HTTP_GET, []() {
    update_server.sendHeader("Connection", "close");
    update_server.send(200, "text/html", serverIndex);
  });
  update_server.on("/update", HTTP_POST, []() {
    update_server.sendHeader("Connection", "close");
    update_server.send(200, "text/plain", (Update.hasError()) ? "Failed" : "Success");
    delay(1000);
    ESP.restart();
  }, []() {
    HTTPUpload& upload = update_server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      printlnToDebug(PSTR("Updating ESP32 firmware..."));
      uint32_t maxSketchSpace = 0x140000;
      if (!Update.begin(maxSketchSpace)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        printlnToDebug(PSTR("Update success, rebooting..."));
      } else {
        Update.printError(Serial);
      }
    }
    yield();
  });
  update_server.begin();
  printlnToDebug(PSTR("Update Server started on port 8080."));
#endif

#ifdef CUSTOM_COMMANDS
#include "BSB_LAN_custom_setup.h"
#endif

#ifdef BUTTONS
  if(button_on_pin[0]){
    pinMode(button_on_pin[0], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(button_on_pin[0]), interruptHandlerTWWPush, FALLING); //TWW push button
  }
  if(button_on_pin[1]){
    pinMode(button_on_pin[1], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(button_on_pin[1]), interruptHandlerPresenceROOM1, FALLING); //Presence ROOM 1 button
  }
  if(button_on_pin[2]){
    pinMode(button_on_pin[2], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(button_on_pin[2]), interruptHandlerPresenceROOM2, FALLING); //Presence ROOM 2 button
  }
  if(button_on_pin[3]){
    pinMode(button_on_pin[3], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(button_on_pin[3]), interruptHandlerPresenceROOM3, FALLING); //Presence ROOM 3 button
  }
#endif

  printlnToDebug(PSTR("Setup complete"));
  debug_mode = save_debug_mode; //restore actual debug mode
}
