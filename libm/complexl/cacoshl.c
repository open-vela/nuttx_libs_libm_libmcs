// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007 The NetBSD Foundation, Inc.

#include <complex.h>

long double complex
cacoshl(long double complex z)
{
	long double complex w;

#if 0 /* does not give the principal value */
	w = I * cacosl(z);
#else
	w = clogl(z + csqrtl(z + 1) * csqrtl(z - 1));
#endif
	return w;
}
