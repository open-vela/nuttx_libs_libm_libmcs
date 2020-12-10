// SPDX-License-Identifier: NetBSD

/*
FUNCTION
        <<cacosh>>, <<cacoshf>>---complex arc hyperbolic cosine

INDEX
        cacosh
INDEX
        cacoshf

SYNOPSIS
       #include <complex.h>
       double complex cacosh(double complex <[z]>);
       float complex cacoshf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex arc hyperbolic cosine of <[z]>,
        with a branch cut at values less than 1 along the real axis.

        <<cacoshf>> is identical to <<cacosh>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        @ifnottex
        These functions return the complex arc hyperbolic cosine value, 
        in the range of a half-strip of non-negative values along the 
        real axis and in the interval [-i * pi, +i * pi] along the 
        imaginary axis.
        @end ifnottex
        @tex
        These functions return the complex arc hyperbolic cosine value, 
        in the range of a half-strip of non-negative values along the 
        real axis and in the interval [$-i\pi$, $+i\pi$] along the 
        imaginary axis.
        @end tex

PORTABILITY
        <<cacosh>> and <<cacoshf>> are ISO C99

QUICKREF
        <<cacosh>> and <<cacoshf>> are ISO C99

*/


#include <complex.h>

#ifndef _DOUBLE_IS_32BITS

double complex
cacosh(double complex z)
{
    double complex w;

    w = clog(z + csqrt(z + 1) * csqrt(z - 1));

    return w;
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double complex cacoshl (long double complex z)
{
    return (long double complex) cacosh((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
