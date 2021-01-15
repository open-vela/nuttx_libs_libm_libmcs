/* SPDX-License-Identifier: NetBSD */

/*
FUNCTION
        <<casin>>, <<casinf>>---complex arc sine

INDEX
        casin
INDEX
        casinf

SYNOPSIS
       #include <complex.h>
       double complex casin(double complex <[z]>);
       float complex casinf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex arc sine of <[z]>,
        with branch cuts outside the interval [-1, +1] along the real axis.

        <<casinf>> is identical to <<casin>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        @ifnottex
        These functions return the complex arc sine value, in the range
        of a strip mathematically  unbounded  along the imaginary axis
        and in the interval [-pi/2, +pi/2] along the real axis.
        @end ifnottex
        @tex
        These functions return the complex arc sine value, in the range
        of a strip mathematically  unbounded  along the imaginary axis
        and in the interval [$-\pi/2$, $+\pi/2$] along the real axis.
        @end tex

PORTABILITY
        <<casin>> and <<casinf>> are ISO C99

QUICKREF
        <<casin>> and <<casinf>> are ISO C99

*/

#include <complex.h>
#include <math.h>

#ifndef _DOUBLE_IS_32BITS

double complex casin(double complex z)
{
    double complex w;
    double complex ca, ct, zz, z2;
    double x, y;

    x = creal(z);
    y = cimag(z);

    ca = x + y * I;
    ct = ca * I;
    /* sqrt( 1 - z*z) */
    /* cmul( &ca, &ca, &zz ) */
    /*x * x  -  y * y */
    zz = (x - y) * (x + y) + (2.0 * x * y) * I;

    zz = 1.0 - creal(zz) - cimag(zz) * I;
    z2 = csqrt(zz);

    zz = ct + z2;
    zz = clog(zz);
    /* multiply by 1/i = -i */
    w = zz * (-1.0 * I);
    return w;
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double complex casinl(long double complex z)
{
    return (long double complex) casin((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
