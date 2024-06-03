/*
 * Copyright (c) 2019-2023 Piotr Stolarz
 * OneWireNg: Arduino 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

#ifndef __OWNG_CONFIG__
#define __OWNG_CONFIG__

#ifdef OWNG_CONFIG_FILE
/*
 * User defined config file
 */
# include OWNG_CONFIG_FILE

#elif !defined(OWNG_NO_NATIVE_CONFIG) && defined(IDF_VER) && !defined(ARDUINO)
/*
 * For ESP-IDF framework there are 2 ways to specify the library configuration:
 * 1. Native configuration (stored in SDK's sdkconfig.h header). For this method
 *    configuration relies on ESP-IDF toolset, which (basing on Kconfig's
 *    deliverables) generates the final sdkconfig.h header. This is the default
 *    and recommended method of configuration.
 * 2. Standard configuration, basing on OneWireNg_Config.h header along
 *    with user's configuration changes provided by parameters macro-defines.
 *    In this method sdkconfig.h header is ignored. The method is chosen if
 *    OWNG_NO_NATIVE_CONFIG is defined.
 *
 * NOTE: In case of Arduino framework, where ESP-IDF SDK is being part of the
 * framework as an auxiliary library, the sdkconfig.h header doesn't contain
 * user's configuration, therefore the standard configuration method is being
 * used.
 */
# include "sdkconfig.h"

# if CONFIG_CRC8_ALGO_BASIC
#  define CONFIG_CRC8_ALGO CRC8_BASIC
# elif CONFIG_CRC8_ALGO_TAB_16LH
#  define CONFIG_CRC8_ALGO CRC8_TAB_16LH
# endif

# if CONFIG_CRC16_ALGO_BASIC
#  define CONFIG_CRC16_ALGO CRC16_BASIC
# elif CONFIG_CRC16_ALGO_TAB_16LH
#  define CONFIG_CRC16_ALGO CRC16_TAB_16LH
# endif

# if CONFIG_BITBANG_TIMING_STRICT
#  define CONFIG_BITBANG_TIMING TIMING_STRICT
# elif CONFIG_BITBANG_TIMING_RELAXED
#  define CONFIG_BITBANG_TIMING TIMING_RELAXED
# elif CONFIG_BITBANG_TIMING_NULL
#  define CONFIG_BITBANG_TIMING TIMING_NULL
# endif

#elif !defined(OWNG_NO_NATIVE_CONFIG) && defined(__MBED__) && !defined(ARDUINO)
/*
 * Similarly to ESP-IDF, for Mbed framework there are 2 ways to specify the
 * library configuration: native (default one, recommended) and standard.
 * OWNG_NO_NATIVE_CONFIG is used to enable the latter.
 */

#else
/*
 * Standard configuration section - configuration parameters are set to their
 * defaults with possible changes in a form of user provided macro-defines.
 */

/**
 * Boolean parameter controlling the way the 1-wire bus is powered for
 * parasitically connected devices.
 *
 * If not configured, the bus is powered by setting the 1-wire data GPIO into
 * the high state and therefore connecting GPIO's voltage source directly to
 * the bus. The mode is feasible for non open-drain type of platforms where
 * a GPIO may provide sufficient power to connected slaves.
 *
 * If configured, the library provides an additional mode with a power-control-GPIO
 * (working in the output mode) controlling a power switching transistor
 * providing an external voltage source to the bus. The GPIO is set to the low
 * state in case the power is enabled on the bus via @ref OneWireNg::powerBus()
 * and to the high state otherwise (the logic may be reversed by
 * @c CONFIG_PWR_CTRL_REV_POLARITY parameter).
 *
 * @note The parameter is supported by bit-banging type of drivers (that is
 *     the ones derived from @ref OneWireNg_BitBang class).
 */
# ifndef CONFIG_PWR_CTRL_ENABLED
#  define CONFIG_PWR_CTRL_ENABLED 0
# endif

/**
 * Boolean parameter to reverse power-control-GPIO logic controlling the power
 * switching transistor.
 *
 * @see CONFIG_PWR_CTRL_ENABLED.
 */
# ifndef CONFIG_PWR_CTRL_REV_POLARITY
#  define CONFIG_PWR_CTRL_REV_POLARITY 0
# endif

/**
 * Boolean parameter to enable 1-wire search.
 *
 * Disabling the 1-wire search may be useful to reduce a footprint of the
 * library on resource constrained platforms, where there is no need to scan
 * the 1-wire bus for present devices (e.g. there is only one device connected).
 */
# ifndef CONFIG_SEARCH_ENABLED
#  define CONFIG_SEARCH_ENABLED 1
# endif

/**
 * Maximum number of family codes used for search filtering.
 * If 0 - filtering disabled.
 *
 * @note The parameter is ignored if 1-wire search is disabled.
 * @see CONFIG_SEARCH_ENABLED
 */
# ifndef CONFIG_MAX_SEARCH_FILTERS
#  define CONFIG_MAX_SEARCH_FILTERS 10
# endif

/**
 * Boolean parameter to enable overdrive (high-speed) mode.
 */
# ifndef CONFIG_OVERDRIVE_ENABLED
#  define CONFIG_OVERDRIVE_ENABLED 0
# endif

/**
 * Type of algorithm used for CRC-8/MAXIM calculation.
 *
 * The macro may be defined as:
 * - @c CRC8_BASIC: Basic method. No memory tables used. This method is
 *   about 8 times slower than the tabled method but no extra memory is used.
 * - @c CRC8_TAB_16LH: 2x16 elements table, 1 byte each.
 */
# ifndef CONFIG_CRC8_ALGO
#  define CONFIG_CRC8_ALGO CRC8_TAB_16LH
# endif

/**
 * Boolean parameter to enable CRC-16/ARC.
 */
# ifndef CONFIG_CRC16_ENABLED
#  define CONFIG_CRC16_ENABLED 0
# endif

/**
 * Type of algorithm used for CRC-16/ARC calculation.
 * Valid only if CRC-16 is enabled via @ref CONFIG_CRC16_ENABLED.
 *
 * The macro may be defined as:
 * - @c CRC16_BASIC: Basic method. No memory tables used. This method is about
 *     8 times slower than the tabled method but no extra memory is used.
 * - @c CRC16_TAB_16LH: 2x16 elements table, 2 bytes each.
 */
# ifndef CONFIG_CRC16_ALGO
#  define CONFIG_CRC16_ALGO CRC16_TAB_16LH
# endif

/**
 * Boolean parameter to control storage of CRC tables in flash memory instead
 * of RAM. Valid only if CRC algorithms are configured for memory tables usage.
 *
 * @note The configuration reduces RAM usage (usually most constrained resource
 *     on embedded devices) by the library instead of flash, but also increases
 *     time needed for CRC calculation, since the flash access is much slower
 *     than RAM.
 */
# ifndef CONFIG_FLASH_CRC_TAB
#  define CONFIG_FLASH_CRC_TAB 0
# endif

/**
 * GPIO blink reveals as a short, unexpected low-high (or vice versa) state
 * change on the digital data wire. The GPIO blink (resulted of the internal
 * library logic) may occur if both of the following circumstances occur:
 *
 * 1. The driver is configured for parasitically powering slaves via GPIO
 *    bit-banging (possible for non open-drain type of output).
 * 2. The underlying platform can't guarantee input to output GPIO switch with
 *    a desired initial state.
 *
 * To prevent the blink resulted of the above @c CONFIG_BUS_BLINK_PROTECTION
 * boolean parameter may be configured. Undesirable side effect of using this
 * parameter is a short period of time when a direct voltage source is provided
 * directly on the data wire. This is basically unwanted behavior in the
 * open-drain environment (except parasitically powering slave devices in a
 * specific period of time during 1-wire activity). The side effect occurs
 * while switching the data wire GPIO from low to high state via the following
 * 3-steps procedure:
 *
 *  1. Initial low state (GPIO configured as output-low).
 *  2. Hight state (GPIO configured as output-high) - direct voltage source
 *     connected to the bus. This is an additional state provided by @c
 *     CONFIG_BUS_BLINK_PROTECTION parameter.
 *  3. High state visible via pull-up resistor (GPIO configured as input).
 *
 * @note @c CONFIG_BUS_BLINK_PROTECTION may be useful to improve 1-wire
 *     communication on long cables by speeding-up low-to-high transition.
 * @note For legacy AVR and ESP8266 platforms (especially working in the
 *     parasitic mode) there are observed problems unless the parameter is
 *     configured.
 */
# ifndef CONFIG_BUS_BLINK_PROTECTION
#  define CONFIG_BUS_BLINK_PROTECTION 0
# endif

/**
 * For platforms which support CPU cycles counter, the boolean parameter enables
 * accurate bit-banging timings by crafted microseconds delay implementation
 * using the counter. The accuracy is especially important for CPUs working
 * with frequencies lower than 40 MHz.
 *
 * @note Currently only ESP32 and ESP8266 support this configuration.
 *     For other platforms the parameter is ignored.
 */
# ifndef CONFIG_BITBANG_DELAY_CCOUNT
#  define CONFIG_BITBANG_DELAY_CCOUNT 1
# endif

/**
 * The parameter controls timing regime while bit-banging 1-wire signals
 * on the data bus. The parameter may be useful while running the library
 * on interrupts intense platforms, where control over the timings may be
 * advisable in terms of overall hardware stability.
 *
 * The macro may be defined as:
 * - @c TIMING_STRICT: All 1-wire signals (except standard reset pulse)
 *   are bit-banged during time-critical (interrupts disabled) state.
 * - @c TIMING_RELAXED: Contrary to the strict configuration the following
 *   signals are bit-banged in time-non-critical (interrupts enabled) state:
 *   - reset sampling period (standard mode),
 *   - write-0 low pulse (standard mode),
 *   - reset low pulse (overdrive mode).
 *   Note, the configuration may cause issues when used along with extensive
 *   amount of interrupts coming from other peripherals (e.g. ESP32 with WiFi
 *   communication).
 * - @c TIMING_NULL: All 1-wire signals are bit-banged in time-non-critical
 *   (interrupts enabled) state. Use with care, especially in the overdrive
 *   mode.
 */
# ifndef CONFIG_BITBANG_TIMING
#  define CONFIG_BITBANG_TIMING TIMING_STRICT
# endif

/**
 * Boolean parameter to enable extended virtual interface.
 *
 * The extended interface enables more advance 1-wire service drivers to be
 * implemented in the future. The penalty is additional overhead needed for
 * calling the virtual methods being part of this interface. Since current
 * implementation doesn't leverage the interface it's recommended to disable
 * this parameter for slower platforms.
 */
# ifndef CONFIG_EXT_VIRTUAL_INTF
#  define CONFIG_EXT_VIRTUAL_INTF 0
# endif

/**
 * For C++11 range-loop used during search-scan process to detect slave devices
 * connected to the bus, the parameter specifies number or the search command
 * resends in case of CRC or bus error. The parameter may be useful for error
 * prone setups. If 0 - no retires.
 *
 * @note The parameter is ignored if 1-wire search is disabled.
 * @see CONFIG_SEARCH_ENABLED
 */
# ifndef CONFIG_ITERATION_RETRIES
#  define CONFIG_ITERATION_RETRIES 0
# endif

/**
 * The library tries to detect if a toolchain supports C++ <new> header, and if
 * so, use it. If the detection fails the library provides custom implementation
 * of basic C++ allocation functionality as C's malloc(), free() counterparts.
 * The boolean parameter forces to always use toolchain's native <new> header
 * even though the detection doesn't indicate existence of such header.
 */
# ifndef CONFIG_USE_NATIVE_CPP_NEW
#  define CONFIG_USE_NATIVE_CPP_NEW 0
# endif

/**
 * Dallas thermometers specific.
 *
 * By default DS18S20 uses 9-bits temperature measurement resolution.
 * Configuring this boolean parameter turns on extended resolution calculation
 * for this type of sensors.
 */
# ifndef CONFIG_DS18S20_EXT_RES
#  define CONFIG_DS18S20_EXT_RES 0
# endif

/**
 * For ESP8266 platform there were reported problems when no extra time
 * has been given after the 1-wire service creation. This parameter specifies
 * amount of time (in msecs) the service delays after performing its
 * initialization but before being ready to use. If 0 - no delay.
 */
# ifndef CONFIG_ESP8266_INIT_TIME
#  define CONFIG_ESP8266_INIT_TIME 500
# endif

/**
 * RP2040 platform is supported by 2 types of drivers:
 * - @c OneWireNg_PicoRP2040 bit-banging driver.
 * - @c OneWireNg_PicoRP2040PIO driver using RP2040's Programmable I/O (PIO)
 *   peripheral for handling 1-wire protocol activities.
 *
 * Configuring the boolean parameter favors the latter PIO driver over the
 * bit-banging one while choosing the driver inside @c OneWireNg_CurrentPlatform.h
 * header.
 *
 * @note @c OneWireNg_PicoRP2040PIO driver doesn't support power-control-GPIO
 *     configuration (@ref CONFIG_PWR_CTRL_ENABLED). Since RP2040 platform is
 *     able to provide direct voltage source via its GPIO pads, parasitically
 *     powered devices need to be powered directly by GPIO controlling the
 *     1-wire bus while using this driver.
 * @note There are observed problems with Pico SDK's serial output
 *     (USB, UART) while using the bit-banging driver in `TIMING_STRICT`
 *     mode (@ref CONFIG_BITBANG_TIMING).
 */
# ifndef CONFIG_RP2040_PIO_DRIVER
#  define CONFIG_RP2040_PIO_DRIVER 1
# endif

/**
 * For RP2040 platform and @ref OneWireNg_PicoRP2040PIO driver, the parameter
 * specifies number of PIO SM used by the driver:
 * - 1: The same SM used for reset and touch,
 * - 2: Separate SMs used for reset and touch.
 *
 * @note The rationale behind this parameter are occasional issues, which
 *     have been observed with starting reset SM while sharing the same SM
 *     for both reset and touch activities.
 */
#ifndef CONFIG_RP2040_PIOSM_NUM_USED
# define CONFIG_RP2040_PIOSM_NUM_USED 2
#endif

#endif

/*
 * If a boolean parameter is defined w/o value assigned, it is assumed as
 * configured.
 */
#define __XEXT1(__prm) (1##__prm)
#define __EXT1(__prm) __XEXT1(__prm)

#ifdef CONFIG_PWR_CTRL_ENABLED
# if (__EXT1(CONFIG_PWR_CTRL_ENABLED) == 1)
#  undef CONFIG_PWR_CTRL_ENABLED
#  define CONFIG_PWR_CTRL_ENABLED 1
# endif
#endif

#ifdef CONFIG_PWR_CTRL_REV_POLARITY
# if (__EXT1(CONFIG_PWR_CTRL_REV_POLARITY) == 1)
#  undef CONFIG_PWR_CTRL_REV_POLARITY
#  define CONFIG_PWR_CTRL_REV_POLARITY 1
# endif
#endif

#ifdef CONFIG_SEARCH_ENABLED
# if (__EXT1(CONFIG_SEARCH_ENABLED) == 1)
#  undef CONFIG_SEARCH_ENABLED
#  define CONFIG_SEARCH_ENABLED 1
# endif
#endif

#ifdef CONFIG_OVERDRIVE_ENABLED
# if (__EXT1(CONFIG_OVERDRIVE_ENABLED) == 1)
#  undef CONFIG_OVERDRIVE_ENABLED
#  define CONFIG_OVERDRIVE_ENABLED 1
# endif
#endif

#ifdef CONFIG_CRC16_ENABLED
# if (__EXT1(CONFIG_CRC16_ENABLED) == 1)
#  undef CONFIG_CRC16_ENABLED
#  define CONFIG_CRC16_ENABLED 1
# endif
#endif

#ifdef CONFIG_FLASH_CRC_TAB
# if (__EXT1(CONFIG_FLASH_CRC_TAB) == 1)
#  undef CONFIG_FLASH_CRC_TAB
#  define CONFIG_FLASH_CRC_TAB 1
# endif
#endif

#ifdef CONFIG_BUS_BLINK_PROTECTION
# if (__EXT1(CONFIG_BUS_BLINK_PROTECTION) == 1)
#  undef CONFIG_BUS_BLINK_PROTECTION
#  define CONFIG_BUS_BLINK_PROTECTION 1
# endif
#endif

#ifdef CONFIG_BITBANG_DELAY_CCOUNT
# if (__EXT1(CONFIG_BITBANG_DELAY_CCOUNT) == 1)
#  undef CONFIG_BITBANG_DELAY_CCOUNT
#  define CONFIG_BITBANG_DELAY_CCOUNT 1
# endif
#endif

#ifdef CONFIG_EXT_VIRTUAL_INTF
# if (__EXT1(CONFIG_EXT_VIRTUAL_INTF) == 1)
#  undef CONFIG_EXT_VIRTUAL_INTF
#  define CONFIG_EXT_VIRTUAL_INTF 1
# endif
#endif

#ifdef CONFIG_USE_NATIVE_CPP_NEW
# if (__EXT1(CONFIG_USE_NATIVE_CPP_NEW) == 1)
#  undef CONFIG_USE_NATIVE_CPP_NEW
#  define CONFIG_USE_NATIVE_CPP_NEW 1
# endif
#endif

#ifdef CONFIG_DS18S20_EXT_RES
# if (__EXT1(CONFIG_DS18S20_EXT_RES) == 1)
#  undef CONFIG_DS18S20_EXT_RES
#  define CONFIG_DS18S20_EXT_RES 1
# endif
#endif

#ifdef CONFIG_RP2040_PIO_DRIVER
# if (__EXT1(CONFIG_RP2040_PIO_DRIVER) == 1)
#  undef CONFIG_RP2040_PIO_DRIVER
#  define CONFIG_RP2040_PIO_DRIVER 1
# endif
#endif

#undef __EXT1
#undef __XEXT1

#endif /* __OWNG_CONFIG__ */
