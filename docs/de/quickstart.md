# Schnellstart-Anleitung

Diese Kurzanleitung ist für Nutzer gedacht, die Erfahrung mit der Installation und Konfiguration von Software auf ihrem Computer haben. Wenn du detailliertere Anweisungen benötigst, wirf bitte einen Blick in die [Installationsanweisungen](install.md)!

1. Stelle sicher, dass deine Heizung mit BSB-LAN [kompatibel](supported_heating_systems.md) ist!
1. [Lade](https://github.com/fredlcore/BSB-LAN/archive/refs/heads/master.zip) die aktuelle BSB-LAN Version aus dem Master Repository herunter und entpacke sie, oder verwende *git* um das [Repository zu klonen](https://github.com/fredlcore/BSB-LAN.git).
1. Navigiere zum BSB_LAN Ordner und benenne die folgenden Dateien um:
    1. `BSB_LAN_custom_defs.h.default` in `BSB_LAN_custom_defs.h`
    1. `BSB_LAN_config.h.default` in `BSB_LAN_config.h`
1. [Lade](https://www.arduino.cc/en/software) die Arduino IDE für dein System herunter und installiere sie.
1. Verbinde deinen Mikrocontroller (ESP32 oder Arduino Due) mit deinem Computer und starte die Arduino IDE.
1. Gehe zu ***Tools/Board/Board Manager*** und stelle sicher, dass das Framework für deine Platine installiert ist ("esp32 by Espressif Systems" für ESP32 Mikrocontroller, "Arduino SAM Boards (32-bits ARM Cortex-M3) by Arduino" für Arduino Due Mikrocontroller)
1. Gehe wieder zu ***Tools/Board*** und wähle deinen Mikrocontroller aus:
    1. *ESP32 Dev Module* für den Joy-It ESP32 NodeMCU.
    1. *Olimex ESP32-EVB* für den ESP32-basierten Olimex EVB.
    1. *Olimex ESP32-POE-ISO* für den ESP32-basierten Olimex POE ISO
    1. *Arduino Due (Programming Port)* für den Arduino Due. **Verwende hier nicht den nativen USB Port!**
1. Gehe jetzt zu ***Tools*** und wähle den passenden Port aus, an den der Microcontroller angeschlossen ist.
1. Gehe wieder zu ***Tools*** und wähle die richtige Upload-Geschwindigkeit aus (bis zu 460800 für ESP32, 115200 für Arduino Due).
1. Für ESP32-basierte Mikrocontroller, gehe wieder zu ***Tools/Partition Scheme*** und wähle "Minimal SPIFFS" als Partitionsschema aus (**verwechsele dies nicht mit dem ähnlichen "Minimal" Partitionsschema**, welches anders ist und in unserem Fall nicht funktioniert). **Wenn du das falsche Partitionsschema auswählst, passt die Firmware nicht auf den ESP32!**
1. Gehe zu ***File/Open*** und navigiere zum BSB_LAN Ordner, doppelklicke dann auf `BSB_LAN.ino`. Das Projekt wird geöffnet.
1. Klicke auf die Registerkarte mit dem Dateinamen `BSB_LAN_config.h` und konfiguriere mindestens Folgendes:
    1. Suche nach `#define LANG DE`: Ändere `DE` zu `EN` für Englisch, `FR` für Französisch usw.
    1. Suche nach `uint8_t network_type`: Setze dies auf `LAN`, wenn du eine Ethernet/LAN Verbindung verwendest. Setze es auf `WLAN`, wenn du eine WiFi/WLAN Verbindung verwendest.
    1. Wenn du DHCP nicht verwendest, konfiguriere die folgenden Optionen entsprechend deinem Netzwerk (stelle sicher, dass du ein Komma anstelle eines Punkts für IP-Adressen verwendest!):
        1. `byte ip_addr[4] = {192,168,178,88};`
        1. `byte gateway_addr[4] = {192,168,178,1};`
        1. `byte dns_addr[4] = {192,168,178,1};`
        1. `byte subnet_addr[4] = {255,255,255,0};`
        1. `char wifi_ssid[32] = "Your_Wifi_network_name";`
        1. `char wifi_pass[32] = "Your_WiFi_network_password";`
1. Klicke jetzt auf ***Sketch/Upload***, um die BSB-LAN Software auf den Mikrocontroller zu laden. Bei ESP32 Microcontrollern ist die Meldung "Hard resetting via RTS pin..." **keine** Fehlermeldung, sondern bedeutet, dass der Upload erfolgreich war und der ESP32 nun neu gestartet wird.
1. Trenne den Mikrocontroller und schalte deine Heizung aus. Suche die BSB/LPB/PPS Anschlüsse. Möglicherweise musst du dazu deine Heizung öffnen. ***Du machst all dies auf eigene Gefahr!***
1. Verbinde jetzt den BSB-LAN Adapter mit dem Mikrocontroller und verbinde den `+` Schraubanschluss mit dem `CL+` (BSB), `DB` (LPB) oder `A6` (PPS, andere Bezeichnungen sind möglich) Anschluss, und den `-` Schraubanschluss mit dem `CL-` (BSB), `MB` (LPB) oder `M` (PPS) Anschluss.
1. Schalte den Mikrocontroller über den USB-Port oder PoE (nur Olimex POE-ISO) ein. Schalte dann die Heizung ein. Die rote LED des BSB-LAN Adapters sollte leuchten. Sie sollte gelegentlich blinken.
1. Öffne jetzt deinen Webbrowser und gib die IP-Adresse von BSB-LAN ein. Wenn MDNS aktiviert ist, kannst du direkt zu `http://bsb-lan.local` gehen. Du findest die IP-Adresse von BSB-LAN entweder in deinem Router oder du verbindest den Mikrocontroller mit deinem PC, öffnest die Arduino IDE und gehst zu ***Tools/Serial Monitor***. Starte den Mikrocontroller neu, und die IP-Adresse wird angezeigt, sobald er mit dem Netzwerk verbunden ist.
1. **Fertig :-)**

---

## Es funktioniert nicht!

Bitte stelle sicher, dass du jeden Eintrag in der [Troubleshooting-Sektion](troubleshooting.md) überprüft hast, bevor du dich an uns wendest!

---

## Warum sehe ich nur so wenige Parameter?

Wenn du BSB-LAN zum ersten Mal verwendest, wirst du feststellen, dass auf der Weboberfläche des Geräts nur sehr wenige Parameter angezeigt werden. Das liegt daran, dass jeder Modelltyp des Siemens-Controllers, der in deine Heizung eingebaut ist, eine andere Gruppe von Parametern unterstützt. Früher habe ich eine Liste von Parametern bereitgestellt, die aus allen möglichen Heizungssystemen gesammelt wurden, aber es stellte sich heraus, dass diese Liste mehrdeutig war oder sogar Fehler enthielt, die wir nicht zuverlässig beheben konnten. Diese Liste ist immer noch in der Release-Version 2.2.x von BSB-LAN verfügbar und kann bei Bedarf von dort kopiert werden.

Es wird jedoch davon abgeraten, dies zu tun, da die genannten Mehrdeutigkeiten und Fehler das Risiko bergen, die Heizung falsch zu konfigurieren. Stattdessen wird empfohlen, auf den Knopf "**Gerätespezifische Parameterliste**" in BSB-LANs Menü zu klicken und die generierte Liste an Frederik (bsb(ät)code-it.de) zu senden. Aus dieser Datei kann eine Parameterliste erstellt werden, die genau zu dem Controller deiner Heizung passt. Leider kann dieser Prozess noch nicht automatisiert werden, aber immerhin muss er nur einmal durchgeführt werden. Diese Rohdaten enthalten keine Einstellungen oder andere persönliche Daten, sondern nur die Parameterstruktur deiner Heizung.

Es liegt in meinem eigenen Interesse, diese Parameterlisten schnell zu erstellen und zurückzusenden, aber ich bitte um Verständnis, wenn es aufgrund von Arbeit oder familiären Verpflichtungen etwas länger dauert.  
Wenn Du die Datei erhalten hast (oder die aus der Release-Version 2.2.x übernommen hast), ersetzt Du damit einfach die gleichnamige Datei im Ordner `BSB_LAN` und wiederholst die Schritte zum Flashen der Software wie oben beschrieben.
