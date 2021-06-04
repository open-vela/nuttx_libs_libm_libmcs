/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/* sqrt(x)
 * Return correctly rounded sqrt.
 *           ------------------------------------------
 *         |  Use the hardware sqrt if you have one |
 *           ------------------------------------------
 * Method:
 *   Bit by bit method using integer arithmetic. (Slow, but portable)
 *   1. Normalization
 *    Scale x to y in [1,4) with even powers of 2:
 *    find an integer k such that  1 <= (y=x*2^(2k)) < 4, then
 *        sqrt(x) = 2^k * sqrt(y)
 *   2. Bit by bit computation
 *    Let q  = sqrt(y) truncated to i bit after binary point (q = 1),
 *         i                             0
 *                                     i+1         2
 *        s  = 2*q , and    y  =  2   * ( y - q  ).        (1)
 *         i      i            i                 i
 *
 *    To compute q    from q , one checks whether
 *            i+1       i
 *
 *                  -(i+1) 2
 *            (q + 2      ) <= y.            (2)
 *                   i
 *                                  -(i+1)
 *    If (2) is false, then q   = q ; otherwise q   = q  + 2      .
 *                    i+1   i             i+1   i
 *
 *    With some algebric manipulation, it is not difficult to see
 *    that (2) is equivalent to
 *                             -(i+1)
 *            s  +  2       <= y            (3)
 *             i                i
 *
 *    The advantage of (3) is that s  and y  can be computed by
 *                      i      i
 *    the following recurrence formula:
 *        if (3) is false
 *
 *        s     =  s  ,    y    = y   ;            (4)
 *         i+1      i         i+1    i
 *
 *        otherwise,
 *                         -i                     -(i+1)
 *        s      =  s  + 2  ,  y    = y  -  s  - 2          (5)
 *           i+1      i          i+1    i     i
 *
 *    One may easily use induction to prove (4) and (5).
 *    Note. Since the left hand side of (3) contain only i+2 bits,
 *          it does not necessary to do a full (53-bit) comparison
 *          in (3).
 *   3. Final rounding
 *    After generating the 53 bits result, we compute one more bit.
 *    Together with the remainder, we can decide whether the
 *    result is exact, bigger than 1/2ulp, or less than 1/2ulp
 *    (it will never equal to 1/2ulp).
 *    The rounding mode can be detected by checking whether
 *    huge + tiny is equal to huge, and whether huge - tiny is
 *    equal to huge for some floating point number "huge" and "tiny".
 *
 * Special cases:
 *    sqrt(+-0) = +-0     ... exact
 *    sqrt(inf) = inf
 *    sqrt(-ve) = NaN     ... with invalid signal
 *    sqrt(NaN) = NaN     ... with invalid signal for signaling NaN
 *
 * Other methods : see the appended file at the end of the program below.
 *---------------
 */

/*
FUNCTION
    <<sqrt>>, <<sqrtf>>---positive square root

INDEX
    sqrt
INDEX
    sqrtf

SYNOPSIS
    #include <math.h>
    double sqrt(double <[x]>);
    float  sqrtf(float <[x]>);

DESCRIPTION
    <<sqrt>> computes the positive square root of the argument.

RETURNS
    On success, the square root is returned. If <[x]> is real and
    positive, then the result is positive.  If <[x]> is real and
    negative, the global value <<errno>> is set to <<EDOM>> (domain error).


PORTABILITY
    <<sqrt>> is ANSI C.  <<sqrtf>> is an extension.
*/

#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

static const double one = 1.0, tiny = 1.0e-300;

double sqrt(double x)
{
    double z;
    int32_t sign = 0x80000000U;
    uint32_t r, t1, s1, ix1, q1;
    int32_t ix0, s0, q, m, t, i;

    EXTRACT_WORDS(ix0, ix1, x);

    /* take care of Inf and NaN */
    if ((ix0 & 0x7ff00000) == 0x7ff00000) {
        if (isnan(x)) {         /* sqrt(NaN)=NaN */
            return x + x;
        } else if (ix0 > 0) {   /* sqrt(+inf)=+inf */
            return x;
        } else {                /* sqrt(-inf)=sNaN */
            return __raise_invalid();
        }
    }

    /* take care of zero and negative values */
    if (ix0 <= 0) {
        if (((ix0 & (~sign)) | ix1) == 0) {
            return x;    /* sqrt(+-0) = +-0 */
        } else if (ix0 < 0) {
            return __raise_invalid();    /* sqrt(-ve) = sNaN */
        }
    }

    /* normalize x */
    m = (ix0 >> 20);

    if (m == 0) {             /* subnormal x */
        while (ix0 == 0) {
            m -= 21;
            ix0 |= (ix1 >> 11);
            ix1 <<= 21;
        }

        for (i = 0; (ix0 & 0x00100000) == 0; i++) {
            ix0 <<= 1;
        }

        m -= i - 1;
        ix0 |= (ix1 >> (32 - i));
        ix1 <<= i;
    }

    m -= 1023;    /* unbias exponent */
    ix0 = (ix0 & 0x000fffff) | 0x00100000;

    if (m & 1) { /* odd m, double x to make it even */
        ix0 += ix0 + (int32_t)((ix1 & (uint32_t)sign) >> 31U);
        ix1 += ix1;
    }

    m >>= 1;    /* m = [m/2] */

    /* generate sqrt(x) bit by bit */
    ix0 += ix0 + (int32_t)((ix1 & (uint32_t)sign) >> 31U);
    ix1 += ix1;
    q = q1 = s0 = s1 = 0;    /* [q,q1] = sqrt(x) */
    r = 0x00200000;        /* r = moving bit from right to left */

    while (r != 0) {
        t = s0 + r;

        if (t <= ix0) {
            s0   = t + r;
            ix0 -= t;
            q   += r;
        }

        ix0 += ix0 + (int32_t)((ix1 & (uint32_t)sign) >> 31U);
        ix1 += ix1;
        r >>= 1;
    }

    r = sign;

    while (r != 0) {
        t1 = s1 + r;
        t  = s0;

        if ((t < ix0) || ((t == ix0) && (t1 <= ix1))) {
            s1  = t1 + r;

            if ((((int32_t)t1 & sign) == sign) && ((int32_t)s1 & sign) == 0) {
                s0 += 1;
            }

            ix0 -= t;

            if (ix1 < t1) {
                ix0 -= 1;
            }

            ix1 -= t1;
            q1  += r;
        }

        ix0 += ix0 + (int32_t)((ix1 & (uint32_t)sign) >> 31U);
        ix1 += ix1;
        r >>= 1;
    }

    /* use floating add to find out rounding direction */
    if ((ix0 | ix1) != 0) {
        z = one - tiny; /* trigger inexact flag */

        if (z >= one) {
            z = one + tiny;

            if (q1 == (uint32_t)0xffffffffU) {
                q1 = 0;
                q += 1;
            } else if (z > one) {
                if (q1 == (uint32_t)0xfffffffeU) {
                    q += 1;
                }

                q1 += 2;
            } else {
                q1 += (q1 & 1);
            }
        }
    }

    ix0 = (q >> 1) + 0x3fe00000;
    ix1 =  q1 >> 1;

    if ((q & 1) == 1) {
        ix1 |= sign;
    }

    ix0 += (m << 20);
    INSERT_WORDS(z, ix0, ix1);
    return z;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double sqrtl(long double x)
{
    return (long double) sqrt((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
