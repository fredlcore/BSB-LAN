# bsb_lan
BSB Boiler-System-Bus LAN Interface designed for Arduino Mega 2560 with Ethernet-Shield for web-based controlling Elco Thision, Brötje and similar heating systems

This hardware/software combination should in principle work with all BSB-based heating systems and has been tested in real life with the following heating systems:

- Brötje ISR-ZR1 Solar- und Systemregler
- Brötje NovoCondens SOB 22C / 26C (oil-fuelled heating system)
- Brötje NovoCondens BOB 20
- Brötje SensoTherm BSW-K Wärmepumpe
- Brötje WGB S 17/20 E EcoTherm Plus
- Brötje WBS 22E (gas-fuelled heating system)
- Elco Straton (oil-fuelled heating system)
- Elco Thision S (gas-fuelled heating system)
- Fujitsu Waterstage (WSYK160DC9) Wärmepumpe

Please note: General parameters should work on all devices, more specific parameters are subsequently added. Your help might be needed if you have a heating system that works on the BSB bus but for which we don't have the more specific parameters added. 

Instructions on how to configure etc. can be found in the README ![here](https://github.com/fredlcore/bsb_lan/blob/master/BSB_lan/BSB_lan).<BR>
The forum thread that led to the development of this interface can be found ![here](http://forum.fhem.de/index.php?topic=29762.new;topicseen#new).<BR>
(Forum is in German, but several members speak English)

Some interface kits from a collective order are still available, fitting directly on the Arduino Mega 2560. Contact bsb (ät) code-it.de if you are interested (German or English).

BSB-Board plain, with location of CL+ and CL- connectors:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/BSB_lan/schematics/BSB-Board%20plain.jpg" size="50%">

BSB-Board populated:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/BSB_lan/schematics/BSB-Board.jpg" size="50%">

BSB-Board and Ethernet Shield plugged into the Arduino Mega 2560:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/BSB_lan/schematics/BSB-Board%20on%20Arduino%20Mega%202560.jpg" size="50%">
