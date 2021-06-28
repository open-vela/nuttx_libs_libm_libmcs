/* SPDX-License-Identifier: RedHat */
/* Copyright (C) 2002 by  Red Hat, Incorporated. All rights reserved. */

/*
FUNCTION
<<fmin>>, <<fminf>>---minimum
INDEX
    fmin
INDEX
    fminf

SYNOPSIS
    #include <math.h>
    double fmin(double <[x]>, double <[y]>);
    float fminf(float <[x]>, float <[y]>);

DESCRIPTION
The <<fmin>> functions determine the minimum numeric value of their arguments.
NaN arguments are treated as missing data:  if one argument is a NaN and the
other numeric, then the <<fmin>> functions choose the numeric value.

RETURNS
The <<fmin>> functions return the minimum numeric value of their arguments.

PORTABILITY
ANSI C, POSIX.

*/

#include <math.h>

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double fmin(double x, double y)
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

    return x < y ? x : y;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double fminl(long double x, long double y)
{
    return (long double) fmin((double) x, (double) y);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
