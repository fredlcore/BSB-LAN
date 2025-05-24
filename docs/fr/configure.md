# Configuration
Il existe deux façons de configurer BSB-LAN :

1. Via le fichier de configuration `BSB_LAN_config.h`
1. Via l'interface web en appelant [http://bsb-lan.local/C](http://bsb-lan.local/C) (ou l'adresse IP correspondante)

Pour la configuration initiale, certains paramètres doivent être configurés dans le fichier de configuration (tels que les paramètres de langue et de réseau).  
Toutes les modifications ultérieures peuvent être effectuées via l'interface web. Il peut cependant être utile de configurer (également) le fichier de configuration dans le cas où tu devrais changer de microcontrôleur. Presque tous les paramètres existent également dans l'interface web et vice versa.

Sur un microcontrôleur basé sur ESP32, BSB-LAN configurera son propre point d'accès sans fil nommé `BSB-LAN` s'il ne peut pas se connecter à un réseau. Ainsi, même sans aucune configuration supplémentaire, tu peux te connecter à ce point d'accès avec le mot de passe `BSB-LPB-PPS-LAN` et accéder à BSB-LAN via l'adresse IP `http://192.168.4.1` et poursuivre la configuration de cette manière. Gardez à l'esprit que si tu as défini un mot de passe ou un nom d'utilisateur et un mot de passe HTTP, ceux-ci sont toujours requis si ces détails sont stockés dans l'EEPROM ou `BSB_LAN_config.h`.

---
## Configuration via `BSB_LAN_config.h`

Le fichier de configuration se compose de variables qui sont utilisées dans d'autres parties de BSB-LAN. Il est donc important de **ne modifier que le contenu** des variables (c'est-à-dire les paramètres) et **pas le type** des variables. Ainsi, si tu as par exemple le paramètre  
`byte ip_addr[4] = {192,168,178,88} ;`  
tu ne dois pas modifier la partie `byte ip_addr[4] =`, mais seulement le contenu, dans ce cas l'adresse IP séparée par des virgules.

---
## Configuration via l'interface web

La configuration de BSB-LAN via l'interface web est assez simple, car tu n'as pas à te soucier des noms de variables, mais tu disposes de descriptions claires.  
Au départ, seul un nombre limité d'options de configuration sont affichées dans l'interface web (indiqués en **gras** ci-dessous). Pour accéder à l'ensemble des paramètres, tu dois définir l'option "extended configuration" sur "on".

---
## Aperçu des options de configuration
<style>
table th:first-of-type {
    width: 20% ;
}
table th:nth-of-type(2) {
    width: 20% ;
}
table th:nth-of-type(3) {
    width: 40% ;
}
table th:nth-of-type(4) {
    width: 20% ;
}
</style>
### Paramètres généraux
|Interface Web|Fichier de configuration|Fonctionnalité|Paramètres possibles|
|-------------|------------------------|--------------|--------------------|
|-            |`#define LANG`          |Définir la langue|`DE`, `EN`, `FR` et autres codes de pays ISO|
|**Afficher la configuration étendue**|-   |Afficher toutes les options de configuration|**On**<br>**Off**|
|**Lire la configuration depuis l'EEPROM**|`UseEEPROM`|Lire la configuration depuis l'EEPROM ou le fichier|**On** (`1`)<br>**Off** (`0`)|
|Niveau d'accès en écriture|-          |Si `DEFAULT_FLAG` est défini sur `FL_SW_CTL_RONLY`, définir le niveau d'accès en écriture ici.|**Off** (lecture seule)<br>**On (Standard)**<br>**On (Complet)**|
|Vérifier les mises à jour|`enable_version_check`|Interroger le serveur BSB-LAN pour une nouvelle version disponible|**On** (`true`)|
|Mise à jour OTA|`enable_ota_update`   |Activer la mise à jour OTA (Over-The-Air)|**On** (`true`)|
|Économie d'énergie|`esp32_save_energy`|Réduit la vitesse, économise l'énergie. Ne pas activer lors de l'utilisation du Wi-Fi.|**On** (`true`)<br>**Off** (`false`)|                        |
| Système de fichiers du serveur Web | `webserver` | Active le service de fichiers depuis la carte SD | **On** (`true`) <br>**Off** (`false`) |
| -            | `#define DEFAULT_FLAG` | Définir l'accès en lecture/écriture au système de chauffage. `FL_RONLY` définit tous les paramètres en lecture seule. `FL_SW_CTL_RONLY` permet de définir l'accès en lecture/écriture via le paramètre de configuration de l'interface web. <BR>`0` donne le droit de réécrire tous les paramètres pouvant être écrits. **Ne pas utiliser cette option sauf instruction contraire !** | **FL_RONLY** <BR>**FL_SW_CTL_RONLY** <BR>**0** |

### Paramètres de bus
|Interface Web|Fichier de configuration|Fonctionnalité|Paramètres possibles|
|-------------|------------------------|--------------|--------------------|
|**Type de bus**|`bus_type`              |Type de bus (BSB/LPB/PPS)|**BSB** (`0`)<br>**LPB** (`1`)<br>**PPS** (`2`)|
| **Mode PPS** | `pps_write` | BSB-LAN peut agir comme une unité de pièce PPS (uniquement si aucune unité de pièce réelle n'est connectée) ou simplement écouter passivement. | **passif** (`0`) <br>**en tant qu'unité de pièce** (`1`) |
| **Modèle QAA PPS** | `QAA_TYPE` | Unité de pièce qui doit être simulée pour le bus PPS | **QAA70** (`0x53`), **QAA50** (`0x52`), **QAA95** (`0x37`), **QAW10** (`0x4D`), **QAW20** (`0x4E`), **MCBA/REA70/DC225** (`0x58`), **QAA10** (`0x5A`), **QAA20** (`0x5B`), **QAA12/13** (`0x5D`), **BMU** (`0x66`), **RVD130** (`0x43`) |
| Adresse propre | `own_address` | Adresse de bus propre (par défaut `66` ne doit pas être modifiée) | **66** (`66`) |
| Adresse de destination | `dest_address` | Adresse de bus de destination. <br>Pour **BSB** toujours `0`. <br>Pour **LPB** `0` si l'appareil de destination se trouve dans le segment 1, adresse de l'appareil 0. <BR>Pour convertir de la notation de segment et d'adresse d'appareil LPB en adresse de destination, multipliez le segment par 16, ajoutez l'adresse de l'appareil et soustrayez un. Par exemple, pour adresser un appareil du segment 4 avec l'adresse de l'appareil 3, l'adresse de destination est `(4 * 16) + 3 - 1 = 66`. <br>Pour **PPS** non pertinent. | **0** (`0`) |
| Numéro d'épingle RX <br>Numéro d'épingle TX | `bus_pins` | Définir les broches RX/TX pour communiquer avec l'adaptateur BSB-LAN. Laissez à `0` pour la détection automatique. | **0** et **0** (`0, 0`) |

### Paramètres réseau
|Interface Web|Fichier de configuration|Fonctionnalité|Paramètres possibles         |
|-------------|------------------------|--------------|-----------------------------|
| **Périphérique réseau** | `network_type` | Choisissez entre WLAN et LAN pour connecter BSB-LAN au réseau. | **LAN** (`0`) <br>**WLAN** (`1`) |
|**Nom du réseau WLAN**|`wifi_ssid`        |Définir le nom du réseau WLAN|**Your_WLAN_name** (`Your_WLAN_name`)|
|**Mot de passe WLAN**|`wifi_pass`         |Définir le mot de passe du WLAN|**YourWLANpassword** (`YourWLANpassword`)|
|Utilisation du DHCP|`use_dhcp`        |Définir si oui ou non utiliser DHCP|**On** (`true`)<br>**Off** (`false`)|
| Adresse IP (fixe) | `ip_addr` | Quand tu n'utilises pas DHCP, tu peux définir une adresse IP fixe ici. Sinon, laisse à `0.0.0.0`. Dans l'interface web, tu peux utiliser la notation par points. Dans le fichier de configuration, tu dois utiliser une virgule comme séparateur. | **192.168.178.88** (`192,168,178,88`) |
| Sous-réseau | `subnet_addr` | Sous-réseau quand tu utilises une adresse IP fixe. Même notation que pour l'adresse IP. | **255.255.255.0** (`255,255,255,0`) |
| Passerelle | `gateway_addr` | Adresse de la passerelle quand tu utilises une adresse IP fixe. Même notation que pour l'adresse IP. | **192.168.178.1** (`192,168,178,1`) |
| Serveur DNS | `dns_addr` | Adresse du serveur DNS quand tu utilises une adresse IP fixe. Même notation que pour l'adresse IP. | **192.168.178.1** (`192,168,178,1`) |
| Port TCP | `HTTPPort` | Numéro de port HTTP pour accéder à l'interface web. Par défaut `80`. | **80** (`80`) |
| Adresse MAC | `mac` | Définir une adresse MAC fixe. Uniquement pertinent sur Arduino. | **00:80:41:19:69:90** (`0x00, 0x80, 0x41, 0x19, 0x69, 0x90`) |
| Nom d'hôte mDNS | `mDNS_hostname` | Nom d'hôte pour la découverte mDNS | **BSB-LAN** (`BSB-LAN`) |
| Authentification HTTP | `USER_PASS` | Si ce paramètre n'est pas vide, il contient le nom d'utilisateur et le mot de passe pour l'authentification HTTP, séparés par un deux-points. | **Nom d'utilisateur: Mot de passe** (`Username:Password`) |
| Mot de passe URL | `PASSKEY` | Ce paramètre ajoute une séquence définie par l'utilisateur qui doit être ajoutée à l'URL après le nom d'hôte. <BR>Par exemple, un mot de passe de `1234` nécessite que chaque URL soit écrite comme `http://bsb-lan.local/1234/` au lieu de simplement `http://bsb-lan.local/`. Laisse vide pour aucun mot de passe. | **1234** (`1234`) |
| Adresse IP de confiance | `trusted_ip_addr` | L'accès à BSB-LAN est possible uniquement depuis cette adresse IP. Même notation que pour l'adresse IP. | **192.168.178.89** (`192,168,178,89`) |
| Adresse IP de confiance | `trusted_ip_addr2` | L'accès à BSB-LAN est possible uniquement depuis cette adresse IP. Même notation que pour l'adresse IP. | **192.168.178.90** (`192,168,178,90`) |
| [](){#BSSID}- | `bssid` | Entre ici une adresse BSSID spécifique pour être sûr de te connecter à un point d'accès précis. Laisse à zéro pour ne pas l'utiliser. | (`0x00, 0x00, 0x00, 0x00, 0x00, 0x00`) |
| - | `ntp_server` | Définis un serveur NTP ici pour obtenir l'heure exacte pour BSB-LAN. Laisse une chaîne vide si tu ne veux pas utiliser de serveur NTP. Uniquement pour les microcontrôleurs basés sur ESP32. | (`pool.ntp.org`) |
| - | `local_timezone` | Fuseau horaire à utiliser pour NTP. Voir [ici](https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv) pour une liste complète. | (`CET-1CEST,M3.5.0,M10.5.0/3`) |

### Journalisation

| Interface Web | Fichier de configuration | Fonctionnalité | Paramètres possibles |
| ------------- | ---------------------- | ------------- | ------------------- |
| **Périphérique de stockage** | `LogDestination` | Sélectionne la destination pour écrire tes logs. La carte SD est fortement recommandée, car l'utilisation de la mémoire flash interne finira par l'user. | **Carte SD** (`SDCARD`) <br>**Mémoire flash interne** (`FLASH`) |
| **Mode de log** | `LoggingMode` | Définir la destination des logs. Plusieurs sélections sont possibles, dans ce cas, les valeurs doivent être ajoutées, par exemple, pour envoyer au courtier MQTT et à UDP, définir la valeur sur `4 + 16 = 20` | **Écrire sur la carte SD** (`1`) <br>**Calculer les moyennes sur 24 heures** (`2`) <br>**Envoyer au courtier MQTT** (`4`) <br>**Envoyer uniquement les paramètres de journalisation au courtier MQTT** (`8`) <br>**Envoyer à UDP** (`16`) |
| **Intervalle de journalisation** | `log_interval` | Intervalle pour l'envoi des logs (en secondes) | **60** (`60`) |
| **Paramètres de journalisation** | `log_parameters` | Liste des paramètres à logger. Voir les instructions d'adressage ci-dessous. | **8700, 8743!2, 8314!2** (`{8700, -1}, {8743, 2}, {8314, 2}`) |
| Journaliser les télégrammes de bus | `logTelegram` | Log les télégrammes de bus bruts, comme les messages de diffusion ou les télégrammes inconnus | **Off** (`LOGTELEGRAM_OFF`) <br>**Journaliser tous les télégrammes de bus** (`LOGTELEGRAM_ON`) <br>**Journaliser uniquement les télégrammes de bus inconnus** (`LOGTELEGRAM_UNKNOWN_ONLY`) <br>**Journaliser uniquement les télégrammes de bus de diffusion** (`LOGTELEGRAM_BROADCAST_ONLY`) <br>**Journaliser uniquement les télégrammes de bus de diffusion inconnus** (`LOGTELEGRAM_UNKNOWN_ONLY + LOGTELEGRAM_BROADCAST_ONLY`) |
| **Paramètres de moyenne sur 24 heures** | `avg_parameters` | Liste des paramètres pour la génération de moyennes sur 24 heures. Voir les instructions d'adressage ci-dessous. | **8700, 8743!2, 8314!2** (`{8700, -1}, {8743, 2}, {8314, 2}`) |
|-|`replaceDisabled`|Dans les paramètres avec des valeurs numériques, ce réglage définit la valeur pour un état désactivé/inactif. Par défaut `---`. Home Assistant attend `None`, d'autres peuvent attendre `0` pour fonctionner correctement.|(`None`)|
| - | `#define DEFAULT_DAYS_TO_PLOT` | Défini le nombre de jours par défaut à tracer pour les données de log | (`3`) |

### MQTT

| Interface Web | Fichier de configuration | Fonctionnalité | Paramètres possibles |
| ------------- | ---------------------- | ------------- | ------------------- |
| **Serveur de courtier MQTT** | `mqtt_broker_addr` | Nom d'hôte/IP du courtier MQTT | **my-mqtt-broker.local** (`my-mqtt-broker.local`) |
| **Nom d'utilisateur MQTT** | `MQTTUsername` | Nom d'utilisateur facultatif pour le courtier MQTT | **MyMQTTusername** (`MyMQTTusername`) |
| **Mot de passe MQTT** | `MQTTPassword` | Mot de passe facultatif pour le courtier MQTT | **MyMQTTpassword** (`MyMQTTpassword`) |
| ID de l'appareil MQTT | `MQTTDeviceID` | Identifiant de l'appareil pour MQTT | **BSB-LAN** (`BSB-LAN`) |
| Préfixe de sujet MQTT | `MQTTTopicPrefix` | Préfixe de sujet pour MQTT | **BSB-LAN** (`BSB-LAN`) |
| Utilisation de MQTT | `mqtt_mode` | Définis le format des messages MQTT | **Texte brut** (`1`) - Envoie le numéro et la valeur du paramètre au format texte brut<br>**JSON** (`2`) - Envoie les messages au format JSON (numéro et valeur du paramètre uniquement)<br>**JSON enrichi** (`3`) - Envoie le numéro, le nom, la valeur, l’unité et les erreurs du paramètre au format JSON.|
|MQTT Units|`mqtt_unit_set`|Types d’unités à envoyer via MQTT|**Localisé** (`CF_MQTT_UNIT_LOCALIZED`) envoie les unités dans la langue que t’as choisie, exactement comme elles s’affichent dans l’interface web de BSB-LAN.<br>**Home Assistant** (`CF_MQTT_UNIT_HOMEASSISTANT`) envoie les unités dans un format compatible avec Home Assistant.<br>**Aucun** (`CF_MQTT_UNIT_NONE`) envoie les messages MQTT sans texte d’unité.<br>**Remarque** : Ce réglage s’applique seulement au mode MQTT 3 (Rich JSON) et à la détection automatique MQTT. Ça change rien à l’interface web, qui affiche toujours les unités dans la langue locale.  

### Capteurs et appareils externes

| Interface Web | Fichier de configuration | Fonctionnalité | Paramètres possibles |
| ------------- | ---------------------- | ------------- | ------------------- |
|Broche OneWire|`One_Wire_Pin`|Définis la broche OneWire (utilise `-1` dans le fichier de config pour désactiver)|**10** (`10`)|
| Broches DHT|`DHT_Pins`|Défini les broches du capteur DHT22 (utilise `-1` dans le fichier de configuration pour désactiver)| **11, 12, 13** (`11, 12, 13, -1, -1, -1, -1, -1, -1`) |
| Capteurs BME280 | `BME_Sensors` | Défini le nombre de capteurs BME280 sur le bus I2C. Tu dois avoir accès aux broches I2C. Les adresses fixes `0x76` et `0x77` seront utilisées. Utilise `0` pour désactiver. | **1** (`1`) |
| Utilisation de MAX ! | `enable_max_cul` | Activer ou désactiver la connexion à CUNO/CUNX/MAX!Cube modifié | **On** (`true`)<br>**Off** (`false`)||
| Adresse IP du cube | `max_cul_ip_addr` | Adresse IP du CUNO/CUNX/MAX!Cube | **192.168.178.21** (`192,168,178,21`) |
| Appareils MAX ! | `max_device_list` | ID des appareils MAX ! à interroger. Ces ID peuvent être trouvés sur une étiquette de l'appareil. Après les avoir entrés ici, chaque appareil doit être mis en mode d'appariement. Cette opération doit être répétée chaque fois que la disposition EEPROM de BSB-LAN est modifiée (voir le journal des modifications). | **KEQ0502326, KEQ0505080, KHA0002948** (`"KEQ0502326", "KEQ0505080", "KHA0002948"`) |
| Utilisation de IPWE | `enable_ipwe` | Activer l'extension IPWE (`/ipwe.cgi`) | **On** (`true`)<br>**Off** (`false`) |
| Paramètres IPWE | `ipwe_parameters` | Liste des paramètres à afficher dans l'extension IPWE. Voir les instructions d'adressage ci-dessous. | 8700, 8743!2, 8314!2 ({8700, -1}, {8743, 2}, {8314, 2}) |

### Débogage

| Interface Web | Fichier de configuration | Fonctionnalité | Paramètres possibles |
| ------------- | --- | --- | --- |
| Utilisation du débogage | `debug_mode` | Sélectionne la sortie de débogage | **Off** (`0`)<br>**Série** (`1`)<br>**Telnet** (`2`) |
| Mode verbeux | `verbose` | Active ou désactive les messages de débogage verbeux (ne pas désactiver sauf si conseillé) | **On**  (`1`)<br>**Off** (`0`) |
| Mode données brutes | `monitor` | Active ou désactive le mode données brutes (ne pas activer sauf si conseillé) | **On**  (`1`)<br>**Off** (`0`) |
| Afficher les paramètres inconnus | `show_unknown` | Essaye d'afficher aussi les paramètres non pris en charge par l'appareil de destination | **On** (`true`)<br>**Off** (`false`) |

---

## Adressage de différents régulateurs de chauffage

Pour adresser des paramètres à partir d'appareils autres que l'appareil de destination par défaut dans l'interface Web, tu dois ajouter un point d'exclamation suivi de l'adresse de l'appareil (voir ci-dessus pour la conversion de la notation segment/appareil en adresse d'appareil).  
Par exemple, le paramètre 8700 de l'adresse d'appareil 1 serait écrit comme `8700!1` au lieu de simplement `8700`.

Dans le fichier de configuration, les paramètres sont répertoriés sous la forme `{numéro de paramètre, adresse de destination}`. Le paramètre 8700 de l'adresse d'appareil 1 serait donc écrit comme `{8700, 1}`. Pour adresser la destination par défaut, utilise `-1`.