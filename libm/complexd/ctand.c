/* SPDX-License-Identifier: NetBSD */

/*
FUNCTION
        <<ctan>>, <<ctanf>>---complex tangent

INDEX
        ctan
INDEX
        ctanf

SYNOPSIS
       #include <complex.h>
       double complex ctan(double complex <[z]>);
       float complex ctanf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex tangent of <[z]>.

        <<ctanf>> is identical to <<ctan>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        These functions return the complex tangent value.

PORTABILITY
        <<ctan>> and <<ctanf>> are ISO C99

QUICKREF
        <<ctan>> and <<ctanf>> are ISO C99

*/


#include <complex.h>
#include <math.h>
#include "internal/ctrigd.h"

#ifndef _DOUBLE_IS_32BITS

/* Taylor series expansion for cosh(2y) - cos(2x) */

double __ctans(double complex z)
{
    double f, x, x2, y, y2, rn, t;
    double d;

    x = fabs(2.0 * creal(z));
    y = fabs(2.0 * cimag(z));

    x = __redupi(x);

    x = x * x;
    y = y * y;
    x2 = 1.0;
    y2 = 1.0;
    f = 1.0;
    rn = 0.0;
    d = 0.0;

    do {
        rn += 1.0;
        f *= rn;
        rn += 1.0;
        f *= rn;
        x2 *= x;
        y2 *= y;
        t = y2 + x2;
        t /= f;
        d += t;

        rn += 1.0;
        f *= rn;
        rn += 1.0;
        f *= rn;
        x2 *= x;
        y2 *= y;
        t = y2 - x2;
        t /= f;
        d += t;
    } while (fabs(t / d) > MACHEP);

    return d;
}

double complex ctan(double complex z)
{
    double complex w;
    double d;

    d = cos(2.0 * creal(z)) + cosh(2.0 * cimag(z));

    if (fabs(d) < 0.25) {
        d = __ctans(z);
    }

    if (d == 0.0) {
        w = HUGE_VAL + HUGE_VAL * I;
        return w;
    }

    w = sin(2.0 * creal(z)) / d + (sinh(2.0 * cimag(z)) / d) * I;
    return w;
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double complex ctanl(long double complex z)
{
    return (long double complex) ctan((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
