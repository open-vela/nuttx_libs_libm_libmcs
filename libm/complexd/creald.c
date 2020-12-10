// SPDX-License-Identifier: PublicDomain
// Written by Matthias Drochner <drochner@NetBSD.org>.

/*
FUNCTION
        <<creal>>, <<crealf>>, <<creall>>---real part

INDEX
        creal
INDEX
        crealf
INDEX
        creall

SYNOPSIS
       #include <complex.h>
       double creal(double complex <[z]>);
       float crealf(float complex <[z]>);
       double long creall(long double complex <[z]>);


DESCRIPTION
        These functions compute the real part of <[z]>.

        <<crealf>> is identical to <<creal>>, except that it performs
        its calculations on <<float complex>>.

        <<creall>> is identical to <<creal>>, except that it performs
        its calculations on <<long double complex>>.

RETURNS
        The creal* functions return the real part value.

PORTABILITY
        <<creal>>, <<crealf>> and <<creall>> are ISO C99

QUICKREF
        <<creal>>, <<crealf>> and <<creall>> are ISO C99

*/


#include <complex.h>
#include "../common/fdlibm.h"

#ifndef _DOUBLE_IS_32BITS

double creal(double complex z)
{
    double_complex w = { .z = z };

    return (REAL_PART(w));
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double creall(long double complex z)
{
    return (long double) creal((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
