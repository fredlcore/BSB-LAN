# bsb_lan

Die deutsche Fassung dieser Datei gibt es <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/README_de.md">hier</A>.

BSB Boiler-System-Bus LAN Interface designed for Arduino Mega 2560 with Ethernet-Shield for web-based controlling Elco Thision, Brötje and similar heating systems, including logging to Micro-SD-card.

This hardware/software combination should in principle work with all BSB-based heating systems and has been tested in real life with the following heating systems:

- Brötje ISR-SSR 
- Brötje ISR-ZR1 
- Brötje NovoCondens BOB 20 (oil-fired)
- Brötje NovoCondens SOB 22C (oil-fired)
- Brötje NovoCondens SOB 26C [ISR + RVS43.222/100] (oil-fired)
- Brötje SensoTherm BSW-K (heat pump)
- Brötje WBS 22E (gas-fired)
- Brötje WGB-U 15H (gas-fired)
- Brötje WGB 15 E [LMS14] (gas-fired)
- Brötje WGB S 17/20 E EcoTherm Plus (gas-fired)
- Brötje WGB EVO 20H (gas-fired)
- Brötje WGB Pro EVO 20C [LMU75] (gas-fired)
- Elco Straton (oil-fired)
- Elco Straton 21 [LOGON B G2Z2 + RVS63.283/160] (oil-fired)
- Elco Thision S 17.1 [LMU74.100A136 + AVS37.394/136] (gas-fired)
- Elco Thision S 25.1 [LOGON B G2Z2 (RSV63.283/360) + LOGON B MM (AVS75.390/260)] (gas-fired)
- Fujitsu Waterstage (WSYK160DC9, RVS21.827/127) (heat pump)

Please note: General parameters should work on all devices, more specific parameters are subsequently added. Your help might be needed if you have a heating system that works on the BSB bus but for which we don't have the more specific parameters added. See <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/FAQ.md#my-heating-system-has-parameters-that-are-not-supported-in-the-software-yet-can-i-help-adding-these-parameters">here</A> how to help us.

Instructions on how to configure etc. can be found in the <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/HOWTO.md">HowTo</A>.<BR>
The forum thread that led to the development of this interface can be found <A HREF="http://forum.fhem.de/index.php?topic=29762.new;topicseen#new">here</A>.<BR>
(Forum is in German, but several members speak English)

Some interface kits from a collective order are still available, fitting directly on the Arduino Mega 2560. Contact bsb (ät) code-it.de if you are interested (German or English).

Web-Interface screenshots:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/Web-Interface.png" size="50%">
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/Web-Interface2.png" size="50%">

BSB-Board plain, with location of CL+ and CL- connectors:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/BSB-Board%20plain.jpg" size="50%">

BSB-Board populated:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/BSB-Board.jpg" size="50%">

BSB-Board and Ethernet Shield plugged into the Arduino Mega 2560:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/BSB-Board%20on%20Arduino%20Mega%202560.jpg" size="50%">
