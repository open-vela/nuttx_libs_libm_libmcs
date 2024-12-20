/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

/*
 * fmodf(x,y)
 * Return x mod y in exact arithmetic
 * Method: shift and subtract
 */

#include <math.h>
#include "../common/tools.h"

static const float Zero[] = {0.0f, -0.0f,};

float fmodf(float x, float y)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_onef;
    y *= __volatile_onef;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    int32_t n, hx, hy, hz, ix, iy, sx, i;

    GET_FLOAT_WORD(hx, x);
    GET_FLOAT_WORD(hy, y);
    sx = hx & 0x80000000U;      /* sign of x */
    hx ^= sx;                   /* |x| */
    hy &= 0x7fffffff;           /* |y| */

    /* purge off exception values */
    if (!FLT_UWORD_IS_FINITE(hx) || !FLT_UWORD_IS_FINITE(hy)) {     /* x or y is +-Inf/NaN */
        if (FLT_UWORD_IS_INFINITE(hx)) {                            /* x is +-Inf */
            return __raise_invalidf();
        } else if (FLT_UWORD_IS_NAN(hx) || FLT_UWORD_IS_NAN(hy)) {  /* x or y is NaN */
            return x + y;
        } else {
            /* No action required */
        }
    } else if (FLT_UWORD_IS_ZERO(hy)) {                             /* y is +-0 */
        return __raise_invalidf();
    } else {
        /* No action required */
    }

    if (hx < hy) {
        return x;    /* |x|<|y| return x */
    }

    if (hx == hy) {
        return Zero[(uint32_t)sx >> 31];    /* |x|=|y| return x*0*/
    }

    /* Note: y cannot be zero if we reach here. */

    /* determine ix = ilogb(x) */
    if (FLT_UWORD_IS_SUBNORMAL(hx)) {   /* subnormal x */
        for (ix = -126, i = (hx << 8); i > 0; i <<= 1) {
            ix -= 1;
        }
    } else {
        ix = (hx >> 23) - 127;
    }

    /* determine iy = ilogb(y) */
    if (FLT_UWORD_IS_SUBNORMAL(hy)) {   /* subnormal y */
        for (iy = -126, i = (hy << 8); i >= 0; i <<= 1) {
            iy -= 1;
        }
    } else {
        iy = (hy >> 23) - 127;
    }

    /* set up {hx,lx}, {hy,ly} and align y to x */
    if (ix >= -126) {
        hx = 0x00800000 | (0x007fffff & hx);
    } else {      /* subnormal x, shift x to normal */
        n = -126 - ix;
        hx = hx << n;
    }

    if (iy >= -126) {
        hy = 0x00800000 | (0x007fffff & hy);
    } else {      /* subnormal y, shift y to normal */
        n = -126 - iy;
        hy = hy << n;
    }

    /* fix point fmod */
    n = ix - iy;

    while (n-- > 0) {
        hz = hx - hy;

        if (hz < 0) {
            hx = hx + hx;
        } else {
            if (hz == 0) {    /* return sign(x)*0 */
                return Zero[(uint32_t)sx >> 31];
            }

            hx = hz + hz;
        }
    }

    hz = hx - hy;

    if (hz >= 0) {
        hx = hz;
    }

    /* convert back to floating value and restore the sign */
    if (hx == 0) {        /* return sign(x)*0 */
        return Zero[(uint32_t)sx >> 31];
    }

    while (hx < 0x00800000) {     /* normalize x */
        hx = hx + hx;
        iy -= 1;
    }

    if (iy >= -126) {      /* normalize output */
        hx = ((hx - 0x00800000) | ((iy + 127) << 23));
        SET_FLOAT_WORD(x, hx | sx);
    } else {        /* subnormal output */
        n = -126 - iy;
        hx >>= n;
        SET_FLOAT_WORD(x, hx | sx);
#ifdef __LIBMCS_FPU_DAZ
        x *= __volatile_onef;
#endif /* defined(__LIBMCS_FPU_DAZ) */
    }

    return x;        /* exact output */
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double fmod(double x, double y)
{
    return (double) fmodf((float) x, (float) y);
}

#endif /* #ifdef __LIBMCS_DOUBLE_IS_32BITS */
