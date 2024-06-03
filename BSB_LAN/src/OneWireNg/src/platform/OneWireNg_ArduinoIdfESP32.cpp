/*
 * Copyright (c) 2022,2024 Piotr Stolarz
 * OneWireNg: Arduino 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

#include "OneWireNg_ArduinoIdfESP32.h"
#ifdef IDF_VER
# include "sdkconfig.h"
#endif

/*
 * There have been identified and described problems with ESP platforms (both
 * ESP8266 and ESP32) while defining IRAM (TIME_CRITICAL) routines inside header
 * files, resulting with "dangerous relocation: l32r: literal placed after use"
 * linking phase errors. The solution to avoid this type of errors is to define
 * the IRAMed routines in separate compilation unit.
 */
#if (defined(ARDUINO_ARCH_ESP32) || defined(IDF_VER)) && \
    !(defined(ARDUINO_ARCH_ESP8266) || defined(CONFIG_IDF_TARGET_ESP8266))
#include <assert.h>
#include "driver/gpio.h"
#include "soc/gpio_periph.h"
#include "Platform_TimeCritical.h"

#define __INPUT  0x01
#define __OUTPUT 0x02
#define __PULLUP 0x04

static void _pinMode(uint8_t pin, uint8_t mode)
{
    gpio_config_t conf = {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
#if SOC_GPIO_SUPPORT_PIN_HYS_FILTER
        .hys_ctrl_mode = GPIO_HYS_SOFT_DISABLE,
#endif
    };
    conf.mode = (gpio_mode_t)(mode & (__INPUT | __OUTPUT));
    if (mode & __PULLUP) {
        conf.pull_up_en = GPIO_PULLUP_ENABLE;
    }
    gpio_config(&conf);
}

#ifndef GPIO_PIN_COUNT
# error "GPIO_PIN_COUNT not defined for this version of SDK"
#endif

#if (GPIO_PIN_COUNT <= 32)
# define REG_GPIO_IN_LO GPIO.in.val
# define REG_GPIO_OUT_SET_LO GPIO.out_w1ts.val
# define REG_GPIO_OUT_CLR_LO GPIO.out_w1tc.val
# define REG_GPIO_MOD_SET_LO GPIO.enable_w1ts.val
# define REG_GPIO_MOD_CLR_LO GPIO.enable_w1tc.val
#else
# if defined(CONFIG_IDF_TARGET_ESP32P4)
#  define REG_GPIO_IN_LO GPIO.in.val
#  define REG_GPIO_OUT_SET_LO GPIO.out_w1ts.val
#  define REG_GPIO_OUT_CLR_LO GPIO.out_w1tc.val
#  define REG_GPIO_MOD_SET_LO GPIO.enable_w1ts.val
#  define REG_GPIO_MOD_CLR_LO GPIO.enable_w1tc.val
# else
#  define REG_GPIO_IN_LO GPIO.in
#  define REG_GPIO_OUT_SET_LO GPIO.out_w1ts
#  define REG_GPIO_OUT_CLR_LO GPIO.out_w1tc
#  define REG_GPIO_MOD_SET_LO GPIO.enable_w1ts
#  define REG_GPIO_MOD_CLR_LO GPIO.enable_w1tc
# endif
# define REG_GPIO_IN_HI GPIO.in1.val
# define REG_GPIO_OUT_SET_HI GPIO.out1_w1ts.val
# define REG_GPIO_OUT_CLR_HI GPIO.out1_w1tc.val
# define REG_GPIO_MOD_SET_HI GPIO.enable1_w1ts.val
# define REG_GPIO_MOD_CLR_HI GPIO.enable1_w1tc.val
#endif

#define __READ_GPIO(gs) \
    ((*gs.inReg & gs.bmsk) != 0)

#define __WRITE0_GPIO(gs) \
    *gs.outClrReg = gs.bmsk

#define __WRITE1_GPIO(gs) \
    *gs.outSetReg = gs.bmsk

#define __WRITE_GPIO(gs, st) \
    if (st) __WRITE1_GPIO(gs); \
    else __WRITE0_GPIO(gs)

#define __GPIO_AS_INPUT(gs) \
    *gs.modClrReg = gs.bmsk

#define __GPIO_AS_OUTPUT(gs) \
    *gs.modSetReg = gs.bmsk

TIME_CRITICAL int OneWireNg_ArduinoIdfESP32::readDtaGpioIn()
{
    return __READ_GPIO(_dtaGpio);
}

TIME_CRITICAL void OneWireNg_ArduinoIdfESP32::setDtaGpioAsInput()
{
    __GPIO_AS_INPUT(_dtaGpio);
}

#if CONFIG_PWR_CTRL_ENABLED
TIME_CRITICAL void OneWireNg_ArduinoIdfESP32::writeGpioOut(
    int state, GpioType gpio)
{
    if (gpio == GPIO_DTA) {
        __WRITE_GPIO(_dtaGpio, state);
    } else {
        __WRITE_GPIO(_pwrCtrlGpio, state);
    }
}

TIME_CRITICAL void OneWireNg_ArduinoIdfESP32::setGpioAsOutput(
    int state, GpioType gpio)
{
    if (gpio == GPIO_DTA) {
        __WRITE_GPIO(_dtaGpio, state);
        __GPIO_AS_OUTPUT(_dtaGpio);
    } else {
        __WRITE_GPIO(_pwrCtrlGpio, state);
        __GPIO_AS_OUTPUT(_pwrCtrlGpio);
    }
}
#else
TIME_CRITICAL void OneWireNg_ArduinoIdfESP32::writeGpioOut(int state)
{
    __WRITE_GPIO(_dtaGpio, state);
}

TIME_CRITICAL void OneWireNg_ArduinoIdfESP32::setGpioAsOutput(int state)
{
    __WRITE_GPIO(_dtaGpio, state);
    __GPIO_AS_OUTPUT(_dtaGpio);
}
#endif /* CONFIG_PWR_CTRL_ENABLED */

#if CONFIG_OVERDRIVE_ENABLED
TIME_CRITICAL int OneWireNg_ArduinoIdfESP32::touch1Overdrive()
{
    __WRITE0_GPIO(_dtaGpio);
    __GPIO_AS_OUTPUT(_dtaGpio);

    /* speed up low-to-high transition */
    __WRITE1_GPIO(_dtaGpio);
    __GPIO_AS_INPUT(_dtaGpio);

    return __READ_GPIO(_dtaGpio);
}
#endif

void OneWireNg_ArduinoIdfESP32::initDtaGpio(unsigned pin, bool pullUp)
{
    assert(GPIO_IS_VALID_GPIO((int)pin) && GPIO_IS_VALID_OUTPUT_GPIO((int)pin));

#if CONFIG_BITBANG_DELAY_CCOUNT
    /* retrieve CPU frequency (for clock-count bit-banging mode) */
    ccntUpdateCpuFreqMHz();
#endif

    if (pin < 32) {
        _dtaGpio.bmsk = (uint32_t)(1UL << pin);
        _dtaGpio.inReg = &REG_GPIO_IN_LO;
        _dtaGpio.outSetReg = &REG_GPIO_OUT_SET_LO;
        _dtaGpio.outClrReg = &REG_GPIO_OUT_CLR_LO;
        _dtaGpio.modSetReg = &REG_GPIO_MOD_SET_LO;
        _dtaGpio.modClrReg = &REG_GPIO_MOD_CLR_LO;
    }
#if (GPIO_PIN_COUNT > 32)
    else {
        _dtaGpio.bmsk = (uint32_t)(1UL << (pin - 32));
        _dtaGpio.inReg = &REG_GPIO_IN_HI;
        _dtaGpio.outSetReg = &REG_GPIO_OUT_SET_HI;
        _dtaGpio.outClrReg = &REG_GPIO_OUT_CLR_HI;
        _dtaGpio.modSetReg = &REG_GPIO_MOD_SET_HI;
        _dtaGpio.modClrReg = &REG_GPIO_MOD_CLR_HI;
    }
#endif
    _pinMode(pin, __INPUT | (pullUp ? __PULLUP : 0));
    setupDtaGpio();
}

#if CONFIG_PWR_CTRL_ENABLED
void OneWireNg_ArduinoIdfESP32::initPwrCtrlGpio(unsigned pin)
{
    assert(GPIO_IS_VALID_GPIO((int)pin) && GPIO_IS_VALID_OUTPUT_GPIO((int)pin));

    if (pin < 32) {
        _pwrCtrlGpio.bmsk = (uint32_t)(1UL << pin);
        _pwrCtrlGpio.outSetReg = &REG_GPIO_OUT_SET_LO;
        _pwrCtrlGpio.outClrReg = &REG_GPIO_OUT_CLR_LO;
        _pwrCtrlGpio.modSetReg = &REG_GPIO_MOD_SET_LO;
        _pwrCtrlGpio.modClrReg = &REG_GPIO_MOD_CLR_LO;
    }
# if (GPIO_PIN_COUNT > 32)
    else {
        _pwrCtrlGpio.bmsk = (uint32_t)(1UL << (pin - 32));
        _pwrCtrlGpio.outSetReg = &REG_GPIO_OUT_SET_HI;
        _pwrCtrlGpio.outClrReg = &REG_GPIO_OUT_CLR_HI;
        _pwrCtrlGpio.modSetReg = &REG_GPIO_MOD_SET_HI;
        _pwrCtrlGpio.modClrReg = &REG_GPIO_MOD_CLR_HI;
    }
# endif
    _pinMode(pin, __OUTPUT);
    setupPwrCtrlGpio(true);
}
#endif /* CONFIG_PWR_CTRL_ENABLED */

#undef __GPIO_AS_OUTPUT
#undef __GPIO_AS_INPUT
#undef __WRITE_GPIO
#undef __WRITE1_GPIO
#undef __WRITE0_GPIO
#undef __READ_GPIO

#undef __PULLUP
#undef __OUTPUT
#undef __INPUT

#endif /* ESP32 */
