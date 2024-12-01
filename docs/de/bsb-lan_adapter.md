# Der BSB-LAN-Adapter
---
### Adapterplatinen verfügbar – schreib' Frederik einfach eine E-Mail an bsb(ät)code-it.de (auf Deutsch oder Englisch) für weitere Details.
---
Um dein Heizsystem mit einem Mikrocontroller zu verbinden, benötigst du eine Adapterplatine, die die notwendige Logik-Pegelumwandlung vornimmt:
<img src="../images/Logic Level Adapter.jpg">
Der Adapter wird dann direkt auf den Mikrocontroller gesteckt, entweder unter die Pins des ESP32-NodeMCU oder auf den UEXT-Anschluss des Olimex:

<img src="../images/Logic Level Adapter on NodeMCU.jpg">  
<img src="../images/Logic Level Adapter in Case.jpg">  
<img src="../images/Logic Level Adapter on Olimex EVB.jpg">  

Die beiden verschiedenen Arten von ESP32-Adaptern (Olimex und ESP32-NodeMCU) unterscheiden sich nur in der Position ihrer Anschlüsse, die anderen Teile der Platine sind identisch.

Die Arduino Due-Platine enthält einen EEPROM-Chip, da die Due-Platine keinen integrierten EEPROM hat. Daher kannst du die Arduino Due-Platine auf einem ESP32-Mikrocontroller wiederverwenden (wenn du die richtigen Pins mit Drähten verbindest), aber du kannst keinen Adapter für den ESP32 auf einem Arduino Due verwenden.
---
# Geeignete Mikrocontroller

BSB-LAN kann auf drei verschiedenen Arten von Mikrocontrollern installiert werden:

1. ESP32-Olimex
2. ESP32-NodeMCU (nur 30-Pin-Version!)
3. Arduino Due

Olimex produziert mehrere Arten von Platinen:
Wir empfehlen entweder die [Olimex ESP32-EVB](https://www.olimex.com/Products/IoT/ESP32/ESP32-EVB/open-source-hardware) oder die [Olimex ESP32-POE-ISO](https://www.olimex.com/Products/IoT/ESP32/ESP32-POE-ISO/open-source-hardware). Die einfache POE-Version (ohne "ISO") wird nicht empfohlen, da sie keine gleichzeitige Verbindung mit PoE-Ethernet und USB zulässt.

Der [Arduino Due](https://store.arduino.cc/products/arduino-due) benötigt ein [Ethernet Shield](https://store.arduino.cc/products/arduino-ethernet-shield-2), um auf das lokale Netzwerk zuzugreifen.

Jeder der verschiedenen Controller hat seine Vor- und Nachteile:

|Funktionalität|ESP32-Olimex|ESP32-POE-ISO|ESP32-NodeMCU|Arduino Due|
|:------------|:----------:|:-----------:|:-----------:|:---------:|
|Ethernet/LAN |X           |X            |-            |X          |
|WiFi/WLAN    |X           |X            |X            |-          |
|Over-the-air-aktualisierbar|X |X            |X            |-          |
|Integrierte microSD-Karte |X |X            |-            |-          |
|Zugängliche GPIOs|2 (GPIO13/16)|einige|einige|viele         |