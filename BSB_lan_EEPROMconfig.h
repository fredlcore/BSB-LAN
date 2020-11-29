typedef enum{
// Version 0 (header + PPS values + space for MAX! devices)
  CF_USEEEPROM, //Size: 1 byte. 0x96 - read config from EEPROM. Other values - read predefined values from BSB_lan_config
  CF_VERSION, //Size: 1 byte. Config version
  CF_CRC32, //Size: 4 byte. CRC32 for list of parameters addressess
  CF_MAX_DEVICES, //Size 11 * 20 bytes.
  CF_MAX_DEVADDR, //Size 4 * 20 bytes.
  CF_PPS_VALUES, //
// Version 1 (parameters which can be changed by URL commands)
  CF_BUSTYPE, //Size: 1 byte. Bus type at start (DROPDOWN selector)
  CF_OWN_BSBADDR, ///Size: 1 byte. BSB bus device address (0x42)
  CF_OWN_LPBADDR, ///Size: 1 byte. LPB bus device address (0x42)
  CF_DEST_LPBADDR, ///Size: 1 byte. LPB bus destination address (0x0)
  CF_PPS_WRITE, ///Size: 1 byte. PPS can write
  CF_LOGTELEGRAM, //Size: 1 byte. Bitwise: LOGTELEGRAM_OFF = 0, LOGTELEGRAM_ON = 1, LOGTELEGRAM_UNKNOWN_ONLY = 2, LOGTELEGRAM_BROADCAST_ONLY = 4, LOGTELEGRAM_UNKNOWNBROADCAST_ONLY = 6
  CF_LOGAVERAGES, //Size: 1 byte. Log average values. 0 - disabled, 1 - enabled. Program list will be set in CF_AVERAGESLIST
  CF_AVERAGESLIST, //Size 2 * 40 bytes. Array of prognrs 1-65535. prognr 0 will be ignored
  CF_LOGCURRVALUES, //Size: 1 byte. Log current values. 0 - disabled, 1 - enabled. Program list will be set in CF_CURRVALUESLIST
  CF_LOGCURRINTERVAL, //Size 4 bytes. Unsigned. logging current values interval in seconds
  CF_CURRVALUESLIST, //Size 2 * 40 bytes. Array of prognrs 1-65535. prognr 0 will be ignored
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
  CF_ONEWIREBUS, //Size: 1 byte. One wire bus pin. 0 will be ignored
  CF_DHTBUS, //Size: 10 bytes (sizeof(DHT_Pins)). DHT temperature/humidity bus pins. 0 will be ignored
  CF_IPWE, //Size: 1 byte. IPWE extension: 0 - disabled, 1 - enabled
  CF_IPWEVALUESLIST, //Size 2 * 40 bytes. Array of prognrs 1-65535. prognr 0 will be ignored
  CF_MAX, //Size: 1 byte. Enable CUNO/CUNX/modified MAX!Cube
  CF_MAX_IPADDRESS, //Size: 4 bytes. IP v4 address of CUNO/CUNX/modified MAX!Cube.
  CF_WRITEMODE, //Size: 1 byte. 0 - all parameters will be FL_RONLY, 1 - write ordinary programs, 2 - write OEM programs
  CF_DEBUG, //Size: 1 byte. Debug: 0 - disabled, 1 - debug to serial interface, 2 - debug to telnet
  CF_MQTT, //Size: 1 byte. MQTT: 0 - disabled, 1 - enabled, plain text, 2 - enabled, JSON
  CF_MQTT_IPADDRESS, //Size: 4 bytes. MQTT broker IP v4 address
  CF_MQTT_USERNAME, //Size: 32 bytes.
  CF_MQTT_PASSWORD, //Size: 32 bytes.
  CF_MQTT_TOPIC, //Size: 32 bytes.
  CF_MQTT_DEVICE, //Size: 32 bytes.
  CF_ROOM_DEVICE, //Size: 2 bytes. 0x53 = QAA70, 0x52 = QAA50
//Version 3 (Web-config, some forgotten options)
  CF_MONITOR, //Size: 1 byte. bus monitor mode
  CF_VERBOSE, //Size: 1 byte. If set to 1, all messages on the bus are printed to debug interface
  CF_CHECKUPDATE, //Size: 1 byte. If set to 1, check for new version
  CF_LAST_OPTION //Virtual option. Must be last in enum. Only for internal usage.
} cf_params;

//according to input_type in configuration_struct
typedef enum {
  CPI_NOTHING,
  CPI_TEXT, // general text field
  CPI_SWITCH,
  CPI_DROPDOWN
} cpi_params;

//according to var_type in configuration_struct
typedef enum {
  CDT_VOID,
  CDT_BYTE,
  CDT_UINT16, //CPI_TEXT field with format for unsigned integer
  CDT_UINT32, //CPI_TEXT field with format for unsigned long integer
  CDT_STRING,
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
  CCAT_MQTT
} ccat_params;


typedef struct {
	uint8_t id;		// a unique identifier that can be used for the input tag name (cf_params)
  uint8_t version; //config version which can manage this parameter
  uint8_t category;	// for grouping configuration options (cdt_params)
  uint8_t input_type;	// input type (text, dropdown etc.) 0 - text field, 1 - switch, 2 - dropdown
	uint8_t var_type;	// variable type (string, integer, float, boolean etc.), could maybe be derived from input_type or vice versa
	const char* desc;	// pointer to text to be displayed for option - is text length necessary if we just read until NULL?
  uint16_t size; //data length in EEPROM
} configuration_struct;

typedef struct {
	uint8_t id;		// a unique identifier of param Category
  const char* desc;	// pointer to text to be displayed for category of option - is text length necessary if we just read until NULL?
} category_list_struct;

PROGMEM_LATE const category_list_struct catalist[]={
  {CCAT_GENERAL,        CAT_GENERAL_TXT},
  {CCAT_IPV4,           CAT_IPV4_TXT},
  {CCAT_MQTT,           CAT_MQTT_TXT}
};

PROGMEM_LATE const configuration_struct config[]={
  {CF_USEEEPROM,        0, CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           CF_USEEEPROM_TXT, sizeof(byte)}, //immediately apply
  {CF_VERSION,          0, CCAT_GENERAL,  CPI_NOTHING,   CDT_VOID,           NULL, sizeof(byte)},
  {CF_CRC32,            0, CCAT_GENERAL,  CPI_NOTHING,   CDT_VOID,           NULL, 4},
#ifdef CONFIG_IN_EEPROM
  {CF_BUSTYPE,          1, CCAT_GENERAL,  CPI_DROPDOWN,  CDT_BYTE,           CF_BUSTYPE_TXT, sizeof(bus_type)},//need handler
  {CF_OWN_BSBADDR,      1, CCAT_GENERAL,  CPI_TEXT,      CDT_BYTE,           CF_OWN_BSBADDR_TXT, sizeof(own_bsb_address)},//need handler
  {CF_OWN_LPBADDR,      1, CCAT_GENERAL,  CPI_TEXT,      CDT_BYTE,           CF_OWN_LPBADDR_TXT, sizeof(own_lpb_address)},//need handler
  {CF_DEST_LPBADDR,     1, CCAT_GENERAL,  CPI_TEXT,      CDT_BYTE,           CF_DEST_LPBADDR_TXT, sizeof(dest_lpb_address)},//need handler
  {CF_PPS_WRITE,        1, CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           CF_PPS_WRITE_TXT, sizeof(pps_write)},//need handler
#ifdef WEBCONFIG
  {CF_ROOM_DEVICE,      2, CCAT_GENERAL,  CPI_DROPDOWN,  CDT_UINT16,         STR15062, sizeof(pps_values[PPS_QTP])},//immediately apply
  {CF_MAC,              2, CCAT_GENERAL,  CPI_TEXT,      CDT_MAC,            CF_MAC_TXT, sizeof(mac)}, //need reboot
  {CF_DHCP,             2, CCAT_IPV4,     CPI_SWITCH,    CDT_BYTE,           CF_DHCP_TXT, sizeof(useDHCP)}, //need reboot
  {CF_IPADDRESS,        2, CCAT_IPV4,     CPI_TEXT,      CDT_IPV4,           CF_IPADDRESS_TXT, sizeof(ip_addr)}, //need reboot
  {CF_MASK,             2, CCAT_IPV4,     CPI_TEXT,      CDT_IPV4,           CF_MASK_TXT, sizeof(subnet_addr)}, //need reboot
  {CF_GATEWAY,          2, CCAT_IPV4,     CPI_TEXT,      CDT_IPV4,           CF_GATEWAY_TXT, sizeof(gateway_addr)}, //need reboot
  {CF_DNS,              2, CCAT_IPV4,     CPI_TEXT,      CDT_IPV4,           CF_DNS_TXT, sizeof(dns_addr)}, //need reboot
  {CF_WWWPORT,          2, CCAT_IPV4,     CPI_TEXT,      CDT_UINT16,         CF_WWWPORT_TXT, sizeof(HTTPPort)}, //need reboot - can't destroy EthernetServer object
  {CF_TRUSTEDIPADDRESS, 2, CCAT_IPV4,     CPI_TEXT,      CDT_IPV4,           CF_TRUSTEDIPADDRESS_TXT, sizeof(trusted_ip_addr)}, //immediately apply
  {CF_TRUSTEDIPADDRESS2,2, CCAT_IPV4,     CPI_TEXT,      CDT_IPV4,           CF_TRUSTEDIPADDRESS_TXT, sizeof(trusted_ip_addr2)},//immediately apply
#endif
  {CF_LOGTELEGRAM,      1, CCAT_GENERAL,  CPI_DROPDOWN,  CDT_BYTE,           CF_LOGTELEGRAM_TXT, sizeof(logTelegram)},//immediately apply
  {CF_LOGAVERAGES,      1, CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           CF_LOGAVERAGES_TXT, sizeof(logAverageValues)},//immediately apply
  {CF_AVERAGESLIST,     1, CCAT_GENERAL,  CPI_TEXT,      CDT_PROGNRLIST,     CF_AVERAGESLIST_TXT, sizeof(avg_parameters)},//immediately apply
  {CF_LOGCURRVALUES,    1, CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           CF_LOGCURRVALUES_TXT, sizeof(logCurrentValues)},//immediately apply
  {CF_LOGCURRINTERVAL,  1, CCAT_GENERAL,  CPI_TEXT,      CDT_UINT32,         CF_LOGCURRINTERVAL_TXT, sizeof(log_interval)},//immediately apply
  {CF_CURRVALUESLIST,   1, CCAT_GENERAL,  CPI_TEXT,      CDT_PROGNRLIST,     CF_CURRVALUESLIST_TXT, sizeof(log_parameters)},//immediately apply
#ifdef WEBCONFIG
  {CF_PASSKEY,          2, CCAT_IPV4,     CPI_TEXT,      CDT_STRING,         CF_PASSKEY_TXT, sizeof(PASSKEY)},//immediately apply
  {CF_BASICAUTH,        2, CCAT_IPV4,     CPI_TEXT,      CDT_STRING,         CF_BASICAUTH_TXT, sizeof(USER_PASS_B64)},//immediately apply
  {CF_WEBSERVER,        2, CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           CF_WEBSERVER_TXT, 1},
  {CF_ONEWIREBUS,       2, CCAT_GENERAL,  CPI_TEXT,      CDT_BYTE,           CF_ONEWIREBUS_TXT, sizeof(One_Wire_Pin)}, //need reboot.
//bus and pins: DHT_Pins
  {CF_DHTBUS,           2, CCAT_GENERAL,  CPI_TEXT,      CDT_DHTBUS,         CF_DHTBUS_TXT, sizeof(DHT_Pins)}, //immediately apply
  {CF_IPWE,             2, CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           CF_IPWE_TXT, sizeof(enable_ipwe)},//immediately apply
  {CF_IPWEVALUESLIST,   2, CCAT_GENERAL,  CPI_TEXT,      CDT_PROGNRLIST,     CF_IPWEVALUESLIST_TXT, sizeof(ipwe_parameters)},//immediately apply
  {CF_MAX,              2, CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           CF_MAX_TXT, sizeof(enable_max_cul)},//immediately apply
  {CF_MAX_IPADDRESS,    2, CCAT_GENERAL,  CPI_TEXT,      CDT_IPV4,           CF_MAX_IPADDRESS_TXT, sizeof(max_cul_ip_addr)}, //need reboot. Can use handler to reconfigure in future
#endif
#endif
  {CF_MAX_DEVICES,      0, CCAT_GENERAL,  CPI_TEXT,      CDT_MAXDEVICELIST,  CF_MAX_DEVICES_TXT, sizeof(max_device_list)}, //Need to call UpdateMaxDeviceList() before saving to EEPROM
  {CF_MAX_DEVADDR,      0, CCAT_GENERAL,  CPI_NOTHING,   CDT_VOID,           NULL, MAX_CUL_DEVICES * sizeof(uint32_t)},
  {CF_PPS_VALUES,       0, CCAT_GENERAL,  CPI_NOTHING,   CDT_VOID,           NULL, sizeof(pps_values[PPS_TWS]) * (PPS_BRS - PPS_TWS + 1)}, //printlnToDebug(PSTR("Reading EEPROM..."));  for (int i=PPS_TWS;i<=PPS_BRS;i++){ ...}
#ifdef CONFIG_IN_EEPROM
#ifdef WEBCONFIG
  {CF_WRITEMODE,        2, CCAT_GENERAL,  CPI_DROPDOWN,  CDT_BYTE,           CF_WRITEMODE_TXT, sizeof(programWriteMode)},
  {CF_DEBUG,            2, CCAT_GENERAL,  CPI_DROPDOWN,  CDT_BYTE,           CF_DEBUG_TXT, sizeof(debug_mode)},
  {CF_VERBOSE,          3, CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           CF_VERBOSE_TXT, sizeof(verbose)},
  {CF_MONITOR,          3, CCAT_GENERAL,  CPI_SWITCH,    CDT_BYTE,           CF_MONITOR_TXT, sizeof(monitor)},
  {CF_MQTT,             2, CCAT_MQTT,     CPI_DROPDOWN,  CDT_BYTE,           CF_MQTT_TXT, sizeof(mqtt_mode)},//need handler
  {CF_MQTT_IPADDRESS,   2, CCAT_MQTT,     CPI_TEXT,      CDT_IPV4,           CF_MQTT_IPADDRESS_TXT, sizeof(mqtt_broker_ip_addr)},//need handler
  {CF_MQTT_USERNAME,    2, CCAT_MQTT,     CPI_TEXT,      CDT_STRING,         CF_MQTT_USERNAME_TXT, sizeof(MQTTUsername)},//immediately apply
  {CF_MQTT_PASSWORD,    2, CCAT_MQTT,     CPI_TEXT,      CDT_STRING,         CF_MQTT_PASSWORD_TXT, sizeof(MQTTPassword)},//immediately apply
  {CF_MQTT_TOPIC,       2, CCAT_MQTT,     CPI_TEXT,      CDT_STRING,         CF_MQTT_TOPIC_TXT, sizeof(MQTTTopicPrefix)},//immediately apply
  {CF_MQTT_DEVICE,      2, CCAT_MQTT,     CPI_TEXT,      CDT_STRING,         CF_MQTT_TOPIC_TXT, sizeof(MQTTDeviceID)}, //immediately apply
  {CF_CHECKUPDATE,      3, CCAT_MQTT,     CPI_SWITCH,    CDT_BYTE,           CF_CHECKUPDATE_TXT, sizeof(enable_version_check)} //immediately apply

#endif
#endif
};

typedef struct{
  uint16_t eeprom_address;//start address in EEPROM
  byte *option_address; //pointer to parameter variable
} addressesOfConfigOptions;
addressesOfConfigOptions options[CF_LAST_OPTION];
