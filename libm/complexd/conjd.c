/* SPDX-License-Identifier: PublicDomain */
/* Written by Matthias Drochner <drochner@NetBSD.org>. */

/*
FUNCTION
        <<conj>>, <<conjf>>---complex conjugate

INDEX
        conj
INDEX
        conjf

SYNOPSIS
       #include <complex.h>
       double complex conj(double complex <[z]>);
       float complex conjf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex conjugate of <[z]>,
        by reversing the sign of its imaginary part.

        <<conjf>> is identical to <<conj>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        The conj functions return the complex conjugate value.

PORTABILITY
        <<conj>> and <<conjf>> are ISO C99

QUICKREF
        <<conj>> and <<conjf>> are ISO C99

*/

#include <complex.h>
#include "../common/fdlibm.h"

#ifndef _DOUBLE_IS_32BITS

double complex conj(double complex z)
{
    double_complex w = { .z = z };

    IMAG_PART(w) = -IMAG_PART(w);

    return (w.z);
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double complex conjl(long double complex z)
{
    return (long double complex) conj((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
