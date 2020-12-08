// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007 The NetBSD Foundation, Inc.

#include <complex.h>
#include <math.h>

long double complex
cpowl(long double complex a, long double complex z)
{
	long double complex w;
	long double x, y, r, theta, absa, arga;

	x = creall(z);
	y = cimagl(z);
	absa = cabsl(a);
	if (absa == 0.0L) {
		return (0.0L + 0.0L * I);
	}
	arga = cargl(a);
	r = powl(absa, x);
	theta = x * arga;
	if (y != 0.0L) {
		r = r * expl(-y * arga);
		theta = theta + y * logl(absa);
	}
	w = r * cosl(theta) + (r * sinl(theta)) * I;
	return w;
}
