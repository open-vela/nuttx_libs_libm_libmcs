/* SPDX-License-Identifier: PublicDomain */
/* Written by Matthias Drochner <drochner@NetBSD.org>. */

/*
FUNCTION
        <<cabs>>, <<cabsf>>, <<cabsl>>---complex absolute-value

INDEX
        cabs
INDEX
        cabsf
INDEX
        cabsl

SYNOPSIS
       #include <complex.h>
       double cabs(double complex <[z]>);
       float cabsf(float complex <[z]>);
       long double cabsl(long double complex <[z]>);


DESCRIPTION
        These functions compute compute the complex absolute value
        (also called norm, modulus, or magnitude) of <[z]>.

        <<cabsf>> is identical to <<cabs>>, except that it performs
        its calculations on <<float complex>>.

        <<cabsl>> is identical to <<cabs>>, except that it performs
        its calculations on <<long double complex>>.

RETURNS
        The cabs* functions return the complex absolute value.

PORTABILITY
        <<cabs>>, <<cabsf>> and <<cabsl>> are ISO C99

QUICKREF
        <<cabs>>, <<cabsf>> and <<cabsl>> are ISO C99

*/


#include <complex.h>
#include <math.h>

#ifndef _DOUBLE_IS_32BITS

double cabs(double complex z)
{
    return hypot(creal(z), cimag(z));
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double cabsl(long double complex z)
{
    return (long double) cabs((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
