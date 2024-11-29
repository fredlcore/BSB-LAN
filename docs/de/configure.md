Es gibt zwei Möglichkeiten, BSB-LAN zu konfigurieren:

1. Über die Konfigurationsdatei `BSB_LAN_config.h`
1. Über die Web-Schnittstelle, indem Sie [http://bsb-lan.local/C](http://bsb-lan.local/C) (oder die entsprechende IP-Adresse) aufrufen

Für die initiale Konfiguration müssen einige Einstellungen in der Konfigurationsdatei vorgenommen werden (z. B. Sprache und Netzwerkeinstellungen).
Alle weiteren Änderungen können auch über die Web-Schnittstelle vorgenommen werden. Es kann jedoch sinnvoll sein, die Konfiguration (auch) in der Konfigurationsdatei vorzunehmen, falls der Mikrocontroller ausgetauscht werden muss. Fast alle Einstellungen sind sowohl in der Web-Schnittstelle als auch in der Konfigurationsdatei verfügbar und umgekehrt.

Auf einem ESP32-basierten Mikrocontroller richtet BSB-LAN seinen eigenen WLAN-Zugangspunkt mit dem Namen `BSB-LAN` ein, wenn es keine Verbindung zu einem Netzwerk herstellen kann. So können Sie auch ohne weitere Konfiguration eine Verbindung zu diesem Zugangspunkt mit dem Passwort `BSB-LPB-PPS-LAN` herstellen und BSB-LAN über die IP-Adresse `http://192.168.4.1` erreichen und auf diesem Weg mit der Konfiguration fortfahren. Bitte beachten Sie, dass ein Passwort oder ein HTTP-Benutzername und ein Passwort weiterhin erforderlich sind, wenn diese Details im EEPROM oder in `BSB_LAN_config.h` gespeichert sind.

---
## Konfiguration über `BSB_LAN_config.h`

Die Konfigurationsdatei besteht aus Variablen, die in anderen Teilen von BSB-LAN verwendet werden. Es ist daher wichtig, **nur den Inhalt** der Variablen (d. h. die Einstellungen) zu ändern und **nicht den Typ** der Variablen. Wenn es also beispielsweise die Einstellung
`byte ip_addr[4] = {192,168,178,88};`
gibt, dürfen Sie den Teil `byte ip_addr[4] =` nicht ändern, sondern nur den Inhalt, in diesem Fall die durch Kommas getrennte IP-Adresse.
---
## Konfiguration über die Web-Schnittstelle

Die Konfiguration von BSB-LAN über die Web-Schnittstelle ist ziemlich unkompliziert, da Sie sich nicht mit Variablennamen befassen müssen, sondern mit klaren Beschreibungen.
Zunächst werden in der Weboberfläche nur eine ausgewählte Anzahl von Konfigurationsoptionen angezeigt. Um auf alle Optionen zugreifen zu können, müssen Sie die Option "Erweiterte Konfiguration" auf "Ein" setzen.
---
## Übersicht über die Konfigurationsoptionen
<style>
table th:first-of-type {
    width: 20%;
}
table th:nth-of-type(2) {
    width: 20%;
}
table th:nth-of-type(3) {
    width: 40%;
}
table th:nth-of-type(4) {
    width: 20%;
}
</style>
### Allgemeine Einstellungen
| Web-Schnittstelle | Konfigurationsdatei | Funktionalität | Mögliche Einstellungen |
|-------------|------------------|-------------|-----------------|
| -            | ** `#define LANG` ** | Sprache festlegen | `DE`, `EN`, `FR` und andere ISO-Ländercodes |
| Erweiterte Konfiguration anzeigen | - | Zeigen Sie alle Konfigurationsoptionen an | **Ein** <br>**Aus** |
| Konfiguration aus EEPROM lesen | `UseEEPROM` | Konfiguration aus EEPROM oder Datei lesen | **Ein**  (`1`) <br>**Aus** (`0`) |
| [](){#WriteAccess} Schreibzugriff (Ebene) | - | Wenn `DEFAULT_FLAG` auf `FL_SW_CTL_RONLY` gesetzt ist, können Sie hier die Ebene des Schreibzugriffs festlegen. | **Aus** (schreibgeschützt) <br>**Ein (Standard)** <br>**Ein (Vollständig)** |
| Nach Updates suchen | `enable_version_check` | Abfragen des BSB-LAN-Servers nach neuen verfügbaren Versionen | **Ein** (`true`) |
| OTA-Update | `enable_ota_update` | Over-the-Air (OTA)-Update aktivieren | **Ein** (`true`) |
| Energiesparmodus | `esp32_save_energy` | Verringert die Geschwindigkeit, spart Energie. Nicht aktivieren, wenn WLAN verwendet wird. | **Ein** (`true`) <br>**Aus** (`false`) |
| Webserver-Dateisystem | `webserver` | Ermöglicht das Bereitstellen von Dateien von der SD-Karte | **Ein** (`true`) <br>**Aus** (`false`) |
| - | `#define DEFAULT_FLAG` | Legen Sie Lese-/Schreibzugriff auf das Heizsystem fest. `FL_RONLY` setzt alle Parameter auf schreibgeschützt. `FL_SW_CTL_RONLY` ermöglicht das Festlegen von Lese-/Schreibzugriff über die Einstellung der Web-Schnittstellenkonfiguration. <BR>`0` macht alle Parameter, die geschrieben werden könnten, beschreibbar. **Verwenden Sie diese Option nicht, es sei denn, Sie werden angewiesen!**|**FL_RONLY**<BR>**FL_SW_CTL_RONLY**<BR>**0**|

### Bustyp-Einstellungen
| Web-Schnittstelle | Konfigurationsdatei | Funktionalität | Mögliche Einstellungen |
|-------------|------------------|-------------|-----------------|
| Bustyp | `bus_type` | Bustyp (BSB/LPB/PPS) | **BSB** (`0`) <br>**LPB** (`1`) <br>**PPS** (`2`) |
| PPS: Modus | `pps_write` | BSB-LAN kann als PPS-Raumgerät fungieren (nur wenn kein echtes Raumgerät angeschlossen ist) oder nur passiv zuhören. | **passiv** (`0`) <br>**als Raumgerät** (`1`) |
| PPS: QAA-Modell | `QAA_TYPE` | Raumgerät, das für den PPS-Bus simuliert werden soll | **QAA70** (`0x53`), **QAA50** (`0x52`), **QAA95** (`0x37`), **QAW10** (`0x4D`), **QAW20** (`0x4E`), **MCBA/REA70/DC225** (`0x58`), **QAA10** (`0x5A`), **QAA20** (`0x5B`), **QAA12/13** (`0x5D`), **BMU** (`0x66`), **RVD130** (`0x43`) |
| Eigene Adresse | `own_address` | Eigene Busadresse (Standard `66` sollte nicht geändert werden) | **66** (`66`) |
| Zieladresse | `dest_address` | Zielbusadresse. <br>Für **BSB** immer `0`. <br>Für **LPB** `0`, wenn sich das Zielgerät im Segment 1, Geräteadresse 0, befindet. <BR>Um von der Notation mit LPB-Segment und Geräteadresse zur Zieladresse zu wechseln, multiplizieren Sie das Segment mit 16, addieren Sie die Geräteadresse und ziehen Sie eins ab. Um beispielsweise ein Gerät im Segment 4 mit der Geräteadresse 3 anzusprechen, lautet die Zieladresse `(4 * 16) + 3 - 1 = 66`. <br>Für **PPS** nicht relevant. | **0** (`0`) |
| RX-Pin-Nummer <br>TX-Pin-Nummer | `bus_pins` | Definieren Sie die RX/TX-Pins, um mit dem BSB-LAN-Adapter zu kommunizieren. Bei `0` bleibt die Auto-Detection aktiviert. | **0** und **0** (`0, 0`) |

### Netzwerkeinstellungen
| Web-Schnittstelle | Konfigurationsdatei | Funktionalität | Mögliche Einstellungen |
|-------------|------------------|-------------|-----------------|
| **Netzwerkgerät** | `network_type` | Wählen Sie zwischen WLAN und LAN, um BSB-LAN mit dem Netzwerk zu verbinden. | **LAN** (`0`) <br>**WLAN** (`1`) |
| **WLAN-SSID** | `wifi_ssid` | Legen Sie den WLAN-Netzwerknamen fest, wenn Sie WLAN verwenden. | **Your_WLAN_name** (`Your_WLAN_name`) |
| **WLAN-Passwort** | `wifi_pass` | Legen Sie das WLAN-Passwort fest, wenn Sie WLAN verwenden. | **YourWLANpassword** (`YourWLANpassword`) |
| **DHCP-Verwendung** | `use_dhcp` | Legen Sie fest, ob DHCP verwendet werden soll, um vom Router eine IP-Adresse zu beziehen. | **Ein** (`true`) <br>**Aus** (`false`) |
| IP-Adresse (fest) | `ip_addr` | Wenn Sie *kein* DHCP verwenden, können Sie hier eine feste IP-Adresse festlegen. Andernfalls belassen Sie es bei `0.0.0.0`. In der Web-Schnittstelle können Sie die Punktnotation verwenden. In der Konfigurationsdatei müssen Sie ein Komma als Trennzeichen verwenden. | **192.168.178.88** (`192,168,178,88`) |
| Subnetz | `subnet_addr` | Subnetz bei Verwendung einer festen IP-Adresse. Verwenden Sie dieselbe Notation wie bei der IP-Adresse. | **255.255.255.0** (`255,255,255,0`) |
| Gateway | `gateway_addr` | Gateway-Adresse bei Verwendung einer festen IP-Adresse. Verwenden Sie dieselbe Notation wie bei der IP-Adresse. | **192.168.178.1** (`192,168,178,1`) |
| DNS-Server | `dns_addr` | DNS-Server-Adresse bei Verwendung einer festen IP-Adresse. Verwenden Sie dieselbe Notation wie bei der IP-Adresse. | **192.168.178.1** (`192,168,178,1`) |
| TCP-Port | `HTTPPort` | HTTP-Portnummer, um auf die Web-Schnittstelle zuzugreifen. Standardmäßig `80`. | **80** (`80`) |
| MAC-Adresse | `mac` | Legen Sie eine feste MAC-Adresse fest. Nur relevant für Arduino. | **00:80:41:19:69:90** (`0x00, 0x80, 0x41, 0x19, 0x69, 0x90`) |
| mDNS-Hostname | `mDNS_hostname` | Hostname für mDNS-Ermittlung | **BSB-LAN** (`BSB-LAN`) |
| HTTP-Authentifizierung | `USER_PASS` | Wenn diese Einstellung nicht leer ist, enthält sie den Benutzernamen und das Passwort für die HTTP-Authentifizierung, getrennt durch einen Doppelpunkt. | **Benutzername:Passwort** (`Username:Password`) |
| URL-Passwort | `PASSKEY` | Das Passwort fügt eine benutzerdefinierte Sequenz hinzu, die nach dem Hostnamen in die URL eingefügt werden muss. <BR>Beispielsweise erfordert ein Passwort von `1234`, dass jede URL wie folgt geschrieben wird: `http://bsb-lan.local/1234/` anstelle von `http://bsb-lan.local/`. Lassen Sie es leer, wenn Sie kein Passwort verwenden möchten. | **1234** (`1234`) |
| Vertrauenswürdige IP-Adresse | `trusted_ip_addr` | Der Zugriff auf BSB-LAN ist nur von dieser IP-Adresse aus möglich. Verwenden Sie dieselbe Notation wie bei der IP-Adresse. | **192.168.178.89** (`192,168,178,89`) |
| Vertrauenswürdige IP-Adresse | `trusted_ip_addr2` | Der Zugriff auf BSB-LAN ist nur von dieser IP-Adresse aus möglich. Verwenden Sie dieselbe Notation wie bei der IP-Adresse. | **192.168.178.90** (`192,168,178,90`) |
| [](){#BSSID}- | `bssid` | Geben Sie hier eine bestimmte BSSID-Adresse ein, um sicherzustellen, dass Sie mit einem bestimmten Zugangspunkt verbunden sind. Setzen Sie sie unter normalen Umständen auf alle Nullen. | (`0x00, 0x00, 0x00, 0x00, 0x00, 0x00`) |
| - | `ntp_server` | Legen Sie hier einen NTP-Server fest, um die genaue Zeit für BSB-LAN zu erhalten. Lassen Sie es leer, wenn Sie NTP nicht verwenden möchten. Nur für ESP32-basierte Mikrocontroller. | (`pool.ntp.org`) |
| - | `local_timezone` | Zeitzone für NTP verwenden. Siehe [hier](https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv) für eine komplette Liste. | (`CET-1CEST,M3.5.0,M10.5.0/3`) |

### Protokollierung

| Web-Schnittstelle | Konfigurationsdatei | Funktionalität | Mögliche Einstellungen |
|-------------|------------------|-------------|-----------------|
| Speichergerät | `LogDestination` | Wählen Sie das Ziel für Protokollierungsaktivitäten aus. Die Verwendung einer SD-Karte wird dringend empfohlen, da die Verwendung des internen Flash-Speichers diesen mit der Zeit abnutzen wird. | **SD-Karte** (`SDCARD`) <br>**Interner Flash-Speicher** (`FLASH`) |
| **Protokollierungsmodus** | `LoggingMode` | Legen Sie die Protokollierungsziele/Aktivitäten fest. Mehrere Auswahlmöglichkeiten sind möglich, für die Konfigurationsdatei müssen die Werte addiert werden, beispielsweise um sie an einen MQTT-Broker und an UDP zu senden, setzen Sie den Wert auf `4 + 16 = 20` | **Schreiben auf SD-Karte** (`1`) <br>**Berechnen von 24-Stunden-Durchschnitten** (`2`) <br>**Senden an MQTT-Broker** (`4`) <br>**Nur Protokollparameter an MQTT senden** (`8`) <br>**Senden an UDP** (`16`) |
| **Protokollintervall** | `log_interval` | Intervall für Protokollierungsaktivitäten (in Sekunden) | **60** (`60`) |
| **Protokollparameter** | `log_parameters` | Liste der Protokollparameter. Siehe Adressierungsanweisungen unten. | **8700, 8743!2, 8314!2** (`{8700, -1}, {8743, 2}, {8314, 2}`) |
| Bus-Telegramme protokollieren | `logTelegram` | Protokollieren Sie rohe Bus-Telegramme, wie z. B. Broadcast-Nachrichten oder unbekannte Telegramme | **Aus** (`LOGTELEGRAM_OFF`) <br>**Alle Bus-Telegramme protokollieren** (`LOGTELEGRAM_ON`) <br>**Nur unbekannte Bus-Telegramme protokollieren** (`LOGTELEGRAM_UNKNOWN_ONLY`) <br>**Nur Broadcast-Bus-Telegramme protokollieren** (`LOGTELEGRAM_BROADCAST_ONLY`) <br>**Nur unbekannte Broadcast-Bus-Telegramme protokollieren** (`LOGTELEGRAM_UNKNOWN_ONLY + LOGTELEGRAM_BROADCAST_ONLY`) |
| 24-Stunden-Durchschnitts-Parameter | `avg_parameters` | Liste der Parameter für die Generierung von 24-Stunden-Durchschnitten. Siehe Adressierungsanweisungen unten. | **8700, 8743!2, 8314!2** (`{8700, -1}, {8743, 2}, {8314, 2}`) |
| - | `#define DEFAULT_DAYS_TO_PLOT` | Definieren Sie die Standardanzahl der Tage, für die Protokolldaten geplottet werden sollen | (`3`) |

### MQTT

| Web-Schnittstelle | Konfigurationsdatei | Funktionalität | Mögliche Einstellungen |
|-------------|------------------|-------------|-----------------|
| **MQTT-Broker-Server** | `mqtt_broker_addr` | Hostname/IP des MQTT-Brokers | **my-mqtt-broker.local** (`my-mqtt-broker.local`) |
| MQTT-Benutzername | `MQTTUsername` | Optionaler Benutzername für den MQTT-Broker | **MyMQTTusername** (`MyMQTTusername`) |
| MQTT-Passwort | `MQTTPassword` | Optionales Passwort für den MQTT-Broker | **My
| DHT Pins | `DHT_Pins` | Legen Sie die DHT22-Sensorklemmen fest (verwenden Sie `-1` in der Konfigurationsdatei, um sie zu deaktivieren) | **11, 12, 13** (`11, 12, 13, -1, -1, -1, -1, -1, -1`) |
| --- | --- | --- | --- |
| BME280-Sensoren | `BME_Sensors` | Legen Sie die Anzahl der BME280-Sensoren auf dem I2C-Bus fest. Sie benötigen Zugriff auf I2C-Pins. Es werden die festen Adressen `0x76` und `0x77` verwendet. Verwenden Sie `0`, um die Funktion zu deaktivieren | **1** (`1`) |
| MAX! Verwendung | `enable_max_cul` | Aktivieren oder deaktivieren Sie die Verbindung zu CUNO/CUNX/modifiziertem MAX!Cube | **Ein** (`true`) **Aus** (`false`) |
| IP-Adresse Cube | `max_cul_ip_addr` | IP-Adresse des CUNO/CUNX/MAX!Cube | **192.168.178.21** (`192,168,178,21`) |
| MAX! Geräte | `max_device_list` | IDs der MAX! Geräte, die abgefragt werden sollen. Diese IDs finden Sie auf einem Aufkleber auf dem Gerät. Nachdem Sie sie hier eingegeben haben, muss jedes Gerät in den Pairing-Modus versetzt werden. Dies muss jedes Mal wiederholt werden, wenn das EEPROM-Layout von BSB-LAN geändert wird (siehe ChangeLog) | **KEQ0502326, KEQ0505080, KHA0002948** (`"KEQ0502326", "KEQ0505080", "KHA0002948"`) |
| IPWE-Verwendung | `enable_ipwe` | Aktivieren Sie die IPWE-Erweiterung (`/ipwe.cgi`) | **Ein** (`true`) **Aus** (`false`) |
| IPWE-Parameter | `ipwe_parameters` | Liste der Parameter für die Anzeige in der IPWE-Erweiterung. Siehe untenstehende Anweisungen zur Adressierung | 8700, 8743!2, 8314!2 ({8700, -1}, {8743, 2}, {8314, 2}) |
| - | `#define CUSTOM_COMMANDS` | Aktivieren Sie benutzerdefinierte Funktionen | - |

### Debugging

| Web-Interface | Konfigurationsdatei | Funktionalität | Mögliche Einstellungen |
| --- | --- | --- | --- |
| Debugging-Verwendung | `debug_mode` | Wählen Sie die Debug-Ausgabe | **Aus** (`0`) **Seriell** (`1`) **Telnet** (`2`) |
| Verbosity-Modus | `verbose` | Aktivieren oder deaktivieren Sie ausführliche Debug-Nachrichten (schalten Sie diese Option nicht aus, es sei denn, Sie werden dazu angeleitet) | **Ein** (`1`) **Aus** (`0`) |
| Rohdatenmodus | `monitor` | Aktivieren oder deaktivieren Sie den Rohdatenmodus (schalten Sie diese Option nicht ein, es sei denn, Sie werden dazu angeleitet) | **Ein** (`1`) **Aus** (`0`) |
| Anzeige unbekannter Parameter | `show_unknown` | Versuchen Sie auch, Parameter anzuzeigen, die vom Zielgerät nicht unterstützt werden | **Ein** (`true`) **Aus** (`false`) |

---

## Adressierung verschiedener Heizungssteuerungen

Um im Web-Interface Parameter von Geräten abzurufen, die nicht dem Standard-Zielgerät entsprechen, müssen Sie ein Ausrufezeichen gefolgt von der Geräteadresse hinzufügen (siehe oben, wie Sie die Segment-/Gerätenotation in eine Geräteadresse umwandeln).

Beispiel: Der Parameter 8700 von Geräteadresse 1 würde als `8700!1` anstelle von nur `8700` geschrieben.

In der Konfigurationsdatei werden Parameter in der Form `{Parameternummer, Zieladresse}` aufgelistet. Der Parameter 8700 von Geräteadresse 1 würde also als `{8700, 1}` geschrieben. Um das Standardziel anzusprechen, können Sie `-1` verwenden.
