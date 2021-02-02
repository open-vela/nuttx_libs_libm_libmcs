/* SPDX-License-Identifier: NetBSD */

#include <complex.h>

float complex casinf(float complex z)
{
    float complex w;
    float complex ca, ct, zz, z2;
    float x, y;

    x = crealf(z);
    y = cimagf(z);

    ca = x + y * I;
    ct = ca * I;
    /* sqrt( 1 - z*z) */
    /* cmul( &ca, &ca, &zz ) */
    /*x * x  -  y * y */
    zz = (x - y) * (x + y) + (2.0f * x * y) * I;

    zz = 1.0f - crealf(zz) - cimagf(zz) * I;
    z2 = csqrtf(zz);

    zz = ct + z2;
    zz = clogf(zz);
    /* multiply by 1/i = -i */
    w = zz * (-1.0f * I);
    return w;
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double complex casin(double complex z)
{
    return (double complex) casinf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
