# Qu'est-ce que BSB-LAN ?

[BSB-LAN est une solution logicielle](https://www.bsb-lan.de)/matérielle pour accéder au [« Boiler-System-Bus » (BSB)][BSB], au [« Local-Process-Bus (LPB) »][LPB] et à la [« Punkt-zu-Punkt-Schnittstelle » (PPS)][PPS]. Le matériel BSB-LAN est disponible pour divers microcontrôleurs basés sur *ESP32* (ESP32 NodeMCU, Olimex EVB, Olimeé POE-ISO) ainsi que pour un *Arduino Due* avec un shield Ethernet. Il permet d'accéder aux systèmes de chauffage Atlantic, Brötje, Elco et de nombreux autres fabricants via Ethernet/WiFi, à condition qu'ils utilisent l'une des cartes électroniques Siemens répertoriés ci-dessous.

BSB-LAN permet de surveiller et de contrôler le système de chauffage et d'enregistrer toutes les valeurs reçues. Ce projet prend en charge presque tous les paramètres disponibles sur les systèmes de chauffage et peut être une alternative plus complète et plus économique à l'OZW 672, à l'OCI 700 ou au Remocon Net B.

L'[intégration facultative dans les systèmes domotiques existants](homeautomation.md) tels que [Home Assistant][HomeAssistant], [ioBroker][ioBroker], [openHAB][openHAB], [Node-RED][NodeRED], [Homebridge][Homebridge], [Jeedom][Jeedom], [SmartHomeNG][SmartHomeNG], [Volkszähler][Volkszaehler], [FHEM][FHEM], [HomeMatic][Homematic], Loxone, IP-Symcon ou EDOMI est possible via [MQTT][MQTT], [JSON][JSON] ou [HTTP access][using].

L'adaptateur peut également être utilisé comme carte d'acquisition sans connexion à Internet grâce à une carte microSD.

Les capteurs de température et d'humidité peuvent également être connectés et leurs données peuvent également être enregistrées et analysées. Vous avez aussi la possibilité d'intégrer votre propre code dans le logiciel BSB-LAN, pour rajouter autant de fonctionnalités que vous le souhaitez.

# Où et comment commencer ?

- Vous êtes un utilisateur expérimenté ? Consultez les [instructions de démarrage rapide](quickstart.md). Sinon (ou si vous rencontrez des problèmes), veuillez continuer à lire !
- Mon système de chauffage est-il pris en charge par BSB-LAN ? Veuillez consulter la [liste des systèmes de chauffage pris en charge](supported_heating_systems.md).
- Si vous savez déjà que votre système est pris en charge, en [savoir plus sur l'adaptateur BSB-LAN](bsb-lan_adapter.md) et où l'obtenir.
- Si vous avez déjà l'adaptateur, vous voudrez peut-être savoir [comment l'installer](install.md).
- Si vous avez installé l'adaptateur, vous devrez [configurer BSB-LAN](configure.md).
- Une fois que vous avez tout configuré, découvrez [comment utiliser BSB-LAN](using.md) ou en savoir plus sur les façons de [l'intégrer dans les systèmes de domotique](homeautomation.md).
- Si vous souhaitez mettre à jour BSB-LAN et que vous souhaitez savoir ce qui a changé depuis votre dernière installation, veuillez consulter le [ChangeLog](CHANGELOG.md).
- Nos [pages wiki](https://github.com/fredlcore/BSB-LAN/wiki) sont en constante évolution et fournissent des connaissances de base ainsi que des sujets plus spécialisés sur BSB-LAN et les systèmes de chauffage en général.
- Si vous rencontrez des problèmes, consultez la [page de dépannage](troubleshooting.md).
- Et avant de poser des questions à qui que ce soit, consultez d'abord nos [Foire aux questions (FAQ)](faq.md) !
