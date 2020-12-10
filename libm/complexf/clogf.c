// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>

float complex
clogf(float complex z)
{
    float complex w;
    float p, rr;

    rr = cabsf(z);
    p = logf(rr);
    rr = atan2f(cimagf(z), crealf(z));
    w = p + rr * I;
    return w;
}

#ifdef _DOUBLE_IS_32BITS

double complex clog (double complex z)
{
    return (double complex) clogf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
