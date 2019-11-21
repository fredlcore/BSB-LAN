# BSB-LPB-PPS-LAN

English version can be found <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/README.md">here</A>. 

LAN-Adapter für den Boiler-System-Bus (BSB), den Local Process Bus (LPB) und die Punkt-zu-Punkt-Schnittstelle (PPS) - entwickelt für einen Arduino Mega 2560 mit Ethernet-Shield zur web-basierten Kontrolle (lokal über LAN aber wenn gewünscht auch über das Internet) von Elco, Brötje und baugleichen Heizungssystemen, einschließlich Logging-Funktion auf Micro-SD-Karte. Dieses Projekt kann in vielfältiger Hinsicht eine kostengünstige Alternative zum OZW 672 oder OCI 700 sein.

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons Lizenzvertrag" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />Dieses Werk ist lizenziert unter einer <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Namensnennung - Nicht-kommerziell - Weitergabe unter gleichen Bedingungen 4.0 International Lizenz</a>.

<B>Bausätze erhältlich!</B> Auf Anfrage sind Platinen mit entsprechenden Bauteilen für die Verwendung am Arduino Mega 2560 erhältlich, bei Interesse bitte e-Mail an bsb (ät) code-it.de schicken (Deutsch/Englisch).

***Ausführliche Informationen zum Adapter und der Software sind im [Handbuch](https://1coderookie.github.io/BSB-LPB-LAN) zu finden.***  
*Eine Schnellinstallationsanleitung ist [hier](https://1coderookie.github.io/BSB-LPB-LAN/kap16.html) verfügbar.*  

Prinzipiell sollte diese Kombination aus Hard- und Software mit allen Heizungssystemen lauffähig sein, deren Steuerung über einen BSB oder LPB verfügt.  
Als einfache Regel kann man sagen, dass die Regler mit einem **S** in der Typenbezeichnung (RV**S** und LM**S**) kompatibel mit BSB-LAN sind und den (nahezu) kompletten Funktionsumfang bieten.  
Die folgende Auflistung gibt eine grobe Übersicht über die Reglertypen, die je nach Typ des Wärmeerzeugers (Öl, Gas, WP etc.) normalerweise verbaut sind (bzw. waren) und die mittels BSB-LAN bedient werden können. Gewisse Einzel- und Spezialfälle (wie bspw. ein RVS-Regler bei einem Gasgerät) sind hier nicht berücksichtigt. Für genauere Informationen bzgl der [Reglertypen](https://1coderookie.github.io/BSB-LPB-LAN/kap03.html#32-detailliertere-auflistung-und-beschreibung-der-unterstützten-regler) und der zu verwendenden [Anschlüsse](https://1coderookie.github.io/BSB-LPB-LAN/kap02.html#23-anschluss-des-adapters) lies bitte im [BSB-LPB-LAN-Handbuch](https://1coderookie.github.io/BSB-LPB-LAN) nach.

**Gasregler:**  
- [LMU74/LMU75](https://1coderookie.github.io/BSB-LPB-LAN/kap03.html#3211-lmu-regler) und (aktuelle Generation) [LMS14/LMS15](https://1coderookie.github.io/BSB-LPB-LAN/kap03.html#3212-lms-regler), Anschluss via BSB, vollumfänglich steuer- und bedienbar  
- [LMU54/LMU64](https://1coderookie.github.io/BSB-LPB-LAN/kap03.html#3211-lmu-regler), Anschluss via PPS, eingeschränkt steuer- und bedienbar   
   
**Öl-/Solar-/Zonenregler:**  
- [RVS43/RVS63/RVS46](https://1coderookie.github.io/BSB-LPB-LAN/kap03.html#3222-rvs-regler), Anschluss via BSB, vollumfänglich steuer- und bedienbar  
- [RVA/RVP](https://1coderookie.github.io/BSB-LPB-LAN/kap03.html#3221-rva--und-rvp-regler), Anschluss via PPS (modellspezifisch vereinzelt auch LPB), eingeschränkt steuer- und bedienbar  
   
**Wärmepumpenregler:**  
- [RVS21/RVS61](https://1coderookie.github.io/BSB-LPB-LAN/kap03.html#3222-rvs-regler), Anschluss via BSB, vollumfänglich steuer- und bedienbar  
   
**Weishaupt (Modell WTU):**  
- [RVS23](https://1coderookie.github.io/BSB-LPB-LAN/kap03.html#3222-rvs-regler), Anschluss via LPB, (nahezu) vollumfänglich steuer- und bedienbar   
   
**Um eine detailliertere Übersicht der gemeldeten Systeme einzusehen, die bisher erfolgreich mit BSB-LAN genutzt werden, folge bitte dem entsprechenden Link:**  
- **[Brötje](https://1coderookie.github.io/BSB-LPB-LAN/kap03.html#311-brötje)**
- **[Elco](https://1coderookie.github.io/BSB-LPB-LAN/kap03.html#312-elco)**
- **[weitere Hersteller (z.B. Fujitsu, Atlantic, Weishaupt)](https://1coderookie.github.io/BSB-LPB-LAN/kap03.html#313-weitere-hersteller)**      
   
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
