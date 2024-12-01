# Fehlerbehebung

BSB-LAN versucht, den Zugriff auf dein Heizsystem so einfach wie möglich zu gestalten, aber es kann immer etwas schiefgehen. Wenn du nach dem Lesen dieses Dokuments und der [FAQ](faq.md) immer noch ein Problem hast, öffne bitte [einen Bug-Report](https://github.com/fredlcore/BSB-LAN/issues/new?assignees=&labels=&projects=&template=bug_report.md&title=%5BBUG%5D) auf der GitHub-Seite des Projekts und stelle sicher, dass du uns alle notwendigen Log-Dateien und weitere erforderliche Details, insbesondere vom Serial Monitor (oder kurz *SerMo*), zur Verfügung stellst.

Bevor du das tust, stelle jedoch sicher, dass du die neueste Version von BSB-LAN aus dem Master-Repository (nicht die Release-Version) installierst, auch wenn deine Version nur ein paar Tage alt ist. Trotzdem könnte seitdem eine Menge passiert sein :)!

### Verwendung des Serial Monitors
- Öffne den Serial Monitor, indem du in der Arduino IDE zu ***Tools/Serial Monitor*** gehst.
- Setze die Übertragungsgeschwindigkeit auf 115200 in der rechten oberen Ecke des Serial Monitor-Fensters.
- Stelle sicher, dass du die Nachrichten direkt ab dem Moment kopierst, in dem dein Mikrocontroller bootet (angezeigt durch die Nachricht `READY`), bis zu dem Moment, in dem das Problem auftritt.
- Sende bitte keine Screenshots, sondern nur Textdateien.

Der Serial Monitor in der Arduino IDE hat derzeit einen Bug, der es dir nur ermöglicht, die Teile der Serial Monitor-Nachrichten zu kopieren, die auf dem Bildschirm sichtbar sind. Auch wenn das bedeutet, dass das Kopieren größerer Teile der Log-Nachrichten mühsam ist, musst du trotzdem den kompletten Log bereitstellen, um Unterstützung zu erhalten. Es hilft ein wenig, die Größe des Serial Monitor-Fensters zu vergrößern.

---
## Kompilierung fehlgeschlagen: "Sketch zu groß"
- [Wähle das Partitionsschema *Minimal SPIFFS*][SPIFFS] in der Arduino IDE unter ***Tools/Partition Scheme***.
**Achtung:** Diese Einstellung wird auf den Standardwert zurückgesetzt, wenn das ESP32-Framework aktualisiert wird!
Wenn du Over-the-Air-Updates verwendest, musst du die Software einmal per USB flashen, nachdem du das Partitionsschema geändert hast, bevor OTA-Updates wieder funktionieren.

---
## Kein Zugriff mehr auf die Web-Oberfläche
Wenn du die Einstellungen so geändert hast, dass du nicht mehr auf die Web-Oberfläche zugreifen kannst, gibt es zwei Möglichkeiten, das System wiederherzustellen:

- **Wenn du das Gerät flashen kannst:**
    1. Konfiguriere `BSB_LAN_config.h` mit korrekten, funktionierenden Einstellungen.
    2. Setze `UseEEPROM` auf `0`.
    3. Spiele BSB-LAN auf den Mikrocontroller auf.
    4. Du kannst jetzt auf BSB-LAN zugreifen. Gehe zu "Einstellungen" und speichere die Einstellungen. Dadurch werden die funktionierenden Einstellungen im EEPROM gespeichert.
    5. Bearbeite `BSB_LAN_config.h` *erneut*(!) und setze `UseEEPROM` auf `1` und spiele BSB-LAN erneut auf den Mikrocontroller auf.
    6. Erst jetzt wird BSB-LAN die Einstellungen aus dem EEPROM lesen und verwenden, so dass du weitere Änderungen über die Web-Oberfläche vornehmen kannst.
- **Wenn du das Gerät nicht flashen kannst:**
    1. Wenn du das Gerät vor Ort nicht flashen kannst, kannst du BSB-LAN auf die letzten `BSB_LAN_config.h`-Einstellungen zurücksetzen, indem du zwei Pins *vor und während des Bootens des Mikrocontrollers* verbindest:
        - ESP32-Olimex: Verbinde die Pins 34 und 3V3.
        - ESP32-NodeMCU: Verbinde die Pins 21 und 3V3.
        - Arduino Due: Verbinde die Pins 31 und 33.
    2. Wenn die Pins erfolgreich verbunden wurden, blinkt die integrierte LED des Mikrocontrollers vier Sekunden lang langsam.
    3. Öffne anschließend die Konfiguration in der Web-Oberfläche, überprüfe alle Einstellungen in der Konfiguration und speichere sie. Dadurch werden die funktionierenden Einstellungen im EEPROM gespeichert.
- **Temporärer Zugangspunkt auf einem ESP32-basierten Mikrocontroller**
    - Auf einem ESP32-basierten Mikrocontroller richtet BSB-LAN seinen eigenen WLAN-Zugangspunkt mit dem Namen `BSB-LAN` ein, wenn er keine Verbindung zu einem Netzwerk herstellen kann. In diesem Fall kannst du dich mit diesem Zugangspunkt mit dem Passwort `BSB-LPB-PPS-LAN` verbinden und BSB-LAN über die IP-Adresse `http://192.168.4.1` erreichen und versuchen, die Konfiguration auf diese Weise zu korrigieren. Bitte beachte, dass du weiterhin einen Passkey oder HTTP-Benutzernamen und Passwort benötigst, wenn diese Details im EEPROM oder in `BSB_LAN_config.h` gespeichert sind.

---
## Ich kann nur auf sehr wenige Parameter über BSB/LPB zugreifen!
- BSB-LAN kommt zunächst nur mit einer kleinen Menge an Parametern, die auf (fast) jedem Heizsystem funktionieren. Du musst eine [gerätespezifische Parameterliste erstellen](install.md#generating-the-device-specific-parameter-list).

---
## Kategorienliste plötzlich sehr klein
- BSB-LAN muss den Controller des Heizsystems erkennen, um die anzuzeigenden Kategorien zu bestimmen. Wenn BSB-LAN nicht mit dem Controller verbunden ist oder die Erkennung fehlschlägt, werden nur wenige universelle Kategorien angezeigt.

---
## Kann keine Parameter lesen / Gerätefamilie ist `0`
- Falscher Bustyp (BSB statt LPB oder umgekehrt).
- Wenn die rote LED des Adapters nicht leuchtet (und idealerweise leicht flackert), gibt es ein Problem mit der Verkabelung zwischen dem Adapter und dem Heizsystem. Die rote LED leuchtet, sobald der Adapter korrekt angeschlossen ist, auch wenn der BSB-LAN-Adapter noch nicht mit dem Mikrocontroller verbunden ist!

---
## Keine Daten, obwohl die rote LED des Adapters leuchtet
- Stelle sicher, dass der Adapter mit CL+/CL- und nicht mit dem dritten Pin (G+) verbunden ist: G+ versorgt die LED mit Strom, ist aber keine Datenleitung.
- [Stelle sicher, dass du den Mikrocontroller eingeschaltet hast][PowerSupply]. Du könntest denken, dass das Heizsystem den Mikrocontroller mit Strom versorgt, weil die LED am BSB-LAN-Adapter leuchtet, aber das tut es nicht. Du musst ihn separat mit Strom versorgen.
- Bei Verwendung des Adapters für die Olimex-Mikrocontroller: Stelle sicher, dass die BSB-LAN-Adapterplatine genau in der Mitte des UEXT-Anschlusses sitzt. Sie passt auch, wenn sie um eine Pin-Reihe nach links oder rechts verschoben ist, aber sie wird nicht funktionieren.
- Stelle sicher, dass die RX/TX-Pins korrekt gesetzt/erkannt werden. Die Startsequenz im Serial Monitor zeigt dir, welche Pins verwendet oder automatisch erkannt wurden.

---
## Keine oder unzuverlässige Netzwerkverbindung
- Versuche, den Mikrocontroller über USB von einem Laptop aus mit Strom zu versorgen. Wir hatten viele Fälle, in denen die Netzteile trotz ausreichender Leistung unzuverlässig waren.
- Schaue dir den Log im Serial Monitor an, um zu überprüfen, ob der Mikrocontroller eine IP-Adresse erhalten hat. Wenn nicht, sind deine Netzwerk-Einstellungen oder die physische Verbindung möglicherweise fehlerhaft.

---
## Keine Verbindung zu verstecktem WLAN-Netzwerk möglich
- Ja, das ist eine bekannte Einschränkung. Die einzige Möglichkeit, das zu tun, ist, [die BSSID explizit in][BSSID] `BSB_LAN_config.h` zu setzen.

---
## Raumtemperatur (oder ein anderer Parameter) kann nicht eingestellt werden
- Überprüfe die Einstellungen von BSB-LAN und stelle sicher, dass [der Schreibzugriff aktiviert ist][WriteAccess] und auf *standard* oder *komplett* gesetzt ist.

---
## Web-Oberfläche hängt sich beim Herstellen einer neuen Verbindung auf
- BSB-LAN ist kein Multitasking-System. Das bedeutet, dass es sich um eine Aufgabe gleichzeitig kümmern kann. Also auch wenn ein URL-Befehl abgebrochen wird (indem das Browser-Fenster geschlossen wird), könnte BSB-LAN das nicht erkennen und erst neue Anfragen bearbeiten, wenn die vorherige Aufgabe abgeschlossen ist.

---
## Der Serial Monitor zeigt keine lesbaren Daten an
- Stelle sicher, dass die Geschwindigkeit korrekt auf 115200 bps gesetzt ist.
- Stelle sicher, dass der richtige Port ausgewählt ist.