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
Au départ, seul un nombre limité d'options de configuration sont affichées dans l'interface web. Pour accéder à l'ensemble des paramètres, tu dois définir l'option "extended configuration" sur "on".

---
## Aperçu des options de configuration

### Paramètres généraux
|Interface Web|Fichier de configuration|Fonctionnalité|Paramètres possibles|
|-------------|------------------------|--------------|--------------------|
|-            |`#define LANG`          |Définir la langue|`DE`, `EN`, `FR` et autres codes de pays ISO|
|Afficher la configuration étendue|-   |Afficher toutes les options de configuration|**On**<br>**Off**|
|Lire la configuration depuis l'EEPROM|`UseEEPROM`|Lire la configuration depuis l'EEPROM ou le fichier|**On** (`1`)<br>**Off** (`0`)|
|Niveau d'accès en écriture|-          |Si `DEFAULT_FLAG` est défini sur `FL_SW_CTL_RONLY`, définir le niveau d'accès en écriture ici.|**Off** (lecture seule)<br>**On (Standard)**<br>**On (Complet)**|
|Vérifier les mises à jour|`enable_version_check`|Interroger le serveur BSB-LAN pour une nouvelle version disponible|**On** (`true`)|
|Mise à jour OTA|`enable_ota_update`   |Activer la mise à jour OTA (Over-The-Air)|**On** (`true`)|
|Économie d'énergie|`esp32_save_energy`|Réduit la vitesse, économise l'énergie. Ne pas activer lors de l'utilisation du Wi-Fi.|**On** (`true`)<br>**Off** (`false`)|                        |

### Paramètres de bus
|Interface Web|Fichier de configuration|Fonctionnalité|Paramètres possibles|
|-------------|------------------------|--------------|--------------------|
|Type de bus  |`bus_type`              |Type de bus (BSB/LPB/PPS)|**BSB** (`0`)<br>**LPB** (`1`)<br>**PPS** (`2`)|

### Paramètres réseau
|Interface Web|Fichier de configuration|Fonctionnalité|Paramètres possibles         |
|-------------|------------------------|--------------|-----------------------------|
|Nom du réseau WLAN|`wifi_ssid`        |Définir le nom du réseau WLAN|**Your_WLAN_name** (`Your_WLAN_name`)|
|Mot de passe WLAN|`wifi_pass`         |Définir le mot de passe du WLAN|**YourWLANpassword** (`YourWLANpassword`)|
|Utilisation du DHCP|`use_dhcp`        |Définir si oui ou non utiliser DHCP|**On** (`true`)<br>**Off** (`false`)|