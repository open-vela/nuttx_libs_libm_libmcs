// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007-2008 David Schultz <das@FreeBSD.ORG>

#include <sys/cdefs.h>
#if 0
__FBSDID("$FreeBSD: head/lib/msun/src/s_csqrtl.c 181402 2008-08-08 00:15:16Z das $");
#else
__RCSID("$NetBSD: csqrtl.c,v 1.2 2014/10/11 00:43:51 christos Exp $");
#endif

#include <complex.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
/*
 * gcc doesn't implement complex multiplication or division correctly,
 * so we need to handle infinities specially. We turn on this pragma to
 * notify conforming c99 compilers that the fast-but-incorrect code that
 * gcc generates is acceptable, since the special cases have already been
 * handled.
 */
// #pragma	STDC CX_LIMITED_RANGE	ON

/* We risk spurious overflow for components >= LDBL_MAX / (1 + sqrt(2)). */
#define	THRESH	(LDBL_MAX / 2.414213562373095048801688724209698L)

#define cpackl(r, i) ((r) + (i) * I)

long double complex
csqrtl(long double complex z)
{
	long double complex result;
	long double a, b;
	long double t;
	bool scale;

	a = creall(z);
	b = cimagl(z);

	/* Handle special cases. */
	if (z == 0.0L)
		return (cpackl(0.0L, b));
	if (isinf(b))
		return (cpackl(INFINITY, b));
	if (isnan(a)) {
		t = (b - b) / (b - b);	/* raise invalid if b is not a NaN */
		return (cpackl(a, t));	/* return NaN + NaN i */
	}
	if (isinf(a)) {
		/*
		 * csqrt(inf + NaN i)  = inf +  NaN i
		 * csqrt(inf + y i)    = inf +  0 i
		 * csqrt(-inf + NaN i) = NaN +- inf i
		 * csqrt(-inf + y i)   = 0   +  inf i
		 */
		if (signbit(a))
			return (cpackl(fabsl(b - b), copysignl(a, b)));
		else
			return (cpackl(a, copysignl(b - b, b)));
	}
	/*
	 * The remaining special case (b is NaN) is handled just fine by
	 * the normal code path below.
	 */

	/* Scale to avoid overflow. */
	if (fabsl(a) >= THRESH || fabsl(b) >= THRESH) {
		a *= 0.25L;
		b *= 0.25L;
		scale = true;
	} else {
		scale = false;
	}

	/* Algorithm 312, CACM vol 10, Oct 1967. */
	if (a >= 0L) {
		t = sqrtl((a + hypotl(a, b)) * 0.5L);
		result = cpackl(t, b / (2.0L * t));
	} else {
		t = sqrtl((-a + hypotl(a, b)) * 0.5L);
		result = cpackl(fabsl(b) / (2.0L * t), copysignl(t, b));
	}

	/* Rescale. */
	if (scale)
		return (result * 2.0L);
	else
		return (result);
}
