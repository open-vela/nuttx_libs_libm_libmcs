/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>
#include "../common/tools.h"

float ceilf(float x)
{
    int32_t i0, j0;
    uint32_t i, ix;
    GET_FLOAT_WORD(i0, x);
    ix = (i0 & 0x7fffffff);
    j0 = (ix >> 23) - 0x7f;

    if (j0 < 23) {
        if (j0 < 0) {  /* raise inexact if x != 0 */
            if (FLT_UWORD_IS_ZERO(ix)) {
                return x;
            }

            (void) __raise_inexactf(x); /* raise inexact flag */

            if (i0 < 0) {
                i0 = (int32_t)0x80000000U;
            } else {
                i0 = 0x3f800000;
            }
        } else {
            i = (0x007fffff) >> j0;

            if ((i0 & i) == 0) {
                return x;    /* x is integral */
            }

            (void) __raise_inexactf(x); /* raise inexact flag */

            if (i0 > 0) {
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

double ceil(double x)
{
    return (double) ceilf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
