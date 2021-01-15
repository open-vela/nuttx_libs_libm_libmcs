/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include "../common/tools.h"

static const float
one    = 1.0,
ln2    = 6.9314718246e-01;  /* 0x3f317218 */

float acoshf(float x)
{
    float t;
    int32_t hx;
    GET_FLOAT_WORD(hx, x);

    if (hx < 0x3f800000) {     /* x < 1 */
        return (x - x) / (x - x);
    } else if (hx >= 0x4d800000) {  /* x > 2**28 */
        if (!FLT_UWORD_IS_FINITE(hx)) {   /* x is inf of NaN */
            return x + x;
        } else {
            return __logf(x) + ln2;    /* acosh(huge)=log(2x) */
        }
    } else if (hx == 0x3f800000) {
        return 0.0;            /* acosh(1) = 0 */
    } else if (hx > 0x40000000) {    /* 2**28 > x > 2 */
        t = x * x;
        return __logf((float)2.0 * x - one / (x + __sqrtf(t - one)));
    } else {            /* 1<x<2 */
        t = x - one;
        return log1pf(t + __sqrtf((float)2.0 * t + t * t));
    }
}

#ifdef _DOUBLE_IS_32BITS

double acosh(double x)
{
    return (double) acoshf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
