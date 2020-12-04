// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007 The NetBSD Foundation, Inc.

#include <sys/cdefs.h>
__RCSID("$NetBSD: conjl.c,v 1.4 2010/09/20 16:55:20 christos Exp $");

#include <complex.h>
#include "../common/fdlibm.h"

/*
 * conjl(long double complex z)
 * This function returns the complex conjugate value of its argument, z.
 */
long double complex
conjl(long double complex z)
{
	long_double_complex w = { .z = z };

	IMAG_PART(w) = -IMAG_PART(w);

	return (w.z);
}
