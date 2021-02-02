/* SPDX-License-Identifier: PublicDomain */
/* Written by Matthias Drochner <drochner@NetBSD.org>. */

#include <complex.h>
#include "../common/tools.h"

float crealf(float complex z)
{
    float_complex w = { .z = z };

    return (REAL_PART(w));
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double creal(double complex z)
{
    return (double) crealf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
