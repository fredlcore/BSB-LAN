# The BSB-LAN adapter
---
### Adapter boards available - contact Frederik at bsb(ät)code-it.de (German or English) for more details.
---
In order to connect to your heating system with a microcontroller, you need to have an adapter board that does the necessary logic-level conversion:
<img src="../images/Logic Level Adapter.jpg">
The adapter is then plugged right onto the microcontroller, either underneath the pins of the ESP32-NodeMCU or onto the UEXT connector of the Olimex:

<img src="../images/Logic Level Adapter on NodeMCU.jpg">  
<img src="../images/Logic Level Adapter in Case.jpg">  
<img src="../images/Logic Level Adapter on Olimex EVB.jpg">  


The two different types of ESP32 adapters (Olimex and ESP32-NoceMCU) only vary in the location of their connectors, the other parts of the board are identical.  
The Arduino Due board contains an EEPROM chip because the Due does not come with on-board EEPROM. Therefore, you can re-use the Arduino Due board on an ESP32 microcontroller (if you connect the correct pins with wires), but you cannot use an adapter for the ESP32 on an Arduino Due.
---
# Suitable microcontrollers

BSB-LAN can be installed on three different types of microcontrollers:  

1. ESP32-Olimex  
1. ESP32-NodeMCU (30 pin version only!) and  
1. Arduino Due.  

Olimex produces several kinds of boards:  
We recommend either the [Olimex ESP32-EVB](https://www.olimex.com/Products/IoT/ESP32/ESP32-EVB/open-source-hardware) or the [Olimex ESP32-POE-ISO](https://www.olimex.com/Products/IoT/ESP32/ESP32-POE-ISO/open-source-hardware). The simple POE version (without the "ISO") is not recommended because it does not allow to be connected to PoE Ethernet and USB at the same time.

The [Arduino Due](https://store.arduino.cc/products/arduino-due) requires an [Ethernet Shield](https://store.arduino.cc/products/arduino-ethernet-shield-2) in order to access the local network.

Each of the different controllers have their advantages and disadvantages:

|Functionality|ESP32-Olimex|ESP32-POE-ISO|ESP32-NodeMCU|Arduino Due|
|:------------|:----------:|:-----------:|:-----------:|:---------:|
|Ethernet/LAN |X           |X            |-            |X          |
|WiFi/WLAN    |X           |X            |X            |-          |
|Over-the-air updateable|X |X            |X            |-          |
|Built-in micro-SD card |X |X            |-            |-          |
|Accessible GPIOs|2 (GPIO13/16)|some|some|many         |