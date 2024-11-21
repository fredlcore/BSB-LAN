# Quickstart instructions
These quickstart instructions are for users who are familiar with installing and configuring software on their computer. If you need more detailed instructions, please head to the [install instructions](install.md)!

1. Make sure that your heating system is [compatible](supported_heating_systems.md) with BSB-LAN!
1. [Download](https://github.com/fredlcore/BSB-LAN/archive/refs/heads/master.zip) and unpack the current BSB-LAN version from the master repository or use *git* to [clone](https://github.com/fredlcore/BSB-LAN.git) the repository.
1. Navigate to the BSB_LAN folder and rename the following files:
    1. `BSB_LAN_custom_defs.h.default` to `BSB_LAN_custom_defs.h`
    1. `BSB_LAN_config.h.default` to `BSB_LAN_config.h`.
1. [Download](https://www.arduino.cc/en/software) and install the Arduino IDE for your system.
1. Connect your microcontroller (ESP32 or Arduino Due) to your computer and start the Arduino IDE.
1. Go to ***Tools/Board/Board Manager*** and make sure that the framework for your board is installed ("esp32 by Espressif Systems" for ESP32 microcontroller, "Arduino SAM Boards (32-bits ARM Cortex-M3) by Arduino" for Arduino Due microcontroller)
1. Again, go to ***Tools/Board*** and select your microcontroller:
    1. *ESP32 Dev Module* for the Joy-It ESP32 NodeMCU.
    1. *Olimex ESP32-EVB* for the ESP32-based Olimex EVB .
    1. *Olimex ESP32-POE-ISO* for the ESP32-based Olimex POE ISO
    1. *Arduino Due (Programming Port)* for the Arduino Due. **Do not use the Native USB Port here**!
1. Again, go to ***Tools/Board*** and select the proper upload speed (up to 460800 for ESP32, 115200 for Arduino Due).
1. For ESP32-based microcontrollers, again, go to ***Tools/Partition Scheme*** and select "Minimal SPIFFS" or for partition scheme (**do not confuse this with the similar "Minimal" partition scheme** which is different and not working in our case). **If you don't set the correct parition scheme, the firmware will not fit into the ESP32!**
1. Go to ***File/Open*** and navigate to the BSB_LAN folder and double-click on `BSB_LAN.ino`. The project will open.
1. Click on the tab with the filename `BSB_LAN_config.h` and configure at least the following:
    1. Search for `#define LANG DE`: Change `DE` to `EN` for English, `FR` for French etc.
    1. Search for `uint8_t network_type`: Set this to `LAN` if you are using Ethernet/LAN connection. Set this to `WLAN` if you are using WiFi/WLAN.
    1. If you are not using DHCP, configure the following options according to your network (make sure to use a comma, not a dot for IP addresses!):
        1. `byte ip_addr[4] = {192,168,178,88};`
        1. `byte gateway_addr[4] = {192,168,178,1};`
        1. `byte dns_addr[4] = {192,168,178,1};`
        1. `byte subnet_addr[4] = {255,255,255,0};`
        1. `char wifi_ssid[32] = "Your_Wifi_network_name";`
        1. `char wifi_pass[32] = "Your_WiFi_network_password";`
1. Now go to ***Sketch/Upload*** and upload the BSB-LAN software to the microcontroller.
1. Unplug the microcontroller and turn off your heating system. Locate the BSB/LPB/PPS connectors. You may have to open your heating system for that. ***Do all this at your own risk!***
1. Now plug the BSB-LAN adapter onto the microcontroller and connect the `+` screw connector to the `CL+` (BSB), `DB` (LPB) or `A6` (PPS, different connector names are possible) connector, and the `-` screw connector to the `CL-` (BSB), `MB` (LPB) or `M` (PPS) connector.
1. Power on the microcontroller via the USB port or via PoE (Olimex POE-ISO only). Then power on the heating system. The red LED of the BSB-LAN adapter should turn on. It should flicker occasionally.
1. Now open your webbrowser and open the IP address of BSB-LAN. If MDNS is enabled, you can directly go to `http://bsb-lan.local`. You can find the IP address of BSB-LAN either in your router, or you connect the microcontroller to your PC and open the Arduino IDE and go to ***Tools/Serial Monitor***. Restart the microcontroller, and the IP address will be displayed upon connecting to the network.
1. **Done :-)**
---
## It's not working!

Please make sure you check **every entry** in the [Troubleshooting-Section](troubleshooting.md) first before getting in touch with us!

---
## Why do I only see so few parameters?

Once you access BSB-LAN for the first time, you will see that only very few parameters are shown on the device’s web interface. This is because each model of the Siemens controller built into your heating system supports a different set of parameters. Previously, I provided a list of parameters collected from all different kinds of heating systems, but it turned out that this list was ambiguous or even contained errors that we couldn’t fix reliably. This list is still available in release version 2.2.x of BSB-LAN and can be copied from there if needed.  
However, it is not advisable to do so because the said ambiguities and errors pose too great a risk of misconfiguring the heating system. Instead, it is recommended to click on the "**Device-specific parameter list**" button in BSB-LAN's menu and send the generated list to Frederik (bsb(ät)code-it.de). From this file, a parameter list can be generated that fits exactly the controller of your heating system. Unfortunately, this process cannot be automated yet, but at least it has to be done just once. These raw data do not contain any settings or other kinds of personal data, just the parameter structure of the heating system.  
It’s in my own interest to create and return these parameter lists without any delay, but I ask for your understanding if it takes a bit longer due to work or family matters.
