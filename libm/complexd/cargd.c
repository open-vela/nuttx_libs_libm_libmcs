/* SPDX-License-Identifier: PublicDomain */
/* Written by Matthias Drochner <drochner@NetBSD.org>. */

/*
FUNCTION
        <<carg>>, <<cargf>>---argument (phase angle)

INDEX
        carg
INDEX
        cargf

SYNOPSIS
       #include <complex.h>
       double carg(double complex <[z]>);
       float cargf(float complex <[z]>);


DESCRIPTION
        These functions compute the argument (also called phase angle)
        of <[z]>, with a branch cut along the negative real axis.

        <<cargf>> is identical to <<carg>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        @ifnottex
        The carg functions return the value of the argument in the
        interval [-pi, +pi]
        @end ifnottex
        @tex
        The carg functions return the value of the argument in the
        interval [$-\pi$, $+\pi$]
        @end tex

PORTABILITY
        <<carg>> and <<cargf>> are ISO C99

QUICKREF
        <<carg>> and <<cargf>> are ISO C99

*/

#include <complex.h>
#include <math.h>

#ifndef _DOUBLE_IS_32BITS

double carg(double complex z)
{
    return atan2(cimag(z), creal(z));
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double cargl(long double complex z)
{
    return (long double) carg((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
