/*
 * Copyright (c) 2019-2022 Piotr Stolarz
 * OneWireNg: Arduino 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

#include "OneWireNg_BitBang.h"
#include "platform/Platform_Delay.h"

#define TIMING_STRICT   1
#define TIMING_RELAXED  2
#define TIMING_NULL     3

#if (CONFIG_BITBANG_TIMING == TIMING_STRICT)
# define TC_STRICT_ENTER() timeCriticalEnter()
# define TC_STRICT_EXIT() timeCriticalExit()
# define TC_RELAXED_ENTER() timeCriticalEnter()
# define TC_RELAXED_EXIT() timeCriticalExit()
# define TC_RELAXED_TO_STRICT()
#elif (CONFIG_BITBANG_TIMING == TIMING_RELAXED)
# define TC_STRICT_ENTER() timeCriticalEnter()
# define TC_STRICT_EXIT() timeCriticalExit()
# define TC_RELAXED_ENTER()
# define TC_RELAXED_EXIT()
# define TC_RELAXED_TO_STRICT() timeCriticalEnter()
#elif (CONFIG_BITBANG_TIMING == TIMING_NULL)
# define TC_STRICT_ENTER()
# define TC_STRICT_EXIT()
# define TC_RELAXED_ENTER()
# define TC_RELAXED_EXIT()
# define TC_RELAXED_TO_STRICT()
#else
# error "Invalid CONFIG_BITBANG_TIMING"
#endif

/*
 * Standard mode timings
 */
/* min. 480 us */
#define STD_RESET_LOW   480
/* reset high; presence-detect sampling: 68-75 us (relaxed) */
#define STD_RESET_SMPL  70
/* reset trailing high */
#define STD_RESET_END   410

/* write-0 low: 60-120 us (relaxed) */
#define STD_WRITE0_LOW  60
/* write-0 trailing high: 5-15 us */
#define STD_WRITE0_END  10

/* write-1 low (strict) */
#define STD_WRITE1_LOW  5
/* write-1 high; sampling max 15 us (low + high; strict) */
#define STD_WRITE1_SMPL 8
/* write-1 trailing high */
#define STD_WRITE1_END  56

/*
 * Overdrive mode timings
 */
/* reset low: 53-80 us (relaxed) */
#define OD_RESET_LOW    68
/* reset high; presence-detect sampling: 8-9 us (strict) */
#define OD_RESET_SMPL   8
/* reset high; trailing part */
#define OD_RESET_END    40

/* write-0 low: 8-13 us (strict) */
#define OD_WRITE0_LOW   8
/* write-0 trailing high: 1-2 us */
#define OD_WRITE0_END   1

/* write-1 low: 0-1 us (strict) */
#define OD_WRITE1_LOW   0   /* <=0: no delay, >0: usec delay */
/* write-1 high; sampling max 2 us (low + high; strict) */
#define OD_WRITE1_SMPL  0   /* <=0: no delay, >0: usec delay */
/* write-1 trailing high */
#define OD_WRITE1_END   7

TIME_CRITICAL OneWireNg::ErrorCode OneWireNg_BitBang::reset()
{
    int presPulse;

    if (_pwre) powerBus(false);

#if CONFIG_OVERDRIVE_ENABLED
    if (_overdrive)
    {
        /* Overdrive mode
         */
        TC_RELAXED_ENTER();
        setBus(0);
        delayUs(OD_RESET_LOW);
        TC_RELAXED_TO_STRICT();
        setBus(1);
        delayUs(OD_RESET_SMPL);
        presPulse = readDtaGpioIn();
        TC_STRICT_EXIT();
        delayUs(OD_RESET_END);
    } else
#endif
    {
        /* Standard mode
         */
        setBus(0);
        delayUs(STD_RESET_LOW);
        TC_RELAXED_ENTER();
        setBus(1);
        delayUs(STD_RESET_SMPL);
        presPulse = readDtaGpioIn();
        TC_RELAXED_EXIT();
        delayUs(STD_RESET_END);
    }
    return (presPulse ? EC_NO_DEVS : EC_SUCCESS);
}

TIME_CRITICAL int OneWireNg_BitBang::touchBit(int bit, bool power)
{
    int smpl = 0;

    if (_pwre) powerBus(false);

#if CONFIG_OVERDRIVE_ENABLED
    if (_overdrive)
    {
        /* Overdrive mode
         */
        if (bit != 0)
        {
            /* write-1 with sampling (alias read) */
            TC_STRICT_ENTER();
            smpl = touch1Overdrive();
            if (power) powerBus(true);
            TC_STRICT_EXIT();
            delayUs(OD_WRITE1_END);
        } else
        {
            /* write-0 */
            TC_STRICT_ENTER();
            setBus(0);
            delayUs(OD_WRITE0_LOW);
            setBus(1);
            if (power) powerBus(true);
            TC_STRICT_EXIT();
            delayUs(OD_WRITE0_END);
        }
    } else
#endif
    {
        /* Standard mode
         */
        if (bit != 0)
        {
            /* write-1 with sampling (alias read) */
            TC_STRICT_ENTER();
            setBus(0);
            delayUs(STD_WRITE1_LOW);
            setBus(1);
            delayUs(STD_WRITE1_SMPL);
            smpl = readDtaGpioIn();
            if (power) powerBus(true);
            TC_STRICT_EXIT();
            delayUs(STD_WRITE1_END);
        } else
        {
            /* write-0 */
            TC_RELAXED_ENTER();
            setBus(0);
            delayUs(STD_WRITE0_LOW);
            setBus(1);
            if (power) powerBus(true);
            TC_RELAXED_EXIT();
            delayUs(STD_WRITE0_END);
        }
    }
    return smpl;
}

#if CONFIG_OVERDRIVE_ENABLED
int OneWireNg_BitBang::touch1Overdrive()
{
    setBus(0);
# if OD_WRITE1_LOW > 0
    delayUs(OD_WRITE1_LOW);
# endif
    /* speed up low-to-high transition */
# if !CONFIG_BUS_BLINK_PROTECTION
    writeDtaGpioOut(1);
# endif
    setBus(1);
# if OD_WRITE1_SMPL > 0
    delayUs(OD_WRITE1_SMPL);
# endif
    return readDtaGpioIn();
}
#endif

OneWireNg::ErrorCode OneWireNg_BitBang::powerBus(bool on)
{
#if CONFIG_PWR_CTRL_ENABLED
    if (_pwrp) {
# if CONFIG_PWR_CTRL_REV_POLARITY
        writeGpioOut((on != 0), GPIO_CTRL_PWR);
# else
        writeGpioOut(!on, GPIO_CTRL_PWR);
# endif
    } else
#endif
    if (on) {
        setDtaGpioAsOutput(1);
    } else {
        setDtaGpioAsInput();
    }
    _pwre = on;
    return EC_SUCCESS;
}
