# Kurzanleitung
Diese Kurzanleitung richtet sich an Benutzer, die mit der Installation und Konfiguration von Software auf ihrem Computer vertraut sind. Wenn Sie ausführlichere Anweisungen benötigen, lesen Sie bitte die [Installationsanweisungen](install.md)!.

1. Stellen Sie sicher, dass Ihre Heizung mit BSB-LAN [kompatibel](supported_heating_systems.md) ist!
1. [Laden Sie](https://github.com/fredlcore/BSB-LAN/archive/refs/heads/master.zip) die aktuelle BSB-LAN-Version aus dem Master-Repository herunter oder verwenden Sie *git*, um das Repository zu [klonen](https://github.com/fredlcore/BSB-LAN.git).
1. Navigieren Sie zum Ordner BSB_LAN und benennen Sie die folgenden Dateien um:
    1. `BSB_LAN_custom_defs.h.default` in `BSB_LAN_custom_defs.h`
    1. `BSB_LAN_config.h.default` in `BSB_LAN_config.h`.
1. [Laden Sie](https://www.arduino.cc/en/software) die Arduino IDE für Ihr System herunter und installieren Sie sie.
1. Verbinden Sie Ihren Mikrocontroller (ESP32 oder Arduino Due) mit Ihrem Computer und starten Sie die Arduino IDE.
1. Gehen Sie zu ***Tools/Board/Board Manager*** und stellen Sie sicher, dass das Framework für Ihre Platine installiert ist ("esp32 by Espressif Systems" für ESP32-Mikrocontroller, "Arduino SAM Boards (32-bits ARM Cortex-M3) by Arduino" für Arduino Due-Mikrocontroller)
1. Gehen Sie erneut zu ***Tools/Board*** und wählen Sie Ihren Mikrocontroller aus:
    1. *ESP32 Dev Module* für den Joy-It ESP32 NodeMCU.
    1. *Olimex ESP32-EVB* für den ESP32-basierten Olimex EVB.
    1. *Olimex ESP32-POE-ISO* für den ESP32-basierten Olimex POE ISO
    1. *Arduino Due (Programming Port)* für den Arduino Due. **Verwenden Sie hier nicht den nativen USB-Port!**
1. Gehen Sie erneut zu ***Tools/Board*** und wählen Sie die richtige Upload-Geschwindigkeit aus (bis zu 460800 für ESP32, 115200 für Arduino Due).
1. Für ESP32-basierte Mikrocontroller gehen Sie erneut zu ***Tools/Partition Scheme*** und wählen "Minimal SPIFFS" als Partitionsschema aus (**nicht zu verwechseln mit dem ähnlichen "Minimal"-Partitionsschema**, das sich unterscheidet und in unserem Fall nicht funktioniert). **Wenn Sie das falsche Partitionsschema auswählen, passt die Firmware nicht auf den ESP32!**
1. Gehen Sie zu ***File/Open***, navigieren Sie zum Ordner BSB_LAN und doppelklicken Sie auf `BSB_LAN.ino`. Das Projekt wird geöffnet.
1. Klicken Sie auf die Registerkarte mit dem Dateinamen `BSB_LAN_config.h` und konfigurieren Sie mindestens Folgendes:
    1. Suchen Sie nach `#define LANG DE`: Ändern Sie `DE` in `EN` für Englisch, `FR` für Französisch usw.
    1. Suchen Sie nach `uint8_t network_type`: Setzen Sie dies auf `LAN`, wenn Sie eine Ethernet/LAN-Verbindung verwenden. Setzen Sie es auf `WLAN`, wenn Sie eine WiFi/WLAN-Verbindung verw verwenden.
    1. Wenn Sie DHCP nicht verwenden, konfigurieren Sie die folgenden Optionen entsprechend Ihrem Netzwerk (stellen Sie sicher, dass Sie für IP-Adressen ein Komma und keinen Punkt verwenden!):
        1. `byte ip_addr[4] = {192,168,178,88};`
        1. `byte gateway_addr[4] = {192,168,178,1};`
        1. `byte dns_addr[4] = {192,168,178,1};`
        1. `byte subnet_addr[4] = {255,255,255,0};`
        1. `char wifi_ssid[32] = "Ihr_WLAN_Netzwerk_Name";`
        1. `char wifi_pass[32] = "Ihr_WLAN_Netzwerk_Passwort";`
1. Klicken Sie jetzt auf ***Sketch/Upload***, um die BSB-LAN-Software auf den Mikrocontroller zu laden.
1. Trennen Sie den Mikrocontroller und schalten Sie Ihre Heizung aus. Suchen Sie die BSB/LPB/PPS-Anschlüsse. Möglicherweise müssen Sie dazu Ihre Heizung öffnen. ***Gehen Sie dabei auf eigene Gefahr vor!***
1. Stecken Sie nun den BSB-LAN-Adapter auf den Mikrocontroller und verbinden Sie den `+` Schraubanschluss mit dem `CL+` (BSB), `DB` (LPB) oder `A6` (PPS, andere Bezeichnungen für den Anschluss sind möglich) und den `-` Schraubanschluss mit dem `CL-` (BSB), `MB` (LPB) oder `M` (PPS).
1. Schalten Sie den Mikrocontroller über den USB-Port oder PoE (nur Olimex POE-ISO) ein. Schalten Sie dann die Heizung ein. Die rote LED des BSB-LAN-Adapters sollte leuchten. Sie sollte gelegentlich blinken.
1. Öffnen Sie nun Ihren Webbrowser und geben Sie die IP-Adresse von BSB-LAN ein. Wenn MDNS aktiviert ist, können Sie direkt zu `http://bsb-lan.local` gehen. Sie finden die IP-Adresse von BSB-LAN entweder in Ihrem Router oder indem Sie den Mikrocontroller mit Ihrem PC verbinden, die Arduino IDE öffnen und zu ***Tools/Serial Monitor*** gehen. Starten Sie den Mikrocontroller neu, und die IP-Adresse wird angezeigt, sobald er mit dem Netzwerk verbunden ist.
1. **Fertig :-)**
---
## Es funktioniert nicht!

Bitte stellen Sie sicher, dass Sie **jeden Eintrag** im [Abschnitt zur Fehlerbehebung](troubleshooting.md) überprüfen, bevor Sie sich an uns wenden!

---
## Warum sehe ich nur so wenige Parameter?

Wenn Sie BSB-LAN zum ersten Mal verwenden, werden Sie feststellen, dass auf der Weboberfläche des Geräts nur sehr wenige Parameter angezeigt werden. Dies liegt daran, dass jeder Modelltyp des Siemens-Controllers, der in Ihrer Heizung verbaut ist, eine andere Gruppe von Parametern unterstützt. Früher habe ich eine Liste von Parametern bereitgestellt, die aus allen möglichen Heizungssystemen gesammelt wurden, aber es stellte sich heraus, dass diese Liste mehrdeutig war oder sogar Fehler enthielt, die wir nicht zuverlässig beheben konnten. Diese Liste ist immer noch in der Release-Version 2.2.x von BSB-LAN verfügbar und kann bei Bedarf von dort kopiert werden.
Es wird jedoch davon abgeraten, da die genannten Mehrdeutigkeiten und Fehler das Risiko bergen, dass die Heizung falsch konfiguriert wird. Stattdessen wird empfohlen, auf die Schaltfläche "**Gerätespezifische Parameterliste**" im Menü von BSB-LAN zu klicken und die generierte Liste an Frederik (bsb(ät)code-it.de) zu senden. Aus dieser Datei kann eine Parameterliste erstellt werden, die genau zu dem Controller Ihrer Heizung passt. Leider kann dieser Prozess noch nicht automatisiert werden, aber zumindest muss er nur einmal durchgeführt werden. Diese Rohdaten enthalten keine Einstellungen oder andere persönliche Daten, sondern nur die Parameterstruktur der Heizung.
Es liegt in meinem eigenen Interesse, diese Parameterlisten schnell zu erstellen und zurückzusenden, aber ich bitte um Ihr Verständnis, wenn es aufgrund von Arbeits- oder Familienverpflichtungen etwas länger dauert.
