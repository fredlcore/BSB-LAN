# Instructions de démarrage rapide

Ces instructions de démarrage rapide s'adressent aux utilisateurs qui sont déjà familiers avec l'installation et la configuration de logiciels sur leur ordinateur. Si tu as besoin d'instructions plus détaillées, consulte les [instructions d'installation](install.md) !

1. Assure-toi que ton système de chauffage est [compatible](supported_heating_systems.md) avec BSB-LAN !
1. [Télécharge](https://github.com/fredlcore/BSB-LAN/archive/refs/heads/master.zip) et décompresse la version actuelle de BSB-LAN depuis le référentiel principal ou utilise *git* pour [cloner](https://github.com/fredlcore/BSB-LAN.git) le référentiel.
1. Va dans le dossier BSB_LAN et renomme les fichiers suivants :
    1. `BSB_LAN_custom_defs.h.default` en `BSB_LAN_custom_defs.h`.
    2. `BSB_LAN_config.h.default` en `BSB_LAN_config.h`.
1. [Télécharge](https://www.arduino.cc/en/software) et installe l'IDE Arduino pour ton système.
1. Connecte ton microcontrôleur (ESP32 ou Arduino Due) à ton ordinateur et démarre l'IDE Arduino.
1. Accède à ***Outils/Board/Board Manager*** et assure-toi que le framework pour ta carte est installé ("esp32 by Espressif Systems" pour le microcontrôleur ESP32, "Arduino SAM Boards (32-bits ARM Cortex-M3) by Arduino" pour le microcontrôleur Arduino Due).
1. Ensuite, accède à ***Outils/Board*** et sélectionne ton microcontrôleur :
    1. *ESP32 Dev Module* pour le Joy-It ESP32 NodeMCU.
    2. *Olimex ESP32-EVB* pour l'Olimex EVB basé sur ESP32.
    3. *Olimex ESP32-POE-ISO* pour l'Olimex POE ISO basé sur ESP32.
    4. *Arduino Due (Programming Port)* pour l'Arduino Due. **N'utilise pas le port USB natif ici** !
1. Maintenant, accède à ***Outils*** et sélectionne le port auquel ton microcontrôleur est connecté.
1. Toujours dans ***Outils***, sélectionne la vitesse de téléchargement appropriée (jusqu'à 460800 pour ESP32, 115200 pour Arduino Due).
1. Pour les microcontrôleurs ESP32, retourne dans ***Outils/Partition Scheme*** et sélectionne "Minimal SPIFFS" pour le schéma de partition (**ne confonds pas avec le schéma "Minimal", qui est différent et ne fonctionne pas ici**). **Si tu ne choisis pas le bon schéma, le micrologiciel ne rentrera pas dans l'ESP32** !
1. Ouvre ***Fichier/Ouvrir***, va dans le dossier BSB_LAN, puis double-clique sur `BSB_LAN.ino`. Le projet s'ouvrira.
1. Clique sur l'onglet nommé `BSB_LAN_config.h` et configure au moins les options suivantes :
    1. Trouve `#define LANG DE` et change `DE` en `EN` pour l'anglais, `FR` pour le français, etc.
    1. Trouve `uint8_t network_type` : définis cette option sur `LAN` si tu utilises une connexion Ethernet/LAN. Mets-la sur `WLAN` si tu utilises une connexion WiFi/WLAN.
    1. Si tu n'utilises pas DHCP, configure les options suivantes selon ton réseau (utilise une virgule, pas un point, pour les adresses IP !) :
        1. `byte ip_addr[4] = {192,168,178,88};`
        1. `byte gateway_addr[4] = {192,168,178,1};`
        1. `byte dns_addr[4] = {192,168,178,1};`
        1. `byte subnet_addr[4] = {255,255,255,0};`
        1. `char wifi_ssid[32] = "Your_Wifi_network_name";`
        1. `char wifi_pass[32] = "Your_WiFi_network_password";`
1. Ensuite, va dans ***Sketch/Upload*** et téléverse le logiciel BSB-LAN sur le microcontrôleur. Avec les microcontrôleurs ESP32, le message "Hard resetting via RTS pin..." **n'est pas** un message d'erreur, mais signifie que l'upload a réussi et que l'ESP32 est en train de redémarrer.
1. Déconnecte le microcontrôleur et éteins ton système de chauffage. Localise les connecteurs BSB/LPB/PPS. Tu devras peut-être ouvrir ton système de chauffage pour cela. ***Fais tout ça à tes propres risques*** !
1. Connecte maintenant l'adaptateur BSB-LAN au microcontrôleur, puis connecte le connecteur à vis `+` au connecteur `CL+` (BSB), `DB` (LPB) ou `A6` (PPS, les noms des connecteurs peuvent varier), et le connecteur à vis `-` au connecteur `CL-` (BSB), `MB` (LPB) ou `M` (PPS).
1. Allume le microcontrôleur via le port USB ou via PoE (uniquement pour Olimex POE-ISO). Puis allume le système de chauffage. La LED rouge de l'adaptateur BSB-LAN doit s'allumer. Elle devrait clignoter de temps en temps.
1. Ouvre ton navigateur web et accède à l'adresse IP de BSB-LAN. Si MDNS est activé, tu peux aller directement sur `http://bsb-lan.local`. Tu peux trouver l'adresse IP de BSB-LAN dans ton routeur, ou connecter le microcontrôleur à ton PC, ouvrir l'IDE Arduino, puis aller dans ***Outils/Moniteur série***. Redémarre le microcontrôleur, et l'adresse IP s'affichera quand il se connecte au réseau.
1. **C'est terminé :-)**

---

## Ça ne fonctionne pas !

Assure-toi de vérifier **chaque point** dans la [section Dépannage](troubleshooting.md) avant de nous contacter !

---

## Pourquoi est-ce que je ne vois que quelques paramètres ?

Lors de ta première connexion à BSB-LAN, tu remarqueras que seuls quelques paramètres sont affichés sur l'interface Web de l'appareil. Cela vient du fait que chaque modèle de contrôleur Siemens intégré à ton système de chauffage prend en charge un ensemble différent de paramètres. Avant, je fournissais une liste de paramètres collectés à partir de différents systèmes de chauffage, mais elle s'est révélée ambiguë ou contenait des erreurs qu'on ne pouvait pas corriger de manière fiable. Cette liste est toujours disponible dans la version 2.2.x de BSB-LAN et peut être copiée à partir de là si nécessaire.  
Cependant, il n'est pas conseillé de l'utiliser car les ambiguïtés et erreurs mentionnées présentent un risque trop élevé de mauvaise configuration du système de chauffage. Clique plutôt sur le bouton "**Liste des paramètres spécifiques à l'appareil**" dans le menu de BSB-LAN et envoie la liste générée à Frederik (bsb(ät)code-it.de). Il pourra générer une liste qui correspond exactement au contrôleur de ton système de chauffage. Ce processus n'est pas encore automatisé, mais il n'a besoin d'être fait qu'une seule fois. Ces données brutes ne contiennent aucune configuration ni donnée personnelle, uniquement la structure des paramètres du système de chauffage.  
Je fais tout mon possible pour créer et renvoyer ces listes rapidement, mais je te demande de comprendre si cela prend un peu plus de temps à cause de mon travail ou d'obligations familiales.  
Quand tu reçois le fichier (ou que tu utilises celui de la version 2.2.x), remplace simplement le fichier du même nom dans le dossier `BSB_LAN` et refais les étapes de flashage mentionnées plus haut.