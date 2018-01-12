# BSB-LPB-PPS-LAN

English version can be found <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/README.md">here</A>. 

LAN-Adapter für den Boiler-System-Bus (BSB) und den Local Process Bus (LPB) - entwickelt für einen Arduino Mega 2560 mit Ethernet-Shield zur web-basierten Kontrolle über Elco Thision, Brötje und baugleiche Heizungssysteme, einschließlich Logging-Funktion auf Micro-SD-Karte.

Prinzipiell sollte diese Kombination aus Hard- und Software mit allen Heizungssystemen lauffähig sein, deren Steuerung über einen BSB oder LPB verfügt. Unter realen Umständen erwies sich die Kombination auf folgenden Systemen als lauffähig:
 - Brötje ISR-SSR [RVS63.283] (Solar-System-Regler) 
 - Brötje ISR-ZR1 [RVS46.530] (Zonen-Regler)
 - Brötje LogoBloc Unit L-UB 25C [RVS43.122] (Ölbrenner)
 - Brötje NovoCondens BOB 20 [RVS43.325] (Ölbrenner)
 - Brötje NovoCondens SOB 26 [RVA63.242] (Ölbrenner) {LPB_only}
 - Brötje NovoCondens SOB 22C [RVS43.222] (Ölbrenner)
 - Brötje NovoCondens SOB 26C [RVS43.222] (Ölbrenner) + EWM [RVS75.390]
 - Brötje SensoTherm BSW-K [RVS61.843] (Wärmepumpe)
 - Brötje BBK 22E [LMS14] (Gasbrenner)
 - Brötje BBS Pro Evo 15C [LMU74] (Gasbrenner)
 - Brötje BBS 15E [LMS14] (Gasbrenner)
 - Brötje BGB 20E [LMS14] (Gasbrenner)
 - Brötje WBS 14D [LMU74] (Gasbrenner)
 - Brötje WBS 22E [LMS14] (Gasbrenner)
 - Brötje WGB-U 15H [LMS14] (Gasbrenner)
 - Brötje WGB 15 E [LMS14] (Gasbrenner)
 - Brötje WGB 20C [LMU74] (Gasbrenner)
 - Brötje WGB S 17/20 E EcoTherm Plus [LMS14] (Gasbrenner)
 - Brötje WGB EVO 20H [LMS15] (Gasbrenner)
 - Brötje WGB Pro EVO 20C [LMU75] (Gasbrenner)
 - Elco Straton 21 [RVS63.283] (Ölbrenner)
 - Elco Thision S Plus 13 [LMS14] (Gasbrenner)
 - Elco Thision S 17.1 [LMU74] (Gasbrenner)
 - Elco Thision S 25.1 [RSV63.283] (Gasbrenner) + MM [AVS75.390]
 - Elco Aquatop 8es [RVS51.843] (entspricht CTA Optihead OH1-8es) (Wärmepumpe)
 - Fujitsu Waterstage WSYK 160 DC 9 [RVS21.827] (Wärmepumpe)
 - Sieger TG11 [RVP54.100] (Ölbrenner) {PPS_only}
 - Weishaupt WTU-25 G mit WRS-CPU B2/E [RVS23.220] (Ölbrenner) {LPB_only}

Bitte beachten: Generelle Parameter sollten bei allen Systemen funktionieren, spezifischere Parameter werden sukzessiv hinzugefügt. Deine Hilfe könnte gebraucht werden, wenn du ein Heizungssystem hast, welches mit BSB, LPB oder PPS arbeitet, wofür wir jedoch noch keine spezifischeren Parameter hinzugefügt haben. Erfahre <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/FAQ_de.md#mein-heizungssystem-verf%C3%BCgt-%C3%BCber-parameter-die-von-der-software-bisher-nicht-unterst%C3%BCtzt-werden-kann-ich-behilflich-sein-diese-parameter-hinzuzuf%C3%BCgen">hier</A>, wie du uns helfen kannst.

Instruktionen, wie die Software konfiguriert werden muss etc. können dem <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/HOWTO_de.md">HowTo</A> entnommen werden.<BR>
Die Forendiskussion die zum Bau dieses Adapters geführt hat, kann <A HREF="https://forum.fhem.de/index.php?topic=29762.new;topicseen#new">hier</A> nachvollzogen werden.<BR>

Einige Adapterbausätze sind noch aus einer Sammelbestellung verfügbar, die direkt auf einen Arduino Mega 2560 oder (mit anderen Pinheadern) auf einen Raspberry Pi 2 passen. Kontaktiere bsb (ät) code-it.de , falls du daran interessiert bist (Deutsch oder Englisch).
Bitte beachte, dass der Adapter zwar an einem Raspberry Pi genutzt werden kann, die hier angebotene Software jedoch nur auf dem Arduino läuft! Wenn der Adapter an einem Raspberry Pi genutzt werden soll, muss stattdessen die Software bsb_gateway genutzt werden, die <A HREF="https://github.com/loehnertj/bsbgateway">hier</A> verfügbar ist. Bitte beachte, dass sich die Funktionalität signifikant unterscheidet, und dass du für jegliche Fragen diesbezüglich den Autor von bsb_gateway kontaktieren musst.

Web-Interface screenshots:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/Web-Interface.png" size="50%">
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/Web-Interface2.png" size="50%">

BSB-Adapterplatine unbestückt, mit den Anschlüssen CL+ und CL-:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/BSB-Board%20plain.jpg" size="50%">

BSB-Adapterplatine und Ethernet-Shield auf dem Arduino Mega2560:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/BSB-Board%20on%20Arduino%20Mega%202560.jpg" size="50%">

BSB-Adapterplatine auf dem Raspberry Pi 2:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/BSB-Board%20on%20Raspberry%20Pi%202.jpg" size="50%">
