/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>
#include "../common/tools.h"

static const float
tiny    =  1.0e-30f,
zero    =  0.0f,
pi_o_4  =  7.8539818525e-01f, /* 0x3f490fdb */
pi_o_2  =  1.5707963705e+00f, /* 0x3fc90fdb */
pi      =  3.1415927410e+00f, /* 0x40490fdb */
pi_lo   = -8.7422776573e-08f; /* 0xb3bbbd2e */

float atan2f(float y, float x)
{
    float z;
    int32_t k, m, hx, hy, ix, iy;

    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;
    GET_FLOAT_WORD(hy, y);
    iy = hy & 0x7fffffff;

    if (FLT_UWORD_IS_NAN(ix) ||
        FLT_UWORD_IS_NAN(iy)) {  /* x or y is NaN */
        return x + y;
    }

    if (hx == 0x3f800000) {
        return atanf(y);    /* x=1.0 */
    }

    m = ((hy >> 31) & 1) | ((hx >> 30) & 2); /* 2*sign(x)+sign(y) */

    /* when y = 0 */
    if (FLT_UWORD_IS_ZERO(iy)) {
        switch (m) {
        default:
        case 0:
        case 1:
            return y;          /* atan(+-0,+anything)=+-0 */

        case 2:
            return  pi + tiny; /* atan(+0,-anything) = pi */

        case 3:
            return -pi - tiny; /* atan(-0,-anything) =-pi */
        }
    }

    /* when x = 0 */
    if (FLT_UWORD_IS_ZERO(ix)) {
        return (hy < 0) ?  -pi_o_2 - tiny : pi_o_2 + tiny;
    }

    /* when x is INF */
    if (FLT_UWORD_IS_INFINITE(ix)) {
        if (FLT_UWORD_IS_INFINITE(iy)) {
            switch (m) {
            default:
            case 0:
                return  pi_o_4 + tiny;               /* atan(+INF,+INF) */

            case 1:
                return -pi_o_4 - tiny;               /* atan(-INF,+INF) */

            case 2:
                return 3.0f * pi_o_4 + tiny;   /*atan(+INF,-INF)*/

            case 3:
                return -3.0f * pi_o_4 - tiny; /*atan(-INF,-INF)*/
            }
        } else {
            switch (m) {
            default:
            case 0:
                return  zero  ;                      /* atan(+...,+INF) */

            case 1:
                return -zero  ;                      /* atan(-...,+INF) */

            case 2:
                return  pi + tiny  ;                 /* atan(+...,-INF) */

            case 3:
                return -pi - tiny  ;                 /* atan(-...,-INF) */
            }
        }
    }

    /* when y is INF */
    if (FLT_UWORD_IS_INFINITE(iy)) {
        return (hy < 0) ? -pi_o_2 - tiny : pi_o_2 + tiny;
    }

    /* compute y/x */
    k = (iy - ix) >> 23;

    if (k > 26) {
        z = pi_o_2 + 0.5f * pi_lo;    /* |y/x| >  2**26 */
        m &= 1;
    } else if (hx < 0 && k < -26) {
        z = 0.0f;    /* 0 > |y|/x > -2**26 */
    } else {
        z = atanf(fabsf(y / x));    /* safe to do y/x */
    }

    switch (m) {
    case 0:
        return       z  ;         /* atan(+,+) */

    case 1:
        return      -z  ;         /* atan(-,+) */

    case 2:
        return  pi - (z - pi_lo); /* atan(+,-) */

    default: /* case 3 */
        return (z - pi_lo) - pi;  /* atan(-,-) */
    }
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double atan2(double y, double x)
{
    return (double) atan2f((float) y, (float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
