# BSB-LPB-LAN

Die deutsche Fassung dieser Datei gibt es <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/README_de.md">hier</A>.

LAN Interface for Boiler-System-Bus (BSB), Local Process Bus (LPB) and (with just basic functionality) Punkt-zu-Punkt-Schnittstelle (PPS/H-Bus) designed for Arduino Mega 2560 with Ethernet-Shield for web-based controlling Elco Thision, Brötje and similar heating systems, including logging to Micro-SD-card.

This hardware/software combination should in principle work with all BSB- and LPB-based heating systems and has been tested in real life with the following heating systems:

- Brötje ISR-SSR [RVS63.283/100] [RVS63.283/200]
- Brötje ISR-ZR1 [RVS46.530/100]
- Brötje L-UB 25C [RVS43.122/100] (oil-fired)
- Brötje NovoCondens SOB 26 [Eurocontrol KM] {LPB_only} (oil-fired)
- Brötje NovoCondens SOB 22C [RVS43.222/100] (oil-fired)
- Brötje NovoCondens SOB 26C [RVS43.222/100] + EWM [RVS75.390/109] (oil-fired)
- Brötje SensoTherm BSW-K (heat pump)
- Brötje BBK 22E [LMS14.001A100] (gas-fired)
- Brötje WBS 22E (gas-fired)
- Brötje WGB-U 15H [LMS14.001B100] (gas-fired)
- Brötje WGB 15 E [LMS14] (gas-fired)
- Brötje WGB 20C [LMU74] (gas-fired)
- Brötje WGB S 17/20 E EcoTherm Plus [LMS14.001B100] (gas-fired)
- Brötje WGB EVO 20H [LMS15] (gas-fired)
- Brötje WGB Pro EVO 20C [LMU75] (gas-fired)
- Elco Straton (oil-fired)
- Elco Straton 21 [LOGON B G2Z2 + RVS63.283/160] (oil-fired)
- Elco Thision S Plus 13 [LMS14.002A167] (gas-fired)
- Elco Thision S 17.1 [LMU74.100A136 + AVS37.394/136] (gas-fired)
- Elco Thision S 25.1 [LOGON B G2Z2 (RSV63.283/360) + LOGON B MM (AVS75.390/260)] (gas-fired)
- Elco Aquatop 8es [RVS51.843/169] (corresponds to CTA Optihead OH1-8es) (heat pump)
- Fujitsu Waterstage WSYK 160 DC 9 [RVS21.827/127] (heat pump)
- Siemens RVS63.283/109 (corresponds to Brötje SSR)
- Weishaupt WTU-25 G mit WRS-CPU B2/E [RVS23.220/320] {LPB_only} (oil-fired)
- PPS-based heating systems (such as Brötje WGB 15 / WGB 20, Weishaupt WRD 0.2 / 1.1, Sieger TG11 / Siegermatic S42DB, Olymp THR 5-25C, Schäfer Interdomo / DomoCommand DC 225), albeit with just very basic functionality)

Please note: General parameters should work on all devices, more specific parameters are subsequently added. Your help might be needed if you have a heating system that works on the BSB or LPB bus but for which we don't have the more specific parameters added. See <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/FAQ.md#my-heating-system-has-parameters-that-are-not-supported-in-the-software-yet-can-i-help-adding-these-parameters">here</A> how to help us.

Instructions on how to configure etc. can be found in the <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/HOWTO.md">HowTo</A>.<BR>
The forum thread that led to the development of this interface can be found <A HREF="http://forum.fhem.de/index.php?topic=29762.new;topicseen#new">here</A>.<BR>
(Forum is in German, but several members speak English)

Some interface kits from a collective order are still available, fitting directly on the Arduino Mega 2560 or (with different pin headers) on the Raspberry Pi 2. Contact bsb (ät) code-it.de if you are interested (German or English).

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
