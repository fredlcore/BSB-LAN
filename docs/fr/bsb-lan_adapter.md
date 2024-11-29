# L'adaptateur BSB-LAN
---
### Pour avoir un adaptateur - contactez Frederik à bsb(ät)code-it.de (en allemand ou en anglais) pour plus de détails.
---
Pour connecter votre système de chauffage à un microcontrôleur, vous avez besoin d'une carte électronique qui effectue la conversion de niveau logique:
<img src="../images/Logic Level Adapter.jpg">
L'adaptateur est ensuite branché directement sur le microcontrôleur, soit sous les broches de l'ESP32-NodeMCU, soit sur le connecteur UEXT de l'Olimex:

<img src="../images/Logic Level Adapter on NodeMCU.jpg">  
<img src="../images/Logic Level Adapter in Case.jpg">  
<img src="../images/Logic Level Adapter on Olimex EVB.jpg">  

Les deux types d'ESP32 (Olimex et ESP32-NoceMCU) ne diffèrent que par l'emplacement de leurs connecteurs, les autres parties de la carte étant identiques.  
L'adaptateur pour l'Arduino Due contient une puce EEPROM car la Due n'est pas équipée d'une EEPROM. Par conséquent, vous pouvez réutiliser l'adaptateur Arduino Due sur un microcontrôleur ESP32 (si vous connectez les bonnes pins avec des fils), mais vous ne pouvez pas utiliser un adaptateur ESP32 sur une Arduino Due.
---
# Microcontrôleurs appropriés

BSB-LAN peut être installé sur trois types différents de microcontrôleurs:

1. ESP32-Olimex
2. ESP32-NodeMCU (version 30 broches uniquement!)
3. Arduino Due.

Olimex produit plusieurs types de cartes:
Nous recommandons soit l'[Olimex ESP32-EVB](https://www.olimex.com/Products/IoT/ESP32/ESP32-EVB/open-source-hardware) soit l'[Olimex ESP32-POE-ISO](https://www.olimex.com/Products/IoT/ESP32/ESP32-POE-ISO/open-source-hardware). La simple version POE (sans "ISO") n'est pas recommandée car elle ne permet pas de se connecter à la fois à l'Ethernet PoE et à l'USB.

L'[Arduino Due](https://store.arduino.cc/products/arduino-due) nécessite un [Shield Ethernet](https://store.arduino.cc/products/arduino-ethernet-shield-2) pour accéder au réseau local.

Chacun des différents contrôleurs a ses avantages et ses inconvénients:

|Fonctionnalité|ESP32-Olimex|ESP32-POE-ISO|ESP32-NodeMCU|Arduino Due|
|:------------|:----------:|:-----------:|:-----------:|:---------:|
|Ethernet/LAN |X           |X            |-            |X          |
|WiFi/WLAN    |X           |X            |X            |-          |
|Mise à jour via OTA|X |X            |X            |-          |
|Carte micro-SD intégrée |X |X            |-            |-          |
|GPIO accessibles|2 (GPIO13/16)|quelques-uns|quelques-uns|beaucoup         |
