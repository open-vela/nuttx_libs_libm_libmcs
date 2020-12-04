// SPDX-License-Identifier: NetBSD

#include <sys/cdefs.h>
/*__RCSID("$NetBSD: cprojf.c,v 1.3 2010/09/20 17:51:38 christos Exp $"); */

#include <complex.h>
#include <math.h>

#include "../common/fdlibm.h"

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

float complex
cprojf(float complex z)
{
	float_complex w = { .z = z };

	if (isinf(crealf(z)) || isinf(cimagf(z))) {
#ifdef __INFINITY
		REAL_PART(w) = __INFINITY;
#else
		REAL_PART(w) = INFINITY;
#endif
		IMAG_PART(w) = copysignf(0.0, cimagf(z));
	}

	return (w.z);
}
