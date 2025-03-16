# Troubleshooting

BSB-LAN tries to make accessing your heating system as easy as possible, but there are always things that can go wrong. If you still have a problem after reading this document as well as the [FAQ](faq.md), please [open up a bug report](https://github.com/fredlcore/BSB-LAN/issues/new?assignees=&labels=&projects=&template=bug_report.md&title=%5BBUG%5D) on the project's GitHub page and make sure that you provide us with all the necessary log files and further required details, especially from the Serial Monitor (or *SerMo* in short).  
Before doing so, however, make sure that you install **the most recent version of BSB-LAN from the master repository** (not the release version), even if yours is "just" a few days old. Still, a lot could have happned since then :)!
### Using the Serial Monitor
- Access the Serial Monitor by going to ***Tools/Serial Monitor*** in the Arduino IDE.
- Set the transmission speed to 115200 at the top right corner of the serial monitor window. 
- Make sure you copy the messages right from the moment your microcontroller boots (indicated by the `READY` message) until the moment you encounter the problem.
- Please **do not send screenshots**, only plain text files.  
- Watch my short [tutorial video](https://youtu.be/DsYPhihl11o) in case you have questions.

The Serial Monitor in the Arduino IDE currently has a bug that allows you to only copy those parts of the Serial Monitor messages that you can see on the screen. Although this means that copying larger portions of log messages is tedious, you still have to provide the complete log in order to get support. Increasing the size of the Serial Monitor window helps a little.

---
## Compiling fails: "Sketch too big"
- [Select the *Minimal SPIFFS* partition scheme][SPIFFS] in the Arduino IDE under ***Tools/Partition Scheme***.   
**Attention:** This setting is reset to default when updating the ESP32 framework!  
If you are using over-the-air updates, you have to flash the software once via USB after changing the partition scheme before OTA updates will work again.

---
## No access to web-interface anymore
If you have changed the settings in such a way that you cannot access the web-interface anymore, there are two ways to restore the system:  

- **If you can flash the device:**
    1. Configure `BSB_LAN_config.h` with correct, working settings.
    1. Set `UseEEPROM` to `0`.
    1. Flash BSB-LAN onto the microcontroller.
    1. You can now access BSB-LAN. Go to "Settings" and save the settings. This will store the working settings to the EEPROM.
    1. Now edit `BSB_LAN_config.h` *again*(!) and set `UseEEPROM` to `1` and flash BSB-LAN again to the microcontroller. 
    1. Only now will BSB-LAN read and use the settings from the EEPROM, so you can make further changes in the web-interface.
- **If you cannot flash the device:**
    1. If you cannot flash the device on site, you can reset BSB-LAN to the last `BSB_LAN_config.h` setting by connecting two pins *before and during booting the microcontroller*:
        - ESP32-Olimex: Connect pins 34 and 3V3.
        - ESP32-NodeMCU: Connect pins 21 and 3V3.
        - Arduino Due: Connect pins 31 and 33.
    1. If the pins were successfully connected, the built-in LED of the microcontroller will flash slowly for four seconds.
    1. Afterwards open the configuration in the web-interface, check all settings in the configuration and save them. This will store the working settings to the EEPROM.
- **Temporary access point on an ESP32-based microcontroller**
    - On an ESP32-based microcontroller, BSB-LAN will set up its own wireless access point named `BSB-LAN` if it cannot connect to any network. In this casee, you can connect to this access point with the password `BSB-LPB-PPS-LAN` and access BSB-LAN via the IP address `http://192.168.4.1` and see if you can fix the configuration this way. Keep in mind that if you have set a passkey or HTTP username and password, these are still required if these details are stored in EEPROM or `BSB_LAN_config.h`.

---
## I can only access very few parameters via BSB/LPB!
- Initially, BSB-LAN only comes with a small set of parameters that work on (almost) every heating system. You need to get a [device specific parameter list](install.md#generating-the-device-specific-parameter-list). If you still have access to only a few parameters after adding the device specific parameter list, then you haven't overwritten the old file, but have probably added a second copy (which is then ignored during compilation).

---
## Category list suddenly so small
- BSB-LAN needs to detect the heating system's controller to determine the categories to display. If BSB-LAN is not connected to the controller or the detection otherwise fails, only a few universal categories are displayed.

---
## Cannot read any parameters / device family is `0`
- Wrong bus type (BSB instead of LPB or vice versa).
- If the red LED of the adapter is not on (and ideally slightly flickering), there is a problem with the wiring between the adapter and the heating system. The red LED will come one once the adapter is connected correctly, even if the BSB-LAN adapter isn't even connected to the microcontroller!

---
## No data even though the adapter's red LED is on
- Make sure the adapter is connected to CL+/CL- and not to the third (G+) pin: G+ will drive the LED, but it's not a data line.
- [Make sure you have powered on the microcontroller][PowerSupply]. You may think that the heating system powers the microcontroller because the LED on the BSB-LAN adapter is on, but it doesn't. You need to power it separately.
- With the adapter for the Olimex microcontrollers: Make sure that the BSB-LAN adapter board sits **exactly** in the center of the UEXT connector. It will still fit in, if it's shifted one pin left or right, but it won't work.
- Make sure the RX/TX pins are set/detected correctly. The startup sequence in the Serial Monitor will show you what pins have are used or have been auto-detected.

---
## No or unreliable network connection
- Try powering the microcontroller via USB from a laptop. We have had many cases where power supplies were unreliable despite having sufficient ratings.
- Look at the Serial Monitor log to check if the microcontroller could acquire an IP address. If not, then your network settings or physical connection may be faulty.

---
## No connection to hidden WiFi network possible
- Yes, that is a known restriction. The only way to do that is to [set the BSSID explicitly][BSSID] in `BSB_LAN_config.h`.

---
## Room temperature (or any other parameter) cannot be set
- Check BSB-LAN's settings and make sure that [write access is enabled][WriteAccess] and set to *standard* or *complete*.  
Furthermore, some parameters are only writeable. For example, the current room temperature can only be set via parameter 10000, but it cannot be read from the same parameter. To check these values, you have to refer to the corresponding parameters in the `status` category. For example, for the current room temperature, on most heaters, this is stored in parameter 8740 for heating circuit 1.

---
## Web-interface freezes when making new connection
- BSB-LAN is not a multi-tasking system. This means it can attend to one task at a time. So even if a URL command is aborted (by closing the browser window), BSB-LAN might not detect this and only start serving new requests once the previous one is finished.

---
## The Serial Monitor is not showing readable data
- Make sure the speed is set correctly to 115200 bps.
- Make sure the correct port is selected.
