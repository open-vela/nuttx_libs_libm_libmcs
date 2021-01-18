/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/* __sinh(x)
 * Method :
 * mathematically sinh(x) if defined to be (exp(x)-exp(-x))/2
 *    1. Replace x by |x| (sinh(-x) = -sinh(x)).
 *    2.
 *                                               E + E/(E+1)
 *        0        <= x <= 22     :  sinh(x) := --------------, E=expm1(x)
 *                                       2
 *
 *        22       <= x <= lnovft :  sinh(x) := exp(x)/2
 *        lnovft   <= x <= ln2ovft:  sinh(x) := exp(x/2)/2 * exp(x/2)
 *        ln2ovft  <  x           :  sinh(x) := x*shuge (overflow)
 *
 * Special cases:
 *    sinh(x) is |x| if x is +INF, -INF, or NaN.
 *    only sinh(0)=0 is exact for finite x.
 */

/*
FUNCTION
        <<sinh>>, <<sinhf>>---hyperbolic sine

INDEX
    sinh
INDEX
    sinhf

SYNOPSIS
        #include <math.h>
        double sinh(double <[x]>);
        float  sinhf(float <[x]>);

DESCRIPTION
    <<sinh>> computes the hyperbolic sine of the argument <[x]>.
    Angles are specified in radians.   <<sinh>>(<[x]>) is defined as
    @ifnottex
    . (exp(<[x]>) - exp(-<[x]>))/2
    @end ifnottex
    @tex
    $${e^x - e^{-x}}\over 2$$
    @end tex

    <<sinhf>> is identical, save that it takes and returns <<float>> values.

RETURNS
    The hyperbolic sine of <[x]> is returned.

    When the correct result is too large to be representable (an
    overflow),  <<sinh>> returns <<HUGE_VAL>> with the
    appropriate sign, and sets the global value <<errno>> to
    <<ERANGE>>.

PORTABILITY
    <<sinh>> is ANSI C.
    <<sinhf>> is an extension.

QUICKREF
    sinh ansi pure
    sinhf - pure
*/

#include "../common/tools.h"

#ifndef _DOUBLE_IS_32BITS

static const double one = 1.0, shuge = 1.0e307;

double sinh(double x)
{
    double t, w, h;
    int32_t ix, jx;
    uint32_t lx;

    /* High word of |x|. */
    GET_HIGH_WORD(jx, x);
    ix = jx & 0x7fffffff;

    /* x is INF or NaN */
    if (ix >= 0x7ff00000) {
        return x + x;
    }

    h = 0.5;

    if (jx < 0) {
        h = -h;
    }

    /* |x| in [0,22], return sign(x)*0.5*(E+E/(E+1))) */
    if (ix < 0x40360000) {        /* |x|<22 */
        if (ix < 0x3e300000)       /* |x|<2**-28 */
            if (shuge + x > one) {
                return x;    /* sinh(tiny) = tiny with inexact */
            }

        t = expm1(fabs(x));

        if (ix < 0x3ff00000) {
            return h * (2.0 * t - t * t / (t + one));
        }

        return h * (t + t / (t + one));
    }

    /* |x| in [22, log(maxdouble)] return 0.5*exp(|x|) */
    if (ix < 0x40862E42) {
        return h * exp(fabs(x));
    }

    /* |x| in [log(maxdouble), overflowthresold] */
    GET_LOW_WORD(lx, x);

    if (ix < 0x408633CE || (ix == 0x408633ce && lx <= (uint32_t)0x8fb9f87d)) {
        w = exp(0.5 * fabs(x));
        t = h * w;
        return t * w;
    }

    /* |x| > overflowthresold, sinh(x) overflow */
    return x * shuge;
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double sinhl(long double x)
{
    return (long double) sinh((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
