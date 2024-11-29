#ChangeLog#

##Aktueller Master##

- **ACHTUNG: Breaking Change!** Vereinfachte Themestruktur für MQTT. Die neue Struktur fügt `/status` zum Abfragen eines Parameters, `/set` zum Festlegen eines Parameters, `/inf` zum Senden von Daten als INF-Telegramm und `/poll` hinzu, um BSB-LAN zu zwingen, ein Update des Parameterwerts an den Broker zu senden. Wenn Sie die MQTT-Auto-Discovery verwenden, sollte das Aufrufen von `/M1` idealerweise diese Änderungen aktualisieren. Wenn Sie jedoch Ihre eigenen Konfigurationen verwenden, müssen Sie hier Anpassungen vornehmen.
- **ACHTUNG: Breaking Change!** Wenn Sie JSON-Einstellungen für MQTT verwenden, wurden zuvor alle Nachrichten in `BSB-LAN/json` geschrieben und damit im Grunde sofort überschrieben, wenn mehrere Parameter protokolliert wurden. Jetzt bestimmt diese Einstellung nur das Format (und nicht das Format und das Thema) der Daten, die in `/status` jedes Parameters geschrieben werden. Für die automatische Erkennung ist Klartext die einzige gültige Wahl.
- **ACHTUNG: Breaking Change** Die vom BSB-LAN an das `MQTT`-Thema gesendete Bestätigungsmeldung wurde entfernt. Stattdessen wurde die QoS für die Veröffentlichung von Nachrichten auf Ebene 1 festgelegt.
- **ACHTUNG: Breaking Change:** Die Log-Konfigurationswerte haben sich geändert. Betroffen sind jedoch nur Benutzer, die sich bei UDP angemeldet haben, und sie müssen ihre Einstellungen anpassen.
- Einstellung hinzugefügt, um nur Protokollparameter an MQTT zu veröffentlichen. Das Erzwingen von MQTT-Updates über das /poll-Thema ist weiterhin möglich.
- state_class für nicht kumulative Sensoren in MQTT Auto-Discovery hinzugefügt
- Aktualisierte Raum-Einheit-Emulation in `custom_functions`, um mit Version 4.x zu funktionieren.
- Fehlerbehebung für VT_ENERGY, neuer Datentyp VT_ENERGY10 und VT_ENERGY10_N hinzugefügt

##Version 4.1##
**06.11.2024**

- **ACHTUNG: Breaking Change!** Thema-Struktur für MQTT geändert. Dies bedeutet, dass alle vorhandenen MQTT-Entitäten in Ihrem Home-Automation-System angepasst oder neu erstellt werden müssen! Die neue Struktur lautet jetzt `BSB-LAN/<device id>/<category id>/<parameter number>`.
- **ACHTUNG: Breaking Change!** Die eindeutige ID für die MQTT-Auto-Discovery wurde geändert. Dies bedeutet, dass alle MQTT-Entitäten, die über die automatische Erkennung erstellt wurden, neu erstellt werden müssen!
- **ACHTUNG:** Die Konfigurationsoptionen `fixed_device_family` und `fixed_device_variant` wurden entfernt, da sie für gerätespezifische Parameterlisten nicht mehr funktionieren. Wenn Ihre Heizung ausgeschaltet ist, wenn Sie den Mikrocontroller einschalten, versucht BSB-LAN alle 60 Sekunden, die Details abzurufen.
- **ACHTUNG:** Änderung der Konfigurationsoptionen führt zu einem neuen EEPROM-Layout, daher wird das EEPROM basierend auf der Konfiguration von `BSB_LAN_config.h` neu initialisiert.
- Die MQTT-Auto-Discovery funktioniert jetzt für alle Geräte, nicht nur für Geräte-ID 0. Verwenden Sie `/M1!<x>` oder `/M0!<x>`, um Entitäten für Geräte-ID `<x>` zu erstellen bzw. zu entfernen.
- Die Flagge der MQTT-Auto-Discovery-Nachrichten wurde auf "beibehalten" geändert, sodass die Parameter nach einem Neustart von Home Assistant verfügbar bleiben.

##Version 4.0##
**01.11.2024**

- **ACHTUNG: Breaking Change!** Der Raumtemperaturparameter 10000, 10001 und 10002 muss jetzt über die zusätzliche Flagge `FL_SPECIAL_INF` verfügen, andernfalls funktioniert das Festlegen der Temperatur nicht!
- **ACHTUNG: Breaking Change!** Der Parameter für die Außentemperatursimulation 10017 muss über die Flagge `FL_SPECIAL_INF` verfügen, andernfalls funktioniert das Festlegen der Temperatur nicht!
- **ACHTUNG: Breaking Change!** Der Raumtemperaturparameter 10000, 10001 und 10002 für Weishaupt-Heizgeräte (Gerätefamilien 49, 50, 51 und 59) muss jetzt über die Flagge `FL_SPECIAL_INF` verfügen, andernfalls funktioniert das Festlegen der Temperatur nicht!
- **ACHTUNG: Breaking Change!** Die URL-Befehle `/U` (Anzeige benutzerdefinierter Variablen) und `/X` (Anzeige MAX! Werte) wurden entfernt, da diese Werte jetzt über die Parameter 20000++ abgerufen werden können
- **ACHTUNG: Breaking Change!** Die PPS-Zeitprogrammparameter (15050-15091) wurden mit den BSB/LPB-Zeitprogrammparametern gestrafft, was zu einem Parameter pro Tag (anstatt sechs) führt, der drei Schaltpunkte (Start und Ende) pro Parameter abdeckt.
- **ACHTUNG:** Für ESP32 erfordert BSB-LAN die ESP32-Framework-Version 3.0.x - achten Sie auf Fehler oder seltsames Verhalten (1-Wire-Sensoren sind noch nicht getestet) sowie auf seltsames Verhalten/Abstürze anderer Art.
- **ACHTUNG:** Neue Konfigurationsoptionen in `BSB_LAN_config.h` - aktualisieren Sie Ihre vorhandenen Konfigurationsdateien! Die webbasierte Konfiguration wird aufgrund der Änderung des EEPROM-Layouts durch die Einstellungen der Konfigurationsdatei überschrieben!
- **ACHTUNG:** Neues Handbuch: https://docs.bsb-lan.de/
- BUTTONS und `RGT_EMULATION` wurden aus dem Hauptcode in die `custom_functions`-Bibliothek verschoben. Um sie weiterhin zu verwenden, nutzen Sie die Dateien `BSB_LAN_custom_*.h` und aktivieren Sie die `CUSTOM_COMMANDS`-Definition.
- Die meisten Konfigurationsdefinitionen wurden aus `BSB_LAN_config.h` entfernt. Fast alle Funktionen können jetzt ohne erneutes Flashen konfiguriert werden.
- BSB-LAN unterstützt jetzt die MQTT-Auto-Discovery (unterstützt z. B. von Home Assistant). Um Geräte zu erstellen, rufen Sie den URL-Befehl `/M1` auf, um sie zu entfernen, rufen Sie `/M0` auf.
- **ACHTUNG:** Die MQTT-Auto-Discovery erstellt einen allgemeinen Schalter für das BSB-LAN-Gerät in Home Assistant. Dieser Schalter schreibt sofort alle Parameter mit den in Home Assistant gespeicherten Werten. Verwenden Sie DIESEN SCHALTER NICHT, es sei denn, Sie wissen wirklich, was er tut!
- Die Schaltfläche "Set" in der Weboberfläche funktioniert jetzt auch mit nicht standardmäßigen Zielgeräten (d. h. 1 anstelle von 0)
- Abgefragte/festgelegte Parameter werden jetzt an den MQTT-Broker weitergeleitet (sofern MQTT aktiviert ist)
- Die zuvor verwendeten `/M1` und `/M0` zum Umschalten der Monitorfunktion wurden entfernt, da sie jetzt über die Konfiguration in der Weboberfläche zugänglich sind.
- Das Auflisten von Kategorien mit `/K` funktioniert jetzt auch mit dem Zielgerät (z. B. /K!1 für Zielgerät 1, Standard ist 0).
- Wichtiger Fehlerbehebung für OTA-Update: Frühere Versionen hatten eine harte Begrenzung der Dateigröße, die bei neueren Heizsystemen mit mehreren hundert Parametern erreicht wurde, sodass kein OTA-Update möglich war. Dies ist jetzt behoben, betroffene Benutzer müssen jedoch ein USB-basiertes Update durchführen.
- 1-Wire- und DHT-Sensoren werden jetzt mit dem Wert -1 anstelle von 0 deaktiviert. In der Weboberfläche wird auch ein leeres Feld akzeptiert.
- MQTTTopicPrefix ist nicht mehr optional, das Thema "fromBroker" wurde entfernt (ehemals zum Senden von Befehlen an BSB-LAN über MQTT verwendet)
- Die Verwendung der 24-Stunden-Durchschnittsfunktion erfordert jetzt nicht mehr die Verwendung einer SD-Karte. Die SD-Karte wird nur verwendet, um Durchschnittswerte zu speichern, wenn die intervallbasierte Protokollierung auf der SD-Karte aktiv ist.
- Neue PPS-Raumgerätevariante für RVD130, die das obere Nibble des Magic Byte bei jeder Transaktion erhöht.
- Das Abrufen der aktuellen Uhrzeit von einem NTP-Server ist standardmäßig aktiviert. Deaktivieren Sie es, indem Sie `ntp_server` auf eine leere Zeichenfolge setzen.
- Neue Parameterflagge `FL_NOSWAP_QUR` für Parameter, die das erste und zweite Byte der Befehls-ID in QUR-Telegrammen nicht austauschen
- Neue Parameterflagge `FL_FORCE_INF` für Parameter, von denen wir sicher sind, dass sie nur mit INF funktionieren (wie z. B. Raumtemperatur). Erzwingt ein INF-Telegramm, auch wenn `/S` verwendet wird, um den Parameter festzulegen (ermöglicht das Festlegen der Raumtemperatur über die Weboberfläche)
- BSB-LAN-Logo-Wasserzeichen in der Protokoll-Graph-Anzeige (DE-cr)
- Binäre ENUMs (ja/nein, ein/aus usw.) geben beim Abfragen jetzt entweder 0 oder 1 zurück, nicht - wie bei einigen Heizsystemen - 0 oder 255. Das Festlegen eines beliebigen Werts von 1 bis 255 ist weiterhin möglich.
- Ein schwerwiegender Fehler in PPS wurde behoben, der verhinderte, dass es im aktiven/Raumgerätemodus ordnungsgemäß ausgeführt wurde.
- Ein Fehler (oder, je nach Perspektive, eine reduzierte Sicherheit) wurde behoben, der verhinderte, dass Befehle über die serielle/Telnet-Konsole ausgegeben wurden, wenn die HTTP-Authentifizierung aktiv war
- Verschiedene Fehlerbehebungen, darunter die Protokollierung von Bus-Telegrammen auf einem Speichergerät.
- Neue Version der OneWireNg-Bibliothek
- Diese Version wurde von den folgenden Sponsoren unterstützt: Erich Scheilko

##Version 3.3##
**12.03.2024**

- **ACHTUNG:** Neue Konfigurationsoptionen in `BSB_LAN_config.h` - aktualisieren Sie Ihre vorhandenen Konfigurationsdateien!
- ESP32: Unterstützung für den Empfang von Datum und Uhrzeit über NTP anstelle der Entnahme aus der Heizung.
- Die MQTT-Broker-Einstellung akzeptiert jetzt Domänennamen sowie IP-Adressen. Ein optionaler Port kann nach einem abschließenden Doppelpunkt hinzugefügt werden, z. B. broker.my-domain.com:1884. Andernfalls wird standardmäßig 1883 verwendet.
- ESP32 NodeMCU: Unterstützung für einen optionalen zusätzlichen SD-Kartenadapter. Die SPI-Pins können in `BSB_LAN_config.h` konfiguriert werden, standardmäßig auf die Standard-SPI-Pins 5, 18, 19 und 23.
- ESP32: Wechsel zwischen Protokoll-Speichergerät (SD-Karte/internem Flash) kann jetzt in der Weboberfläche erfolgen.
- ESP32: Erstellen Sie ein temporäres WiFi-AP, falls die Ethernet-Verbindung fehlschlägt
- ESP32 NodeMCU: Der EEPROM-Clear-Pin wurde von 18 auf 21 geändert, um Konflikte mit SPI-SD-Kartenadaptern zu vermeiden.
- Diese Version wurde von den folgenden GitHub-Sponsoren unterstützt: jsimon3

##Version 3.2##
**15.11.2023**

- **ACHTUNG:** In `BSB_LAN_config.h` werden `log_parameters`, `avg_parameters` und `ipwe_parameters` jetzt in geschweiften Klammern und mit einer anderen Größe (40 statt 80) und einem anderen Typ (`parameter` anstelle von `float`) geschrieben. Aktualisieren Sie Ihre `BSB_LAN_config.h` entsprechend, um Fehler zu vermeiden!
- Hinzugefügte Versionsprüfungen der Konfigurationsdatei, um die Verwendung veralteter Konfigurationsdateien mit neueren Softwareversionen zu verhindern.
- Die Variable `esp32_save_energy` ist jetzt standardmäßig auf false gesetzt, da sie nur sinnvoll erscheint, wenn eine LAN-Verbindung verwendet wird oder wenn Sie WiFi verwenden und mit der Auswirkung auf die Leistung leben können.
- Der Ordner `custom_functions` wurde hinzugefügt, in dem Codebeispiele für nützliche Funktionen gesammelt werden, die dennoch zu spezifisch sind, um in den Kerncode von BSB-LAN aufgenommen zu werden.
- Hinzugefügtes benutzerdefiniertes Funktionsbeispiel für die Zuordnung von DS18B20-Sensoren zu festen benutzerdefinierten Float-Parametern
- Diese Version wurde von den folgenden GitHub-Sponsoren unterstützt: BraweProg, fdobrovolny, Harald

##Version 3.1##
**04.06.2023**

- **ACHTUNG:** Für ESP32-Geräte, die den internen Flash-Speicher für die Protokollierung verwenden: Das Dateisystem wurde von SPIFFS auf LittleFS umgestellt. Laden Sie vor dem Aktualisieren wichtige Protokolldaten herunter!
- **ACHTUNG:** In `BSB_LAN_config.h` hat sich die Struktur von `log_parameters`, `avg_parameters` und `ipwe_parameters` geändert und enthält jetzt das Zielgerät auf dem Bus!
- **ACHTUNG:** Das neue EEPROM-Schema kann zu verlorenen Web-Konfigurationseinstellungen führen, wenn es aktualisiert wird. Notieren Sie sich Ihre Einstellungen, bevor Sie aktualisieren!
- **ACHTUNG:** Neue Variable `esp32_save_energy` in `BSB_LAN_config.h` - aktualisieren Sie vor dem Kompilieren der neuen Version.
- **ACHTUNG:** Neue Variable bssid in `BSB_LAN_config.h` - definiert eine feste BSSID-Adresse, mit der eine Verbindung hergestellt werden soll, wenn WiFi auf ESP32 verwendet wird.
- Parameter können jetzt auch beim Protokollieren (einschließlich MQTT) oder beim Verwenden von Durchschnitts- oder IPWE-Parametern mithilfe der !-Notation von anderen Geräten auf dem Bus abgefragt werden
- Aktivieren/Deaktivieren der Energiesparfunktion auf ESP32. Spart 20 % Energie, kann sich aber auf die WiFi-Reichweite und die Downloadgeschwindigkeit von Protokolldateien auswirken, wenn WiFi verwendet wird (LAN nicht betroffen)
- Verbesserte Leistung und Flash-Speichernutzung auf ESP32-Geräten, die den internen Flash-Speicher für die Protokollierung verwenden, aufgrund des Wechsels von SPIFFS zu LittleFS
- Um die Handhabung großer Datenprotokolle zu verbessern: Datumsbereichsauswahl in `/DG`, neue URL-Befehle `/Da,b`, `/DA`, `/DB`, `/Dn`, `/DI` und `/DKn`
- Diese Version wurde von den folgenden GitHub-Sponsoren unterstützt: lapixo, nrobadey

##Version 3.0##
**16.03.2023**

- **ACHTUNG:** `BSB_LAN_custom_defs.h`.default muss in `BSB_LAN_custom_defs.h` umbenannt werden und enthält standardmäßig nur eine sehr begrenzte Anzahl von Parametern. Weitere Informationen finden Sie im Handbuch, um gerätespezifische Parameterlisten zu erhalten.
- Fügen Sie den neuen `/LN`-URL-Befehl hinzu, um die Protokollierung unabhängig vom aktuellen Intervall zu erzwingen.
- Verbesserte Bibliotheksprüfungen: ESP32-Benutzer müssen die ArduinoMDNS- und WiFiSpi-Ordner nicht mehr entfernen.
- Neue SdFat-Version 2 für Arduino Due
- Neuer Datentyp `VT_BINARY_ENUM`
- Diese Version wurde von den folgenden GitHub-Sponsoren unterstützt: Alex, DE-cr

##Version 2.2##
**01.11.2022**

- **ACHTUNG:** In `BSB_LAN_config.h`.default haben mehrere Variablen ihren Variablentyp geändert, es ist wahrscheinlich am besten, Ihre `BSB_LAN_config.h` von Grund auf neu zu erstellen.
- Parameternummern sind jetzt Gleitkommazahlen (d. h. XXXX.Y), da einige Parameter zwei verschiedene Arten von Informationen enthalten. Diese werden jetzt in Dezimalschritten von 0,1 angezeigt. Sie können den "Haupt"-Parameter weiterhin über XXXX (ohne .Y) abfragen
- Viele Fehlerbehebungen und neue Datentypen
- Gerätespezifische Parameterlisten werden unterstützt

##Version 2.1##
**30.07.2022**

- Viele neue Parameter für LMU64
- **ACHTUNG:** Neue Kategorien für LMU64- und RVD/RVP-Controller aufgrund ihrer unterschiedlichen Nummerierungsschemata. Wird mit der Zeit gefüllt. Die PPS- und Sensorkategorien sind um zwei nach oben gerückt.
- ESP32: OTA verwendet jetzt die systemweite HTTP-AUTH
Wenn BSB-LAN keine Verbindung zum WiFi auf dem ESP32 herstellen kann, richtet es für 30 Minuten seinen eigenen Zugangspunkt mit dem Namen „BSB-LAN“ und dem Passwort „BSB-LPB-PPS-LAN“ ein. Anschließend wird es neu starten und erneut versuchen, eine Verbindung herzustellen.

Neue MQTT-Funktionen, einschließlich der Möglichkeit, jeden Parameter über eine MQTT-Nachricht festzulegen und durch Senden einer MQTT-Nachricht aktiv einen beliebigen Parameter abzufragen.

Unterstützung für BME250-Sensoren hinzugefügt.

Festlegung einer temporären Zieladresse zum Abfragen von Parametern durch Hinzufügen von `!x` (wobei `x` die Ziel-ID ist), z. B. `/6224!10`, um die Identifikation der Anzeigeeinheit abzufragen.

Die URL-Befehle `/A`, `/B`, `/T` und `/JA` wurden entfernt, da nun alle Sensoren über die Parameternummern 20000 und höher sowie (derzeit) unter der neuen Kategorie K49 zugänglich sind.

Neue Kategorien hinzugefügt, nachfolgende Kategorien wurden nach oben verschoben.

Bei der HTTP-Authentifizierung werden nun Klartext-Benutzername und -Passwort in der Konfiguration verwendet.

PPS-Benutzer können nun Uhrzeit und Wochentag an die Heizung senden.

Viele neue Parameter hinzugefügt.

Der URL-Befehl `/JR` ermöglicht das Abfragen des Standardwerts (Resetwert) eines Parameters im JSON-Format.

Der URL-Befehl `/JB` ermöglicht das Sichern von Parametern in einer JSON-Datei.

Eine neue Bibliothek für den DHT22 sollte zuverlässigere Ergebnisse liefern.

Konsolidierte Datentypen und Wertetypen: Neue Datentypen `VT_YEAR`, `VT_DAYMONTH` und `VT_TIME` als Untergruppen von `VT_DATETIME` für die Parameter 1-3, die `VT_SUMMERPERIOD` ersetzen und `VT_VACATIONPROG` anpassen. Neue Wertetypen `DT_THMS` für Zeitangaben in Stunden:Minuten:Sekunden.

MQTT: Verwenden Sie `MQTTDeviceID` als Client-ID für den Broker, standardmäßig ist dies weiterhin `BSB-LAN`. ACHTUNG: Überprüfen Sie Ihre Konfiguration, falls Ihr Broker die Client-ID für die Autorisierung oder ähnliches benötigt.

##Version 1.1##
**10.11.2020**

- **ACHTUNG:** Der Parameter „DHW Push“ („Trinkwasser Push“) musste von 1601 auf 1603 verschoben werden, da 1601 auf einigen Heizungen eine andere „offizielle“ Bedeutung hat. Bitte überprüfen Sie Ihre Konfiguration und nehmen Sie ggf. Änderungen vor.
- **ACHTUNG:** Es wurden neue Kategorien hinzugefügt, sodass sich die meisten Kategorienummern (mit `/K`) um einige Nummern verschieben werden.
- Der URL-Befehl `/JA` gibt Durchschnittswerte aus.
- Viele neue dekodierte Parameter.
- Neue Parameter für die Gerätefamilien 25, 44, 51, 59, 68, 85, 88, 90, 96, 97, 108, 134, 162, 163, 170, 195, 209, 211.
- Verbesserte mobile Darstellung der Weboberfläche.
- Hinzugefügte Definition „BtSerial“ zum Umleiten der seriellen Ausgabe auf Serial2, wo ein Bluetooth-Adapter angeschlossen werden kann (5V->5V, GND->GND, RX->TX2, TX->RX2). Der Adapter muss im Slave-Modus und mit 115200 bps, 8N1 konfiguriert sein.
- Viele neue polnische Übersetzungen.
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
- Code-Optimierung und -Restrukturierung, allgemeine Leistungssteigerung.
- Neue Schemata für das Platinenlayout V3.
- Viele Fehlerbehebungen.

##Version 0.44##
**11.05.2020**

- Hinzugefügte Webserver-Funktionalität über SD-Karte und verschiedene andere Verbesserungen von GitHub-Benutzer dukess.
- Hinzugefügte JSON-Ausgabe für MQTT.
- Mobile-freundlichere Weboberfläche.
- Weitere Parameter und Gerätefamilien.
- Letzte Version, die vollständig auf dem Mega 2560 getestet wurde. Künftige Versionen können zwar weiterhin auf dem Mega ausgeführt werden, werden aber nur auf dem Arduino Due getestet.

##Version 0.43##
**20.02.2020**

- Unterstützung für HardwareSerial (Serial1) Verbindung des Adapters hinzugefügt. Verwenden Sie den RX-Pin 19 in der Bus()-Definition, um ihn zu aktivieren. Weitere Informationen zur Hardware finden Sie im Handbuch/Forum.
- Hinzugefügte Definition DebugTelnet, um die serielle Ausgabe an einen Telnet-Client (Port 23, kein Passwort) in `BSB_LAN_config.h` umzuleiten.
- Möglichkeit hinzugefügt, BSB-LAN (fast) vollständig über den USB-Seriellen-Port zu steuern. Die meisten Befehle werden wie ihre URL-Gegenstücke unterstützt, d. h. `/<Passwort>/xxx` zum Abfragen des Parameters xxx oder `/<Passwort>/N` zum Neustart des Arduino.
- Standard-Geräte-ID von 6 (Raumregler „RGT1“) auf ungenutzte ID 66 („LAN“) geändert.
- Viele neue Parameter, führen Sie `/Q` aus, um mögliche Änderungen für Ihre Gerätefamilie zu sehen, und senden Sie uns Feedback!
- Globale Variablen (Arrays von 20 Bytes) `custom_floats[]` und `custom_longs[]` hinzugefügt, die mit `BSB_LAN_custom.h` verwendet werden können, z. B. zum Lesen von Sensoren usw. Die Ausgabe dieser Variablen erfolgt über den neuen URL-Befehl `/U`.
- Gerätefamilien 23 und 29 (Grünenwald-Heizungen) hinzugefügt.
- Gerätefamilien 49, 52, 59 (Weishaupt-Heizungen) hinzugefügt.
- Gerätefamilien 91, 92, 94, 118, 133, 136, 137, 165, 184, 188 (verschiedene Regler wie QAA75 oder AVS37) hinzugefügt.
- Gerätefamilie 171 (Bösch Holzpelletsystem) hinzugefügt.
- Gerätefamilie 172 (SensoTherm BLW Split B (RVS21.826F/200)) hinzugefügt.
- Gerätefamilien 186 und 164 (Olymp WHS-500) hinzugefügt.
- Gerätefamilie 195 Variante 2 (Thision 19 Plus / LMS14.111B109) hinzugefügt.
- Einschließlich DHT, 1Wire und Brennerstatusparameter (>20000) für MQTT.
- Englisch ist nun die Standardsprache.
- Verschiedene Übersetzungen aktualisiert.
- STL-Dateien hinzugefügt, um ein Gehäuse mit einem 3D-Drucker zu drucken (danke an den FHEM-Benutzer EPo!).
- Alle Sensoren wurden zu `/T` verschoben, `/H` wird nun nicht mehr verwendet.
- Neue virtuelle Parameter 702/703 für Weishaupt-Raumregler.
- Neuer virtueller Parameter 10003, um die Außentemperatur auf neueren Systemen festzulegen.
- Textbeschreibungen für Fehlerphasen (6706 ff.) hinzugefügt.
- `/Q` ist nun umfassender.
- Neue Datentypen `VT_CUSTOM_ENUM` und `VT_CUSTOM_BYTE` zum Extrahieren von Informationen aus nicht standardisierten Telegrammen (wie 702/703) hinzugefügt.
- Fehlerbehebung: DHCP (Ethernet)-Implementierung.

##Version 0.42##
**21.03.2019**

- Lokalisierung hinzugefügt! Jetzt können Sie bei der Übersetzung von BSB-LAN in Ihre Sprache helfen! Kopieren Sie einfach eine der Sprachdateien aus dem Lokalisierungsordner (`LANG_DE.h` ist die vollständigste) und übersetzen Sie, was Sie können. Nicht übersetzte Elemente werden in Deutsch angezeigt.
   Achtung: Die Sprachdefinition in `BSB_LAN_config.h` lautet nun `#define LANG <ISO-CODE>`
   Beispiel: `#define LANG DE`
- Export zum MQTT-Broker hinzugefügt, verwenden Sie `log_parameters`[] in `BSB_LAN_config.h`, um Parameter zu definieren und die `MQTTBrokerIP`-Definition zu aktivieren.
- Unterstützung für WLAN-Module wie ESP8266 oder Wemos Mega hinzugefügt, die an Serial3 (RX:15/TX:14) des Arduino angeschlossen sind.
   Der ESP8266 muss mit der AT-Firmware von Espressif geflasht werden, um zu funktionieren.
   Bitte beachten Sie, dass WLAN über Serial deutlich langsamer ist (nur 115kpbs) als „reine“ TCP/IP-Verbindungen.
- Neue Kategorie „34 - Konfiguration / Erweiterungsmodule“ hinzugefügt. Alle nachfolgenden Kategorien verschieben sich um eine Nummer nach oben!
- Viele neue Parameter aus der Gerätefamilie 123, führen Sie `/Q` aus, um zu sehen, ob einige Parameter auch für Ihre Heizung funktionieren!
- Viele neue, noch unbekannte Parameter durch Brute-Force-Abfragen hinzugefügt :) (Parameternummern 10200 und höher).
- Weitere PPS-Bus-Befehle hinzugefügt, Parameternummern auf 15000 und höher verschoben.
- Der Standard-PPS-Modus ist nun „listening“.
   Verwenden Sie den dritten Parameter der Bus-Definition, um zwischen „listening“ und „controlling“ zu wechseln, 1 steht für „controlling“, alles andere für „listening“,
   d. h. BSB bus(68,67,1) sendet Daten an die Heizung, BSB bus(68,67) empfängt nur Daten von der Heizung/Raumregler.
   Sie können zwischen den Modi zur Laufzeit mit dem URL-Befehl `/P2,x` wechseln, wobei x entweder 1 (für „controlling“) oder nicht 1 (für „listening“) ist.
- Fehler behoben, der PPS-Bus-Abfragen zum Absturz brachte.
- Stabilitätsverbesserungen für den PPS-Bus.
- Legende beim Plotten mehrerer Parameter verbessert.
- JSON-Export hinzugefügt; Abfrage mit `/JQ=a,b,c,d...` oder Push-Abfragen an `/JQ` oder Push-Set-Befehle an `/JS`.
- Protokollierung von MAX!-Parametern nun mit dem Protokollparameter 20007 möglich.
- Waterstage WP-Gerätefamilie (119) hinzugefügt.
- WHG Procon-Gerätefamilie (195) hinzugefügt.
- Einheit in die Protokolldatei sowie in die Durchschnittsausgabe aufgenommen.
- Gerätematching in `cmd_tbl` neu geschrieben, um auch die Gerätevariante zu berücksichtigen. Führen Sie `/Q` aus, um zu sehen, ob der Übergang für Ihr Gerät funktioniert hat!
- `BSB_LAN_custom_setup.h` und `BSB_LAN_custom_global.h` hinzugefügt, damit Sie individuellen Code hinzufügen können (am besten in Verbindung mit `BSB_LAN_custom.h`).
- Alle (bekannten) OEM-Parameter mit der Flagge `FL_OEM` markiert. OEM-Parameter sind standardmäßig schreibgeschützt. Um sie beschreibbar zu machen, ändern Sie `FL_OEM` von 5 auf 4 in `BSB_LAN_defs.h`.
- Leistung beim Abfragen mehrerer Parameter gleichzeitig (ähnlich wie bei der Kategoriesuche) verbessert.
- Konfigurationsoption zum Definieren des Subnetzes hinzugefügt.
- `/Q` benötigt nun nicht mehr `#define DEBUG`.
- Fehlerbehebung ENUM-Speicheradressierung.
- Fehlerbehebung in der Reset-Funktion `/N`, EEPROM während des Resets mit `/NE` löschen.
- favicon.ico hinzugefügt.
- Aufteilung von cmdtbl in cmdtbl1 und cmdtbl2 aufgrund der Arduino-Grenze (?) von 32 kB Größe der Struktur, wodurch mehr Platz für neue Parameter geschaffen wird.

##Version 0.41##
**17.03.2019**

- Zwischenversion, die alle Änderungen von 0.42 oben enthält, mit Ausnahme der Lokalisierung, d. h. alle Textfragmente sind weiterhin Teil des Hauptcodes.

##Version 0.40##
**21.01.2018**

- Abfrage von MAX!-Heizungsthermostaten implementiert, Anzeige mit dem URL-Befehl `/X`
   Siehe `BSB_LAN_custom.h` für ein Beispiel zum Übertragen der durchschnittlichen Raumtemperatur an das Heizungssystem.
- Neue Kategorie „22 - Energiezähler“ hinzugefügt – beachten Sie, dass sich alle nachfolgenden Kategorien um eine verschieben!
- Neuer virtueller Parameter 1601 (manueller TWW-Push).
- Fujitsu Waterstage WSYP100DG6-Gerätefamilie (211) hinzugefügt.
- CTC-Gerätefamilie (103) hinzugefügt.
- Neue Definition `#define TRUSTED_IP2` hinzugefügt, um den Zugriff auf eine zweite lokale IP-Adresse zu gewähren.
- Optionale Definition `#define GatewayIP` in `BSB_LAN_config.h` hinzugefügt, um die Routeradresse anders als x.x.x.1 festzulegen.
- Parameter 10109 entfernt, da er derselbe ist wie 10000.
- Funktion zum Überprüfen aller bekannten CommandIDs auf Ihrem eigenen Heizungssystem hinzugefügt. Verwenden Sie `/Q`, nachdem Sie die Definition `#define DEBUG` in `BSB_LAN_config.h` aktiviert haben.
- Parameternummern zum Kategorienmenü hinzugefügt.
- analyze.sh aktualisiert.
- Behebung des Speicherproblems.
- HTML-Zeichenfolgen in `html_strings.h` verschoben.

##Version 0.39##
**02.01.2018**

- Implementierung des PPS-Bus-Protokolls.
   Siehe `/K40` für die begrenzten Befehle, die für diesen Bus verfügbar sind.
   Verwenden Sie setBusType(2), um den Bus-Typ beim Booten auf PPS festzulegen, oder `/P2`, um ihn temporär zu wechseln.
- GPIOs mit `/Gxx,I` auf Eingabe setzen.
- Definition `#define CUSTOM_COMMANDS` hinzugefügt.
   Verwenden Sie dies in Ihrer Konfiguration, um individuellen Code aus `BSB_LAN_custom.h`
   (muss von Ihnen erstellt werden!) einzubinden, der am Ende jeder Haupt-Schleife ausgeführt wird.
   Die Variablen `custom_timer` und `custom_timer_compare` wurden hinzugefügt, um
   Code in beliebigen Intervallen auszuführen.
- LogoBloc Unit L-UB 25C-Gerätefamilie (95) hinzugefügt.
- Verschiedene neue Parameter hinzugefügt.
- Fehlerbehebung für die Protokollierung der Brennerlaufzeit Stufe 2.

##Version 0.38##
**22.11.2017**

- **ACHTUNG:** Neue `BSB_LAN_config.h`-Konfigurationen! Sie müssen Ihre Konfiguration anpassen, wenn Sie auf diese Version aktualisieren!
   Der Webserver-Port wird nun in `#
## Version 0.34 ##
**29.05.2017**

- Logdaten können nun als Graph angezeigt werden
- Das Webinterface kann nun `VT_BIT`-Typ-Parameter in einer für Menschen lesbaren Form anzeigen und festlegen
- KonfigRGx-Beschreibungen hinzugefügt; Vorsicht: Es wurden verschiedene Quellen verwendet, es gibt keine Garantie, dass die Beschreibungen zu Ihrem individuellen Heizungssystem passen!
- `VT_BIT` ist im Webinterface standardmäßig schreibgeschützt. Um es festzulegen, verwenden Sie den URL-Befehl `/S` mit der dezimalen Darstellung des Werts
- Ein Fehler im Zusammenhang mit `VT_SECONDS_SHORT5` wurde behoben, der die Parameter 9500 und 9540 betraf
- Ein Fehler im Zusammenhang mit der Gerätefamilie von Fujitsu (von 127 bis 170) wurde behoben
- Bibliotheken aus dem Ordner "libraries" in den Ordner "src" verschoben, sodass sie ohne Kopieren in den Arduino-Bibliotheksordner einbezogen werden können
- Den Include-Pfad für "OneWire.h" in "DallasTemperature.h" geändert

## Version 0.33 ##
**09.05.2017**

- Keine Heizungssystem-Definitionen mehr aufgrund der neuen Auto-Detect-Funktion, die auf der Gerätefamilie (Parameter 6225) basiert, oder legen Sie die `device_id`-Variable direkt auf den Parameterwert fest
- Zwei weitere Sicherheitsoptionen: `TRUSTED_IP`, um den Zugriff auf eine einzige IP-Adresse zu beschränken, und HTTP-Authentifizierung mit Benutzername und Passwort
- Durchschnittswerte werden auf der SD-Karte gespeichert, sofern vorhanden und die LOGGER-Definition aktiviert ist
- Deaktivieren Sie die Protokollierung, indem Sie `/L0=0` festlegen, sodass Sie die LOGGER-Definition aktivieren können, ohne die SD-Karte zu füllen, aber dennoch Durchschnittswerte speichern können
- Neue Fehlercodes für THISION
- Daten-Payload-Dump auf der Website für Befehle unbekannten Typs hinzugefügt, nicht unterstützte Parameter abgeblendet
- Aktivieren Sie die Protokollierung von Telegrammen (Protokollparameter 30000) auch im Monitor-Modus (bsb.cpp und bsb.h aktualisiert)
- Die Uhrzeit des Heizungssystems wird nun periodisch aus Broadcast-Telegrammen abgerufen, was die Busaktivität weiter reduziert
- Neuer Datentyp `VT_BIT` für Parameter, die einzelne Bits festlegen. Wird als Binärzahlen angezeigt, die Einstellung erfolgt weiterhin mithilfe der dezimalen Darstellung
- Neuer Datentyp `VT_TEMP_SHORT5_US` für unsignierte einbyte-Temperaturen, geteilt durch 2 (bisher nur 887 Vorlaufsoll NormAussentemp)
- Neuer Datentyp `VT_PERCENT5` für unsignierte einbyte-Temperaturen, geteilt durch 2 (bisher nur 885 Pumpe-PWM Minimum)
- Neuer Datentyp `VT_SECONDS_WORD5` für zwei Byte-Sekunden, geteilt durch 2 (bisher nur 2232, 9500 und 9540)
- Neuer Datentyp `VT_SECONDS_SHORT4` für (signierte?) einbyte-Sekunden, geteilt durch 4 (bisher nur 2235)
- Neuer Datentyp `VT_SECONDS_SHORT5` für (signierte?) einbyte-Sekunden, geteilt durch 5 (bisher nur 9500, 9540)
- Neuer Datentyp `VT_SPEED2` für zwei Byte-Umdrehungen pro Minute (bisher nur 7050)
- Die set()-Funktion von offensichtlichen Duplikaten bereinigt
- Fälle für `VT_TEMP_WORD`, `VT_SECONDS_WORD5`, `VT_TEMP_SHORT`, `VT_TEMP_SHORT5`, `VT_SECONDS_SHORT4` zur set()-Funktion hinzugefügt

## Version 0.32 ##
**18.04.2017**

- Viele neue unterstützte Parameter
- Das neu gestaltete Webinterface ermöglicht die Steuerung des Heizungssystems ohne zusätzliche Software oder kryptische URL-Befehle. URL-Befehle sind natürlich weiterhin verfügbar, sodass Sie nichts ändern müssen, wenn Sie FHEM etc. verwenden
- Deutsches Webinterface mit der Definition `LANG_DE` verfügbar
- Neuer URL-Befehl `/LB=x` zum Protokollieren nur von Broadcast-Nachrichten (x=1) oder allen Busnachrichten (x=0)
- Neuer URL-Befehl `/X` zum Zurücksetzen des Arduino (die Definition RESET in `BSB_LAN_config.h` muss aktiviert sein)
- Neue Protokollierungsparameter 20002 und 20003 für Ladezeiten und Zyklen von Warmwasser
- DS18B20-Protokollierungsparameter von 20010-20019 auf 20200-20299 und DHT22-Protokollierungsparameter von 20020-20029 auf 20100-20199 verschoben
- Durchschnittlicher Protokollierungsparameter von 20002 auf 20004 verschoben
- Verschiedene Parameter auf schreibgeschützt festgelegt, da sie offensichtlich schreibgeschützt sind (K33-36)
- Verschiedene Fehlerbehebungen

## Version 0.31 ##
**10.04.2017**

- Die Protokolldatei-Dumping-Rate um den Faktor 5 erhöht / Solange wir noch Speicherplatz haben, können Sie logbuflen von 100 auf 1000 erhöhen, um die Übertragungsgeschwindigkeit von ca. 16 auf 18 kB/s zu erhöhen
- Die Überwachung der Brenneraktivität basierend auf Broadcast-Nachrichten für Brötje-Systeme angepasst
- Die Definition `PROGNR_5895` entfernt, da sie bisher nur eine ENUM-Definition deaktiviert hat
- Die Definition `PROGNR_6030` entfernt, da der doppelte Befehls-ID über die Definitionen BROETJE/nicht-BROETJE aufgelöst werden konnte
- `BROETJE_SOB` in BROETJE umbenannt, um eine feinere Unterscheidung zwischen verschiedenen BROETJE-Fällen zu ermöglichen (z. B. 6800ff)
   Das bedeutet, dass Sie beim Einsatz eines Brötje-Systems nun ZWEI Definitionen aktivieren müssen: Die allgemeine BROETJE-Definition sowie `BROETJE_SOB` oder `BROETJE_BSW`.
   Werfen Sie einen Blick auf Ihr serielles Protokoll für die Parameter 6800, um zu sehen, welche Befehls-IDs zu Ihrem System passen, und aktivieren Sie eine von beiden entsprechend.
- Die 16-Bit-Adressierung des Flash-Speichers in 32-Bit geändert, um Abstürze aufgrund immer größerer PROGMEM-Tabellen zu beheben - jetzt haben wir wieder viel Platz zum Atmen für neue Befehls-IDs :)
- Nachgestelltes \0-Zeichen aus mehreren ENUMs entfernt, das zu falschen ENUM-Auflistungen führte. Bitte beachten Sie, dass ENUMs nicht mit einem nachgestellten \0 enden sollten!

## Version 0.30 ##
**22.03.2017**

- Die Time-Bibliothek von Paul Stoffregen (https://github.com/PaulStoffregen/Time) ist nun erforderlich und im Bibliotheksordner enthalten.
- Fügt die Protokollierung roher Telegrammdaten auf der SD-Karte mit dem Protokollierungsparameter 30000 hinzu. Die Protokollierung von Telegrammdaten wird durch die Befehle `/V` und `/LU` beeinflusst
- Fügt den Befehl `/LU=x` hinzu, um nur bekannte (x=0) oder unbekannte (x=1) Befehls-IDs zu protokollieren, wenn Telegrammdaten protokolliert werden
- Die Definition `USE_BROADCAST` entfernt, Broadcast-Daten werden nun immer verarbeitet
- Neue interne Funktionen GetDateTime, TranslateAddr, TranslateType

## Version 0.29 ##
**07.03.2017**

- Fügt den Befehl `/C` hinzu, um die aktuelle Konfiguration anzuzeigen
- Fügt den Befehl `/L` hinzu, um das Protokollierungsintervall und die Parameter zu konfigurieren
- Fügt für den Befehl `/A` die Option hinzu, 24-Stunden-Durchschnittsparameter während der Laufzeit festzulegen
- Fügt den speziellen Parameter 20002 für die Protokollierung des Befehls `/A` (24-Stunden-Durchschnitte, macht nur bei langen Protokollierungsintervallen Sinn) hinzu
- Fehlerbehebungen für die Protokollierung von DS18B20-Sensoren

## Version 0.28 ##
**05.03.2017**

- Fügt spezielle Parameter 20000++ für die SD-Karten-Protokollierung der Befehle `/B,` `/T` und `/H` hinzu (siehe `BSB_LAN_config.h` für Beispiele)
- Fügt Versionsinformationen zur `BSB_LAN`-Weboberfläche hinzu

## Version 0.27 ##
**01.03.2017**

- Fügt ein Datumsfeld zur Protokolldatei hinzu (erfordert die genaue Zeit, die vom Heizungssystem gesendet wird)
- `/D0` erstellt die Datei datalog.txt neu mit einer Tabellenkopfzeile
- Dem Befehls-Tabellen-Struktur wurde das Feld "flags" hinzugefügt. Derzeit wird nur `FL_RONLY` unterstützt, um einen Parameter schreibgeschützt zu machen
- `DEFAULT_FLAG` in der Konfiguration hinzugefügt. Standardmäßig auf `NULL` gesetzt, d. h. alle Felder sind les-/schreibbar.
   Wenn Sie es auf `FL_RONLY` setzen, werden alle Parameter schreibgeschützt, z. B. für eine zusätzliche Sicherheitsebene.
   Einzelne Parameter können auf `NULL`/`FL_RONLY` gesetzt werden, um nur diese Parameter schreibbar/schreibgeschützt zu machen.

## Version 0.26 ##
**27.02.2017**

- Funktionalität für die Protokollierung auf einer Micro-SD-Karte mithilfe des Steckplatzes des W5100-Ethernet-Shields hinzugefügt
- Weitere Parameter hinzugefügt (z. B. 8009)

## Version 0.25 ##
**21.02.2017**

- Weitere FUJITSU-Parameter hinzugefügt

## Version 0.24 ##
**14.02.2017**

- README mit hinzugefügten Funktionen aktualisiert
- Deutsche Übersetzungen von FAQ und README hinzugefügt, bereitgestellt von Ulf Dieckmann

## Version 0.23 ##
**12.02.2017**

- Kleiner Fehlerbehebung

## Version 0.22 ##
**07.02.2017**

- Weitere FUJITSU-Parameter
- (Hoffentlich) korrekte Implementierung von `VT_VOLTAGE`-Messwerten
- Kleinere Fehlerbehebungen

## Version 0.21 ##
**06.02.2017**

- Hinzugefügt wurden zahlreiche Parameter für die Fujitsu-Wärmepumpe, einschließlich der neuen `#define FUJITSU`-Direktive zur Aktivierung dieser Parameter aufgrund unterschiedlicher Parameternummern
- Kleinere Fehlerbehebungen

## Version 0.20 ##
**27.01.2017**

- Hinzugefügt wurden weitere Parameter für Feststoffkessel
- Kleinere Fehlerbehebungen

## Version 0.19 ##
**01.01.2017**

- Hinzugefügt wurde der Feuchtigkeitsbefehl `/H`, derzeit für DHT22-Sensoren
- Hinzugefügt wurde der 24-Stunden-Durchschnittsbefehl `/A`, definieren Sie die Parameter in `BSB_LAN_config.h`
- Entfernt wurden nachfolgende Leerzeichen aus Menüzeichenfolgen
- Beheben wurde die Befehls-ID 0x053D04A2 für THISION-Heizgeräte
- Rob Tillaarts DHT-Bibliothek wurde einbezogen, da es verschiedene Bibliotheken gibt, die das Protokoll implementieren, und diese hier verwendete Bibliothek ermöglicht es, mehrere Sensoren mit einem Objekt anzusprechen.
- Entfernt wurde der URL-Parameter `/temp`, da er eine Duplikat von `/T` ist
- Einbezogen wurde eine Schleife, um DHT22-Sensoren in IPWE anzuzeigen
- Das Kompilieren von IPWE-Erweiterungen ist nun optional (`#define IPWE`)

## Version 0.18 ##
**22.12.2016**

- Die Konfiguration wurde in `bsb_lan_config.h` ausgelagert
- Die Befehlsdefinitionen wurden in `bsb_lan_defs.h` ausgelagert
- Die GPIO-Rückgabewerte wurden von LOW/HIGH in 1/0 geändert
- IPWE wurde reaktiviert und aktualisiert (definieren Sie die Parameter in der Konfiguration)
- Beim Zugriff auf GPIO wird nun überprüft, ob die Pins geschützt sind (in der Konfiguration definieren)
- In den neuen Unterordner "schematics" wurden Schaltpläne und PCB-Dateien hinzugefügt

## Version 0.17a ##
**20.12.2016**

- Kleinere Fehler wurden korrigiert

## Version 0.17 ##
**20.12.2016**

- Version 0.16 wurde mit den Änderungen von FHEM-Benutzer miwi zusammengeführt

## Version 0.16 ##
**20.11.2016**

- IPWE- und EthRly-Schnittstelle entfernt
- GPIO-Schnittstelle hinzugefügt
- Parameter von J.Weber zusammengeführt
- Duplizierte Befehls-IDs aufgelöst

## Version 0.15a ##
**25.07.2016**

- Die Befehle aus einem Python-Projekt und diesem Projekt wurden zusammengeführt,
   die beiden Versionen wurden zusammengeführt, offensichtliche Fehler wurden korrigiert.
   In ENUM-Definitionen wurden hypothetische numerische Werte eingefügt,
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
- Den Enum8005 wurden die Werte 0x0f und 0x10 hinzugefügt
- Die Zeichenfolgen für Zeitprogramme wurden korrigiert
- Für das Senden einer Nachricht wurde ein Timeout (1 Sekunde) hinzugefügt
- `/T` wurde hinzugefügt, um One-Wire-Temperatursensoren in gemischten Abfragen abzufragen
- Spezielle Behandlung für Broetje SOB hinzugefügt
- Einstellungen vereinfacht

## Version 0.12 ##
**09.04.2015**

- `ONEWIRE_SENSORS` zu ipwe hinzugefügt
- Parameterdecodierung für das ELCO Thision-Heizungssystem korrigiert

## Version 0.11 ##
**07.04.2015**

- Parameterdecodierung für das ELCO Thision-Heizungssystem korrigiert

## Version 0.10 ##
**15.03.2015**

- Weitere Parameter für das ELCO Thision-Heizungssystem hinzugefügt

## Version 0.9 ##
**09.03.2015**

- Weitere Parameter für das ELCO Thision-Heizungssystem hinzugefügt
- printTelegramm gibt den Wertestring für die weitere Verarbeitung zurück

## Version 0.8 ##
**05.03.2015**

- Parameter für das ELCO Thision-Heizungssystem hinzugefügt
- IPWE-Erweiterung hinzugefügt
- Kleinere Fehlerbehebungen

## Version 0.7 ##
**06.02