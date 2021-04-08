/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*
FUNCTION
        <<sin>>, <<sinf>>, <<cos>>, <<cosf>>---sine or cosine
INDEX
sin
INDEX
sinf
INDEX
cos
INDEX
cosf
SYNOPSIS
        #include <math.h>
        double sin(double <[x]>);
        float  sinf(float <[x]>);
        double cos(double <[x]>);
        float cosf(float <[x]>);

DESCRIPTION
    <<sin>> and <<cos>> compute (respectively) the sine and cosine
    of the argument <[x]>.  Angles are specified in radians.

    <<sinf>> and <<cosf>> are identical, save that they take and
    return <<float>> values.


RETURNS
    The sine or cosine of <[x]> is returned.

PORTABILITY
    <<sin>> and <<cos>> are ANSI C.
    <<sinf>> and <<cosf>> are extensions.

QUICKREF
    sin ansi pure
    sinf - pure
*/

/* sin(x)
 * Return sine function of x.
 *
 * internal function:
 *    __sin        ... sine function on [-pi/4,pi/4]
 *    __cos        ... cose function on [-pi/4,pi/4]
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
 *          0          S           C            T
 *          1          C          -S           -1/T
 *          2         -S          -C            T
 *          3         -C           S           -1/T
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

double sin(double x)
{
    double y[2], z = 0.0;
    int32_t n, ix;

    /* High word of x. */
    GET_HIGH_WORD(ix, x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;

    if (ix <= 0x3fe921fb) {
        if(ix < 0x3e500000) {      /* |x| < 2**-26 */
           if(((int)x) == 0) {
               return x;           /* generate inexact */
           }
        }
        
        return __sin(x, z, 0);
    }

    /* sin(Inf or NaN) is NaN */
    else if (ix >= 0x7ff00000) {
        return x - x;
    }

    /* argument reduction needed */
    else {
        n = __rem_pio2(x, y);

        switch (n & 3) {
        case 0:
            return  __sin(y[0], y[1], 1);

        case 1:
            return  __cos(y[0], y[1]);

        case 2:
            return -__sin(y[0], y[1], 1);

        default:
            return -__cos(y[0], y[1]);
        }
    }
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double sinl(long double x)
{
    return (long double) sin((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
