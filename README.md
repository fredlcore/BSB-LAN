# BSB-LPB-PPS-LAN

Die deutsche Fassung dieser Datei gibt es [hier](README_de.md).

Before getting started, please read through the manual [here](https://docs.bsb-lan.de).

BSB-LAN is a software/hardware solution for accessing the “Boiler-System-Bus” (BSB), the “Local-Process-Bus (LPB)” and the “Punkt-zu-Punkt-Schnittstelle” (PPS). The adapter is available for various *ESP32*-based microcontrollers (ESP32 NodeMCU, Olimex EVB, Olimex POE-ISO) as well as for an *Arduino Due* with Ethernet shield. It allows accessing the heating systems from Atlantic, Brötje, Elco and many other manufacturers via LAN/WLAN, provided that they use one of the Siemens controllers listed below. BSB-LAN makes it possible to control or regulate the heating and log any given values. This project supports almost all parameters available on the heating systems and can be a more comprehensive and cost-effective alternative to the OZW 672, OCI 700 or Remocon Net B.

---

***Interface kits available!***  
**Interface boards are available for the ESP32 upon request. These can simply be plugged on top of one of the listed microcontrollers.Getting the board from here helps supporting this project in the future, so if you are interested, please send Frederik an e-mail (German or English) to <br /> bsb (ät) code-it.de <br /> for further informations.**  

---  

Using the adapter and the BSB-LAN software, various values and parameters can easily be monitored, logged and, if so desired, controlled and changed via a web-interface.
Optional integration into existing smart home systems such as FHEM, openHAB, HomeMatic, ioBroker, Loxone, IP-Symcon, EDOMI, Home Assistant, SmartHomeNG or Node-RED is possible via MQTT, JSON or HTTP access. 
The adapter can also be used as a standalone logger without LAN or Internet connection when using a microSD card.  
Temperature and humidity sensors can also be connected and their data can also be logged and analyzed. The option of integrating your own code into the BSB-LAN software also offers a wide range of expansion options. 
        
**In the following, some model series from different manufacturers are listed, which usually have installed BSB-LAN compatible controllers:**  
- Broetje: BBK, BBS, BGB, BLW (**not BLW NEO!**), BMR, BOB, BSK, Eurocontrol, SGB, SOB, SPK, WBS, WGB, WGB EVO, WGB Pro EVO, WGB-M, WGB-U, WOB 
- Boesch: heat pumps with RVS controller type
- Elco: Aerotop, Aquatop, Rendamax, Straton, Thision, Thision S, Thision S Plus, Trigon S Plus  
- ATAG: QR  
- Atlantic: Alféa Evolution, Axeo, Excellia, Extensa, Hynea hybrid duo gaz, Varmax  
- Austria Email: LWP, LWPK  
- Baxi: Luna Platinum
- Chappée: Klista
- CTA: Optiheat  
- Deville: 9942, 9981
- ECO: AiWA, AW, BW, DW, heatLite, Star, TBW, TWW, WW, WWi, TWW
- EcoStar: Ecodense WT-S 45
- EVI Heat: Combi-7
- Fernwärme: RVD230
- Froeling: Rendagas Plus
- Fujitsu Waterstage: Comfort, Duo
- Geminox: Thrs
- Gruenenwald: Greenheat
- GS: UnoTec
- Hansa: SND
- Herz: Commotherm 5 DeLuxe
- Interdomo: Domostar GBK 25H/SH
- MAN/MHG: Ecostar 200
- MHG: Procon E, ecoWP Xe
- Oilon: SH, SHx
- Olymp: SHS, WHS
- Sieger: TG11
- Sixmadun: TG11BE
- Sunex: Nexus
- Termomax: Termo ÖV
- Thermics: Energie
- Thermital: TBox Clima TOP
- Tifell: Biofell
- Viessmann: Vitotwin 300-W
- Wamak: AiWa, DB
- Weishaupt: WTU

If your heater has one of the following controllers, but your model ist not listed in our manual, feel free to get in touch with us, as these models have been confirmed working:  
AVS37, AVS55, AVS71, AVS74, AVS75, AVS77, AVS79, LMS14, LMS15, LMS15, LMU64, LMU74, LMU75, RVA61, RVA63, RVA33, RVA36, RVA43, RVA46, RVA47, RVA53, RVA60, RVA61, RVA63, RVA65, RVA66, RVC32, RVD110, RVD115, RVD120, RVD125, RVD130, RVD135, RVD139, RVD140, RVD144, RVD145, RVD230, RVD235, RVD240, RVD245, RVD250, RVD255, RVD260, RVD265, RVL469, RVL470, RVL471, RVL472, RVL479, RVL480, RVL481, RVL482, RVP340, RVP350, RVP351, RVP360, RVP361, RVP5xx, RVS13, RVS21, RVS23, RVS26, RVS41, RVS43, RVS46, RVS47, RVS51, RVS53, RVS61, RVS63, RVS65, RVS68, RWI65, WRI80
<BR><BR>

<B>Attention!</B><BR>
Some companies which previously used BSB/LPB in their heating systems have now switched to other systems for their lower-cost devices. Examples are Brötje's WLC/WLS/BOK series. These are not compatible with BSB/LPB and only allow very limited parameters to be configured by the user. If you have one of these heating systems, you are so far out of luck to configure and monitor your heating system as it can be done with the more expensive (but BSB/LPB compatible) devices mentioned above among others.

Instructions on how to configure etc. can be found in the <A HREF="https://docs.bsb-lan.de">manual</A>.<BR>
The forum thread that led to the development of this interface can be found <A HREF="http://forum.fhem.de/index.php?topic=29762.new;topicseen#new">here</A>.<BR>
(Forum is in German, but several members speak English)

Please take note that while the board can also be used on the Raspberry Pi, the software provided here only runs on the ESP32 and Arduino Due respectively! For using the board with the Pi, you have to use the software bsb_gateway which is available <A HREF="https://github.com/loehnertj/bsbgateway">here</A>. Please also note that the functionality differs significantly, and that you would have to contact the author of bsb_gateway for any question related to it.

Web-Interface screenshots:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/docs/images/Web-Interface.png" size="50%">
<img src="https://github.com/fredlcore/bsb_lan/blob/master/docs/images/Web-Interface2.png" size="50%">

BSB-Board populated for ESP32 Olimex boards:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/docs/images/Logic%20Level%20Adapter.jpg" size="50%">

BSB-Board on Olimex POE inside the project's 3D-printed case:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/docs/images/Logic%20Level%20Adapter%20in%20Case.jpg" size="50%">


<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.
