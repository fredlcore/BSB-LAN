# BSB-LPB-PPS-LAN

Die deutsche Fassung dieser Datei gibt es <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/README_de.md">hier</A>.

LAN Interface for [Boiler-System-Bus (BSB)](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap02.html#21-bsb-and-lpb), [Local Process Bus (LPB)](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap02.html#21-bsb-and-lpb) and [Point-to-Point-Interface (PPS)](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap02.html#22-pps) designed for Arduino Due with Ethernet-Shield for web-based controlling (locally via LAN or if so desiread also via the internet) heating systems such as Elco Thision, Brötje and similar systems, including logging to Micro-SD-card. This project can serve in many ways as a cost-effective alternative to the OZW 672 or OCI 700.

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.

<B>Interface kits available!</B> PCB boards with parts are available upon request. If you are interested, please send an e-mail to bsb (ät) code-it.de (German or English) for further information.  
   
***Please read the [BSB-LPB-LAN manual](https://1coderookie.github.io/BSB-LPB-LAN_EN)!***  
*A quick installation guide is available [here](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap16.html).* 
   
With the usage of the BSB-LPB-LAN adapter and the BSB-LAN software, various functions, values and parameters can now be easily monitored, logged and (if wanted) web-based controlled and changed.
An optional integration into existing SmartHome systems such as [FHEM](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap11.html#111-fhem), [openHAB](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap11.html#112-openhab), [HomeMatic](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap11.html#113-homematic-eq3), [IoBroker](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap11.html#114-iobroker), [Loxone](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap11.html#115-loxone), [IP-Symcon](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap11.html#116-ip-symcon), [EDOMI](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap11.md#1110-edomi) or [Home Assistant](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap11.md#1111-home-assistant) can be done via [HTTPMOD](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap11.html#1112-integration-via-httpmod-module), [JSON](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#824-retrieving-and-controlling-via-json) or [MQTT](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap11.html#117-mqtt-influxdb-telegraf-and-grafana).
In addition, the use of the adapter as a [standalone logger](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap09.html#91-usage-of-the-adapter-as-a-standalone-logger-with-bsb-lan) without LAN or Internet connection when using a microSD card is also possible.
Furthermore, optional [temperature and humidity sensors](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap12.html#123-usage-of-optional-sensors-dht22-and-ds18b20) can be connected and their data also logged and evaluated. By using an Arduino and the ability to integrate your own code into the BSB-LAN software, there is also a wide range of expansion options.
   
The following overview shows the most common used controllers of the different heating systems which will work with BSB-LAN. As a basic rule we can say, that the controller types of the last years which are named with an **S** at the end (RV**S** and LM**S**) are comaptible with BSB-LAN and offer (mostly) the full range of funtionality. For further and more detailed informations about the different [controllers](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.html#32-detailed-listing-and-description-of-the-supported-controllers) and the [connection](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap02.html#23-connecting-the-adapter-to-the-controller) see the corresponding chapters.  
   
**Gas-fired heating systems controllers:**  
- [LMU74/LMU75](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.html#3211-lmu-controllers) and [LMS14/LMS15](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.html#3212-lms-controllers) (latest models), connection via BSB, complete functionality  
- [LMU54/LMU64](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.html#3211-lmu-controllers), connection via PPS, limited functionality  
   
**Oil-fired heating systems controllers / solarthermic controllers / zone controllers:**  
- [RVS43/RVS63/RVS46](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.html#3222-rvs-controllers), connection via BSB, full functionality  
- [RVA/RVP](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.html#3221-rva-and-rvp-controllers), connection via PPS (modelspecific sometimes LPB), limited functionality 
   
**Heat pump controllers:**  
- [RVS21/RVS61](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.html#3222-rvs-controllers), connection via BSB, full functionality  
   
**Weishaupt (model WTU):**  
- [RVS23](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.html#3222-rvs-controllers), connection via LPB, (nearly) full functionality  
     
**In the following, some model series from different manufacturers are listed, which usually have installed BSB-LAN compatible controllers:**  
- Broetje: BBK, BBS, BGB, BLW, BMR, BOB, BSK, SOB, WBS, WGB, WGB EVO, WGB Pro EVO, WGB-M, WGB-U, WOB  
- Elco: Aerotop, Aquatop, Straton, Thision, Thision S, Thision S Plus  
- Atlantic: Alféa Excellia, Extensa  
- Austria Email: LWPK  
- Baxi: Luna Platinum
- CTA: Optiheat  
- Froeling: Rendagas Plus
- Fujitsu: Waterstage Comfort, WSHA, WSYK, WSYP
- Gruenenwald: Greenheat
- MHG: Procon E
- Olymp: SHS, WHS
- Thermital: TBox Clima TOP
- Weishaupt: WTU
   
***To see a more detailed listing of the reported systems which are sucessfully used with BSB-LAN please follow the corresponding link:***  
- **[Broetje](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.html#311-broetje)**  
- **[Elco](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.html#312-elco)**  
- **[Other Manufacturers (e.g. Fujitsu, Atlantic, Weishaupt)](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.html#313-other-manufacturers)**  


Please note: General parameters should work on all devices, more specific parameters are subsequently added. Your help might be needed if you have a heating system that works on the BSB, LPB or PPS but for which we don't have the more specific parameters added. See <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/FAQ.md#my-heating-system-has-parameters-that-are-not-supported-in-the-software-yet-can-i-help-adding-these-parameters">here</A> how to help us.

<B>Attention!</B><BR>
Some companies which previously used BSB/LPB in their heating systems have now switched to other systems for their lower-cost devices. Examples are Brötje's WLC/WLS/BOK series. These are not compatible with BSB/LPB and only allow very limited parameters to be configured by the user. If you have one of these heating systems, you are so far out of luck to configure and monitor your heating system as it can be done with the more expensive (but BSB/LPB compatible) devices mentioned above among others.
<BR><BR>

Instructions on how to configure etc. can be found in the <A HREF="https://1coderookie.github.io/BSB-LPB-LAN_EN">manual</A>.<BR>
The forum thread that led to the development of this interface can be found <A HREF="http://forum.fhem.de/index.php?topic=29762.new;topicseen#new">here</A>.<BR>
(Forum is in German, but several members speak English)

Please take note that while the board can also be used on the Raspberry Pi, the software provided here only runs on the Arduino! For using the board with the Pi, you have to use the software bsb_gateway which is available <A HREF="https://github.com/loehnertj/bsbgateway">here</A>. Please also note that the functionality differs significantly, and that you would have to contact the author of bsb_gateway for any question related to it.

Web-Interface screenshots:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/Web-Interface.png" size="50%">
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/Web-Interface2.png" size="50%">

BSB-Board plain, with location of CL+ and CL- connectors:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/BSB-Board%20plain.jpg" size="50%">

BSB-Board and Ethernet Shield plugged into the Arduino Due:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/BSB-Board%20on%20Arduino%20Due.jpg" size="50%">
