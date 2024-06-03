# OneWireNg

[![Arduino builds](https://github.com/pstolarz/OneWireNg/actions/workflows/arduino-builds.yml/badge.svg?branch=master)](https://github.com/pstolarz/OneWireNg/actions/workflows/arduino-builds.yml)
[![PlatformIO builds](https://github.com/pstolarz/OneWireNg/actions/workflows/platformio-builds.yml/badge.svg?branch=master)](https://github.com/pstolarz/OneWireNg/actions/workflows/platformio-builds.yml)
[![ESP-IDF builds](https://github.com/pstolarz/OneWireNg/actions/workflows/espidf-builds.yml/badge.svg?branch=master)](https://github.com/pstolarz/OneWireNg/actions/workflows/espidf-builds.yml)
[![Pico SDK builds](https://github.com/pstolarz/OneWireNg/actions/workflows/picosdk-builds.yml/badge.svg?branch=master)](https://github.com/pstolarz/OneWireNg/actions/workflows/picosdk-builds.yml)
[![Mbed OS builds](https://github.com/pstolarz/OneWireNg/actions/workflows/mbedos-builds.yml/badge.svg?branch=master)](https://github.com/pstolarz/OneWireNg/actions/workflows/mbedos-builds.yml)
[![Unit tests](https://github.com/pstolarz/OneWireNg/actions/workflows/ut.yml/badge.svg?branch=master)](https://github.com/pstolarz/OneWireNg/actions/workflows/ut.yml)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/pstolarz/library/OneWireNg.svg)](https://registry.platformio.org/libraries/pstolarz/OneWireNg)
<br>

This is an 1-wire service library, intended as an alternative for the classic
[OneWire](https://github.com/PaulStoffregen/OneWire) library. The library
provides basic 1-wire services (reset, search, touch, read, write, parasite
powering) and may serve for further work while interfacing with various 1-wire
devices.

## Table of Contents

* [Features](#features)
* [Usage](#usage)
  * [ESP-IDF](#usage_idf)
  * [Pico SDK](#usage_pico)
  * [Mbed OS](#usage_mbed)
* [Supported platforms](#supported_plats)
* [Overdrive mode](#od_mode)
* [Parasite powering](#parasite)
* [Architecture details](#arch)
  * [`OneWireNg`](#arch_owng)
    * [Memory allocation caveat](#arch_owng_malloc)
  * [`OneWireNg_BitBang`](#arch_bb)
  * [`OneWireNg_PLATFORM`](#arch_plat)
    * [RP2040 drivers](#arch_rp2040)
* [OneWire compatibility](#ow)
  * [DallasTemperature library](#ow_dallas)
* [License](#license)

<a name="features"></a>
## Features

* All bus activities are performed respecting open-drain character of the 1-wire
  protocol.

  During normal 1-wire activities, the master MCU GPIO controlling the bus is
  never set high (providing direct voltage source on the bus) instead the GPIO
  is switched to the reading mode causing the high state seen on the bus via
  the pull-up resistor.

* 1-wire touch support.

  The 1-wire touch may substantially simplify complex bus activities consisting
  of write-read pairs by combining them into a single touch activity. See
  [examples](examples) for details.

* Parasite powering support.

  The 1-wire bus may be powered directly by the master MCU GPIO or via a switching
  transistor controlled by a dedicated MCU GPIO. More details [below](#parasite-powering).

* Search filtering.

  Search algorithm allows efficient filtering basing on a selected set of family
  codes. Maximum size of the set is configurable by `CONFIG_MAX_SEARCH_FILTERS`.

* Overdrive (high-speed) mode support.

  The overdrive mode enables speed up the 1-wire communication by a factor of 10.
  Only limited number of 1-wire devices support this mode (e.g. DS2408, DS2431).

* Dallas temperature sensors drivers.

  [Generic Dallas thermometers](src/drivers/DSTherm.h) and
  [MAX31850/MAX31851](src/drivers/MAX31850.h) drivers for handling Dallas
  thermometers and thermocouples. See [examples](examples) for details.

* OneWire compatibility interface.

  The interface allows effortless switch into OneWireNg for projects using
  OneWire library. See [below](#onewire-compatibility) for details.

* Clear and flexible architecture.

  The code architecture allows fast and easy porting for new Arduino platforms
  or even usage core part of the library outside the Arduino environment.
  See below for usage details on ESP-IDF, Pico SDK or Mbed OS based platforms.

<a name="usage"></a>
## Usage

Refer to [`examples`](examples) directory for usage details for each of the
supported frameworks: Arduino, ESP-IDF, Pico SDK and Mbed.

For API specification refer to sources inline documentation (mainly
[`OneWireNg`](src/OneWireNg.h) class). For convenience it's possible to generate
HTML/LaTeX [Doxygen](https://www.doxygen.nl/index.html) documentation by issuing
`doxygen` from the main library directory. The documentation will be placed in
`extras/doc`.

File [`src/OneWireNg_Config.h`](src/OneWireNg_Config.h) contains parameters
configuring the library functionality. See the file for more details.

<a name="usage_idf"></a>
### ESP-IDF (incl. ESP8266 RTOS SDK v3)

Preferred way to add OneWireNg as a library for Espressif [ESP-IDF](https://github.com/espressif/esp-idf)
framework is to add it as a git submodule located at project's `components`
subdirectory:

```
git submodule add -- https://github.com/pstolarz/OneWireNg components/OneWireNg
```

Next checkout specific library `VERSION`:

```
cd components/OneWireNg
git checkout VERSION
```

While added the library shall be configured via ESP-IDF native configuration
(see [`Kconfig`](Kconfig) for details), which shadows the `OneWireNg_Config.h`
configuration file.

<a name="usage_pico"></a>
### Pico SDK

Preferred way to add OneWireNg as a library for [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk)
framework is to add it as a git submodule:

```
git submodule add -- https://github.com/pstolarz/OneWireNg OneWireNg
```

Checkout on a specific library `VERSION`:

```
cd OneWireNg
git checkout VERSION
```

Finally add OneWireNg as a library in a Pico SDK project's `CMakeLists.txt`
file as follows:

```
cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(some_project)
pico_sdk_init()

add_executable(some_project)

...

add_subdirectory(OneWireNg)
target_link_libraries(some_project PRIVATE OneWireNg)

pico_add_extra_outputs(some_project)
```

<a name="usage_mbed"></a>
### Mbed OS

*NOTE: The library usage for [Mbed OS](https://os.mbed.com) is experimental.
The only board used for tests of this framework is NUCLEO-L552ZE-Q.*

To add OneWireNg as a library for Mbed framework project use (for specific
`VERSION`):

```
mbed add https://github.com/pstolarz/OneWireNg#VERSION
```

While added the library shall be configured via Mbed native configuration (see
[`mbed_lib.json`](mbed_lib.json) for details), which shadows the
`OneWireNg_Config.h` configuration file.

<a name="supported_plats"></a>
## Supported platforms

* Arduino AVR.
    * Platform class: `OneWireNg_ArduinoAVR`.
    * Tested on Arduino UNO (ATmega328P).
* Arduino megaAVR (recent Microchip AVR architecture).
    * Platform class: `OneWireNg_ArduinoMegaAVR`.
    * [Reported to be working.](https://github.com/SpenceKonde/megaTinyCore/blob/master/megaavr/extras/LibraryCompatibility.md)
* Arduino ESP8266/ESP-IDF.
    * Platform class: `OneWireNg_ArduinoIdfESP8266`.
    * Tested on WemOS D1.
* Arduino/ESP-IDF ESP32 (classic, S, C, H and P families).
    * Platform class: `OneWireNg_ArduinoIdfESP32`.
    * Tested on ESP32-WROOM-32, ESP32-S2-WROVER, ESP32-S3-WROOM-1, ESP32-C3-32S-Kit.
* Arduino/Pico SDK RP2040.
    * Platform classes: `OneWireNg_PicoRP2040`, `OneWireNg_PicoRP2040PIO`.
    * Tested on Raspberry Pi Pico.
* Arduino/Mbed OS based platforms (incl. Edge, Giga, Nano, Nicla, Portena, RP2040).
    * Platform class: `OneWireNg_ArduinoMbedHAL`.
    * Tested on Raspberry Pi Pico, Nucleo-144 (L552ZE-Q).
* Arduino STM32.
    * Platform class: `OneWireNg_ArduinoSTM32`.
    * Tested on Nucleo-144 (L552ZE-Q).
* Arduino SAM.
    * Platform class: `OneWireNg_ArduinoSAM`.
    * [Reported to be working.](https://github.com/pstolarz/OneWireNg/issues/33)
* Arduino SAMD/SAMD-Beta.
    * Platform class: `OneWireNg_ArduinoSAMD`.
    * **Not tested**.

NOTE: Expect more platforms support in the future. **I'm inviting all developers**
eager to help me with porting and testing the library for new platforms.

<a name="od_mode"></a>
## Overdrive mode

When configured with `CONFIG_OVERDRIVE_ENABLED` the library supports 1-wire
overdrive mode. The mode requires very strict and short timings while bit-banging
data on the 1-wire bus, therefore is vulnerable for any inaccuracies.

While configured with `CONFIG_BITBANG_DELAY_CCOUNT` the mode is confirmed to
work on the following platforms and CPU frequencies:

* AVR
    * Arduino UNO (ATmega328P); 16MHz.
* ESP8266
    * WemOS D1; 160,80MHz.
* ESP32
    * ESP32-WROOM-32; 240,160,80,40,20MHz
    * ESP32-S2-WROVER; 240,160,80,40,20,10MHz
    * ESP32-S3-WROOM-1; 240,160,80MHz (other freqs not tested)
    * ESP32-C3-32S-Kit; 240,160MHz (other freqs not tested)
* RP2040
    * Raspberry Pi Pico; 50-250MHz (bit-banging and PIO drivers)
* STM32
    * NUCLEO-L552ZE-Q; 110MHz

<a name="parasite"></a>
## Parasite powering

**Bit-banging drivers**

For bit-banging type of drivers, the library supports two modes of providing
a direct voltage source on the 1-wire bus for parasitically powered slaves:

1. If platform's GPIO set to the high-state (in the output mode) is able to
   serve as a voltage source, the library may leverage this trait. The master
   MCU GPIO controlling the 1-wire bus is set to the high-state powering the
   bus when additional energy is needed for connected slaves.

2. If platform's GPIO is of an open-drain type, then a GPIO is not able to
   directly serve as a voltage source powering the connected slaves. In this
   case an additional switching transistor is leveraged to control providing
   an external power source to the bus and is controlled by a dedicated
   power-control-GPIO as presented on the following figure.

![Switching transistor parasite powering](extras/img/parasite.svg)

To enable the second mode the library needs to be configured with
`CONFIG_PWR_CTRL_ENABLED`.

Choice between the two types is made by selecting appropriate constructor of a
platform class. For example:

```cpp
#include "OneWireNg_CurrentPlatform.h"

static OneWireNg *ow = NULL;

void setup()
{
    /*
     * Macro-defines used:
     *
     * OW_PIN: GPIO pin number used for bit-banging 1-wire bus.
     * PWR_CTRL_PIN: power-control-GPIO pin number (optional).
     */
#ifdef PWR_CTRL_PIN
# if CONFIG_PWR_CTRL_ENABLED
#  error "CONFIG_PWR_CTRL_ENABLED needs to be configured"
# endif
    // switching transistor powering
    ow = new OneWireNg_CurrentPlatform(OW_PIN, PWR_CTRL_PIN);
#else
    // GPIO bit-bang powering
    ow = new OneWireNg_CurrentPlatform(OW_PIN);
#endif

    // ...

    // write array of bytes and power the bus subsequently;
    // the bus is powered until explicit unpowering or next 1-wire bus activity
    ow->writeBytes(bytes, bytes_len, true);

    // wait for connected slaves to fulfill their task requiring extra powering
    delay(750);

    // unpower the bus explicitly
    ow->powerBus(false);
}
```

configures 1-wire service to work in one of the above modes.

**RP2040 PIO driver**

RP2040 PIO driver (`OneWireNg_PicoRP2040PIO` class) doesn't support
power-control-GPIO configuration. Since RP2040 platform is able to provide
direct voltage source via its GPIO pads, parasitically powered devices need
to be powered directly by GPIO controlling the 1-wire bus while using this
driver.

**Caveats**

* Parasite powered slaves are less stable (more error prone) than regularly
  powered devices. If possible, try to avoid parasitically powered setups.

* For legacy AVR (non mega-AVR) and ESP8266 platforms (especially working
  in the parasitic mode) there are observed problems unless the parameter
  `CONFIG_BUS_BLINK_PROTECTION` is configured.

<a name="arch"></a>
## Architecture details

![OneWirNg class diagram](extras/img/classOneWireNg__inherit__graph.png)

<a name="arch_owng"></a>
### `OneWireNg`

The class provides public interface for 1-wire service. Object of this class
isn't constructed directly rather than casted from a derived class object
implementing platform specific details.

As an example:

```cpp
#include "OneWireNg_CurrentPlatform.h"

static OneWireNg *ow = NULL;

void setup()
{
    OneWireNg::Id id;
    ow = new OneWireNg_CurrentPlatform(10);

    ow->searchReset();
    while (ow->search(id) == OneWireNg::EC_MORE) {
        // 'id' contains 1-wire address of a connected slave
    }
}
```

creates 1-wire service interface for current platform and performs search on
the bus. The bus is controlled by MCU pin number 10. Alternatively it is possible
to use C++11 range loop to detect slaves connected to the 1-wire bus:

```cpp
#include "OneWireNg_CurrentPlatform.h"

static OneWireNg *ow = NULL;

void setup()
{
    ow = new OneWireNg_CurrentPlatform(10);

    for (const auto& id: *ow) {
        // 'id' contains 1-wire address of a connected slave
    }
}
```

NOTE: During creation of an `OneWireNg` object, the class constructor performs
various platform specific activities required to setup the 1-wire service. For
this reason the `OneWireNg` object may be created only when the platform itself
is fully started-up and initialized, e.g. in `setup()` method but not as a
global variable initialized during its creation.

Additionally it is strongly recommended to maintain single `OneWireNg` service
object across all 1-wire activities handled by this service on a specific bus.
Of course it is perfectly possible to created multiple `OneWireNg` services
handling different 1-wire buses.

<a name="arch_owng_malloc"></a>
#### Memory allocation caveat

If heap allocation is inadvisable use in-place `new` operator:

```cpp
#include "OneWireNg_CurrentPlatform.h"

ALLOC_ALIGNED static uint8_t OneWireNg_buf[sizeof(OneWireNg_CurrentPlatform)];
static OneWireNg *ow = NULL;

void setup()
{
    ow = new (OneWireNg_buf) OneWireNg_CurrentPlatform(10);
    // ...
}
```

or use `Placeholder` utility template to store `OneWireNg` specialized object:

```cpp
#include "OneWireNg_CurrentPlatform.h"
#include "utils/Placeholder.h"

static Placeholder<OneWireNg_CurrentPlatform> ow;

void setup()
{
    // initialize the placeholded object by in-place new
    new (&ow) OneWireNg_CurrentPlatform(10);
    // ...
}
```

Refer to [examples](examples) for more information how to use the `Placeholder`
in the context of object stored within.

<a name="arch_bb"></a>
### `OneWireNg_BitBang`

The class is derived from `OneWireNg` and implements the 1-wire interface basing
on GPIO bit-banging. Object of this class isn't constructed directly rather than
the class is intended to be inherited by a derived class providing protected
interface implementation for low level GPIO activities (set mode, read, write).

<a name="arch_plat"></a>
### `OneWireNg_PLATFORM`

Are family of classes providing platform specific implementation (`PLATFORM`
states for a platform name e.g. `OneWireNg_ArduinoAVR` provides AVR implementation
for Arduino environment).

The platform classes implement `OneWireNg` interface directly (via direct
`OneWireNg` class inheritance) or indirectly (e.g. GPIO bit-banging implementation
bases on `OneWireNg_BitBang`, which provides GPIO bit-banging 1-wire service
implementation leaving the platform class to provide platform specific low-level
GPIO activities details).

Platform classes have a public constructor allowing to create 1-wire service for
a particular platform (see [above](#architecture-details)).

NOTE: For the convenience there has been provided `OneWireNg_CurrentPlatform.h`
header which tries to detect platform the compilation is proceeded and:
 * include proper platform class header,
 * assign `OneWireNg_CurrentPlatform` macro-define to the detected platform class.

<a name="arch_rp2040"></a>
### RP2040 drivers

`OneWireNg_PicoRP2040PIO` is derived from `OneWireNg` and implements the 1-wire
interface for RP2040 MCU using Programmable I/O (PIO) peripheral. Second type
of driver supporting RP2040 platform is `OneWireNg_PicoRP2040` bit-banging
driver. Use `CONFIG_RP2040_PIO_DRIVER` configuration parameter to setup a
specific driver for the platform.

NOTE: There are observed problems with Pico SDK's serial output (USB,
UART) while using the bit-banging driver in `TIMING_STRICT` mode (see
`CONFIG_BITBANG_TIMING`).

<a name="ow"></a>
## OneWire compatibility

[`OneWire`](src/OneWire.h) class provides compatibility interface between
OneWireNg and [OneWire](https://github.com/PaulStoffregen/OneWire) library.
The main purpose of this class is to provide fast and effortless mechanism for
developers experiencing issues with OneWire and eager to give OneWireNg a try.
Finally, it's strongly recommended to switch into OneWireNg interface rather
than stay with the OneWire due to OneWireNg's more mature and feature-rich API
(search filtering, OD mode, touch support).

<a name="ow_dallas"></a>
### DallasTemperature library

As an example of usage of the compatibility interface there has been created
the [following fork](https://github.com/pstolarz/Arduino-Temperature-Control-Library/tree/OneWireNg)
of [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library)
library ported with OneWireNg.

<a name="license"></a>
## License

2 clause BSD license. See [`LICENSE`](LICENSE) file for details.
