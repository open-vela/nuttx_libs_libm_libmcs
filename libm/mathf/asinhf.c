/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>
#include "../common/tools.h"

static const float
one =   1.0000000000e+00, /* 0x3F800000 */
ln2 =   6.9314718246e-01; /* 0x3f317218 */

float asinhf(float x)
{
    float t, w;
    int32_t hx, ix;
    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;

    if (!FLT_UWORD_IS_FINITE(ix)) {
        return x + x;    /* x is inf or NaN */
    }

    if (ix < 0x31800000) {  /* |x|<2**-28 */
        return __raise_inexactf(x);    /* return x inexact except 0 */
    }

    if (ix > 0x4d800000) { /* |x| > 2**28 */
        w = logf(fabsf(x)) + ln2;
    } else if (ix > 0x40000000) {  /* 2**28 > |x| > 2.0 */
        t = fabsf(x);
        w = logf((float)2.0 * t + one / (sqrtf(x * x + one) + t));
    } else {        /* 2.0 > |x| > 2**-28 */
        t = x * x;
        w = log1pf(fabsf(x) + t / (one + sqrtf(one + t)));
    }

    if (hx > 0) {
        return w;
    } else {
        return -w;
    }
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double asinh(double x)
{
    return (double) asinhf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
