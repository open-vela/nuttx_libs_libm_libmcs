// SPDX-License-Identifier: NetBSD

/*
FUNCTION
        <<cacos>>, <<cacosf>>---complex arc cosine

INDEX
        cacos
INDEX
        cacosf

SYNOPSIS
       #include <complex.h>
       double complex cacos(double complex <[z]>);
       float complex cacosf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex arc cosine of <[z]>,
        with branch cuts outside the interval [-1, +1] along the real axis.

        <<cacosf>> is identical to <<cacos>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        @ifnottex
        These functions return the complex arc cosine value, in the range
        of a strip mathematically  unbounded  along the imaginary axis
        and in the interval [0, pi] along the real axis.
        @end ifnottex
        @tex
        These functions return the complex arc cosine value, in the range
        of a strip mathematically  unbounded  along the imaginary axis
        and in the interval [<<0>>, $\pi$] along the real axis.
        @end tex

PORTABILITY
        <<cacos>> and <<cacosf>> are ISO C99

QUICKREF
        <<cacos>> and <<cacosf>> are ISO C99

*/

#include <complex.h>
#include <math.h>

#ifndef _DOUBLE_IS_32BITS

double complex cacos(double complex z)
{
    double complex w;
    double complex tmp0, tmp1;

    tmp0 = casin(z);
    tmp1 = M_PI_2 - creal(tmp0);
    w = tmp1 - (cimag(tmp0) * I);

    return w;
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double complex cacosl(long double complex z)
{
    return (long double complex) cacos((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
