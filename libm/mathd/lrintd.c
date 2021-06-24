/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*
FUNCTION
<<lrint>>, <<lrintf>>, <<llrint>>, <<llrintf>>---round to integer
INDEX
    lrint
INDEX
    lrintf
INDEX
    llrint
INDEX
    llrintf

SYNOPSIS
    #include <math.h>
    long int lrint(double <[x]>);
    long int lrintf(float <[x]>);
    long long int llrint(double <[x]>);
    long long int llrintf(float <[x]>);

DESCRIPTION
The <<lrint>> and <<llrint>> functions round their argument to the nearest
integer value, using the current rounding direction.  If the rounded value is
outside the range of the return type, the numeric result is unspecified.  A
range error may occur if the magnitude of <[x]> is too large.
The "inexact" floating-point exception is raised in implementations that
support it when the result differs in value from the argument (i.e., when
a fraction actually has been truncated).

RETURNS
<[x]> rounded to an integral value, using the current rounding direction.

SEEALSO
<<lround>>

PORTABILITY
ANSI C, POSIX

*/

/*
 * lrint(x)
 * Return x rounded to integral value according to the prevailing
 * rounding mode.
 * Method:
 *    Using floating addition.
 * Exception:
 *    Inexact flag raised if x not equal to lrint(x).
 */

#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

/* Adding a double, x, to 2^52 will cause the result to be rounded based on
   the fractional part of x, according to the implementation's current rounding
   mode.  2^52 is the smallest double that can be represented using all 52 significant
   digits. */
static const double TWO52[2] = {
     4.50359962737049600000e+15, /* 0x43300000, 0x00000000 */
    -4.50359962737049600000e+15, /* 0xC3300000, 0x00000000 */
};

long int lrint(double x)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    int32_t _i0, _j0, sx;
    uint32_t i1;
    double t;
    volatile double w;
    long int result;

    EXTRACT_WORDS(_i0, i1, x);

    /* Extract sign bit. */
    sx = (_i0 >> 31) & 1;

    /* Extract exponent field. */
    _j0 = ((_i0 & 0x7ff00000) >> 20) - 1023;
    /* _j0 in [-1023,1024] */

    if (_j0 < 20) {
        /* _j0 in [-1023,19] */
        if (_j0 < -1) {
            return 0;
        } else {
            /* _j0 in [0,19] */
            /* shift amt in [0,19] */
            w = TWO52[sx] + x;
            t = w - TWO52[sx];
            GET_HIGH_WORD(_i0, t);

            /* Detect the all-zeros representation of plus and
               minus zero, which fails the calculation below. */
            if ((_i0 & ~(1U << 31)) == 0) {
                return 0;
            }

            /* After round:  _j0 in [0,20] */
            _j0 = ((_i0 & 0x7ff00000) >> 20) - 1023;
            _i0 &= 0x000fffff;
            _i0 |= 0x00100000;
            /* shift amt in [20,0] */
            result = _i0 >> (20 - _j0);
        }
    } else if ((uint32_t)_j0 < (8 * sizeof(long int)) - 1) {
        /* 32bit return: _j0 in [20,30] */
        /* 64bit return: _j0 in [20,62] */
        if (_j0 >= 52) {
            /* 64bit return: _j0 in [52,62] */
            /* 64bit return: left shift amt in [32,42] */
            result = ((long int)((_i0 & 0x000fffff) | 0x00100000) << (_j0 - 20)) |
                     /* 64bit return: right shift amt in [0,10] */
                     ((long int) i1 << (_j0 - 52));
        } else {
            /* 32bit return: _j0 in [20,30] */
            /* 64bit return: _j0 in [20,51] */
            w = TWO52[sx] + x;
            t = w - TWO52[sx];
            EXTRACT_WORDS(_i0, i1, t);
            _j0 = ((_i0 & 0x7ff00000) >> 20) - 1023;
            _i0 &= 0x000fffff;
            _i0 |= 0x00100000;
            /* After round:
            * 32bit return: _j0 in [20,31];
            * 64bit return: _j0 in [20,52] */
            /* 32bit return: left shift amt in [0,11] */
            /* 64bit return: left shift amt in [0,32] */
            /* ***32bit return: right shift amt in [32,21] */
            /* ***64bit return: right shift amt in [32,0] */
            result = ((long int) _i0 << (_j0 - 20)) | SAFE_RIGHT_SHIFT(i1, (uint32_t)(52 - _j0));
        }
    } else {
        (void) __raise_invalid();
        if (sx != 0) {
            return __MIN_LONG;
        }
        else {
            return __MAX_LONG;
        }
    }

    return (sx != 0) ? -result : result;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long int lrintl(long double x)
{
    return lrint((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
