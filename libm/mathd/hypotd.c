/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/* __hypot(x,y)
 *
 * Method :
 *    If (assume round-to-nearest) z=x*x+y*y
 *    has error less than sqrt(2)/2 ulp, than
 *    sqrt(z) has error less than 1 ulp (exercise).
 *
 *    So, compute sqrt(x*x+y*y) with some care as
 *    follows to get the error below 1 ulp:
 *
 *    Assume x>y>0;
 *    (if possible, set rounding to round-to-nearest)
 *    1. if x > 2y  use
 *        x1*x1+(y*y+(x2*(x+x1))) for x*x+y*y
 *    where x1 = x with lower 32 bits cleared, x2 = x-x1; else
 *    2. if x <= 2y use
 *        t1*y1+((x-y)*(x-y)+(t1*y2+t2*y))
 *    where t1 = 2x with lower 32 bits cleared, t2 = 2x-t1,
 *    y1= y with lower 32 bits chopped, y2 = y-y1.
 *
 *    NOTE: scaling may be necessary if some argument is too
 *          large or too tiny
 *
 * Special cases:
 *    hypot(x,y) is INF if x or y is +INF or -INF; else
 *    hypot(x,y) is NAN if x or y is NAN.
 *
 * Accuracy:
 *     hypot(x,y) returns sqrt(x^2+y^2) with error less
 *     than 1 ulps (units in the last place)
 */

/*
FUNCTION
    <<hypot>>, <<hypotf>>---distance from origin
INDEX
    hypot
INDEX
    hypotf

SYNOPSIS
    #include <math.h>
    double hypot(double <[x]>, double <[y]>);
    float hypotf(float <[x]>, float <[y]>);

DESCRIPTION
    <<hypot>> calculates the Euclidean distance
    @tex
    $\sqrt{x^2+y^2}$
    @end tex
    @ifnottex
    <<sqrt(<[x]>*<[x]> + <[y]>*<[y]>)>>
    @end ifnottex
    between the origin (0,0) and a point represented by the
    Cartesian coordinates (<[x]>,<[y]>).  <<hypotf>> differs only
    in the type of its arguments and result.

RETURNS
    Normally, the distance value is returned.  On overflow,
    <<hypot>> returns <<HUGE_VAL>> and sets <<errno>> to
    <<ERANGE>>.

PORTABILITY
    <<hypot>> and <<hypotf>> are not ANSI C.  */

#include "../common/tools.h"

#ifndef _DOUBLE_IS_32BITS

double hypot(double x, double y)
{
    double a = x, b = y, t1, t2, y1, y2, w;
    int32_t j, k, ha, hb;

    GET_HIGH_WORD(ha, x);
    ha &= 0x7fffffff;
    GET_HIGH_WORD(hb, y);
    hb &= 0x7fffffff;

    if (hb > ha) {
        a = y;
        b = x;
        j = ha;
        ha = hb;
        hb = j;
    } else {
        a = x;
        b = y;
    }

    SET_HIGH_WORD(a, ha);         /* a <- |a| */
    SET_HIGH_WORD(b, hb);         /* b <- |b| */

    if ((ha - hb) > 0x3c00000) {
        return a + b;             /* x/y > 2**60 */
    }

    k = 0;

    if (ha > 0x5f300000) {        /* a>2**500 */
        if (ha >= 0x7ff00000) {   /* Inf or NaN */
            uint32_t low;
            w = a + b;            /* for sNaN */
            GET_LOW_WORD(low, a);

            if (((ha & 0xfffff) | low) == 0) {
                w = a;
            }

            GET_LOW_WORD(low, b);

            if (((hb ^ 0x7ff00000) | low) == 0) {
                w = b;
            }

            return w;
        }

        /* scale a and b by 2**-600 */
        ha -= 0x25800000;
        hb -= 0x25800000;
        k += 600;
        SET_HIGH_WORD(a, ha);
        SET_HIGH_WORD(b, hb);
    }

    if (hb < 0x20b00000) {        /* b < 2**-500 */
        if (hb <= 0x000fffff) {   /* subnormal b or 0 */
            uint32_t low;
            GET_LOW_WORD(low, b);

            if ((hb | low) == 0) {
                return a;
            }

            t1 = 0;
            SET_HIGH_WORD(t1, 0x7fd00000);   /* t1=2^1022 */
            b *= t1;
            a *= t1;
            k -= 1022;
        } else {        /* scale a and b by 2^600 */
            ha += 0x25800000;     /* a *= 2^600 */
            hb += 0x25800000;     /* b *= 2^600 */
            k -= 600;
            SET_HIGH_WORD(a, ha);
            SET_HIGH_WORD(b, hb);
        }
    }

    /* medium size a and b */
    w = a - b;

    if (w > b) {
        t1 = 0;
        SET_HIGH_WORD(t1, ha);
        t2 = a - t1;
        w  = sqrt(t1 * t1 - (b * (-b) - t2 * (a + t1)));
    } else {
        a  = a + a;
        y1 = 0;
        SET_HIGH_WORD(y1, hb);
        y2 = b - y1;
        t1 = 0;
        SET_HIGH_WORD(t1, ha + 0x00100000);
        t2 = a - t1;
        w  = sqrt(t1 * y1 - (w * (-w) - (t1 * y2 + t2 * b)));
    }

    if (k != 0) {
        uint32_t high;
        t1 = 1.0;
        GET_HIGH_WORD(high, t1);
        SET_HIGH_WORD(t1, high + (k << 20));
        return t1 * w;
    } else {
        return w;
    }
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double hypotl(long double x, long double y)
{
    return (long double) hypot((double) x, (double) y);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
