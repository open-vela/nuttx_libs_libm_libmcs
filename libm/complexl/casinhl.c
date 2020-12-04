// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007 The NetBSD Foundation, Inc.

#include <complex.h>

long double complex
casinhl(long double complex z)
{
	long double complex w;

	w = -1.0L * I * casinl(z * I);
	return w;
}
