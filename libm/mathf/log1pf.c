/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>
#include "../common/tools.h"
#include "internal/log1pmff.h"

static const float
ln2_hi = 6.9313812256e-01, /* 0x3f317180 */
ln2_lo = 9.0580006145e-06; /* 0x3717f7d1 */

static const float zero = 0.0;

float log1pf(float x)
{
    float hfsq, f, c, R, u;
    int32_t k, hx, hu, ax;

    GET_FLOAT_WORD(hx, x);
    ax = hx & 0x7fffffff;

    k = 1;

    if (!FLT_UWORD_IS_FINITE(hx)) { /* x = NaN/+-Inf */
        return x + x;
    }

    if (hx < 0x3ed413d7) {          /* x < 0.41422  */
        if (ax >= 0x3f800000) {     /* x <= -1.0 */
            if (x == (float) -1.0) {
                return __raise_div_by_zerof(-1.0f); /* log1p(-1)=-inf */
            } else {
                return __raise_invalidf();          /* log1p(x<-1)=NaN */
            }
        }

        if (ax < 0x31000000) {      /* |x| < 2**-29 */
            if (ax < 0x24800000) {  /* |x| < 2**-54 */
                return __raise_inexactf(x);
            } else {
                return __raise_inexactf(x - x * x * 0.5f);
            }
        }

        if (hx > 0 || hx <= ((int32_t)0xbe95f61fU)) {
            k = 0;
            f = x;
            hu = 1;
        }    /* -0.2929<x<0.41422 */
    }

    if (k != 0) {
        if (hx < 0x5a000000) {
            u  = (float)1.0 + x;
            GET_FLOAT_WORD(hu, u);
            k  = (hu >> 23) - 127;
            /* correction term */
            c  = (k > 0) ? (float)1.0 - (u - x) : x - (u - (float)1.0);
            c /= u;
        } else {
            u  = x;
            GET_FLOAT_WORD(hu, u);
            k  = (hu >> 23) - 127;
            c  = 0;
        }

        hu &= 0x007fffff;

        if (hu < 0x3504f7) {
            SET_FLOAT_WORD(u, hu | 0x3f800000); /* normalize u */
        } else {
            k += 1;
            SET_FLOAT_WORD(u, hu | 0x3f000000); /* normalize u/2 */
            hu = (0x00800000 - hu) >> 2;
        }

        f = u - (float)1.0;
    }

    hfsq = (float)0.5 * f * f;

    if (hu == 0) { /* |f| < 2**-20 */
        if (f == zero) {
            if (k == 0) {
                return zero;
            } else {
                c += k * ln2_lo;
                return k * ln2_hi + c;
            }
        }

        R = hfsq * ((float)1.0 - (float)0.66666666666666666 * f);

        if (k == 0) {
            return f - R;
        } else {
            return k * ln2_hi - ((R - (k * ln2_lo + c)) - f);
        }
    }

    if (k == 0) {
        return f - (hfsq - __log1pmff(f));
    } else {
        return k * ln2_hi - ((hfsq - (__log1pmff(f) + (k * ln2_lo + c))) - f);
    }
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double log1p(double x)
{
    return (double) log1pf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
