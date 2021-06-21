/* SPDX-License-Identifier: NetBSD */

#include <complex.h>
#include <math.h>

float complex cacosf(float complex z)
{
#ifdef __LIBMCS_FPU_DAZ
    z *= __volatile_onef;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    float complex w;

    w = casinf(z);
    w = ((float)M_PI_2 - crealf(w)) - cimagf(w) * I;
    return w;
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double complex cacos(double complex z)
{
    return (double complex) cacosf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
