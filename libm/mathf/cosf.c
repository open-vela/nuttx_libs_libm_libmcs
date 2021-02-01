/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>
#include "../common/tools.h"
#include "internal/trigf.h"

float cosf(float x)
{
    float y[2], z = 0.0;
    int32_t n, ix;

    GET_FLOAT_WORD(ix, x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;

    if (ix <= 0x3f490fd8) {
        return __cosf(x, z);
    }

    /* cos(Inf or NaN) is NaN */
    else if (!FLT_UWORD_IS_FINITE(ix)) {
        return x - x;
    }

    /* argument reduction needed */
    else {
        n = __rem_pio2f(x, y);

        switch (n & 3) {
        case 0:
            return  __cosf(y[0], y[1]);

        case 1:
            return -__sinf(y[0], y[1], 1);

        case 2:
            return -__cosf(y[0], y[1]);

        default:
            return  __sinf(y[0], y[1], 1);
        }
    }
}

#ifdef _DOUBLE_IS_32BITS

double cos(double x)
{
    return (double) cosf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
