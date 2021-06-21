/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*

FUNCTION
        <<tanh>>, <<tanhf>>---hyperbolic tangent

INDEX
tanh
INDEX
tanhf

SYNOPSIS
        #include <math.h>
        double tanh(double <[x]>);
        float tanhf(float <[x]>);

DESCRIPTION

<<tanh>> computes the hyperbolic tangent of
the argument <[x]>.  Angles are specified in radians.

<<tanh(<[x]>)>> is defined as
. sinh(<[x]>)/cosh(<[x]>)

<<tanhf>> is identical, save that it takes and returns <<float>> values.

RETURNS
The hyperbolic tangent of <[x]> is returned.

PORTABILITY
<<tanh>> is ANSI C.  <<tanhf>> is an extension.

*/

/* Tanh(x)
 * Return the Hyperbolic Tangent of x
 *
 * Method :
 *                       x    -x
 *                      e  - e
 *    0. tanh(x) is defined to be -----------
 *                       x    -x
 *                      e  + e
 *    1. reduce x to non-negative by tanh(-x) = -tanh(x).
 *    2.  0      <= x <= 2**-55 : tanh(x) := x*(one+x)
 *                            -t
 *        2**-55 <  x <=  1     : tanh(x) := -----; t = expm1(-2x)
 *                           t + 2
 *                             2
 *        1      <= x <=  22.0  : tanh(x) := 1-  ----- ; t=expm1(2x)
 *                           t + 2
 *        22.0   <  x <= INF    : tanh(x) := 1.
 *
 * Special cases:
 *    tanh(NaN) is NaN;
 *    only tanh(0)=0 is exact for finite argument.
 */

#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

static const double one = 1.0, two = 2.0;

double tanh(double x)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    double t, z;
    int32_t jx, ix;

    /* High word of |x|. */
    GET_HIGH_WORD(jx, x);
    ix = jx & 0x7fffffff;

    /* x is INF or NaN */
    if (ix >= 0x7ff00000) {
        if (isnan(x)) {             /* tanh(NaN) = NaN */
            return x + x;
        } else if (jx >= 0) {
            return one;             /* tanh(+inf)=+1 */
        } else {
            return -one;            /* tanh(-inf)=-1 */
        }
    }

    /* |x| < 22 */
    if (ix < 0x40360000) {          /* |x|<22 */
        if (ix < 0x3c800000) {      /* |x|<2**-55 */
            if (x == 0.0) {         /* return x inexact except 0 */
                return x;
            } else {
                return __raise_inexact(x);
            }
        }

        if (ix >= 0x3ff00000) {     /* |x|>=1  */
            t = expm1(two * fabs(x));
            z = one - two / (t + two);
        } else {
            t = expm1(-two * fabs(x));
            z = -t / (t + two);
        }

    /* |x| > 22, return +-1 */
    } else {
        z = __raise_inexact(one);               /* raised inexact flag */
    }

    return (jx >= 0) ? z : -z;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double tanhl(long double x)
{
    return (long double) tanh((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
