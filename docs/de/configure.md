# Konfiguration von BSB-LAN

Es gibt zwei Möglichkeiten, BSB-LAN zu konfigurieren:

1. Über die Konfigurationsdatei `BSB_LAN_config.h`
2. Über die Web-Oberfläche, indem du [http://bsb-lan.local/C](http://bsb-lan.local/C) (oder die entsprechende IP-Adresse) aufrufst

Für die initiale Konfiguration müssen einige Einstellungen in der Konfigurationsdatei vorgenommen werden, wie z.B. Sprache und Netzwerk-Einstellungen.

Alle weiteren Änderungen können auch über die Web-Oberfläche vorgenommen werden. Es kann aber sinnvoll sein, die Konfiguration (auch) in der Konfigurationsdatei vorzunehmen, falls man den Mikrocontroller austauschen muss. Fast alle Einstellungen sind sowohl in der Web-Oberfläche als auch in der Konfigurationsdatei verfügbar.

Auf einem ESP32-basierten Mikrocontroller richtet BSB-LAN seinen eigenen WLAN-Zugangspunkt mit dem Namen `BSB-LAN` ein, wenn es keine Verbindung zu einem Netzwerk herstellen kann. So kannst du dich auch ohne weitere Konfiguration mit diesem Zugangspunkt verbinden und das Passwort `BSB-LPB-PPS-LAN` verwenden, um BSB-LAN über die IP-Adresse `http://192.168.4.1` zu erreichen und mit der Konfiguration fortzufahren. Bitte beachte, dass ein Passwort oder HTTP-Benutzername und -Passwort weiterhin erforderlich sind, wenn diese Details in der EEPROM oder in `BSB_LAN_config.h` gespeichert sind.

---

## Konfiguration über `BSB_LAN_config.h`

Die Konfigurationsdatei besteht aus Variablen, die in anderen Teilen von BSB-LAN verwendet werden. Es ist daher wichtig, **nur den Inhalt** der Variablen (d.h. die Einstellungen) zu ändern und **nicht den Typ** der Variablen. Wenn es also zum Beispiel die Einstellung

`byte ip_addr[4] = {192,168,178,88};`

gibt, darfst du den Teil `byte ip_addr[4] =` nicht verändern, sondern nur den Inhalt, in diesem Fall die durch Kommas getrennte IP-Adresse.

---

## Konfiguration über die Web-Oberfläche

Die Konfiguration von BSB-LAN über die Web-Oberfläche ist relativ unkompliziert, da du dich nicht mit Variablennamen beschäftigen musst, sondern klare Beschreibungen vorgegeben sind.

Anfänglich werden nur eine ausgewählte Anzahl von Konfigurationsoptionen in der Web-Oberfläche angezeigt (im Folgenden **fett** markiert). Um Zugang zu allen Optionen zu erhalten, musst du die "erweiterte Konfiguration" auf "ein" setzen.

---

## Übersicht der Konfigurationsoptionen
<style>
table th:first-of-type {
    width: 20% ;
}
table th:nth-of-type(2) {
    width: 20% ;
}
table th:nth-of-type(3) {
    width: 40% ;
}
table th:nth-of-type(4) {
    width: 20% ;
}
</style>

### Allgemeine Einstellungen

| Web-Oberfläche | Konfigurationsdatei | Funktionalität | Mögliche Einstellungen |
| ------------- | ------------------- | ------------- | ------------------- |
| - | **`#define LANG`** | Sprache festlegen | `DE`, `EN`, `FR` und andere ISO-Ländercodes |
|**Anzeige der erweiterten Konfiguration**| - | Alle Konfigurationsoptionen anzeigen | **Ein** <br> **Aus** |
|**Konfiguration aus EEPROM lesen**| `UseEEPROM` | Konfiguration aus EEPROM oder Datei lesen | **Ein** (`1`) <br> **Aus** (`0`) |
| [](){#WriteAccess} Schreibzugriff (Level) | - | Wenn `DEFAULT_FLAG` auf `FL_SW_CTL_RONLY` gesetzt ist, kannst du hier den Level des Schreibzugriffs festlegen. | **Aus** (schreibgeschützt) <br> **Ein (Standard)** <br> **Ein (Komplett)** |
| Nach Updates suchen | `enable_version_check` | BSB-LAN Server nach neuen verfügbaren Versionen abfragen | **Ein** (`true`) |
| OTA Update | `enable_ota_update` | Over-the-Air (OTA) Update aktivieren | **Ein** (`true`) |
| Energiesparmodus | `esp32_save_energy` | Reduziert die Geschwindigkeit und spart Energie. Nicht aktivieren, wenn WLAN verwendet wird. | **Ein** (`true`) <br> **Aus** (`false`) |
| Webserver-Dateisystem | `webserver` | Ermöglicht das Bereitstellen von Dateien von der SD-Karte | **Ein** (`true`) <br> **Aus** (`false`) |
| - | `#define DEFAULT_FLAG` | Lese-/Schreibzugriff auf das Heizungssystem festlegen. `FL_RONLY` setzt alle Parameter auf schreibgeschützt. `FL_SW_CTL_RONLY` ermöglicht die Einstellung des Lese-/Schreibzugriffs über die Konfigurationseinstellung der Web-Oberfläche. <BR> `0` macht alle Parameter, die geschrieben werden könnten, beschreibbar. **Verwende diese Option nicht, es sei denn, du wirst angewiesen, dies zu tun!** | **FL_RONLY** <br> **FL_SW_CTL_RONLY** <br> **0** |

### Bus-Einstellungen

| Web-Oberfläche | Konfigurationsdatei | Funktionalität | Mögliche Einstellungen |
| ------------- | ------------------- | ------------- | ------------------- |
|**Bustyp**| `bus_type` | Bustyp (BSB/LPB/PPS) | **BSB** (`0`) <br> **LPB** (`1`) <br> **PPS** (`2`) |
|**PPS: Modus**| `pps_write` | BSB-LAN kann als PPS-Raumgerät agieren (nur wenn kein echtes Raumgerät angeschlossen ist) oder nur passiv zuhören. | **passiv** (`0`) <br> **als Raumgerät** (`1`) |
|**PPS: QAA-Modell**| `QAA_TYPE` | Raumgerät, das für den PPS-Bus simuliert werden soll | **QAA70** (`0x53`), **QAA50** (`0x52`), **QAA95** (`0x37`), **QAW10** (`0x4D`), **QAW20** (`0x4E`), **MCBA/REA70/DC225** (`0x58`), **QAA10** (`0x5A`), **QAA20** (`0x5B`), **QAA12/13** (`0x5D`), **BMU** (`0x66`), **RVD130** (`0x43`) |
| Eigene Adresse | `own_address` | Eigene Bus-Adresse (Standard `66` sollte nicht geändert werden) | **66** (`66`) |
| Zieladresse | `dest_address` | Ziel-Bus-Adresse. <br> Für **BSB** immer `0`. <br> Für **LPB** `0`, wenn das Zielgerät im Segment 1, Geräteadresse 0 ist. <BR> Um von der LPB-Segment- und Geräteadress-Notation zur Zieladresse zu wechseln, multipliziere das Segment mit 16, addiere die Geräteadresse und ziehe eins ab. Um zum Beispiel ein Gerät im Segment 4 mit der Geräteadresse 3 anzusprechen, ist die Zieladresse `(4 * 16) + 3 - 1 = 66`. <br> Für **PPS** nicht relevant. | **0** (`0`) |
| RX-Pin-Nummer <br> TX-Pin-Nummer | `bus_pins` | Definiere die RX/TX-Pins, um mit dem BSB-LAN-Adapter zu kommunizieren. Bei `0` bleibt die Auto-Detection aktiviert. | **0** und **0** (`0, 0`) |

### Netzwerk-Einstellungen

| Web-Oberfläche | Konfigurationsdatei | Funktionalität | Mögliche Einstellungen |
| ------------- | ------------------- | ------------- | ------------------- |
| **Netzwerkgerät** | `network_type` | Wähle zwischen WLAN und LAN, um BSB-LAN mit dem Netzwerk zu verbinden. | **LAN** (`0`) <br> **WLAN** (`1`) |
| **WLAN SSID** | `wifi_ssid` | Setze den WLAN-Netzwerknamen, wenn du WLAN verwendest. | **Dein_WLAN-Name** (`Your_WLAN_name`) |
| **WLAN Passwort** | `wifi_pass` | Setze das WLAN-Passwort, wenn du WLAN verwendest. | **DeinWLANPasswort** (`YourWLANpassword`) |
| DHCP-Nutzung | `use_dhcp` | Setze, ob DHCP verwendet werden soll, um eine IP-Adresse vom Router zu beziehen. | **Ein** (`true`) <br> **Aus** (`false`) |
| IP-Adresse (fest) | `ip_addr` | Wenn du *kein* DHCP verwendest, kannst du hier eine feste IP-Adresse einstellen. Ansonsten lasse es bei `0.0.0.0`. In der Web-Oberfläche kannst du die Punkt-Notation verwenden. In der Konfigurationsdatei musst du ein Komma als Trennzeichen verwenden. | **192.168.178.88** (`192,168,178,88`) |
| Subnetz | `subnet_addr` | Subnetz-Adresse, wenn eine feste IP-Adresse verwendet wird. Verwende die gleiche Notation wie bei der IP-Adresse. | **255.255.255.0** (`255,255,255,0`) |
| Gateway | `gateway_addr` | Gateway-Adresse, wenn eine feste IP-Adresse verwendet wird. Verwende die gleiche Notation wie bei der IP-Adresse. | **192.168.178.1** (`192,168,178,1`) |
| DNS-Server | `dns_addr` | DNS-Server-Adresse, wenn eine feste IP-Adresse verwendet wird. Verwende die gleiche Notation wie bei der IP-Adresse. | **192.168.178.1** (`192,168,178,1`) |
| TCP-Port | `HTTPPort` | HTTP-Port-Nummer, um auf die Web-Oberfläche zuzugreifen. Standardmäßig ist es `80`. | **80** (`80`) |
| MAC-Adresse | `mac` | Setze eine feste MAC-Adresse. Nur relevant für Arduino. | **00:80:41:19:69:90** (`0x00, 0x80, 0x41, 0x19, 0x69, 0x90`) |
| mDNS-Hostname | `mDNS_hostname` | Hostname für mDNS-Discovery | **BSB-LAN** (`BSB-LAN`) |
| HTTP-Authentifizierung | `USER_PASS` | Wenn nicht leer, enthält diese Einstellung den Benutzernamen und das Passwort für die HTTP-Authentifizierung, getrennt durch einen Doppelpunkt. | **Benutzername:Passwort** (`Username:Password`) |
| URL-Passwort | `PASSKEY` | Das Passwort fügt eine benutzerdefinierte Sequenz hinzu, die nach dem Hostnamen in die URL eingefügt werden muss. <BR> Zum Beispiel erfordert ein Passwort von `1234`, dass jede URL wie folgt geschrieben wird: `http://bsb-lan.local/1234/` anstatt einfach `http://bsb-lan.local/`. Lass es leer, wenn du kein Passwort verwenden möchtest. | **1234** (`1234`) |
| Vertrauenswürdige IP-Adresse | `trusted_ip_addr` | Der Zugriff auf BSB-LAN ist nur von dieser IP-Adresse aus möglich. Verwende die gleiche Notation wie bei der IP-Adresse. | **192.168.178.89** (`192,168,178,89`) |
| Vertrauenswürdige IP-Adresse | `trusted_ip_addr2` | Der Zugriff auf BSB-LAN ist nur von dieser IP-Adresse aus möglich. Verwende die gleiche Notation wie bei der IP-Adresse. | **192.168.178.90** (`192,168,178,90`) |
| [](){#BSSID} - | `bssid` | Gib hier eine spezifische BSSID-Adresse ein, um sicherzustellen, dass du dich mit einem bestimmten Zugangspunkt verbindest. Setze es auf alle Nullen, wenn es keine besonderen Umstände gibt. | (`0x00, 0x00, 0x00, 0x00, 0x00, 0x00`) |
| - | `ntp_server` | Gib hier einen NTP-Server an, um die genaue Zeit für BSB-LAN zu erhalten. Setze es auf eine leere Zeichenkette, wenn du NTP nicht verwenden möchtest. Nur für ESP32-basierte Mikrocontroller. | (`pool.ntp.org`) |
| - | `local_timezone` | Zeitzone, die für NTP verwendet werden soll. Siehe [hier](https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv) für eine komplette Liste. | (`CET-1CEST,M3.5.0,M10.5.0/3`) |

### Logging

| Web-Oberfläche | Konfigurationsdatei | Funktionalität | Mögliche Einstellungen |
| ------------- | ------------------- | ------------- | ------------------- |
|**Speichergerät**| `LogDestination` | Wähle das Ziel für Logging-Aktivitäten. Eine SD-Karte wird dringend empfohlen, da die Verwendung des internen Flash-Speichers diesen mit der Zeit abnutzen wird. | **SD-Karte** (`SDCARD`) <br> **Interner Flash-Speicher** (`FLASH`) |
| **Logging-Modus** | `LoggingMode` | Setze die Logging-Ziele/Aktivitäten. Mehrere Auswahlmöglichkeiten sind möglich, für die Konfigurationsdatei müssen die Werte addiert werden, zum Beispiel, um sie an einen MQTT-Broker und an UDP zu senden, setze den Wert auf `4 + 16 = 20` | **Schreibe auf SD-Karte** (`1`) <br> **Berechne 24h-Durchschnitte** (`2`) <br> **Sende an MQTT-Broker** (`4`) <br> **Sende nur Log-Parameter an MQTT** (`8`) <br> **Sende an UDP** (`16`) |
| **Logging-Intervall** | `log_interval` | Intervall für Logging-Aktivitäten (in Sekunden) | **60** (`60`) |
| **Log-Parameter** | `log_parameters` | Liste der Logging-Parameter. Siehe Anweisungen zur Adressierung unten. | **8700, 8743!2, 8314!2** (`{8700, -1}, {8743, 2}, {8314, 2}`) |
| Log-Bus-Telegramme | `logTelegram` | Logge rohe Bus-Telegramme, wie z.B. Broadcast-Nachrichten oder unbekannte Telegramme | **Aus** (`LOGTELEGRAM_OFF`) <br> **Logge alle Bus-Telegramme** (`LOGTELEGRAM_ON`) <br> **Logge nur unbekannte Bus-Telegramme** (`LOGTELEGRAM_UNKNOWN_ONLY`) <br> **Logge nur Broadcast-Bus-Telegramme** (`LOGTELEGRAM_BROADCAST_ONLY`) <br> **Logge nur unbekannte Broadcast-Bus-Telegramme** (`LOGTELEGRAM_UNKNOWN_ONLY + LOGTELEGRAM_BROADCAST_ONLY`) |
|**24h-Durchschnitte-Parameter**| `avg_parameters` | Liste der Parameter für die Generierung von 24-Stunden-Durchschnitten. Siehe Anweisungen zur Adressierung unten. | **8700, 8743!2, 8314!2** (`{8700, -1}, {8743, 2}, {8314, 2}`) |
|-|`replaceDisabled`|Definiert in numerischen Parametern den Wert für einen deaktivierten/inaktiven Zustand. Standard ist `---`, Home Assistant erwartet `None`, andere Systeme evtl. `0`, um reibungslos zu funktionieren.|(`---`)|
| - | `#define DEFAULT_DAYS_TO_PLOT` | Definiere die Standardanzahl der Tage, um Logging-Daten zu plotten | (`3`) |

### MQTT

| Web-Oberfläche | Konfigurationsdatei | Funktionalität | Mögliche Einstellungen |
| ------------- | ------------------- | ------------- | ------------------- |
| **MQTT-Broker-Server** | `mqtt_broker_addr` | Hostname/IP des MQTT-Brokers | **my-mqtt-broker.local** (`my-mqtt-broker.local`) |
| **MQTT-Benutzername** | `MQTTUsername` | Optionaler Benutzername für den MQTT-Broker | **MyMQTTusername** (`MyMQTTusername`) |
| **MQTT-Passwort** | `MQTTPassword` | Optionales Passwort für den MQTT-Broker | **MyMQTTpassword** (`MyMQTTpassword`) |
| MQTT-Geräte-ID | `MQTTDeviceID` | Geräte-Identifikator für MQTT | **BSB-LAN** (`BSB-LAN`) |
| MQTT-Topic-Präfix | `MQTTTopic
|MQTT Modus|`mqtt_mode`|Format für MQTT Telegramme|**Einfach** (`1`) - Sendet Parameternummer und -wert als String<br>**JSON** (`2`) - Sendet Telegramme im JSON Format (nur Parameternummer und -wert)<br>**Rich JSON** (`3`) - Sendet Parameternummer, -name, -wert und -einheit sowie etwaigen Fehler im JSON Format.|
|MQTT Einheiten|`mqtt_unit_set`|Über MQTT übermittelte Parametereinheiten|**Lokalisiert** (`CF_MQTT_UNIT_LOCALIZED`) sendet Einheiten in der konfigurierten Sprache, so wie im BSB-LAN Webinterface angezeigt.<br>**Home Assistant** (`CF_MQTT_UNIT_HOMEASSISTANT`) sendet Einheiten passend für Home Assistant<br>**Keine** (`CF_MQTT_UNIT_NONE`) sendet MQTT Telegramme ohne Einheiten<br>**Hinweis:** Diese Einstellung wirkt sich nur auf MQTT Modus 3 (Rich JSON) und MQTT Auto-Discovery aus. Es hat keine Auswirkung auf das Webinterface, wo de Einheiten immer nur in der landesspezifischen Sprache angezeigt werden.|

### Sensoren und externe Geräte

| Web-Oberfläche | Konfigurationsdatei | Funktionalität | Mögliche Einstellungen |
| --- | --- | --- | --- |
|OneWire Pins|`One_Wire_Pin`|Legt den Pin für OneWire fest (verwende `-1` der Konfigurationsdatei, um es zu deaktivieren)|**10** (`10`)|
| DHT Pins | `DHT_Pins` | Legt die Pins für den DHT22 Sensor fest (verwende `-1` in der Konfigurationsdatei, um es zu deaktivieren) | **11, 12, 13** (`11, 12, 13, -1, -1, -1, -1, -1, -1`) |
| BME280 Sensoren | `BME_Sensors` | Leg die Anzahl der BME280 Sensoren auf dem I2C Bus fest. Du musst Zugang zu den I2C Pins haben. Die festen Adressen `0x76` und `0x77` werden verwendet. Verwende `0` zum Deaktivieren | **1** (`1`) |
| MAX! Verwendung | `enable_max_cul` | Aktiviere oder deaktiviere die Verbindung zum CUNO/CUNX/modifizierten MAX!Cube | **An** (`true`)<br>**Aus** (`false`)||
| IP Adresse Cube | `max_cul_ip_addr` | IP Adresse des CUNO/CUNX/MAX!Cube | **192.168.178.21** (`192,168,178,21`) |
| MAX! Geräte | `max_device_list` | IDs der MAX! Geräte, die abgefragt werden sollen. Diese IDs findest du auf einem Aufkleber auf dem Gerät. Nachdem du sie hier eingegeben hast, muss jedes Gerät in den Pairing-Modus versetzt werden. Dies muss jedes Mal wiederholt werden, wenn das EEPROM Layout von BSB-LAN geändert wird (siehe ChangeLog) | **KEQ0502326, KEQ0505080, KHA0002948** (`"KEQ0502326", "KEQ0505080", "KHA0002948"`) |
| IPWE Verwendung | `enable_ipwe` | Aktiviere die IPWE Erweiterung (`/ipwe.cgi`) | **An** (`true`)<br>**Aus** (`false`) |
| IPWE Parameter | `ipwe_parameters` | Liste der Parameter für die Anzeige in der IPWE Erweiterung. Siehe unten für Anweisungen zur Adressierung | 8700, 8743!2, 8314!2 ({8700, -1}, {8743, 2}, {8314, 2}) |

### Debugging

| Web-Interface | Konfigurationsdatei | Funktionalität | Mögliche Einstellungen |
| --- | --- | --- | --- |
| Debugging Verwendung | `debug_mode` | Wähle die Debug-Ausgabe | **Aus** (`0`)<br>**Seriell** (`1`)<br>**Telnet** (`2`) |
| Ausführlichkeit | `verbose` | Aktiviere oder deaktiviere ausführliche Debug-Nachrichten (schalte es nicht aus, es sei denn, du wirst dazu angeleitet) | **An** (`1`)<br>**Aus** (`0`) |
| Rohdatenmodus | `monitor` | Aktiviere oder deaktiviere den Rohdatenmodus (schalte ihn nicht ein, es sei denn, du wirst dazu angeleitet!) | **An** (`1`)<br>**Aus** (`0`) |
| Unbekannte Parameter anzeigen | `show_unknown` | Versuche auch Parameter anzuzeigen, die vom Zielgerät nicht unterstützt werden | **An** (`true`)<br>**Aus** (`false`) |

---
## Adressierung verschiedener Heizungssteuerungen

Um Parameter von Geräten abzurufen, die nicht das Standard-Zielgerät im Web-Interface sind, musst du ein Ausrufezeichen gefolgt von der Geräteadresse hinzufügen (siehe oben, wie du die Segment-/Gerätenotation in die Geräteadresse umwandelst).
Zum Beispiel würde der Parameter 8700 vom Gerät mit der Adresse 1 als `8700!1` statt einfach `8700` geschrieben werden.

Für die Konfigurationsdatei werden die Parameter in der Form `{Parameternummer, Zieladresse}` aufgelistet. Der Parameter 8700 vom Gerät mit der Adresse 1 würde also als `{8700, 1}` geschrieben werden. Um das Standard-Zielgerät anzusprechen, kannst du `-1` verwenden.
