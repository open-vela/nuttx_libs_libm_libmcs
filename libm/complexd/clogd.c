/* SPDX-License-Identifier: NetBSD */

/*
FUNCTION
        <<clog>>, <<clogf>>---complex base-e logarithm

INDEX
        clog
INDEX
        clogf

SYNOPSIS
       #include <complex.h>
       double complex clog(double complex <[z]>);
       float complex clogf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex natural (base-<[e]>) logarithm
        of <[z]>, with a branch cut along the negative real axis.

        <<clogf>> is identical to <<clog>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        @ifnottex
        The clog functions return the complex natural logarithm value, in
        the range of a strip mathematically unbounded along the real axis
        and in the interval [-i*pi , +i*pi] along the imaginary axis.
        @end ifnottex
        @tex
        The clog functions return the complex natural logarithm value, in
        the range of a strip mathematically unbounded along the real axis
         and in the interval [$-i\pi$, $+i\pi$] along the imaginary axis.
        @end tex

PORTABILITY
        <<clog>> and <<clogf>> are ISO C99

QUICKREF
        <<clog>> and <<clogf>> are ISO C99

*/

#include <complex.h>
#include <math.h>

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double complex clog(double complex z)
{
#ifdef __LIBMCS_FPU_DAZ
    z *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    double complex w;
    double p, rr;

    rr = cabs(z);
    p = log(rr);
    rr = atan2(cimag(z), creal(z));
    /* w = p + rr * I; */
    w = CMPLX(p, rr);
    return w;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double complex clogl(long double complex z)
{
    return (long double complex) clog((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
