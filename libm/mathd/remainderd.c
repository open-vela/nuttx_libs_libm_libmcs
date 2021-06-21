/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/* __remainder(x,p)
 * Return :
 *     returns  x REM p  =  x - [x/p]*p as if in infinite
 *     precise arithmetic, where [x/p] is the (infinite bit)
 *    integer nearest x/p (in half way case choose the even one).
 * Method :
 *    Based on fmod() return x-[x/p]chopped*p exactlp.
 */

/*
FUNCTION
<<remainder>>, <<remainderf>>---round and  remainder
INDEX
    remainder
INDEX
    remainderf

SYNOPSIS
    #include <math.h>
    double remainder(double <[x]>, double <[y]>);
    float remainderf(float <[x]>, float <[y]>);

DESCRIPTION
<<remainder>> and <<remainderf>> find the remainder of
<[x]>/<[y]>; this value is in the range -<[y]>/2 .. +<[y]>/2.

RETURNS
<<remainder>> returns the integer result as a double.

PORTABILITY
<<remainder>> is a System V release 4.
<<remainderf>> is an extension.

*/

#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

static const double zero = 0.0;

double remainder(double x, double p)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
    p *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    int32_t hx, hp;
    uint32_t sx, lx, lp;
    double p_half;

    EXTRACT_WORDS(hx, lx, x);
    EXTRACT_WORDS(hp, lp, p);
    sx = hx & 0x80000000U;
    hp &= 0x7fffffff;
    hx &= 0x7fffffff;

    /* purge off exception values */
    if ((hx >= 0x7ff00000) || (hp >= 0x7ff00000)) { /* x or p not finite */
        if (isnan(x) || isnan(p)) {                 /* x or p is NaN */
            return x + p;
        } else if (hx == 0x7ff00000 && lx == 0) {   /* x is infinite */
            return __raise_invalid();
        } else {
            /* No action required */
        }
    } else if ((hp | lp) == 0) {                    /* p = 0 */
        return __raise_invalid();
    } else {
        /* No action required */
    }

    if (hp <= 0x7fdfffff) {
        x = fmod(x, p + p);                         /* now x < 2p */
    }

    if (((hx - hp) | (lx - lp)) == 0) {             /* x equals p */
        return zero * x;
    }

    x  = fabs(x);
    p  = fabs(p);

    if (hp < 0x00200000) {
        if (x + x > p) {
            x -= p;

            if (x + x >= p) {
                x -= p;
            }
        }
    } else {
        p_half = 0.5 * p;

        if (x > p_half) {
            x -= p;

            if (x >= p_half) {
                x -= p;
            }
        }
    }

    GET_HIGH_WORD(hx, x);
    SET_HIGH_WORD(x, hx ^ sx);
    return x;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double remainderl(long double x, long double y)
{
    return (long double) remainder((double) x, (double) y);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
