// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007 The NetBSD Foundation, Inc.

#include <complex.h>
#include <math.h>
#include "cephes_subrl.h"

long double complex
cacosl(long double complex z)
{
	long double complex w;

	w = casinl(z);
	w = (M_PI_2L - creall(w)) - cimagl(w) * I;
	return w;
}

