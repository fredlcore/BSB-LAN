# BSB-LPB-PPS-LAN

Die deutsche Fassung dieser Datei gibt es <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/README_de.md">hier</A>.

LAN Interface for Boiler-System-Bus (BSB), Local Process Bus (LPB) and Point-to-Point-Interface (PPS) designed for Arduino Mega 2560 with Ethernet-Shield for web-based controlling Elco Thision, Brötje and similar heating systems, including logging to Micro-SD-card.

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.

<B>Interface kits available!</B> PCB boards with parts are available upon request. If you are interested, please send an e-mail to bsb (ät) code-it.de (German or English) for further information.

This hardware/software combination should in principle work with all BSB- and LPB-based heating systems and has been tested in real life with the following heating systems:

- Atlantic Alféa Extensa + [RVS21.831F] (heat pump)
- Austria Email LWPK 8 [RVS21.831] (heat pump)
- Baxi Luna Platinum + [LMS15] (gas-fired) 
- Brötje BBK 22E [LMS14] (gas-fired)
- Brötje BBK 22F [LMS14] (gas-fired)
- Brötje BBS Pro Evo 15C [LMU74] (gas-fired)
- Brötje BSK 20 [LMS14] (gas-fired)
- Brötje EcoCondens BBS 15E [LMS14] (gas-fired)
- Brötje EcoCondens BBS 20E [LMS14] (gas-fired)
- Brötje EcoCondens BBS 28C [LMU7] (gas-fired)
- Brötje EcoCondens BBS EVO 20G [LMS15] (gas-fired)  
- Brötje EcoSolar Kompakt BMR 20/24 [LMS15] (gas-fired + solar)  
- Brötje EcoTherm Kompakt WMS 12 [LMS 15] (gas-fired)
- Brötje EcoTherm Kompakt WMS 24 [LMS 15] (gas-fired)
- Brötje EcoTherm Plus BBS2N.28 [LMU 64] (gas-fired) (by usage of OCI420 via LPB!)
- Brötje EcoTherm Plus WGB2N.20 [LMU 64] (gas-fired) (by usage of OCI420 via LPB!)
- Brötje ISR-SSR [RVS63.283]
- Brötje ISR-ZR1 [RVS46.530]
- Brötje LogoBloc Unit L-UB 25C [RVS43.122] (oil-fired)
- Brötje NovoCondens BOB 20 [RVS43.325] (oil-fired)
- Brötje NovoCondens SOB 26 [RVA63.242] (oil-fired) {LPB_only} 
- Brötje NovoCondens SOB 22C [RVS43.222] (oil-fired)
- Brötje NovoCondens SOB 26C [RVS43.222] (oil-fired) + EWM [RVS75.390]
- Brötje NovoCondens WOB 20D [RVS43.325] (oil-fired)
- Brötje SensoTherm BLW 12B [RVS21.825] (heat pump)
- Brötje SensoTherm BLW 15B [RVS21.825] (heat pump)
- Brötje SensoTherm BSW 10E [RVS61.843] (heat pump)
- Brötje SensoTherm BSW-K [RVS61.843] (heat pump)
- Brötje TrioCondens BGB 20E [LMS14] (gas-fired)
- Brötje WBS 14D [LMU74] (gas-fired)
- Brötje WBS 14F [LMS14] (gas-fired)
- Brötje WBS 22E [LMS14] (gas-fired)
- Brötje WGB 15E [LMS14] (gas-fired)
- Brötje WGB 20C [LMU74] (gas-fired)
- Brötje WGB-C 20/24H [LMS14] (gas-fired)
- Brötje WGB EVO 20H [LMS15] (gas-fired)
- Brötje WGB EVO 15I [LMS15] (gas-fired)
- Brötje WGB Pro EVO 20C [LMU75] (gas-fired)
- Brötje WGB S 17/20E EcoTherm Plus [LMS14] (gas-fired)
- Brötje WGB-U 15H [LMS14] (gas-fired)
- CTC 380 IC [RVS43.143] (oil-fired)
- Deville 9981 [RVA53.140] (oil-fired) {PPS_only}
- Elco Aerotop G07-14 [RVS61.843] (heat pump)
- Elco Aerotop T07-16 [RVS61.843] (heat pump)
- Elco Aerotop T10C [RVS61.843] (heat pump)
- Elco Aquatop 8es [RVS51.843] (corresponds to CTA Optihead OH1-8es) (heat pump)
- Elco Straton 21 [RVS63.283] (oil-fired)
- Elco Thision S Plus 13 [LMS14] (gas-fired)
- Elco Thision S 13.1 [LMU7] (gas-fired)
- Elco Thision S 17.1 [LMU74.100] & [RVS63.283] (gas-fired)
- Elco Thision S 25.1 [RSV63.283] (gas-fired) + MM [AVS75.390] 
- Fröling Rendagas Plus [RVA63.244] (gas-fired)
- Fujitsu Waterstage Comfort 10 [RVS21.827] (heat pump)
- Fujitsu Waterstage WSHA 050 DA [RVS41.813] (heat pump)
- Fujitsu Waterstage WSYK 160 DC 9 [RVS21.827] (heat pump)
- Fujitsu Waterstage WSYP 100 DG 6 [RVS21.831] (heat pump)
- MHG Procon E 25 HS [LMS14] (gas-fired)
- Sieger TG11 [RVP54.100] (oil-fired) {PPS_only}
- Weishaupt WTU-25 G with WRS-CPU B2/E [RVS23.220] (oil-fired) {LPB_only}

- PPS-based heating systems (e.g. RVP digital Serie D, RVP54…, ALBATROS RVA…, LGM11… and such as those using a QAA50 / QAA70 or similar like Brötje WGB 15 / WGB 20 / Triobloc E23 (Eurocontrol K), Weishaupt WRD 0.2 / 1.1, Sieger TG11 (with Siegermatic S42DB), Olymp THR 5-25C, Schäfer Interdomo (with DomoCommand DC 225)), albeit with PPS-typical limited functionality compared to BSB/LPB.

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
