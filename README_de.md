# BSB-LPB-PPS-LAN

English version can be found <A HREF="https://github.com/fredlcore/bsb_lan/blob/master/README.md">here</A>. 

Das (englische) Handbuch findet sich [hier](https://docs.bsb-lan.de).

BSB-LAN ist eine Software/Hardware-Lösung, um auf den "Boiler-System-Bus" (BSB), den "Local-Process-Bus (LPB)" und die "Punkt-zu-Punkt-Schnittstelle" (PPS) zuzugreifen. Es gibt den BSB-LAN Adapter für verschiedene *ESP32*-basierte Microcontroller (ESP32 NodeMCU, Olimex EVB, Olimex POE-ISO) bzw. für einen *Arduino Due* mit Ethernet-Shield, um damit web-basiert über LAN/WLAN auf Heizungssysteme von Atlantic, Brötje, Elco und vielen anderen Herstellern, die Siemens-Regler verwenden, zuzugreifen. Damit ist es möglich, die Heizung zu steuern bzw. zu regeln und beliebige Werte zu loggen. Dieses Projekt unterstützt fast alle an den Heizungen verfügbaren Parameter und kann in vielfältiger Hinsicht eine umfangreichere und kostengünstige Alternative zum OZW 672, OCI 700 oder Remocon Net B sein.

---

***Platinen erhältlich!***  
**Es sind Platinen für den ESP32 erhältlich, die einfach nur auf den jeweiligen Microcontroller aufgesteckt werden müssen. Mit dem Kauf eines Boards unterstützt Ihr darüber hinaus die Weiterentwicklung dieses Projekts. Bei Interesse bitte Frederik eine e-Mail an bsb (ät) code-it.de schicken (Deutsch/Englisch).**  

---
   
Mit Hilfe des Adapters und der BSB-LAN-Software können sehr einfach verschiedene Werte und Parameter beobachtet, geloggt und bei Bedarf web-basiert gesteuert und geändert werden.
Eine optionale Einbindung in bestehende Smart-Home-Systeme wie bspw. FHEM, openHAB, HomeMatic, ioBroker, Loxone, IP-Symcon, EDOMI, Home Assistant, SmartHomeNG oder Node-RED kann mittels MQTT, JSON oder HTTP-Zugriffe erfolgen. 
Darüber hinaus ist der Einsatz des Adapters als Standalone-Logger ohne LAN- oder Internetanbindung bei Verwendung einer microSD-Karte ebenfalls möglich.  
Zusätzlich können Temperatur- und Feuchtigkeitssensoren angeschlossen und deren Daten ebenso geloggt und ausgewertet werden. Durch die Möglichkeit, eigenen Code in die BSB-LAN-Software zu integrieren, bietet sich darüber hinaus ein weites Spektrum an Erweiterungsmöglichkeiten. 
  
**Im Folgenden werden einige Modellreihen verschiedener Hersteller aufgelistet, die i.d.R. BSB-LAN-kompatible Regler verbaut haben:**  
- Brötje: BBK, BBS, BGB, BLW (**siehe Ausnahmen unten!**), BMK, BMR, BOB, BSK, BSW, Eurocontrol, ISR, LogoBloc, SGB, SOB, SPK, WBC (**siehe Ausnahmen unten!**), WBS (**siehe Ausnahmen unten!**), WGB (**siehe Ausnahmen unten!**), WMC, WMS, WOB
- **Nicht funktionierende Brötje-Modelle: BOK, BLW Mono, BLW Neo, BLW Split, BSW Neo, WBC 22.1/28.1, WBC 14.1/22.1, WGB-K 22.1/28.1, WGB 14.1/22.1/28.1/38.1, WHC, WHS, WLC, WLS und alle weiteren Modelle mit IWR Regelung** 
- Bösch: Wärmepumpen mit RVS-Controllertyp
- Elco: Aerotop (**nicht Aerotop Mono!**), Aquatop, Rendamax, Straton, Thision (**nicht Thision Mini!**), Thision S, Thision S Plus, Trigon S Plus
- Alarko: Aldens WM/WS
- ATAG: QR
- Atlantic: Alféa, Axeo, Excellia, Extensa, Hynea Hybrid Duo Gaz, Navistem, Perfinox, Varmax
- Austria Email: LWP, LWPK
- Baxi: Luna Platinum, Luna Duo, Block Kondens
- Boesch: SLS
- Chappée: Luna, Klista
- CitrinSolar: proClima
- CTA: Optiheat
- CTC: 380 IC
- Deville: 9942, 9981
- Eco: AiWA, AW, BW, DW, heatLite, Star, TBW, WW, WWi, TWW
- Ecostar: Ecodense WT-S 45
- Etna: II GWS
- EVI Heat: Combi-7
- Fernwärme: RVD230
- Fröling: Rendagas Plus
- Fujitsu Waterstage: Comfort, Duo, WOHA, WSHA, WSYA, WSYK, WSYP
- Gebwell: T2
- Geminox: Thrs
- General: (aka Fujitsu Waterstage) WC13F / WOC13RIYF / WGHA 100DG
- Gorenje: Aerogor Compact, Aerogor Compact EVI, Aerogor ECO Inverter 10 A, Aerogor Split AW, Aerogor Split HD, Aerogor Split HD EVI, Aquagor, Aquagor EVI, Geogor All-In-One, Terragor, Terragor EVI
- Grünenwald: Greenheat
- GS: UnoTec
- Hansa: SND
- Herz: Commotherm 5 DeLuxe
- Hotjet: One2, Wx, ZETXe, ZETXi
- Ideal: Logic Air Heat Pump
- Interdomo: Domostar GBK 25H/SH
- MAN/MHG: Ecostar 200
- MHG: ecoWP Xe, Procon E
- Oilon: SH, SHx
- Olymp: SHS, WHS
- Palazzetti: Choro Sistema Calore
- Robur: K18 Simplygas / Hybrigas
- Sieger: TG11
- Šildymo Technologijų Centras (ŠTC): STC9
- Sixmadun: TG11BE
- Smartheat: UI400
- SSP: Proburner
- Strebel: S-ASX
- Sunex: Nexus
- Termomax: Termo ÖV
- Thercon: Therma Silent Coax Single, THERMA Silent Coax Combi 300/500
- Thermics: Energie
- Thermital: TBox Clima TOP
- Tifell: Biofell
- Variheat: 110C
- Viadrus : Claudius K1, K2
- Viessmann: Vitotwin 300-W (ausschließlich!)
- Wamak: AiWa, DB
- Weishaupt: WTU  

Wenn Deine Heizung einen der folgenden Regler enthält, aber Dein Modell noch nicht aufgeführt ist, setze Dich gerne mit uns in Verbindung, da diese Regler als kompatibel mit einem der unterstützten Bussysteme identifiziert wurden:   
AVS37, AVS55, AVS71, AVS74, AVS75, AVS77, AVS79, LMS14, LMS15, LMS15, LMU64, LMU74, LMU75, RVA61, RVA63, RVA33, RVA36, RVA43, RVA46, RVA47, RVA53, RVA60, RVA61, RVA63, RVA65, RVA66, RVC32, RVD110, RVD115, RVD120, RVD125, RVD130, RVD135, RVD139, RVD140, RVD144, RVD145, RVD230, RVD235, RVD240, RVD245, RVD250, RVD255, RVD260, RVD265, RVL469, RVL470, RVL471, RVL472, RVL479, RVL480, RVL481, RVL482, RVP320, RVP330, RVP340, RVP350, RVP351, RVP360, RVP361, RVP5xx, RVS13, RVS21, RVS23, RVS26, RVS41, RVS43, RVS46, RVS47, RVS51, RVS53, RVS61, RVS63, RVS65, RVS68, RWI65, WRI80

<B>Achtung!</B><BR>
Einige Hersteller, die vormals auf BSB/LPB gesetzt haben, sind bei "günstigeren" Geräten auf andere Bus-Systeme gewechselt. Beispiele hierfür sind die Brötje WLC/WLS/BOK Geräte. Diese sind nicht kompatibel mit BSB/LPB und erlauben nur die Einstellung von wenigen Parametern durch den Benutzer. Besitzer dieser Geräte sind bis dato nicht in der Lage ihr Heizungssystem zu konfigurieren und zu überwachen, wie dies mit teureren (aber BSB/LPB-kompatiblen) Geräten, wie z.B. den oben genannten, möglich ist.
<BR><BR>
Die Forendiskussion die zum Bau dieses Adapters geführt hat, kann <A HREF="https://forum.fhem.de/index.php?topic=29762.new;topicseen#new">hier</A> nachvollzogen werden.<BR>

Bitte beachte, dass der Adapter zwar an einem Raspberry Pi genutzt werden kann, die hier angebotene Software jedoch nur auf dem ESP32 bzw. Arduino läuft! Wenn der Adapter an einem Raspberry Pi genutzt werden soll, muss stattdessen die Software bsb_gateway genutzt werden, die <A HREF="https://github.com/loehnertj/bsbgateway">hier</A> verfügbar ist. Bitte beachte, dass die Funktionalität am Raspberry deutlich weniger umfangreich ist, und dass Du für jegliche Fragen diesbezüglich den Autor von bsb_gateway kontaktieren musst.

Web-Interface screenshots:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/docs/images/Web-Interface.png" size="50%">
<img src="https://github.com/fredlcore/bsb_lan/blob/master/docs/images/Web-Interface2.png" size="50%">

BSB-Adapterplatine in Bestückung für ESP32 Olimex Boards:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/docs/images/Logic%20Level%20Adapter.jpg" size="50%">

BSB-Adapterplatine auf ESP32 Olimex POE im 3D-gedruckten Projekt-Gehäuse:
<img src="https://github.com/fredlcore/bsb_lan/blob/master/docs/images/Logic%20Level%20Adapter%20in%20Case.jpg" size="50%">

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons Lizenzvertrag" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />Dieses Werk ist lizenziert unter einer <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Namensnennung - Nicht-kommerziell - Weitergabe unter gleichen Bedingungen 4.0 International Lizenz</a>.
