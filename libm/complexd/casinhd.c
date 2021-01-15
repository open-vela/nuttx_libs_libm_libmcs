/* SPDX-License-Identifier: NetBSD */

/*
FUNCTION
        <<casinh>>, <<casinhf>>---complex arc hyperbolic sine

INDEX
        casinh
INDEX
        casinhf

SYNOPSIS
       #include <complex.h>
       double complex casinh(double complex <[z]>);
       float complex casinhf(float complex <[z]>);


DESCRIPTION
        @ifnottex
        These functions compute the complex arc hyperbolic sine of <[z]>,
        with branch cuts outside the interval [-i, +i] along the
        imaginary axis.
        @end ifnottex
        @tex
        These functions compute the complex arc hyperbolic sine of <[z]>,
        with branch cuts outside the interval [$-i$, $+i$] along the
        imaginary axis.
        @end tex

        <<casinhf>> is identical to <<casinh>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        @ifnottex
        These functions return the complex arc hyperbolic sine value,
        in the range of a strip mathematically unbounded along the
        real axis and in the interval [-i*p/2, +i*p/2] along the
        imaginary axis.
        @end ifnottex
        @tex
        These functions return the complex arc hyperbolic sine value,
        in the range of a strip mathematically unbounded along the
        real axis and in the interval [$-i\pi/2$, $+i\pi/2$] along the
        imaginary axis.
        @end tex

PORTABILITY
        <<casinh>> and <<casinhf>> are ISO C99

QUICKREF
        <<casinh>> and <<casinhf>> are ISO C99

*/


#include <complex.h>

#ifndef _DOUBLE_IS_32BITS

double complex casinh(double complex z)
{
    double complex w;

    w = -1.0 * I * casin(z * I);
    return w;
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double complex casinhl(long double complex z)
{
    return (long double complex) casinh((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
