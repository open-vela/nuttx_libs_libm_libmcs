/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>
#include "../common/tools.h"
#include "internal/errorfunctionf.h"

static const float
tiny =  1e-30,
one  =  1.0000000000e+00, /* 0x3F800000 */
erx  =  8.4506291151e-01, /* 0x3f58560b */
efx  =  1.2837916613e-01, /* 0x3e0375d4 */
efx8 =  1.0270333290e+00; /* 0x3f8375d4 */

float erff(float x)
{
    int32_t hx, ix, i;
    float R, S, P, Q, s, z, r;
    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;

    if (!FLT_UWORD_IS_FINITE(ix)) {       /* erf(nan)=nan */
        i = ((uint32_t)hx >> 31) << 1;
        return (float)(1 - i) + one / x; /* erf(+-inf)=+-1 */
    }

    if (ix < 0x3f580000) {       /* |x|<0.84375 */
        if (ix < 0x31800000) {    /* |x|<2**-28 */
            if (ix < 0x04000000)
                /*avoid underflow */
            {
                return (float)0.125 * ((float)8.0 * x + efx8 * x);
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
            return one - tiny;
        } else {
            return tiny - one;
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
    SET_FLOAT_WORD(z, ix & 0xfffff000);
    r  =  expf(-z * z - (float)0.5625) * expf((z - x) * (z + x) + R / S);

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
