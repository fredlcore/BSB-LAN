#define CF_LOGMODE_SD_CARD 1
#define CF_LOGMODE_24AVG 2
#define CF_LOGMODE_MQTT 4
#define CF_LOGMODE_MQTT_ONLY_LOG_PARAMS 8
#define CF_LOGMODE_UDP 16

typedef enum{
// Version 0 (header + PPS values + space for MAX! devices)
  CF_USEEEPROM, //Size: 1 byte. 0x96 - read config from EEPROM. Other values - read predefined values from BSB_lan_config
  CF_VERSION, //Size: 2 byte. Config version Values: 0-65534
  CF_CRC32, //Size: 4 byte. CRC32 for list of parameters addressess
  CF_MAX_DEVICES, //Size 11 * 20 bytes.
  CF_MAX_DEVADDR, //Size 4 * 20 bytes.
  CF_PPS_VALUES, //
// Version 1 (parameters which can be changed by URL commands)
  CF_BUSTYPE, //Size: 1 byte. Bus type at start (DROPDOWN selector)
  CF_OWN_BSBADDR, ///Size: 1 byte. BSB bus device address (0x42). Not used. Leaved for compatibility
  CF_OWN_BSBLPBADDR, ///Size: 1 byte. LPB/BSB bus device address (0x42)
  CF_DEST_BSBLPBADDR, ///Size: 1 byte. LPB/BSB bus destination address (0x0)
  CF_PPS_MODE, ///Size: 1 byte. PPS can write
  CF_LOGTELEGRAM, //Size: 1 byte. Bitwise: LOGTELEGRAM_OFF = 0, LOGTELEGRAM_ON = 1, LOGTELEGRAM_UNKNOWN_ONLY = 2, LOGTELEGRAM_BROADCAST_ONLY = 4, LOGTELEGRAM_UNKNOWN_ONLY + LOGTELEGRAM_BROADCAST_ONLY = 6
  CF_AVERAGESLIST, //Size (4 + 2) * 40 bytes. Array of prognrs 1-65535. prognr 0 will be ignored
  CF_LOGCURRINTERVAL, //Size 4 bytes. Unsigned. logging current values interval in seconds
  CF_CURRVALUESLIST, //Size (4 + 2) * 40 bytes. Array of prognrs 1-65535. prognr 0 will be ignored
// Version 2 (Web-config)
  CF_MAC, //Size: 6 bytes. MAC address
  CF_DHCP, //Size: 1 byte. DHCP: 0 - disabled, 1 - enabled
  CF_IPADDRESS, //Size: 4 bytes. IP v4 address
  CF_MASK, //Size: 4 bytes. Network mask
  CF_GATEWAY, //Size: 4 bytes. Gateway
  CF_DNS, //Size: 4 bytes. DNS server address
  CF_WWWPORT, //Size: 2 bytes. Port number, 1-65535
  CF_TRUSTEDIPADDRESS,//Size: 4 bytes. First trusted IP v4 address. 0 - disabled
  CF_TRUSTEDIPADDRESS2,//Size: 4 bytes. Second trusted IP v4 address. 0 - disabled
  CF_PASSKEY, //Size 64 bytes. String with PASSKEY
  CF_BASICAUTH, //Size 64 bytes. String with USER_PASS_B64
  CF_WEBSERVER, //Size: 1 byte. External (read files from SD card) webserver: 0 - disabled, 1 - enabled
  CF_ONEWIREBUS, //Size: 1 byte. One wire bus pin. -1 will be ignored
  CF_DHTBUS, //Size: 10 bytes (sizeof(DHT_Pins)). DHT temperature/humidity bus pins. -1 will be ignored
  CF_IPWE, //Size: 1 byte. IPWE extension: 0 - disabled, 1 - enabled
  CF_IPWEVALUESLIST, //Size (4 + 2) * 40 bytes. Array of prognrs 1-65535. prognr 0 will be ignored
  CF_MAX, //Size: 1 byte. Enable CUNO/CUNX/modified MAX!Cube
  CF_MAX_IPADDRESS, //Size: 4 bytes. IP v4 address of CUNO/CUNX/modified MAX!Cube.
  CF_WRITEMODE, //Size: 1 byte. 0 - all parameters will be FL_RONLY, 1 - write ordinary programs, 2 - write OEM programs
  CF_DEBUG, //Size: 1 byte. Debug: 0 - disabled, 1 - debug to serial interface, 2 - debug to telnet
  CF_MQTT, //Size: 1 byte. MQTT: 0 - disabled, 1 - enabled, plain text, 2 - enabled, JSON
  CF_MQTT_SERVER, //Size: 33 bytes. MQTT broker domain name or IP address
  CF_MQTT_USERNAME, //Size: 65 bytes.
  CF_MQTT_PASSWORD, //Size: 65 bytes.
  CF_MQTT_TOPIC, //Size: 32 bytes.
  CF_MQTT_DEVICE, //Size: 32 bytes.
  CF_ROOM_DEVICE, //Size: 2 bytes. 0x53 = QAA70, 0x52 = QAA50
//Version 3 (Web-config, some forgotten options)
// removed with version 14
// CF_MONITOR, //Size: 1 byte. bus monitor mode
  CF_VERBOSE, //Size: 1 byte. If set to 1, all messages on the bus are printed to debug interface
  CF_CHECKUPDATE, //Size: 1 byte. If set to 1, check for new version
// Version 4 (WiFi options)
  CF_WIFI_SSID, //Size: 32 byte by standart.
  CF_WIFI_PASSWORD, //Size 64 bytes.
// Version 5 (Room Units 1-3 Emulation)
// removed with version 13
/*
  CF_RGT1_SENSOR_ID, //Size 2*5 bytes. Programs ID to temperature sensor access
  CF_RGT2_SENSOR_ID, //Size 2*5 bytes. Programs ID to temperature sensor access
  CF_RGT3_SENSOR_ID, //Size 2*5 bytes. Programs ID to temperature sensor access
  CF_TWW_PUSH_PIN_ID, //Size 1 byte. Pin number for "TWW push" button connection. 0 will be ignored
  CF_RGT1_PRES_PIN_ID, //Size 1 byte. Pin number for "Presence" button connection. 0 will be ignored
  CF_RGT2_PRES_PIN_ID, //Size 1 byte. Pin number for "Presence" button connection. 0 will be ignored
  CF_RGT3_PRES_PIN_ID, //Size 1 byte. Pin number for "Presence" button connection. 0 will be ignored
*/
// Version 6 ()
  CF_BMEBUS, //Size: 1 byte. If set to 1 or 2 then BME280 sensor(s) will be used
  CF_OTA_UPDATE, //Size: 1 byte. OTA update for ESP32. 0 - disabled, 1 - enabled.
  CF_MDNS_HOSTNAME, //Size: 32 byte. Host name for mDNS discovery service
// Version 7 ()
  CF_SHOW_UNKNOWN, //Size: 1 byte. show/hide unknown parameters from web display
// Version 8 (bus pins and device family and variant)
  CF_RX_PIN, //Size: 1 byte. RX pin
  CF_TX_PIN, //Size: 1 byte. TX pin
/* removed with version 14
  CF_DEVICE_FAMILY, //Size: 2 bytes. Heater family ID
  CF_DEVICE_VARIANT, //Size: 2 bytes. Heater variant ID
*/
// Version 9 (config level)
  CF_CONFIG_LEVEL, // Size: 1 byte. Configuration webconfig complexity. 0 - basic, 1 - advanced.
// Version 10 (Logger switcher)
  CF_LOGMODE, // Size: 1 byte. Bitwise value. Logging: 0 - disabled, 1 - write values to SD card, 2 - write 24h averages to SD card, 4 - send values to MQTT, 8 - only log parameters to MQTT, 16 - send values to UDP.
// Version 11 (ESP32 energy save mode)
  CF_ESP32_ENERGY_SAVE,
// Version 12 (MQTT server (changed above), network type, log destination)
  CF_LOG_DEST,
  CF_NETWORK_TYPE,
// Version 13 (introduce dummy variable to easily change minimum EEPROM schema version in case of change in variable type etc.)
  CF_DUMMY,
//Maximum version can be 65534 (0xFFFE). In other case initConfigTable() will locked in infinite loop
//Maximum options count can be 253 for same reason (or must changing uint8_t type to uint16_t)
// Version 14 (remove fixed device family/variant)
  CF_LAST_OPTION //Virtual option. Must be last in enum. Only for internal usage.
} cf_params;

//according to input_type in configuration_struct
typedef enum {
  CPI_NOTHING,
  CPI_TEXT, // general text field
  CPI_SWITCH,
  CPI_DROPDOWN,
  CPI_CHECKBOXES
} cpi_params;

//according to var_type in configuration_struct
typedef enum {
  CDT_VOID, // byte array
  CDT_BYTE, // unsigned byte. can be various format
  CDT_INT8,   // CPI_TEXT field with format for signed 8-bit integer
  CDT_UINT16, //CPI_TEXT field with format for unsigned integer
  CDT_UINT32, //CPI_TEXT field with format for unsigned long integer
  CDT_STRING, //CPI_TEXT field
  CDT_MAC, //CPI_TEXT field with format for MAC input/output
  CDT_IPV4, //CPI_TEXT field with format for IPv4 input/output
  CDT_PROGNRLIST, //CPI_TEXT field with format for programs list input/output
  CDT_MAXDEVICELIST,//CPI_TEXT field with format for MAX! devices list input/output
  CDT_DHTBUS //CPI_TEXT field with format for DHT bus
} cdt_params;

//according to category in configuration_struct
typedef enum {
  CCAT_GENERAL,
  CCAT_IPV4,
  CCAT_MQTT,
  CCAT_BUS,
  CCAT_IPWE,
  CCAT_DHTBUS,
  CCAT_ONEWIREBUS,
  CCAT_DEBUG,
  CCAT_MAX,
  CCAT_LOGGING,
  CCAT_24HAVG,
  CCAT_RGT_EMUL,
  CCAT_BMEBUS
} ccat_params;


typedef struct {
  uint8_t id;          // a unique identifier that can be used for the input tag name (cf_params)
  uint8_t version;     // config version which can manage this parameter
  uint8_t category;    // for grouping configuration options (cdt_params)
  uint8_t input_type;  // input type (text, dropdown etc.) 0 - none 1 - text field, 2 - switch, 3 - dropdown, 4 - bitwise (checkboxes)
  uint8_t var_type;    // variable type (string, integer, float, boolean etc.), could maybe be derived from input_type or vice versa
  uint8_t flags;       // options flags: 1 - basic option, 2 - advanced option
  const char* desc;    // pointer to text to be displayed for option - is text length necessary if we just read until NULL?
  uint16_t size;       // data length in EEPROM
} configuration_struct;

#define OPT_FL_BASIC 1
#define OPT_FL_ADVANCED 2

typedef struct {
  uint8_t id;          // a unique identifier of param Category
  const char* desc;    // pointer to text to be displayed for category of option - is text length necessary if we just read until NULL?
} category_list_struct;

const category_list_struct catalist[]={
  {CCAT_GENERAL,        CAT_GENERAL_TXT},
  {CCAT_IPV4,           CAT_IPV4_TXT},
  {CCAT_MQTT,           CAT_MQTT_TXT},
  {CCAT_BUS,            CAT_BUS_TXT},
  {CCAT_IPWE,           CAT_IPWE_TXT},
  {CCAT_DHTBUS,         CAT_DHTBUS_TXT},
  {CCAT_ONEWIREBUS,     CAT_ONEWIREBUS_TXT},
  {CCAT_DEBUG,          CAT_DEBUG_TXT},
  {CCAT_MAX,            CAT_MAX_TXT},
  {CCAT_LOGGING,        CAT_LOGGING_TXT},
  {CCAT_24HAVG,         CAT_24HAVG_TXT},
  {CCAT_RGT_EMUL,       CAT_RGT_EMUL_TXT},
  {CCAT_BMEBUS,         CAT_BMEBUS_TXT}
};

const configuration_struct config[]={
  {CF_CONFIG_LEVEL,     9, CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           OPT_FL_BASIC|OPT_FL_ADVANCED, CF_CONFIG_LEVEL_TXT, sizeof(config_level)}, //immediately apply
  {CF_USEEEPROM,        0, CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           OPT_FL_BASIC|OPT_FL_ADVANCED, CF_USEEEPROM_TXT, sizeof(UseEEPROM)}, //immediately apply
  {CF_VERSION,          0, CCAT_GENERAL,  CPI_NOTHING,   CDT_VOID,           OPT_FL_BASIC|OPT_FL_ADVANCED, NULL, sizeof(uint16_t)},
  {CF_CRC32,            0, CCAT_GENERAL,  CPI_NOTHING,   CDT_VOID,           OPT_FL_BASIC|OPT_FL_ADVANCED, NULL, sizeof(uint32_t)},
  {CF_WRITEMODE,        2, CCAT_GENERAL,  CPI_DROPDOWN,  CDT_BYTE,           OPT_FL_BASIC|OPT_FL_ADVANCED, CF_WRITEMODE_TXT, sizeof(programWriteMode)},
  {CF_CHECKUPDATE,      3, CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           OPT_FL_ADVANCED, CF_CHECKUPDATE_TXT, sizeof(enable_version_check)}, //immediately apply
#ifdef ESP32
  {CF_OTA_UPDATE,       6, CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           OPT_FL_ADVANCED, CF_OTA_UPDATE_TXT, sizeof(enable_ota_update)}, //immediately apply
  {CF_ESP32_ENERGY_SAVE,11,CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           OPT_FL_ADVANCED, CF_ENERGY_SAVE_TXT, sizeof(esp32_save_energy)}, //need reboot
#endif
  {CF_WEBSERVER,        2, CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           OPT_FL_ADVANCED, CF_WEBSERVER_TXT, sizeof(webserver)},
  {CF_BUSTYPE,          1, CCAT_BUS,      CPI_DROPDOWN,  CDT_BYTE,           OPT_FL_BASIC|OPT_FL_ADVANCED, CF_BUSTYPE_TXT, sizeof(bus_type)},//need handler
  {CF_PPS_MODE,         1, CCAT_BUS,      CPI_DROPDOWN,  CDT_BYTE,           OPT_FL_BASIC|OPT_FL_ADVANCED, CF_PPS_WRITE_TXT, sizeof(pps_write)},//need handler
  {CF_ROOM_DEVICE,      2, CCAT_BUS,      CPI_DROPDOWN,  CDT_UINT16,         OPT_FL_BASIC|OPT_FL_ADVANCED, CF_QAA_TYPE_TXT, sizeof(pps_values[PPS_QTP])},//immediately apply
//  {CF_OWN_BSBADDR,      1, CCAT_BUS,      CPI_NOTHING,   CDT_BYTE,           OPT_FL_ADVANCED, NULL, sizeof(byte)},//Not used. Leaved for compatibility
  {CF_OWN_BSBLPBADDR,   1, CCAT_BUS,      CPI_TEXT,      CDT_BYTE,           OPT_FL_ADVANCED, CF_OWN_BSBLPBADDR_TXT, sizeof(own_address)},//need handler
  {CF_DEST_BSBLPBADDR,  1, CCAT_BUS,      CPI_TEXT,      CDT_BYTE,           OPT_FL_ADVANCED, CF_DEST_BSBLPBADDR_TXT, sizeof(dest_address)},//need handler
  {CF_RX_PIN,           8, CCAT_BUS,      CPI_TEXT,      CDT_BYTE,           OPT_FL_ADVANCED, CF_RX_PIN_TXT, sizeof(bus_pins[0])},//need reboot
  {CF_TX_PIN,           8, CCAT_BUS,      CPI_TEXT,      CDT_BYTE,           OPT_FL_ADVANCED, CF_TX_PIN_TXT, sizeof(bus_pins[0])},//need reboot
  {CF_NETWORK_TYPE,     12,CCAT_IPV4,     CPI_DROPDOWN,  CDT_BYTE,           OPT_FL_BASIC|OPT_FL_ADVANCED, CF_NETWORK_TYPE_TXT, sizeof(network_type)},// should not need reboot, but crashes if no reboot?
  {CF_WIFI_SSID,        4, CCAT_IPV4,     CPI_TEXT,      CDT_STRING,         OPT_FL_BASIC|OPT_FL_ADVANCED, CF_WIFI_SSID_TXT, sizeof(wifi_ssid)}, //need reboot
  {CF_WIFI_PASSWORD,    4, CCAT_IPV4,     CPI_TEXT,      CDT_STRING,         OPT_FL_BASIC|OPT_FL_ADVANCED, CF_WIFI_PASSWORD_TXT, sizeof(wifi_pass)},//need reboot
  {CF_DHCP,             2, CCAT_IPV4,     CPI_SWITCH,    CDT_BYTE,           OPT_FL_ADVANCED, CF_DHCP_TXT, sizeof(useDHCP)}, //need reboot
  {CF_IPADDRESS,        2, CCAT_IPV4,     CPI_TEXT,      CDT_IPV4,           OPT_FL_ADVANCED, CF_IPADDRESS_TXT, sizeof(ip_addr)}, //need reboot
  {CF_MASK,             2, CCAT_IPV4,     CPI_TEXT,      CDT_IPV4,           OPT_FL_ADVANCED, CF_MASK_TXT, sizeof(subnet_addr)}, //need reboot
  {CF_GATEWAY,          2, CCAT_IPV4,     CPI_TEXT,      CDT_IPV4,           OPT_FL_ADVANCED, CF_GATEWAY_TXT, sizeof(gateway_addr)}, //need reboot
  {CF_DNS,              2, CCAT_IPV4,     CPI_TEXT,      CDT_IPV4,           OPT_FL_ADVANCED, CF_DNS_TXT, sizeof(dns_addr)}, //need reboot
  {CF_WWWPORT,          2, CCAT_IPV4,     CPI_TEXT,      CDT_UINT16,         OPT_FL_ADVANCED, CF_WWWPORT_TXT, sizeof(HTTPPort)}, //need reboot - can't destroy EthernetServer object
  {CF_MAC,              2, CCAT_IPV4,     CPI_TEXT,      CDT_MAC,            OPT_FL_ADVANCED, CF_MAC_TXT, sizeof(mac)}, //need reboot
  {CF_MDNS_HOSTNAME,    6, CCAT_IPV4,     CPI_TEXT,      CDT_STRING,         OPT_FL_ADVANCED, CF_MDNS_HOSTNAME_TXT, sizeof(mDNS_hostname)},//need reboot
  {CF_BASICAUTH,        2, CCAT_IPV4,     CPI_TEXT,      CDT_STRING,         OPT_FL_ADVANCED, CF_BASICAUTH_TXT, sizeof(USER_PASS)},//immediately apply
  {CF_PASSKEY,          2, CCAT_IPV4,     CPI_TEXT,      CDT_STRING,         OPT_FL_ADVANCED, CF_PASSKEY_TXT, sizeof(PASSKEY)},//immediately apply
  {CF_TRUSTEDIPADDRESS, 2, CCAT_IPV4,     CPI_TEXT,      CDT_IPV4,           OPT_FL_ADVANCED, CF_TRUSTEDIPADDRESS_TXT, sizeof(trusted_ip_addr)}, //immediately apply
  {CF_TRUSTEDIPADDRESS2,2, CCAT_IPV4,     CPI_TEXT,      CDT_IPV4,           OPT_FL_ADVANCED, CF_TRUSTEDIPADDRESS_TXT, sizeof(trusted_ip_addr2)},//immediately apply
#ifdef ESP32
  {CF_LOG_DEST,         12,CCAT_LOGGING,  CPI_DROPDOWN,  CDT_BYTE,           OPT_FL_BASIC|OPT_FL_ADVANCED, CF_LOG_DEST_TXT, sizeof(LogDestination)}, //need handler
#endif
  {CF_LOGMODE,          10,CCAT_LOGGING,  CPI_CHECKBOXES,CDT_BYTE,           OPT_FL_BASIC|OPT_FL_ADVANCED, CF_LOGMODE_TXT, sizeof(LoggingMode)}, //immediately apply
  {CF_LOGCURRINTERVAL,  1, CCAT_LOGGING,  CPI_TEXT,      CDT_UINT32,         OPT_FL_BASIC|OPT_FL_ADVANCED, CF_LOGCURRINTERVAL_TXT, sizeof(log_interval)},//immediately apply
  {CF_CURRVALUESLIST,   1, CCAT_LOGGING,  CPI_TEXT,      CDT_PROGNRLIST,     OPT_FL_BASIC|OPT_FL_ADVANCED, CF_PROGLIST_TXT, sizeof(log_parameters)},//immediately apply
  {CF_LOGTELEGRAM,      1, CCAT_LOGGING,  CPI_DROPDOWN,  CDT_BYTE,           OPT_FL_ADVANCED, CF_LOGTELEGRAM_TXT, sizeof(logTelegram)},//immediately apply
  {CF_AVERAGESLIST,     1, CCAT_24HAVG,   CPI_TEXT,      CDT_PROGNRLIST,     OPT_FL_BASIC|OPT_FL_ADVANCED, CF_PROGLIST_TXT, sizeof(avg_parameters)},//immediately apply
  {CF_MQTT_SERVER,      12,CCAT_MQTT,     CPI_TEXT,      CDT_STRING,         OPT_FL_ADVANCED, CF_MQTT_SERVER_TXT, sizeof(mqtt_broker_addr)},//need handler
  {CF_MQTT_USERNAME,    2, CCAT_MQTT,     CPI_TEXT,      CDT_STRING,         OPT_FL_ADVANCED, CF_MQTT_USERNAME_TXT, sizeof(MQTTUsername)},//immediately apply
  {CF_MQTT_PASSWORD,    2, CCAT_MQTT,     CPI_TEXT,      CDT_STRING,         OPT_FL_ADVANCED, CF_MQTT_PASSWORD_TXT, sizeof(MQTTPassword)},//immediately apply
  {CF_MQTT_DEVICE,      2, CCAT_MQTT,     CPI_TEXT,      CDT_STRING,         OPT_FL_ADVANCED, CF_MQTT_DEVICE_TXT, sizeof(MQTTDeviceID)}, //immediately apply
  {CF_MQTT_TOPIC,       2, CCAT_MQTT,     CPI_TEXT,      CDT_STRING,         OPT_FL_ADVANCED, CF_MQTT_TOPIC_TXT, sizeof(MQTTTopicPrefix)},//immediately apply
  {CF_MQTT,             2, CCAT_MQTT,     CPI_DROPDOWN,  CDT_BYTE,           OPT_FL_ADVANCED, CF_USE_TXT, sizeof(mqtt_mode)},//need handler
  {CF_ONEWIREBUS,       2, CCAT_ONEWIREBUS,CPI_TEXT,     CDT_INT8,           OPT_FL_ADVANCED, CF_PINS_TXT, sizeof(One_Wire_Pin)}, //need reboot.
//bus and pins: DHT_Pins
  {CF_DHTBUS,           2, CCAT_DHTBUS,   CPI_TEXT,      CDT_DHTBUS,         OPT_FL_ADVANCED, CF_PINS_TXT, sizeof(DHT_Pins)}, //immediately apply
  {CF_BMEBUS,           6, CCAT_BMEBUS,   CPI_TEXT,      CDT_BYTE,           OPT_FL_ADVANCED, CF_NUM_TXT, sizeof(BME_Sensors)}, //need reboot
  {CF_MAX,              2, CCAT_MAX,      CPI_SWITCH,    CDT_BYTE,           OPT_FL_ADVANCED, CF_USE_TXT, sizeof(enable_max_cul)},//immediately apply
  {CF_MAX_IPADDRESS,    2, CCAT_MAX,      CPI_TEXT,      CDT_IPV4,           OPT_FL_ADVANCED, CF_MAX_IPADDRESS_TXT, sizeof(max_cul_ip_addr)}, //need reboot. Can use handler to reconfigure in future
  {CF_MAX_DEVICES,      0, CCAT_MAX,      CPI_TEXT,      CDT_MAXDEVICELIST,  OPT_FL_ADVANCED, CF_DEVICES_TXT, sizeof(max_device_list)}, //Need to call UpdateMaxDeviceList() before saving to EEPROM
  {CF_MAX_DEVADDR,      0, CCAT_MAX,      CPI_NOTHING,   CDT_VOID,           OPT_FL_BASIC|OPT_FL_ADVANCED, NULL, MAX_CUL_DEVICES * sizeof(uint32_t)},
  {CF_PPS_VALUES,       0, CCAT_GENERAL,  CPI_NOTHING,   CDT_VOID,           OPT_FL_BASIC|OPT_FL_ADVANCED, NULL, sizeof(pps_values)}, //printlnToDebug("Reading EEPROM...");  for (int i=PPS_TWS;i<=PPS_BRS;i++){ ...}
  {CF_IPWE,             2, CCAT_IPWE,     CPI_SWITCH,    CDT_BYTE,           OPT_FL_ADVANCED, CF_USE_TXT, sizeof(enable_ipwe)},//immediately apply
  {CF_IPWEVALUESLIST,   2, CCAT_IPWE,     CPI_TEXT,      CDT_PROGNRLIST,     OPT_FL_ADVANCED, CF_PROGLIST_TXT, sizeof(ipwe_parameters)},//immediately apply
  {CF_DEBUG,            2, CCAT_DEBUG,    CPI_DROPDOWN,  CDT_BYTE,           OPT_FL_ADVANCED, CF_USE_TXT, sizeof(debug_mode)},
  {CF_VERBOSE,          3, CCAT_DEBUG,    CPI_DROPDOWN,  CDT_BYTE,           OPT_FL_ADVANCED, CF_VERBOSE_TXT, sizeof(verbose)},
  {CF_SHOW_UNKNOWN,     7, CCAT_DEBUG,    CPI_SWITCH,    CDT_BYTE,           OPT_FL_ADVANCED, CF_SHOW_UNKNOWN_TXT, sizeof(show_unknown)},//immediately apply
  {CF_DUMMY,           14, CCAT_DEBUG,    CPI_NOTHING,   CDT_VOID,           OPT_FL_BASIC|OPT_FL_ADVANCED, CF_SHOW_UNKNOWN_TXT, sizeof(byte)},// dummy variable for forcing new EEPROM schema version
};

typedef struct{
  uint16_t eeprom_address;//start address in EEPROM
  byte *option_address; //pointer to parameter variable
} addressesOfConfigOptions;
addressesOfConfigOptions options[CF_LAST_OPTION];
