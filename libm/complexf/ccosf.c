/* SPDX-License-Identifier: NetBSD */

#include <complex.h>
#include <math.h>

float complex ccosf(float complex z)
{
    float complex w;
    float ch, sh;

    __ccoshsinhf(cimagf(z), &ch, &sh);
    w = cosf(crealf(z)) * ch - (sinf(crealf(z)) * sh) * I;
    return w;
}

#ifdef _DOUBLE_IS_32BITS

double complex ccos(double complex z)
{
    return (double complex) ccosf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
