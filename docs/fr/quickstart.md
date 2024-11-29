# Instructions de démarrage rapide
Ces instructions de démarrage rapide s'adressent aux utilisateurs qui sont familiarisés avec l'installation et la configuration de logiciels sur leur ordinateur. Si vous avez besoin d'instructions plus détaillées, veuillez consulter les [instructions d'installation](install.md) !

1. Assurez-vous que votre système de chauffage est [compatible](supported_heating_systems.md) avec BSB-LAN !
2. [Téléchargez](https://github.com/fredlcore/BSB-LAN/archive/refs/heads/master.zip) et décompressez la version actuelle de BSB-LAN à partir du référentiel principal ou utilisez *git* pour [cloner](https://github.com/fredlcore/BSB-LAN.git) le référentiel.
3. Accédez au dossier BSB_LAN et renommez les fichiers suivants :
    1. `BSB_LAN_custom_defs.h.default` en `BSB_LAN_custom_defs.h`
    2. `BSB_LAN_config.h.default` en `BSB_LAN_config.h`.
4. [Téléchargez](https://www.arduino.cc/en/software) et installez l'IDE Arduino pour votre système.
5. Connectez votre microcontrôleur (ESP32 ou Arduino Due) à votre ordinateur et démarrez l'IDE Arduino.
6. Accédez à ***Outils/Board/Board Manager*** et assurez-vous que le framework pour votre carte est installé ("esp32 by Espressif Systems" pour le microcontrôleur ESP32, "Arduino SAM Boards (32-bits ARM Cortex-M3) by Arduino" pour le microcontrôleur Arduino Due)
7. À nouveau, accédez à ***Outils/Board*** et sélectionnez votre microcontrôleur :
    1. *ESP32 Dev Module* pour le Joy-It ESP32 NodeMCU.
    2. *Olimex ESP32-EVB* pour l'Olimex EVB basé sur ESP32.
    3. *Olimex ESP32-POE-ISO* pour l'Olimex POE ISO basé sur ESP32
    4. *Arduino Due (Programming Port)* pour l'Arduino Due. **N'utilisez pas le port USB natif ici** !
8. À nouveau, accédez à ***Outils/Board*** et sélectionnez la vitesse de téléchargement appropriée (jusqu'à 460800 pour ESP32, 115200 pour Arduino Due).
9. Pour les microcontrôleurs basés sur ESP32, accédez à nouveau à ***Outils/Partition Scheme*** et sélectionnez "Minimal SPIFFS" pour le schéma de partition (**ne confondez pas avec le schéma de partition "Minimal" similaire qui est différent et ne fonctionne pas dans notre cas**). **Si vous ne définissez pas le bon schéma de partition, le micrologiciel ne rentrera pas dans l'ESP32** !
10. Accédez à ***Fichier/Ouvrir*** et accédez au dossier BSB_LAN, puis double-cliquez sur `BSB_LAN.ino`. Le projet s'ouvrira.
11. Cliquez sur l'onglet avec le nom de fichier `BSB_LAN_config.h` et configurez au moins les options suivantes :
    1. Recherchez `#define LANG DE` : changez `DE` en `EN` pour l'anglais, `FR` pour le français, etc.
    2. Recherchez `uint8_t network_type` : définissez cette option sur `LAN` si vous utilisez une connexion Ethernet/LAN. Définissez-la sur `WLAN` si vous utilisez une connexion WiFi/WLAN.
    3. Si vous n'utilisez pas DHCP, configurez les options suivantes en fonction de votre réseau (assurez-vous d'utiliser une virgule, et non un point, pour les adresses IP !) :
        1. `byte ip_addr[4] = {192,168,178,88};`
        2. `byte gateway_addr[4] = {192,168,178,1};`
        3. `byte dns_addr[4] = {192,168,178,1};`
        4. `byte subnet_addr[4] = {255,255,255,0};`
        5. `char wifi_ssid[32] = "Your_Wifi_network_name";`
        6. `char wifi_pass[32] = "Your_WiFi_network_password";`
12. Accédez maintenant à ***Sketch/Upload*** et téléchargez le logiciel BSB-LAN sur le microcontrôleur.
13. Déconnectez le microcontrôleur et éteignez votre système de chauffage. Localisez les connecteurs BSB/LPB/PPS. Vous devrez peut-être ouvrir votre système de chauffage pour cela. ***Faites tout cela à vos propres risques*** !
14. Connectez maintenant l'adaptateur BSB-LAN au microcontrôleur et connectez le connecteur à vis `+` au connecteur `CL+` (BSB), `DB` (LPB) ou `A6` (PPS, les noms des connecteurs peuvent varier), et le connecteur à vis `-` au connecteur `CL-` (BSB), `MB` (LPB) ou `M` (PPS).
15. Allumez le microcontrôleur via le port USB ou via PoE (uniquement Olimex POE-ISO). Puis allumez le système de chauffage. Le LED rouge de l'adaptateur BSB-LAN doit s'allumer. Il devrait clignoter de temps en temps.
16. Ouvrez maintenant votre navigateur web et accédez à l'adresse IP de BSB-LAN. Si MDNS est activé, vous pouvez directement accéder à `http://bsb-lan.local`. Vous pouvez trouver l'adresse IP de BSB-LAN dans votre routeur, ou vous pouvez connecter le microcontrôleur à votre PC et ouvrir l'IDE Arduino, puis accéder à ***Outils/Moniteur série***. Redémarrez le microcontrôleur, et l'adresse IP s'affichera lors de la connexion au réseau.
17. **C'est terminé :-)**
---
## Ça ne fonctionne pas !

Veuillez vous assurer de vérifier **chaque entrée** dans la [section Dépannage](troubleshooting.md) avant de nous contacter !

---
## Pourquoi est-ce que je ne vois que quelques paramètres ?

Lors de votre première connexion à BSB-LAN, vous remarquerez que seuls quelques paramètres sont affichés sur l'interface Web de l'appareil. Cela est dû au fait que chaque modèle du contrôleur Siemens intégré à votre système de chauffage prend en charge un ensemble différent de paramètres. Auparavant, je fournissais une liste de paramètres collectés à partir de différents types de systèmes de chauffage, mais il s'est avéré que cette liste était ambiguë ou contenait même des erreurs que nous ne pouvions pas corriger de manière fiable. Cette liste est toujours disponible dans la version 2.2.x de BSB-LAN et peut être copiée à partir de là si nécessaire.
Cependant, il n'est pas conseillé de le faire car les ambiguïtés et les erreurs mentionnées présentent un risque trop élevé de mauvaise configuration du système de chauffage. Il est plutôt recommandé de cliquer sur le bouton "**Liste des paramètres spécifiques à l'appareil**" dans le menu de BSB-LAN et d'envoyer la liste générée à Frederik (bsb(ät)code-it.de). À partir de ce fichier, une liste de paramètres peut être générée qui correspond exactement au contrôleur de votre système de chauffage. Malheureusement, ce processus ne peut pas encore être automatisé, mais au moins il n'a besoin d'être fait qu'une seule fois. Ces données brutes ne contiennent aucune configuration ni aucun autre type de données personnelles, uniquement la structure des paramètres du système de chauffage.
Il est dans mon propre intérêt de créer et de renvoyer ces listes de paramètres sans délai, mais je vous prie de bien vouloir comprendre si cela prend un peu plus de temps en raison de mon travail ou de mes obligations familiales.
