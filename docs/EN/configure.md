# Configuration
There are two ways to configure BSB-LAN:

1. Through the configuration file `BSB_LAN_config.h`
1. Through the web-interface by calling [http://bsb-lan.local/C](http://bsb-lan.local/C) (or the corresponding IP address)

For the initial configuration, some settings have to be configured in the configuration file (such as language and network settings).  
Any further changes can be done also in the web-interface. It may, however, be useful to do the configuration (also) in the configuration file in case one needs to change the microcontroller. Almost all settings exist also in the web-interface and vice versa.  

On an ESP32-based microcontroller, BSB-LAN will set up its own wireless access point named `BSB-LAN` if it cannot connect to any network. So even without any further configuration, you can connect to this access point with the password `BSB-LPB-PPS-LAN` and access BSB-LAN via the IP address `http://192.168.4.1` and proceed with the configuration via this way. Keep in mind that if you have set a passkey or HTTP username and password, these are still required if these details are stored in EEPROM or `BSB_LAN_config.h`.


---
## Configuration through `BSB_LAN_config.h``

The configuration file consists of variables that are used in other parts of BSB-LAN. It is therefore important to **only change the contents** of the variables (i.e. the settings) and **not the type** of the variables. So if there is for example the setting  
`byte ip_addr[4] = {192,168,178,88};`  
you must not alter the `byte ip_addr[4] =` part, only the contents, in this case the comma-separated IP address.
---
## Configuration through the web-interface

Configuring BSB-LAN through the web-interface is pretty straightforward, as you don't have to deal with variable names but clear descriptions.
Initially, only a selected number of configuration options are displayed in the webinterface (marked in **bold** below). To have access to all of them, you have to set the "extended configuration" option to "on".
---
## Overview of configuration options
<style>
table th:first-of-type {
    width: 20%;
}
table th:nth-of-type(2) {
    width: 20%;
}
table th:nth-of-type(3) {
    width: 40%;
}
table th:nth-of-type(4) {
    width: 20%;
}
</style>

### General Settings
|Web-Interface|Configuration File|Functionality|Possible settings|
|-------------|------------------|-------------|-----------------|
|-            |**`#define LANG`**|Set language |`DE`, `EN`, `FR` and other ISO country codes|
|**Display extended configuration**|-|Show all configuration options|**On**<br>**Off**|
|**Read config from EEPROM**|`UseEEPROM`|Read configuration from EEPROM or file|**On**  (`1`)<br>**Off** (`0`)|
|[](){#WriteAccess}Write access (level)|-          |If `DEFAULT_FLAG`is set to `FL_SW_CTL_RONLY`, you can set the level of write access here.|**Off** (read-only)<br>**On (Standard)**<br>**On (Complete)**
|Check for updates|`enable_version_check`|Query BSB-LAN server for new available version|**On** (`true`)|
|OTA Update|`enable_ota_update`|Enable over-the-air (OTA) update|**On** (`true`)|
|Energy saving|`esp32_save_energy`|Reduces speed, saves energy. Do not enable when using WiFi.|**On** (`true`)<br>**Off** (`false`)|
|Webserver file system|`webserver`|Enables serving files from SD card|**On** (`true`)<br>**Off** (`false`)|
|-            |`#define DEFAULT_FLAG`|Set read/write access to heating system. `FL_RONLY` sets all parameters to read-only. `FL_SW_CTL_RONLY` allows setting read/write access via web-interface configuration setting.<BR>`0` makes all  parameters that could be written writeable. **Do not use this option unless instructed otherwise!**|**FL_RONLY**<BR>**FL_SW_CTL_RONLY**<BR>**0**|

### Bus settings
|Web-Interface|Configuration File|Functionality|Possible settings|
|-------------|------------------|-------------|-----------------|
|**Bus type**|`bus_type`|Bus type (BSB/LPB/PPS)|**BSB** (`0`)<br>**LPB** (`1`)<br>**PPS** (`2`)|
|**PPS: mode**|`pps_write`|BSB-LAN can act as a PPS room unit (only if no real room unit is connected) or just listen passively.|**passive** (`0`)<br>**as room unit** (`1`)|
|**PPS: QAA model**|`QAA_TYPE`|Room unit that should be simulated for PPS bus|**QAA70** (`0x53`), **QAA50** (`0x52`), **QAA95** (`0x37`), **QAW10** (`0x4D`), **QAW20** (`0x4E`), **MCBA/REA70/DC225** (`0x58`), **QAA10** (`0x5A`), **QAA20** (`0x5B`), **QAA12/13** (`0x5D`), **BMU** (`0x66`), **RVD130** (`0x43`)|
|Own address|`own_address`|Own bus address (default `66` should not be changed)|**66** (`66`)|
|Destination address|`dest_address`|Destination bus address.<br>For **BSB** always `0`.<br>For **LPB** `0` if destination device is in segment 1, device address 0.<BR>To convert from LPB segment and device address notation to destination address, multiply segment by 16, add the device address and subtract one. For example, to address a device in segment 4 with device address 3, the destination address is `(4 * 16) + 3 - 1 = 66`.<br>For **PPS** not relevant.|**0** (`0`)|
|RX pin number<br>TX pin number|`bus_pins`|Define the RX/TX pins to communicate with the BSB-LAN adapter. Leave at `0` for auto-detection.|**0** and **0** (`0, 0`)|

### Network settings
|Web-Interface|Configuration File|Functionality|Possible settings|
|-------------|------------------|-------------|-----------------|
|**Network device**|**`network_type`**|Choose between WLAN and LAN to connect BSB-LAN to the network.|**LAN** (`0`)<br>**WLAN** (`1`)|
|**WLAN SSID**|**`wifi_ssid`**|Set the WLAN network name when using WLAN.|**Your_WLAN_name** (`Your_WLAN_name`)|
|**WLAN password**|**`wifi_pass`**|Set the WLAN password when using WLAN.|**YourWLANpassword** (`YourWLANpassword`)|
|DHCP usage|**`use_dhcp`**|Set whether or not to use DHCP to get an IP address from the router.|**On** (`true`)<br>**Off** (`false`)|
|IP address (fixed)|`ip_addr`|When *not* using DHCP, you can set a fixed IP address here. Otherwise leave at `0.0.0.0`. In the web-interface, you may use dot notation. In the configuration file, you have to use comma as a separator.|**192.168.178.88** (`192,168,178,88`)|
|Subnet|`subnet_addr`|Subnet when using fixed IP address. Same notation as with IP address.|**255.255.255.0** (`255,255,255,0`)|
|Gateway|`gateway_addr`|Gateway address when using fixed IP address. Same notation as with IP address.|**192.168.178.1** (`192,168,178,1`)|
|DNS Server|`dns_addr`|DNS server address when using fixed IP address. Same notation as with IP address.|**192.168.178.1** (`192,168,178,1`)|
|TCP Port|`HTTPPort`|HTTP port number to access the web-interface. Defaults to `80`.|**80** (`80`)|
|MAC address|`mac`|Set a fixed MAC address. Only relevant on Arduino.|**00:80:41:19:69:90** (`0x00, 0x80, 0x41, 0x19, 0x69, 0x90`)|
|mDNS Hostname|`mDNS_hostname`|Hostname for mDNS discovery|**BSB-LAN** (`BSB-LAN`)|
|HTTP authentification|`USER_PASS`|If not empty, this setting contains the username and password for HTTP authentification, separated by a colon.|**Username:Password** (`Username:Password`)|
|URL Passkey|`PASSKEY`|Passkey adds a user-defined sequence that needs to be added to the URL after the hostname.<BR>For example, a passkey of `1234` requires every URL to be written as `http://bsb-lan.local/1234/` instead of just `http://bsb-lan.local/`. Leave empty for no passkey.|**1234** (`1234`)|
|Trusted IP address|`trusted_ip_addr`|Access to BSB-LAN is only possible from this IP address. Same notation as with IP address.|**192.168.178.89** (`192,168,178,89`)|
|Trusted IP address|`trusted_ip_addr2`|Access to BSB-LAN is only possible from this IP address. Same notation as with IP address.|**192.168.178.90** (`192,168,178,90`)|
|[](){#BSSID}-|`bssid`|Enter a specific BSSID address here to ensure connecting to a specific access point. Set to all zeros under normal circumstances.|(`0x00, 0x00, 0x00, 0x00, 0x00, 0x00`)|
|-|`ntp_server`|Set an NTP server here to acquire exact time for BSB-LAN. Set to empty string if you don't want to use NTP. ESP32-based microcontrollers only.|(`pool.ntp.org`)|
|-|`local_timezone`|Timezone to use for NTP. See [here](https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv) for a complete list.|(`CET-1CEST,M3.5.0,M10.5.0/3`)|

### Logging

|Web-Interface|Configuration File|Functionality|Possible settings|
|-------------|------------------|-------------|-----------------|
|**Storage device**|`LogDestination`|Select the destination for logging activities. SD card is highly recommended, as using the internal flash will wear out the internal flash eventually.|**SD card** (`SDCARD`)<br>**Internal Flash Storage** (`FLASH`)|
|**Logging mode**|`LoggingMode`|Set the logging destinations/activities. Multiple selections are possible, for the configuration file, the values have to be added, for example, to send to MQTT broker and to UDP, set the value to `4 + 16 = 20`|**Write to SD card** (`1`)<br>**Calculate 24h averages** (`2`)<br>**Send to MQTT broker** (`4`)<br>**Only send log parameters to MQTT** (`8`)<br>**Send to UDP** (`16`)|
|**Logging Interval**|`log_interval`|Interval for logging activities (in seconds)|**60** (`60`)|
|**Log Parameters**|`log_parameters`|List of logging parameters. See addressing instructions below.|**8700, 8743!2, 8314!2** (`{8700, -1}, {8743, 2}, {8314, 2}`)|
|Log bus telegrams|`logTelegram`|Log raw bus telegrams, such as broadcast messages or unknown telegrams|**Off** (`LOGTELEGRAM_OFF`)<br>**Log all bus telegrams** (`LOGTELEGRAM_ON`)<br>**Log unknown bus telegrams only** (`LOGTELEGRAM_UNKNOWN_ONLY`)<br>**Log broadcast bus telegrams only** (`LOGTELEGRAM_BROADCAST_ONLY`)<br>**Log unknown broadcast bus telegrams only** (`LOGTELEGRAM_UNKNOWN_ONLY + LOGTELEGRAM_BROADCAST_ONLY`)|
|**24h averages parameters**|`avg_parameters`|List of parameters for generating 24 hour averages. See addressing instructions below.|**8700, 8743!2, 8314!2** (`{8700, -1}, {8743, 2}, {8314, 2}`)|
|-|`replaceDisabled`|In parameters with numerical values, this setting defines the value for a deactivated/inactive status. Defaults to `---`; Home Assistant expects `None`, others might expect `0` in order to work properly.|(`---`)|
|-|`#define DEFAULT_DAYS_TO_PLOT`|Define default number of days to plot logging data|(`3`)|

### MQTT

|Web-Interface|Configuration File|Functionality|Possible settings|
|-------------|------------------|-------------|-----------------|
|**MQTT Broker server**|`mqtt_broker_addr`|Hostname/IP of the MQTT broker|**my-mqtt-broker.local** (`my-mqtt-broker.local`)|
|**MQTT Username**|`MQTTUsername`|Optional username for MQTT broker|**MyMQTTusername** (`MyMQTTusername`)|
|**MQTT Password**|`MQTTPassword`|Optional password for MQTT broker|**MyMQTTpassword** (`MyMQTTpassword`)|
|MQTT Device ID|`MQTTDeviceID`|Device identifier for MQTT|**BSB-LAN** (`BSB-LAN`)|
|MQTT Topic prefix|`MQTTTopicPrefix`|Topic prefix for MQTT|**BSB-LAN** (`BSB-LAN`)|
|MQTT Usage|`mqtt_mode`|Set the format for MQTT messages|**Plain text** (`1`) - Send parameter number and value in plain text format<br>**JSON** (`2`) - Send messages in JSON format (parameter number and value only)<br>**Rich JSON** (`3`) - Send parameter number/name/value/unit/error in JSON format.|
|MQTT Units|`mqtt_unit_set`|Types of units to be sent to MQTT|**Localized** (`CF_MQTT_UNIT_LOCALIZED`) sends unit strings in the configured language, exactly as shown in the BSB-LAN web interface.<br>**Home Assistant** (`CF_MQTT_UNIT_HOMEASSISTANT`) sends unit strings in Home Assistant compatible format.<br>**None** (`CF_MQTT_UNIT_NONE`) will send MQTT messags with no unit text.<br>**Note:** This setting only applies to MQTT mode 3 (Rich JSON) and MQTT auto-discovery. It does not affect the web interface which will always show units in the localized language.|

### Sensors and external devices

|Web-Interface|Configuration File|Functionality|Possible settings|
|-------------|------------------|-------------|-----------------|
|OneWire Pins|`One_Wire_Pin`|Set the OneWire pin (use `-1` in configuration file to disable)|**10** (`10`)|
|DHT Pins|`DHT_Pins`|Set the DHT22 sensor pins (use `-1` in configuration file to disable)|**11, 12, 13** (`11, 12, 13, -1, -1, -1, -1, -1, -1, -1`)
|BME280 sensors|`BME_Sensors`|Set number of BME280 sensors on the I2C bus. You need to have access to I2C pins. Fixed addresses `0x76` and `0x77` will be used. Use `0` to disable.|**1** (`1`)|
|MAX! Usage|`enable_max_cul`|Enable or disable connection to CUNO/CUNX/modified MAX!Cube|**On** (`true`)<br>**Off** (`false`)||
|IP address cube|`max_cul_ip_addr`|IP address of the CUNO/CUNX/MAX!Cube|**192.168.178.21** (`192,168,178,21`)|
|MAX! Devices|`max_device_list`|IDs of MAX! devices to be polled. These IDs can be found on a sticker of the device. After entering them here, each device needs to be set into pairing mode. This has to be repeated every time the EEPROM layout of BSB-LAN is changed (see ChangeLog).|**KEQ0502326, KEQ0505080, KHA0002948** (`"KEQ0502326", "KEQ0505080", "KHA0002948"`)|
|IPWE Usage|`enable_ipwe`|Enable IPWE extension (`/ipwe.cgi`)|**On** (`true`)<br>**Off** (`false`)|
|IPWE Parameters|`ipwe_parameters`|List of parameters for display in IPWE extension. See addressing instructions below.|8700, 8743!2, 8314!2 ({8700, -1}, {8743, 2}, {8314, 2})|

### Debugging

|Web-Interface|Configuration File|Functionality|Possible settings|
|-------------|------------------|-------------|-----------------|
|Debugging Usage|`debug_mode`|Select debug output|**Off** (`0`)<br>**Serial** (`1`)<br>**Telnet** (`2`)|
|Verbosity mode|`verbose`|Enable or disable verbose debug messages (do not turn off unless advised)|**On**  (`1`)<br>**Off** (`0`)|
|Raw data mode|`monitor`|Enable or disable raw data mode (do not turn on unless advised!)|**On**  (`1`)<br>**Off** (`0`)|
|Display unknown parameters|`show_unknown`|Try and display also parameters not supported by destination device|**On** (`true`)<br>**Off** (`false`)|

---
## Adressing different heating controllers

In order to address parameters from devices other than the default destination device in the web-interface, you need to add an exclamation mark followed by the device address (see above for converting segment/device notation to device address).  
For example, parameter 8700 from device address 1 would be written as `8700!1`instead of just `8700`.  

For the configuration file, parameters are listed in the form `{parameter number, destination address}`. Parameter 8700 from device address 1 would thus be written as `{8700, 1}`.  To address the default destination, you can do so by using `-1`. 

