#ChangeLog#

##Aktueller Master##

- **ACHTUNG: Breaking Change!** Vereinfachte Themestruktur für MQTT. Die neue Struktur fügt `/status` zum Abfragen eines Parameters, `/set` zum SETzen eines Parameters, `/inf` zum Senden von Daten als INF-Telegramm und `/poll` hinzu, um BSB-LAN dazu zu zwingen, ein Update des Parameterwerts an den Broker zu senden. Wenn du MQTT Auto-Discovery verwendest, sollte das Aufrufen von `/M1` idealerweise diese Änderungen aktualisieren. Wenn du jedoch deine eigenen Konfigurationen verwendest, musst du hier Anpassungen vornehmen.
- **ACHTUNG: Breaking Change!** Wenn du JSON-Einstellungen für MQTT verwendest, wurden zuvor alle Nachrichten an `BSB-LAN/json` geschrieben und damit im Grunde sofort überschrieben, wenn mehrere Parameter protokolliert wurden. Jetzt bestimmt diese Einstellung nur das Format (und nicht Format und Thema) der Daten, die in `/status` jedes Parameters geschrieben werden. Für die automatische Erkennung bleibt Plain Text die einzige gültige Wahl.
- **ACHTUNG: Breaking Change** Die Bestätigungsmeldung, die von BSB-LAN an das `MQTT`-Thema gesendet wurde, wurde entfernt. Stattdessen wurde die QoS für das Veröffentlichen von Nachrichten auf Ebene 1 festgelegt.
- **ACHTUNG: Breaking Change:** Die Log-Konfigurationswerte haben sich geändert. Allerdings sind nur Benutzer betroffen, die sich bei UDP angemeldet haben und ihre Einstellungen anpassen müssen.
- Hinzugefügte Einstellung, um nur Protokollparameter an MQTT zu veröffentlichen. Das Erzwingen von MQTT-Updates über das `/poll`-Thema ist weiterhin möglich.
- Hinzugefügter `state_class` für nicht kumulative Sensoren in MQTT Auto-Discovery
- Aktualisierte Raum-Einheit-Emulation in `custom_functions`, um mit Version 4.x zu funktionieren
- Fehlerbehebung für `VT_ENERGY`, neuer Datentyp `VT_ENERGY10` und `VT_ENERGY10_N` hinzugefügt

##Version 4.1##
**06.11.2024**

- **ACHTUNG: Breaking Change!** Geänderte Themestruktur für MQTT. Das bedeutet, dass alle vorhandenen MQTT-Entitäten in deinem Home-Automation-System angepasst oder neu erstellt werden müssen! Die neue Struktur lautet jetzt `BSB-LAN/<device id>/<category id>/<parameter number>`.
- **ACHTUNG: Breaking Change!** Geänderte `unique_id` für MQTT Auto-Discovery. Das bedeutet, dass alle MQTT-Entitäten, die über die automatische Erkennung erstellt wurden, neu erstellt werden müssen!
- **ACHTUNG:** Die Konfigurationsoptionen `fixed_device_family` und `fixed_device_variant` wurden entfernt, da sie nicht mehr mit gerätespezifischen Parameterlisten funktionieren. Wenn dein Heizsystem ausgeschaltet ist, wenn du den Mikrocontroller einschaltest, wird BSB-LAN alle 60 Sekunden versuchen, die Details abzurufen.
- **ACHTUNG:** Änderung der Konfigurationsoptionen führt zu einem neuen EEPROM-Layout, daher wird das EEPROM basierend auf der Konfiguration von `BSB_LAN_config.h` neu initialisiert.
- MQTT Auto-Discovery funktioniert jetzt für alle Geräte, nicht nur für Geräte-ID 0. Verwende `/M1!<x>` oder `/M0!<x>`, um Entitäten für Geräte-ID `<x>` zu erstellen/entfernen.
- Geänderte MQTT Auto-Discovery-Nachrichten-Flag auf "beibehalten", damit Parameter nach einem Neustart von Home Assistant verfügbar bleiben.

##Version 4.0##
**01.11.2024**

- **ACHTUNG: Breaking Change!** Der Raumtemperaturparameter 10000, 10001 und 10002 muss jetzt die zusätzliche Flagge `FL_SPECIAL_INF` haben, sonst funktioniert das Einstellen der Temperatur nicht!
- **ACHTUNG: Breaking Change!** Der Außentemperatur-Simulations-Parameter 10017 muss die `FL_SPECIAL_INF`-Flagge entfernen, sonst funktioniert das Einstellen der Temperatur nicht!
- **ACHTUNG: Breaking Change!** Der Raumtemperaturparameter 10000, 10001 und 10002 für Weishaupt-Heizgeräte (Gerätefamilien 49, 50, 51 und 59) müssen jetzt die `FL_SPECIAL_INF`-Flagge entfernen, sonst funktioniert das Einstellen der Temperatur nicht!
- **ACHTUNG: Breaking Change!** Die URL-Befehle `/U` (Anzeige benutzerdefinierter Variablen) und `/X` (Anzeige MAX! Werte) wurden entfernt, da diese Werte jetzt über die Parameter 20000++ abgerufen werden können
- **ACHTUNG: Breaking Change!** Die PPS-Zeitprogrammparameter (15050-15091) wurden mit den BSB/LPB-Zeitprogrammparametern gestrafft, was zu einem Parameter pro Tag (anstatt sechs) führt, der drei Schaltpunkte (Start und Ende) pro Parameter abdeckt.
- **ACHTUNG:** Für ESP32 erfordert BSB-LAN die ESP32-Framework-Version 3.0.x - achte auf Fehler oder seltsames Verhalten (1-Wire-Sensoren sind noch nicht getestet) sowie jegliches andere seltsame Verhalten/Abstürze.
- **ACHTUNG:** Neue Konfigurationsoptionen in `BSB_LAN_config.h` - aktualisiere deine bestehenden Konfigurationsdateien! Die webbasierte Konfiguration wird aufgrund der Änderung des EEPROM-Layouts durch die Einstellungen der Konfigurationsdatei überschrieben!
- **ACHTUNG:** Neues Handbuch-URL: https://docs.bsb-lan.de/
- BUTTONS und `RGT_EMULATION` wurden aus dem Hauptcode in die `custom_functions`-Bibliothek verschoben. Um sie weiterhin zu verwenden, nutze die Dateien `BSB_LAN_custom_*.h` und aktiviere die `CUSTOM_COMMANDS`-Definition.
- Die meisten Konfigurationsdefinitionen wurden aus `BSB_LAN_config.h` entfernt. Fast alle Funktionen können jetzt ohne erneutes Flashen konfiguriert werden.
- BSB-LAN unterstützt jetzt MQTT Auto Discovery (unterstützt z. B. von Home Assistant). Um Geräte zu erstellen, rufe den URL-Befehl `/M1` auf, um sie zu entfernen, rufe `/M0` auf.
- **ACHTUNG:** MQTT Auto Discovery erstellt einen allgemeinen Schalter für das BSB-LAN-Gerät in Home Assistant. Dieser Schalter wird sofort alle Parameter mit den in Home Assistant gespeicherten Werten schreiben. VERWENDE DIESEN SCHALTER NICHT, es sei denn, du weißt wirklich, was er tut!
- Die Schaltfläche "Set" in der Weboberfläche funktioniert jetzt auch mit nicht standardmäßigen Zielgeräten (d. h. 1 anstelle von 0)
- Abgefragte/gesetzte Parameter werden jetzt an den MQTT-Broker weitergeleitet (sofern MQTT aktiviert ist)
- Die zuvor verwendeten `/M1` und `/M0` zum Umschalten der Monitorfunktion wurden entfernt, da sie jetzt über die Konfiguration in der Weboberfläche zugänglich sind.
- Das Auflisten von Kategorien mit `/K` funktioniert jetzt auch mit dem Zielgerät (z. B. `/K!1` für Zielgerät 1, Standard ist 0).
- Wichtiger Fehlerbehebung für OTA-Update: Vorherige Versionen hatten eine harte Begrenzung der Dateigröße, die bei neueren Heizsystemen mit mehreren hundert Parametern erreicht wurde, so dass kein OTA-Update möglich war. Dies ist jetzt behoben, aber betroffene Benutzer müssen ein USB-basiertes Update noch einmal durchführen.
- 1-Wire- und DHT-Sensoren werden jetzt mit dem Wert -1 anstelle von 0 deaktiviert. In der Weboberfläche wird auch ein leeres Feld akzeptiert.
- MQTTTopicPrefix ist nicht mehr optional, das Thema "fromBroker" wurde entfernt (früher zum Senden von Befehlen an BSB-LAN über MQTT verwendet)
- Die Verwendung der 24-Stunden-Durchschnittsfunktion erfordert jetzt nicht mehr die Verwendung einer SD-Karte. Die SD-Karte wird nur verwendet, um Durchschnittswerte zu speichern, wenn die intervallbasierte Protokollierung auf die SD-Karte aktiviert ist.
- Neue PPS-Raum-Einheit-Variante für RVD130, die das obere Nibble des Magic Byte bei jeder Transaktion erhöht.
- Das Abrufen der aktuellen Uhrzeit von einem NTP-Server ist standardmäßig aktiviert. Deaktivieren Sie es, indem Sie `ntp_server` auf eine leere Zeichenfolge setzen.
- Neue Parameterflagge `FL_NOSWAP_QUR` für Parameter, die das erste und zweite Byte der Befehls-ID in QUR-Telegrammen nicht vertauschen
- Neue Parameterflagge `FL_FORCE_INF` für Parameter, von denen wir sicher sind, dass sie nur mit INF funktionieren (wie z.B. Raumtemperatur). Erzwingt ein INF-Telegramm, auch wenn `/S` verwendet wird, um den Parameter zu setzen (ermöglicht das Einstellen der Raumtemperatur über die Weboberfläche)
- BSB-LAN-Logo-Wasserzeichen in der Log-Graph-Anzeige (DE-cr)
- Binäre ENUMs (ja/nein, ein/aus usw.) geben jetzt beim Abfragen entweder 0 oder 1 zurück, nicht - wie bei einigen Heizsystemen - 0 oder 255. Das Setzen eines beliebigen Werts von 1 bis 255 ist weiterhin möglich.
- Behebung eines kritischen Fehlers in PPS, der ein ordnungsgemäßes Funktionieren im aktiven/Raum-Einheit-Modus verhinderte.
- Fehlerbehebung (oder, je nach Perspektive, verringerte Sicherheit), die das Senden von Befehlen über die serielle/Telnet-Konsole verhinderte, wenn die HTTP-Authentifizierung aktiv war
- Verschiedene Fehlerbehebungen, darunter die Protokollierung von Bus-Telegrammen auf dem Speichergerät.
- Neue OneWireNg-Bibliotheksversion
- Diese Version wurde von den folgenden Sponsoren unterstützt: Erich Scheilko

##Version 3.3##
**12.03.2024**

- **ACHTUNG:** Neue Konfigurationsoptionen in `BSB_LAN_config.h` - aktualisiere deine bestehenden Konfigurationsdateien!
- ESP32: Unterstützung für den Empfang von Datum und Uhrzeit über NTP anstelle der Entnahme aus der Heizung.
- Die MQTT-Broker-Einstellung akzeptiert jetzt Domain-Namen sowie IP-Adressen. Ein optionaler Port kann nach einem abschließenden Doppelpunkt hinzugefügt werden, z. B. broker.my-domain.com:1884. Andernfalls wird standardmäßig 1883 verwendet.
- ESP32 NodeMCU: Unterstützung für einen optionalen zusätzlichen SD-Kartenadapter. Die SPI-Pins können in `BSB_LAN_config.h` konfiguriert werden, standardmäßig auf die Standard-SPI-Pins 5, 18, 19 und 23.
- ESP32: Wechsel zwischen Log-Speichergerät (SD-Karte / interner Flash) kann jetzt in der Weboberfläche erfolgen.
- ESP32: Erstellen Sie ein temporäres WiFi-AP, falls die Ethernet-Verbindung fehlschlägt
- ESP32 NodeMCU: Der EEPROM-Clear-Pin wurde von 18 auf 21 geändert, um keine Kollisionen mit SPI-SD-Kartenadaptern zu verursachen.
- Diese Version wurde von den folgenden GitHub-Sponsoren unterstützt: jsimon3

##Version 3.2##
**15.11.2023**

- **ACHTUNG:** In `BSB_LAN_config.h` wurde das Layout von `log_parameters`, `avg_parameters` und `ipwe_parameters` in geschweifte Klammern geschrieben und die Größe (40 statt 80) und der Typ (`parameter` statt `float`) geändert. Aktualisiere deine `BSB_LAN_config.h` entsprechend, um Fehler zu vermeiden!
- Hinzugefügte Versionskontrolle von Konfigurationsdateien, um die Verwendung veralteter Konfigurationsdateien mit neueren Softwareversionen zu verhindern.
- Die Variable `esp32_save_energy` ist jetzt standardmäßig deaktiviert, da sie nur sinnvoll erscheint, wenn eine LAN-Verbindung verwendet wird oder wenn du WiFi verwendest und mit der Leistungseinbuße leben kannst.
- Hinzugefügter Ordner `custom_functions`, in dem Codebeispiele für nützliche Funktionen gesammelt werden, die dennoch zu spezifisch sind, um sie zum BSB-LAN-Kerncode hinzuzufügen.
- Hinzugefügtes benutzerdefiniertes Funktionsbeispiel für die Zuordnung von DS18B20-Sensoren zu festen benutzerdefinierten Float-Parametern
- Diese Version wurde von den folgenden GitHub-Sponsoren unterstützt: BraweProg, fdobrovolny, Harald

##Version 3.1##
**04.06.2023**

- **ACHTUNG:** Für ESP32-Geräte, die den internen Flash-Speicher für die Protokollierung verwenden: Das Dateisystem wurde von SPIFFS auf LittleFS umgestellt. Lade vor dem Update wichtige Protokolldaten herunter!
- **ACHTUNG:** In `BSB_LAN_config.h` wurde die Struktur von `log_parameters`, `avg_parameters` und `ipwe_parameters` geändert und umfasst jetzt das Zielgerät auf dem Bus!
- **ACHTUNG:** Das neue EEPROM-Schema kann zu einem Verlust der Web-Konfigurationseinstellungen führen, wenn es aktualisiert wird. Notiere dir deine Einstellungen, bevor du aktualisierst!
- **ACHTUNG:** Neue Variable `esp32_save_energy` in `BSB_LAN_config.h` - aktualisiere sie, bevor du die neue Version kompilierst.
- **ACHTUNG:** Neue Variable `bssid` in `BSB_LAN_config.h` - definiert eine feste BSSID-Adresse, mit der eine Verbindung hergestellt werden soll, wenn WiFi auf ESP32 verwendet wird.
- Parameter können jetzt auch beim Protokollieren (einschließlich MQTT) oder beim Verwenden von Durchschnitts- oder IPWE-Parametern von anderen Geräten auf dem Bus mithilfe der !-Notation abgefragt werden
- Aktivieren/Deaktivieren der Energiesparfunktion auf ESP32. Spart 20% Energie, kann aber Auswirkungen auf die WiFi-Reichweite und die Downloadgeschwindigkeit von Protokolldateien haben, wenn WiFi verwendet wird (LAN ist nicht betroffen)
- Verbesserte Leistung und Flash-Speichernutzung auf ESP32-Geräten, die den internen Flash-Speicher für die Protokollierung verwenden, aufgrund des Wechsels von SPIFFS zu LittleFS
- Um die Handhabung großer Datenprotokolle zu verbessern: Datumsbereichsauswahl in `/DG`, neue URL-Befehle `/Da,b`, `/DA`, `/DB`, `/Dn`, `/DI` und `/DKn`
- Diese Version wurde von den folgenden GitHub-Sponsoren unterstützt: lapixo, nrobadey

##Version 3.0##
**16.03.2023**

- **ACHTUNG:** `BSB_LAN_custom_defs.h`.default muss in `BSB_LAN_custom_defs.h` umbenannt werden und enthält standardmäßig nur eine sehr begrenzte Anzahl von Parametern. Siehe Handbuch, um gerätespezifische Parameterlisten zu erhalten.
- Füge den neuen URL-Befehl `/LN` hinzu, um die Protokollierung unabhängig vom aktuellen Intervall zu erzwingen.
- Verbesserte Bibliotheksprüfungen: ESP32-Benutzer müssen die ArduinoMDNS- und WiFiSpi-Ordner nicht mehr entfernen.
- Neue SdFat-Version 2 für Arduino Due
- Neuer Datentyp `VT_BINARY_ENUM`
- Diese Version wurde von den folgenden GitHub-Sponsoren unterstützt: Alex, DE-cr

##Version 2.2##
**01.11.2022**

- **ACHTUNG:** Mehrere Variablen in `BSB_LAN_config.h`.default haben ihren Variablentyp geändert, es ist wahrscheinlich am besten, deine `BSB_LAN_config.h` von Grund auf neu zu erstellen.
- Parameternummern sind jetzt Gleitkommazahlen (d. h. XXXX.Y), da einige Parameter zwei verschiedene Arten von Informationen enthalten. Diese werden jetzt in Dezimalzahlen mit 0,1 Inkrementen angezeigt. Du kannst den "Haupt"-Parameter immer noch über XXXX (ohne .Y) abfragen
- Viele Fehlerbehebungen und neue Datentypen
- Gerätespezifische Parameterlisten werden unterstützt

##Version 2.1##
**30.07.2022**

- Viele neue Parameter für LMU64
- **ACHTUNG:** Neue Kategorien für LMU64- und RVD/RVP-Controller aufgrund ihrer unterschiedlichen Nummerierungsschemata. Wird mit der Zeit gefüllt. Die PPS- und Sensorkategorien
Wenn BSB-LAN keine Verbindung zum WLAN auf dem ESP32 herstellen kann, richtet es für 30 Minuten seinen eigenen Zugangspunkt mit dem Namen „BSB-LAN“ und dem Passwort „BSB-LPB-PPS-LAN“ ein. Danach startet es neu und versucht erneut, eine Verbindung herzustellen.

Neue MQTT-Funktionen, einschließlich der Möglichkeit, jeden Parameter über eine MQTT-Nachricht festzulegen und einmalig durch Senden einer MQTT-Nachricht abzufragen.

Unterstützung für BME250-Sensoren hinzugefügt.

Festlegung einer temporären Zieladresse zum Abfragen von Parametern durch Hinzufügen von `!x` (wobei `x` die Ziel-ID ist), z. B. `/6224!10`, um die Identifikation der Anzeigeeinheit abzufragen.

Die URL-Befehle `/A`, `/B`, `/T` und `/JA` wurden entfernt, da nun alle Sensoren über die Parameternummern 20000 und höher sowie (derzeit) unter der neuen Kategorie K49 zugänglich sind.

Neue Kategorien hinzugefügt, nachfolgende Kategorien wurden nach oben verschoben.

Die HTTP-Authentifizierung verwendet nun Klartext-Benutzername und -Passwort in der Konfiguration.

PPS-Benutzer können nun Uhrzeit und Wochentag an die Heizung senden.

Viele neue Parameter hinzugefügt.

Der URL-Befehl `/JR` ermöglicht das Abfragen des Standardwerts (Resetwert) eines Parameters im JSON-Format.

Der URL-Befehl `/JB` ermöglicht das Sichern von Parametern in einer JSON-Datei.

Eine neue Bibliothek für den DHT22 sollte zuverlässigere Ergebnisse liefern.

Konsolidierte Datentypen und Wertetypen: Neue Datentypen `VT_YEAR`, `VT_DAYMONTH` und `VT_TIME` als Untergruppen von `VT_DATETIME` für die Parameter 1-3, die `VT_SUMMERPERIOD` ersetzen und `VT_VACATIONPROG` anpassen. Neue Wertetypen `DT_THMS` für Zeitangaben in Stunden:Minuten:Sekunden.

MQTT: Verwenden Sie `MQTTDeviceID` als Client-ID für den Broker, standardmäßig ist dies „BSB-LAN“. ACHTUNG: Überprüfen Sie Ihre Konfiguration, falls Ihr Broker für die Autorisierung usw. auf die Client-ID angewiesen ist.

##Version 1.1##
**10.11.2020**

- **ACHTUNG:** Der Parameter „DHW Push“ („Trinkwasser Push“) musste von 1601 auf 1603 verschoben werden, da 1601 auf einigen Heizungen eine andere „offizielle“ Bedeutung hat. Bitte überprüfen Sie Ihre Konfiguration und nehmen Sie ggf. Änderungen vor.
- **ACHTUNG:** Es wurden neue Kategorien hinzugefügt, sodass sich die meisten Kategorienummern (mit `/K`) um einige Nummern verschieben werden.
- Der URL-Befehl `/JA` gibt Durchschnittswerte aus.
- Viele neue Parameter decodiert.
- Neue Parameter für Gerätefamilien 25, 44, 51, 59, 68, 85, 88, 90, 96, 97, 108, 134, 162, 163, 170, 195, 209, 211.
- Verbesserte mobile Anzeige der Weboberfläche.
- Hinzugefügte Definition „BtSerial“ zum Umleiten der seriellen Ausgabe auf Serial2, wo ein Bluetooth-Adapter angeschlossen werden kann (5V->5V, GND->GND, RX->TX2, TX->RX2). Der Adapter muss im Slave-Modus und mit 115200 bps, 8N1 konfiguriert sein.
- Viele neue polnische Übersetzungen hinzugefügt.
- Neue Datentypen `VT_BYTE10` und `VT_SPF`.
- Fehlerbehebung für PPS-Bus bezüglich der Anzeige von Heizzeitprogrammen.
- Fehlerbehebung für MQTT.

##Version 1.0##
**03.08.2020**

- Der URL-Befehl `/JI` gibt die Konfiguration im JSON-Format aus.
- Der URL-Befehl `/JC` ruft eine Liste möglicher Werte aus einer benutzerdefinierten Liste von Funktionen ab. Beispiel: `/JC=505,700,701,702,711,1600,1602`
- Protokolltelegramme (Protokollparameter 30000) werden nun in eine separate Datei (`journal.txt`) geschrieben. Sie können mit dem Befehl `/D0` (gleichzeitig mit datalog.txt) zurückgesetzt und mit dem Befehl `/DJ` abgerufen werden.
- Die WLAN-Konfiguration wurde entfernt, da sie für den Due nicht mehr anwendbar ist.
- Viele neue Parameter für verschiedene Gerätefamilien.
- Code-Optimierung und -Restrukturierung, allgemeine Geschwindigkeitssteigerung.
- Neue Schematiken für das Board-Layout V3.
- Viele Fehlerbehebungen.

##Version 0.44##
**11.05.2020**

- Webserver-Funktionalität über SD-Karte hinzugefügt und verschiedene andere Verbesserungen von GitHub-User dukess übernommen.
- JSON-Ausgabe für MQTT hinzugefügt.
- Weboberfläche für mobile Geräte optimiert.
- Weitere Parameter und Gerätefamilien hinzugefügt.
- Letzte Version, die vollständig auf dem Mega 2560 getestet wurde. Künftige Versionen können zwar weiterhin auf dem Mega ausgeführt werden, werden aber nur noch auf dem Arduino Due getestet.

##Version 0.43##
**20.02.2020**

- Unterstützung für HardwareSerial (Serial1) Verbindung des Adapters hinzugefügt. Verwenden Sie den RX-Pin 19 in der Bus()-Definition, um ihn zu aktivieren. Weitere Informationen zur Hardware finden Sie im Handbuch/Forum.
- Hinzugefügte Definition DebugTelnet, um die serielle Ausgabe an einen Telnet-Client (Port 23, kein Passwort) in `BSB_LAN_config.h` umzuleiten.
- Möglichkeit hinzugefügt, BSB-LAN (fast) vollständig über den USB-Seriellen-Port zu steuern. Die meisten Befehle werden wie ihre URL-Pendants unterstützt, d. h. `/<Passwort>/xxx` zum Abfragen des Parameters xxx oder `/<Passwort>/N` zum Neustart des Arduino.
- Standard-Geräte-ID von 6 (Raumregler „RGT1“) auf ungenutzte ID 66 („LAN“) geändert.
- Viele neue Parameter, führen Sie `/Q` aus, um mögliche Änderungen für Ihre Gerätefamilie zu sehen, und senden Sie uns Ihre Rückmeldungen!
- Globale Variablen (Arrays von 20 Bytes) `custom_floats[]` und `custom_longs[]` hinzugefügt, die mit `BSB_LAN_custom.h` verwendet werden können, z. B. zum Auslesen von Sensoren usw. Die Ausgabe dieser Variablen erfolgt über den neuen URL-Befehl `/U`.
- Gerätefamilien 23 und 29 (Grünenwald-Heizungen) hinzugefügt.
- Gerätefamilien 49, 52, 59 (Weishaupt-Heizungen) hinzugefügt.
- Gerätefamilien 91, 92, 94, 118, 133, 136, 137, 165, 184, 188 (verschiedene Regler wie QAA75 oder AVS37) hinzugefügt.
- Gerätefamilie 171 (Bösch Holzpellet-System) hinzugefügt.
- Gerätefamilie 172 (SensoTherm BLW Split B (RVS21.826F/200)) hinzugefügt.
- Gerätefamilien 186 und 164 (Olymp WHS-500) hinzugefügt.
- Gerätefamilie 195 Variante 2 (Thision 19 Plus / LMS14.111B109) hinzugefügt.
- DHT, 1Wire und Brennerstatus-Parameter (>20000) in MQTT einbezogen.
- Englisch ist nun die Standardsprache.
- Verschiedene Übersetzungen aktualisiert.
- STL-Dateien hinzugefügt, um ein Gehäuse mit einem 3D-Drucker zu drucken (danke an den FHEM-Benutzer EPo!).
- Alle Sensoren wurden nach `/T` verschoben, `/H` wird nun nicht mehr verwendet.
- Neue virtuelle Parameter 702/703 für Weishaupt-Raumregler.
- Neuer virtueller Parameter 10003, um die Außentemperatur auf neueren Systemen festzulegen.
- Textbeschreibungen für Fehlerphasen (6706 ff.) hinzugefügt.
- `/Q` ist nun umfassender.
- Neue Datentypen `VT_CUSTOM_ENUM` und `VT_CUSTOM_BYTE` zum Extrahieren von Informationen aus nicht-standardisierten Telegrammen (wie z. B. 702/703) hinzugefügt.
- Fehlerbehebung: DHCP (Ethernet)-Implementierung.

##Version 0.42##
**21.03.2019**

- Lokalisierung hinzugefügt! Jetzt können Sie bei der Übersetzung von BSB-LAN in Ihre Sprache helfen! Kopieren Sie einfach eine der Sprachdateien aus dem Lokalisierungsordner (`LANG_DE.h` ist die vollständigste) und übersetzen Sie, was Sie können. Nicht übersetzte Elemente werden in Deutsch angezeigt.
   Achtung: Die Sprachdefinition in `BSB_LAN_config.h` lautet nun `#define LANG <ISO-CODE>`
   Beispiel: `#define LANG DE`
- Export zum MQTT-Broker hinzugefügt, verwenden Sie `log_parameters`[] in `BSB_LAN_config.h`, um Parameter zu definieren und die `MQTTBrokerIP`-Definition zu aktivieren.
- Unterstützung für WLAN-Module wie ESP8266 oder Wemos Mega hinzugefügt, die mit Serial3 (RX:15/TX:14) des Arduino verbunden sind.
   Der ESP8266 muss mit der AT-Firmware von Espressif geflasht werden, um zu funktionieren.
   Bitte beachten Sie, dass WLAN über Serial grundsätzlich viel langsamer ist (nur 115kpbs) als „reine“ TCP/IP-Verbindungen.
- Neue Kategorie „34 - Konfiguration / Erweiterungsmodule“ hinzugefügt. Alle nachfolgenden Kategorien verschieben sich um eine Nummer nach oben!
- Viele neue Parameter aus der Gerätefamilie 123, führen Sie `/Q` aus, um zu sehen, ob einige Parameter auch für Ihre Heizung funktionieren!
- Viele neue, noch unbekannte Parameter durch Brute-Force-Abfragen hinzugefügt :) (Parameternummern 10200 und höher).
- Weitere PPS-Bus-Befehle hinzugefügt, Parameternummern auf 15000 und höher verschoben.
- Standard-PPS-Modus jetzt „listening“.
   Verwenden Sie den dritten Parameter der Bus-Definition, um zwischen „listening“ und „controlling“ zu wechseln, 1 steht für „controlling“, alles andere für „listening“,
   d. h. BSB bus(68,67,1) sendet Daten an die Heizung, BSB bus(68,67) empfängt nur Daten von der Heizung/Raumregler.
   Sie können zwischen den Modi zur Laufzeit mit dem URL-Befehl `/P2,x` wechseln, wobei x entweder 1 (für „controlling“) oder nicht 1 (für „listening“) ist.
- Fehler behoben, der PPS-Bus-Abfragen zum Absturz brachte.
- Stabilitätsverbesserungen für den PPS-Bus.
- Legende beim Plotten mehrerer Parameter verbessert.
- JSON-Export hinzugefügt; Abfrage mit `/JQ=a,b,c,d...` oder Push-Abfragen an `/JQ` oder Push-Set-Befehle an `/JS`.
- Protokollierung von MAX! Parameter jetzt mit Protokollparameter 20007 möglich.
- Waterstage WP-Gerätefamilie (119) hinzugefügt.
- WHG Procon-Gerätefamilie (195) hinzugefügt.
- Einheit in die Protokolldatei sowie in die Durchschnittsausgabe aufgenommen.
- Gerätematching in `cmd_tbl` neu geschrieben, um auch die Gerätevariante zu berücksichtigen. Führen Sie `/Q` aus, um zu sehen, ob der Übergang für Ihr Gerät funktioniert hat!
- `BSB_LAN_custom_setup.h` und `BSB_LAN_custom_global.h` hinzugefügt, damit Sie individuellen Code hinzufügen können (am besten in Verbindung mit `BSB_LAN_custom.h`)
- Alle (bekannten) OEM-Parameter mit der Flagge `FL_OEM` markiert. OEM-Parameter sind standardmäßig schreibgeschützt. Um sie beschreibbar zu machen, ändern Sie `FL_OEM` von 5 auf 4 in `BSB_LAN_defs.h`.
- Leistung beim Abfragen mehrerer Parameter gleichzeitig (ähnlich wie bei der Kategoriesuche) verbessert.
- Konfigurationsoption zum Definieren des Subnetzes hinzugefügt.
- `/Q` benötigt nicht mehr `#define DEBUG`.
- Fehlerbehebung ENUM-Speicheradressierung.
- Fehlerbehebung in der Reset-Funktion `/N`, EEPROM während des Resets mit `/NE` löschen.
- favicon.ico hinzugefügt.
- Aufteilung von cmdtbl in cmdtbl1 und cmdtbl2 aufgrund der Arduino-Grenze (?) von 32 kB Größe der Struktur, wodurch mehr Platz für neue Parameter geschaffen wird.

##Version 0.41##
**17.03.2019**

- Zwischenversion, die alle Änderungen von 0.42 oben enthält, mit Ausnahme der Lokalisierung, d. h. alle Textfragmente sind immer noch Teil des Hauptcodes.

##Version 0.40##
**21.01.2018**

- Abfrage von MAX! Heizungsthermostaten implementiert, Anzeige mit dem URL-Befehl `/X`
   Siehe `BSB_LAN_custom.h` für ein Beispiel, um die durchschnittliche Raumtemperatur an das Heizungssystem zu übertragen.
- Neue Kategorie „22 - Energiezähler“ hinzugefügt – beachten Sie, dass sich alle nachfolgenden Kategorien um eine nach oben verschieben!
- Neuer virtueller Parameter 1601 (manueller TWW-Push).
- Fujitsu Waterstage WSYP100DG6-Gerätefamilie (211) hinzugefügt.
- CTC-Gerätefamilie (103) hinzugefügt.
- Neue Definition `#define TRUSTED_IP2` hinzugefügt, um den Zugriff auf eine zweite lokale IP-Adresse zu gewähren.
- Optionale Definition `#define GatewayIP` in `BSB_LAN_config.h` hinzugefügt, um die Router-Adresse anders als x.x.x.1 festzulegen.
- Parameter 10109 entfernt, da er derselbe ist wie 10000.
- Funktion hinzugefügt, um alle bekannten CommandIDs auf Ihrem eigenen Heizungssystem zu überprüfen. Verwenden Sie `/Q`, nachdem Sie die Definition `#define DEBUG` in `BSB_LAN_config.h` aktiviert haben.
- Parameternummern zum Kategoriemenü hinzugefügt.
- analyze.sh aktualisiert.
- Speicherproblem hoffentlich behoben.
- HTML-Zeichenfolgen nach `html_strings.h` verschoben.

##Version 0.39##
**02.01.2018**

- Implementierung des PPS-Bus-Protokolls.
   Siehe `/K40` für die begrenzten Befehle, die für diesen Bus verfügbar sind.
   Verwenden Sie setBusType(2), um den Bus-Typ beim Booten auf PPS zu setzen, oder `/P2`, um ihn zur Laufzeit zu wechseln.
- Setzen Sie GPIOs auf Eingang, indem Sie `/Gxx,I` verwenden.
- Definition `#define CUSTOM_COMMANDS` hinzugefügt.
   Verwenden Sie diese in Ihrer Konfiguration, um individuellen Code aus `BSB_LAN_custom.h`
   (muss von Ihnen erstellt werden!) einzubeziehen, der am Ende jeder Haupt-Schleife ausgeführt wird.
   Die Variablen `custom_timer` und `custom_timer_compare` wurden hinzugefügt, um
   Code in beliebigen Intervallen auszuführen.
- LogoBloc Unit L-UB 25C-Gerätefamilie (95) hinzugefügt.
- mehrere neue Parameter hinzugefügt.
- Fehlerbehebung für die Protokollierung der Brennerlaufzeit Stufe 2.

##Version 0.38##
**22.11.2017**

- **ACHTUNG:** Neue `BSB_LAN_config.h` Konfigurationen! Sie müssen Ihre
## Version 0.34 ##
**29.05.2017**

- Logdaten können jetzt als Graph angezeigt werden
- Das Webinterface kann jetzt `VT_BIT`-Typ-Parameter in einer für Menschen lesbaren Form anzeigen und festlegen
- KonfigRGx-Beschreibungen hinzugefügt; Vorsicht: Es wurden verschiedene Quellen verwendet, es gibt keine Garantie, dass die Beschreibungen zu deinem individuellen Heizungssystem passen!
- `VT_BIT` ist im Webinterface generell schreibgeschützt. Um es festzulegen, benutze den URL-Befehl `/S` mit der dezimalen Darstellung des Werts
- Ein Bug mit `VT_SECONDS_SHORT5`, der die Parameter 9500 und 9540 betraf, wurde behoben.
- Ein Bug in Bezug auf die Gerätefamilie von Fujitsu (von 127 bis 170) wurde behoben
- Bibliotheken aus dem Ordner "libraries" in "src" verschoben, sodass sie ohne Kopieren in den Arduino-Bibliotheksordner einbezogen werden können
- Den Include-Pfad von "DallasTemperature.h" für "OneWire.h" geändert

## Version 0.33 ##
**09.05.2017**

- Keine Heizungssystem-Definitionen mehr aufgrund der neuen Auto-Detect-Funktion, die auf der Gerätefamilie (Parameter 6225) basiert, oder setze die `device_id`-Variable direkt auf den Parameterwert
- Zwei weitere Sicherheitsoptionen: `TRUSTED_IP`, um den Zugriff auf eine IP-Adresse zu beschränken, und HTTP-Authentifizierung mit Benutzername und Passwort
- Durchschnittswerte werden auf der SD-Karte gespeichert, falls vorhanden und die LOGGER-Definition aktiviert ist
- Deaktiviere die Protokollierung, indem du `/L0=0` setzt - so kannst du die LOGGER-Definition aktivieren, ohne die SD-Karte zu füllen, aber trotzdem Durchschnittswerte speichern
- Neue Fehlercodes für THISION
- Daten-Payload-Dump auf der Website für Befehle unbekannten Typs hinzugefügt, nicht unterstützte Parameter abgeblendet
- Aktiviere die Protokollierung von Telegrammen (Protokollparameter 30000) auch im Monitor-Modus (bsb.cpp und bsb.h aktualisiert)
- Die Zeit des Heizungssystems wird jetzt periodisch aus Broadcast-Telegrammen abgerufen, was die Busaktivität weiter reduziert
- Neuer Datentyp `VT_BIT` für Parameter, die einzelne Bits setzen. Wird als Binärzahlen angezeigt, Einstellung erfolgt weiterhin mit der Dezimaldarstellung
- Neuer Datentyp `VT_TEMP_SHORT5_US` für unsignierte ein Byte-Temperaturen, geteilt durch 2 (bisher nur 887 Vorlaufsoll NormAussentemp)
- Neuer Datentyp `VT_PERCENT5` für unsignierte ein Byte-Temperaturen, geteilt durch 2 (bisher nur 885 Pumpe-PWM Minimum)
- Neuer Datentyp `VT_SECONDS_WORD5` für zwei Byte-Sekunden, geteilt durch 2 (bisher nur 2232, 9500 und 9540)
- Neuer Datentyp `VT_SECONDS_SHORT4` für (signierte?) ein Byte-Sekunden, geteilt durch 4 (bisher nur 2235)
- Neuer Datentyp `VT_SECONDS_SHORT5` für (signierte?) ein Byte-Sekunden, geteilt durch 5 (bisher nur 9500, 9540)
- Neuer Datentyp `VT_SPEED2` für zwei Byte-Umdrehungen pro Minute (bisher nur 7050)
- Set()-Funktion von offensichtlichen Duplikaten bereinigt
- Fälle für `VT_TEMP_WORD`, `VT_SECONDS_WORD5`, `VT_TEMP_SHORT`, `VT_TEMP_SHORT5`, `VT_SECONDS_SHORT4` zur Set()-Funktion hinzugefügt

## Version 0.32 ##
**18.04.2017**

- Viele neue unterstützte Parameter
- Das neu gestaltete Webinterface ermöglicht die Steuerung des Heizungssystems ohne zusätzliche Software oder kryptische URL-Befehle. URL-Befehle sind natürlich weiterhin verfügbar, sodass du nichts ändern musst, wenn du FHEM etc. verwendest.
- Deutsches Webinterface mit der Definition `LANG_DE` verfügbar
- Neuer URL-Befehl `/LB=x` zum Protokollieren nur von Broadcast-Nachrichten (x=1) oder allen Bus-Nachrichten (x=0)
- Neuer URL-Befehl `/X` zum Reset des Arduino (die RESET-Definition in `BSB_LAN_config.h` muss aktiviert sein)
- Neue Protokollparameter 20002 und 20003 für Ladezeiten und Zyklen von Warmwasser
- DS18B20-Protokollparameter von 20010-20019 auf 20200-20299 und DHT22-Protokollparameter von 20020-20029 auf 20100-20199 verschoben
- Durchschnittsprotokollparameter von 20002 auf 20004 verschoben
- Verschiedene Parameter auf schreibgeschützt gesetzt, da sie offensichtlich schreibgeschützt sind (K33-36)
- Verschiedene Fehlerbehebungen

## Version 0.31 ##
**10.04.2017**

- Die Protokolldatei-Dumping-Rate um den Faktor 5 erhöht / Solange wir noch Speicherplatz haben, kannst du logbuflen von 100 auf 1000 erhöhen, um die Übertragungsgeschwindigkeit von ca. 16 auf 18 kB/s zu steigern
- Überwachung der Brenneraktivität basierend auf Broadcast-Nachrichten für Brötje-Systeme angepasst
- Die Definition `PROGNR_5895` entfernt, da sie bisher nur eine ENUM-Definition deaktiviert hat.
- Die Definition `PROGNR_6030` entfernt, da der doppelte Befehlscode über die BROETJE / non-BROETJE-Definitionen aufgelöst werden konnte
- `BROETJE_SOB` in BROETJE umbenannt, um eine feinere Unterscheidung zwischen verschiedenen BROETJE-Fällen zu ermöglichen (z.B. 6800ff)
   Das bedeutet, dass du jetzt ZWEI Definitionen aktivieren musst, wenn du ein Brötje-System verwendest: Das allgemeine BROETJE sowie `BROETJE_SOB` oder `BROETJE_BSW`.
   Wirf einen Blick in dein serielles Protokoll für die Parameter 6800, um zu sehen, welche Befehlscodes zu deinem System passen, und aktiviere entsprechend einen von beiden.
- 16-Bit-Adressierung des Flash-Speichers in 32-Bit-Adressierung geändert, um Abstürze aufgrund immer größerer PROGMEM-Tabellen zu beheben - jetzt haben wir wieder viel Platz zum Atmen für neue Befehlscodes :)
- Nachgestelltes \0-Zeichen aus mehreren ENUMs entfernt, das zu falschen ENUM-Auflistungen führte. Bitte beachte, dass ENUMs nicht mit einem nachgestellten \0 enden sollten!

## Version 0.30 ##
**22.03.2017**

- Die Time-Bibliothek von Paul Stoffregen (https://github.com/PaulStoffregen/Time) ist jetzt erforderlich und im Bibliotheksordner enthalten.
- Fügt die Protokollierung roher Telegrammdaten auf der SD-Karte mit dem Protokollparameter 30000 hinzu. Die Protokollierung von Telegrammdaten wird durch die Befehle `/V` und `/LU` beeinflusst
- Fügt den Befehl `/LU=x` hinzu, um nur bekannte (x=0) oder unbekannte (x=1) Befehlscodes zu protokollieren, wenn Telegrammdaten protokolliert werden
- Die Definition `USE_BROADCAST` entfernt, Broadcast-Daten werden jetzt immer verarbeitet
- Neue interne Funktionen GetDateTime, TranslateAddr, TranslateType

## Version 0.29 ##
**07.03.2017**

- Fügt den Befehl `/C` hinzu, um die aktuelle Konfiguration anzuzeigen
- Fügt den Befehl `/L` hinzu, um das Protokollintervall und die Parameter zu konfigurieren
- Fügt für den Befehl `/A` die Option hinzu, 24-Stunden-Durchschnittsparameter während der Laufzeit festzulegen
- Fügt den speziellen Parameter 20002 für die Protokollierung des `/A`-Befehls (24-Stunden-Durchschnitte, macht nur Sinn für lange Protokollierungsintervalle) hinzu
- Fehlerbehebungen für die Protokollierung von DS18B20-Sensoren

## Version 0.28 ##
**05.03.2017**

- Fügt spezielle Parameter 20000+ für die SD-Karten-Protokollierung der Befehle `/B,` `/T` und `/H` hinzu (siehe `BSB_LAN_config.h` für Beispiele)
- Fügt Versionsinformationen zum `BSB_LAN`-Webinterface hinzu

## Version 0.27 ##
**01.03.2017**

- Fügt ein Datumsfeld zur Protokolldatei hinzu (erfordert die genaue Zeit, die vom Heizungssystem gesendet wird)
- `/D0` erstellt die Datei datalog.txt neu mit einer Tabellenkopfzeile
- Dem Befehls-Tabellen-Strukturfeld "flags" hinzugefügt. Derzeit wird nur `FL_RONLY` unterstützt, um einen Parameter schreibgeschützt zu machen
- `DEFAULT_FLAG` in der Konfiguration hinzugefügt. Standardmäßig auf `NULL` gesetzt, d.h. alle Felder sind les- und schreibbar.
   Wenn es auf `FL_RONLY` gesetzt ist, werden alle Parameter schreibgeschützt, z.B. für eine zusätzliche Sicherheitsebene.
   Einzelne Parameter können auf `NULL`/`FL_RONLY` gesetzt werden, um nur diese Parameter schreibbar/schreibgeschützt zu machen.

## Version 0.26 ##
**27.02.2017**

- Funktionalität zur Protokollierung auf Micro-SD-Karte mithilfe des Steckplatzes des w5100-Ethernet-Shields hinzugefügt
- Weitere Parameter hinzugefügt (z.B. 8009)

## Version 0.25 ##
**21.02.2017**

- Weitere FUJITSU-Parameter hinzugefügt

## Version 0.24 ##
**14.02.2017**

- README mit hinzugefügten Funktionen aktualisiert
- Deutsche Übersetzungen von FAQ und README hinzugefügt, bereitgestellt von Ulf Dieckmann

## Version 0.23 ##
**12.02.2017**

- Kleiner Bugfix

## Version 0.22 ##
**07.02.2017**

- Weitere FUJITSU-Parameter
- (Hoffentlich) korrekte Implementierung von `VT_VOLTAGE`-Messwerten
- Kleinere Fehlerbehebungen

## Version 0.21 ##
**06.02.2017**

- Verschiedene Parameter für die Fujitsu-Wärmepumpe hinzugefügt, einschließlich der neuen `#define FUJITSU`-Direktive, um diese Parameter aufgrund unterschiedlicher Parameternummern zu aktivieren
- Kleinere Fehlerbehebungen

## Version 0.20 ##
**27.01.2017**

- Weitere Parameter für Feststoffkessel hinzugefügt
- Kleinere Fehlerbehebungen

## Version 0.19 ##
**01.01.2017**

- Feuchtigkeitsbefehl `/H` hinzugefügt, derzeit für DHT22-Sensoren
- 24-Stunden-Durchschnittsbefehl `/A` hinzugefügt, Parameter in `BSB_LAN_config.h` definieren
- Nachfolgende Leerzeichen aus Menü-Zeichenfolgen entfernt
- Befehlscode 0x053D04A2 für THISION-Heizungen korrigiert
- Rob Tillaarts DHT-Bibliothek einbezogen, da es verschiedene Bibliotheken zur Implementierung des Protokolls gibt und diese hier verwendete Bibliothek mehrere Sensoren mit einem Objekt ansprechen kann.
- `/temp`-URL-Parameter entfernt, da er ein Duplikat von `/T` ist
- Schleife zum Anzeigen von DHT22-Sensoren in IPWE hinzugefügt
- Kompilierung von IPWE-Erweiterungen optional gemacht (`#define IPWE`)

## Version 0.18 ##
**22.12.2016**

- Konfiguration in `bsb_lan_config.h` ausgelagert
- Befehlsdefinitionen in `bsb_lan_defs.h` ausgelagert
- GPIO-Rückgabewerte von LOW/HIGH in 1/0 geändert
- IPWE reaktiviert und aktualisiert (Parameter in der Konfiguration definieren)
- Überprüfung auf geschützte Pins beim Zugriff auf GPIO (in der Konfiguration definieren)
- Schaltpläne und PCB-Dateien in den neuen Unterordner "schematics" verschoben

## Version 0.17a ##
**20.12.2016**

- Kleinere Fehler korrigiert

## Version 0.17 ##
**20.12.2016**

- Version 0.16 mit Änderungen von FHEM-Benutzer miwi zusammengeführt

## Version 0.16 ##
**20.11.2016**

- IPWE- und EthRly-Schnittstelle entfernt
- GPIO-Schnittstelle hinzugefügt
- Parameter von J.Weber zusammengeführt
- Duplizierte Befehlscodes aufgelöst

## Version 0.15a ##
**25.07.2016**

- Die Befehle aus einem Python-Projekt und diesem Projekt zusammengeführt,
   die beiden Versionen zusammengeführt, offensichtliche Fehler korrigiert.
   Hypothetische numerische Werte in ENUM-Definitionen eingefügt,
   wo in Broetje-Handbüchern nur die Meldungstexte dokumentiert waren.
- Informationen aus Traces in einer Broetje-Installation mit
   einem ISR-SSR-Controller und einem WOB 25C-Ölbrenner hinzugefügt.

## Version 0.15 ##
**21.04.2016**

- Solar- und Pufferspeicher von Elco Logon B & Logon B MM hinzugefügt

## Version 0.14 ##
**04.04.2016**

- Kleinere Fehlerbehebungen für Broetje SOB
- Broadcast-Verarbeitung erweitert (experimentell)

## Version 0.13 ##
**31.03.2016**

- Widerstandswert im Empfangs-Pfad von 4k7 auf 1k5 geändert
- Werte 0x0f und 0x10 zu Enum8005 hinzugefügt
- Zeichenfolgen für Zeitprogramme korrigiert
- Timeout für das Senden einer Nachricht hinzugefügt (1 Sekunde)
- `/T` zum Abfragen von One-Wire-Temperatursensoren in gemischten Abfragen hinzugefügt
- Spezielle Behandlung für Broetje SOB hinzugefügt
- Einstellungen vereinfacht

## Version 0.12 ##
**09.04.2015**

- `ONEWIRE_SENSORS` zu ipwe hinzugefügt
- Parameter-Dekodierung für ELCO Thision-Heizungssystem korrigiert

## Version 0.11 ##
**07.04.2015**

- Parameter-Dekodierung für ELCO Thision-Heizungssystem korrigiert

## Version 0.10 ##
**15.03.2015**

- Weitere Parameter für ELCO Thision-Heizungssystem hinzugefügt

## Version 0.9 ##
**09.03.2015**

- Weitere Parameter für ELCO Thision-Heizungssystem hinzugefügt
- printTelegramm gibt Zeichenfolge für weitere Verarbeitung zurück

## Version 0.8 ##
**05.03.2015**

- Parameter für ELCO Thision-Heizungssystem hinzugefügt
- IPWE-Erweiterung hinzugefügt
- Kleinere Fehlerbehebungen

## Version 0.7 ##
**06.02.2015**

- Bus-Monitor-Funktionalität hinzugefügt

## Version 0.6 ##
**02.02.2015**

- SoftwareSerial in BSBSoftwareSerial umbenannt
- Ordnerstruktur geändert, um ein einfaches Kompilieren mit dem Arduino-SDK zu ermöglichen

## Version 0.5 ##
**02.02.2015**
