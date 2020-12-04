// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007 The NetBSD Foundation, Inc.

#include <complex.h>
#include <math.h>
#include "cephes_subrl.h"

#ifdef __weak_alias
__weak_alias(catanl, _catanl)
#endif

long double complex
catanl(long double complex z)
{
	long double complex w;
	long double a, t, x, x2, y;

	x = creall(z);
	y = cimagl(z);

	if ((x == 0.0L) && (y > 1.0L))
		goto ovrf;

	x2 = x * x;
	a = 1.0L - x2 - (y * y);
	if (a == 0.0)
		goto ovrf;

	t = 0.5L * atan2l(2.0L * x, a);
	w = _redupil(t);

	t = y - 1.0L;
	a = x2 + (t * t);
	if (a == 0.0L)
		goto ovrf;

	t = y + 1.0L;
	a = (x2 + (t * t))/a;
	w = w + (0.25L * logl(a)) * I;
	return w;

ovrf:
#if 0
	mtherr ("catanl", OVERFLOW);
#endif
	w = HUGE_VALL + HUGE_VALL * I;
	return w;
}

