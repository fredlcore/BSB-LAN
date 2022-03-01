/*
 * Copyright (c) 2021 Piotr Stolarz
 * OneWireNg: Arduino 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

#ifndef __OWNG_PLATFORM_DELAY__
#define __OWNG_PLATFORM_DELAY__

#ifdef ARDUINO
# include "Arduino.h"
# define delayUs(__us) delayMicroseconds(__us)
# define delayMs(__ms) delay(__ms)
#else
# ifdef __TEST__
#  include <unistd.h>
#  define delayUs(__us) usleep(__us)
#  define delayMs(__ms) usleep(1000L * (__ms))
# else
#  error "Delay API unsupported for the target platform."
# endif
#endif

#endif /* __OWNG_PLATFORM_DELAY__ */
