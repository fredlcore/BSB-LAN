/*
 * Copyright (c) 2021,2022 Piotr Stolarz
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
#include <string.h>  /* memset */
#include "platform/Platform_New.h"

/**
 * Simple placeholder template with automatic conversion to a reference or a
 * pointer of the stored object. Overloaded @c operator&() and @c operator*()
 * allow to retrieve casted address and a reference to the stored object.
 * @c operator->() enables accessing placeholded object's members.
 */
template<class T, bool Init = false>
class Placeholder
{
public:
    T *operator&() {
        return reinterpret_cast<T*>(_buf);
    }

    T& operator*() {
        return *operator&();
    }

    T *operator->() {
        return operator&();
    }

    operator T*() {
        return operator&();
    }

    operator T&() {
        return *operator&();
    }

protected:
    ALLOC_ALIGNED uint8_t _buf[sizeof(T)];
};

/**
 * Zero initialized @c Placeholder specialization.
 */
template<class T>
class Placeholder<T, true>: public Placeholder<T, false>
{
public:
    Placeholder() {
        memset(this->_buf, 0, sizeof(this->_buf));
    }
};

#endif /* __OWNG_PLACEHOLDER__ */
