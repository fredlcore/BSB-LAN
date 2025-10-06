# Verbindung von BSB-LAN mit Heimautomatisierungssystemen

BSB-LAN bietet vier Möglichkeiten, eine Verbindung zu Heimautomatisierungssystemen herzustellen:

1. Verwendung unterstützter Module für spezifische Heimautomatisierungssysteme
2. Austausch von Daten über MQTT
3. Austausch von Daten über JSON
4. Austausch von Daten über URL-Befehle und Screen Scraping

---

## Verwendung unterstützter Module für spezifische Heimautomatisierungssysteme

Für einige Systeme gibt es spezifische Module, die verwendet werden können, um nahtlos auf BSB-LAN zuzugreifen:

[](){#HomeAssistant}
### Home Assistant

Während das offizielle Plugin nicht mehr funktioniert, funktioniert der MQTT-Ansatz (siehe unten) gut mit Home Assistant, einschließlich der Auto-Discovery-Funktion.
Hier ist ein Link zu einem [Video im BSB-LAN YouTube-Kanal](https://youtu.be/DbHEiWm5nBs), das zeigt, wie man BSB-LAN in Home Assistant mithilfe der Auto-Discovery-Funktion von Home Assistant einrichtet.

Für weitere Details zur Implementierung kannst du auch auf diese Tutorials verweisen:

GitHub-User @ryann72 hat detaillierte Anweisungen für [BSB-LAN und HomeAssistant/Mosquitto](https://github.com/ryann72/Home-assistant-tutoriel/blob/main/BSB-LAN/tutoriel%20BSB-LAN%20English.md) geschrieben. Es ist auch auf [Französisch](https://github.com/ryann72/Home-assistant-tutoriel/blob/main/BSB-LAN/tutoriel%20BSB-LAN.md) verfügbar.

YouTuber @StoneTime hat zwei Videos (in Deutsch) erstellt, in denen er die [Installation von BSB-LAN](https://www.youtube.com/watch?v=n-5I-TUzXuk) sowie die [Einrichtung in Home Assistant](https://www.youtube.com/watch?v=R2Q-_flTPvk) zeigt. Vielen Dank!

YouTuber @ArminasTV hat zwei Videos (in Französisch) erstellt, in denen er die [Installation von BSB-LAN](https://www.youtube.com/watch?v=5lNgNYlZ7M0&t=0s) sowie die Einrichtung mit [Home Assistant und MQTT](https://www.youtube.com/watch?v=WtmKPo1xMio&t=411s) zeigt. Merci beaucoup!

[](){#Homebridge}
### Homebridge

BSB-LAN-User Michael hat ein [Plugin für Homebridge](https://www.npmjs.com/package/@bsblan/homebridge-bsblan-thermostat) geschrieben. Vielen Dank!

[](){#ioBroker}
### ioBroker

GitHub-User @hacki11 hat [einen Adapter für ioBroker](https://github.com/hacki11/ioBroker.bsblan) entwickelt. Vielen Dank!

[](){#Jeedom}
### Jeedom

GitHub-User @bernard-dandrea hat ein [Plugin für Jeedom](https://bernard-dandrea.github.io/jeedom-BSBLAN/fr_FR/) (mit einer französischen Beschreibung) geschrieben. Vielen Dank!

[](){#NodeRED}
### Node-RED

GitHub-User @konne hat ein [Modul für Node-RED](https://github.com/node-red-contrib/node-red-contrib-bsb-lan) geschrieben. Vielen Dank!

[](){#FHEM}
### FHEM

FHEM-Forum-User Luposoft hat eine kompakte [Erklärung](https://forum.fhem.de/index.php/topic,29762.msg1129702.html#msg1129702) der Konfiguration für die Verwendung von FHEM über MQTT geschrieben. Vielen Dank!

[](){#openHAB}
### openHAB

Seit Version 2.5.4 gibt es ein [Binding](https://www.openhab.org/addons/bindings/bsblan/), das offiziell Teil von OpenHAB ist.

[](){#Homematic}
### Homematic

FHEM-Forum-User PaulM hat [einige Skripte](https://forum.fhem.de/index.php?topic=29762.1830) geschrieben, um die Integration von BSB-LAN in Homematic zu demonstrieren. Vielen Dank!

[](){#SmartHomeNG}
### SmartHomeNG

GitHub-User @thensty hat ein [Plugin für SmartHomeNG](https://github.com/smarthomeNG/plugins/tree/develop/bsblan) geschrieben. Vielen Dank!

[](){#Volkszaehler}
### Volkszaehler

GitHub-User @lapixo hat ein [Skript für das Volkszaehler-Projekt](https://github.com/lapixo/volkszaehler_bsb-lan/tree/main) beigetragen. Vielen Dank!

[](){#Bash}
### Bash-Skript

GitHub-User @khfm hat [Bash-Skripte](https://github.com/khfm/bsb-lan-readout) geschrieben, um Daten abzufragen und sie mithilfe von gnuplot anzuzeigen. Vielen Dank!

---

[](){#MQTT}
## Austausch von Daten über MQTT

Dies ist die empfohlene Methode, um BSB-LAN mit Heimautomatisierungssystemen zu verbinden, da sie einen nahtlosen Datenaustausch ermöglicht.
Als Voraussetzung wird ein MQTT-Broker (wie z.B. [Mosquitto](https://mosquitto.org)) benötigt, der entweder lokal ausgeführt wird oder über einen öffentlichen Dienst genutzt werden kann. Einige Heimautomatisierungssysteme wie Home Assistant bieten die Installation von Mosquitto als Teil ihrer Software an.

**Achtung:** Derzeit scheint der Mosquitto-Broker ab Version 2.0.16 ein Problem mit der Verarbeitung einer großen Anzahl von Nachrichten zu haben ([siehe diesen Bug-Report](https://github.com/eclipse-mosquitto/mosquitto/issues/2887)). Wenn du das Problem hast, dass deine BSB-LAN-Entitäten als "nicht verfügbar" angezeigt werden, insbesondere nach der Verwendung der Auto-Discovery-Funktion unten, solltest du auf Mosquitto Version 2.0.15 herunterstufen. Beachte jedoch, dass diese Version Sicherheitslücken aufweist, daher solltest du sicherstellen, dass dein Broker mindestens in einer Firewall-Umgebung ausgeführt wird.

In BSB-LAN musst du mindestens die folgenden Konfigurationen vornehmen oder aktivieren:

- Setze den **Logging-Modus** (zusätzlich) auf **Senden an MQTT-Broker**.
- Setze das **Log-Intervall** auf die Zeit (in Sekunden), in der du die Log-Parameter veröffentlichen möchtest.
- Wähle bis zu 20 **Log-Parameter** aus, die du an dein Heimautomatisierungssystem senden möchtest.
- Setze die **MQTT-Nutzung** auf **Plain Text**.
- Setze den **MQTT-Broker-Server** auf den Hostnamen deines MQTT-Brokers (z.B. den Mosquitto-Server).

Wenn dein Heimautomatisierungssystem MQTT Auto-Discovery unterstützt (wie bei Home Assistant), kannst du den URL-Befehl `/M1!<x>` aufrufen und BSB-LAN wird Auto-Discovery-Nachrichten für **alle verfügbaren Parameter** vom Gerät mit der ID `<x>` an den MQTT-Broker und damit an das Heimautomatisierungssystem senden. Bitte beachte, dass alle Parameter als nur lesbar übermittelt werden, solange in den BSB-LAN Einstellungen der Schreibschutz für Parameter aktiv ist. Wenn diese Einstellung später in BSB-LAN geändert wird, muss man den Auto-Discovery-Prozess erneut starten.  
Möglicherweise musst du danach aufräumen oder eine Löschnachricht für alle diese Parameter mit dem URL-Befehl `/M0!<x>` senden, wenn du diese Funktion nicht mehr verwenden möchtest.

Wenn du deine eigenen Verbindungsdetails einrichten möchtest, ist die Topic-Struktur von BSB-LAN wie folgt:
`<BSB-LAN MQTT Topic>/<Geräte-ID>/<Kategorie-Nr.>/<Parameter-Nr.>`
wobei

- `<BSB-LAN MQTT Topic>` in den Einstellungen von BSB-LAN definiert ist (Standardwert ist `BSB-LAN`),
- `<Geräte-ID>` die ID des Heizungsreglers ist (in der Regel `0` für den Hauptregler),
- `<Kategorie-Nr.>` die Kategorienummer ist, wie sie mit dem URL-Befehl `/K` verwendet wird,
- `<Parameter-Nr.>` die Parameternummer ist, wie z.B. `501.1`.

Diese Struktur wird von einem der folgenden Topics gefolgt, die die auszuführende Aktion bestimmen:

- `/status` - enthält den Wert des Parameters in der MQTT-Payload.
- `/set` - wird verwendet, um einen Parameter mit dem Wert in der veröffentlichten MQTT-Payload mithilfe des SET-Telegramms (Standardmethode zum Festlegen von Parametern) zu setzen.
- `/inf` - ähnlich wie `/set`, verwendet aber das INF-Telegramm (wird z.B. zum Senden des Raumtemperaturparameters 10000 verwendet).
- `/poll` - ignoriert den veröffentlichten Wert und erzwingt, dass BSB-LAN den `/status` des gleichen Parameters sofort mit einem neu abgerufenen Parameterwert aktualisiert. `/poll` kann auch direkt unterhalb des Hauptthemas aufgerufen werden (z.B. `BSB-LAN/poll`), wo es eine Liste von Parametern akzeptiert, die durch Kommas getrennt sind. Die `/status`-Topics dieser Parameter werden dann in einem Schritt aktualisiert. Parameter können entweder im Topic-Stil (mit führendem Schrägstrich) oder ähnlich wie die Liste der Logging-Parameter in den BSB-LAN-Einstellungen adressiert werden (siehe Beispiele unten).

Gleichzeitig wird die Legacy-Methode zum Senden von URL-Befehlen über MQTT direkt an das Hauptthema (wie in den Einstellungen definiert, Standardwert ist `BSB-LAN`) aus Kompatibilitätsgründen weiterhin unterstützt, ist aber veraltet. Antworten werden immer an `/status` des oben genannten Topic-Struktur geschrieben.

Das `/status`-Topic wird auf vier Arten aktualisiert:

- über Logging-Parameter an MQTT, wie oben erklärt
- jedes Mal, wenn eine URL-Abfrage an BSB-LAN gesendet wird (kann deaktiviert werden, indem **Nur Logging-Parameter an MQTT senden** in der Konfiguration aktiviert wird)
- jedes Mal, wenn ein Parameter über die Raumsteuerung geändert wird (kann deaktiviert werden, indem **Nur Logging-Parameter an MQTT senden** in der Konfiguration aktiviert wird)
- jedes Mal, wenn der Parameter über das `/poll`-Topic aktualisiert wird, wie oben erklärt

In diesen Fällen werden die jeweiligen Werte der betroffenen Parameter an den MQTT-Broker gesendet, so dass auch Änderungen, die außerhalb von BSB-LAN vorgenommen wurden, an das Heimautomatisierungssystem gesendet werden. Aus diesem Grund ist der MQTT-Ansatz die empfohlene Methode, um eine Verbindung zu einem Heimautomatisierungssystem herzustellen.

Dies bedeutet auch, dass du als Alternative zur integrierten Logging-Funktion von BSB-LAN einfach periodisch eine URL mit den Parametern aufrufen kannst, die du aktualisiert sehen möchtest. Da diese Parameter auch an den MQTT-Broker gesendet werden, erhält dein Heimautomatisierungssystem sie ebenfalls.

Beispielsweise werden, wenn du die URL `http://bsb-lan.local/700/8700` periodisch aufrufst, sowohl der Betriebsmodus der Heizkreislauf 1 (Parameter 700) als auch die aktuelle Außentemperatur (Parameter 8700) an den MQTT-Broker gesendet.

### Beispiele für das Abfragen oder Setzen von Parametern über MQTT mit Mosquitto ###
Abfrage der Außentemperatur (Geräte-ID 0, Kategorie-Nr. 51, Parameter 8700):
`mosquitto_sub -h my.mosquitto-broker.local -u USER -P PASSWORD -t BSB-LAN/0/51/8700/status`

Setze die Komfort-Soll-Temperatur (Geräte-ID 0, Kategorie-Nr. 16, Parameter 710) auf 20 Grad:
`mosquitto_pub -h my.mosquitto-broker.local -u USER -P PASSWORD -m "20" -t BSB-LAN/0/16/710/set`

Erzwinge eine sofortige Aktualisierung der Außentemperatur (Geräte-ID 0, Kategorie-Nr. 51, Parameter 8700):
`mosquitto_pub -h my.mosquitto-broker.local -u USER -P PASSWORD -m "" -t BSB-LAN/0/51/8700/poll`

Erzwinge eine sofortige Aktualisierung der Parameter 700 und 8700 vom Standardgerät sowie des Parameters 8326 von Gerät mit der ID 1:
`mosquitto_pub -h my.mosquitto-broker.local -u USER -P PASSWORD -m "700,8700,8326!1" -t BSB-LAN/poll`
oder
`mosquitto_pub -h my.mosquitto-broker.local -u USER -P PASSWORD -m "/0/16/700,/0/51/8700,/1/50/8326" -t BSB-LAN/poll`

**Achtung:** Bitte beachte, dass die Kategorienummer von System zu System unterschiedlich ist und zuerst mit deinem System verglichen werden muss!

---
[](){#JSON}
## Austausch von Daten über JSON

BSB-LAN ermöglicht das Abfragen und Setzen von Parametern über JSON-Strukturen und stellt auf diese Weise auch zahlreiche Informationen über die Parameter und Kategoriestrukturen bereit. Die JSON-API wird über [URL-Befehle](using.md) aufgerufen und die `openapi.yaml`-Datei in diesem Repository kann mit [Swagger](https://editor.swagger.io/?url=https://raw.githubusercontent.com/fredlcore/bsb_lan/master/openapi.yaml) verwendet werden, um ihre Möglichkeiten und Funktionalitäten zu erkunden.

---
## Austausch von Daten über URL-Befehle und Screen Scraping

Für einfachere Lösungen können [die URL-Befehle][using] zum Abfragen und Setzen von Parametern verwendet werden, um BSB-LAN von anderen Systemen aus zu steuern. Screen Scraping ist möglich, da das Projekt versucht, bestimmte Arten der Datendarstellung nicht zu verändern, so dass das Parsing mit regulären Ausdrücken weiterhin funktioniert. Dennoch ist für die meisten Szenarien wahrscheinlich eine der anderen Optionen vorzuziehen.
