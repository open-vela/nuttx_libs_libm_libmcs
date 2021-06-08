/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>
#include "../common/tools.h"
#include "internal/errorfunctionf.h"

static const float
erx  =  8.4506291151e-01f, /* 0x3f58560b */
efx  =  1.2837916613e-01f, /* 0x3e0375d4 */
efx8 =  1.0270333290e+00f; /* 0x3f8375d4 */

float erff(float x)
{
    int32_t hx, ix;
    float R, S, P, Q, s, z, r;
    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;

    if (!FLT_UWORD_IS_FINITE(ix)) {
        if (isnan(x)) {         /* erf(nan) = nan */
            return x + x;
        } else if (hx > 0) {    /* erf(+inf) = +1 */
            return 1.0f;
        } else {                /* erf(-inf) = -1 */
            return -1.0f;
        }
    }

    if (ix < 0x3f580000) {       /* |x|<0.84375 */
        if (ix < 0x31800000) {    /* |x|<2**-28 */
            if (ix < 0x04000000)
                /*avoid underflow */
            {
                return 0.125f * (8.0f * x + efx8 * x);
            }

            return x + efx * x;
        }

        return x + x * __erff_y(x);
    }

    if (ix < 0x3fa00000) {       /* 0.84375 <= |x| < 1.25 */
        s = fabsf(x) - one;
        P = __erff_P(s);
        Q = __erff_Q(s);

        if (hx >= 0) {
            return erx + P / Q;
        } else {
            return -erx - P / Q;
        }
    }

    if (ix >= 0x40c00000) {        /* inf>|x|>=6 */
        if (hx >= 0) {
            return __raise_inexactf(one);
        } else {
            return -__raise_inexactf(one);
        }
    }

    x = fabsf(x);
    s = one / (x * x);

    if (ix < 0x4036DB6E) {  /* |x| < 1/0.35 */
        R = __erff_Ra(s);
        S = __erff_Sa(s);
    } else {    /* |x| >= 1/0.35 */
        R = __erff_Rb(s);
        S = __erff_Sb(s);
    }

    GET_FLOAT_WORD(ix, x);
    SET_FLOAT_WORD(z, ix & 0xfffff000U);
    r  =  expf(-z * z - 0.5625f) * expf((z - x) * (z + x) + R / S);

    if (hx >= 0) {
        return one - r / x;
    } else {
        return  r / x - one;
    }
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double erf(double x)
{
    return (double) erff((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
