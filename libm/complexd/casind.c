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

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double complex casin(double complex z)
{
#ifdef __LIBMCS_FPU_DAZ
    z *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    double complex w;
    double complex ct, zz, z2;
    double x, y;

    x = creal(z);
    y = cimag(z);

    ct = CMPLX(-y, x);
    /* zz = (x - y) * (x + y) + (2.0 * x * y) * I; */
    zz = CMPLX((x - y) * (x + y), 2.0 * x * y);

    /* zz = 1.0 - creal(zz) - cimag(zz) * I; */
    zz = CMPLX(1.0 - creal(zz), -cimag(zz));
    z2 = csqrt(zz);

    zz = ct + z2;
    zz = clog(zz);
    /* w = zz * (-1.0 * I); */
    w = CMPLX(cimag(zz), -creal(zz));
    return w;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double complex casinl(long double complex z)
{
    return (long double complex) casin((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
