/* SPDX-License-Identifier: GTDGmbH */
/* Copyright 2020-2021 by GTD GmbH. */

#ifndef _DOUBLE_IS_32BITS

double fma(double x, double y, double z)
{
    return x * y + z;
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double fmal(long double x, long double y, long double z)
{
    return (long double) fma((double) x, (double) y, (double) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
