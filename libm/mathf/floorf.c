/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

/*
 * floorf(x)
 * Return x rounded toward -inf to integral value
 * Method:
 *    Bit twiddling.
 * Exception:
 *    Inexact flag raised if x not equal to floorf(x).
 */

#include <math.h>
#include "../common/tools.h"

float floorf(float x)
{
    int32_t i0, j0;
    uint32_t i, ix;
    GET_FLOAT_WORD(i0, x);
    ix = (i0 & 0x7fffffff);
    j0 = (ix >> 23) - 0x7f;

    if (j0 < 23) {
        if (j0 < 0) {  /* raise inexact if x != 0 */
            (void) __raise_inexactf(x);

            if (i0 >= 0) {
                i0 = 0;
            } else if (!FLT_UWORD_IS_ZERO(ix)) {
                i0 = (int32_t)0xbf800000;
            }
        } else {
            i = (0x007fffff) >> j0;

            if ((i0 & i) == 0) {    /* x is integral */
                return x;
            }

            (void) __raise_inexactf(x);
            
            if (i0 < 0) {
                i0 += (0x00800000) >> j0;
            }

            i0 &= (~i);
        }
    } else {
        if (!FLT_UWORD_IS_FINITE(ix)) {
            return x + x;    /* inf or NaN */
        } else {
            return x;    /* x is integral */
        }
    }

    SET_FLOAT_WORD(x, i0);
    return x;
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double floor(double x)
{
    return (double) floorf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
