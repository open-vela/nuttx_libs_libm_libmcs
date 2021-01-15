/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <limits.h>
#include "tools.h"

int ilogbf(float x)
{
    int32_t hx, ix;

    GET_FLOAT_WORD(hx, x);
    hx &= 0x7fffffff;

    if (FLT_UWORD_IS_ZERO(hx)) {
        return FP_ILOGB0;    /* ilogb(0) = special case error */
    }

    if (FLT_UWORD_IS_SUBNORMAL(hx)) {
        for (ix = -126, hx <<= 8; hx > 0; hx <<= 1) {
            ix -= 1;
        }

        return ix;
    }

#if FP_ILOGBNAN != INT_MAX
    else if (FLT_UWORD_IS_NAN(hx)) {
        return FP_ILOGBNAN;    /* NAN */
    }

#endif
    else if (!FLT_UWORD_IS_FINITE(hx)) {
        return INT_MAX;
    } else {
        return (hx >> 23) - 127;
    }
}

#ifdef _DOUBLE_IS_32BITS

int ilogb(double x)
{
    return ilogbf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
