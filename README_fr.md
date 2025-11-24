#BSB-LPB-PPS-LAN

[<img src="https://img.shields.io/github/last-commit/fredlcore/BSB-LAN">]()
[<img src="https://img.shields.io/github/commit-activity/t/fredlcore/BSB-LAN">]()
[<img src="https://img.shields.io/github/stars/fredlcore/BSB-LAN?style=plastic">](https://github.com/fredlcore/BSB-LAN/stargazers)
[<img src="https://img.shields.io/github/forks/fredlcore/BSB-LAN?style=plastic">](https://github.com/fredlcore/BSB-LAN/forks)
[<img src="https://img.shields.io/github/followers/fredlcore?style=plastic">](https://github.com/fredlcore?tab=followers)

Die deutsche Fassung dieser Datei gibt es [hier](README_de.md).

The English version of this file is available [here](README.md).

Avant de commencer, merci de lire le manuel [ici](https://docs.bsb-lan.de/fr/).

BSB-LAN est une solution matérielle et logicielle permettant d’accéder au “Boiler-System-Bus” (BSB), au “Local-Process-Bus (LPB)” et à “l'interface point-à-point” (PPS). L’adaptateur est disponible pour divers microcontrôleurs basés sur ESP32 (ESP32 NodeMCU, Olimex EVB, Olimex POE-ISO) ainsi que pour un Arduino Due avec shield Ethernet. Il permet d’accéder aux systèmes de chauffage d’Atlantic, Brötje, Elco et de nombreux autres fabricants via LAN/WLAN, à condition qu’ils utilisent l’un des contrôleurs Siemens listés ci-dessous. BSB-LAN permet de piloter ou de réguler le chauffage et de journaliser différentes valeurs. Ce projet prend en charge presque tous les paramètres disponibles sur les systèmes de chauffage et constitue une alternative plus complète et économique aux modules OZW 672, OCI 700 ou Remocon Net B.

---

***Kits d’interface disponibles !***

**Des cartes d’interface pour ESP32 sont disponibles sur demande. Elles peuvent simplement être enfichées sur l’un des microcontrôleurs listés. L’achat de ces cartes permet de soutenir ce projet à l’avenir. Si vous êtes intéressé, merci d’envoyer un e-mail à Frederik (allemand ou anglais) à <br /> bsb (ät) code-it.de <br /> pour plus d’informations.**

---

En utilisant l’adaptateur et le logiciel BSB-LAN, diverses valeurs et paramètres peuvent être facilement surveillés, journalisés et, si désiré, contrôlés et modifiés via une interface web.
L’intégration dans des systèmes domotiques existants comme FHEM, openHAB, HomeMatic, ioBroker, Loxone, IP-Symcon, EDOMI, Home Assistant, SmartHomeNG ou Node-RED est possible via MQTT, JSON ou HTTP.
L’adaptateur peut également fonctionner en mode autonome sans connexion LAN ou Internet en utilisant une carte microSD.
Des capteurs de température et d’humidité peuvent également être connectés et leurs données enregistrées et analysées. Il est également possible d’intégrer son propre code dans le logiciel BSB-LAN, offrant ainsi de nombreuses possibilités d’extension.

**Ci-dessous, certaines séries de modèles de différents fabricants sont répertoriées, qui ont généralement installé des contrôleurs compatibles BSB-LAN :**  
- Brötje: BBK, BBS, BGB, BLW (**voir les exceptions ci-dessous !**), BMK, BMR, BOB, BSK, BSW, Eurocontrol, ISR, LogoBloc, SGB, SOB, SPK, WBC (**voir les exceptions ci-dessous !**), WBS (**voir les exceptions ci-dessous !**), WGB (**voir les exceptions ci-dessous !**), WMC, WMS, WOB
- **Modèles Brötje non fonctionnels : BOK, BLW Mono, BLW Neo, BLW Split, BSW Neo, WBC 22.1/28.1, WBC 14.1/22.1, WGB-K 22.1/28.1, WGB 14.1/22.1/28.1/38.1, WHC, WHS, WLC, WLS et tous les autres avec contrôleur IWR**  
- Bösch: pompes à chaleur avec contrôleur de type RVS
- Elco: Aerotop (**pas Aerotop Mono !**), Aquatop, Rendamax, Straton, Thision (**pas Thision Mini!**), Thision S, Thision S Plus, Trigon S Plus
- Alarko: Aldens WM/WS
- ATAG: QR
- Atlantic: Alféa, Axeo, Excellia, Extensa, Hynea hybrid duo gaz, Navistem, Perfinox, Varmax
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
- Froeling: Rendagas Plus
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
- Viessmann: Vitotwin 300-W (seulement !)
- Wamak: AiWa, DB
- Weishaupt: WTU  


Si votre appareil de chauffage est équipé de l'un des contrôleurs suivants, mais que votre modèle n'est pas répertorié dans notre manuel, n'hésitez pas à nous contacter, car le fonctionnement de ces modèles a été confirmé :
AVS37, AVS55, AVS71, AVS74, AVS75, AVS77, AVS79, LMS14, LMS15, LMS15, LMU64, LMU74, LMU75, RVA61, RVA63, RVA33, RVA36, RVA43, RVA46, RVA47, RVA53, RVA60, RVA61, RVA63, RVA65, RVA66, RVC32, RVD110, RVD115, RVD120, RVD125, RVD130, RVD135, RVD139, RVD140, RVD144, RVD145, RVD230, RVD235, RVD240, RVD245, RVD250, RVD255, RVD260, RVD265, RVL469, RVL470, RVL471, RVL472, RVL479, RVL480, RVL481, RVL482, RVP320, RVP330, RVP340, RVP350, RVP351, RVP360, RVP361, RVP5xx, RVS13, RVS21, RVS23, RVS26, RVS41, RVS43, RVS46, RVS47, RVS51, RVS53, RVS61, RVS63, RVS65, RVS68, RWI65, WRI80
<BR><BR>

<B>Attention !</B><BR>
Certaines entreprises qui utilisaient auparavant BSB/LPB dans leurs systèmes de chauffage ont désormais opté pour d’autres systèmes sur leurs gammes économiques. C’est le cas des séries WLC/WLS/BOK de Brötje. Ces modèles ne sont pas compatibles avec BSB/LPB et ne permettent à l’utilisateur de configurer qu’un nombre très limité de paramètres. Si vous possédez l’un de ces systèmes, il ne sera pas possible de le configurer et de le surveiller comme c’est le cas avec les appareils compatibles BSB/LPB mentionnés plus haut.

Les instructions de configuration et autres se trouvent dans le <A HREF="https://docs.bsb-lan.de/fr/">manuel</A>.<BR>
Le fil de discussion ayant conduit au développement de cette interface se trouve <A HREF="http://forum.fhem.de/index.php?topic=29762.new;topicseen#new">ici</A>.<BR>
(Le forum est en allemand, mais plusieurs membres parlent anglais)

Veuillez noter que bien que la carte puisse également être utilisée sur Raspberry Pi, le logiciel fourni ici ne fonctionne que sur ESP32 et Arduino Due ! Pour utiliser la carte avec le Pi, il faut utiliser le logiciel bsb_gateway disponible <A HREF="https://github.com/loehnertj/bsbgateway">ici</A>. Veuillez aussi noter que les fonctionnalités diffèrent significativement et que vous devrez contacter l’auteur de bsb_gateway pour toute question à son sujet.

Captures d’écran de l’interface web :
<img src="https://github.com/fredlcore/bsb_lan/blob/master/docs/images/Web-Interface.png" size="50%">
<img src="https://github.com/fredlcore/bsb_lan/blob/master/docs/images/Web-Interface2.png" size="50%">

Carte BSB montée pour les cartes ESP32 Olimex :
<img src="https://github.com/fredlcore/bsb_lan/blob/master/docs/images/Logic%20Level%20Adapter.jpg" size="50%">

Carte BSB sur Olimex POE dans le boîtier imprimé 3D du projet :
<img src="https://github.com/fredlcore/bsb_lan/blob/master/docs/images/Logic%20Level%20Adapter%20in%20Case.jpg" size="50%">

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Licence Creative Commons" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />Ce travail est sous licence <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution - Pas d’Utilisation Commerciale - Partage dans les Mêmes Conditions 4.0 International</a>.
