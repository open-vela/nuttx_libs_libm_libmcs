/* SPDX-License-Identifier: GTDGmbH */
/* Copyright 2020-2021 by GTD GmbH. */

#include <math.h>

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double fma(double x, double y, double z)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
    y *= __volatile_one;
    z *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    return x * y + z;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double fmal(long double x, long double y, long double z)
{
    return (long double) fma((double) x, (double) y, (double) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
