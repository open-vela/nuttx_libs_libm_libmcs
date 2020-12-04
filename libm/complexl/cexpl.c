// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007 The NetBSD Foundation, Inc.

#include <complex.h>
#include <math.h>

long double complex
cexpl(long double complex z)
{
	long double complex w;
	long double r, x, y;

	x = creall(z);
	y = cimagl(z);
	r = expl(x);
	w = r * cosl(y) + r * sinl(y) * I;
	return w;
}
