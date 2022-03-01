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

#ifndef __OWNG_PLACEHOLDER__
#define __OWNG_PLACEHOLDER__

#include <stdint.h>
#include "platform/Platform_New.h"

/**
 * Simple placeholder template with automatic conversion to a reference of the
 * stored object. Overloaded @c operator&() allows to retrieve casted address
 * of a buffer storing the object.
 */
template<class T>
class Placeholder
{
public:
    T *operator&() {
        return reinterpret_cast<T*>(buf);
    }

    operator T&() {
        return *operator&();
    }

private:
    ALLOC_ALIGNED uint8_t buf[sizeof(T)];
};

#endif /* __OWNG_PLACEHOLDER__ */
