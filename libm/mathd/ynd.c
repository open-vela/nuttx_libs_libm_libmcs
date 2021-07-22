/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*
 * wrapper jn(int n, double x), yn(int n, double x)
 * floating point Bessel's function of the 1st and 2nd kind
 * of order n
 *
 * Special cases:
 *    y0(0)=y1(0)=yn(n,0) = -inf with division by zero signal;
 *    y0(-ve)=y1(-ve)=yn(n,-ve) are NaN with invalid signal.
 * Note 2. About jn(n,x), yn(n,x)
 *    For n=0, j0(x) is called,
 *    for n=1, j1(x) is called,
 *    for n<x, forward recursion us used starting
 *    from values of j0(x) and j1(x).
 *    for n>x, a continued fraction approximation to
 *    j(n,x)/j(n-1,x) is evaluated and then backward
 *    recursion is used starting from a supposed value
 *    for j(n,x). The resulting value of j(0,x) is
 *    compared with the actual value to correct the
 *    supposed value of j(n,x).
 *
 *    yn(n,x) is similar in all respects, except
 *    that forward recursion is used for all
 *    values of n>1.
 *
 */

#include <math.h>
#include "internal/besseld.h"
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double yn(int n, double x)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    int32_t i, hx, ix, lx;
    int32_t sign;
    double a, b, temp;

    EXTRACT_WORDS(hx, lx, x);
    ix = 0x7fffffff & hx;

    /* if Y(n,NaN) is NaN */
    if (isnan(x)) {         /* yn(n,NaN) = NaN */
        return x + x;
    }

    if ((ix | lx) == 0) {   /* yn(n,+-0) = +Inf */
        return __raise_div_by_zero(-1.0);
    }

    if (hx < 0) {           /* yn(n,<0) = NaN, y1(n,-Inf) = NaN */
        return __raise_invalid();
    }

    sign = 1;

    if (n < 0) {
        n = -n;
        sign = 1 - ((n & 1) << 1);
    }

    if (n == 0) {
        return (y0(x));
    }

    if (n == 1) {
        return (sign * y1(x));
    }

    if (ix == 0x7ff00000) { /* yn(n,+Inf) = +0.0 */
        return zero;
    }

    if (ix >= 0x52D00000) { /* x > 2**302 */
        /* (x >> n**2)
         *        Jn(x) = cos(x-(2n+1)*pi/4)*sqrt(2/x*pi)
         *        Yn(x) = sin(x-(2n+1)*pi/4)*sqrt(2/x*pi)
         *        Let s=sin(x), c=cos(x),
         *        xn=x-(2n+1)*pi/4, sqt2 = sqrt(2),then
         *
         *           n    sin(xn)*sqt2    cos(xn)*sqt2
         *        ----------------------------------
         *           0     s-c         c+s
         *           1    -s-c         -c+s
         *           2    -s+c        -c-s
         *           3     s+c         c-s
         */
        switch (n & 3) {
        default:    /* FALLTHRU */
        case 0:
            temp =  sin(x) - cos(x);
            break;

        case 1:
            temp = -sin(x) - cos(x);
            break;

        case 2:
            temp = -sin(x) + cos(x);
            break;

        case 3:
            temp =  sin(x) + cos(x);
            break;
        }

        b = invsqrtpi * temp / sqrt(x);
    } else {
        uint32_t high;
        a = y0(x);
        b = y1(x);
        /* quit if b is -inf */
        GET_HIGH_WORD(high, b);

        for (i = 1; i < n && high != 0xfff00000U; i++) {
            temp = b;
            b = ((double)(i + i) / x) * b - a;
            GET_HIGH_WORD(high, b);
            a = temp;
        }
    }

    if (sign > 0) {
        return b;
    } else {
        return -b;
    }
}

#endif /* defined(_DOUBLE_IS_32BITS) */
