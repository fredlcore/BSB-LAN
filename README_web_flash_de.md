# BSB-LAN Web Flash Anleitung

Anleitung zum Flashen der BSB-LAN Firmware über den Browser mit [esptool-js](https://espressif.github.io/esptool-js/) – kein Python, keine Arduino IDE erforderlich.

---

## Voraussetzungen

- **Browser:** Google Chrome oder Microsoft Edge (WebSerial wird von Firefox nicht unterstützt)
- **Kabel:** USB-Kabel zwischen PC und ESP32
- **Firmware:** Artifact-ZIP aus der GitHub Actions Pipeline (siehe unten)

---

## Schritt 1 – Firmware herunterladen

1. Auf GitHub zum Repository navigieren
2. Auf **Actions** klicken → neuesten erfolgreichen Build öffnen
3. Unter **Artifacts** das passende ZIP für dein Board herunterladen:

| Artifact | Board |
|---|---|
| `BSB-LAN-firmware-esp32-nodemcu` | Joy-It ESP32 NodeMCU |
| `BSB-LAN-firmware-esp32-olimex-evb` | Olimex ESP32-EVB |
| `BSB-LAN-firmware-esp32-olimex-poe-iso` | Olimex ESP32-POE-ISO |

4. ZIP entpacken – der Ordner enthält folgende Dateien:

```
BSB_LAN.ino.bootloader.bin
BSB_LAN.ino.partitions.bin
boot_app0.bin
BSB_LAN.ino.bin
flash_manifest.json
```

---

## Schritt 2 – ESP32 verbinden

1. ESP32 per USB mit dem PC verbinden
2. Sicherstellen dass kein anderes Programm (Arduino IDE, ESPHome, etc.) den Port belegt

---

## Schritt 3 – esptool-js öffnen

👉 **https://espressif.github.io/esptool-js/**

1. Auf **Connect** klicken
2. Im Browser-Dialog den richtigen COM-Port auswählen (`COM3`, `/dev/ttyUSB0`, `/dev/cu.usbserial-*` o.ä.)
3. Baudrate auf **921600** lassen

---

## Schritt 4 – Dateien und Adressen eintragen

Im Bereich **Flash Address** müssen alle 4 Dateien mit den korrekten Adressen eingetragen werden.

Auf **Add File** klicken und nacheinander eintragen:

| Flash-Adresse | Datei |
|---|---|
| `0x1000` | `BSB_LAN.ino.bootloader.bin` |
| `0x8000` | `BSB_LAN.ino.partitions.bin` |
| `0xe000` | `boot_app0.bin` |
| `0x10000` | `BSB_LAN.ino.bin` |

> Die Adressen sind auch in der mitgelieferten `flash_manifest.json` dokumentiert.

---

## Schritt 5 – Flashen

1. Auf **Program** klicken
2. Den Fortschrittsbalken abwarten – der Vorgang dauert ca. 30–60 Sekunden
3. Nach erfolgreichem Flash erscheint die Meldung `Leaving... Hard resetting via RTS pin...` – das ist **kein Fehler**, sondern bedeutet dass der ESP32 neu startet

---

## Nach dem Flash

BSB-LAN ist jetzt geflasht und startet automatisch. Beim ersten Start:

1. BSB-LAN versucht sich mit dem in `BSB_LAN_config.h` konfigurierten Netzwerk zu verbinden
2. IP-Adresse im Router nachschlagen oder per Serial Monitor (115200 Baud) ablesen
3. Im Browser aufrufen:
   ```
   http://<IP-Adresse>/
   ```
   oder per mDNS (falls aktiviert):
   ```
   http://bsb-lan.local/
   ```

---

## Häufige Probleme

| Problem | Lösung |
|---|---|
| Port wird nicht angezeigt | USB-Treiber installieren: [CP210x](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) oder [CH340](https://www.wch-ic.com/downloads/CH341SER_ZIP.html) |
| Verbindung schlägt fehl | Boot-Taste am ESP32 gedrückt halten während auf **Connect** geklickt wird |
| Flash schlägt fehl | Anderen USB-Port probieren, Baudrate auf `460800` reduzieren |
| Browser unterstützt WebSerial nicht | Chrome oder Edge verwenden (kein Firefox) |
| `0x1000` Fehler bei Olimex POE | Adresse `0x1000` durch `0x0` ersetzen (abhängig von Bootloader-Version) |

---

## OTA-Updates (nach dem Erstflash)

Für zukünftige Updates muss nicht erneut über USB geflasht werden. Wenn OTA in den BSB-LAN Einstellungen aktiviert ist, reicht es die neue `BSB_LAN.ino.bin` hochzuladen:

```
http://bsb-lan.local:8080
```

Nur die `BSB_LAN.ino.bin` wird benötigt – Bootloader und Partitionstabelle bleiben unverändert.
