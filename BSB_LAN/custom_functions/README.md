# Custom functions for BSB-LAN

BSB-LAN allows to add custom functions through the following files:

`BSB_LAN_custom_global.h` -> This file allows you to add global variables.  
`BSB_LAN_custom_setup.h` -> This file is called at the end of the `setup()` function.  
`BSB_LAN_custom.h` -> This file is called with every iteration of the `loop()` function.  
  
In this folder, we collect scripts which add a certain functionality that is too specific to be added to the core functionality of BSB-LAN, but can be added through BSB-LAN's custom functions scripts.  
To use these scripts, you have to do two things:  
1. Copy the files of the example you want to use to BSB-LAN's main directory (where also BSB_LAN.ino and BSB_LAN_config.h can be found).
2. Enable the CUSTOM_COMMANDS definement by removing the to leading slashes at the beginning of the line so that it looks like this:  
`#define CUSTOM_COMMANDS`

Theoretically, you can use several of these custom functions at the same time, and sometimes it's as easy as just copy-pasting each code segment one after the other for each file. But do take note that this is similar to writing code for BSB-LAN itself, so be aware of what you are doing.
**Please understand that we cannot give any individual support in case of errors or problems!**

## DHT22 sensor controls fan

This script reads the temperatures from two DHT22 sensors (one outside and one inside) and turns on a fan connected to GPIO 6 in case the absolute inside humidity is higher than the absolute outside humidity and the inside temperature is higher than 15 degrees celsius.

## Map DS18B20 sensors to custom floats

This script takes the readings of DS18B20 sensors and writes them to the custom floats parameters (20700 and above) for easier access.

## Modbus Interface

This set of scripts enable BSB-LAN to be accessed via Modbus. Parameters can be read and written. However, take note that no data type conversion takes place in this script, so only unsigned 16-bit integer values will be transmitted correctly. All other kinds of data types will have to be encoded/decoded accordingly. If you can live with sending/receiving temperature values with their decimal places removed, you can use this script for example to set setpoint temperatures, query outside temperatures or change operation modes without having to worry about conversions.

## Send NTP time to heater

This script connects to an NTP time server and writes the accurate time to the heater's internal clock.

## Send room temperature based on MAX thermostats

This script collects the current temperature of registered MAX! thermostats, calculates an avaerage and sends this average as the current room temperature to the heater (via parameter 10000).

## Set room temperature to sensor value

This script takes the value of one parameter (for examle 20500.1 for the temperature of the first MAX! device) and sends it to the room temperature parameter (10000 for BSB/LPB, 15008 for PPS) every five minutes. This way, BSB-LAN can replace the room temperature sensor function of a room unit when using one of the devices/sensors that BSB-LAN can access out-of-the-box (DS18B20, DHT22, BME280 sensors or MAX! devices).

## Emulation of Room Unit and Presence Buttons

_The pushbutton functionality will need adjustments and is not compatible out-of-the-box from version 3 onwards._  

With the setup of the BSB-LAN adapter a room unit can be emulated if you add one or more sensors and push buttons.
The following functions are implemented in the code:
- Integration fo connected sensors for measuring and transmitting the room temperature(s) to the desired heating circuit(s)
- Triggering a DHW push by using a pushbutton
- Using the presence function for the heating circuits 1-3 by using a pushbutton (automatic detection of the present state with the corresponding change between comfort and reduced mode in the automatic mode).
More details can be found in the README file in each folder.
