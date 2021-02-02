/* SPDX-License-Identifier: GTDGmbH */
/* Copyright 2020-2021 by GTD GmbH. */

#ifndef __LIBMCS_DOUBLE_IS_32BITS

#include <math.h>

double nexttoward(double x, long double y)
{
    return nextafter(x, (double) y);
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double nexttowardl(long double x, long double y)
{
    return (long double) nexttoward((double) x, y);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
