# Installation

Die Installation von BSB-LAN besteht aus drei Schritten:

1. Installation der Arduino IDE, um die BSB-LAN-Software auf den Mikrocontroller zu flashen
2. Zusammenbau der Hardware-Komponenten
3. Anschluss von BSB-LAN an die Heizung

## Installation der Arduino IDE und Flashen von BSB-LAN

1. Lade die aktuelle Version von BSB-LAN aus dem Master-Repository herunter [Download](https://github.com/fredlcore/BSB-LAN/archive/refs/heads/master.zip) und entpacke sie, oder verwende *git*, um das Repository zu klonen [clone](https://github.com/fredlcore/BSB-LAN.git).
2. Navigiere zum BSB_LAN-Ordner und benenne die folgenden Dateien um:
    1. `BSB_LAN_custom_defs.h.default` in `BSB_LAN_custom_defs.h`
    2. `BSB_LAN_config.h.default` in `BSB_LAN_config.h`
3. Lade die Arduino IDE für dein System herunter [Download](https://www.arduino.cc/en/software) und installiere sie.
4. Verbinde deinen Mikrocontroller (ESP32 oder Arduino Due) mit deinem Computer und starte die Arduino IDE.
5. Gehe zu ***Tools/Board/Board Manager*** und stelle sicher, dass das Framework für deine Platine installiert ist ("esp32 by Espressif Systems" für ESP32-Mikrocontroller, "Arduino SAM Boards (32-bits ARM Cortex-M3) by Arduino" für Arduino Due-Mikrocontroller)
6. Gehe wieder zu ***Tools/Board*** und wähle deinen Mikrocontroller aus:
    1. *ESP32 Dev Module* für den Joy-It ESP32 NodeMCU.
    2. *Olimex ESP32-EVB* für den ESP32-basierten Olimex EVB.
    3. *OlimeMultiplier-ESP32-POE-ISO* für den ESP32-basierten Olimex POE ISO
    4. *Arduino Due (Programming Port)* für den Arduino Due. **Verwende hier nicht den nativen USB-Port!**
7. Gehe wieder zu ***Tools/Board*** und wähle die richtige Upload-Geschwindigkeit aus (bis zu 460800 für ESP32, 115200 für Arduino Due).
8. [](){#SPIFFS}Für ESP32-basierte Mikrocontroller, gehe wieder zu ***Tools/Board*** und wähle "Minimal SPIFFS" als Partitionsschema aus (**verwechsle dies nicht mit dem ähnlichen "Minimal"-Partitionsschema**, das anders ist und in unserem Fall nicht funktioniert). **Wenn du das falsche Partitionsschema auswählst, passt die Firmware nicht auf den ESP32!**
9. Gehe zu ***File/Open***, navigiere zum BSB_LAN-Ordner und doppelklicke auf `BSB_LAN.ino`. Das Projekt wird geöffnet.
10. Du kannst jetzt mit der [Konfiguration](configure.md) von BSB-LAN fortfahren.
11. Wenn du mit der Konfiguration fertig bist, gehe zu ***Sketch/Upload*** und lade die BSB-LAN-Software auf den Mikrocontroller.

### Nachfolgende Updates auf ESP32-basierten Mikrocontrollern "over the air" (OTA)

Wenn du BSB-LAN auf einem ESP32-basierten Mikrocontroller ausführst und Over-the-Air-Updates in den [Einstellungen](configure.md) aktiviert hast, kannst du zukünftige Updates von BSB-LAN mit deinem Browser durchführen. Wähle statt *Sketch/Upload* ***Sketch/Export Compiled Binary*** aus. Dadurch wird ein `build`-Ordner in deinem BSB-LAN-Ordner erstellt, in dem du unter anderem die Datei `BSB_LAN.ino.bin` findest. Öffne jetzt [http://bsb-lan.local:8080](http://bsb-lan.local:8080) und wähle die Datei zum Hochladen aus. Unterbreche den Upload-Prozess nicht. Du kannst versuchen, BSB-LAN in einem anderen Browser-Fenster zu öffnen, um zu sehen, ob der Prozess abgeschlossen ist.
Bitte beachte, dass dies nur für ESP32-basierte Mikrocontroller gilt. Arduinos unterstützen diese Funktion nicht.

## Zusammenbau des BSB-LAN-Adapters

Du kannst einen fertig montierten Adapter von Frederik (bsb(ät)code-it.de) beziehen oder ihn selbst bauen (siehe Ordner `schematics` für die Schaltpläne). Sobald du den BSB-LAN-Adapter hast, musst du ihn nur noch in den Mikrocontroller stecken. Wenn du einen Olimex-Mikrocontroller verwendest, überprüfe doppelt, ob der Adapter wirklich mittig auf dem Connector sitzt, da er auch dann noch passt, wenn er um eine Pin-Reihe nach links oder rechts versetzt ist.

## Anschluss von BSB-LAN an die Heizung

Sobald der Mikrocontroller und der BSB-LAN-Adapter fertig sind, führe die folgenden Schritte aus, um BSB-LAN mit der Heizung zu verbinden:

1. Trenne den Mikrocontroller von deinem Computer und schalte deine Heizung aus. Suche die BSB/LPB/PPS-Anschlüsse. Möglicherweise musst du dazu deine Heizung öffnen. Schaue in der Liste der [unterstützten Heizungssysteme](supported_heating_systems.md) nach, um eine Vorstellung davon zu bekommen, wo sich die Pins befinden.<br>***All dies geschieht auf eigene Gefahr!***<br>***Wenn du nicht vorsichtig bist, könntest du deine Ausrüstung beschädigen!***<br>**Achte besonders darauf, elektrostatische Entladungen (ESD) zu verhindern, die sowohl BSB-LAN als auch den Heizungsregler zerstören können!**
2. Stecke jetzt den BSB-LAN-Adapter auf den Mikrocontroller und verbinde den `+` Schraubanschluss mit dem `CL+` (BSB), `DB` (LPB) oder `A6` (PPS, andere Connector-Namen sind möglich) Connector, und den `-` Schraubanschluss mit dem `CL-` (BSB), `MB` (LPB) oder `M` (PPS) Connector. Wenn es keinen leeren Connector gibt, ist es kein Problem, die Drähte für BSB-LAN an einen bereits "verwendeten" Connector anzuschließen, solange die Drähte vorsichtig eingesteckt werden. Bei den Kabeln wird ein (idealerweise abgeschirmtes) verdrilltes Zweileiterkabel empfohlen [von Siemens](https://sid.siemens.com/v/u/20140). Allerdings haben auch einige Benutzer gute Erfahrungen mit einfachem Klingeldraht gemacht, solange die Distanzen nicht zu lang sind.
3. [](){#PowerSupply}Jetzt musst du den Mikrocontroller einschalten. Beachte, dass die Heizung den Mikrocontroller nicht mit Strom versorgt, auch wenn die LED des BSB-LAN-Adapters leuchtet, wenn du ihn mit der Heizung verbindest. Du musst den Mikrocontroller über seinen USB-Port (oder über PoE auf dem Olimex POE-ISO) mit Strom versorgen. Verwende eine stabile Stromversorgung mit mindestens 2 Ampere. Sobald der Mikrocontroller eingeschaltet ist, schalte die Heizung ein. Die rote LED des BSB-LAN-Adapters sollte leuchten. Sie sollte gelegentlich blinken.
4. Öffne jetzt deinen Webbrowser und gib die IP-Adresse von BSB-LAN ein. Wenn MDNS aktiviert ist, kannst du direkt zu [`http://bsb-lan.local`](http://bsb-lan.local) gehen. Andernfalls kannst du die IP-Adresse von BSB-LAN entweder in deinem Router finden, oder du verbindest den Mikrocontroller mit deinem PC, öffnest die Arduino IDE, gehst zu ***Tools/Serial Monitor*** und setzt die Geschwindigkeit des seriellen Monitors auf 115200. Starte den Mikrocontroller neu, und die IP-Adresse wird angezeigt, sobald er mit dem Netzwerk verbunden ist.

## Generieren der gerätespezifischen Parameterliste

Wenn du BSB-LAN zum ersten Mal öffnest, wirst du feststellen, dass auf der Weboberfläche des Geräts nur sehr wenige Parameter angezeigt werden. Dies liegt daran, dass jedes Modell des Siemens-Reglers, der in deine Heizung eingebaut ist, eine andere Gruppe von Parametern unterstützt. Früher habe ich eine Liste von Parametern bereitgestellt, die aus allen möglichen Heizungssystemen gesammelt wurden, aber es stellte sich heraus, dass diese Liste mehrdeutig war oder sogar Fehler enthielt, die wir nicht zuverlässig beheben konnten. Diese Liste ist immer noch in der Release-Version 2.2.x von BSB-LAN verfügbar und kann bei Bedarf von dort kopiert werden.
Es wird jedoch davon abgeraten, dies zu tun, da die genannten Mehrdeutigkeiten und Fehler das Risiko bergen, die Heizung falsch zu konfigurieren. Stattdessen wird empfohlen, auf den Button "**Gerätespezifische Parameterliste**" im Menü von BSB-LAN zu klicken und die generierte Liste an Frederik (bsb(ät)code-it.de) zu senden. Aus dieser Datei kann eine Parameterliste erstellt werden, die genau zu dem Regler deiner Heizung passt. Leider kann dieser Prozess noch nicht automatisiert werden, aber immerhin muss er nur einmal durchgeführt werden. Diese Rohdaten enthalten keine Einstellungen oder andere persönliche Daten, sondern nur die Parameterstruktur der Heizung.
Es liegt in meinem eigenen Interesse, diese Parameterlisten schnell zu erstellen und zurückzusenden, aber ich bitte um Verständnis, wenn es aufgrund von Arbeits- oder Familienverpflichtungen etwas länger dauert.

Sobald du die Parameterliste erhalten hast (oder die aus Version 2.2.x genommen hast), musst du die vorhandene `BSB_LAN_custom_defs.h` Datei durch die gesendete ersetzen, sie kompilieren und wieder flashen. Jetzt kannst du auf alle Parameter zugreifen.
