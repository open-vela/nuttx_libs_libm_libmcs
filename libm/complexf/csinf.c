/* SPDX-License-Identifier: NetBSD */

#include <complex.h>
#include <math.h>
#include "internal/ctrigf.h"

float complex csinf(float complex z)
{
    float complex w;
    float ch, sh;

    __ccoshsinhf(cimagf(z), &ch, &sh);
    w = sinf(crealf(z)) * ch + (cosf(crealf(z)) * sh) * I;
    return w;
}

#ifdef _DOUBLE_IS_32BITS

double complex csin(double complex z)
{
    return (double complex) csinf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
