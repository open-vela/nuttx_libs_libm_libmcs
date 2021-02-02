/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*
FUNCTION
       <<fabs>>, <<fabsf>>---absolute value (magnitude)
INDEX
    fabs
INDEX
    fabsf

SYNOPSIS
    #include <math.h>
       double fabs(double <[x]>);
       float fabsf(float <[x]>);

DESCRIPTION
<<fabs>> and <<fabsf>> calculate
@tex
$|x|$,
@end tex
the absolute value (magnitude) of the argument <[x]>, by direct
manipulation of the bit representation of <[x]>.

RETURNS
The calculated value is returned.  No errors are detected.

PORTABILITY
<<fabs>> is ANSI.
<<fabsf>> is an extension.

*/

#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double fabs(double x)
{
    uint32_t high;
    GET_HIGH_WORD(high, x);
    SET_HIGH_WORD(x, high & 0x7fffffff);
    return x;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double fabsl(long double x)
{
    return (long double) fabs((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
