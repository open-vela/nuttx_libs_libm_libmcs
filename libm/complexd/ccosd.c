/* SPDX-License-Identifier: NetBSD */

/*
FUNCTION
        <<ccos>>, <<ccosf>>---complex cosine

INDEX
        ccos
INDEX
        ccosf

SYNOPSIS
       #include <complex.h>
       double complex ccos(double complex <[z]>);
       float complex ccosf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex cosine of <[z]>.

        <<ccosf>> is identical to <<ccos>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        These functions return the complex cosine value.

PORTABILITY
        <<ccos>> and <<ccosf>> are ISO C99

QUICKREF
        <<ccos>> and <<ccosf>> are ISO C99

*/


#include <complex.h>
#include <math.h>
#include "internal/ctrigd.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double complex ccos(double complex z)
{
#ifdef __LIBMCS_FPU_DAZ
    z *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    double complex w;
    double ch, sh;

    __ccoshsinh(cimag(z), &ch, &sh);
    w = cos(creal(z)) * ch - (sin(creal(z)) * sh) * I;
    return w;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double complex ccosl(long double complex z)
{
    return (long double complex) ccos((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
