// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007 The NetBSD Foundation, Inc.

#include <complex.h>
#include <math.h>

long double complex
clogl(long double complex z)
{
	long double complex w;
	long double p, rr;

	rr = cabsl(z);
	p = logl(rr);
	rr = atan2l(cimagl(z), creall(z));
	w = p + rr * I;
	return w;
}
