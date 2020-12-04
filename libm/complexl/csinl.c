// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007 The NetBSD Foundation, Inc.

#include <complex.h>
#include <math.h>
#include "cephes_subrl.h"

long double complex
csinl(long double complex z)
{
	long double complex w;
	long double ch, sh;

	_cchshl(cimagl(z), &ch, &sh);
	w = sinl(creall(z)) * ch + (cosl(creall(z)) * sh) * I;
	return w;
}
