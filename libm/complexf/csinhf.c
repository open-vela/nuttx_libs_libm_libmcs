// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>

float complex
csinhf(float complex z)
{
    float complex w;
    float x, y;

    x = crealf(z);
    y = cimagf(z);
    w = sinhf(x) * cosf(y) + (coshf(x) * sinf(y)) * I;
    return w;
}

#ifdef _DOUBLE_IS_32BITS

double complex csinh (double complex z)
{
    return (double complex) csinhf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
