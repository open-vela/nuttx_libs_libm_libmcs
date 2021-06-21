/* SPDX-License-Identifier: NetBSD */

/*
FUNCTION
        <<csinh>>, <<csinhf>>---complex hyperbolic sine

INDEX
        csinh
INDEX
        csinhf

SYNOPSIS
       #include <complex.h>
       double complex csinh(double complex <[z]>);
       float complex csinhf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex hyperbolic sine of <[z]>.

        <<ccoshf>> is identical to <<ccosh>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        These functions return the complex hyperbolic sine value.

PORTABILITY
        <<csinh>> and <<csinhf>> are ISO C99

QUICKREF
        <<csinh>> and <<csinhf>> are ISO C99

*/

#include <complex.h>
#include <math.h>

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double complex csinh(double complex z)
{
#ifdef __LIBMCS_FPU_DAZ
    z *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    double complex w;
    double x, y;

    x = creal(z);
    y = cimag(z);
    w = sinh(x) * cos(y) + (cosh(x) * sin(y)) * I;
    return w;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double complex csinhl(long double complex z)
{
    return (long double complex) csinh((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
