/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/**
 *
 * This family of functions implements the hyperbolic arc tangent of :math:`x`.
 *
 * Synopsis
 * ========
 *
 * .. code-block:: c
 *
 *     #include <math.h>
 *     float atanhf(float x);
 *     double atanh(double x);
 *     long double atanhl(long double x);
 *
 * Description
 * ===========
 *
 * ``atanh`` computes the hyperbolic inverse tangent (*hyperbolic arc tangent*) of the input value.
 *
 * Mathematical Function
 * =====================
 * 
 * .. math::
 *
 *    atanh(x) \approx tanh^{-1}(x) = \frac{1}{2} ln \left( \frac{1+x}{1-x} \right)
 *
 * Returns
 * =======
 *
 * ``atanh`` returns the hyperbolic inverse tangent.
 *
 * Exceptions
 * ==========
 *
 * Raise ``invalid operation`` exception when the input value is not in the interval :math:`[-1, 1]`.
 *
 * Raise ``divide by zero`` exception when the input value is :math:`-1` or :math:`+1`.
 *
 * .. May raise ``underflow`` exception.
 *
 * Output map
 * ==========
 *
 * +---------------------+--------------+--------------+--------------+---------------------+--------------+--------------+---------------------+--------------+--------------+--------------+--------------+
 * | **x**               | :math:`-Inf` | :math:`<-1`  | :math:`-1`   | :math:`\in ]-1,-0[` | :math:`-0`   | :math:`+0`   | :math:`\in ]+0,+1[` | :math:`+1`   | :math:`>+1`  | :math:`+Inf` | :math:`NaN`  |
 * +=====================+==============+==============+==============+=====================+==============+==============+=====================+==============+==============+==============+==============+
 * | **atanh(x)**        | :math:`qNaN` | :math:`qNaN` | :math:`-Inf` | :math:`tanh^{-1} x` | :math:`x`                   | :math:`tanh^{-1} x` | :math:`+Inf` | :math:`qNaN` | :math:`qNaN` | :math:`qNaN` |
 * +---------------------+--------------+--------------+--------------+---------------------+--------------+--------------+---------------------+--------------+--------------+--------------+--------------+
 * 
 *///

/* __atanh(x)
 * Method :
 *    1.Reduced x to positive by atanh(-x) = -atanh(x)
 *    2.For x>=0.5
 *                  1              2x                          x
 *    atanh(x) = --- * log(1 + -------) = 0.5 * log1p(2 * --------)
 *                  2             1 - x                      1 - x
 *
 *     For x<0.5
 *    atanh(x) = 0.5*log1p(2x+2x*x/(1-x))
 *
 * Special cases:
 *    atanh(x) is NaN if |x| > 1 with signal;
 *    atanh(NaN) is that NaN with no signal;
 *    atanh(+-1) is +-INF with signal.
 *
 */

/*
FUNCTION
    <<atanh>>, <<atanhf>>---inverse hyperbolic tangent

INDEX
    atanh
INDEX
    atanhf

SYNOPSIS
    #include <math.h>
    double atanh(double <[x]>);
    float atanhf(float <[x]>);

DESCRIPTION
    <<atanh>> calculates the inverse hyperbolic tangent of <[x]>.

    <<atanhf>> is identical, other than taking and returning
    <<float>> values.

RETURNS
    <<atanh>> and <<atanhf>> return the calculated value.

    If
    @ifnottex
    |<[x]>|
    @end ifnottex
    @tex
    $|x|$
    @end tex
    is greater than 1, the global <<errno>> is set to <<EDOM>> and
    the result is a NaN.  A <<DOMAIN error>> is reported.

    If
    @ifnottex
    |<[x]>|
    @end ifnottex
    @tex
    $|x|$
    @end tex
    is 1, the global <<errno>> is set to <<EDOM>>; and the result is
    infinity with the same sign as <<x>>.  A <<SING error>> is reported.

PORTABILITY
    Neither <<atanh>> nor <<atanhf>> are ANSI C.

QUICKREF
    atanh - pure
    atanhf - pure

*/

#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

static const double one = 1.0;

double atanh(double x)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    double t;
    int32_t hx, ix;
    uint32_t lx;
    EXTRACT_WORDS(hx, lx, x);
    ix = hx & 0x7fffffff;

    if ((ix | ((lx | (-lx)) >> 31)) > 0x3ff00000) { /* |x|>1 */
        if (isnan(x)) {
            return x + x;
        } else {
            return __raise_invalid();
        }
    }

    if (ix == 0x3ff00000) {
        return __raise_div_by_zero(x);
    }

    if (ix < 0x3e300000) {     /* x<2**-28 */
        if (x == 0.0) {        /* return x inexact except 0 */
            return x;
        } else {
            return __raise_inexact(x);
        }
    }

    SET_HIGH_WORD(x, ix);

    if (ix < 0x3fe00000) {     /* x < 0.5 */
        t = x + x;
        t = 0.5 * log1p(t + t * x / (one - x));
    } else {
        t = 0.5 * log1p((x + x) / (one - x));
    }

    if (hx >= 0) {
        return t;
    } else {
        return -t;
    }
}
#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double atanhl(long double x)
{
    return (long double) atanh((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
