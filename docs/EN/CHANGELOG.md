#ChangeLog#

##Current Master##

- **ATTENTION: BREAKING CHANGE!** Streamlined topic structure for MQTT. New strucuture adds `/status` for querying a parameter, `/set` for SETting a parameter, `/inf` for sending data as INF telegram and `/poll` to force BSB-LAN to send an update of that parameter value to the broker. If you are using MQTT auto-discovery, ideally, calling `/M1` should update these changes. However, if you are using your own configurations, you'll have to make adjustments here.
- **ATTENTION: BREAKING CHANGE!** When using JSON settings for MQTT, previously all messages were written to the `BSB-LAN/json` and thus basically immediately overwritten when logging several parameters. Now this setting only determines the format (and not format and topic) of the data that is written into `/status` of each parameter. For auto-discovery, plain text remains the only valid choice.
- **ATTENTION: BREAKING CHANGE** The acknowledgement message sent by BSB-LAN to the `MQTT` topic has been removed. Instead, QoS for publishing messages has been set to level 1.
- **ATTENTION: BREAKING CHANGE:** Log configuration values have changed. However, only users that have logged to UDP are affected and will have to adjust their settings.
- **ATTENTION:** `/JK=ALL` now lists all categories of all devices in LPB systems with more than one device. Use `dev_fam` (device family), `dev_var` (device variant), `dev_id` (destination device ID) and `dev_name` (device model) elements to sort and identify which category applies to the current destination device. 
- Added setting to only publish log parameters to MQTT. Forcing MQTT updates via /poll topic are still possible.
- Added state_class for non cumulative sensors in MQTT auto-discovery
- Updated the room unit emulation in `custom_functions` to work with version 4.x.
- Bugfix for VT_ENERGY, added new data type VT_ENERGY10 and VT_ENERGY10_N
- Disabling parameters can now be done both with an empty value as well as by sending `---`. Sending an empty value is still possible, but is depracated and will be removed at some later time.
- BSB-LAN now scans the BSB/LPB bus during startup (and later periodically, if not connected to heating system) for other devices on the bus. This significantly reduces access times later on for systems with more than one device on the bus.
- New version from new repo of PubSubClient. Hopefully with this version, disconnects will be greatly reduced.
- French and German translations of the manual added, special thanks to GitHub user @plauwers for this!
- Numerous bugfixes, especially for the JSON API

##Version 4.1##
**06.11.2024**  

- **ATTENTION: BREAKING CHANGE!** Changed topic structure for MQTT. This means that all existing MQTT entities in your home-automation system will have to be adjusted or created anew! The new structure now is `BSB-LAN/<device id>/<category id>/<parameter number>`.
- **ATTENTION: BREAKING CHANGE!** Changed unique_id for MQTT auto-discovery. This means that all MQTT entities that have been created via auto-discovery will have to be created anew!
- **ATTENTION:** Configuration options `fixed_device_family` and `fixed_device_variant` have been removed since they no longer work for device-specific parameter lists. If your heating system is off when turning on the microcontroller, BSB-LAN will try to acquire the details every 60 seconds.
- **ATTENTION:** Change of configuration options results in new EEPROM layout, therefore EEPROM will be reinitialized based on configuration of `BSB_LAN_config.h`.
- MQTT auto-discovery now works for all devices, not only device ID 0. Use `/M1!<x>` or `/M0!<x>` to create/remove entities for device ID `<x>`.
- Changed MQTT auto-discovery messages' flag to "retain" so that parameters remain available after reboot of Home Assistant.

##Version 4.0##
**01.11.2024**  

- **ATTENTION: BREAKING CHANGE!** Room temperature parameter 10000, 10001 and 10002 must now have the additional flag `FL_SPECIAL_INF`, otherwise setting temperature will not work!
- **ATTENTION: BREAKING CHANGE!** Outside temperature simulation parameter 10017 must have `FL_SPECIAL_INF` flag removed, otherwise setting temperature will not work!
- **ATTENTION: BREAKING CHANGE!** Room temperature parameter 10000, 10001 and 10002 for Weishaupt heaters (device families 49, 50, 51 and 59) must now have `FL_SPECIAL_INF` flag removd, otherwise setting temperature will not work!
- **ATTENTION: BREAKING CHANGE!** URL commands `/U` (dislpay user-defined variables) and `/X` (display MAX! values) have been removed as these values can now be accessed via parameters 20000++
- **ATTENTION: BREAKING CHANGE!** PPS time program parameters (15050-15091) have been streamlined with BSB/LPB time program parameters, resulting in only one parameter per day (instead of six), covering three switch points (start and end) per parameter.
- **ATTENTION:** For ESP32, BSB-LAN requires ESP32 framework version 3.0.x - please look out for errors or strange behaviour (1-Wire sensors are still not tested) as well as any other kind of strange behaviour/crashes.
- **ATTENTION:** New configuration options in `BSB_LAN_config.h` - please update your existing configuration files! Web-based configuration will be overwritten with config file settings due to change in EEPROM layout! 
- **ATTENTION:** New manual URL: https://docs.bsb-lan.de/
- BUTTONS and `RGT_EMULATION` have been moved from main code to `custom_functions` library. To continue using them, make use of `BSB_LAN_custom_*.h` files and activate `CUSTOM_COMMANDS` definement.
- Most configuration definements removed from `BSB_LAN_config.h`. Almost all functionality can now be configured without reflashing.
- BSB-LAN now supports MQTT auto discovery (supported e.g. by Home Assistant). To create devices, call URL command `/M1`, to remove them call `/M0` 
- **ATTENTION:** MQTT auto discovery creates a general switch for the BSB-LAN device in Home Assistant. This switch will immediately write all parameters with the values stored in Home Assistant. DO NOT USE THIS SWITCH unless you REALLY know what it does!
- "Set" button in webinterface now also works with non-default destination devices (i.e. 1 instead of 0)
- Queried/set parameters are now forwarded to the MQTT broker (if MQTT is enabled)
- Previously used `/M1` and `/M0` for toggling monitor function have been removed since it can now be accessed via the configuration in the webinterface.
- Listing categories with `/K` now also works with destination device (e.g. /K!1 for destination device 1, default is 0).
- Important bugfix for OTA update: Previous versions had a hard limit on file size which newer heating systems with several hundred parameters hit, so no OTA update was possible. This is now fixed, but affected users will have to make a USB-based update one more time.
- 1-Wire- and DHT-sensors are now be disabled with value -1 instead of 0. In web interface, an empty field is also accepted.
- MQTTTopicPrefix is no longer optional, "fromBroker" topic removed (formerly used to send commands to BSB-LAN via MQTT)
- Using the 24h averages functionality no longer requires the use of an SD card. SD card will only be used to store averages if interval logging to SD card is active.
- New PPS room unit variant for RVD130, which increases high nibble of magic byte at every transaction.
- Polling current time from NTP server is active by default. Deactivate by setting `ntp_server` to empty string.
- New parameter flag `FL_NOSWAP_QUR` for parameters that do not swap the first two bytes of command ID in QUR telegram
- New parameter flag `FL_FORCE_INF` for parameters from which we are certain they only work with INF (such as room temperature). Will force an INF telegram even if `/S` is used to set the parameter (allows setting room temperature via web interface)
- BSB-LAN logo watermark in log graph display (DE-cr)
- Binary ENUMs (yes/no, on/off etc.) now return either 0 or 1 when queried, not - as is the case with some heating systems - 0 or 255. Setting any value from 1 to 255 is still possible. 
- Fixed a breaking bug in PPS that prevented running properly in active/room unit mode.
- Fixed bug (or, based on perspective, reduced security) that prevented issuing commands via serial/telnet console when HTTP authentication was active
- Various bugfixes, among others logging of bus telegrams on storage device.
- New OneWireNg library version
- This release has been supported by the following sponsors: Erich Scheilko

##Version 3.3##
**12.03.2024**  

- **ATTENTION:** New configuration options in `BSB_LAN_config.h` - please update your existing configuration files!
- ESP32: Support for receiving date and time via NTP instead of taking it from the heater.
- MQTT broker setting now accepts domain names as well as IP addresses. An optional port can be added after a trailing colon, e.g. broker.my-domain.com:1884. Otherwise defaults to 1883.
- ESP32 NodeMCU: Support for optional additional SD card adapter. SPI pins can be configured in `BSB_LAN_config.h`, defaulting to standard SPI pins 5, 18, 19 and 23.
- ESP32: Switching between log storage device (SD card / internal flash) can now be done in the web interface.
- ESP32: Create temporary WiFi AP in case Ethernet connection fails
- ESP32 NodeMCU: EEPROM clear pin has changed from 18 to 21 in order not to collide with SPI SD card adapters.
- This release has been supported by the following GitHub sponsors: jsimon3

##Version 3.2##
**15.11.2023**  

- **ATTENTION:** In `BSB_LAN_config.h`, new layout of `log_parameters`, `avg_parameters` and `ipwe_parameters` now written in curly brackets and different size (40 instead of 80) and type (`parameter` instead of `float`). Please update your `BSB_LAN_config.h` accordingly to prevent errors!
- Added configuration file versioning checks to prevent the use of outdated configuration files with newer software versions.
- Variable `esp32_save_energy` now defaults to false because it only seems to make sense when using LAN connection or if you use WiFi and can live with the performance impact.
- Added folder `custom_functions` where code examples for useful functions will be collected which are nevertheless too specific to be added to BSB-LAN's core code.
- Added custom function example for mapping DS18B20 sensors to fixed custom floats parameters
- This release has been supported by the following GitHub Sponsors: BraweProg, fdobrovolny, Harald

##Version 3.1##
**04.06.2023**  

- **ATTENTION:** For ESP32 devices using internal flash for log storage: Filesystem was switched from SPIFFS to LittleFS. Download important log data before updating!
- **ATTENTION:** In `BSB_LAN_config.h`, the structure of `log_parameters`, `avg_parameters` and `ipwe_parameters` has changed and now includes the destination device on the bus!
- **ATTENTION:** New EEPROM schema may result in lost web-configuration settings when updating. Note your settings prior to updating!
- **ATTENTION:** New variable `esp32_save_energy` in `BSB_LAN_config.h` - update before compiling new version.
- **ATTENTION:** New variable bssid in `BSB_LAN_config.h` - defines a fixed BSSID address to connect to when using WiFi on ESP32.
- Parameters can now be queried from other devices on the bus using the ! notation also when logging (including MQTT) or using average or IPWE parameters
- Enable/disable power saving on ESP32. Saves 20% of energy, but can have impact on WiFi range and downloading speed of log files when using WiFi (LAN not affected)
- Improved performance and flash memory usage on ESP32 devices using internal flash for logging due to switch from SPIFFS to LittleFS
- To improve handling of large datalogs: date range selection in `/DG`, new url commands `/Da,b`, `/DA`, `/DB`, `/Dn`, `/DI` and `/DKn`
- This release has been supported by the following GitHub Sponsors: lapixo, nrobadey

##Version 3.0##
**16.03.2023**  

- **ATTENTION:** `BSB_LAN_custom_defs.h`.default needs to be renamed to `BSB_LAN_custom_defs.h` and only contains a very limited set of parameters by default. See the manual for getting device-specific parameter lists.
- Add new `/LN` URL command to force logging irrespective of current interval.
- Improved library checks: No need for ESP32 users to remove ArduinoMDNS and WiFiSpi folders anymore.
- New SdFat version 2 for Arduino Due
- New data type `VT_BINARY_ENUM`
- This release has been supported by the following GitHub Sponsors: Alex, DE-cr

##Version 2.2##
**01.11.2022**  

- **ATTENTION:** Several variables in `BSB_LAN_config.h`.default have changed their variable type, it's probably best to re-create your `BSB_LAN_config.h` from scratch.
- Parameter numbers are now floating point (i.e. XXXX.Y) because some parameters contain two different kinds of information. These are now shown in decimal increments of 0.1. You can still qurey the "main" parameter via XXXX (without .Y)
- Lots of bugfixes and new data types
- Device-specific parameter lists supported

##Version 2.1##
**30.07.2022**  

- Many new parameters for LMU64
- **ATTENTION:** New categories for LMU64 and RVD/RVP controllers due to their different numbering schemes. Will be filled over time. PPS and sensor categories have moved up by two.
- ESP32: OTA now uses system-wide HTTP AUTH authentication credentials
- Improved built-in chart display `/DG`, new configuration definement `#define USE_ADVANCED_PLOT_LOG_FILE` - thanks to Christian Ramharter
- Optional logging via UDP broadcast added (configurable, same parameters and format as in SD card logging)
- Lots of bugfixes

##Version 2.0##
**31.12.2021**  

- **ATTENTION:** LOTS of new functionalities, some of which break compatibility with previous versions, so be careful and read all the docs if you make the upgrade!
- **ATTENTION:** Added and reorganized PPS parameters, almost all parameter numbers have changed!
- **ATTENTION:** Change of EEPROM layout will lead to loading of default values from `BSB_LAN_config.h`! You need to write settings to EEPROM in configuration menu again!
- **ATTENTION:** Folder locations and filenames have been adjusted for easier installation! If you update your installation, please take note that the configuration is now in `BSB_LAN_config.h` (LAN in caps), and no longer in `BSB_lan_config.h` (lower-caps "lan")
- **ATTENTION:** HTTP-Authentication configuration has changed and now uses plain text instead of Base64 encoded strings!
- Thanks to GitHub user do13, this code now also compiles on a ESP32, tested on NodeMCU-ESP32, Olimex ESP32-POE and Olimex ESP32-EVB boards. ESP32 code uses SDK version 2.0.2, please take note when configuring Arduino IDE!
- OTA Updates now possible for ESP32-based devices
- Support for special PPS devices (based on DC225/Honeywell MCBA) added
- Webinterface allows for configuration of most settings without the need to re-flash, also split into basic and extended configuration
- Added better WiFi option for Arduinos through Jiri Bilek's WiFiSpi library, using an ESP8266-based microcontroller like Wemos D1 mini or LoLin NodeMCU. Older WiFi-via-Serial approach no longer supported.
- Added `MDNS_SUPPORT` definement in config so that BSB-LAN can be discovered through mDNS
- If BSB-LAN cannot connect to WiFi on ESP32, it will set up its own access point `BSB-LAN` with password `BSB-LPB-PPS-LAN` for 30 minutes. After that, it will reboot and try to connect again.
- New MQTT functions, including allowing any parameter to be set by an MQTT message and actively query any parameter once by sending an MQTT message
- Added support for BME280 sensors
- Setting a temporary destination address for querying parameters by adding `!x` (where `x` is the destination id), e.g. `/6224!10` to query the identification of the display unit
- URL commands `/A` `/B` `/T` and `/JA` have been removed as all sensors can now be accessed via parameter numbers 20000 and above as well as (currently) under new category K49.
- New categories added, subsequent categories have been shifted up
- HTTP Authentification now uses clear text username and password in configuration
- PPS users can now send time and day of week to heater
- Lots of new parameters added
- URL command `/JR` allows for querying the standard (reset) value of a parameter in JSON format
- URL command `/JB` allows for backing up parameters to JSON file
- New library for DHT22 should provide more reliable results
- Consolidated data and value types: New data types `VT_YEAR`, `VT_DAYMONTH`, `VT_TIME` as subsets of `VT_DATETIME` for parameters 1-3, replacing `VT_SUMMERPERIOD` and adjusting `VT_VACATIONPROG`. New value types `DT_THMS` for time consisting of hour:minutes:seconds
- MQTT: Use `MQTTDeviceID` as a client ID for the broker, still defaults to `BSB-LAN`. ATTENTION: Check your config if you're broker relies on the client ID in any way for authorization etc.

##Version 1.1##
**10.11.2020**  

- **ATTENTION:** DHW Push ("Trinkwasser Push") parameter had to be moved from 1601 to 1603 because 1601 has a different "official" meaning on some heaters. Please check and change your configuration if necessary
- **ATTENTION:** New categories added, most category numbers (using `/K)` will be shifted up by a few numbers.
- `/JA` URL command outputs average values
- Many new parameters decoded
- New parameters for device families 25, 44, 51, 59, 68, 85, 88, 90, 96, 97, 108, 134, 162, 163, 170, 195, 209, 211
- Improved mobile display of webinterface
- Added definement "BtSerial" for diverting serial output to Serial2 where a Bluetooth adapter can be connected (5V->5V, GND->GND, RX->TX2, TX->RX2). Adapter has to be in slave mode and configured to 115200 bps, 8N1.
- Lots of added Polish translations
- New data types `VT_BYTE10`, `VT_SPF`
- Bugfix for PPS bus regarding display of heating time programs
- Bugfix for MQTT

##Version 1.0##
**03.08.2020**  

- `/JI` URL command outputs configuration in JSON structure
- `/JC` URL command gets list of possible values from user-defined list of functions.  
Example: `/JC=505,700,701,702,711,1600,1602`
- Logging telegrams (log parameter 30000) now writes to separate file (`journal.txt`). It can be reset with `/D0` (same time with datalog.txt) command and dumped with `/DJ` command.
- removed WIFI configuration as it is no longer applicable for the Due
- lots of new parameters for various device families
- Code optimization and restructuring, general increase of speed
- new schemativs for board layout V3
- lots of bugfixes

##Version 0.44##
**11.05.2020**  

- Added webserver functionality via SD card and various other improvements from GitHub user dukess
- Added JSON output for MQTT
- mobile friendlier web interface
- more parameters and device families
- last version completely tested on Mega 2560. Future versions may still run on the Mega, but will only be tested on the Arduino Due.

##Version 0.43##
**20.02.2020**  

- Added support for HardwareSerial (Serial1) connection of the adapter. Use RX pin 19 in bus() definition to activate. See manual/forum for hardware details.
- Added definement DebugTelnet to divert serial output to telnet client (port 23, no password) in `BSB_LAN_config.h`
- Added possibility to control BSB-LAN (almost?) completely via USB-serial port. Most commands supported like their URL-counterparts, i.e. `/<passcode>/xxx` to query parameter xxx or `/<passcode>/N` to restart Arduino.
- Changed default device ID from 6 (room controller "RGT1") to unused ID 66 ("LAN")
- Many new parameters, please run `/Q` to see any possible changes for your device family and report back to us!
- Added global variables (arrays of 20 bytes) `custom_floats[]` and `custom_longs[]` for use with `BSB_LAN_custom.h`, for example to read sensors etc.
   Output of these variables is done via new URL command `/U`
- Added device families 23 and 29 (Grünenwald heaters)
- Added device families 49, 52, 59 (Weishaupt heaters)
- Added device fmilies 91, 92, 94, 118, 133, 136, 137, 165, 184, 188 (various controllers like QAA75 or AVS37)
- Added device family 171 (Bösch wood pellet system)
- Added device family 172 (SensoTherm BLW Split B (RVS21.826F/200))
- Added device families 186 and 164 (Olymp WHS-500)
- Added device family 195 variant 2 (Thision 19 Plus / LMS14.111B109)
- Including DHT, 1Wire and burner status parameters (>20000) to MQTT
- English is now default language
- Updated various translations
- Added STL files to print a case with a 3D printer (thanks to FHEM user EPo!)
- Moved all sensors to `/T` , `/H` is now no longer used
- New virtual parameters 702/703 for Weishaupt room controller
- New virtual parameter 10003 to set outside temperature on newer systems
- Added text descriptions for error phases (6706 ff.)
- `/Q` is now more comprehensive
- New data types `VT_CUSTOM_ENUM` and `VT_CUSTOM_BYTE` to extract information from non-standard telegrams (such as 702/703)
- Bugfix: DHCP (ethernet) implementation

##Version 0.42##
**21.03.2019**  

- Added localization! Now you can help translate BSB-LAN into your language! Simply copy one of the language files from the localization folder (`LANG_DE.h` is the most complete) and translate whatever you can. Non-translated items will be displayed in German.
   Attention: Language definition in `BSB_LAN_config.h` is now `#define LANG <ISO-CODE>`
   For example: `#define LANG DE`
- Added export to MQTT broker, use `log_parameters`[] in `BSB_LAN_config.h` to define parameters and activate `MQTTBrokerIP` definement.
- Added support for WiFi modules such as an ESP8266 or a Wemos Mega connected to Serial3 (RX:15/TX:14) of the Arduino.
   The ESP8266 has to be flashed with the AT firmware from Espressif to work.
   Please take note that WiFi over serial is by design much slower (only 115kpbs) than "pure" TCP/IP connections.
- Added new category "34 - Konfiguration / Erweiterungsmodule". All subsequent categories move one number up!
- Lots of new parameters coming from device family 123, please run `/Q` to see if some parameters also work for your heater!
- Lots of new yet unknown parameters through brute force querying :) (parameter numbers 10200 and above)
- Added further PPS-Bus commands, moved parameter numbers to 15000 and above
- Default PPS mode now "listening".
   Use third parameter of bus definition to switch between listening and controlling, 1 stands for controlling, everything else for listening,
   i.e. BSB bus(68,67,1) sends data to the heater, BSB bus(68,67) only receives data from heater / room controller.
   You can switch between modes at run-time with URL command `/P2,x` where x is either 1 (for controlling) or not 1 (for listening only)
- Fixed bug that crashed PPS bus queries
- Stability improvements for PPS bus
- Improved graph legend when plotting several parameters
- Added JSON export; query with `/JQ=a,b,c,d...` or push queries to `/JQ` or push set commands to `/JS`
- Logging of MAX! parameters now possible with logging parameter 20007
- Added Waterstage WP device family (119)
- Added WHG Procon device family (195)
- Added unit to log file as well as average output
- Rewrote device matching in `cmd_tbl` to accomodate also device variant (Gerätevariante). Run `/Q` to see if transition has worked for your device!
- Added `BSB_LAN_custom_setup.h` and `BSB_LAN_custom_global.h` for you to add individual code (best used in conjunction with `BSB_LAN_custom.h`)
- Marked all (known) OEM parameters with flag `FL_OEM`. OEM parameters are set by default as read-only. To make them writeable, change `FL_OEM` from 5 to 4 in `BSB_LAN_defs.h`
- Increased performance for querying several parameters at once (similar to category query)
- Added config option to define subnet.
- `/Q` no longer needs `#define DEBUG`
- Bugfix ENUM memory adressing
- Bugfix in reset function `/N`, clear EEPROM during reset with `/NE`
- Added favicon.ico
- Split of cmdtbl into cmdtbl1 and cmdtbl2 due to Arduino's(?) limit of 32kB size of struct, opening up more space for new parameters.

##Version 0.41##
**17.03.2019**  

- Interim release containing all changes from 0.42 above, except locaization, i.e. all text fragments are still part of the main code.

##Version 0.40##
**21.01.2018**  

- Implemented polling of MAX! heating thermostats, display with URL command `/X`
   See `BSB_LAN_custom.h` for an example to transmit average room temperature to heating system.
- Added new category "22 - Energiezähler" - please note that all subsequent categories move one up!
- New virtual parameter 1601 (manual TWW push)
- Added Fujitsu Waterstage WSYP100DG6 device family (211)
- Added CTC device family (103)
- New definement `#define TRUSTED_IP2` to grant access to a second local IP address
- Added optional definement `#define GatewayIP` in `BSB_LAN_config.h` to enable setting router address different from x.x.x.1
- Removed parameter 10109 because it is the same as 10000
- Added function to check all known CommandIDs on your own heating system. Use `/Q` after enabling definement `#define DEBUG` in `BSB_LAN_config.h`
- Added parameter numbers to category menu
- Updated analyze.sh
- hopefully fixing the memory issue
- Moved HTML strings to `html_strings.h`

##Version 0.39##
**02.01.2018**  

- Implemntation of PPS-Bus protocol.
   See `/K40` for the limited commands available for this bus.
   Use setBusType(2) to set to PPS upon boot or `/P2` to switch temporarily.
- Set GPIOs to input by using `/Gxx,I`
- Definement `#define CUSTOM_COMMANDS` added.
   Use this in your configuration to include individual code from `BSB_LAN_custom.h`
   (needs to be created by you!) which is executed at the end of each main loop.
   Variables `custom_timer` and `custom_timer_compare` have been added to execute
   code at arbitrary intervals.
- Added LogoBloc Unit L-UB 25C device family (95)
- several new parameters added
- Bugfix for logging Brennerlaufzeit Stufe 2

##Version 0.38##
**22.11.2017**  

- **ATTENTION:** New `BSB_LAN_config.h` configurations! You need to adjust your configuration when upgrading to this version!
   Webserver port is now defined in `#define Port xx`
   IP address is now defined in `#define IPAddr 88,88,88,88` form - note the commas instead of dots!
   Special log parameters 20002 to 20006 have changed, see `BSB_LAN_config.h` for their new meaning
- Added new virtual parameter 701 (Präsenztaste) which enters reduced temperature mode until next timed switch
- Added Brötje BOB device family (138), including many new parameters!
- Added Brötje SOB26 device family (28)
- Added Elco Aquatop 8es device family (85)
- Added Elco Thision 13 Plus device family (203)
- Added Weishaupt WTU 25-G familiy (50)
- Added output for absolute humidity (g/m3) for DHT22 sensors
- New schematics for Arduino/Raspberry board layout
- Included support for W5500 Ethernet2 shields. Activate definement `ETHERNET_W5500` in `BSB_LAN_config.h`
- Including two-stage oil furnaces BC-counters and logging - please note that logging parameters have been adjusted, see `BSB_LAN_config.h` for new values!
- Added new options for commands `/P` and `/S` to allow specifying a different destination device during runtime
- Added new configuration definement `CUSTOM_COMMANDS` which includes `BSB_LAN_custom.h` at the end of each main loop. You may use `custom_timer` (set to current millis()) and `custom_timer_compare` to execute only every x milliseconds.
- Bugfixing SD-card logging in monitor mode
- Bugfix for setting hour:time parameters via webinterface

##Version 0.37##
**08.09.2017**  

- LPB implementation! More than 450 parameters supported! Switch temporarily between LPB and BSB with the `/Px` command (with x equals to 0=BSB, 1=LPB) or use the setBusType config option to set bus-type at boot-time. Parameter numbers are the same as for BSB.

##Version 0.36##
**23.08.2017**  

- bugfix: brought back `VT_BIT` list of options which were erroneously deleted :(, fixed/freed several memory issues

##Version 0.35##
**25.06.2017**  

- new category "Sitherm Pro"; caution: category numbers all move up by one, starting from category "Wärmepumpe" (from 20 to 21) onwards.
- graph display of logging data now comes with crosshair and shows detailed values as tooltip
- improved SD-card output by factor 3 (from 16 to 45 kbps), switching SD-card library from from SD.h to SdFat.h (https://github.com/greiman/SdFat) brings another 10% performance boost
- adjusted paths and directory layout of SdFat to enable compiling from sketch directory.
- new data type `VT_SINT` for signed int data, currently only used in some Sitherm Pro parameters

##Version 0.34##
**29.05.2017**  

- Log data can now be displayed as graph
- Webinterface can now display and set `VT_BIT` type parameters in human-readable form
- added KonfigRGx descriptions; caution: various sources used, no guarantee that descriptions match your individual heating system!
- `VT_BIT` is generally read-only in the webinterface. To set, use URL command `/S` with decimal representation of value
- fixed a bug with `VT_SECONDS_SHORT5`, affecting parameters 9500 and 9540.
- fixed bug regarding Fujitsu's device family (from 127 to 170)
- moved libraries from folder libraries to src so they can be included without copying them to the Arduino libraries folder
- modified DallasTemperature.h's include path for OneWire.h

##Version 0.33##
**09.05.2017**  

- no more heating system definements anymore due to new autodetect function based on device family (parameter 6225), or set `device_id` variable to parameter value directly
- two more security options: `TRUSTED_IP` to limit access to one IP address only, and HTTP authentication with username and password
- Average values are saved on SD-card if present and LOGGER definement is activated
- deactivate logging by setting `/L0=0` - this way you can enable LOGGER definement without filling up SD card but still save average values
- new error codes for THISION
- added dump of data payload on website for commands of unknown type, greyed out unsopported parameters
- enable logging of telegrams (log parameter 30000) also in monitor mode (bsb.cpp and bsb.h updated)
- time from heating system is now retreived periodically from broadcast telegrams, further reducing bus activity
- new data type `VT_BIT` for parameters that set individual bits. Display as binary digits, setting still using decimal representation
- new data type `VT_TEMP_SHORT5_US` for unsigned one byte temperatures divided by 2 (so far only 887 Vorlaufsoll NormAussentemp)
- new data type `VT_PERCENT5` for unsigned one byte temperatures divided by 2 (so far only 885 Pumpe-PWM Minimum)
- new data type `VT_SECONDS_WORD5` for two byte seconds divided by 2 (so far only 2232, 9500 and 9540)
- new data type `VT_SECONDS_SHORT4` for (signed?) one byte seconds divided by 4 (so far only 2235)
- new data type `VT_SECONDS_SHORT5` for (signed?) one byte seconds divided by 5 (so far only 9500, 9540)
- new data type `VT_SPEED2` for two byte rpm (so far only 7050)
- cleaned up set() function from apparent duplicate cases
- added cases for `VT_TEMP_WORD`, `VT_SECONDS_WORD5`, `VT_TEMP_SHORT`, `VT_TEMP_SHORT5`, `VT_SECONDS_SHORT4` to set() function

##Version 0.32##
**18.04.2017**  

- lots of new parameters suppoerted
- newly designed webinterface allows control over heating system without any additional software or cryptic URL commands. URL commands of course are still available, so no need to change anything when using FHEM etc.
- German webinterface available with definement `LANG_DE`
- new URL-command `/LB=x` to log only broadcast messages (x=1) or all bus messages (x=0)
- new URL-command `/X` to reset the Arduino (need to enable RESET definement in `BSB_LAN_config.h`)
- new logging parameters 20002 and 20003 for hot water loading times and cycles
- moved DS18B20 logging parameters from 20010-20019 to 20200-20299 and DHT22 logging parameters from 20020-20029 to 20100 to 20199
- moved average logging parameter from 20002 to 20004
- set numerous parameters to read-only because that's what they obviously are (K33-36)
- various bugfixes

##Version 0.31##
**10.04.2017**  

- increased dumping of logfile by factor 5 / as long as we still have memory left, you can increase logbuflen from 100 to 1000 to increase transfer speed from approx. 16 to 18 kB/s
- adjusted burner activity monitoring based on broadcast messages for Brötje systems
- removed definement `PROGNR_5895` because so far, it has only disabled an ENUM definition.
- removed definement `PROGNR_6030` because double command ID could be resolved via BROETJE / non-BROETJE definements
- renamed `BROETJE_SOB` to BROETJE in order to allow for fine-grained distinction between different BROETJE cases (e.g. 6800ff)
   This means you have to activate TWO definements when using a Brötje system now: The general BROETJE as well as `BROETJE_SOB` or `BROETJE_BSW`.
   Have a look at your serial log for parameters 6800 to see which command IDs fit your system and activate one of both accordingly.
- changed 16-Bit addressing of flash memory to 32-Bit to address crashes due to ever growing PROGMEM tables - now we have lots of air to breathe again for new command IDs :)
- removed trailing \0 string from several ENUMs that led to wrong ENUM listings. Please keep in mind not to end ENUMs with a trailing \0 !

##Version 0.30##
**22.03.2017**  

- Time library by Paul Stoffregen (https://github.com/PaulStoffregen/Time) is now required and included in the library folder.
- adds logging of raw telegram data to SD card with logging parameter 30000. Logging telegram data is affected by commands `/V` and `/LU`
- adds command `/LU=x` to log only known (x=0) or unknown (x=1) command IDs when logging telegram data
- removed define `USE_BROADCAST`, broadcast data is now always processed
- new internal functions GetDateTime, TranslateAddr, TranslateType

##Version 0.29##
**07.03.2017**  

- adds command `/C` to display current configuration
- adds command `/L` to configure logging interval and parameters
- adds option for command `/A` to set 24h average parameters during runtime
- adds special parameter 20002 for logging `/A` command (24h averages, only makes sense for long logging intervals)
- bugfixes for logging DS18B20 sensors

##Version 0.28##
**05.03.2017**  

- adds special parameters 20000++ for SD card logging of `/B,` `/T` and `/H` commands (see `BSB_LAN_config.h` for examples)
- adds version info to `BSB_LAN` web interface

##Version 0.27##
**01.03.2017**  

- adds date field to log file (requires exact time to be sent by heating system)
- `/D0` recreates datalog.txt file with table header
- added "flags" field to command table structure. Currently, only `FL_RONLY` is supported to make a parameter read-only
- added `DEFAULT_FLAG` in config. Defaults to `NULL`, i.e. all fields are read/writeable.
   Setting it to `FL_RONLY` makes all parameters read-only, e.g. for added level of security.
   Individual parameters can be set to `NULL`/`FL_RONLY` to make only these parameters writable/read-only.

##Version 0.26##
**27.02.2017**  

- added functionality for logging on micro SD card, using the slot of the w5100 Ethernet shield
- more parameters added (e.g. 8009)

##Version 0.25##
**21.02.2017**  

- more FUJITSU parameters added

##Version 0.24##
**14.02.2017**  

- updated README with added functions
- added German translations of FAQ and README, courtesy of Ulf Dieckmann

##Version 0.23##
**12.02.2017**  

- minor bugfix

##Version 0.22##
**07.02.2017**  

- more FUJITSU parameters
- (hopefully) correct implementation of `VT_VOLTAGE` readings
- minor bugfixes

##Version 0.21##
**06.02.2017**  

- added numerous parameters for Fujitsu Wärmepumpe, including new `#define FUJITSU` directive to activate these parameters due to different parameter numbers
- minor bugfixes

##Version 0.20##
**27.01.2017**  

- added more parameters for Feststoffkessel
- minor bugfixes

##Version 0.19##
**01.01.2017**  

- added humidity command `/H`, currently for DHT22 sensors
- added 24h average command `/A`, define parameters in `BSB_LAN_config.h`
- removed trailing whitespace from menu strings
- fixed command id 0x053D04A2 for THISION heaters
- included Rob Tillaart's DHT library because there are various libraries implementing the protocol and this one is used in the code for its ability to address multiple sensors with one object.
- removed /temp URL parameter as it is a duplicate of `/T`
- included loop to display DHT22 sensors in IPWE
- making compiling IPWE extensions optional (`#define IPWE`)

##Version 0.18##
**22.12.2016**  

- split off configuration into ``bsb_lan_config.h``
- split off command definitions into ``bsb_lan_defs.h``
- changed GPIO return values from LOW/HIGH to 1/0
- reactivated and updated IPWE (define parameters in config)
- check for protected pins when accessing GPIO (define in config)
- added schematics and PCB files to new subfolder "schematics"

##Version 0.17a##
**20.12.2016**  

- minor errors corrected

##Version 0.17##
**20.12.2016**  

- merged v0.16 with FHEM user miwi's changes

##Version 0.16##
**20.11.2016**  

- removed IPWE and EthRly interface
- added GPIO interface
- merged parameters from J.Weber
- resolved duplicate command IDs

##Version 0.15a##
**25.07.2016**  

- collated the commands from a Python project and this project,
   merged the two versions, corrected obvious errors.
   Inserted hypothetical numerical values in ENUM definitions
   where Broetje manuals documented only the message texts.
- added information from traces in a Broetje installation with
   an ISR-SSR controller and a WOB 25C oil furnace.

##Version 0.15##
**21.04.2016**  

- added Solar and Pufferspeicher from Elco Logon B & Logon B MM

##Version 0.14##
**04.04.2016**  

- minor bugfixes for Broetje SOB
- extended broadcast handling (experimental)

##Version 0.13##
**31.03.2016**  

- change resistor value in receiving path from 4k7 to 1k5
- added values 0x0f and 0x10 to Enum8005
- fixed strings for Zeitprogramme
- added timeout for sending a message (1 second)
- added `/T` for querying one wire temperature sensors in mixed querys
- added special handling for Broetje SOB
- simplified settings

##Version 0.12##
**09.04.2015**  

- added `ONEWIRE_SENSORS` to ipwe
- fixed parameter decoding for ELCO Thision heating system

##Version 0.11##
**07.04.2015**  

- fixed parameter decoding for ELCO Thision heating system

##Version 0.10##
**15.03.2015**  

- added more parameters for ELCO Thision heating system

##Version 0.9##
**09.03.2015**  

- added more parameters for ELCO Thision heating system
- printTelegramm returns value string for further processing

##Version 0.8##
**05.03.2015**  

- added parameters for ELCO Thision heating system
- added IPWE extension
- minor bugfixes

##Version 0.7##
**06.02.2015**  

- added bus monitor functionality

##Version 0.6##
**02.02.2015**  

- renamed SoftwareSerial to BSBSoftwareSerial
- changed folder structure to enable simple build with arduino sdk

##Version 0.5##
**02.02.2015**

- bugfixes
- added documentation (README)
- added passkey feature
- added `/R` feature (query reset value)
- added `/E` feature (list enum values)
- added setter for almost all value types
- fixed indentation
- added `/V` feature to set verbosity for serial output
- set baudrate to 115200 for serial output
- redirecting favicon request
- added some images of the BSB adapter

##Version 0.1##
**21.01.2015**

 - initial version
