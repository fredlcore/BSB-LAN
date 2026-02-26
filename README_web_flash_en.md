# BSB-LAN Web Flash Guide

How to flash the BSB-LAN firmware directly in your browser using [esptool-js](https://espressif.github.io/esptool-js/) – no Python, no Arduino IDE required.

---

## Prerequisites

- **Browser:** Google Chrome or Microsoft Edge (WebSerial is not supported by Firefox)
- **Cable:** USB cable between PC and ESP32
- **Firmware:** Artifact ZIP from the GitHub Actions pipeline (see below)

---

## Step 1 – Download the firmware

1. Navigate to the repository on GitHub
2. Click **Actions** → open the latest successful build
3. Under **Artifacts** download the correct ZIP for your board:

| Artifact | Board |
|---|---|
| `BSB-LAN-firmware-esp32-nodemcu` | Joy-It ESP32 NodeMCU |
| `BSB-LAN-firmware-esp32-olimex-evb` | Olimex ESP32-EVB |
| `BSB-LAN-firmware-esp32-olimex-poe-iso` | Olimex ESP32-POE-ISO |

4. Extract the ZIP – the folder contains the following files:

```
BSB_LAN.ino.bootloader.bin
BSB_LAN.ino.partitions.bin
boot_app0.bin
BSB_LAN.ino.bin
flash_manifest.json
```

---

## Step 2 – Connect the ESP32

1. Connect the ESP32 to your PC via USB
2. Make sure no other program (Arduino IDE, ESPHome, etc.) is occupying the port

---

## Step 3 – Open esptool-js

👉 **https://espressif.github.io/esptool-js/**

1. Click **Connect**
2. Select the correct COM port in the browser dialog (`COM3`, `/dev/ttyUSB0`, `/dev/cu.usbserial-*`, etc.)
3. Leave the baud rate at **921600**

---

## Step 4 – Enter files and addresses

In the **Flash Address** section all 4 files must be added with their correct addresses.

Click **Add File** and enter them one by one:

| Flash Address | File |
|---|---|
| `0x1000` | `BSB_LAN.ino.bootloader.bin` |
| `0x8000` | `BSB_LAN.ino.partitions.bin` |
| `0xe000` | `boot_app0.bin` |
| `0x10000` | `BSB_LAN.ino.bin` |

> The addresses are also documented in the included `flash_manifest.json`.

---

## Step 5 – Flash

1. Click **Program**
2. Wait for the progress bar to complete – the process takes approximately 30–60 seconds
3. After a successful flash the message `Leaving... Hard resetting via RTS pin...` will appear – this is **not an error**, it means the ESP32 is restarting

---

## After flashing

BSB-LAN is now flashed and will start automatically. On first boot:

1. BSB-LAN will attempt to connect to the network configured in `BSB_LAN_config.h`
2. Look up the IP address in your router or read it via Serial Monitor (115200 baud)
3. Open in your browser:
   ```
   http://<IP-address>/
   ```
   or via mDNS (if enabled):
   ```
   http://bsb-lan.local/
   ```

---

## Troubleshooting

| Problem | Solution |
|---|---|
| Port not shown | Install USB driver: [CP210x](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) or [CH340](https://www.wch-ic.com/downloads/CH341SER_ZIP.html) |
| Connection fails | Hold the Boot button on the ESP32 while clicking **Connect** |
| Flash fails | Try a different USB port, reduce baud rate to `460800` |
| Browser does not support WebSerial | Use Chrome or Edge (not Firefox) |
| `0x1000` error on Olimex POE | Replace address `0x1000` with `0x0` (depends on bootloader version) |

---

## OTA Updates (after initial flash)

For future updates you do not need to flash via USB again. If OTA is enabled in the BSB-LAN settings, simply upload the new `BSB_LAN.ino.bin`:

```
http://bsb-lan.local:8080
```

Only `BSB_LAN.ino.bin` is needed – the bootloader and partition table remain unchanged.
