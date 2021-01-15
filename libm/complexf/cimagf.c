/* SPDX-License-Identifier: PublicDomain */
/* Written by Matthias Drochner <drochner@NetBSD.org>. */

#include <complex.h>
#include "../common/tools.h"

float cimagf(float complex z)
{
    float_complex w = { .z = z };

    return (IMAG_PART(w));
}

#ifdef _DOUBLE_IS_32BITS

double cimag(double complex z)
{
    return (double) cimagf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
