/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>
#include "../common/tools.h"

static const float one = 1.0, tiny = 1.0e-30;

float sqrtf(float x)
{
    float z;
    uint32_t r, hx;
    int32_t ix, s, q, m, t, i;

    GET_FLOAT_WORD(ix, x);
    hx = ix & 0x7fffffff;

    /* take care of Inf and NaN */
    if (!FLT_UWORD_IS_FINITE(hx)) {
        return x * x + x;            /* sqrt(NaN)=NaN, sqrt(+inf)=+inf, sqrt(-inf)=sNaN */
    }

    /* take care of zero and -ves */
    if (FLT_UWORD_IS_ZERO(hx)) {
        return x;    /* sqrt(+-0) = +-0 */
    }

    if (ix < 0) {
        return (x - x) / (x - x);    /* sqrt(-ve) = sNaN */
    }

    /* normalize x */
    m = (ix >> 23);

    if (FLT_UWORD_IS_SUBNORMAL(hx)) {       /* subnormal x */
        for (i = 0; (ix & 0x00800000L) == 0; i++) {
            ix <<= 1;
        }

        m -= i - 1;
    }

    m -= 127;    /* unbias exponent */
    ix = (ix & 0x007fffffL) | 0x00800000L;

    if (m & 1) { /* odd m, double x to make it even */
        ix += ix;
    }

    m >>= 1;    /* m = [m/2] */

    /* generate sqrt(x) bit by bit */
    ix += ix;
    q = s = 0;        /* q = sqrt(x) */
    r = 0x01000000L;        /* r = moving bit from right to left */

    while (r != 0) {
        t = s + r;

        if (t <= ix) {
            s    = t + r;
            ix  -= t;
            q   += r;
        }

        ix += ix;
        r >>= 1;
    }

    /* use floating add to find out rounding direction */
    if (ix != 0) {
        z = one - tiny; /* trigger inexact flag */

        if (z >= one) {
            z = one + tiny;

            if (z > one) {
                q += 2;
            } else {
                q += (q & 1);
            }
        }
    }

    ix = (q >> 1) + 0x3f000000L;
    ix += (m << 23);
    SET_FLOAT_WORD(z, ix);
    return z;
}

#ifdef _DOUBLE_IS_32BITS

double sqrt(double x)
{
    return (double) sqrtf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
