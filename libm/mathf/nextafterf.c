/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>
#include "../common/tools.h"

float nextafterf(float x, float y)
{
    int32_t hx, hy, ix, iy;

    GET_FLOAT_WORD(hx, x);
    GET_FLOAT_WORD(hy, y);
    ix = hx & 0x7fffffff;      /* |x| */
    iy = hy & 0x7fffffff;      /* |y| */

    if (FLT_UWORD_IS_NAN(ix) || FLT_UWORD_IS_NAN(iy)) {
        return x + y;
    } else if (hx == hy) {
        return x;                      /* x=y, return x */
    } else if (ix == 0) {              /* x == 0 */
        if (ix == iy) {
            return x;                  /* x=y, return x */
        }
        SET_FLOAT_WORD(x, (hy & 0x80000000U) | 1U);
        (void) __raise_underflowf(x);
        return x;
    } else if (hx >= 0) {              /* x > 0 */
        if (hx > hy) {                 /* x > y, x -= ulp */
            hx -= 1;
        } else {                       /* x < y, x += ulp */
            hx += 1;
        }
    } else {                           /* x < 0 */
        if (hy >= 0 || hx > hy) {      /* x < y, x -= ulp */
            hx -= 1;
        } else {                       /* x > y, x += ulp */
            hx += 1;
        }
    }

    hy = hx & 0x7f800000;

    if (hy > FLT_UWORD_MAX) {
        return __raise_overflowf(x);  /* overflow if x is finite */
    }

    if (hy < 0x00800000) {            /* underflow */
        (void) __raise_underflowf(x);
    }

    SET_FLOAT_WORD(x, hx);
    return x;
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double nextafter(double x, double y)
{
    return (double) nextafterf((float) x, (float) y);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
