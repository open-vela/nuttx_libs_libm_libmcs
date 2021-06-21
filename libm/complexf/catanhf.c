/* SPDX-License-Identifier: NetBSD */

#include <complex.h>

float complex catanhf(float complex z)
{
#ifdef __LIBMCS_FPU_DAZ
    z *= __volatile_onef;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    float complex w;

    w = -1.0f * I * catanf(z * I);
    return w;
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double complex catanh(double complex z)
{
    return (double complex) catanhf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
