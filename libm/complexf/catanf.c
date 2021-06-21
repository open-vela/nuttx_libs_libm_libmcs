/* SPDX-License-Identifier: NetBSD */

#include <complex.h>
#include <math.h>
#include "internal/ctrigf.h"

float complex catanf(float complex z)
{
#ifdef __LIBMCS_FPU_DAZ
    z *= __volatile_onef;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    float complex w;
    float a, t, x, x2, y;

    x = crealf(z);
    y = cimagf(z);

    if ((x == 0.0f) && (y > 1.0f)) {
        goto ovrf;
    }

    x2 = x * x;
    a = 1.0f - x2 - (y * y);

    if (a == 0.0f) {
        goto ovrf;
    }

    t = 0.5f * atan2f(2.0f * x, a);
    w = __redupif(t);

    t = y - 1.0f;
    a = x2 + (t * t);

    if (a == 0.0f) {
        goto ovrf;
    }

    t = y + 1.0f;
    a = (x2 + (t * t)) / a;
    w = w + (0.25f * logf(a)) * I;
    return w;

ovrf:
    w = HUGE_VALF + HUGE_VALF * I;
    return w;
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double complex catan(double complex z)
{
    return (double complex) catanf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
