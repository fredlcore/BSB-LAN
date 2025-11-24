# BSB-LPB-PPS-LAN

[<img src="https://img.shields.io/github/last-commit/fredlcore/BSB-LAN">]()
[<img src="https://img.shields.io/github/commit-activity/t/fredlcore/BSB-LAN">]()
[<img src="https://img.shields.io/github/stars/fredlcore/BSB-LAN?style=plastic">](https://github.com/fredlcore/BSB-LAN/stargazers)
[<img src="https://img.shields.io/github/forks/fredlcore/BSB-LAN?style=plastic">](https://github.com/fredlcore/BSB-LAN/forks)
[<img src="https://img.shields.io/github/followers/fredlcore?style=plastic">](https://github.com/fredlcore?tab=followers)

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
- Brötje: BBK, BBS, BGB, BLW (**see exceptions below!**), BMK, BMR, BOB, BSK, BSW, Eurocontrol, ISR, LogoBloc, SGB, SOB, SPK, WBC (**see exceptions below!**), WBS (**see exceptions below!**), WGB (**see exceptions below!**), WMC, WMS, WOB
- **Not working Brötje models: BOK, BLW Mono, BLW Neo, BLW Split, BSW Neo, WBC 22.1/28.1, WBC 14.1/22.1, WGB-K 22.1/28.1, WGB 14.1/22.1/28.1/38.1, WHC, WHS, WLC, WLS and all others with IWR controller**  
- Bösch: heat pumps with RVS controller type
- Elco: Aerotop (**not Aerotop Mono!**), Aquatop, Rendamax, Straton, Thision (**not Thision Mini!**), Thision S, Thision S Plus, Trigon S Plus
- Alarko: Aldens WM/WS
- ATAG: QR
- Atlantic: Alféa, Axeo, Excellia, Extensa, Hynea hybrid duo gaz, Navistem, Perfinox, Varmax
- Austria Email: LWP, LWPK
- Baxi: Luna Platinum, Luna Duo, Block Kondens
- Boesch: SLS
- Chappée: Luna, Klista
- CitrinSolar: proClima
- CTA: Optiheat
- CTC: 380 IC
- Deville: 9942, 9981
- Eco: AiWA, AW, BW, DW, heatLite, Star, TBW, WW, WWi, TWW
- Ecostar: Ecodense WT-S 45
- Etna: II GWS
- EVI Heat: Combi-7
- Fernwärme: RVD230
- Froeling: Rendagas Plus
- Fujitsu Waterstage: Comfort, Duo, WOHA, WSHA, WSYA, WSYK, WSYP
- Gebwell: T2
- Geminox: Thrs
- General: (aka Fujitsu Waterstage) WC13F / WOC13RIYF / WGHA 100DG
- Gorenje: Aerogor Compact, Aerogor Compact EVI, Aerogor ECO Inverter 10 A, Aerogor Split AW, Aerogor Split HD, Aerogor Split HD EVI, Aquagor, Aquagor EVI, Geogor All-In-One, Terragor, Terragor EVI
- Grünenwald: Greenheat
- GS: UnoTec
- Hansa: SND
- Herz: Commotherm 5 DeLuxe
- Hotjet: One2, Wx, ZETXe, ZETXi
- Ideal: Logic Air Heat Pump
- Interdomo: Domostar GBK 25H/SH
- MAN/MHG: Ecostar 200
- MHG: ecoWP Xe, Procon E
- Oilon: SH, SHx
- Olymp: SHS, WHS
- Palazzetti: Choro Sistema Calore
- Robur: K18 Simplygas / Hybrigas
- Sieger: TG11
- Šildymo Technologijų Centras (ŠTC): STC9
- Sixmadun: TG11BE
- Smartheat: UI400
- SSP: Proburner
- Strebel: S-ASX
- Sunex: Nexus
- Termomax: Termo ÖV
- Thercon: Therma Silent Coax Single, THERMA Silent Coax Combi 300/500
- Thermics: Energie
- Thermital: TBox Clima TOP
- Tifell: Biofell
- Variheat: 110C
- Viadrus : Claudius K1, K2
- Viessmann: Vitotwin 300-W (exclusively!)
- Wamak: AiWa, DB
- Weishaupt: WTU  

If your heater has one of the following controllers, but your model ist not listed in our manual, feel free to get in touch with us, as these models have been confirmed working:  
AVS37, AVS55, AVS71, AVS74, AVS75, AVS77, AVS79, LMS14, LMS15, LMS15, LMU64, LMU74, LMU75, RVA61, RVA63, RVA33, RVA36, RVA43, RVA46, RVA47, RVA53, RVA60, RVA61, RVA63, RVA65, RVA66, RVC32, RVD110, RVD115, RVD120, RVD125, RVD130, RVD135, RVD139, RVD140, RVD144, RVD145, RVD230, RVD235, RVD240, RVD245, RVD250, RVD255, RVD260, RVD265, RVL469, RVL470, RVL471, RVL472, RVL479, RVL480, RVL481, RVL482, RVP320, RVP330, RVP340, RVP350, RVP351, RVP360, RVP361, RVP5xx, RVS13, RVS21, RVS23, RVS26, RVS41, RVS43, RVS46, RVS47, RVS51, RVS53, RVS61, RVS63, RVS65, RVS68, RWI65, WRI80
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
