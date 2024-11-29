# Fehlerbehebung

BSB-LAN versucht, den Zugriff auf Ihre Heizung so einfach wie möglich zu gestalten, aber es kann immer etwas schiefgehen. Wenn Sie nach dem Lesen dieses Dokuments und der [FAQ](faq.md) immer noch ein Problem haben, öffnen Sie bitte [einen Fehlerbericht](https://github.com/fredlcore/BSB-LAN/issues/new?assignees=&labels=&projects=&template=bug_report.md&title=%5BBUG%5D) auf der GitHub-Seite des Projekts und stellen Sie sicher, dass Sie uns alle erforderlichen Protokolldateien und weitere erforderliche Details, insbesondere vom Serial Monitor (oder kurz *SerMo*), zur Verfügung stellen.

Bevor Sie dies jedoch tun, stellen Sie sicher, dass Sie die neueste Version von BSB-LAN aus dem Master-Repository (nicht die Release-Version) installieren, auch wenn Ihre Version nur wenige Tage alt ist. Trotzdem könnte seitdem viel passiert sein :)!

### Verwendung des Serial Monitors

- Greifen Sie auf den Serial Monitor zu, indem Sie in der Arduino IDE zu ***Tools/Serial Monitor*** gehen.
- Legen Sie die Übertragungsgeschwindigkeit in der oberen rechten Ecke des Fensters des Serial Monitors auf 115200 fest.
- Stellen Sie sicher, dass Sie die Nachrichten direkt ab dem Moment kopieren, in dem Ihr Mikrocontroller bootet (angezeigt durch die Nachricht `READY`), bis zum Moment, in dem das Problem auftritt.
- Senden Sie bitte keine Screenshots, sondern nur Textdateien.

Der Serial Monitor in der Arduino IDE weist derzeit einen Fehler auf, der es Ihnen nur ermöglicht, die Teile der Serial Monitor-Nachrichten zu kopieren, die auf dem Bildschirm sichtbar sind. Auch wenn dies bedeutet, dass das Kopieren größerer Teile von Protokollnachrichten mühsam ist, müssen Sie trotzdem das vollständige Protokoll bereitstellen, um Unterstützung zu erhalten. Das Vergrößern des Fensters des Serial Monitors hilft ein wenig.

---

## Kompilieren fehlgeschlagen: "Sketch zu groß"

- Wählen Sie in der Arduino IDE unter ***Tools/Partition Scheme*** das [Partitionsschema *Minimal SPIFFS*][SPIFFS] aus.
**Achtung:** Diese Einstellung wird beim Aktualisieren des ESP32-Frameworks auf den Standardwert zurückgesetzt!
Wenn Sie Over-the-Air-Updates verwenden, müssen Sie das Softwareprogramm einmal über USB flashen, nachdem Sie das Partitionsschema geändert haben, bevor Over-the-Air-Updates wieder funktionieren.

---

## Kein Zugriff mehr auf die Web-Oberfläche

Wenn Sie die Einstellungen so geändert haben, dass Sie nicht mehr auf die Web-Oberfläche zugreifen können, gibt es zwei Möglichkeiten, das System wiederherzustellen:

- **Wenn Sie das Gerät flashen können:**
    1. Konfigurieren Sie `BSB_LAN_config.h` mit korrekten, funktionierenden Einstellungen.
    2. Setzen Sie `UseEEPROM` auf `0`.
    3. Flashen Sie BSB-LAN auf den Mikrocontroller.
    4. Sie können jetzt auf BSB-LAN zugreifen. Gehen Sie zu "Einstellungen" und speichern Sie die Einstellungen. Dadurch werden die funktionierenden Einstellungen im EEPROM gespeichert.
    5. Bearbeiten Sie nun `BSB_LAN_config.h` *erneut*(!) und setzen Sie `UseEEPROM` auf `1` und flashen Sie BSB-LAN erneut auf den Mikrocontroller.
    6. Erst jetzt wird BSB-LAN die Einstellungen aus dem EEPROM lesen und verwenden, sodass Sie weitere Änderungen an der Web-Oberfläche vornehmen können.
- **Wenn Sie das Gerät nicht flashen können:**
    1. Wenn Sie das Gerät vor Ort nicht flashen können, können Sie BSB-LAN auf die letzte `BSB_LAN_config.h`-Einstellung zurücksetzen, indem Sie vor und während des Bootens des Mikrocontrollers zwei Pins verbinden:
        - ESP32-Olimex: Verbinden Sie die Pins 34 und 3V3.
        - ESP32-NodeMCU: Verbinden Sie die Pins 21 und 3V3.
        - Arduino Due: Verbinden Sie die Pins 31 und 33.
    2. Wenn die Pins erfolgreich verbunden wurden, blinkt die integrierte LED des Mikrocontrollers vier Sekunden lang langsam.
    3. Öffnen Sie anschließend die Konfiguration in der Web-Oberfläche, überprüfen Sie alle Einstellungen in der Konfiguration und speichern Sie sie. Dadurch werden die funktionierenden Einstellungen im EEPROM gespeichert.
- **Temporärer Zugangspunkt auf einem ESP32-basierten Mikrocontroller**
    - Auf einem ESP32-basierten Mikrocontroller richtet BSB-LAN seinen eigenen drahtlosen Zugangspunkt namens `BSB-LAN` ein, wenn er keine Verbindung zu einem Netzwerk herstellen kann. In diesem Fall können Sie eine Verbindung zu diesem Zugangspunkt mit dem Passwort `BSB-LPB-PPS-LAN` herstellen und auf BSB-LAN über die IP-Adresse `http://192.168.4.1` zugreifen und sehen, ob Sie die Konfiguration auf diese Weise beheben können. Bitte beachten Sie, dass Sie, wenn Sie einen Passcode oder einen HTTP-Benutzernamen und ein Passwort festgelegt haben, diese weiterhin benötigen, wenn diese Details im EEPROM oder in `BSB_LAN_config.h` gespeichert sind.

---

## Ich kann über BSB/LPB nur auf sehr wenige Parameter zugreifen!

- BSB-LAN verfügt zunächst nur über eine kleine Gruppe von Parametern, die auf (fast) jedem Heizungssystem funktionieren. Sie benötigen eine [gerätespezifische Parameterliste](install.md#generating-the-device-specific-parameter-list).

---

## Kategorieliste plötzlich so klein

- BSB-LAN muss den Controller des Heizungssystems erkennen, um die anzuzeigenden Kategorien zu bestimmen. Wenn BSB-LAN nicht mit dem Controller verbunden ist oder die Erkennung anderweitig fehlschlägt, werden nur wenige universelle Kategorien angezeigt.

---

## Kann keine Parameter lesen / Gerätefamilie ist `0`

- Falscher Bustyp (BSB statt LPB oder umgekehrt).
- Wenn die rote LED des Adapters nicht leuchtet (und idealerweise leicht flackert), besteht ein Problem mit der Verkabelung zwischen dem Adapter und dem Heizungssystem. Die rote LED leuchtet, sobald der Adapter korrekt angeschlossen ist, selbst wenn der BSB-LAN-Adapter nicht mit dem Mikrocontroller verbunden ist!

---

## Keine Daten, obwohl die rote LED des Adapters leuchtet

- Stellen Sie sicher, dass der Adapter mit CL+/CL- und nicht mit dem dritten Pin (G+) verbunden ist: G+ treibt die LED an, ist aber keine Datenleitung.
- Stellen Sie sicher, dass Sie den Mikrocontroller [eingeschaltet haben][PowerSupply]. Sie könnten denken, dass das Heizungssystem den Mikrocontroller mit Strom versorgt, weil die LED am BSB-LAN-Adapter leuchtet, aber das tut es nicht. Sie müssen es separat mit Strom versorgen.
- Bei Verwendung des Adapters für die Olimex-Mikrocontroller: Stellen Sie sicher, dass die BSB-LAN-Adapterplatine **genau** in der Mitte des UEXT-Anschlusses sitzt. Sie passt auch dann noch hinein, wenn sie um eine Pin-Position nach links oder rechts verschoben ist, aber sie funktioniert nicht.
- Stellen Sie sicher, dass die RX/TX-Pins korrekt gesetzt/erkannt werden. Die Startsequenz im Serial Monitor zeigt Ihnen, welche Pins verwendet werden oder automatisch erkannt wurden.

---

## Keine oder unzuverlässige Netzwerkverbindung

- Versuchen Sie, den Mikrocontroller über USB von einem Laptop aus mit Strom zu versorgen. Wir hatten viele Fälle, in denen die Netzteile trotz ausreichender Nennleistung unzuverlässig waren.
- Sehen Sie sich das Protokoll des Serial Monitors an, um zu überprüfen, ob der Mikrocontroller eine IP-Adresse erhalten konnte. Wenn nicht, sind Ihre Netzwerkeinstellungen oder die physische Verbindung möglicherweise fehlerhaft.

---

## Keine Verbindung zu einem versteckten WLAN-Netzwerk möglich

- Ja, das ist eine bekannte Einschränkung. Die einzige Möglichkeit, dies zu tun, besteht darin, die [BSSID in `BSB_LAN_config.h` explizit festzulegen][BSSID].

---

## Raumtemperatur (oder ein anderer Parameter) kann nicht eingestellt werden

- Überprüfen Sie die Einstellungen von BSB-LAN und stellen Sie sicher, dass der [Schreibzugriff aktiviert ist][WriteAccess] und auf *standard* oder *komplett* gesetzt ist.

---

## Web-Oberfläche hängt sich beim Herstellen einer neuen Verbindung auf

- BSB-LAN ist kein Multitasking-System. Das bedeutet, dass es sich um eine Aufgabe gleichzeitig kümmern kann. Also auch wenn ein URL-Befehl abgebrochen wird (indem das Browserfenster geschlossen wird), erkennt BSB-LAN dies möglicherweise nicht und beginnt erst dann, neue Anfragen zu bearbeiten, wenn die vorherige abgeschlossen ist.

---

## Der Serial Monitor zeigt keine lesbaren Daten an

- Stellen Sie sicher, dass die Geschwindigkeit korrekt auf 115200 bps eingestellt ist.
- Stellen Sie sicher, dass der richtige Port ausgewählt ist.