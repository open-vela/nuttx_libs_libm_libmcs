/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/* cos(x)
 * Return cosine function of x.
 *
 * internal function:
 *    __sin        ... sine function on [-pi/4,pi/4]
 *    __cos        ... cosine function on [-pi/4,pi/4]
 *    __rem_pio2    ... argument reduction routine
 *
 * Method.
 *      Let S,C and T denote the sin, cos and tan respectively on
 *    [-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2
 *    in [-pi/4 , +pi/4], and let n = k mod 4.
 *    We have
 *
 *          n        sin(x)      cos(x)        tan(x)
 *     ----------------------------------------------------------
 *        0           S       C         T
 *        1           C      -S        -1/T
 *        2          -S      -C         T
 *        3          -C       S        -1/T
 *     ----------------------------------------------------------
 *
 * Special cases:
 *      Let trig be any of sin, cos, or tan.
 *      trig(+-INF)  is NaN, with signals;
 *      trig(NaN)    is that NaN;
 *
 * Accuracy:
 *    TRIG(x) returns trig(x) nearly rounded
 */

#include <math.h>
#include "../common/tools.h"
#include "internal/trigd.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double cos(double x)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    double y[2], z = 0.0;
    int32_t n, ix;

    /* High word of x. */
    GET_HIGH_WORD(ix, x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;
    
    if(ix <= 0x3fe921fb) {
        if(ix < 0x3e46a09e) {        /* if x < 2**-27 * sqrt(2) */
            if (x == 0.0) {          /* return 1 inexact except 0 */
                return 1.0;
            } else {
                return __raise_inexactf(1.0);
            }
        }
        
        return __cos(x, z);
    }

    /* cos(Inf or NaN) is NaN */
    else if (ix >= 0x7ff00000) {
        if (isnan(x)) {
            return x + x;
        } else {
            return __raise_invalid();
        }
    }

    /* argument reduction needed */
    else {
        n = __rem_pio2(x, y);

        switch (n & 3) {
        case 0:
            return  __cos(y[0], y[1]);

        case 1:
            return -__sin(y[0], y[1], 1);

        case 2:
            return -__cos(y[0], y[1]);

        default:
            return  __sin(y[0], y[1], 1);
        }
    }
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double cosl(long double x)
{
    return (long double) cos((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
