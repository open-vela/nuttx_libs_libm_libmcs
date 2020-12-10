// SPDX-License-Identifier: NetBSD

/*
FUNCTION
        <<ccosh>>, <<ccoshf>>---complex hyperbolic cosine

INDEX
        ccosh
INDEX
        ccoshf

SYNOPSIS
       #include <complex.h>
       double complex ccosh(double complex <[z]>);
       float complex ccoshf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex hyperbolic cosine of <[z]>.

        <<ccoshf>> is identical to <<ccosh>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        These functions return the complex hyperbolic cosine value.

PORTABILITY
        <<ccosh>> and <<ccoshf>> are ISO C99

QUICKREF
        <<ccosh>> and <<ccoshf>> are ISO C99

*/


#include <complex.h>
#include <math.h>

#ifndef _DOUBLE_IS_32BITS

double complex ccosh(double complex z)
{
    double complex w;
    double x, y;

    x = creal(z);
    y = cimag(z);
    w = cosh(x) * cos(y) + (sinh(x) * sin(y)) * I;
    return w;
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double complex ccoshl(long double complex z)
{
    return (long double complex) ccosh((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
