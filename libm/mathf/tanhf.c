// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

#include "fdlibm.h"

static const float one = 1.0, two = 2.0, tiny = 1.0e-30;

float tanhf(float x)
{
    float t, z;
    __int32_t jx, ix;

    GET_FLOAT_WORD(jx, x);
    ix = jx & 0x7fffffff;

    /* x is INF or NaN */
    if (!FLT_UWORD_IS_FINITE(ix)) {
        if (jx >= 0) {
            return one / x + one;    /* tanh(+-inf)=+-1 */
        } else {
            return one / x - one;    /* tanh(NaN) = NaN */
        }
    }

    /* |x| < 22 */
    if (ix < 0x41b00000) {        /* |x|<22 */
        if (ix < 0x24000000) {     /* |x|<2**-55 */
            return x * (one + x);    /* tanh(small) = small */
        }

        if (ix >= 0x3f800000) {  /* |x|>=1  */
            t = expm1f(two * fabsf(x));
            z = one - two / (t + two);
        } else {
            t = expm1f(-two * fabsf(x));
            z = -t / (t + two);
        }

    /* |x| > 22, return +-1 */
    } else {
        z = one - tiny;        /* raised inexact flag */
    }

    return (jx >= 0) ? z : -z;
}

#ifdef _DOUBLE_IS_32BITS

double tanh(double x)
{
    return (double) tanhf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
