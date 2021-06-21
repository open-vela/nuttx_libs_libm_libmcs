/* SPDX-License-Identifier: NetBSD */

/*
FUNCTION
        <<cpow>>, <<cpowf>>---complex power

INDEX
        cpow
INDEX
        cpowf

SYNOPSIS
       #include <complex.h>
       double complex cpow(double complex <[x]>, double complex <[y]>);
       float complex cpowf(float complex <[x]>, float complex <[y]>);


DESCRIPTION
        @ifnottex
        The cpow functions compute the complex power function x^y
        power, with a branch cut for the first parameter along the
        negative real axis.
        @end ifnottex
        @tex
        The cpow functions compute the complex power function $x^y$
        power, with a branch cut for the first parameter along the
        negative real axis.
        @end tex

        <<cpowf>> is identical to <<cpow>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        The cpow functions return the complex power function value.

PORTABILITY
        <<cpow>> and <<cpowf>> are ISO C99

QUICKREF
        <<cpow>> and <<cpowf>> are ISO C99

*/


#include <complex.h>
#include <math.h>

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double complex cpow(double complex x, double complex y)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
    y *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    double complex w;
    double realz, imagz, result, theta, absx, argx;

    realz = creal(y);
    imagz = cimag(y);
    absx = cabs(x);

    if (absx == 0.0) {
        return (0.0 + 0.0 * I);
    }

    argx = carg(x);
    result = pow(absx, realz);
    theta = realz * argx;

    if (imagz != 0.0) {
        result = result * exp(-imagz * argx);
        theta = theta + imagz * log(absx);
    }

    w = result * cos(theta) + (result * sin(theta)) * I;
    return w;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double complex cpowl(long double complex x, long double complex y)
{
    return (long double complex) cpow((double complex) x, (double complex) y);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
