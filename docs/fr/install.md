# Installation

L'installation de BSB-LAN nécessite trois étapes :

1. Installer l'IDE Arduino pour flasher le logiciel BSB-LAN sur le microcontrôleur.
1. Assembler les pièces matérielles.
1. Connecter BSB-LAN au système de chauffage.

---

## Installation de l'IDE Arduino et flashage de BSB-LAN

1. [Télécharge](https://github.com/fredlcore/BSB-LAN/archive/refs/heads/master.zip) et décompresse la version actuelle de BSB-LAN à partir du référentiel principal ou utilise *git* pour [cloner](https://github.com/fredlcore/BSB-LAN.git) le référentiel.
1. Accède au dossier BSB_LAN et renomme les fichiers suivants :
    1. `BSB_LAN_custom_defs.h.default` en `BSB_LAN_custom_defs.h`.
    1. `BSB_LAN_config.h.default` en `BSB_LAN_config.h`.
1. [Télécharge](https://www.arduino.cc/en/software) et installe l'IDE Arduino pour ton système. Les utilisateurs avancés peuvent [consulter notre Wiki](https://github.com/fredlcore/BSB-LAN/wiki/Installing-BSB%E2%80%90LAN-using-arduino%E2%80%90cli) pour utiliser l’outil en ligne de commande `arduino-cli`.
1. Connecte ton microcontrôleur (ESP32 ou Arduino Due) à ton ordinateur et démarre l'IDE Arduino. Si le microcontrôleur n'est pas détecté comme périphérique USB, tu devras peut-être d'abord installer le pilote USB fourni par le fabricant du microcontrôleur.
1. Accède à ***Outils/Conseil/Gestionnaire de cartes*** et assure-toi que le framework pour ta carte est installé ("esp32 by Espressif Systems" pour le microcontrôleur ESP32, "Arduino SAM Boards (32-bits ARM Cortex-M3) by Arduino" pour le microcontrôleur Arduino Due).
1. Ensuite, accède à ***Outils/Conseil*** et sélectionne ton microcontrôleur :
    1. *ESP32 Dev Module* pour le Joy-It ESP32 NodeMCU.
    1. *Olimex ESP32-EVB* pour l'Olimex EVB basé sur ESP32.
    1. *Olimex ESP32-POE-ISO* pour l'Olimex POE ISO basé sur ESP32.
    1. *Arduino Due (Programming Port)* pour l'Arduino Due. **N'utilise pas le port USB natif ici** !
1. Maintenant, accède à ***Outils*** et sélectionne le port auquel ton microcontrôleur est connecté.
1. Toujours dans ***Outils***, sélectionne la vitesse de téléchargement appropriée (jusqu'à 460800 pour ESP32, 115200 pour Arduino Due).
1. [](){#SPIFFS}Pour les microcontrôleurs basés sur ESP32, retourne dans ***Outils/Conseil*** et sélectionne "Minimal SPIFFS" pour le schéma de partition (**ne confonds pas ceci avec le schéma de partition "Minimal", qui est différent et ne fonctionnera pas ici**). **Si tu ne choisis pas le bon schéma de partition, le micrologiciel ne rentrera pas dans l'ESP32 !**
1. Accède à ***Fichier/Ouvrir***, va dans le dossier BSB_LAN, puis double-clique sur `BSB_LAN.ino`. Le projet s'ouvrira.
1. Tu peux maintenant passer à la [configuration](configure.md) de BSB-LAN.
1. Une fois la configuration terminée, va dans ***Esquisse/Téléverser*** et téléverse le logiciel BSB-LAN sur le microcontrôleur. Avec les microcontrôleurs ESP32, le message "Hard resetting via RTS pin..." **n'est pas** un message d'erreur, mais signifie que l'upload a réussi et que l'ESP32 est en train de redémarrer.
1. Le même processus devra être suivi à chaque mise à jour, y compris lors de l'ajout de la liste des paramètres spécifiques à l'appareil.

---

## Assemblage de l'adaptateur BSB-LAN

Tu peux obtenir un adaptateur entièrement assemblé auprès de Frederik (bsb(ät)code-it.de) ou en construire un toi-même (consulte le dossier `schémas` pour les schémas). Une fois que tu as l'adaptateur BSB-LAN prêt, branche-le simplement sur le microcontrôleur. Si tu utilises un microcontrôleur Olimex, vérifie bien que l'adaptateur est bien centré sur le connecteur, car il peut encore s'insérer même s'il est décalé d'une rangée de broches sur la gauche ou la droite.

---

## Connexion de BSB-LAN au système de chauffage

Une fois le microcontrôleur et l'adaptateur BSB-LAN prêts, suis ces étapes pour connecter BSB-LAN au système de chauffage :

1. Débranche le microcontrôleur de ton ordinateur et éteins ton système de chauffage. Localise les connecteurs BSB/LPB/PPS. Tu devras peut-être ouvrir ton système de chauffage pour ça. Consulte la liste des [systèmes de chauffage pris en charge](supported_heating_systems.md) pour savoir où se trouvent les broches.<br>***Fais tout ça à tes propres risques !***<br>***Si tu n'es pas prudent, tu risques d'endommager ton équipement !***<br>**Fais particulièrement attention aux décharges électrostatiques (ESD) qui peuvent détruire à la fois BSB-LAN et le contrôleur de chauffage !**
1. Branche maintenant l'adaptateur BSB-LAN sur le microcontrôleur et connecte le connecteur à vis `+` au connecteur `CL+` (BSB), `DB` (LPB) ou `A6` (PPS, différents noms de connecteurs sont possibles), et le connecteur à vis `-` au connecteur `CL-` (BSB), `MB` (LPB) ou `M` (PPS).  
S'il te manque une fiche appropriée pour la connexion au contrôleur, tu peux improviser avec des [fiches sabot de 6,35 mm](https://www.reichelt.com/fr/fr/shop/produit/fiche_sabot_largeur_6_35_mm_jaune-7910).  
S'il n'y a pas de connecteur vide, pas de souci à ajouter les fils pour BSB-LAN à un connecteur déjà utilisé, à condition qu'ils soient insérés avec soin. Concernant les câbles, un câble torsadé à deux cœurs (idéalement blindé) est recommandé [par Siemens](https://sid.siemens.com/v/u/20140). Cependant, de nombreux utilisateurs ont réussi avec un simple fil de téléphone si les distances ne sont pas trop longues.
1. [](){#PowerSupply}Alimente maintenant le microcontrôleur. Le système de chauffage n'alimente pas le microcontrôleur, même si la LED de l'adaptateur BSB-LAN s'allume quand tu le connectes au système de chauffage. Utilise son port USB (ou PoE pour l'Olimex POE-ISO). Assure-toi d'avoir une alimentation stable d'au moins 2 ampères. Une fois le microcontrôleur alimenté, allume le système de chauffage. La LED rouge de l'adaptateur BSB-LAN devrait s'allumer et clignoter de temps en temps.
1. Ouvre ton navigateur et accède à l'adresse IP de BSB-LAN. Si MDNS est activé, tu peux aller directement sur [`http://bsb-lan.local`](http://bsb-lan.local). Sinon, trouve l'adresse IP de BSB-LAN dans ton routeur ou connecte le microcontrôleur à ton PC, ouvre l'IDE Arduino, puis va dans ***Outils/Moniteur série***, règle la vitesse à 115200, et redémarre le microcontrôleur. L'adresse IP s'affichera une fois qu'il sera connecté au réseau.

---

## Génération de la liste des paramètres spécifiques à l'appareil

Quand tu accèdes à BSB-LAN pour la première fois, tu remarqueras que seuls quelques paramètres sont affichés sur l'interface Web de l'appareil. Cela vient du fait que chaque modèle de contrôleur Siemens intégré à ton système de chauffage prend en charge un ensemble différent de paramètres. Avant, je fournissais une liste de paramètres collectés à partir de tous les types de systèmes de chauffage, mais il s'est avéré que cette liste était ambiguë ou contenait même des erreurs qu'on ne pouvait pas corriger de manière fiable. Cette liste est toujours disponible dans la version 2.2.x de BSB-LAN et peut être copiée à partir de là si nécessaire.  
Cependant, il n'est pas conseillé de le faire, car les ambiguïtés et les erreurs susmentionnées présentent un risque trop élevé de mauvaise configuration du système de chauffage. Il est plutôt recommandé de cliquer sur le bouton "**Liste des paramètres spécifiques à l'appareil**" dans le menu BSB-LAN et d'envoyer la liste générée à Frederik (bsb(ät)code-it.de). À partir de ce fichier, une liste de paramètres peut être générée qui correspond exactement au contrôleur de ton système de chauffage. Malheureusement, ce processus ne peut pas encore être automatisé, mais il n'a besoin d'être effectué qu'une seule fois. Ces données brutes ne contiennent aucun paramètre ni aucun autre type de données personnelles, uniquement la structure des paramètres du système de chauffage.  
C'est dans mon propre intérêt de créer et de renvoyer ces listes de paramètres sans délai, mais je te demande de bien vouloir comprendre si cela prend un peu plus de temps à cause de mon travail ou de questions familiales.  

Une fois que tu as reçu la liste des paramètres (ou que tu as pris celle de la version 2.2.x), tu dois remplacer le fichier `BSB_LAN_custom_defs.h` existant par celui qui t'a été envoyé, le compiler et le flasher à nouveau. Tu es maintenant prêt à accéder à tous les paramètres.

---
# Mises à jour

Si tu veux mettre à jour vers une nouvelle version de BSB-LAN, les points suivants doivent être notés :

- En gros, une mise à jour est comme une nouvelle installation.
- Vérifie le fichier `CHANGELOG.md` mis à jour pour voir ce qui a changé entre ta version et la version mise à jour.
- Les paramètres dans `BSB_LAN_config.h` ne sont pas écrasés, mais peuvent devoir être ajustés. Plus de détails peuvent être trouvés dans le fichier `CHANGELOG.md`.
- La liste de paramètres spécifique à l'appareil `BSB_LAN_custom_defs.h` n'est pas non plus écrasée et reste inchangée ; ce n'est que dans de rares cas que de petites modifications sont nécessaires, qui sont ensuite indiquées dans le fichier `CHANGELOG.md`.
- Certaines mises à jour modifient la structure EEPROM (voir notes dans le fichier `CHANGELOG.md`). Si tel est le cas, les paramètres BSB LAN sont réécrits dans l'EEPROM en fonction des valeurs du fichier `BSB_LAN_config.h`. Avant une mise à jour, les paramètres du fichier `BSB_LAN_config.h` doivent être à nouveau vérifiés pour garantir au moins l'accès au réseau.

## Mises à jour ultérieures sur les microcontrôleurs basés sur ESP32 "over the air" (OTA)

Si tu exécutes BSB-LAN sur un microcontrôleur basé sur ESP32 et que tu as activé les mises à jour Over-the-Air dans les [paramètres](configure.md), tu peux effectuer les futures mises à jour de BSB-LAN à l'aide de ton navigateur. Pour ce faire, au lieu d'utiliser *Esquisse/Téléverser*, tu dois sélectionner ***Esquisse/Exporter le binaire compilé***. Cela créera un dossier `build` dans ton dossier BSB-LAN, dans lequel tu trouveras, entre autres, le fichier `BSB_LAN.ino.bin`. Ouvre maintenant [http://bsb-lan.local:8080](http://bsb-lan.local:8080), sélectionne et téléverse ce fichier. Ne coupe pas le processus de téléversement. Tu peux essayer d'accéder à BSB-LAN à partir d'une autre fenêtre de navigateur pour voir si le processus est terminé.  
Note bien que cela ne s'applique qu'aux microcontrôleurs basés sur ESP32. Les cartes Arduino ne prennent pas en charge cette fonctionnalité.