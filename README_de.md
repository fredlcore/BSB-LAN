# BSB-LPB-PPS-LAN

English version can be found <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/README.md">here</A>. 

LAN-Adapter für den ["Boiler-System-Bus" (BSB)](https://1coderookie.github.io/BSB-LPB-LAN/kap10.html#1011-bsb), den ["Local-Process-Bus (LPB)](https://1coderookie.github.io/BSB-LPB-LAN/kap10.html#1012-lpb) und die ["Punkt-zu-Punkt-Schnittstelle" (PPS)](https://1coderookie.github.io/BSB-LPB-LAN/kap10.html#1013-pps-schnittstelle) - entwickelt für einen *Arduino Due* mit Ethernet-Shield und für einen *ESP32* zur web-basierten Kontrolle (lokal über W/LAN, aber wenn gewünscht auch über das Internet) von Elco, Brötje und baugleichen Heizungssystemen, einschließlich Logging-Funktion auf Micro-SD-Karte. Dieses Projekt unterstützt mehr als 1300 Parameter unterschiedlicher Heizungen und kann in vielfältiger Hinsicht eine umfangreichere und kostengünstige Alternative zum OZW 672, OCI 700 oder Remocon Net B sein.

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons Lizenzvertrag" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />Dieses Werk ist lizenziert unter einer <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Namensnennung - Nicht-kommerziell - Weitergabe unter gleichen Bedingungen 4.0 International Lizenz</a>.

---

***Bausätze erhältlich!***  
**Auf Anfrage sind Platinen mit entsprechenden Bauteilen für die Verwendung am Arduino Due oder ESP32 erhältlich, bei Interesse bitte Frederik eine e-Mail an bsb (ät) code-it.de schicken (Deutsch/Englisch).**  

---

***Ausführliche Informationen zum Adapter und der Software sind im [Handbuch](https://1coderookie.github.io/BSB-LPB-LAN/) zu finden.***  
   
***Schnellstartanleitungen für die Installation und Inbetriebnahme des BSB-LAN-Setups sind hier verfügbar:***  
***[Schnellstartanleitung für den Arduino Due](https://1coderookie.github.io/BSB-LPB-LAN/SSA_DUE.html)***  
***[Schnellstartanleitung für ESP32-Boards](https://1coderookie.github.io/BSB-LPB-LAN/SSA_ESP32.html)***  
     
---     
   
Mit Hilfe des Adapters und der BSB-LAN-Software können nun unkompliziert verschiedene Funktionen, Werte und Parameter beobachtet, geloggt und bei Bedarf web-basiert gesteuert und geändert werden.
Eine optionale Einbindung in bestehende Smart-Home-Systeme wie bspw. [FHEM](https://1coderookie.github.io/BSB-LPB-LAN/kap08.html#81-fhem), [openHAB](https://1coderookie.github.io/BSB-LPB-LAN/kap08.html#82-openhab), [HomeMatic](https://1coderookie.github.io/BSB-LPB-LAN/kap08.html#83-homematic-eq3), [ioBroker](https://1coderookie.github.io/BSB-LPB-LAN/kap08.html#84-iobroker), [Loxone](https://1coderookie.github.io/BSB-LPB-LAN/kap08.html#85-loxone), [IP-Symcon](https://1coderookie.github.io/BSB-LPB-LAN/kap08.html#86-ip-symcon), [EDOMI](https://1coderookie.github.io/BSB-LPB-LAN/kap08.html#810-edomi), [Home Assistant](https://1coderookie.github.io/BSB-LPB-LAN/kap08.html#811-home-assistant), [SmartHomeNG](https://1coderookie.github.io/BSB-LPB-LAN/kap08.html#812-smarthomeng) oder [Node-RED](https://1coderookie.github.io/BSB-LPB-LAN/kap08.html#813-node-red) kann mittels [HTTPMOD](https://1coderookie.github.io/BSB-LPB-LAN/kap08.html#812-einbindung-mittels-httpmod-modul), [MQTT](https://1coderookie.github.io/BSB-LPB-LAN/kap05.html#52-mqtt) oder [JSON](https://1coderookie.github.io/BSB-LPB-LAN/kap05.html#53-json) erfolgen. 
Darüber hinaus ist der Einsatz des Adapters als [Standalone-Logger](https://1coderookie.github.io/BSB-LPB-LAN/kap06.html#61-loggen-von-daten) ohne LAN- oder Internetanbindung bei Verwendung einer microSD-Karte ebenfalls möglich.  
Zusätzlich können [Temperatur- und Feuchtigkeitssensoren](https://1coderookie.github.io/BSB-LPB-LAN/kap07.html#71-verwendung-optionaler-sensoren-dht22-ds18b20-bme280) angeschlossen und deren Daten ebenso geloggt und ausgewertet werden. Durch die Verwendung eines Arduino und die Möglichkeit, [eigenen Code in die BSB-LAN-Software zu integrieren](https://1coderookie.github.io/BSB-LPB-LAN/kap06.html#68-eigenen-code-in-bsb-lan-einbinden), bietet sich darüber hinaus ein weites Spektrum an Erweiterungsmöglichkeiten. 
   
Prinzipiell sollte diese Kombination aus Hard- und Software mit allen Heizungssystemen lauffähig sein, deren Steuerung über einen BSB oder LPB verfügt.  
Als einfache Regel kann man sagen, dass die Regler mit einem **S** in der Typenbezeichnung (RV**S** und LM**S**) kompatibel mit BSB-LAN sind und den (nahezu) kompletten Funktionsumfang bieten.  
Die folgende Auflistung gibt eine grobe Übersicht über die Reglertypen, die je nach Typ des Wärmeerzeugers (Öl, Gas, WP etc.) normalerweise verbaut sind (bzw. waren) und die mittels BSB-LAN bedient werden können. Gewisse Einzel- und Spezialfälle (wie bspw. ein RVS-Regler bei einem Gasgerät) sind hier nicht berücksichtigt. Für genauere Informationen bzgl der [Reglertypen](https://1coderookie.github.io/BSB-LPB-LAN/kap10.html#102-detaillierte-beschreibung-der-kompatiblen-regler) und der zu verwendenden [Anschlüsse](https://1coderookie.github.io/BSB-LPB-LAN/kap03.html#31-anschluss-des-adapters) lies bitte im [BSB-LPB-LAN-Handbuch](https://1coderookie.github.io/BSB-LPB-LAN/) nach.

**Gasregler:**  
- [LMU74/LMU75](https://1coderookie.github.io/BSB-LPB-LAN/kap10.html#10211-lmu-regler) und (aktuelle Generation) [LMS14/LMS15](https://1coderookie.github.io/BSB-LPB-LAN/kap10.html#10212-lms-regler), Anschluss via BSB  
- [LMU54/LMU64](https://1coderookie.github.io/BSB-LPB-LAN/kap10.html#10211-lmu-regler), Anschluss via PPS   
   
**Öl-/Solar-/Zonenregler:**  
- [RVS43/RVS63/RVS46](https://1coderookie.github.io/BSB-LPB-LAN/kap10.html#10222-rvs-regler), Anschluss via BSB  
- [RVA/RVP](https://1coderookie.github.io/BSB-LPB-LAN/kap10.html#10221-rva--und-rvp-regler), Anschluss via PPS (modellspezifisch vereinzelt auch LPB)  
   
**Wärmepumpenregler:**  
- [RVS21/RVS61](https://1coderookie.github.io/BSB-LPB-LAN/kap10.html#10222-rvs-regler), Anschluss via BSB  
   
**Weishaupt (Modell WTU):**  
- [RVS23](https://1coderookie.github.io/BSB-LPB-LAN/kap10.html#10222-rvs-regler), Anschluss via LPB      
  
**Im Folgenden werden einige Modellreihen verschiedener Hersteller aufgelistet, die i.d.R. BSB-LAN-kompatible Regler verbaut haben:**  
- Brötje: BBK, BBS, BGB, BLW, BMR, BOB, BSK, SOB, WBS, WGB, WGB EVO, WGB Pro EVO, WGB-M, WGB-U, WOB  
- Bösch: Wärmepumpen mit RVS-Reglern
- Elco: Aerotop, Aquatop, Straton, Thision, Thision S, Thision S Plus  
- ATAG: QR  
- Atlantic: Alféa Evolution, Excellia, Extensa  
- Austria Email: LWPK  
- Baxi: Luna Platinum
- Chappée: Klista
- CTA: Optiheat  
- Deville: 9942, 9981
- EVI Heat: Combi-7
- Fernwärme: RVD230
- Froeling: Rendagas Plus
- Fujitsu Waterstage: Comfort, Duo
- Geminox: Thrs
- Gruenenwald: Greenheat
- Hansa: SND
- Interdomo: Domostar GBK 25H/SH
- MAN/MHG: Ecostar 200
- MHG: Procon E
- Oilon: SH, SHx
- Olymp: SHS, WHS
- Sieger: TG11
- Sixmadun: TG11BE
- Termomax: Termo ÖV
- Thermics: Energie
- Thermital: TBox Clima TOP
- Viessmann: Vitotwin 300-W
- Wamak: DB
- Weishaupt: WTU
   
***Um eine detailliertere Übersicht der gemeldeten Systeme einzusehen, die bisher erfolgreich mit BSB-LAN genutzt werden, folge bitte dem entsprechenden Link:***  
- **[Brötje](https://1coderookie.github.io/BSB-LPB-LAN/kap11.html#111-brötje)**
- **[Elco](https://1coderookie.github.io/BSB-LPB-LAN/kap11.html#112-elco)**
- **[weitere Hersteller (z.B. Fujitsu, Atlantic, Weishaupt)](https://1coderookie.github.io/BSB-LPB-LAN/kap11.html#113-weitere-hersteller)**      
   
Bitte beachte: Generelle Parameter sollten bei allen Systemen funktionieren, spezifischere Parameter werden sukzessiv hinzugefügt. Deine Hilfe könnte gebraucht werden, wenn du ein Heizungssystem hast, welches mit BSB, LPB oder PPS arbeitet, wofür wir jedoch noch keine spezifischeren Parameter hinzugefügt haben. Erfahre <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/FAQ_de.md#mein-heizungssystem-verf%C3%BCgt-%C3%BCber-parameter-die-von-der-software-bisher-nicht-unterst%C3%BCtzt-werden-kann-ich-behilflich-sein-diese-parameter-hinzuzuf%C3%BCgen">hier</A>, wie du uns helfen kannst.
<BR><BR>
<B>Achtung!</B><BR>
Einige Hersteller, die vormals auf BSB/LPB gesetzt haben, sind bei "günstigeren" Geräten auf andere Bus-Systeme gewechselt. Beispiele hierfür sind die Brötje WLC/WLS/BOK Geräte. Diese sind nicht kompatibel mit BSB/LPB und erlauben nur die Einstellung von wenigen Parametern durch den Benutzer. Besitzer dieser Geräte sind bis dato nicht in der Lage ihr Heizungssystem zu konfigurieren und zu überwachen, wie dies mit teureren (aber BSB/LPB-kompatiblen) Geräten, wie z.B. den oben genannten, möglich ist.
<BR><BR>
Die Forendiskussion die zum Bau dieses Adapters geführt hat, kann <A HREF="https://forum.fhem.de/index.php?topic=29762.new;topicseen#new">hier</A> nachvollzogen werden.<BR>

Bitte beachte, dass der Adapter zwar an einem Raspberry Pi genutzt werden kann, die hier angebotene Software jedoch nur auf dem Arduino läuft! Wenn der Adapter an einem Raspberry Pi genutzt werden soll, muss stattdessen die Software bsb_gateway genutzt werden, die <A HREF="https://github.com/loehnertj/bsbgateway">hier</A> verfügbar ist. Bitte beachte, dass die Funktionalität am Raspberry deutlich weniger umfangreich ist, und dass Du für jegliche Fragen diesbezüglich den Autor von bsb_gateway kontaktieren musst.

Web-Interface screenshots:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/BSB_LAN/schematics/Web-Interface.png" size="50%">
<img src="https://github.com/fredlcore/bsb_lan/blob/master/BSB_LAN/schematics/Web-Interface2.png" size="50%">

BSB-Adapterplatine unbestückt, mit den Anschlüssen CL+ und CL- sowie den zwingend benötigten Pin-Anschlüssen in roter Umrandung:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/BSB_LAN/schematics/BSB-Board%20plain.jpg" size="50%">

BSB-Adapterplatine und Ethernet-Shield auf dem Arduino Due:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/BSB_LAN/schematics/BSB-Board%20on%20Arduino%20Due.jpg" size="50%">
