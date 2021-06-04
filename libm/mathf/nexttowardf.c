/* SPDX-License-Identifier: RichFelker */
/* Copyright © 2005-2014 Rich Felker, et al. */

#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_LONG_DOUBLE_IS_64BITS

float nexttowardf(float x, long double y)
{
    return nextafterf(x, (float) y);
}

#else

union fshape {
    float value;
    uint32_t bits;
};

float nexttowardf(float x, long double y)
{
    union fshape ux;
    uint32_t e;

    if (isnan(x) || isnan(y)) {
        return x + y;
    }

    if (x == y) {
        return y;
    }

    ux.value = x;

    if (x == 0) {
        ux.bits = 1;

        if (signbit(y)) {
            ux.bits |= 0x80000000U;
        }
    } else if (x < y) {
        if (signbit(x)) {
            ux.bits--;
        } else {
            ux.bits++;
        }
    } else {
        if (signbit(x)) {
            ux.bits++;
        } else {
            ux.bits--;
        }
    }

    e = ux.bits & 0x7f800000;

    /* raise overflow if ux.value is infinite and x is finite */
    if (e == 0x7f800000) {
        return __raise_overflowf(x);
    }

    /* raise underflow if ux.value is subnormal or zero */
    if (e == 0) {
        (void) __raise_underflowf(x);
    }

    return ux.value;
}

#endif /* __LIBMCS_LONG_DOUBLE_IS_64BITS */

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double nexttoward(double x, long double y)
{
    return (double) nexttowardf((float) x, y);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
