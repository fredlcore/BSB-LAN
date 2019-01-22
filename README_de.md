# BSB-LPB-PPS-LAN

English version can be found <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/README.md">here</A>. 

LAN-Adapter für den Boiler-System-Bus (BSB), den Local Process Bus (LPB) und die Punkt-zu-Punkt-Schnittstelle (PPS) - entwickelt für einen Arduino Mega 2560 mit Ethernet-Shield zur web-basierten Kontrolle von Elco, Brötje und baugleichen Heizungssystemen, einschließlich Logging-Funktion auf Micro-SD-Karte.

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons Lizenzvertrag" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />Dieses Werk ist lizenziert unter einer <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Namensnennung - Nicht-kommerziell - Weitergabe unter gleichen Bedingungen 4.0 International Lizenz</a>.

<B>Bausätze erhältlich!<B> Auf Anfrage sind Platinen mit entsprechenden Bauteilen für die Verwendung am Arduino Mega 2560 erhältlich, bei Interesse bitte e-Mail an bsb (ät) code-it.de schicken (Deutsch/Englisch).

<b>Ausführliche Informationen zum Adapter und der Software sind im Handbuch zu finden.</b>

Prinzipiell sollte diese Kombination aus Hard- und Software mit allen Heizungssystemen lauffähig sein, deren Steuerung über einen BSB oder LPB verfügt. Unter realen Umständen erwies sich die Kombination auf folgenden Systemen als lauffähig:
 - Atlantic Alféa Extensa + [RVS21.831F] (Wärmepumpe)
 - Baxi Luna Platinum + [LMS15] (Gasbrenner) 
 - Brötje BBK 22E [LMS14] (Gasbrenner)
 - Brötje BBK 22F [LMS14] (Gasbrenner)
 - Brötje BBS Pro Evo 15C [LMU74] (Gasbrenner)
 - Brötje EcoCondens BBS 15E [LMS14] (Gasbrenner)
 - Brötje EcoCondens BBS 20E [LMS14] (Gasbrenner)
 - Brötje EcoCondens BBS 28C [LMU7] (Gasbrenner)
 - Brötje EcoCondens BBS EVO 20G [LMS15] (Gasbrenner)
 - Brötje EcoTherm Kompakt WMS 12 [LMS 15] (Gasbrenner)
 - Brötje EcoTherm Kompakt WMS 24 [LMS 15] (Gasbrenner)
 - Brötje ISR-SSR [RVS63.283] (Solar-System-Regler) 
 - Brötje ISR-ZR1 [RVS46.530] (Zonen-Regler)
 - Brötje LogoBloc Unit L-UB 25C [RVS43.122] (Ölbrenner)
 - Brötje NovoCondens BOB 20 [RVS43.325] (Ölbrenner)
 - Brötje NovoCondens SOB 26 [RVA63.242] (Ölbrenner) {LPB_only}
 - Brötje NovoCondens SOB 22C [RVS43.222] (Ölbrenner)
 - Brötje NovoCondens SOB 26C [RVS43.222] (Ölbrenner) + EWM [RVS75.390]
 - Brötje NovoCondens WOB 20D [RVS43.325] (Ölbrenner)
 - Brötje SensoTherm BLW 12B [RVS21.825] (Wärmepumpe)
 - Brötje SensoTherm BLW 15B [RVS21.825] (Wärmepumpe)
 - Brötje SensoTherm BSW-K [RVS61.843] (Wärmepumpe)
 - Brötje TrioCondens BGB 20E [LMS14] (Gasbrenner)
 - Brötje WBS 14D [LMU74] (Gasbrenner)
 - Brötje WBS 14F [LMS14] (Gasbrenner)
 - Brötje WBS 22E [LMS14] (Gasbrenner)
 - Brötje WGB 15E [LMS14] (Gasbrenner)
 - Brötje WGB 20C [LMU74] (Gasbrenner)
 - Brötje WGB-C 20/24H [LMS14] (Gasbrenner)
 - Brötje WGB EVO 20H [LMS15] (Gasbrenner)
 - Brötje WGB Pro EVO 20C [LMU75] (Gasbrenner)
 - Brötje WGB S 17/20E EcoTherm Plus [LMS14] (Gasbrenner)
 - Brötje WGB-U 15H [LMS14] (Gasbrenner)
 - CTC 380 IC [RVS43.143] (Ölbrenner)
 - Elco Aerotop G07-14 [RVS61.843] (Wärmepumpe)
 - Elco Aerotop T10C [RVS61.843] (Wärmepumpe)
 - Elco Aquatop 8es [RVS51.843] (entspricht CTA Optihead OH1-8es) (Wärmepumpe)
 - Elco Straton 21 [RVS63.283] (Ölbrenner)
 - Elco Thision S Plus 13 [LMS14] (Gasbrenner)
 - Elco Thision S 13.1 [LMU7] (Gasbrenner)
 - Elco Thision S 17.1 [LMU74] & [RVS63.283] (Gasbrenner)
 - Elco Thision S 25.1 [RSV63.283] (Gasbrenner) + MM [AVS75.390]
 - Fujitsu Waterstage WSYK 160 DC 9 [RVS21.827] (Wärmepumpe)
 - Fujitsu Waterstage WSYP 100 DG 6 [RVS21.831] (Wärmepumpe)
 - MHG Procon E 25 HS [LMS14] (Gasbrenner)
 - Sieger TG11 [RVP54.100] (Ölbrenner) {PPS_only}
 - Weishaupt WTU-25 G mit WRS-CPU B2/E [RVS23.220] (Ölbrenner) {LPB_only}

 - PPS-basierte Regler (wie bspw. RVP digital Serie D, RVP54…, ALBATROS RVA…, LGM11…) bzw. Heizungssysteme, bei denen ein QAA50 / QAA70 zum Einsatz kommt (wie bspw. Brötje WGB 15 / WGB 20 / Triobloc E23 (Eurocontrol K), Weishaupt WRD 0.2 / 1.1, Sieger TG11 (mit Siegermatic S42DB), Olymp THR 5-25C, Schäfer Interdomo (mit DomoCommand DC 225)), allerdings mit PPS-typischer eingeschränkter Funktionalität im Vergleich zu BSB/LPB.

Bitte beachte: Generelle Parameter sollten bei allen Systemen funktionieren, spezifischere Parameter werden sukzessiv hinzugefügt. Deine Hilfe könnte gebraucht werden, wenn du ein Heizungssystem hast, welches mit BSB, LPB oder PPS arbeitet, wofür wir jedoch noch keine spezifischeren Parameter hinzugefügt haben. Erfahre <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/FAQ_de.md#mein-heizungssystem-verf%C3%BCgt-%C3%BCber-parameter-die-von-der-software-bisher-nicht-unterst%C3%BCtzt-werden-kann-ich-behilflich-sein-diese-parameter-hinzuzuf%C3%BCgen">hier</A>, wie du uns helfen kannst.
<BR><BR>
<B>Achtung!</B><BR>
Einige Hersteller, die vormals auf BSB/LPB gesetzt haben, sind bei "günstigeren" Geräten auf andere Bus-Systeme gewechselt. Beispiele hierfür sind die Brötje WLC/WLS/BOK Geräte. Diese sind nicht kompatibel mit BSB/LPB und erlauben nur die Einstellung von wenigen Parametern durch den Benutzer. Besitzer dieser Geräte sind bis dato nicht in der Lage ihr Heizungssystem zu konfigurieren und zu überwachen, wie dies mit teureren (aber BSB/LPB-kompatiblen) Geräten, wie z.B. den oben genannten, möglich ist.
<BR><BR>
Die Forendiskussion die zum Bau dieses Adapters geführt hat, kann <A HREF="https://forum.fhem.de/index.php?topic=29762.new;topicseen#new">hier</A> nachvollzogen werden.<BR>

Bitte beachte, dass der Adapter zwar an einem Raspberry Pi genutzt werden kann, die hier angebotene Software jedoch nur auf dem Arduino läuft! Wenn der Adapter an einem Raspberry Pi genutzt werden soll, muss stattdessen die Software bsb_gateway genutzt werden, die <A HREF="https://github.com/loehnertj/bsbgateway">hier</A> verfügbar ist. Bitte beachte, dass die Funktionalität am Raspberry deutlich weniger umfangreich ist, und dass Du für jegliche Fragen diesbezüglich den Autor von bsb_gateway kontaktieren musst.

Web-Interface screenshots:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/Web-Interface.png" size="50%">
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/Web-Interface2.png" size="50%">

BSB-Adapterplatine unbestückt, mit den Anschlüssen CL+ und CL-:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/BSB-Board%20plain.jpg" size="50%">

BSB-Adapterplatine und Ethernet-Shield auf dem Arduino Mega2560:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/BSB-Board%20on%20Arduino%20Mega%202560.jpg" size="50%">

BSB-Adapterplatine auf dem Raspberry Pi 2:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/schematics/BSB-Board%20on%20Raspberry%20Pi%202.jpg" size="50%">
