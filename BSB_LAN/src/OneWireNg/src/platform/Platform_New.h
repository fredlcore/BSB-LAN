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

#ifndef __OWNG_PLATFORM_NEW__
#define __OWNG_PLATFORM_NEW__
/*
 * The header defines inline new/delete operators. The main purpose for this
 * is to provide basic C++ allocation functionality as C's malloc(), free()
 * counterparts for toolchains that don't support C++ <new> header or the
 * support is insufficient.
 */

#include "../OneWireNg_Config.h"

#if __cplusplus >= 201103L
# define ALLOC_ALIGNED alignas(void*)
# define NOEXCEPT noexcept
#else
# define ALLOC_ALIGNED __attribute__ ((aligned(sizeof(void*))))
# define NOEXCEPT throw()
#endif

#if CONFIG_USE_NATIVE_CPP_NEW
# include <new>
#else
# ifdef __has_include
#  if __has_include(<new>)
#   include <new>
#   ifndef _NEW
#    define _NEW
#   endif
#  endif
# endif
# ifndef _NEW
#  include <stdlib.h>

#  if __cpp_aligned_new
static_assert(alignof(max_align_t) >= __STDCPP_DEFAULT_NEW_ALIGNMENT__,
    "Alt. allocation implementation can't guarantee proper C++17 alignment");
#  endif

inline void *operator new(size_t sz) {
    return malloc(sz);
}

inline void *operator new[](size_t sz) {
    return malloc(sz);
}

inline void *operator new(size_t sz, void *ptr) NOEXCEPT {
    (void)sz;
    return ptr;
}

inline void operator delete(void *ptr) NOEXCEPT {
    free(ptr);
}

inline void operator delete[](void *ptr) NOEXCEPT {
    free(ptr);
}

#  if __cpp_sized_deallocation
inline void operator delete(void* ptr, size_t sz) NOEXCEPT {
    (void)sz;
    free(ptr);
}

inline void operator delete[](void* ptr, size_t sz) NOEXCEPT {
    (void)sz;
    free(ptr);
}
#  endif
# endif /* _NEW */
#endif

#endif /* __OWNG_PLATFORM_NEW__ */
