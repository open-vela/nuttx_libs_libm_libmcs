/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*
FUNCTION
       <<ldexp>>, <<ldexpf>>---load exponent

INDEX
    ldexp
INDEX
    ldexpf

SYNOPSIS
       #include <math.h>
       double ldexp(double <[val]>, int <[exp]>);
       float ldexpf(float <[val]>, int <[exp]>);

DESCRIPTION
<<ldexp>> calculates the value
@ifnottex
<[val]> times 2 to the power <[exp]>.
@end ifnottex
@tex
$val\times 2^{exp}$.
@end tex
<<ldexpf>> is identical, save that it takes and returns <<float>>
rather than <<double>> values.

RETURNS
<<ldexp>> returns the calculated value.

Underflow and overflow both set <<errno>> to <<ERANGE>>.
On underflow, <<ldexp>> and <<ldexpf>> return 0.0.
On overflow, <<ldexp>> returns plus or minus <<HUGE_VAL>>.

PORTABILITY
<<ldexp>> is ANSI. <<ldexpf>> is an extension.

*/

#include <math.h>

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double ldexp(double value, int exp)
{
    if (!isfinite(value) || value == 0.0) {
        return value;
    }

    value = scalbn(value, exp);
    return value;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double ldexpl(long double value, int exp)
{
    return (long double) ldexp((double) value, exp);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
