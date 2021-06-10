/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>
#include "../common/tools.h"

static const float zero = 0.0f;

float remainderf(float x, float p)
{
    int32_t hx, hp;
    uint32_t sx;
    float p_half;

    GET_FLOAT_WORD(hx, x);
    GET_FLOAT_WORD(hp, p);
    sx = hx & 0x80000000U;
    hp &= 0x7fffffff;
    hx &= 0x7fffffff;

    /* purge off exception values */
    if (FLT_UWORD_IS_NAN(hx) || FLT_UWORD_IS_NAN(hp)) {                 /* x or p is NaN */
        return x + p;
    } else if (FLT_UWORD_IS_ZERO(hp) || FLT_UWORD_IS_INFINITE(hx)) {    /* p is 0 or x is inf */
        return __raise_invalidf();
    } else {
        /* No action required */
    }

    if (hp <= FLT_UWORD_HALF_MAX) {
        x = fmodf(x, p + p);    /* now x < 2p */
    }

    if ((hx - hp) == 0) {
        return zero * x;
    }

    x  = fabsf(x);
    p  = fabsf(p);

    if (hp < 0x01000000) {
        if (x + x > p) {
            x -= p;

            if (x + x >= p) {
                x -= p;
            }
        }
    } else {
        p_half = 0.5f * p;

        if (x > p_half) {
            x -= p;

            if (x >= p_half) {
                x -= p;
            }
        }
    }

    GET_FLOAT_WORD(hx, x);
    SET_FLOAT_WORD(x, hx ^ sx);
    return x;
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double remainder(double x, double y)
{
    return (double) remainderf((float) x, (float) y);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
