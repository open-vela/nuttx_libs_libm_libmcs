/* SPDX-License-Identifier: RedHat */
/* Copyright (C) 2002 by  Red Hat, Incorporated. All rights reserved. */

/*
FUNCTION
<<fmax>>, <<fmaxf>>---maximum
INDEX
    fmax
INDEX
    fmaxf

SYNOPSIS
    #include <math.h>
    double fmax(double <[x]>, double <[y]>);
    float fmaxf(float <[x]>, float <[y]>);

DESCRIPTION
The <<fmax>> functions determine the maximum numeric value of their arguments.
NaN arguments are treated as missing data:  if one argument is a NaN and the
other numeric, then the <<fmax>> functions choose the numeric value.

RETURNS
The <<fmax>> functions return the maximum numeric value of their arguments.

PORTABILITY
ANSI C, POSIX.

*/

#include <math.h>

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double fmax(double x, double y)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
    y *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    if (isnan(x)) {
        return y;
    }

    if (isnan(y)) {
        return x;
    }

    return x > y ? x : y;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double fmaxl(long double x, long double y)
{
    return (long double) fmax((double) x, (double) y);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
