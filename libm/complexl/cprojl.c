// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007 The NetBSD Foundation, Inc.

#include <sys/cdefs.h>
__RCSID("$NetBSD: cprojl.c,v 1.7 2014/10/10 00:48:18 christos Exp $");

#include <complex.h>
#include <math.h>

#include "../common/fdlibm.h"

/*
 * cprojl(long double complex z)
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
long double complex
cprojl(long double complex z)
{
	long_double_complex w = { .z = z };

	/*CONSTCOND*/
	if (isinf(creall(z)) || isinf(cimagl(z))) {
#ifdef __INFINITY
		REAL_PART(w) = HUGE_VAL;
#else
		REAL_PART(w) = INFINITY;
#endif
		IMAG_PART(w) = copysignl(0.0L, cimagl(z));
	}

	return (w.z);
}
