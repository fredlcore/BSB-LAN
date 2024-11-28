# ChangeLog #

## Current Master ##

- **ATTENTION : CHANGEMENT CASSANT !** Structure de sujet rationalisée pour MQTT. La nouvelle structure ajoute `/status` pour interroger un paramètre, `/set` pour définir un paramètre, `/inf` pour envoyer des données sous la forme d'un télégramme INF et `/poll` pour forcer BSB-LAN à envoyer une mise à jour de la valeur du paramètre au courtier. Si vous utilisez la découverte automatique MQTT, idéalement, l'appel de `/M1` devrait mettre à jour ces changements. Cependant, si vous utilisez vos propres configurations, vous devrez apporter des ajustements ici.
- **ATTENTION : CHANGEMENT CASSANT !** Lorsque vous utilisez des paramètres JSON pour MQTT, auparavant, tous les messages étaient écrits dans `BSB-LAN/json` et donc fondamentalement immédiatement remplacés lorsque plusieurs paramètres étaient enregistrés. Ce paramètre détermine désormais uniquement le format (et non le format et le sujet) des données qui sont écrites dans `/status` de chaque paramètre. Pour la découverte automatique, le texte brut reste le seul choix valide.
- **ATTENTION : CHANGEMENT CASSANT** Le message d'accusé de réception envoyé par BSB-LAN au sujet `MQTT` a été supprimé. Au lieu de cela, la QoS pour la publication des messages a été définie au niveau 1.
- **ATTENTION : CHANGEMENT CASSANT :** Les valeurs de configuration du journal ont changé. Cependant, seuls les utilisateurs qui se sont connectés à UDP sont concernés et devront ajuster leurs paramètres.
- Ajout d'un paramètre pour publier uniquement les paramètres de journalisation sur MQTT. Les mises à jour MQTT forcées via le sujet `/poll` sont toujours possibles.
- Ajout de state_class pour les capteurs non cumulatifs dans la découverte automatique MQTT
- Mise à jour de l'émulation de l'unité de pièce dans `custom_functions` pour fonctionner avec la version 4.x.
- Correction d'un bogue pour VT_ENERGY, ajout de nouveaux types de données VT_ENERGY10 et VT_ENERGY10_N

## Version 4.1 ##
**06.11.2024**

- **ATTENTION : CHANGEMENT CASSANT !** Structure de sujet modifiée pour MQTT. Cela signifie que toutes les entités MQTT existantes dans votre système de domotique devront être ajustées ou recréées ! La nouvelle structure est désormais `BSB-LAN/<device id>/<category id>/<parameter number>`.
- **ATTENTION : CHANGEMENT CASSANT !** L'identifiant unique pour la découverte automatique MQTT a été modifié. Cela signifie que toutes les entités MQTT qui ont été créées via la découverte automatique devront être recréées !
- **ATTENTION :** Les options de configuration `fixed_device_family` et `fixed_device_variant` ont été supprimées car elles ne fonctionnent plus pour les listes de paramètres spécifiques aux appareils. Si votre système de chauffage est éteint lorsque vous allumez le microcontrôleur, BSB-LAN essaiera d'obtenir les détails toutes les 60 secondes.
- **ATTENTION :** Le changement des options de configuration entraîne une nouvelle disposition de l'EEPROM, l'EEPROM sera donc réinitialisée en fonction de la configuration de `BSB_LAN_config.h`.
- La découverte automatique MQTT fonctionne désormais pour tous les appareils, et pas seulement pour l'ID d'appareil 0. Utilisez `/M1!<x>` ou `/M0!<x>` pour créer/supprimer des entités pour l'ID d'appareil `<x>`.
- Le drapeau des messages de découverte automatique MQTT a été modifié en "retain" afin que les paramètres restent disponibles après le redémarrage de Home Assistant.

## Version 4.0 ##
**01.11.2024**

- **ATTENTION : CHANGEMENT CASSANT !** Le paramètre de température de la pièce 10000, 10001 et 10002 doit désormais avoir le drapeau supplémentaire `FL_SPECIAL_INF`, sinon la température de consigne ne fonctionnera pas !
- **ATTENTION : CHANGEMENT CASSANT !** Le paramètre de simulation de la température extérieure 10017 doit avoir le drapeau `FL_SPECIAL_INF` supprimé, sinon la température de consigne ne fonctionnera pas !
- **ATTENTION : CHANGEMENT CASSANT !** Le paramètre de température de la pièce 10000, 10001 et 10002 pour les appareils de chauffage Weishaupt (familles d'appareils 49, 50, 51 et 59) doit désormais avoir le drapeau `FL_SPECIAL_INF` supprimé, sinon la température de consigne ne fonctionnera pas !
- **ATTENTION : CHANGEMENT CASSANT !** Les commandes d'URL `/U` (afficher les variables définies par l'utilisateur) et `/X` (afficher les valeurs MAX !) ont été supprimées car ces valeurs peuvent désormais être accessibles via les paramètres 20000++
- **ATTENTION : CHANGEMENT CASSANT !** Les paramètres du programme horaire PPS (15050-15091) ont été rationalisés avec les paramètres du programme horaire BSB/LPB, ce qui a permis d'obtenir un seul paramètre par jour (au lieu de six), couvrant trois points de commutation (début et fin) par paramètre.
- **ATTENTION :** Pour ESP32, BSB-LAN nécessite la version 3.0.x du framework ESP32 - veuillez rechercher les erreurs ou les comportements étranges (les capteurs 1-Wire n'ont pas encore été testés) ainsi que tout autre type de comportement étrange/plantages.
- **ATTENTION :** Nouvelles options de configuration dans `BSB_LAN_config.h` - veuillez mettre à jour vos fichiers de configuration existants ! La configuration basée sur le Web sera écrasée par les paramètres du fichier de configuration en raison d'un changement dans la disposition de l'EEPROM !
- **ATTENTION :** Nouveau manuel d'utilisation : https://docs.bsb-lan.de/
- Les boutons et `RGT_EMULATION` ont été déplacés du code principal vers la bibliothèque `custom_functions`. Pour continuer à les utiliser, utilisez les fichiers `BSB_LAN_custom_*.h` et activez la définition `CUSTOM_COMMANDS`.
- La plupart des définitions de configuration ont été supprimées de `BSB_LAN_config.h`. Presque toutes les fonctionnalités peuvent désormais être configurées sans reflash.
- BSB-LAN prend désormais en charge la découverte automatique MQTT (prise en charge, par exemple, par Home Assistant). Pour créer des appareils, appelez la commande d'URL `/M1`, pour les supprimer, appelez `/M0`
- **ATTENTION :** La découverte automatique MQTT crée un commutateur général pour l'appareil BSB-LAN dans Home Assistant. Ce commutateur écrira immédiatement toutes les valeurs de paramètre stockées dans Home Assistant. N'UTILISEZ PAS CE COMMUTATEUR à moins de SAVOIR EXACTEMENT ce qu'il fait !
- Le bouton "Set" dans l'interface Web fonctionne désormais également avec les appareils de destination non par défaut (c'est-à-dire 1 au lieu de 0)
- Les paramètres interrogés/définis sont désormais transférés au courtier MQTT (si MQTT est activé)
- Les commandes `/M1` et `/M0` précédemment utilisées pour activer/désactiver la fonction de surveillance ont été supprimées car elles peuvent désormais être accessibles via la configuration dans l'interface Web.
- La liste des catégories avec `/K` fonctionne désormais également avec l'appareil de destination (par exemple, /K!1 pour l'appareil de destination 1, la valeur par défaut est 0).
- Correction d'un bogue important pour la mise à jour OTA : les versions précédentes avaient une limite stricte sur la taille du fichier que les systèmes de chauffage plus récents avec plusieurs centaines de paramètres ont atteinte, de sorte qu'aucune mise à jour OTA n'était possible. Ceci est maintenant corrigé, mais les utilisateurs concernés devront effectuer une mise à jour USB une fois de plus.
- Les capteurs 1-Wire et DHT sont désormais désactivés avec la valeur -1 au lieu de 0. Dans l'interface Web, un champ vide est également accepté.
- MQTTTopicPrefix n'est plus facultatif, le sujet "fromBroker" a été supprimé (anciennement utilisé pour envoyer des commandes à BSB-LAN via MQTT)
- L'utilisation de la fonctionnalité des moyennes sur 24 heures ne nécessite plus l'utilisation d'une carte SD. La carte SD ne sera utilisée que pour stocker les moyennes si la journalisation des intervalles sur la carte SD est active.
- Nouvelle variante d'unité de pièce PPS pour RVD130, qui augmente le nibble supérieur du byte magique à chaque transaction.
- L'interrogation de l'heure actuelle auprès d'un serveur NTP est active par défaut. La désactiver en définissant `ntp_server` sur une chaîne vide.
- Nouveau drapeau de paramètre `FL_NOSWAP_QUR` pour les paramètres qui n'échangent pas les deux premiers octets de l'ID de commande dans le télégramme QUR
- Nouveau drapeau de paramètre `FL_FORCE_INF` pour les paramètres dont nous sommes certains qu'ils ne fonctionnent qu'avec INF (tels que la température de la pièce). Forcera un télégramme INF même si `/S` est utilisé pour définir le paramètre (permet de définir la température de la pièce via l'interface Web)
- Filigrane du logo BSB-LAN dans l'affichage du graphique du journal (DE-cr)
- Les ENUM binaires (oui/non, on/off, etc.) renvoient désormais soit 0 soit 1 lorsqu'ils sont interrogés, et non - comme c'est le cas avec certains systèmes de chauffage - 0 ou 255. La définition de toute valeur de 1 à 255 est toujours possible.
- Correction d'un bogue critique dans PPS qui empêchait son exécution correcte en mode unité active/pièce.
- Correction d'un bogue (ou, selon le point de vue, réduction de la sécurité) qui empêchait l'émission de commandes via la console série/Telnet lorsque l'authentification HTTP était active
- Diverses corrections de bugs, notamment la journalisation des télégrammes de bus sur le périphérique de stockage.
- Nouvelle version de la bibliothèque OneWireNg
- Cette version a été soutenue par les sponsors suivants : Erich Scheilko

## Version 3.3 ##
**12.03.2024**

- **ATTENTION :** Nouvelles options de configuration dans `BSB_LAN_config.h` - veuillez mettre à jour vos fichiers de configuration existants !
- ESP32 : prise en charge de la réception de la date et de l'heure via NTP au lieu de les obtenir à partir du chauffage.
- Le paramètre du courtier MQTT accepte désormais les noms de domaine ainsi que les adresses IP. Un port facultatif peut être ajouté après un deux-points, par exemple broker.my-domain.com:1884. Sinon, la valeur par défaut est 1883.
- ESP32 NodeMCU : prise en charge d'un adaptateur de carte SD supplémentaire facultatif. Les broches SPI peuvent être configurées dans `BSB_LAN_config.h`, par défaut sur les broches SPI standard 5, 18, 19 et 23.
- ESP32 : Le passage d'un périphérique de stockage de journal (carte SD/flash interne) à un autre peut désormais être effectué dans l'interface Web.
- ESP32 : Créer un point d'accès WiFi temporaire en cas de défaillance de la connexion Ethernet
- ESP32 NodeMCU : La broche de réinitialisation de l'EEPROM est passée de 18 à 21 pour éviter les collisions avec les adaptateurs de carte SD SPI.
- Cette version a été soutenue par les sponsors GitHub suivants : jsimon3

## Version 3.2 ##
**15.11.2023**

- **ATTENTION :** Dans `BSB_LAN_config.h`, la nouvelle disposition de `log_parameters`, `avg_parameters` et `ipwe_parameters` est désormais écrite entre accolades et de taille différente (40 au lieu de 80) et de type (`parameter` au lieu de `float`). Veuillez mettre à jour votre `BSB_LAN_config.h` en conséquence pour éviter les erreurs !
- Ajout de vérifications de version de fichier de configuration pour empêcher l'utilisation de fichiers de configuration obsolètes avec de nouvelles versions logicielles.
- La variable `esp32_save_energy` est désormais définie par défaut sur false car elle ne semble avoir de sens que lorsque l'on utilise une connexion LAN ou si l'on utilise le WiFi et que l'on peut vivre avec l'impact sur les performances.
- Ajout du dossier `custom_functions` où seront collectés des exemples de code pour des fonctions utiles qui sont néanmoins trop spécifiques pour être ajoutées au code principal de BSB-LAN.
- Ajout d'un exemple de fonction personnalisée pour la cartographie des capteurs DS18B20 sur des paramètres de nombres à virgule flottante personnalisés
- Cette version a été soutenue par les sponsors GitHub suivants : BraweProg, fdobrovolny, Harald

## Version 3.1 ##
**04.06.2023**

- **ATTENTION :** Pour les appareils ESP32 utilisant la flash interne pour le stockage des journaux : le système de fichiers est passé de SPIFFS à LittleFS. Téléchargez les données de journal importantes avant de mettre à jour !
- **ATTENTION :** Dans `BSB_LAN_config.h`, la structure de `log_parameters`, `avg_parameters` et `ipwe_parameters` a changé et inclut désormais l'appareil de destination sur le bus !
- **ATTENTION :** Le nouveau schéma d'EEPROM peut entraîner la perte des paramètres de configuration Web lors de la mise à jour. Notez vos paramètres avant de mettre à jour !
- **ATTENTION :** Nouvelle variable `esp32_save_energy` dans `BSB_LAN_config.h` - mettez à jour avant de compiler la nouvelle version.
- **ATTENTION :** Nouvelle variable bssid dans `BSB_LAN_config.h` - définit une adresse BSSID fixe à laquelle se connecter lors de l'utilisation du WiFi sur ESP32.
- Les paramètres peuvent désormais être interrogés à partir d'autres appareils sur le bus à l'aide de la notation ! également lors de la journalisation (y compris MQTT) ou lors de l'utilisation de paramètres de moyenne ou de IPWE
- Activer/désactiver l'économie d'énergie sur ESP32. Économise 20 % d'énergie, mais peut avoir un impact sur la portée WiFi et la vitesse de téléchargement des fichiers de journal lorsque vous utilisez le WiFi (LAN non affecté)
- Amélioration des performances et de l'utilisation de la mémoire flash sur les appareils ESP32 utilisant la flash interne pour la journalisation grâce au passage de SPIFFS à LittleFS
- Pour améliorer la gestion des grands journaux de données : sélection de la plage de dates dans `/DG`, nouvelles commandes d'URL `/Da,b`, `/DA`, `/DB`, `/Dn`, `/DI` et `/DKn`
- Cette version a été soutenue par les sponsors GitHub suivants : lapixo, nrobadey

## Version 3.0 ##
**16.03.2023**

- **ATTENTION :** `BSB_LAN_custom_defs.h`.default doit être renommé en `BSB_LAN_custom_defs.h` et ne contient qu'un ensemble très limité de paramètres par défaut. Consultez le manuel pour obtenir des listes de paramètres spécifiques aux appareils.
- Ajouter la nouvelle commande d'URL `/LN` pour forcer la journalisation indépendamment de l'intervalle actuel.
- Amélioration des vérifications de la bibliothèque : les utilisateurs d'ESP32 n'ont plus besoin de supprimer les dossiers ArduinoMDNS et WiFiSpi.
- Nouvelle version de SdFat 2 pour Arduino Due
- Nouveau type de données `VT_BINARY_ENUM`
- Cette version a été soutenue par les sponsors GitHub suivants : Alex, DE-cr

## Version 2.2 ##
**01.11.2022**

- **ATTENTION :** Plusieurs variables dans `BSB_LAN_config.h`.default ont changé de type de variable, il est probablement préférable de recréer votre `BSB_LAN_config.h` à partir de zéro.
- Les numéros de paramètre sont désormais à virgule flottante (c'est-à-dire XXXX.Y) car certains paramètres contiennent deux types d'informations différents. Ils sont désormais affichés par incréments décimaux de 0,1. Vous pouvez toujours interroger le paramètre "principal" via XXXX (sans .Y)
- De nombreux correctifs de bugs et de nouveaux types de données
- Les listes de paramètres spécifiques aux appareils sont prises en charge

## Version 2.1 ##
**30.07.2022**

- De nombreux nouveaux paramètres pour LMU64
- **ATTENTION :** Nouvelles catégories pour les contrôleurs LMU64 et RVD/RVP en raison de leurs systèmes de numérotation différents. Ils seront remplis au fil du temps. Les catégories PPS et capteurs ont été déplacées de deux positions.
- ESP32 : OTA utilise désormais les informations d'identification d'authentification HTTP système-wide
- Amélioration de l'affichage intégré des graphiques `/DG`, nouvelle définition de configuration `#define USE_ADVANCED_PLOT_LOG_FILE` - grâce à Christian Ramharter
- Ajout d'une journalisation facultative via la diffusion
- Si BSB-LAN ne parvient pas à se connecter au Wi-Fi sur ESP32, il configurera son propre point d'accès « BSB-LAN » avec le mot de passe « BSB-LPB-PPS-LAN » pendant 30 minutes. Après cela, il redémarrera et tentera de se reconnecter.
- Nouvelles fonctions MQTT, y compris la possibilité de définir n'importe quel paramètre par un message MQTT et d'interroger activement n'importe quel paramètre une fois en envoyant un message MQTT.
- Prise en charge ajoutée pour les capteurs BME280.
- Définition d'une adresse de destination temporaire pour l'interrogation des paramètres en ajoutant « !x » (où « x » est l'ID de destination), par exemple « /6224!10 » pour interroger l'identification de l'unité d'affichage.
- Les commandes URL « /A », « /B », « /T » et « /JA » ont été supprimées car tous les capteurs peuvent désormais être accessibles via les numéros de paramètre 20 000 et plus, ainsi que (actuellement) sous la nouvelle catégorie K49.
- De nouvelles catégories ont été ajoutées, les catégories suivantes ont été décalées vers le haut.
- L'authentification HTTP utilise désormais un nom d'utilisateur et un mot de passe en texte clair dans la configuration.
- Les utilisateurs de PPS peuvent désormais envoyer l'heure et le jour de la semaine au chauffage.
- De nombreux nouveaux paramètres ont été ajoutés.
- La commande URL « /JR » permet d'interroger la valeur standard (réinitialisée) d'un paramètre au format JSON.
- La commande URL « /JB » permet de sauvegarder les paramètres dans un fichier JSON.
- La nouvelle bibliothèque pour DHT22 devrait fournir des résultats plus fiables.
- Types de données et de valeurs consolidés: nouveaux types de données « VT_YEAR », « VT_DAYMONTH » et « VT_TIME » en tant que sous-ensembles de « VT_DATETIME » pour les paramètres 1-3, en remplaçant « VT_SUMMERPERIOD » et en ajustant « VT_VACATIONPROG ». Nouveaux types de valeurs « DT_THMS » pour l'heure composée de heures:minutes:secondes.
- MQTT: utilisez « MQTTDeviceID » comme ID client pour le courtier, qui par défaut est toujours « BSB-LAN ». ATTENTION: Vérifiez votre configuration si votre courtier dépend de l'ID client de quelque manière que ce soit pour l'autorisation, etc.

## Version 1.1 ##
**10.11.2020**

- **ATTENTION:** le paramètre Push ECS (« Trinkwasser Push ») a dû être déplacé de 1601 à 1603 car 1601 a une signification « officielle » différente sur certains appareils de chauffage. Veuillez vérifier et modifier votre configuration si nécessaire.
- **ATTENTION:** de nouvelles catégories ont été ajoutées, la plupart des numéros de catégorie (en utilisant « /K ») seront décalés de quelques numéros.
- La commande URL « /JA » affiche les valeurs moyennes.
- De nombreux nouveaux paramètres décodés.
- Nouveaux paramètres pour les familles d'appareils 25, 44, 51, 59, 68, 85, 88, 90, 96, 97, 108, 134, 162, 163, 170, 195, 209, 211.
- Amélioration de l'affichage mobile de l'interface Web.
- Ajout de la définition « BtSerial » pour détourner la sortie série vers Serial2 où un adaptateur Bluetooth peut être connecté (5V->5V, GND->GND, RX->TX2, TX->RX2). L'adaptateur doit être en mode esclave et configuré à 115 200 bps, 8N1.
- De nombreuses traductions polonaises ajoutées.
- Nouveaux types de données « VT_BYTE10 » et « VT_SPF ».
- Correction d'un bogue concernant l'affichage des programmes de temps de chauffage sur le bus PPS.
- Correction d'un bogue MQTT.

## Version 1.0 ##
**03.08.2020**

- La commande URL « /JI » affiche la configuration au format JSON.
- La commande URL « /JC » obtient la liste des valeurs possibles à partir d'une liste de fonctions définies par l'utilisateur.
  Exemple: « /JC=505,700,701,702,711,1600,1602 ».
- Les télégrammes de journalisation (paramètre de journalisation 30 000) écrivent désormais dans un fichier séparé (« journal.txt »). Il peut être réinitialisé avec la commande « /D0 » (en même temps que datalog.txt) et vidé avec la commande « /DJ ».
- La configuration Wi-Fi a été supprimée car elle n'est plus applicable pour le Due.
- De nombreux nouveaux paramètres pour diverses familles d'appareils.
- Optimisation et restructuration du code, augmentation générale de la vitesse.
- Nouveaux schémas pour la disposition de la carte V3.
- De nombreux bogues corrigés.

## Version 0.44 ##
**11.05.2020**

- Ajout de la fonctionnalité de serveur Web via une carte SD et diverses autres améliorations de l'utilisateur GitHub dukess.
- Ajout d'une sortie JSON pour MQTT.
- Interface Web plus conviviale pour les appareils mobiles.
- Plus de paramètres et de familles d'appareils.
- Dernière version entièrement testée sur Mega 2560. Les futures versions pourront toujours s'exécuter sur la Mega, mais ne seront testées que sur l'Arduino Due.

## Version 0.43 ##
**20.02.2020**

- Prise en charge ajoutée pour HardwareSerial (Serial1) connexion de l'adaptateur. Utilisez l'épingle RX 19 dans la définition du bus pour l'activer. Consultez le manuel/forum pour plus de détails matériels.
- Ajout de la définition DebugTelnet pour détourner la sortie série vers un client Telnet (port 23, sans mot de passe) dans « BSB_LAN_config.h ».
- Ajout de la possibilité de contrôler BSB-LAN (presque) complètement via le port série USB. La plupart des commandes sont prises en charge comme leurs homologues URL, c'est-à-dire « /<passcode>/xxx » pour interroger le paramètre xxx ou « /<passcode>/N » pour redémarrer l'Arduino.
- Changement de l'ID d'appareil par défaut de 6 (contrôleur de pièce « RGT1 ») à l'ID inutilisé 66 (« LAN »).
- De nombreux nouveaux paramètres, exécutez « /Q » pour voir les éventuels changements pour votre famille d'appareils et nous faire un rapport!
- Ajout de variables globales (tableaux de 20 octets) « custom_floats[] » et « custom_longs[] » pour une utilisation avec « BSB_LAN_custom.h », par exemple pour lire des capteurs, etc.
  La sortie de ces variables se fait via la nouvelle commande URL « /U ».
- Ajout des familles d'appareils 23 et 29 (chaudières Grünenwald).
- Ajout des familles d'appareils 49, 52, 59 (chaudières Weishaupt).
- Ajout des familles d'appareils 91, 92, 94, 118, 133, 136, 137, 165, 184, 188 (divers contrôleurs tels que QAA75 ou AVS37).
- Ajout de la famille d'appareils 171 (système de granulés de bois Bösch).
- Ajout de la famille d'appareils 172 (SensoTherm BLW Split B (RVS21.826F/200)).
- Ajout des familles d'appareils 186 et 164 (Olymp WHS-500).
- Ajout de la variante 2 de la famille d'appareils 195 (Thision 19 Plus / LMS14.111B109).
- Inclusion des paramètres DHT, 1Wire et de l'état du brûleur (>20000) dans MQTT.
- L'anglais est maintenant la langue par défaut.
- Mise à jour de diverses traductions.
- Ajout de fichiers STL pour imprimer un boîtier avec une imprimante 3D (grâce à l'utilisateur FHEM EPo!).
- Déplacement de tous les capteurs vers « /T », « /H » n'est plus utilisé.
- Nouveaux paramètres virtuels 702/703 pour le contrôleur de pièce Weishaupt.
- Nouveau paramètre virtuel 10003 pour définir la température extérieure sur les systèmes plus récents.
- Ajout de descriptions de texte pour les phases d'erreur (6706 et suivantes).
- « /Q » est maintenant plus complet.
- Nouveaux types de données « VT_CUSTOM_ENUM » et « VT_CUSTOM_BYTE » pour extraire des informations de télégrammes non standard (tels que 702/703).
- Correction d'un bogue: implémentation DHCP (Ethernet).

## Version 0.42 ##
**21.03.2019**

- Ajout de la localisation! Vous pouvez maintenant aider à traduire BSB-LAN dans votre langue! Il vous suffit de copier l'un des fichiers de langue du dossier de localisation (« LANG_DE.h » est le plus complet) et de traduire ce que vous pouvez. Les éléments non traduits seront affichés en allemand.
  Attention: la définition de la langue dans « BSB_LAN_config.h » est désormais « #define LANG <ISO-CODE> ».
  Par exemple: « #define LANG DE ».
- Ajout d'une exportation vers un courtier MQTT, utilisez « log_parameters »[] dans « BSB_LAN_config.h » pour définir les paramètres et activer la définition « MQTTBrokerIP ».
- Ajout de la prise en charge des modules Wi-Fi tels qu'un ESP8266 ou un Wemos Mega connecté à Serial3 (RX:15/TX:14) de l'Arduino.
  L'ESP8266 doit être flashé avec le microprogramme AT d'Espressif pour fonctionner.
  Veuillez noter que le Wi-Fi via la série est, par conception, beaucoup plus lent (seulement 115 kpbs) que les connexions TCP/IP « pures ».
- Ajout d'une nouvelle catégorie « 34 - Konfiguration / Erweiterungsmodule ». Toutes les catégories suivantes se déplacent d'un numéro vers le haut!
- De nombreux nouveaux paramètres provenant de la famille d'appareils 123, exécutez « /Q » pour voir si certains paramètres fonctionnent également pour votre appareil de chauffage!
- De nombreux nouveaux paramètres encore inconnus via une interrogation par force brute :) (numéros de paramètre 10200 et plus).
- Ajout de nouvelles commandes PPS-Bus, déplacement des numéros de paramètre à 15000 et plus.
- Le mode PPS par défaut est désormais « écoute ».
  Utilisez le troisième paramètre de la définition du bus pour passer de l'écoute à la commande, 1 pour la commande, tout le reste pour l'écoute,
  c'est-à-dire que BSB bus(68,67,1) envoie des données à la chaudière, BSB bus(68,67) ne reçoit que des données de la chaudière/du contrôleur de pièce.
  Vous pouvez passer d'un mode à l'autre à l'exécution avec la commande URL « /P2,x » où x est soit 1 (pour la commande) soit autre chose que 1 (pour l'écoute uniquement).
- Correction d'un bogue qui a provoqué le plantage des requêtes de bus PPS.
- Améliorations de la stabilité pour le bus PPS.
- Amélioration de la légende du graphique lors de la représentation de plusieurs paramètres.
- Ajout d'une exportation JSON; interroger avec « /JQ=a,b,c,d... » ou pousser des requêtes vers « /JQ » ou pousser des commandes set vers « /JS ».
- La journalisation des paramètres MAX! est désormais possible avec le paramètre de journalisation 20007.
- Ajout de la famille d'appareils Waterstage WP (119).
- Ajout de la famille d'appareils WHG Procon (195).
- Ajout de l'unité au fichier journal ainsi qu'à la sortie moyenne.
- Réécriture de l'appariement des appareils dans « cmd_tbl » pour prendre en charge également la variante de l'appareil (Gerätevariante). Exécutez « /Q » pour voir si la transition a fonctionné pour votre appareil!
- Ajout de « BSB_LAN_custom_setup.h » et « BSB_LAN_custom_global.h » pour vous permettre d'ajouter du code individuel (meilleur utilisé en conjonction avec « BSB_LAN_custom.h »).
- Tous les paramètres (connus) OEM ont été marqués avec le drapeau « FL_OEM ». Les paramètres OEM sont par défaut en lecture seule. Pour les rendre accessibles en écriture, changez « FL_OEM » de 5 à 4 dans « BSB_LAN_defs.h ».
- Amélioration des performances pour l'interrogation de plusieurs paramètres à la fois (similaire à la requête de catégorie).
- Ajout d'une option de configuration pour définir le sous-réseau.
- « /Q » n'a plus besoin de « #define DEBUG ».
- Correction d'un bogue d'adressage de mémoire ENUM.
- Correction d'un bogue dans la fonction de réinitialisation « /N », effacement de l'EEPROM pendant la réinitialisation avec « /NE ».
- Ajout de favicon.ico.
- Division de cmdtbl en cmdtbl1 et cmdtbl2 en raison de la limite de taille de struct de 32 Ko d'Arduino, ce qui libère de l'espace pour de nouveaux paramètres.

## Version 0.41 ##
**17.03.2019**

- Version intermédiaire contenant tous les changements de la version 0.42 ci-dessus, à l'exception de la localisation, c'est-à-dire que tous les fragments de texte font toujours partie du code principal.

## Version 0.40 ##
**21.01.2018**

- Mise en œuvre de l'interrogation des thermostats de chauffage MAX!, affichage avec la commande URL « /X ».
  Voir « BSB_LAN_custom.h » pour un exemple d'envoi de la température moyenne de la pièce au système de chauffage.
- Ajout d'une nouvelle catégorie « 22 - Energiezähler » - veuillez noter que toutes les catégories suivantes se déplacent d'un cran vers le haut!
- Nouveau paramètre virtuel 1601 (poussée TWW manuelle).
- Ajout de la famille d'appareils Fujitsu Waterstage WSYP100DG6 (211).
- Ajout de la famille d'appareils CTC (103).
- Nouvelle définition « #define TRUSTED_IP2 » pour accorder l'accès à une deuxième adresse IP locale.
- Ajout d'une définition facultative « #define GatewayIP » dans « BSB_LAN_config.h » pour activer la définition de l'adresse du routeur différente de x.x.x.1.
- Suppression du paramètre 10109 car il est identique à 10000.
- Ajout d'une fonction pour vérifier tous les CommandIDs connus sur votre propre système de chauffage. Utilisez « /Q » après avoir activé la définition « #define DEBUG » dans « BSB_LAN_config.h ».
- Ajout de numéros de paramètre au menu de catégorie.
- Mise à jour de analyze.sh.
- espérons que cela résout le problème de mémoire
- Déplacement des chaînes HTML vers « html_strings.h ».

## Version 0.39 ##
**02.01.2018**

- Implémentation du protocole PPS-Bus.
  Voir « /K40 » pour les commandes limitées disponibles pour ce bus.
  Utilisez setBusType(2) pour définir le PPS au démarrage ou « /P2 » pour basculer temporairement.
- Définissez les GPIOs en entrée en utilisant « /Gxx,I ».
- Définition « #define CUSTOM_COMMANDS » ajoutée.
  Utilisez ceci dans votre configuration pour inclure du code individuel de « BSB_LAN_custom.h »
  (doit être créé par vous!) qui est exécuté à la fin de chaque boucle principale.
  Les variables « custom_timer » et « custom_timer_compare » ont été ajoutées pour exécuter
  du code à des intervalles arbitraires.
- Ajout de la famille d'appareils LogoBloc Unit L-UB 25C (95).
- plusieurs nouveaux paramètres ajoutés.
- Correction d'un bogue pour la journal
## Version 0.34 ##
**29.05.2017**

- Les données de journalisation peuvent maintenant être affichées sous forme de graphique.
- L'interface Web peut maintenant afficher et définir les paramètres de type `VT_BIT` sous une forme lisible par l'utilisateur.
- Ajout de descriptions KonfigRGx ; attention : plusieurs sources ont été utilisées, il n'est pas garanti que les descriptions correspondent à votre système de chauffage individuel.
- `VT_BIT` est généralement en lecture seule dans l'interface Web. Pour le définir, utilisez la commande d'URL `/S` avec la représentation décimale de la valeur.
- Correction d'un bug avec `VT_SECONDS_SHORT5`, qui affecte les paramètres 9500 et 9540.
- Correction d'un bug concernant la famille d'appareils Fujitsu (de 127 à 170).
- Déplacement des bibliothèques du dossier `libraries` vers `src` afin qu'elles puissent être incluses sans les copier dans le dossier `Arduino libraries`.
- Modification du chemin d'inclusion de `DallasTemperature.h` pour `OneWire.h`.

## Version 0.33 ##
**09.05.2017**

- Plus de définitions de systèmes de chauffage en raison de la nouvelle fonction d'auto-détection basée sur la famille d'appareils (paramètre 6225), ou définissez la variable `device_id` directement sur la valeur du paramètre.
- Deux options de sécurité supplémentaires : `TRUSTED_IP` pour limiter l'accès à une seule adresse IP, et l'authentification HTTP avec nom d'utilisateur et mot de passe.
- Les valeurs moyennes sont enregistrées sur la carte SD si elle est présente et que la définition LOGGER est activée.
- Désactiver la journalisation en définissant `/L0=0` - de cette façon, vous pouvez activer la définition LOGGER sans remplir la carte SD, mais toujours enregistrer les valeurs moyennes.
- Nouveaux codes d'erreur pour THISION.
- Ajout du vidage de la charge utile des données sur le site Web pour les commandes de type inconnu, les paramètres non pris en charge sont grisés.
- Activer la journalisation des télégrammes (paramètre de journalisation 30000) également en mode surveillance (bsb.cpp et bsb.h mis à jour).
- L'heure du système de chauffage est désormais récupérée périodiquement à partir des télégrammes de diffusion, ce qui réduit encore l'activité du bus.
- Nouveau type de données `VT_BIT` pour les paramètres qui définissent des bits individuels. Affichage sous forme de chiffres binaires, la définition utilise toujours la représentation décimale.
- Nouveau type de données `VT_TEMP_SHORT5_US` pour les températures non signées sur un octet divisées par 2 (pour l'instant, uniquement 887 Vorlaufsoll NormAussentemp).
- Nouveau type de données `VT_PERCENT5` pour les températures non signées sur un octet divisées par 2 (pour l'instant, uniquement 885 Pumpe-PWM Minimum).
- Nouveau type de données `VT_SECONDS_WORD5` pour les secondes sur deux octets divisées par 2 (pour l'instant, uniquement 2232, 9500 et 9540).
- Nouveau type de données `VT_SECONDS_SHORT4` pour les secondes sur un octet (signé ?) divisées par 4 (pour l'instant, uniquement 2235).
- Nouveau type de données `VT_SECONDS_SHORT5` pour les secondes sur un octet (signé ?) divisées par 5 (pour l'instant, uniquement 9500, 9540).
- Nouveau type de données `VT_SPEED2` pour les rpm sur deux octets (pour l'instant, uniquement 7050).
- Nettoyage de la fonction set() pour supprimer les cas de doublons apparents.
- Ajout de cas pour `VT_TEMP_WORD`, `VT_SECONDS_WORD5`, `VT_TEMP_SHORT`, `VT_TEMP_SHORT5`, `VT_SECONDS_SHORT4` à la fonction set().

## Version 0.32 ##
**18.04.2017**

- De nombreux nouveaux paramètres sont pris en charge.
- La nouvelle interface Web permet de contrôler le système de chauffage sans logiciel supplémentaire ou commandes URL cryptiques. Les commandes URL sont bien sûr toujours disponibles, il n'est donc pas nécessaire de changer quoi que ce soit lors de l'utilisation de FHEM, etc.
- L'interface Web en allemand est disponible avec la définition `LANG_DE`.
- Nouvelle commande URL `/LB=x` pour journaliser uniquement les messages de diffusion (x=1) ou tous les messages du bus (x=0).
- Nouvelle commande URL `/X` pour réinitialiser l'Arduino (il faut activer la définition RESET dans `BSB_LAN_config.h`).
- Nouveaux paramètres de journalisation 20002 et 20003 pour les temps et cycles de chargement de l'eau chaude.
- Déplacement des paramètres de journalisation DS18B20 de 20010-20019 à 20200-20299 et des paramètres de journalisation DHT22 de 20020-20029 à 20100-20199.
- Déplacement du paramètre de journalisation moyen de 20002 à 20004.
- Définition de nombreux paramètres en lecture seule car c'est ce qu'ils sont évidemment (K33-36).
- Diverses corrections de bugs.

## Version 0.31 ##
**10.04.2017**

- Augmentation du vidage du fichier journal par un facteur 5 / tant que nous avons encore de la mémoire, vous pouvez augmenter logbuflen de 100 à 1000 pour augmenter la vitesse de transfert d'environ 16 à 18 Ko/s.
- Ajustement de la surveillance de l'activité de la chaudière en fonction des messages de diffusion pour les systèmes Brötje.
- Suppression de la définition `PROGNR_5895` car jusqu'à présent, elle a seulement désactivé une définition ENUM.
- Suppression de la définition `PROGNR_6030` car le double ID de commande pouvait être résolu via les définitions BROETJE / non-BROETJE.
- Renommage de `BROETJE_SOB` en BROETJE pour permettre une distinction fine entre les différents cas BROETJE (par exemple 6800ff).
   Cela signifie que vous devez maintenant activer DEUX définitions lors de l'utilisation d'un système Brötje : la définition générale BROETJE ainsi que `BROETJE_SOB` ou `BROETJE_BSW`.
   Jetez un coup d'œil à votre journal série pour les paramètres 6800 afin de voir quels ID de commande correspondent à votre système et activez l'un des deux en conséquence.
- Changement de l'adressage 16 bits de la mémoire flash en 32 bits pour résoudre les problèmes de plantage dus à des tables PROGMEM de plus en plus grandes - nous avons maintenant beaucoup d'espace pour respirer à nouveau pour de nouveaux ID de commande :)
- Suppression du caractère de fin de chaîne \0 de plusieurs ENUMs qui a conduit à des listes ENUM incorrectes. Veuillez garder à l'esprit de ne pas terminer les ENUMs par un caractère de fin de chaîne \0 !

## Version 0.30 ##
**22.03.2017**

- La bibliothèque Time de Paul Stoffregen (https://github.com/PaulStoffregen/Time) est désormais requise et incluse dans le dossier de la bibliothèque.
- Ajout de la journalisation des données de télégramme brut sur la carte SD avec le paramètre de journalisation 30000. La journalisation des données de télégramme est affectée par les commandes `/V` et `/LU`.
- Ajout de la commande `/LU=x` pour journaliser uniquement les ID de commande connus (x=0) ou inconnus (x=1) lors de la journalisation des données de télégramme.
- Suppression de la définition `USE_BROADCAST`, les données de diffusion sont désormais toujours traitées.
- Nouvelles fonctions internes GetDateTime, TranslateAddr, TranslateType.

## Version 0.29 ##
**07.03.2017**

- Ajout de la commande `/C` pour afficher la configuration actuelle.
- Ajout de la commande `/L` pour configurer l'intervalle de journalisation et les paramètres.
- Ajout d'une option pour la commande `/A` pour définir les paramètres de moyenne sur 24 heures pendant l'exécution.
- Ajout d'un paramètre spécial 20002 pour la journalisation de la commande `/A` (moyennes sur 24 heures, n'a de sens que pour les longs intervalles de journalisation).
- Corrections de bugs pour la journalisation des capteurs DS18B20.

## Version 0.28 ##
**05.03.2017**

- Ajout de paramètres spéciaux 20000++ pour la journalisation sur carte SD des commandes `/B,` `/T` et `/H` (voir `BSB_LAN_config.h` pour des exemples).
- Ajout d'informations de version à l'interface Web `BSB_LAN`.

## Version 0.27 ##
**01.03.2017**

- Ajout d'un champ de date au fichier journal (nécessite l'envoi de l'heure exacte par le système de chauffage).
- `/D0` recrée le fichier datalog.txt avec l'en-tête de tableau.
- Ajout d'un champ "flags" à la structure de la table de commandes. Actuellement, seul `FL_RONLY` est pris en charge pour rendre un paramètre en lecture seule.
- Ajout de `DEFAULT_FLAG` dans la configuration. Par défaut à `NULL`, c'est-à-dire que tous les champs sont en lecture/écriture.
   La définition à `FL_RONLY` rend tous les paramètres en lecture seule, par exemple pour un niveau de sécurité supplémentaire.
   Les paramètres individuels peuvent être définis sur `NULL`/`FL_RONLY` pour rendre uniquement ces paramètres accessibles en écriture/lecture seule.

## Version 0.26 ##
**27.02.2017**

- Ajout de la fonctionnalité de journalisation sur carte micro SD, en utilisant l'emplacement de la carte SD du bouclier Ethernet w5100.
- Ajout de paramètres supplémentaires (par exemple 8009).

## Version 0.25 ##
**21.02.2017**

- Ajout de paramètres FUJITSU supplémentaires.

## Version 0.24 ##
**14.02.2017**

- Mise à jour du README avec les fonctions ajoutées.
- Ajout des traductions allemandes du FAQ et du README, gracieuseté d'Ulf Dieckmann.

## Version 0.23 ##
**12.02.2017**

- Correction de bugs mineurs.

## Version 0.22 ##
**07.02.2017**

- Ajout de paramètres FUJITSU supplémentaires.
- Implémentation (espérons-le) correcte des lectures `VT_VOLTAGE`.
- Corrections de bugs mineurs.

## Version 0.21 ##
**06.02.2017**

- Ajout de nombreux paramètres pour la pompe à chaleur Fujitsu, y compris la nouvelle directive `#define FUJITSU` pour activer ces paramètres en raison de numéros de paramètres différents.
- Corrections de bugs mineurs.

## Version 0.20 ##
**27.01.2017**

- Ajout de paramètres supplémentaires pour Feststoffkessel.
- Corrections de bugs mineurs.

## Version 0.19 ##
**01.01.2017**

- Ajout de la commande d'humidité `/H`, actuellement pour les capteurs DHT22.
- Ajout de la commande de moyenne sur 24 heures `/A`, définissez les paramètres dans `BSB_LAN_config.h`.
- Suppression des espaces blancs de fin des chaînes de menu.
- Correction de l'ID de commande 0x053D04A2 pour les chauffe-eau THISION.
- Inclusion de la bibliothèque DHT de Rob Tillaart car il existe plusieurs bibliothèques implémentant le protocole et celle-ci est utilisée dans le code pour sa capacité à adresser plusieurs capteurs avec un seul objet.
- Suppression du paramètre d'URL `/temp` car il est un doublon de `/T`.
- Inclusion d'une boucle pour afficher les capteurs DHT22 dans IPWE.
- Rendre la compilation des extensions IPWE optionnelle (`#define IPWE`).

## Version 0.18 ##
**22.12.2016**

- Séparation de la configuration dans `bsb_lan_config.h`.
- Séparation des définitions de commandes dans `bsb_lan_defs.h`.
- Changement des valeurs de retour GPIO de LOW/HIGH à 1/0.
- Réactivation et mise à jour d'IPWE (définissez les paramètres dans la configuration).
- Vérification des broches protégées lors de l'accès à GPIO (définissez dans la configuration).
- Ajout des schémas et des fichiers PCB dans un nouveau sous-dossier "schémas".

## Version 0.17a ##
**20.12.2016**

- Correction d'erreurs mineures.

## Version 0.17 ##
**20.12.2016**

- Fusion de v0.16 avec les modifications de l'utilisateur FHEM miwi.

## Version 0.16 ##
**20.11.2016**

- Suppression d'IPWE et de l'interface EthRly.
- Ajout de l'interface GPIO.
- Fusion des paramètres de J.Weber.
- Résolution des ID de commande en double.

## Version 0.15a ##
**25.07.2016**

- Regroupement des commandes d'un projet Python et de ce projet,
   fusion des deux versions, correction des erreurs évidentes.
   Insertion de valeurs numériques hypothétiques dans les définitions ENUM
   où les manuels Broetje documentaient uniquement les textes des messages.
- Ajout d'informations à partir de traces dans une installation Broetje avec
   un contrôleur ISR-SSR et une chaudière à mazout WOB 25C.

## Version 0.15 ##
**21.04.2016**

- Ajout de Solar et Pufferspeicher d'Elco Logon B & Logon B MM.

## Version 0.14 ##
**04.04.2016**

- Corrections de bugs mineurs pour Broetje SOB.
- Extension du traitement des diffusions (expérimental).

## Version 0.13 ##
**31.03.2016**

- Changement de la valeur de résistance dans le chemin de réception de 4k7 à 1k5.
- Ajout des valeurs 0x0f et 0x10 à Enum8005.
- Correction des chaînes pour Zeitprogramme.
- Ajout d'un délai d'attente pour l'envoi d'un message (1 seconde).
- Ajout de `/T` pour interroger les capteurs de température One Wire dans les requêtes mixtes.
- Ajout d'un traitement spécial pour Broetje SOB.
- Simplification des paramètres.

## Version 0.12 ##
**09.04.2015**

- Ajout de `ONEWIRE_SENSORS` à ipwe.
- Correction du décodage des paramètres pour le système de chauffage ELCO Thision.

## Version 0.11 ##
**07.04.2015**

- Correction du décodage des paramètres pour le système de chauffage ELCO Thision.

## Version 0.10 ##
**15.03.2015**

- Ajout de paramètres supplémentaires pour le système de chauffage ELCO Thision.

## Version 0.9 ##
**09.03.2015**

- Ajout de paramètres supplémentaires pour le système de chauffage ELCO Thision.
- printTelegramm renvoie la chaîne de valeur pour un traitement ultérieur.

## Version 0.8 ##
**05.03.2015**

- Ajout de paramètres pour le système de chauffage ELCO Thision.
- Ajout de l'extension IPWE.
- Corrections de bugs mineurs.

## Version 0.7 ##
**06.02.2015**

- Ajout de la fonctionnalité de surveillance du bus.

## Version 0.6 ##
**02.02.2015**

- Renommage de SoftwareSerial en BSBSoftwareSerial.
- Changement de la structure de dossiers pour permettre une construction simple avec le kit de développement Arduino.

## Version 0.5 ##
**02.
