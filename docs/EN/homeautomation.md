# Connecting BSB-LAN to home automation systems

BSB-LAN provides four ways to connect to home automation systems:  

1. Using supported modules for specific home automation systems
1. Exchanging data via MQTT
1. Exchanging data via JSON
1. Exchanging data via URL commands and screen scraping

---
## Using supported modules for specific home automation systems

For some systems, specific modules exist that can be used to access BSB-LAN seamlessly:
[](){#HomeAssistant}
### Home Assistant

While the official plugin no longer works, the MQTT approach (see below) works well with Home Assistant, including the auto-discovery feature.  
Here is a link to a [video in the BSB-LAN YouTube channel](https://youtu.be/DbHEiWm5nBs) that shows how to set up BSB-LAN in Home Assistant using the auto-discovery feature of Home Assistant.

For further details of the implementation, you may also refer to these tutorials:

GitHub user @ryann72 wrote detailed instructions for [BSB-LAN and HomeAssistant/Mosquitto](https://github.com/ryann72/Home-assistant-tutoriel/blob/main/BSB-LAN/tutoriel%20BSB-LAN%20English.md). It is also available in [French](https://github.com/ryann72/Home-assistant-tutoriel/blob/main/BSB-LAN/tutoriel%20BSB-LAN.md).

YouTuber @StoneTime has created two videos (in German) where he shows the [installation of BSB-LAN](https://www.youtube.com/watch?v=n-5I-TUzXuk) as well as [setting it up in Home Assistant](https://www.youtube.com/watch?v=R2Q-_flTPvk). Dankeschön!

YouTuber @ArminasTV has created two videos (in French) where he shows the [installation of BSB-LAN](https://www.youtube.com/watch?v=5lNgNYlZ7M0&t=0s) as well as how to set it up with [Home Assistant and MQTT](https://www.youtube.com/watch?v=WtmKPo1xMio&t=411s). Merci beacoup!

[](){#Homebridge}
### Homebridge

BSB-LAN user Michael has written a [plugin for Homebridge](https://www.npmjs.com/package/@bsblan/homebridge-bsblan-thermostat). Thank you!

[](){#ioBroker}
### ioBroker

GitHub user @hacki11 has developed [an adapter for ioBroker](https://github.com/hacki11/ioBroker.bsblan). Thank you!

[](){#Jeedom}
### Jeedom

GitHub user @bernard-dandrea has written a [plugin for Jeedom](https://bernard-dandrea.github.io/jeedom-BSBLAN/fr_FR/) (with a French description). Thank you!

[](){#NodeRED}
### Node-RED

GitHub user @konne wrote a [module for Node-RED](https://github.com/node-red-contrib/node-red-contrib-bsb-lan). Thank you!

[](){#FHEM}
### FHEM

FHEM forum user Luposoft has written a compact [explanation](https://forum.fhem.de/index.php/topic,29762.msg1129702.html#msg1129702) of the configuration for using FHEM via MQTT. Thank you!

[](){#openHAB}
### openHAB

Since version 2.5.4, there exists a [binding](https://www.openhab.org/addons/bindings/bsblan/) that is officially part of OpenHAB.

[](){#Homematic}
###Homematic

FHEM forum user PaulM has [written a few scripts](https://forum.fhem.de/index.php?topic=29762.1830) to showcase the integration of BSB-LAN into Homematic. Thank you!

[](){#SmartHomeNG}
### SmartHomeNG

GitHub user @thensty wrote a [plugin for SmartHomeNG](https://github.com/smarthomeNG/plugins/tree/develop/bsblan). Thank you!

[](){#Volkszaehler}
### Volkszaehler

GitHub user @lapixo has contributed a [script for the Volkszaehler project](https://github.com/lapixo/volkszaehler_bsb-lan/tree/main). Thank you!

[](){#Bash}
### Bash script

GitHub user @khfm has written [Bash scripts](https://github.com/khfm/bsb-lan-readout) to query data and display it using gnuplot. Thank you!

---

[](){#MQTT}
## Exchanging data via MQTT

This is the recommended way to connect BSB-LAN to home automation systems because it allows seamless exchange of data.  
As a prerequisite, a MQTT broker (such as [mosquitto](https://mosquitto.org)) is needed, either running locally or via making use of a public service. Some home automation systems such as Home Assistant offer the installation of mosquitto as part of their software.

**Attention:** Currently, the mosquitto broker seems to have an issue with handling larger numbers of messages from versions 2.0.16 onwards ([see this bug report](https://github.com/eclipse-mosquitto/mosquitto/issues/2887)). If you encounter the problem that your BSB-LAN entities become "unavailable", especially after using the auto-discovery feature below, please downgrade to mosquitto version 2.0.15. However, be aware that this version has security issues, so make sure that your broker runs at least in a firewalled environment.  

In BSB-LAN, you need to make or enable at least the following configurations:

- Set **Logging mode** (additionally) to **Send to MQTT Broker**.
- Set **Log Interval** to the time (in seconds) you want the log parameters to be published. 
- Select up to 20 **Log Parameters** you want to be sent to your home automation system.
- Set **MQTT Usage** to **plain text**.
- Set **MQTT Broker Server** to the hostname of your MQTT broker (such as the mosquitto server).

If your home automation system supports MQTT auto-discovery (as is the case with Home Assistant), you can call URL command `/M1!<x>` and BSB-LAN will send auto-discovery messages for **all available parameters** from device ID `<x>` to the MQTT broker and thus to the home automation system. You may have to clean up afterwards or send a removal message for all these parameters using URL command `/M0!<x>` if you don't want to use this feature anymore.  

Otherwise, if you want to set up your own connection details, the topic structure of BSB-LAN is as follows:  
`<BSB-LAN MQTT Topic>/<device ID>/<category no.>/<parameter no.>`  
whereas  

- `<BSB-LAN MQTT Topic>` is defined in BSB-LAN's settings (defaults to `BSB-LAN`),  
- `<device ID>` is the ID of the heating controller (usually `0` for the main controller),  
- `<category no.>` is the category number as it is used with URL-command `/K`,  
- `<parameter no.>` is the parameter number, such as `501.1`.  

This structure is followed by one of these topics that determine the action to be performed:  

- `/status` - contains the value of the parameter in the MQTT payload.  
- `/set` - used to set a parameter with the value contained in the published MQTT payload using the SET telegram (default way of setting parameters).  
- `/inf` - same as `/set`, but uses the INF telegram (used for sending room temperature parameter 10000, for example).
- `/poll` - ignores the published value and forces BSB-LAN to immediately update `/status` of the same parameter with a freshly retrieved parameter value. `/poll` can also be accessed directly below the main topic (e.g. `BSB-LAN/poll`) where it accepts a list of parameters separated by comma. These parameters will then immediately have their respective `/status` topics updated in one go. Addressing parameters can either be done in topic-style (with leading slash) or similar to the list of logging parameters in BSB-LAN's settings (see examples below).  

At the same time, the legacy way of sending URL commands via MQTT directly to the main topic (as defined in the settings, defaulting to `BSB-LAN`), is still supported for compatibility reasons, but deprecated. Responses will always be written to `/status` of the above mentioned topic structure.  

The `/status` topic is updated in four ways:

- via logging parameters to MQTT as explained above
- every time a URL query is made to BSB-LAN (can be disabled by **activating** `Only send log parameters to MQTT` in configuration)
- every time a parameter is changed through the room unit (can be disabled by **activating** `Only send log parameters to MQTT` in configuration)
- every time the parameter is updated via the `/poll` topic as explained above

In these cases, the respective values of the parameters affected will be sent to the MQTT broker, so even changes made outside of BSB-LAN are sent to the home automation system, which is why the MQTT approach is the recommended way to connect to a home automation system.  
This also means that, as an alternative to the built-in logging feature of BSB-LAN, you can also just periodically call a URL with the parameters you want to see updated. Since these parameters will also be sent to the MQTT broker, your home automation system will receive them as well.  
For example, if you periodically call the URL `http://bsb-lan.local/700/8700`, both the operating mode of heat circuit 1 (parameter 700) as well as the current outside temperature (parameter 8700) will be sent to the MQTT broker.

### Examples for querying or setting parameters via MQTT using mosquitto ###
Query the outside temperature (device ID 0, category no. 51, parameter 8700):  
`mosquitto_sub -h my.mosquitto-broker.local -u USER -P PASSWORD -t BSB-LAN/0/51/8700/status`  

Set the comfort temperature setpoint (device ID 0, category no. 16, parameter 710) to 20 degrees:  
`mosquitto_pub -h my.mosquitto-broker.local -u USER -P PASSWORD -m "20" -t BSB-LAN/0/16/710/set`  

Force immediate update of outside temperature (device ID 0, category no. 51, parameter 8700):  
`mosquitto_pub -h my.mosquitto-broker.local -u USER -P PASSWORD -m "" -t BSB-LAN/0/51/8700/poll`  

Force immediate update of parameters 700 and 8700 from default device as well as parameter 8326 from device ID 1:  
`mosquitto_pub -h my.mosquitto-broker.local -u USER -P PASSWORD -m "700,8700,8326!1" -t BSB-LAN/poll`  
or  
`mosquitto_pub -h my.mosquitto-broker.local -u USER -P PASSWORD -m "/0/16/700,/0/51/8700,/1/50/8326" -t BSB-LAN/poll`  

**Attention:** Take note that the category number differs from system to system and has to be compared with your system first!

---
[](){#JSON}
## Exchanging data via JSON

BSB-LAN allows to query and set parameters via JSON structures and also provides numerous information about the parameters and category structures this way. The JSON API is accessd via [URL commands](using.md) and the `openapi.yaml` file provided in this repository can be used with [Swagger](https://editor.swagger.io/?url=https://raw.githubusercontent.com/fredlcore/bsb_lan/master/openapi.yaml) to explore its possibilities and functionalitites.

---
## Exchanging data via URL commands and screen scraping

For simpler solutions, [using the URL commands][using] to query and set parameters can be used to control BSB-LAN from other systems. Screen scraping is possible since the project tries not to break certain ways of displaying data, so that parsing with regular expressions remains feasible. Nevertheless, for most scenarios one of the other options will probably be preferrable.