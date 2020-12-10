// SPDX-License-Identifier: RedHat
// Copyright (C) 2002 by  Red Hat, Incorporated. All rights reserved.

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

#include "fdlibm.h"

#ifndef _DOUBLE_IS_32BITS

double fmin(double x, double y)
{
  if (__fpclassifyd(x) == FP_NAN)
    return y;
  if (__fpclassifyd(y) == FP_NAN)
    return x;
  
  return x < y ? x : y;
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double fminl (long double x, long double y)
{
    return (long double) fmin((double) x, (double) y);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
