/* SPDX-License-Identifier: NetBSD */

/*
FUNCTION
        <<catanh>>, <<catanhf>>---complex arc hyperbolic tangent

INDEX
        catanh
INDEX
        catanhf

SYNOPSIS
       #include <complex.h>
       double complex catanh(double complex <[z]>);
       float complex catanhf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex arc hyperbolic tan of <[z]>,
        with branch cuts outside the interval [-1, +1] along the
        real axis.

        <<catanhf>> is identical to <<catanh>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        @ifnottex
        These functions return the complex arc hyperbolic tangent value,
        in the range of a strip mathematically unbounded along the
        real axis and in the interval [-i*p/2, +i*p/2] along the
        imaginary axis.
        @end ifnottex
        @tex
        These functions return the complex arc hyperbolic tangent value,
        in the range of a strip mathematically unbounded along the
        real axis and in the interval [$-i\pi/2$, $+i\pi/2$] along the
        imaginary axis.
        @end tex

PORTABILITY
        <<catanh>> and <<catanhf>> are ISO C99

QUICKREF
        <<catanh>> and <<catanhf>> are ISO C99

*/

#include <complex.h>

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double complex catanh(double complex z)
{
#ifdef __LIBMCS_FPU_DAZ
    z *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    double complex w;
    double complex tmp;

    /* w = -1.0 * I * catan(z * I) */
    tmp = CMPLX(-cimag(z), creal(z));
    tmp = catan(tmp);
    w = CMPLX(cimag(tmp), -creal(tmp));
    return w;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double complex catanhl(long double complex z)
{
    return (long double complex) catanh((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
