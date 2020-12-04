// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007 The NetBSD Foundation, Inc.

#include <complex.h>
#include <math.h>
#include "cephes_subrl.h"

long double complex
ctanl(long double complex z)
{
	long double complex w;
	long double d;

	d = cosl(2.0L * creall(z)) + coshl(2.0L * cimagl(z));

	if (fabsl(d) < 0.25L)
		d = _ctansl(z);

	if (d == 0.0L) {
		/* mtherr ("ctan", OVERFLOW); */
		w = HUGE_VALL + HUGE_VALL * I;
		return w;
	}

	w = sinl(2.0L * creall(z)) / d + (sinhl(2.0L * cimagl(z)) / d) * I;
	return w;
}
