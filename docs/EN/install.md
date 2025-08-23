# Installation
Installing BSB-LAN requires three steps:

1. Installing the Arduino IDE in order to flash the BSB-LAN software onto the microcontroller
1. Assembling the hardware parts
1. Connecting BSB-LAN to the heating system

---
## Installing the Arduino IDE and flashing BSB-LAN

1. [Download](https://github.com/fredlcore/BSB-LAN/archive/refs/heads/master.zip) and unpack the current BSB-LAN version from the master repository or use *git* to [clone](https://github.com/fredlcore/BSB-LAN.git) the repository.
1. Navigate to the BSB_LAN folder and rename the following files:
    1. `BSB_LAN_custom_defs.h.default` to `BSB_LAN_custom_defs.h`
    1. `BSB_LAN_config.h.default` to `BSB_LAN_config.h`.
1. [Download](https://www.arduino.cc/en/software) and install the Arduino IDE for your system. Advanced users may [refer to our Wiki](https://github.com/fredlcore/BSB-LAN/wiki/Installing-BSB%E2%80%90LAN-using-arduino%E2%80%90cli) for using the command-line-based `arduino-cli` tool.
1. Connect your microcontroller (ESP32 or Arduino Due) to your computer and start the Arduino IDE. If the microcontroller is not detected as a USB device, you may have to install the USB driver provided by the manufacturer of the microcontroller first.
1. Go to ***Tools/Board/Board Manager*** and make sure that the framework for your board is installed ("esp32 by Espressif Systems" for ESP32 microcontroller, "Arduino SAM Boards (32-bits ARM Cortex-M3) by Arduino" for Arduino Due microcontroller)
1. Again, go to ***Tools/Board*** and select your microcontroller:
    1. *ESP32 Dev Module* for the Joy-It ESP32 NodeMCU.
    1. *Olimex ESP32-EVB* for the ESP32-based Olimex EVB .
    1. *Olimex ESP32-POE-ISO* for the ESP32-based Olimex POE ISO
    1. *Arduino Due (Programming Port)* for the Arduino Due. **Do not use the Native USB Port here**!
1. Now, go to ***Tools*** and select the port that your microcontroller is connected to.
1. Again, go to ***Tools*** and select the proper upload speed (up to 460800 for ESP32, 115200 for Arduino Due).
1. [](){#SPIFFS}For ESP32-based microcontrollers, again, go to ***Tools/Board*** and select "Minimal SPIFFS" for partition scheme (**do not confuse this with the similar "Minimal" partition scheme** which is different and not working in our case). **If you don't set the correct parition scheme, the firmware will not fit into the ESP32!**
1. Go to ***File/Open*** and navigate to the BSB_LAN folder and double-click on `BSB_LAN.ino`. The project will open.
1. You may now proceed to [configure](configure.md) BSB-LAN.
1. When you are done configuring, go to ***Sketch/Upload*** and upload the BSB-LAN software to the microcontroller. For ESP32 microcontrollers, the message "Hard resetting via RTS pin..." is **not** an error message, but means that the upload was successful and the ESP32 is now restarting.
1. The same process has to be done with every future update, including when adding the device-specific parameter list.

---
## Assembling the BSB-LAN adapter
You can either get a fully assembled adapter from Frederik (bsb(ät)code-it.de) or build one on your own (see the folder `schematics` for the schematics). Once you have the BSB-LAN adapter ready, you just need to plug it into the microcontroller. If you are using an Olimex microcontroller, double-check that the adapter really sits in the center of the connector, because it still fits even if it is moved by one pin row to the left or right.

---
## Connecting BSB-LAN to the heating system

Once the microcontroller and the BSB-LAN adapter are ready, perform the following steps to connect BSB-LAN to the heating system:

1. Unplug the microcontroller from your computer and turn off your heating system. Locate the BSB/LPB/PPS connectors. You may have to open your heating system for that. Have a look at the list of [supported heating systems](supported_heating_systems.md) to get an idea where the pins are located.<br>***Do all this at your own risk!***<br>***If you are not careful, you may damage your equipment!***<br>**Especially take care to prevent electrostatic discharge (ESD) which can destroy both BSB-LAN and the heating controller!**
1. Now plug the BSB-LAN adapter onto the microcontroller and connect the `+` screw connector to the `CL+` (BSB), `DB` (LPB) or `A6` (PPS, different connector names are possible) connector, and the `-` screw connector to the `CL-` (BSB), `MB` (LPB) or `M` (PPS) connector.  
If your controller is missing a proper plug for the connector, you might improvise with a [6.35mm flat connector sleeve](https://www.reichelt.com/de/en/shop/product/flat_connector_sleeve_width_6_35_mm_yellow-7910).  
If there is no empty connector, there is no problem adding the wires for BSB-LAN to an already "used" connector, provided the wires are inserted carefully. Regarding the cables, an (ideally screened/shielded) twisted two-core cable is recommended [by Siemens](https://sid.siemens.com/v/u/20140). However, a number of users have also been successful with plain bell wire if the distances are not too long.
1. [](){#PowerSupply}Now you need to power on the microcontroller. Take note that the heating system does not power the microcontroller, even if the BSB-LAN adapter's LED turns on when you connect it to the heating system. You need to supply power to the microcontroller via its USB port (or via PoE on the Olimex POE-ISO). Make sure to use a stable power supply with at least 2 amperes. Once the microcontroller is powered on, turn on the heating system. The red LED of the BSB-LAN adapter should alight. It should flicker occasionally.
1. Now open your webbrowser and open the IP address of BSB-LAN. If MDNS is enabled, you can directly go to [`http://bsb-lan.local`](http://bsb-lan.local). Otherwise, you can find the IP address of BSB-LAN either in your router, or you connect the microcontroller to your PC and open the Arduino IDE and go to ***Tools/Serial Monitor*** and set the serial monitor speed to 115200. Restart the microcontroller, and the IP address will be displayed upon connecting to the network.

---
## Generating the device-specific parameter list

Once you access BSB-LAN for the first time, you will see that only very few parameters are shown on the device’s web interface. This is because each model of the Siemens controller built into your heating system supports a different set of parameters. Previously, I provided a list of parameters collected from all different kinds of heating systems, but it turned out that this list was ambiguous or even contained errors that we couldn’t fix reliably. This list is still available in release version 2.2.x of BSB-LAN and can be copied from there if needed.  
However, it is not advisable to do so because the said ambiguities and errors pose too great a risk of misconfiguring the heating system. Instead, it is recommended to click on the "**Device-specific parameter list**" button in BSB-LAN's menu and send the generated list to Frederik (bsb(ät)code-it.de). From this file, a parameter list can be generated that fits exactly the controller of your heating system. Unfortunately, this process cannot be automated yet, but at least it has to be done just once. These raw data do not contain any settings or other kinds of personal data, just the parameter structure of the heating system.  
It’s in my own interest to create and return these parameter lists without any delay, but I ask for your understanding if it takes a bit longer due to work or family matters.  

Once you have received the parameter list (or taken the one from version 2.2.x), you have to replace the existing `BSB_LAN_custom_defs.h` file with the one sent to you, compile it and flash it again. Now you are ready to access all parameters.

---
# Updates

If you want to update to a new version of BSB-LAN, the following points should be noted:

- Basically, an update is the same as a new installation.
- Check the updated file `CHANGELOG.md` to see what has changed between your version and the updated version.
- The settings in `BSB_LAN_config.h` are not overwritten, but may need to be adjusted. More details can be found in the file `CHANGELOG.md`.
- The device-specific parameter list `BSB_LAN_custom_defs.h` is also not overwritten and remains unchanged; it does not need to be recreated! Only in rare cases are small modifications necessary, which are then indicated in the file `CHANGELOG.md`.
- Some updates change the EEPROM structure (see notes in the file `CHANGELOG.md`). If this is the case, the BSB LAN settings are rewritten to the EEPROM based on the values ​​in the `BSB_LAN_config.h` file. Before an update, the settings in the `BSB_LAN_config.h` file should also be checked again to ensure at least network access.

## Subsequent updates on ESP32-based microcontrollers "over the air" (OTA)

If you are running BSB-LAN on an ESP32-based microcontroller and have enabled Over-the-Air Updates in the [settings](configure.md), you can perform future updates of BSB-LAN using your browser. To do that, instead of using *Sketch/Upload*, you need to select ***Sketch/Export Compiled Binary***. This will create a `build` folder in your BSB-LAN folder in which you will find among others the file `BSB_LAN.ino.bin`. Now open [http://bsb-lan.local:8080](http://bsb-lan.local:8080) and select and upload that file. Do not interrupt the upload process. You may try to access BSB-LAN from a different browser window to see if the process is completed.  
Please take note that this only applies to ESP32-based microcontrollers. Arduinos do not support this functionality.

