# BSB-LPB-PPS-LAN

Die deutsche Fassung dieser Datei gibt es <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/README_de.md">hier</A>.

Before starting with anything, please read through the manual [here](https://docs.bsb-lan.de/EN).

BSB-LAN is an interface for the Boiler-System-Bus (BSB), Local Process Bus (LPB) and Point-to-Point-Interface (PPS). The adapter interface is designed for an *ESP32*-based microcontrollers (ESP32 NodeMCU, Olimex EVB, Olimex POE) or for an *Arduino Due* with Ethernet-Shield for web-based controlling via LAN/WLAN of heating systems such as Elco Thision, Brötje and other heating systems using Siemens controllers. Logging values on microSD-card is also possible. This project supports almost all parameters available on the respective heating systems and can serve in many ways as a cost-effective and in several ways more powerful alternative to the OZW 672, OCI 700 or Remocon Net B.

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.

---

***Interface kits available!***  
**Interface boards are available for the ESP32 upon request. These can simply be plugged on top of one of the listed microcontrollers.Getting the board from here helps supporting this project in the future, so if you are interested, please send Frederik an e-mail (German or English) to <br /> bsb (ät) code-it.de <br /> for further informations.**  

---  
  
With the usage of the BSB-LPB-LAN adapter and the BSB-LAN software, various functions, values and parameters can now be easily monitored, logged and (if wanted) web-based controlled and changed.
An optional integration into existing SmartHome systems such as FHEM, openHAB, HomeMatic, ioBroker, Loxone, IP-Symcon, EDOMI, Home Assistant, SmartHomeNG or Node-RED can be done via HTTPMOD, JSON) or MQTT.
In addition, the use of the adapter as a standalone logger without LAN or Internet connection when using a microSD card is also possible.
Furthermore, optional temperature and humidity sensors can be connected and their data also logged and evaluated. With the ability to integrate your own code into the BSB-LAN software, there is also a wide range of expansion options.
   
The following overview shows the most common used controllers of the different heating systems which will work with BSB-LAN. As a basic rule we can say, that the controller types of the last years which are named with an **S** at the end (RV**S** and LM**S**) are comaptible with BSB-LAN and offer (mostly) the full range of funtionality. For further and more detailed informations about the different controllers and the connection see the corresponding chapters.  
   
**Gas-fired heating systems controllers:**  
- LMU74/LMU75 and LMS14/LMS15 (latest models), connection via BSB  
- LMU54/LMU64, connection via LPB through OCI420 plugin.
   
**Oil-fired heating systems controllers / solarthermic controllers / zone controllers:**  
- RVS43/RVS63/RVS46, connection via BSB  
- RVA/RVP, connection via PPS (modelspecific sometimes LPB) 
   
**Heat pump controllers:**  
- RVS21/RVS61, connection via BSB  
   
**Weishaupt (model WTU):**  
- RVS23, connection via LPB  
     
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
   
***To see a more detailed listing of the reported systems which are sucessfully used with BSB-LAN please follow the corresponding link:***  
- **Broetje**  
- **Elco**  
- **Other Manufacturers (e.g. Fujitsu, Atlantic, Weishaupt)**  


If your heater has one of the following controllers, but your model ist not listed in our manual, feel free to get in touch with us, as these models have been confirmed working:  
AVS37, AVS55, AVS71, AVS74, AVS75, AVS77, AVS79, LMS14, LMS15, LMS15, LMU6x, LMU74, LMU75, RVA61, RVA63, RVA33, RVA36, RVA43, RVA46, RVA47, RVA53, RVA60, RVA61, RVA63, RVA65, RVA66, RVC32, RVD110, RVD115, RVD120, RVD125, RVD130, RVD135, RVD139, RVD140, RVD144, RVD145, RVD230, RVD235, RVD240, RVD245, RVD250, RVD255, RVD260, RVD265, RVL469, RVL470, RVL471, RVL472, RVL479, RVL480, RVL481, RVL482, RVP340, RVP350, RVP351, RVP360, RVP361, RVP5xx, RVS13, RVS21, RVS23, RVS26, RVS41, RVS43, RVS46, RVS47, RVS51, RVS53, RVS61, RVS63, RVS65, RVS68, RWI65, WRI80
<BR><BR>

<B>Attention!</B><BR>
Some companies which previously used BSB/LPB in their heating systems have now switched to other systems for their lower-cost devices. Examples are Brötje's WLC/WLS/BOK series. These are not compatible with BSB/LPB and only allow very limited parameters to be configured by the user. If you have one of these heating systems, you are so far out of luck to configure and monitor your heating system as it can be done with the more expensive (but BSB/LPB compatible) devices mentioned above among others.

Instructions on how to configure etc. can be found in the <A HREF="https://1coderookie.github.io/BSB-LPB-LAN_EN">manual</A>.<BR>
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
