# BSB-LPB-PPS-LAN

Die deutsche Fassung dieser Datei gibt es <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/README_de.md">hier</A>.

LAN Interface for Boiler-System-Bus (BSB), Local Process Bus (LPB) and Point-to-Point-Interface (PPS) designed for Arduino Mega 2560 with Ethernet-Shield for web-based controlling (locally via LAN or if so desiread also via the internet) heating systems such as Elco Thision, Brötje and similar systems, including logging to Micro-SD-card. This project can serve in many ways as a cost-effective alternative to the OZW 672 or OCI 700.

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.

<B>Interface kits available!</B> PCB boards with parts are available upon request. If you are interested, please send an e-mail to bsb (ät) code-it.de (German or English) for further information.
   
The following overview shows the most common used controllers of the different heating systems which will work with BSB-LAN. For further and more detailed informations about the different [controllers](chap03.md#32-detailed-listing-and-description-of-the-supported-controllers) and the [connection](chap02.md#23-connecting-the-adapter-to-the-controller) see the corresponding chapters in the [manual](https://1coderookie.github.io/BSB-LPB-LAN_EN).  
   
**Gas-fired heating systems controllers:**  
- [LMU74/LMU75](chap03.md#3211-lmu-controllers) and [LMS14/LMS15](chap03.md#3212-lms-controllers) (latest models), connection via BSB, complete functionality  
- [LMU54/LMU64](chap03.md#3211-lmu-controllers), connection via PPS, limited functionality  
   
**Oil-fired heating systems controllers / solarthermic controllers / zone controllers:**  
- [RVS43/RVS63/RVS46](chap03.md#3222-rvs-controllers), connection via BSB, full functionality  
- [RVA/RVP](chap03.md#3221-rva-and-rvp-controllers), connection via PPS (modelspecific sometimes LPB), limited functionality 
   
**Heat pump controllers:**  
- [RVS21/RVS61](chap03.md#3222-rvs-controllers), connection via BSB, full functionality  
   
**Weishaupt (model WTU):**  
- [RVS23](https://1coderookie.github.io/BSB-LPB-LAN/kap03.html#3222-rvs-regler), connection via LPB, (nearly) full functionality  
   
**To see a more detailed listing of the reported systems which are sucessfully used with BSB-LAN please follow the corresponding link:**  
- **[Broetje](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.html#311-broetje)**  
- **[Elco](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.html#312-elco)**  
- **[Other Manufacturers (e.g. Fujitsu, Atlantic, Weishaupt)](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap03.html#313-other-manufacturers)**  


Please note: General parameters should work on all devices, more specific parameters are subsequently added. Your help might be needed if you have a heating system that works on the BSB, LPB or PPS but for which we don't have the more specific parameters added. See <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/FAQ.md#my-heating-system-has-parameters-that-are-not-supported-in-the-software-yet-can-i-help-adding-these-parameters">here</A> how to help us.

<B>Attention!</B><BR>
Some companies which previously used BSB/LPB in their heating systems have now switched to other systems for their lower-cost devices. Examples are Brötje's WLC/WLS/BOK series. These are not compatible with BSB/LPB and only allow very limited parameters to be configured by the user. If you have one of these heating systems, you are so far out of luck to configure and monitor your heating system as it can be done with the more expensive (but BSB/LPB compatible) devices mentioned above among others.
<BR><BR>

Instructions on how to configure etc. can be found in the <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/HOWTO.md">HowTo</A>.<BR>
The forum thread that led to the development of this interface can be found <A HREF="http://forum.fhem.de/index.php?topic=29762.new;topicseen#new">here</A>.<BR>
(Forum is in German, but several members speak English)

Please take note that while the board can also be used on the Raspberry Pi, the software provided here only runs on the Arduino! For using the board with the Pi, you have to use the software bsb_gateway which is available <A HREF="https://github.com/loehnertj/bsbgateway">here</A>. Please also note that the functionality differs significantly, and that you would have to contact the author of bsb_gateway for any question related to it.

Web-Interface screenshots:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/Web-Interface.png" size="50%">
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/Web-Interface2.png" size="50%">

BSB-Board plain, with location of CL+ and CL- connectors:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/BSB-Board%20plain.jpg" size="50%">

BSB-Board and Ethernet Shield plugged into the Arduino Mega 2560:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/BSB-Board%20on%20Arduino%20Mega%202560.jpg" size="50%">

BSB-Board on Raspberry Pi 2:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/BSB-Board%20on%20Raspberry%20Pi%202.jpg" size="50%">
