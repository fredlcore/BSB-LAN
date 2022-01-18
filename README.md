# BSB-LPB-PPS-LAN

Die deutsche Fassung dieser Datei gibt es <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/README_de.md">hier</A>.

LAN Interface for [Boiler-System-Bus (BSB)](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap10.html#1011-bsb), [Local Process Bus (LPB)](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap10.html#1012-lpb) and [Point-to-Point-Interface (PPS)](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap10.html#1013-pps) designed for an *Arduino Due* with Ethernet-Shield and for an *ESP32* for web-based controlling (locally via W/LAN or if so desired also via the internet) heating systems such as Elco Thision, Brötje and similar systems, including logging to microSD-card (Due only). This project supports more than 1300 parameters on various heating systems and can serve in many ways as a cost-effective and in several ways more powerful alternative to the OZW 672, OCI 700 or Remocon Net B.

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.

<B>Interface kits available!</B> PCB boards with parts are available upon request. If you are interested, please send an e-mail to bsb (ät) code-it.de (German or English) for further information.  
   
***Please read the [BSB-LPB-LAN manual](https://1coderookie.github.io/BSB-LPB-LAN_EN)!***  
   
With the usage of the BSB-LPB-LAN adapter and the BSB-LAN software, various functions, values and parameters can now be easily monitored, logged and (if wanted) web-based controlled and changed.
An optional integration into existing SmartHome systems such as [FHEM](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#81-fhem), [openHAB](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#82-openhab), [HomeMatic](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#83-homematic-eq3), [ioBroker](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#84-iobroker), [Loxone](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#85-loxone), [IP-Symcon](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#86-ip-symcon), [EDOMI](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#810-edomi), [Home Assistant](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#811-home-assistant), [SmartHomeNG](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#812-smarthomeng) or [Node-RED](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#813-node-red) can be done via [HTTPMOD](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#812-integration-via-httpmod-module), [JSON](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap05.html#53-json)) or [MQTT](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap05.html#52-mqtt).
In addition, the use of the adapter as a [standalone logger](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap06.html#61-logging-data) without LAN or Internet connection when using a microSD card is also possible.
Furthermore, optional [temperature and humidity sensors](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap07.html#71-usage-of-optional-sensors-dht22-ds18b20-bme280) can be connected and their data also logged and evaluated. By using an Arduino and the ability to integrate your own code into the BSB-LAN software, there is also a wide range of expansion options.
   
The following overview shows the most common used controllers of the different heating systems which will work with BSB-LAN. As a basic rule we can say, that the controller types of the last years which are named with an **S** at the end (RV**S** and LM**S**) are comaptible with BSB-LAN and offer (mostly) the full range of funtionality. For further and more detailed informations about the different [controllers](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap10.html#102-detailed-description-of-the-supported-controllers) and the [connection](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.md#31-connecting-the-adapter) see the corresponding chapters.  
   
**Gas-fired heating systems controllers:**  
- [LMU74/LMU75](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap10.html#10211-lmu-controllers) and [LMS14/LMS15](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap10.html#10212-lms-controllers) (latest models), connection via BSB  
- [LMU54/LMU64](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap10.html#10211-lmu-controllers), connection via PPS  
   
**Oil-fired heating systems controllers / solarthermic controllers / zone controllers:**  
- [RVS43/RVS63/RVS46](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap10.html#10222-rvs-controllers), connection via BSB  
- [RVA/RVP](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap10.html#10221-rva-and-rvp-controllers), connection via PPS (modelspecific sometimes LPB) 
   
**Heat pump controllers:**  
- [RVS21/RVS61](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap10.html#10222-rvs-controllers), connection via BSB  
   
**Weishaupt (model WTU):**  
- [RVS23](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap10.html#10222-rvs-controllers), connection via LPB  
     
**In the following, some model series from different manufacturers are listed, which usually have installed BSB-LAN compatible controllers:**  
- Broetje: BBK, BBS, BGB, BLW, BMR, BOB, BSK, SOB, WBS, WGB, WGB EVO, WGB Pro EVO, WGB-M, WGB-U, WOB  
- Boesch: heat pumps with RVS controller type
- Elco: Aerotop, Aquatop, Straton, Thision, Thision S, Thision S Plus  
- ATAG: QR  
- Atlantic: Alféa Evolution, Excellia, Extensa  
- Austria Email: LWPK  
- Baxi: Luna Platinum
- Chappée: Klista
- CTA: Optiheat  
- Deville: 9942, 9981
- EVI Heat: Combi-7
- Fernwärme: RVD230
- Froeling: Rendagas Plus
- Fujitsu Waterstage: Comfort, Duo
- Geminox: Thrs
- Gruenenwald: Greenheat
- Hansa: SND
- Interdomo: Domostar GBK 25H/SH
- MAN/MHG: Ecostar 200
- MHG: Procon E
- Oilon: SH, SHx
- Olymp: SHS, WHS
- Sieger: TG11
- Sixmadun: TG11BE
- Termomax: Termo ÖV
- Thermics: Energie
- Thermital: TBox Clima TOP
- Viessmann: Vitotwin 300-W
- Wamak: DB
- Weishaupt: WTU
   
***To see a more detailed listing of the reported systems which are sucessfully used with BSB-LAN please follow the corresponding link:***  
- **[Broetje](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap11.html#111-broetje)**  
- **[Elco](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap11.html#112-elco)**  
- **[Other Manufacturers (e.g. Fujitsu, Atlantic, Weishaupt)](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap11.html#113-other-manufacturers)**  


Please note: General parameters should work on all devices, more specific parameters are subsequently added. Your help might be needed if you have a heating system that works on the BSB, LPB or PPS but for which we don't have the more specific parameters added. See <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/FAQ.md#my-heating-system-has-parameters-that-are-not-supported-in-the-software-yet-can-i-help-adding-these-parameters">here</A> how to help us.

<B>Attention!</B><BR>
Some companies which previously used BSB/LPB in their heating systems have now switched to other systems for their lower-cost devices. Examples are Brötje's WLC/WLS/BOK series. These are not compatible with BSB/LPB and only allow very limited parameters to be configured by the user. If you have one of these heating systems, you are so far out of luck to configure and monitor your heating system as it can be done with the more expensive (but BSB/LPB compatible) devices mentioned above among others.
<BR><BR>

Instructions on how to configure etc. can be found in the <A HREF="https://1coderookie.github.io/BSB-LPB-LAN_EN">manual</A>.<BR>
The forum thread that led to the development of this interface can be found <A HREF="http://forum.fhem.de/index.php?topic=29762.new;topicseen#new">here</A>.<BR>
(Forum is in German, but several members speak English)

Please take note that while the board can also be used on the Raspberry Pi, the software provided here only runs on the Arduino! For using the board with the Pi, you have to use the software bsb_gateway which is available <A HREF="https://github.com/loehnertj/bsbgateway">here</A>. Please also note that the functionality differs significantly, and that you would have to contact the author of bsb_gateway for any question related to it.

Web-Interface screenshots:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/BSB_LAN/schematics/Web-Interface.png" size="50%">
<img src="https://github.com/fredlcore/bsb_lan/blob/master/BSB_LAN/schematics/Web-Interface2.png" size="50%">

BSB-Board plain, with location of CL+ and CL- connectors as well as pads framed in red for required pins:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/BSB_LAN/schematics/BSB-Board%20plain.jpg" size="50%">

BSB-Board and Ethernet Shield plugged into the Arduino Due:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/BSB_LAN/schematics/BSB-Board%20on%20Arduino%20Due.jpg" size="50%">
