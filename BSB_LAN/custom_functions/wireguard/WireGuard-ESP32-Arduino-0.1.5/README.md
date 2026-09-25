# WireGuard-ESP32 (Patched for ESP-IDF v5.4 + PSK Support)

Fork of [ciniml/WireGuard-ESP32-Arduino](https://github.com/ciniml/WireGuard-ESP32-Arduino) v0.1.5 with patches for modern ESP32 Arduino cores (M5Stack ESP32 core 3.2.5 / ESP-IDF v5.4).

## Changes from upstream

### ESP-IDF v5.4 compatibility
- **`wireguardif.c`**: Replaced deprecated `tcpip_adapter.h` with `esp_netif.h` and `esp_netif_net_stack.h`. Replaced `tcpip_adapter_get_netif()` with `esp_netif_get_handle_from_ifkey()` / `esp_netif_get_netif_impl()`.
- **`wireguard.h`**: Added missing `handshake_destroy()` function declaration (was defined in `wireguard.c` but never declared in the header, causing implicit declaration errors with stricter compilers).

### Preshared key and keepalive support
- **`WireGuard-ESP32.h` / `WireGuard.cpp`**: Added new `begin()` overload that accepts a base64-encoded preshared key and keepalive interval:

```cpp
bool begin(
    const IPAddress& localIP,
    const char* privateKey,
    const char* remotePeerAddress,
    const char* remotePeerPublicKey,
    uint16_t remotePeerPort,
    const char* presharedKey,    // base64-encoded PSK (or NULL)
    uint16_t keepAlive = 0       // keepalive interval in seconds (0 = disabled)
);
```

The original `begin()` without PSK/keepalive still works (calls the new overload with `NULL` / `0`).

## Usage

### Basic (no PSK)

```cpp
#include <WireGuard-ESP32.h>

static WireGuard wg;

// After WiFi connect + NTP sync:
wg.begin(local_ip, private_key, endpoint_address, public_key, endpoint_port);
```

### With preshared key and keepalive

```cpp
wg.begin(
    IPAddress(10, 8, 0, 18),
    "your_private_key_base64",
    "endpoint.example.com",
    "peer_public_key_base64",
    51820,
    "preshared_key_base64",  // PSK from WireGuard config
    10                        // keepalive every 10 seconds
);
```

### Split tunnel (recommended for IoT)

By default, `wg.begin()` sets the WireGuard interface as the default route, which breaks outbound internet traffic if the VPN server doesn't forward it. To keep WiFi as the default outbound route (split tunnel):

```cpp
#include "lwip/netif.h"

struct netif *wifi_default = netif_default;  // save before wg.begin()
wg.begin(...);
netif_set_default(wifi_default);             // restore WiFi as default
```

This way outbound internet traffic uses WiFi directly, while inbound VPN connections (e.g., OTA web server) are still handled through the WireGuard interface.

### Task watchdog on ESP-IDF v5

The library's lwIP interactions may trigger spurious `task_wdt: task not found` errors during init. Suppress them by temporarily disabling the task watchdog:

```cpp
#include "esp_task_wdt.h"

esp_task_wdt_deinit();
wg.begin(...);

esp_task_wdt_config_t wdt_cfg = { .timeout_ms = 5000, .idle_core_mask = 0, .trigger_panic = false };
esp_task_wdt_init(&wdt_cfg);
```

## Tested on

- M5Stack Tab5 (ESP32-P4) with M5Stack ESP32 Arduino core 3.2.5 (ESP-IDF v5.4)

## License

BSD 3-Clause License — same as the original.

The original WireGuard implementation for lwIP is copyrighted under BSD 3 clause, Copyright (c) 2021 Daniel Hope (www.floorsense.nz). See [LICENSE](LICENSE) for details.

Original Arduino ESP32 port by Kenta Ida (fuga@fugafuga.org).
