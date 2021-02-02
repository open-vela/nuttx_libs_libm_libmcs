/* SPDX-License-Identifier: RichFelker */
/* Copyright © 2005-2014 Rich Felker, et al. */

#include <math.h>
#include "../common/tools.h"

union fshape {
    float value;
    uint32_t bits;
};

/* This is only necessary because the implementation of isnan only works */
/* properly when long double == double. */
/* See: https://sourceware.org/ml/newlib/2014/msg00684.html */
#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

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
            ux.bits |= 0x80000000;
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
        volatile float force_eval;
        force_eval = x + x;
    }

    /* raise underflow if ux.value is subnormal or zero */
    if (e == 0) {
        volatile float force_eval;
        force_eval = x * x + ux.value * ux.value;
    }

    return ux.value;
}

#endif /* __LIBMCS_LONG_DOUBLE_IS_64BITS */
