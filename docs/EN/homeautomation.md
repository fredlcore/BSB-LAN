# Connecting BSB-LAN to home automation systems

BSB-LAN provides four ways to connect to home automation systems:  

1. Exchanging data via MQTT (recommended)
1. Exchanging data via JSON
1. Using supported modules for specific home automation systems
1. Exchanging data via URL commands and screen scraping

---
## Exchanging data via MQTT

This is the recommended way to connect BSB-LAN to home automation systems because it allows seamless exchange of data.  
As a prerequisite, a MQTT broker (such as [mosquitto](https://mosquitto.org) is needed, either running locally or via making use of a public service. Some home automation systems such as Home Assistant offer the installation of mosquitto as part of their software.

In BSB-LAN, you need to make or enable at least the following configurations:

- Set **Logging mode** (additionally) to **Send to MQTT Broker**.
- Set **Log Interval** to the time (in seconds) you want the log parameters to be published. 
- Select up to 20 **Log Parameters** you want to be sent to your home automation system.
- Set **MQTT Usage** to **plain text**
- Set **MQTT Broker Server** to the hostname of your MQTT broker (such as the mosquitto server)

If your home automation system supports MQTT auto-discovery (as is the case with Home Assistant), you can call URL command `/M1` and BSB-LAN will send auto-discovery messages for **all available parameters** to the MQTT broker and thus to the home automation system. You may have to clean up afterwards or send a removal message for all these parameters using URL command `/M0`.  
Every time a query is made in BSB-LAN or a parameter changes its value through the room unit, the new value will be sent to the MQTT broker, so even changes made outside of BSB-LAN should be updated into the home automation system, which is why the MQTT approach is the recommended way to connect to a home automation system.

Examples for querying or setting parameters via MQTT would look like this (using mosquitto):  
Query the outside temperature (parameter 8700):  
`mosquitto_pub -h my.mosquitto-broker.local -u USER -P PASSWORD -m "8700" -t BSB-LAN -d`  

Set the comfort temperature setpoint (parameter 710) to 20 degrees:
`mosquitto_pub -h my.mosquitto-broker.local -u USER -P PASSWORD -m "S700=20" -t BSB-LAN -d`  

---

## Exchanging data via JSON

BSB-LAN allows to query and set parameters via JSON structures and also provides numerous information about the parameters and category structures this way. The JSON API is accessd via [URL commands](using.md) and the `openapi.yaml` file provided in this repository can be used with [Swagger](https://editor.swagger.io/?url=https://raw.githubusercontent.com/fredlcore/bsb_lan/master/openapi.yaml) to explore its possibilities and functionalitites.

---
## Using supported modules for specific home automation systems

For some systems, specific modules exist that can be used to access BSB-LAN seamlessly:
[](){#HomeAssistant}
### Home Assistant

While the official plugin no longer works, the MQTT approach above works well with Home Assistant.  
For the details of the implementation, you may also refer to these tutorials:

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
## Exchanging data via URL commands and screen scraping

For simpler solutions, [using the URL commands][using-en] to query and set parameters can be used to control BSB-LAN from other systems. Screen scraping is possible since the project tries not to break certain ways of displaying data, so that parsing with regular expressions remains feasible. Nevertheless, for most scenarios one of the other options will probably be preferrable.