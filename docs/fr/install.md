# Installation
L'installation de BSB-LAN nécessite trois étapes :

1. Installer l'IDE Arduino pour flasher le logiciel BSB-LAN sur le microcontrôleur
2. Assembler les pièces matérielles
3. Connecter BSB-LAN au système de chauffage

## Installation de l'IDE Arduino et flashage de BSB-LAN

1. [Téléchargez](https://github.com/fredlcore/BSB-LAN/archive/refs/heads/master.zip) et décompressez la version actuelle de BSB-LAN à partir du référentiel principal ou utilisez *git* pour [cloner](https://github.com/fredlcore/BSB-LAN.git) le référentiel.
2. Accédez au dossier BSB_LAN et renommez les fichiers suivants :
    1. `BSB_LAN_custom_defs.h.default` en `BSB_LAN_custom_defs.h`
    2. `BSB_LAN_config.h.default` en `BSB_LAN_config.h`.
3. [Téléchargez](https://www.arduino.cc/en/software) et installez l'IDE Arduino pour votre système.
4. Connectez votre microcontrôleur (ESP32 ou Arduino Due) à votre ordinateur et démarrez l'IDE Arduino.
5. Accédez à ***Outils/Conseil/Gestionnaire de cartes*** et assurez-vous que le framework pour votre carte est installé ("esp32 by Espressif Systems" pour le microcontrôleur ESP32, "Arduino SAM Boards (32-bits ARM Cortex-M3) by Arduino" pour le microcontrôleur Arduino Due)
6. À nouveau, accédez à ***Outils/Conseil*** et sélectionnez votre microcontrôleur :
    1. *ESP32 Dev Module* pour le Joy-It ESP32 NodeMCU.
    2. *Olimex ESP32-EVB* pour l'Olimex EVB basé sur ESP32.
    3. *OlimeMultiplier l'option Olimex ESP32-POE-ISO* pour l'Olimex POE ISO basé sur ESP32
    4. *Arduino Due (Programming Port)* pour l'Arduino Due. **N'utilisez pas le port USB natif ici** !
7. À nouveau, accédez à ***Outils/Conseil*** et sélectionnez la vitesse de téléchargement appropriée (jusqu'à 460800 pour ESP32, 115200 pour Arduino Due).
8. [](){#SPIFFS}Pour les microcontrôleurs basés sur ESP32, accédez à nouveau à ***Outils/Conseil*** et sélectionnez "Minimal SPIFFS" pour le schéma de partition (**ne confondez pas ceci avec le schéma de partition "Minimal" similaire** qui est différent et ne fonctionne pas dans notre cas). **Si vous ne définissez pas le bon schéma de partition, le micrologiciel ne rentrera pas dans l'ESP32 !**
9. Accédez à ***Fichier/Ouvrir*** et accédez au dossier BSB_LAN, puis double-cliquez sur `BSB_LAN.ino`. Le projet s'ouvrira.
10. Vous pouvez maintenant passer à la [configuration](configure.md) de BSB-LAN.
11. Une fois la configuration terminée, accédez à ***Esquisse/Téléverser*** et téléversez le logiciel BSB-LAN sur le microcontrôleur.

### Mises à jour ultérieures sur les microcontrôleurs basés sur ESP32 "over the air" (OTA)

Si vous exécutez BSB-LAN sur un microcontrôleur basé sur ESP32 et que vous avez activé les mises à jour Over-the-Air dans les [paramètres](configure.md), vous pouvez effectuer les futures mises à jour de BSB-LAN à l'aide de votre navigateur. Pour ce faire, au lieu d'utiliser *Esquisse/Téléverser*, vous devez sélectionner ***Esquisse/Exporter le binaire compilé***. Cela créera un dossier `build` dans votre dossier BSB-LAN dans lequel vous trouverez, entre autres, le fichier `BSB_LAN.ino.bin`. Ouvrez maintenant [http://bsb-lan.local:8080](http://bsb-lan.local:8080) et sélectionnez et téléversez ce fichier. Ne pas interrompre le processus de téléversement. Vous pouvez essayer d'accéder à BSB-LAN à partir d'une autre fenêtre de navigateur pour voir si le processus est terminé.  
Veuillez noter que cela ne s'applique qu'aux microcontrôleurs basés sur ESP32. Les cartes Arduino ne prennent pas en charge cette fonctionnalité.

## Assemblage de l'adaptateur BSB-LAN
Vous pouvez obtenir un adaptateur entièrement assemblé auprès de Frederik (bsb(ät)code-it.de) ou en construire un vous-même (consultez le dossier `schémas` pour les schémas). Une fois que vous avez l'adaptateur BSB-LAN prêt, vous devez simplement le brancher sur le microcontrôleur. Si vous utilisez un microcontrôleur Olimex, vérifiez à nouveau que l'adaptateur est bien centré sur le connecteur, car il peut encore s'insérer même s'il est décalé d'une rangée de broches sur la gauche ou sur la droite.

## Connexion de BSB-LAN au système de chauffage

Une fois le microcontrôleur et l'adaptateur BSB-LAN prêts, effectuez les étapes suivantes pour connecter BSB-LAN au système de chauffage :

1. Débranchez le microcontrôleur de votre ordinateur et éteignez votre système de chauffage. Localisez les connecteurs BSB/LPB/PPS. Vous devrez peut-être ouvrir votre système de chauffage pour cela. Consultez la liste des [systèmes de chauffage pris en charge](supported_heating_systems.md) pour savoir où se trouvent les broches.<br>***Faites tout cela à vos propres risques !***<br>***Si vous n'êtes pas prudent, vous risquez d'endommager votre équipement !***<br>**Prenez particulièrement soin d'éviter les décharges électrostatiques (ESD) qui peuvent détruire à la fois BSB-LAN et le contrôleur de chauffage !**
2. Branchez maintenant l'adaptateur BSB-LAN sur le microcontrôleur et connectez le connecteur à vis `+` au connecteur `CL+` (BSB), `DB` (LPB) ou `A6` (PPS, différents noms de connecteurs sont possibles), et le connecteur à vis `-` au connecteur `CL-` (BSB), `MB` (LPB) ou `M` (PPS). S'il n'y a pas de connecteur vide, il n'y a aucun problème à ajouter les fils pour BSB-LAN à un connecteur déjà "utilisé", à condition que les fils soient insérés avec soin. En ce qui concerne les câbles, un câble torsadé à deux cœurs (idéalement blindé/blindé) est recommandé [par Siemens](https://sid.siemens.com/v/u/20140). Cependant, un certain nombre d'utilisateurs ont également réussi avec un simple fil de téléphone si les distances ne sont pas trop longues.
3. [](){#PowerSupply}Vous devez maintenant alimenter le microcontrôleur. Notez que le système de chauffage n'alimente pas le microcontrôleur, même si la LED de l'adaptateur BSB-LAN s'allume lorsque vous le connectez au système de chauffage. Vous devez alimenter le microcontrôleur via son port USB (ou via PoE sur l'Olimex POE-ISO). Assurez-vous d'utiliser une alimentation stable d'au moins 2 ampères. Une fois le microcontrôleur alimenté, allumez le système de chauffage. La LED rouge de l'adaptateur BSB-LAN doit s'allumer. Il devrait clignoter de temps en temps.
4. Ouvrez maintenant votre navigateur web et accédez à l'adresse IP de BSB-LAN. Si MDNS est activé, vous pouvez directement accéder à [`http://bsb-lan.local`](http://bsb-lan.local). Sinon, vous pouvez trouver l'adresse IP de BSB-LAN dans votre routeur, ou vous pouvez connecter le microcontrôleur à votre PC et ouvrir l'IDE Arduino, puis accéder à ***Outils/Moniteur série*** et définir la vitesse du moniteur série sur 115200. Redémarrez le microcontrôleur, et l'adresse IP s'affichera lors de la connexion au réseau.

## Génération de la liste des paramètres spécifiques à l'appareil

Lorsque vous accédez à BSB-LAN pour la première fois, vous remarquerez que seuls quelques paramètres sont affichés sur l'interface Web de l'appareil. Cela est dû au fait que chaque modèle du contrôleur Siemens intégré à votre système de chauffage prend en charge un ensemble différent de paramètres. Auparavant, je fournissais une liste de paramètres collectés à partir de tous les types de systèmes de chauffage, mais il s'est avéré que cette liste était ambiguë ou contenait même des erreurs que nous ne pouvions pas corriger de manière fiable. Cette liste est toujours disponible dans la version 2.2.x de BSB-LAN et peut être copiée à partir de là si nécessaire.  
Cependant, il n'est pas conseillé de le faire car les ambiguïtés et les erreurs susmentionnées présentent un risque trop élevé de mauvaise configuration du système de chauffage. Il est plutôt recommandé de cliquer sur le bouton "**Liste des paramètres spécifiques à l'appareil**" dans le menu BSB-LAN et d'envoyer la liste générée à Frederik (bsb(ät)code-it.de). À partir de ce fichier, une liste de paramètres peut être générée qui correspond exactement au contrôleur de votre système de chauffage. Malheureusement, ce processus ne peut pas encore être automatisé, mais au moins il n'a besoin d'être effectué qu'une seule fois. Ces données brutes ne contiennent aucun paramètre ni aucun autre type de données personnelles, uniquement la structure des paramètres du système de chauffage.  
Il est dans mon propre intérêt de créer et de renvoyer ces listes de paramètres sans délai, mais je vous demande de bien vouloir comprendre si cela prend un peu plus de temps en raison de mon travail ou de questions familiales.  

Une fois que vous avez reçu la liste des paramètres (ou que vous avez pris celle de la version 2.2.x), vous devez remplacer le fichier `BSB_LAN_custom_defs.h` existant par celui qui vous a été envoyé, le compiler et le flasher à nouveau. Vous êtes maintenant prêt à accéder à tous les paramètres.
