// SPDX-License-Identifier: PublicDomain
// Written by Matthias Drochner <drochner@NetBSD.org>.

#include <complex.h>
#include <math.h>

float
cabsf(float complex z)
{
    return hypotf( crealf(z), cimagf(z) );
}

#ifdef _DOUBLE_IS_32BITS

double cabs (double complex z)
{
    return (double) cabsf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */