# bsb_lan

English version can be found <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/README_de.md">here</A>.

BSB-LAN-Adapter, entwickelt für einen Arduino Mega 2560 samt Ethernet-Shield, um web-basiert die Kontrolle über Elco Thision, Brötje und baugleiche Heizungssysteme zu erlangen.

Prinzipiell sollte diese Kombination aus Hard- und Software mit allen Heizungssystemen lauffähig sein, deren Steuerung über einen BSB verfügt. Unter realen Umständen erwies sich die Kombination auf folgenden Systemen als lauffähig:
 - Brötje ISR-SSR Solarsystemregler
 - Brötje ISR-ZR1 Solar- und Systemregler
 - Brötje NovoCondens SOB 22C / 26C (Öl)
 - Brötje NovoCondens BOB 20 (Öl)
 - Brötje SensoTherm BSW-K (Wärmepumpe)
 - Brötje WGB-U 15H mit Solareinspeisung für TWW (Gas)
 - Brötje WGB 15 E (Gas, Pufferspeicher, Solarunterstützung)
 - Brötje WGB S 17/20 E EcoTherm Plus (Gas)
 - Brötje WBS 22E (Gasbrenner)
 - Elco Straton (Öl)
 - Elco Thision S (Gas)
 - Fujitsu Waterstage (WSYK160DC9) (Wärmepumpe)

Bitte beachten: Generelle Parameter sollten bei allen Systemen funktionieren, spezifischere Parameter werden sukzessiv hinzugefügt. Deine Hilfe könnte gebraucht werden, wenn du ein Heizungssystem hast, welches mit dem BSB arbeitet, wofür wir jedoch noch keine spezifischeren Parameter hinzugefügt haben. Erfahre <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/FAQ.md#my-heating-system-has-parameters-that-are-not-supported-in-the-software-yet-can-i-help-adding-these-parameters">hier</A>, wie du uns helfen kannst.

Instruktionen, wie die Software konfiguriert werden muss etc. können dem README ![hier](https://github.com/fredlcore/bsb_lan/blob/master/BSB_lan/BSB_lan/README_DE.txt) entnommen werden.<BR>
Die Forendiskussion die zum Bau dieses Adapters geführt hat, kann <A HREF="https://forum.fhem.de/index.php?topic=29762.new;topicseen#new">hier</A> nachvollzogen werden.<BR>

Einige Adapter-Bausätze, die direkt auf einen Arduino Mega2560 passen, sind noch von einer Sammelbestellung her verfügbar. Bei Interesse kontaktiere bitte bsb (ät) code-it.de .

BSB-Adapterplatine unbestückt, mit den Anschlüssen CL+ und CL-:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/BSB_lan/schematics/BSB-Board%20plain.jpg" size="50%">

BSB-Adapterplatine bestückt:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/BSB_lan/schematics/BSB-Board.jpg" size="50%">

BSB-Adapterplatine und Ethernet-Shield auf dem Arduino Mega2560:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/BSB_lan/schematics/BSB-Board%20on%20Arduino%20Mega%202560.jpg" size="50%">
