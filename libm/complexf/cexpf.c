// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>

float complex
cexpf(float complex z)
{
    float complex w;
    float r, x, y;

    x = crealf(z);
    y = cimagf(z);
    r = expf(x);
    w = r * cosf(y) + r * sinf(y) * I;
    return w;
}

#ifdef _DOUBLE_IS_32BITS

double complex cexp (double complex z)
{
    return (double complex) cexpf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
