/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*
FUNCTION
       <<ilogb>>, <<ilogbf>>---get exponent of floating-point number
INDEX
    ilogb
INDEX
    ilogbf

SYNOPSIS
    #include <math.h>
        int ilogb(double <[val]>);
        int ilogbf(float <[val]>);

DESCRIPTION

    All nonzero, normal numbers can be described as <[m]> *
    2**<[p]>.  <<ilogb>> and <<ilogbf>> examine the argument
    <[val]>, and return <[p]>.  The functions <<frexp>> and
    <<frexpf>> are similar to <<ilogb>> and <<ilogbf>>, but also
    return <[m]>.

RETURNS

<<ilogb>> and <<ilogbf>> return the power of two used to form the
floating-point argument.
If <[val]> is <<0>>, they return <<FP_ILOGB0>>.
If <[val]> is infinite, they return <<INT_MAX>>.
If <[val]> is NaN, they return <<FP_ILOGBNAN>>.
(<<FP_ILOGB0>> and <<FP_ILOGBNAN>> are defined in math.h, but in turn are
defined as INT_MIN or INT_MAX from limits.h.  The value of FP_ILOGB0 may be
either INT_MIN or -INT_MAX.  The value of FP_ILOGBNAN may be either INT_MAX or
INT_MIN.)

@comment The bugs might not be worth noting, given the mass non-C99/POSIX
@comment behavior of much of the Newlib math library.
@comment BUGS
@comment On errors, errno is not set per C99 and POSIX requirements even if
@comment (math_errhandling & MATH_ERRNO) is non-zero.

PORTABILITY
C99, POSIX
*/

/* ilogb(double x)
 * return the binary exponent of non-zero x
 * ilogb(0) = 0x80000001
 * ilogb(inf/NaN) = 0x7fffffff (no signal is raised)
 */

#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

int ilogb(double x)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    int32_t hx, lx, ix;

    EXTRACT_WORDS(hx, lx, x);
    hx &= 0x7fffffff;

    if (hx < 0x00100000) {
        if ((hx | lx) == 0) {
            (void) __raise_invalid();
            return FP_ILOGB0;    /* ilogb(0) = special case error */
        } else {         /* subnormal x */
            if (hx == 0) {
                for (ix = -1043; lx > 0; lx <<= 1) {
                    ix -= 1;
                }
            } else {
                for (ix = -1022, hx <<= 11; hx > 0; hx <<= 1) {
                    ix -= 1;
                }
            }
        }

        return ix;
    } else if (hx < 0x7ff00000) {
        return (hx >> 20) - 1023;
    } else if (hx > 0x7ff00000) {
        (void) __raise_invalid();
        return FP_ILOGBNAN;     /* NAN */
    } else {
        (void) __raise_invalid();
        return INT_MAX;         /* infinite */
    }
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

int ilogbl(long double x)
{
    return ilogb((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
