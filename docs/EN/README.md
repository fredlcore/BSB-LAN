# What is BSB-LAN?

BSB-LAN is a software/hardware solution for accessing the “Boiler-System-Bus” (BSB), the “Local-Process-Bus (LPB)” and the “Punkt-zu-Punkt-Schnittstelle” (PPS). The BSB-LAN hardware is available for various *ESP32*-based microcontrollers (ESP32 NodeMCU, Olimex EVB, Olimex POE-ISO) as well as for an *Arduino Due* with Ethernet shield. It allows accessing the heating systems from Atlantic, Brötje, Elco and many other manufacturers via LAN/WLAN, provided that they use one of the Siemens controllers listed below. BSB-LAN makes it possible to control or regulate the heating and log any given values. This project supports almost all parameters available on the heating systems and can be a more comprehensive and cost-effective alternative to the OZW 672, OCI 700 or Remocon Net B.

Using the adapter and the BSB-LAN software, various values and parameters can easily be monitored, logged and, if so desired, controlled and changed via a web-interface.
Optional integration into existing smart home systems such as FHEM, openHAB, HomeMatic, ioBroker, Loxone, IP-Symcon, EDOMI, Home Assistant, SmartHomeNG or Node-RED is possible via MQTT, JSON or HTTP access. 
The adapter can also be used as a standalone logger without LAN or Internet connection when using a microSD card.  
Temperature and humidity sensors can also be connected and their data can also be logged and analyzed. The option of integrating your own code into the BSB-LAN software also offers a wide range of expansion options. 

# Where and how do I begin?
- You are an experienced user? Head on to the [quickstart instructions](quickstart.md). Otherwise (or if you run into problems), please read on!
- Is my heating system supported by BSB-LAN? Please go to the [list of supported heating systems](supported_heating_systems.md).
- If you already know that your system is supported, [find out more about the BSB-LAN adapter](bsb-lan_adapter.md) and where to get it.
- If you already have the adapter, you may want to know [how to install the adapter](install.md).
- If you have installed the adapter, you will need to [configure BSB-LAN](configure.md).
- Once you have everything up and running, find out about [how to use BSB-LAN](using.md) or learn more about the ways to [ingetrate BSB-LAN into home automation systems](homeautomation.md).
- If you run into troubles, have a look at the [troubleshooting page](troubleshooting.md).
- And before you ask anyone else any questions, have a look at our [Frequently Asked Questions (FAQ)](faq.md) first!
