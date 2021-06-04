/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*
FUNCTION
       <<modf>>, <<modff>>---split fractional and integer parts

INDEX
    modf
INDEX
    modff

SYNOPSIS
    #include <math.h>
    double modf(double <[val]>, double *<[ipart]>);
        float modff(float <[val]>, float *<[ipart]>);

DESCRIPTION
    <<modf>> splits the double <[val]> apart into an integer part
    and a fractional part, returning the fractional part and
    storing the integer part in <<*<[ipart]>>>.  No rounding
    whatsoever is done; the sum of the integer and fractional
    parts is guaranteed to be exactly  equal to <[val]>.   That
    is, if <[realpart]> = modf(<[val]>, &<[intpart]>); then
    `<<<[realpart]>+<[intpart]>>>' is the same as <[val]>.
    <<modff>> is identical, save that it takes and returns
    <<float>> rather than <<double>> values.

RETURNS
    The fractional part is returned.  Each result has the same
    sign as the supplied argument <[val]>.

PORTABILITY
    <<modf>> is ANSI C. <<modff>> is an extension.

QUICKREF
    modf  ansi pure
    modff - pure

*/

/*
 * modf(double x, double *iptr)
 * return fraction part of x, and return x's integral part in *iptr.
 * Method:
 *    Bit twiddling.
 *
 * Exception:
 *    No exception.
 */

#include <assert.h>
#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double modf(double x, double *iptr)
{
    double _xi = 0.0;
    int32_t i0, i1, j0;
    uint32_t i;

	assert(iptr != (void*)0);
	if(iptr == (void*)0) {
	    iptr = &_xi;
	}

    EXTRACT_WORDS(i0, i1, x);
    j0 = ((i0 >> 20) & 0x7ff) - 0x3ff;                 /* exponent of x */

    if (j0 < 20) {                                     /* integer part in high x */
        if (j0 < 0) {                                  /* |x|<1 */
            INSERT_WORDS(*iptr, i0 & 0x80000000U, 0U); /* *iptr = +-0 */
            return x;
        } else {
            i = (0x000fffff) >> j0;

            if (((i0 & i) | i1) == 0) {                /* x is integral */
                *iptr = x;
                INSERT_WORDS(x, i0 & 0x80000000U, 0U); /* return +-0 */
                return x;
            } else {
                INSERT_WORDS(*iptr, i0 & (~i), 0);
                return x - *iptr;
            }
        }
    } else if (j0 > 51) {                              /* no fraction part */
        *iptr = x;

        if (isnan(x)) {
            return *iptr = x + x;                      /* x is NaN, return NaN */
        }

        INSERT_WORDS(x, i0 & 0x80000000U, 0U);         /* return +-0 */
        return x;
    } else {                                           /* fraction part in low x */
        i = ((uint32_t)(0xffffffffU)) >> (j0 - 20);

        if ((i1 & i) == 0) {                           /* x is integral */
            *iptr = x;
            INSERT_WORDS(x, i0 & 0x80000000U, 0U);     /* return +-0 */
            return x;
        } else {
            INSERT_WORDS(*iptr, i0, i1 & (~i));
            return x - *iptr;
        }
    }
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double modfl(long double x, long double *iptr)
{
    return (long double) modf((double) x, (long double *) iptr);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
