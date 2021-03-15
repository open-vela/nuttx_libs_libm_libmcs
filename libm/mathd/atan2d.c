/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/* __atan2(y,x)
 * Method :
 *    1. Reduce y to positive by atan2(y,x)=-atan2(-y,x).
 *    2. Reduce x to positive by (if x and y are unexceptional):
 *        ARG (x+iy) = arctan(y/x)          ... if x > 0,
 *        ARG (x+iy) = pi - arctan[y/(-x)]   ... if x < 0,
 *
 * Special cases:
 *
 *    ATAN2((anything), NaN ) is NaN;
 *    ATAN2(NAN , (anything) ) is NaN;
 *    ATAN2(+-0, +(anything but NaN)) is +-0  ;
 *    ATAN2(+-0, -(anything but NaN)) is +-pi ;
 *    ATAN2(+-(anything but 0 and NaN), 0) is +-pi/2;
 *    ATAN2(+-(anything but INF and NaN), +INF) is +-0 ;
 *    ATAN2(+-(anything but INF and NaN), -INF) is +-pi;
 *    ATAN2(+-INF,+INF ) is +-pi/4 ;
 *    ATAN2(+-INF,-INF ) is +-3pi/4;
 *    ATAN2(+-INF, (anything but,0,NaN, and INF)) is +-pi/2;
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following
 * constants. The decimal values may be used, provided that the
 * compiler will convert from decimal to binary accurately enough
 * to produce the hexadecimal values shown.
 */

/*
FUNCTION
        <<atan2>>, <<atan2f>>---arc tangent of y/x

INDEX
   atan2
INDEX
   atan2f

SYNOPSIS
        #include <math.h>
        double atan2(double <[y]>,double <[x]>);
        float atan2f(float <[y]>,float <[x]>);

DESCRIPTION

<<atan2>> computes the inverse tangent (arc tangent) of <[y]>/<[x]>.
<<atan2>> produces the correct result even for angles near
@ifnottex
pi/2 or -pi/2
@end ifnottex
@tex
$\pi/2$ or $-\pi/2$
@end tex
(that is, when <[x]> is near 0).

<<atan2f>> is identical to <<atan2>>, save that it takes and returns
<<float>>.

RETURNS
<<atan2>> and <<atan2f>> return a value in radians, in the range of
@ifnottex
-pi to pi.
@end ifnottex
@tex
$-\pi$ to $\pi$.
@end tex

PORTABILITY
<<atan2>> is ANSI C.  <<atan2f>> is an extension.

*/

#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

static const double
tiny    = 1.0e-300,
zero    = 0.0,
pi_o_4  = 7.8539816339744827900E-01, /* 0x3FE921FB, 0x54442D18 */
pi_o_2  = 1.5707963267948965580E+00, /* 0x3FF921FB, 0x54442D18 */
pi      = 3.1415926535897931160E+00, /* 0x400921FB, 0x54442D18 */
pi_lo   = 1.2246467991473531772E-16; /* 0x3CA1A626, 0x33145C07 */

double atan2(double y, double x)
{
    double z;
    int32_t k, m, hx, hy, ix, iy;
    uint32_t lx, ly;

    EXTRACT_WORDS(hx, lx, x);
    ix = hx & 0x7fffffff;
    EXTRACT_WORDS(hy, ly, y);
    iy = hy & 0x7fffffff;

    if (((ix | ((lx | -lx) >> 31)) > 0x7ff00000) ||
        ((iy | ((ly | -ly) >> 31)) > 0x7ff00000)) { /* x or y is NaN */
        return x + y;
    }

    if (((hx - 0x3ff00000) | lx) == 0) {
        return atan(y);    /* x=1.0 */
    }

    m = ((hy >> 31) & 1) | ((hx >> 30) & 2); /* 2*sign(x)+sign(y) */

    /* when y = 0 */
    if ((iy | ly) == 0) {
        switch (m) {
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
    if ((ix | lx) == 0) {
        return (hy < 0) ?  -pi_o_2 - tiny : pi_o_2 + tiny;
    }

    /* when x is INF */
    if (ix == 0x7ff00000) {
        if (iy == 0x7ff00000) {
            switch (m) {
            case 0:
                return  pi_o_4 + tiny;       /* atan(+INF,+INF) */

            case 1:
                return -pi_o_4 - tiny;       /* atan(-INF,+INF) */

            case 2:
                return  3.0 * pi_o_4 + tiny; /* atan(+INF,-INF) */

            case 3:
                return -3.0 * pi_o_4 - tiny; /* atan(-INF,-INF) */
            }
        } else {
            switch (m) {
            case 0:
                return  zero;      /* atan(+...,+INF) */

            case 1:
                return -zero;      /* atan(-...,+INF) */

            case 2:
                return  pi + tiny; /* atan(+...,-INF) */

            case 3:
                return -pi - tiny; /* atan(-...,-INF) */
            }
        }
    }

    /* when y is INF */
    if (iy == 0x7ff00000) {
        return (hy < 0) ? -pi_o_2 - tiny : pi_o_2 + tiny;
    }

    /* compute y/x */
    k = (iy - ix) >> 20;

    if (k > 60) {
        z = pi_o_2 + 0.5 * pi_lo;  /* |y/x| >  2**60 */
    } else if (hx < 0 && k < -60) {
        z = 0.0;                   /* |y|/x < -2**60 */
    } else {
        z = atan(fabs(y / x));     /* safe to do y/x */
    }

    switch (m) {
    case 0:
        return  z;                 /* atan(+,+) */

    case 1:
        {
            uint32_t zh;
            GET_HIGH_WORD(zh, z);
            SET_HIGH_WORD(z, zh ^ 0x80000000);
        }
        return  z;                 /* atan(-,+) */

    case 2:
        return  pi - (z - pi_lo);  /* atan(+,-) */

    default: /* case 3 */
        return (z - pi_lo) - pi;   /* atan(-,-) */
    }
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double atan2l(long double y, long double x)
{
    return (long double) atan2((double) y, (double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
