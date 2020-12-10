// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.

/*
FUNCTION
    <<exp2>>, <<exp2f>>---exponential, base 2
INDEX
    exp2
INDEX
    exp2f

SYNOPSIS
    #include <math.h>
    double exp2(double <[x]>);
    float exp2f(float <[x]>);

DESCRIPTION
    <<exp2>> and <<exp2f>> calculate 2 ^ <[x]>, that is, 
    @ifnottex
    2 raised to the power <[x]>.
    @end ifnottex
    @tex
    $2^x$
    @end tex

RETURNS
    On success, <<exp2>> and <<exp2f>> return the calculated value.
    If the result underflows, the returned value is <<0>>.  If the
    result overflows, the returned value is <<HUGE_VAL>>.  In
    either case, <<errno>> is set to <<ERANGE>>.

PORTABILITY
    ANSI C, POSIX.

*/

#include "fdlibm.h"
#include <math.h>

#ifndef _DOUBLE_IS_32BITS

double exp2(double x)
{
    return pow(2.0, x);
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double exp2l (long double x)
{
    return (long double) exp2((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
