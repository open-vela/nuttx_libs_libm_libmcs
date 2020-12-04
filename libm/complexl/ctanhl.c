// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007 The NetBSD Foundation, Inc.

#include <complex.h>
#include <math.h>

long double complex
ctanhl(long double complex z)
{
	long double complex w;
	long double x, y, d;

	x = creall(z);
	y = cimagl(z);
	d = coshl(2.0L * x) + cosl(2.0L * y);
	w = sinhl(2.0L * x) / d  +  (sinl(2.0L * y) / d) * I;

	return w;
}
