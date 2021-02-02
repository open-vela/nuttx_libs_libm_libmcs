/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/* __tan( x, y, k )
 * internal tan function on [-pi/4, pi/4], pi/4 ~ 0.7854
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 * Input k indicates whether tan (if k=1) or
 * -1/tan (if k= -1) is returned.
 *
 * Algorithm
 *    1. Since tan(-x) = -tan(x), we need only to consider positive x.
 *    2. if x < 2^-28 (hx<0x3e300000 0), return x with inexact if x!=0.
 *    3. tan(x) is approximated by a odd polynomial of degree 27 on
 *       [0,0.67434]
 *                       3             27
 *           tan(x) ~ x + T1*x + ... + T13*x
 *       where
 *
 *             |tan(x)         2     4            26   |     -59.2
 *             |----- - (1+T1*x +T2*x +.... +T13*x    )| <= 2
 *             |  x                     |
 *
 *       Note: tan(x+y) = tan(x) + tan'(x)*y
 *                  ~ tan(x) + (1+x*x)*y
 *       Therefore, for better accuracy in computing tan(x+y), let
 *             3      2      2       2       2
 *        r = x *(T2+x *(T3+x *(...+x *(T12+x *T13))))
 *       then
 *                     3    2
 *        tan(x+y) = x + (T1*x + (x *(r+y)+y))
 *
 *      4. For x in [0.67434,pi/4],  let y = pi/4 - x, then
 *        tan(x) = tan(pi/4-y) = (1-tan(y))/(1+tan(y))
 *               = 1 - 2*(tan(y) - (tan(y)^2)/(1+tan(y)))
 */

/*

FUNCTION
        <<tan>>, <<tanf>>---tangent

INDEX
tan
INDEX
tanf

SYNOPSIS
        #include <math.h>
        double tan(double <[x]>);
        float tanf(float <[x]>);

DESCRIPTION
<<tan>> computes the tangent of the argument <[x]>.
Angles are specified in radians.

<<tanf>> is identical, save that it takes and returns <<float>> values.

RETURNS
The tangent of <[x]> is returned.

PORTABILITY
<<tan>> is ANSI. <<tanf>> is an extension.
*/

/* tan(x)
 * Return tangent function of x.
 *
 * internal function:
 *    __tan        ... tangent function on [-pi/4,pi/4]
 *    __rem_pio2    ... argument reduction routine
 *
 * Method.
 *      Let S,C and T denote the sin, cos and tan respectively on
 *    [-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2
 *    in [-pi/4 , +pi/4], and let n = k mod 4.
 *    We have
 *
 *          n        sin(x)      cos(x)        tan(x)
 *     ----------------------------------------------------------
 *        0           S       C         T
 *        1           C      -S        -1/T
 *        2          -S      -C         T
 *        3          -C       S        -1/T
 *     ----------------------------------------------------------
 *
 * Special cases:
 *      Let trig be any of sin, cos, or tan.
 *      trig(+-INF)  is NaN, with signals;
 *      trig(NaN)    is that NaN;
 *
 * Accuracy:
 *    TRIG(x) returns trig(x) nearly rounded
 */

#include <math.h>
#include "../common/tools.h"
#include "internal/trigd.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

static const double
one    =  1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
pio4   =  7.85398163397448278999e-01, /* 0x3FE921FB, 0x54442D18 */
pio4lo =  3.06161699786838301793e-17, /* 0x3C81A626, 0x33145C07 */
T[] =  {
     3.33333333333334091986e-01, /* 0x3FD55555, 0x55555563 */
     1.33333333333201242699e-01, /* 0x3FC11111, 0x1110FE7A */
     5.39682539762260521377e-02, /* 0x3FABA1BA, 0x1BB341FE */
     2.18694882948595424599e-02, /* 0x3F9664F4, 0x8406D637 */
     8.86323982359930005737e-03, /* 0x3F8226E3, 0xE96E8493 */
     3.59207910759131235356e-03, /* 0x3F6D6D22, 0xC9560328 */
     1.45620945432529025516e-03, /* 0x3F57DBC8, 0xFEE08315 */
     5.88041240820264096874e-04, /* 0x3F4344D8, 0xF2F26501 */
     2.46463134818469906812e-04, /* 0x3F3026F7, 0x1A8D1068 */
     7.81794442939557092300e-05, /* 0x3F147E88, 0xA03792A6 */
     7.14072491382608190305e-05, /* 0x3F12B80F, 0x32F0A7E9 */
    -1.85586374855275456654e-05, /* 0xBEF375CB, 0xDB605373 */
     2.59073051863633712884e-05, /* 0x3EFB2A70, 0x74BF7AD4 */
};

double __tan(double x, double y, int iy)
{
    double z, r, v, w, s;
    int32_t ix, hx;
    GET_HIGH_WORD(hx, x);
    ix = hx & 0x7fffffff;  /* high word of |x| */

    if (ix < 0x3e300000) {         /* x < 2**-28 */
        if ((int)x == 0) {         /* generate inexact */
            uint32_t low;
            GET_LOW_WORD(low, x);

            if (((ix | low) | (iy + 1)) == 0) {
                return one / fabs(x);
            } else {
                if (iy == 1) {
                    return x;
                } else {
                    double a, t;
                    z = w = x + y;
                    SET_LOW_WORD(z, 0);
                    v = y - (z - x);
                    t = a = -one / w;
                    SET_LOW_WORD(t, 0);
                    s = one + t * z;
                    return t + a * (s + t * v);
                }
            }
        }
    }

    if (ix >= 0x3FE59428) {          /* |x|>=0.6744 */
        if (hx < 0) {
            x = -x;
            y = -y;
        }

        z = pio4 - x;
        w = pio4lo - y;
        x = z + w;
        y = 0.0;
    }

    z    =  x * x;
    w     =  z * z;
    /* Break x^5*(T[1]+x^2*T[2]+...) into
     *      x^5(T[1]+x^4*T[3]+...+x^20*T[11]) +
     *      x^5(x^2*(T[2]+x^4*T[4]+...+x^22*[T12]))
     */
    r = T[1] + w * (T[3] + w * (T[5] + w * (T[7] + w * (T[9] + w * T[11]))));
    v = z * (T[2] + w * (T[4] + w * (T[6] + w * (T[8] + w * (T[10] + w * T[12])))));
    s = z * x;
    r = y + z * (s * (r + v) + y);
    r += T[0] * s;
    w = x + r;

    if (ix >= 0x3FE59428) {
        v = (double)iy;
        return (double)(1 - ((hx >> 30) & 2)) * (v - 2.0 * (x - (w * w / (w + v) - r)));
    }

    if (iy == 1) {
        return w;
    } else {
        /* if allow error up to 2 ulp, simply return -1.0/(x+r) here */
        /*  compute -1.0/(x+r) accurately */
        double a, t;
        z  = w;
        SET_LOW_WORD(z, 0);
        v  = r - (z - x);   /* z+v = r+x */
        t = a  = -1.0 / w;  /* a = -1.0/w */
        SET_LOW_WORD(t, 0);
        s  = 1.0 + t * z;
        return t + a * (s + t * v);
    }
}

double tan(double x)
{
    double y[2], z = 0.0;
    int32_t n, ix;

    /* High word of x. */
    GET_HIGH_WORD(ix, x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;

    if (ix <= 0x3fe921fb) {
        return __tan(x, z, 1);
    }

    /* tan(Inf or NaN) is NaN */
    else if (ix >= 0x7ff00000) {
        return x - x;    /* NaN */
    }

    /* argument reduction needed */
    else {
        n = __rem_pio2(x, y);
        return __tan(y[0], y[1], 1 - ((n & 1) << 1)); /*   1 -- n even, -1 -- n odd */
    }
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double tanl(long double x)
{
    return (long double) tan((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
