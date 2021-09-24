/* SPDX-License-Identifier: NetBSD */

#include <complex.h>
#include <math.h>

#include "../common/tools.h"

/*
 * cprojf(float complex z)
 *
 * These functions return the value of the projection (not stereographic!)
 * onto the Riemann sphere.
 *
 * z projects to z, except that all complex infinities (even those with one
 * infinite part and one NaN part) project to positive infinity on the real axis.
 * If z has an infinite part, then cproj(z) shall be equivalent to:
 *
 * INFINITY + I * copysign(0.0, cimag(z))
 */

float complex cprojf(float complex z)
{
    float_complex w = { .z = z };

    if (isinf(REAL_PART(w)) || isinf(IMAG_PART(w))) {
        REAL_PART(w) = INFINITY;
        IMAG_PART(w) = copysignf(0.0, cimagf(z));
    }

    return (w.z);
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double complex cproj(double complex z)
{
    return (double complex) cprojf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
