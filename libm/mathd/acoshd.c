/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/* __ieee754_acosh(x)
 * Method :
 *    Based on
 *        acosh(x) = log [ x + sqrt(x*x-1) ]
 *    we have
 *        acosh(x) := log(x)+ln2,    if x is large; else
 *        acosh(x) := log(2x-1/(sqrt(x*x-1)+x)) if x>2; else
 *        acosh(x) := log1p(t+sqrt(2.0*t+t*t)); where t=x-1.
 *
 * Special cases:
 *    acosh(x) is NaN with signal if x<1.
 *    acosh(NaN) is NaN without signal.
 */

/*
FUNCTION
<<acosh>>, <<acoshf>>---inverse hyperbolic cosine

INDEX
acosh
INDEX
acoshf

SYNOPSIS
    #include <math.h>
    double acosh(double <[x]>);
    float acoshf(float <[x]>);

DESCRIPTION
<<acosh>> calculates the inverse hyperbolic cosine of <[x]>.
<<acosh>> is defined as
@ifnottex
. log(<[x]> + sqrt(<[x]>*<[x]>-1))
@end ifnottex
@tex
$$ln\Bigl(x + \sqrt{x^2-1}\Bigr)$$
@end tex

<[x]> must be a number greater than or equal to 1.

<<acoshf>> is identical, other than taking and returning floats.

RETURNS
<<acosh>> and <<acoshf>> return the calculated value.  If <[x]>
less than 1, the return value is NaN and <<errno>> is set to <<EDOM>>.

PORTABILITY
Neither <<acosh>> nor <<acoshf>> are ANSI C.  They are not recommended
for portable programs.


QUICKREF
 ansi posix rentrant
 acos     n,n,m
 acosf   n,n,m

MATHREF
 acosh, NAN,   arg,DOMAIN,EDOM
 acosh, < 1.0, NAN,DOMAIN,EDOM
 acosh, >=1.0, acosh(arg),,,

MATHREF
 acoshf, NAN,   arg,DOMAIN,EDOM
 acoshf, < 1.0, NAN,DOMAIN,EDOM
 acoshf, >=1.0, acosh(arg),,,

*/

#include "../common/tools.h"

#ifndef _DOUBLE_IS_32BITS

static const double
one    = 1.0,
ln2    = 6.93147180559945286227e-01;  /* 0x3FE62E42, 0xFEFA39EF */

double acosh(double x)
{
    double t;
    int32_t hx;
    uint32_t lx;
    EXTRACT_WORDS(hx, lx, x);

    if (hx < 0x3ff00000) {     /* x < 1 */
        return (x - x) / (x - x);
    } else if (hx >= 0x41b00000) {  /* x > 2**28 */
        if (hx >= 0x7ff00000) {  /* x is inf of NaN */
            return x + x;
        } else {
            return __ieee754_log(x) + ln2;    /* acosh(huge)=log(2x) */
        }
    } else if (((hx - 0x3ff00000) | lx) == 0) {
        return 0.0;            /* acosh(1) = 0 */
    } else if (hx > 0x40000000) {    /* 2**28 > x > 2 */
        t = x * x;
        return __ieee754_log(2.0 * x - one / (x + __ieee754_sqrt(t - one)));
    } else {            /* 1<x<2 */
        t = x - one;
        return log1p(t + __ieee754_sqrt(2.0 * t + t * t));
    }
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double acoshl(long double x)
{
    return (long double) acosh((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
