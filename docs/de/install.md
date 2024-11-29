# Installation
Die Installation von BSB-LAN umfasst drei Schritte:

1. Installation der Arduino IDE, um die BSB-LAN-Software auf den Mikrocontroller zu flashen
2. Zusammenbau der Hardware-Komponenten
3. Anschluss von BSB-LAN an die Heizungsanlage

## Installation der Arduino IDE und Flashen von BSB-LAN

1. Laden Sie die aktuelle Version von BSB-LAN aus dem Master-Repository [herunter](https://github.com/fredlcore/BSB-LAN/archive/refs/heads/master.zip) und entpacken Sie sie, oder verwenden Sie *git*, um das Repository zu [klonen](https://github.com/fredlcore/BSB-LAN.git).
2. Navigieren Sie zum Ordner BSB_LAN und benennen Sie die folgenden Dateien um:
    - `BSB_LAN_custom_defs.h.default` in `BSB_LAN_custom_defs.h`
    - `BSB_LAN_config.h.default` in `BSB_LAN_config.h`
3. Laden Sie die [Arduino IDE](https://www.arduino.cc/en/software) herunter und installieren Sie sie für Ihr System.
4. Verbinden Sie Ihren Mikrocontroller (ESP32 oder Arduino Due) mit Ihrem Computer und starten Sie die Arduino IDE.
5. Gehen Sie zu ***Tools/Board/Board Manager*** und stellen Sie sicher, dass das Framework für Ihre Platine installiert ist ("esp32 by Espressif Systems" für ESP32-Mikrocontroller, "Arduino SAM Boards (32-bits ARM Cortex-M3) by Arduino" für Arduino Due-Mikrocontroller).
6. Gehen Sie erneut zu ***Tools/Board*** und wählen Sie Ihren Mikrocontroller aus:
    - *ESP32 Dev Module* für den Joy-It ESP32 NodeMCU
    - *Olimex ESP32-EVB* für den ESP32-basierten Olimex EVB
    - *Olime0x ESP32-POE-ISO* für den ESP32-basierten Olimex POE ISO
    - *Arduino Due (Programming Port)* für den Arduino Due. **Verwenden Sie hier NICHT den nativen USB-Port!**
7. Gehen Sie erneut zu ***Tools/Board*** und wählen Sie die richtige Upload-Geschwindigkeit aus (bis zu 460800 für ESP32, 115200 für Arduino Due).
8. [](){#SPIFFS}Für ESP32-basierte Mikrocontroller gehen Sie erneut zu ***Tools/Board*** und wählen Sie "Minimal SPIFFS" als Partitionsschema aus (**verwechseln Sie dies nicht mit dem ähnlichen "Minimal"-Partitionsschema**, das anders ist und in unserem Fall nicht funktioniert). **Wenn Sie das falsche Partitionsschema auswählen, passt die Firmware nicht auf den ESP32!**
9. Gehen Sie zu ***File/Open***, navigieren Sie zum Ordner BSB_LAN und doppelklicken Sie auf `BSB_LAN.ino`. Das Projekt wird geöffnet.
10. Nun können Sie mit der [Konfiguration](configure.md) von BSB-LAN fortfahren.
11. Wenn Sie mit der Konfiguration fertig sind, gehen Sie zu ***Sketch/Upload*** und laden Sie die BSB-LAN-Software auf den Mikrocontroller.

### Nachfolgende Updates auf ESP32-basierten Mikrocontrollern "over the air" (OTA)

Wenn Sie BSB-LAN auf einem ESP32-basierten Mikrocontroller ausführen und Over-the-Air-Updates in den [Einstellungen](configure.md) aktiviert haben, können Sie zukünftige Updates von BSB-LAN mithilfe Ihres Browsers durchführen. Wählen Sie dazu statt *Sketch/Upload* die Option ***Sketch/Export Compiled Binary***. Dadurch wird ein `build`-Ordner in Ihrem BSB-LAN-Ordner erstellt, in dem Sie unter anderem die Datei `BSB_LAN.ino.bin` finden. Öffnen Sie nun [http://bsb-lan.local:8080](http://bsb-lan.local:8080) und wählen und laden Sie diese Datei hoch. Unterbrechen Sie den Upload-Vorgang nicht. Sie können versuchen, BSB-LAN von einem anderen Browser-Fenster aus zu öffnen, um zu sehen, ob der Prozess abgeschlossen ist.
Bitte beachten Sie, dass dies nur für ESP32-basierte Mikrocontroller gilt. Arduinos unterstützen diese Funktionalität nicht.

## Zusammenbau des BSB-LAN-Adapters
Sie können einen fertig montierten Adapter von Frederik (bsb(ät)code-it.de) beziehen oder ihn selbst bauen (siehe Ordner `schematics` für die Schaltpläne). Sobald Sie den BSB-LAN-Adapter haben, müssen Sie ihn nur noch in den Mikrocontroller einstecken. Wenn Sie einen Olimex-Mikrocontroller verwenden, überprüfen Sie doppelt, ob der Adapter wirklich in der Mitte des Steckverbinders sitzt, da er auch dann noch passt, wenn er um eine Pin-Reihe nach links oder rechts versetzt ist.

## Anschluss von BSB-LAN an die Heizungsanlage

Sobald der Mikrocontroller und der BSB-LAN-Adapter fertig sind, führen Sie die folgenden Schritte aus, um BSB-LAN mit der Heizungsanlage zu verbinden:

1. Trennen Sie den Mikrocontroller von Ihrem Computer und schalten Sie Ihre Heizungsanlage aus. Suchen Sie die BSB/LPB/PPS-Anschlüsse. Möglicherweise müssen Sie dazu Ihre Heizungsanlage öffnen. Sehen Sie sich die Liste der [unterstützten Heizungsanlagen](supported_heating_systems.md) an, um eine Vorstellung davon zu bekommen, wo sich die Pins befinden.<br>***Gehen Sie dabei auf eigene Gefahr vor!***<br>***Wenn Sie nicht vorsichtig sind, können Sie Ihre Ausrüstung beschädigen!***<br>**Achten Sie besonders darauf, elektrostatische Entladungen (ESD) zu verhindern, die sowohl BSB-LAN als auch den Heizungsregler zerstören können!**
2. Stecken Sie nun den BSB-LAN-Adapter auf den Mikrocontroller und verbinden Sie den `+` Schraubanschluss mit dem `CL+` (BSB), `DB` (LPB) oder `A6` (PPS, unterschiedliche Bezeichnungen des Steckers sind möglich) Anschluss, und den `-` Schraubanschluss mit dem `CL-` (BSB), `MB` (LPB) oder `M` (PPS) Anschluss. Wenn kein leerer Anschluss vorhanden ist, ist es kein Problem, die Drähte für BSB-LAN an einen bereits "verwendeten" Anschluss anzuschließen, vorausgesetzt, die Drähte werden vorsichtig eingesteckt. Was die Kabel betrifft, so wird von [Siemens](https://sid.siemens.com/v/u/20140) ein (idealerweise abgeschirmtes) verdrilltes Zweileiterkabel empfohlen. Allerdings haben auch einige Benutzer gute Erfahrungen mit einfachem Klingeldraht gemacht, wenn die Entfernungen nicht zu groß sind.
3. [](){#PowerSupply}Nun müssen Sie den Mikrocontroller einschalten. Beachten Sie, dass die Heizungsanlage den Mikrocontroller nicht mit Strom versorgt, auch wenn die LED des BSB-LAN-Adapters leuchtet, wenn Sie ihn mit der Heizungsanlage verbinden. Sie müssen den Mikrocontroller über seinen USB-Anschluss (oder über PoE auf dem Olimex POE-ISO) mit Strom versorgen. Stellen Sie sicher, dass Sie eine stabile Stromversorgung mit mindestens 2 Ampere verwenden. Sobald der Mikrocontroller eingeschaltet ist, schalten Sie die Heizungsanlage ein. Die rote LED des BSB-LAN-Adapters sollte leuchten. Sie sollte gelegentlich blinken.
4. Öffnen Sie nun Ihren Webbrowser und geben Sie die IP-Adresse von BSB-LAN ein. Wenn MDNS aktiviert ist, können Sie direkt zu [`http://bsb-lan.local`](http://bsb-lan.local) gehen. Andernfalls können Sie die IP-Adresse von BSB-LAN entweder in Ihrem Router finden, oder Sie verbinden den Mikrocontroller mit Ihrem PC, öffnen die Arduino IDE, gehen zu ***Tools/Serial Monitor*** und setzen die Geschwindigkeit des seriellen Monitors auf 115200. Starten Sie den Mikrocontroller neu, und die IP-Adresse wird angezeigt, sobald er mit dem Netzwerk verbunden ist.

## Generieren der gerätespezifischen Parameterliste

Wenn Sie BSB-LAN zum ersten Mal aufrufen, werden Sie feststellen, dass auf der Weboberfläche des Geräts nur sehr wenige Parameter angezeigt werden. Dies liegt daran, dass jedes Modell des Siemens-Reglers, der in Ihre Heizungsanlage eingebaut ist, eine andere Gruppe von Parametern unterstützt. Früher habe ich eine Liste von Parametern bereitgestellt, die aus allen möglichen Heizungsanlagen gesammelt wurden, aber es stellte sich heraus, dass diese Liste mehrdeutig war oder sogar Fehler enthielt, die wir nicht zuverlässig beheben konnten. Diese Liste ist immer noch in der Release-Version 2.2.x von BSB-LAN verfügbar und kann bei Bedarf von dort kopiert werden.
Es wird jedoch davon abgeraten, dies zu tun, da die genannten Mehrdeutigkeiten und Fehler das Risiko bergen, die Heizungsanlage falsch zu konfigurieren. Stattdessen wird empfohlen, auf die Schaltfläche "**Gerätespezifische Parameterliste**" im Menü von BSB-LAN zu klicken und die generierte Liste an Frederik (bsb(ät)code-it.de) zu senden. Aus dieser Datei kann eine Parameterliste erstellt werden, die genau zu dem Regler Ihrer Heizungsanlage passt. Leider kann dieser Prozess noch nicht automatisiert werden, aber zumindest muss er nur einmal durchgeführt werden. Diese Rohdaten enthalten keine Einstellungen oder andere Arten von persönlichen Daten, sondern nur die Parameterstruktur der Heizungsanlage.
Es liegt in meinem eigenen Interesse, diese Parameterlisten ohne Verzögerung zu erstellen und zurückzusenden, aber ich bitte um Ihr Verständnis, wenn es aufgrund von Arbeits- oder Familienverpflichtungen etwas länger dauert.

Sobald Sie die Parameterliste erhalten haben (oder die aus Version 2.2.x genommen haben), müssen Sie die vorhandene Datei `BSB_LAN_custom_defs.h` durch die an Sie gesendete Datei ersetzen, sie kompilieren und erneut flashen. Nun können Sie auf alle Parameter zugreifen.