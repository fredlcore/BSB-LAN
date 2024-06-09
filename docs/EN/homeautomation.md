# Connecting BSB-LAN to home automation systems

BSB-LAN provides three ways to connect to home automation systems: 
1. Exchanging data via MQTT (recommended)
2. Exchanging data via JSON
3. Exchanging data via URL commands and screen scraping
4. Using supported modules for specific home automation systems

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

## Exchanging data via JSON

BSB-LAN allows to query and set parameters via JSON structures and also provides numerous information about the parameters and category structures this way. The JSON API is accessd via [URL commands](using.md) and the `openapi.yaml` file provided in this repository can be used with [Swagger](https://editor.swagger.io/?url=https://raw.githubusercontent.com/fredlcore/bsb_lan/master/openapi.yaml) to explore its possibilities and functionalitites.

## Exchanging data via URL commands and screen scraping

For simpler solutions, using the URL commands to query and set parameters can be used to control BSB-LAN from other systems. Screen scraping is possible since the project tries not to break certain ways of displaying data, so that parsing with regular expressions remains feasible. Nevertheless, for most scenarios one of the other options will probably be preferrable.

## Using supported modules for specific home automation systems

For some systems, specific modules exist that can be used to access BSB-LAN seamlessly:

### Homebridge

BSB-LAN user Michael has written a [plugin for Homebridge](https://www.npmjs.com/package/@bsblan/homebridge-bsblan-thermostat). Thank you!

### ioBroker

GitHub user @hacki11 has developed [an adapter for ioBroker](https://github.com/hacki11/ioBroker.bsblan). Thank you!

### Jeedom

GitHub user @bernard-dandrea has written a [plugin for Jeedom](https://bernard-dandrea.github.io/jeedom-BSBLAN/fr_FR/) (with a French description). Thank you!

### Node-RED

GitHub user @konne wrote a [module for Node-RED](https://github.com/node-red-contrib/node-red-contrib-bsb-lan). Thank you!

### OpenHAB

Since version 2.5.4, there exists a [binding](https://www.openhab.org/addons/bindings/bsblan/) that is officially part of OpenHAB

### SmartHomeNG

GitHub user @thensty wrote a [plugin for SmartHomeNG](https://github.com/smarthomeNG/plugins/tree/develop/bsblan). Thank you!

### Volkszaehler

GitHub user @lapixo has contributed a [script for the Volkszaehler project](https://github.com/lapixo/volkszaehler_bsb-lan/tree/main). Thank you!

### Bash script

GitHub user @khfm has written [Bash scripts](https://github.com/khfm/bsb-lan-readout) to query data and display it using gnuplot. Thank you!