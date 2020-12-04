// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007 The NetBSD Foundation, Inc.

#include <complex.h>
#include <math.h>
#include "cephes_subrl.h"

/* calculate cosh and sinh */

void
_cchshl(long double x, long double *c, long double *s)
{
	long double e, ei;

	if (fabsl(x) <= 0.5L) {
		*c = coshl(x);
		*s = sinhl(x);
	} else {
		e = expl(x);
		ei = 0.5L / e;
		e = 0.5L * e;
		*s = e - ei;
		*c = e + ei;
	}
}

/* Program to subtract nearest integer multiple of PI */

/* extended precision value of PI: */
static const long double DP1 = 3.14159265358979323829596852490908531763125L;
static const long double DP2 = 1.6667485837041756656403424829301998703007e-19L;
#ifndef __vax__
static const long double DP3 = 1.8830410776607851167459095484560349402753e-39L;
#define MACHEPL 1.1e-38L
#else
static const long double DP3 = 0L;
#define MACHEPL 1.1e-19L
#endif

long double
_redupil(long double x)
{
	long double t;
	long long i;

	t = x / M_PIL;
	if (t >= 0.0L)
		t += 0.5L;
	else
		t -= 0.5L;

	i = t;	/* the multiple */
	t = i;
	t = ((x - t * DP1) - t * DP2) - t * DP3;
	return t;
}

/* Taylor series expansion for cosh(2y) - cos(2x) */

long double
_ctansl(long double complex z)
{
	long double f, x, x2, y, y2, rn, t;
	long double d;

	x = fabsl(2.0L * creall(z));
	y = fabsl(2.0L * cimagl(z));

	x = _redupil(x);

	x = x * x;
	y = y * y;
	x2 = 1.0;
	y2 = 1.0;
	f = 1.0;
	rn = 0.0;
	d = 0.0;
	do {
		rn += 1.0L;
		f *= rn;
		rn += 1.0L;
		f *= rn;
		x2 *= x;
		y2 *= y;
		t = y2 + x2;
		t /= f;
		d += t;

		rn += 1.0L;
		f *= rn;
		rn += 1.0L;
		f *= rn;
		x2 *= x;
		y2 *= y;
		t = y2 - x2;
		t /= f;
		d += t;
	} while (fabsl(t/d) > MACHEPL);
	return d;
}
