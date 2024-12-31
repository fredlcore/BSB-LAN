# What is BSB-LAN?
<div style="float:left"><svg class='logo' viewBox='0 0 400 400' xmlns='http://www.w3.org/2000/svg' height=100% width=100%><path id='b' d='m98 47-63 1c-6 0-12 4-11 11v88c1 5 3 10 10 11l79-1c25-1 24-53 4-61 11-5 18-49-19-49zM48 72h52c1 10-2 18-11 19l-38 1v22l43-1c14 0 14 11 14 20H48Z'/><use href='#b' x='246'/><path d='m268 350 1-100c2-14 14-16 29-1l56 59v-69h25l-1 99c1 12-12 17-22 7l-63-64v69Zm-65-173c-112 90-67 155-34 173-4-11-7-23-6-38h60c0 29-4 31-8 40 57-35 42-86 15-112-21-21-32-40-27-63zm-10 81c13 10 18 20 24 30h-48c5-9 8-18 24-30zM21 239h25v86h77v25l-90-1s-11 1-11-12z M246 47v25h-68c-10 1-11 18 1 18l47 1c41 3 37 63 2 66l-82 1v-25h77c11 0 12-18 0-18h-48c-42-5-37-67 0-67z'/></svg></div>
[BSB-LAN is a software](https://www.bsb-lan.de)/hardware solution for accessing the [“Boiler-System-Bus” (BSB)][BSB], the [“Local-Process-Bus (LPB)”][LPB] and the [“Punkt-zu-Punkt-Schnittstelle” (PPS)][PPS]. The BSB-LAN hardware is available for various *ESP32*-based microcontrollers (ESP32 NodeMCU, Olimex EVB, Olimex POE-ISO) as well as for an *Arduino Due* with Ethernet shield. It allows accessing the heating systems from Atlantic, Brötje, Elco and many other manufacturers via LAN/WLAN, provided that they use one of the Siemens controllers listed below.  
BSB-LAN makes it possible to monitor and control the heating system and log any given values. This project supports almost all parameters available on the heating systems and can be a more comprehensive and cost-effective alternative to the OZW 672, OCI 700 or Remocon Net B.

Optional [integration into existing smart home systems](homeautomation.md) such as [Home Assistant][HomeAssistant], [ioBroker][ioBroker], [openHAB][openHAB], [Node-RED][NodeRED], [Homebridge][Homebridge], [Jeedom][Jeedom], [SmartHomeNG][SmartHomeNG], [Volkszähler][Volkszaehler], [FHEM][FHEM], [HomeMatic][Homematic], Loxone, IP-Symcon or EDOMI is possible via [MQTT][MQTT], [JSON][JSON] or [HTTP access][using]. 
The adapter can also be used as a standalone logger without LAN or Internet connection when using a microSD card.  
Temperature and humidity sensors can also be connected and their data can also be logged and analyzed. The option of integrating your own code into the BSB-LAN software also offers a wide range of expansion options. 

# Where and how do I begin?
- You are an experienced user? Head on to the [quickstart](quickstart.md) or [update](install.md#updates) instructions. Otherwise (or if you run into problems), please read on!
- Is my heating system supported by BSB-LAN? Please go to the [list of supported heating systems](supported_heating_systems.md).
- If you already know that your system is supported, [find out more about the BSB-LAN adapter](bsb-lan_adapter.md) and where to get it.
- If you already have the adapter, you may want to know [how to install the adapter](install.md).
- If you have installed the adapter, you will need to [configure BSB-LAN](configure.md).
- Once you have everything up and running, find out about [how to use BSB-LAN](using.md) or learn more about the ways to [ingetrate BSB-LAN into home automation systems](homeautomation.md).
- If you want to update BSB-LAN and would like to know what has changed since your last installation, please check the [ChangeLog](CHANGELOG.md).
- Our [wiki pages](https://github.com/fredlcore/BSB-LAN/wiki) are continuously growing and provide background knowledge as well as more specialized topics on BSB-LAN and heating systems in general.
- If you run into troubles, have a look at the [troubleshooting page](troubleshooting.md).
- And before you ask anyone else any questions, have a look at our [Frequently Asked Questions (FAQ)](faq.md) first!
