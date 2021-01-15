/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*
FUNCTION
       <<nextafter>>, <<nextafterf>>---get next number

INDEX
    nextafter
INDEX
    nextafterf

SYNOPSIS
       #include <math.h>
       double nextafter(double <[val]>, double <[dir]>);
       float nextafterf(float <[val]>, float <[dir]>);

DESCRIPTION
<<nextafter>> returns the double-precision floating-point number
closest to <[val]> in the direction toward <[dir]>.  <<nextafterf>>
performs the same operation in single precision.  For example,
<<nextafter(0.0,1.0)>> returns the smallest positive number which is
representable in double precision.

RETURNS
Returns the next closest number to <[val]> in the direction toward
<[dir]>.

PORTABILITY
    Neither <<nextafter>> nor <<nextafterf>> is required by ANSI C
    or by the System V Interface Definition (Issue 2).
*/

/* IEEE functions
 *    nextafter(x,y)
 *    return the next machine floating-point number of x in the
 *    direction toward y.
 *   Special cases:
 */

#include "fdlibm.h"

#ifndef _DOUBLE_IS_32BITS

double nextafter(double x, double y)
{
    __int32_t  hx, hy, ix, iy;
    __uint32_t lx, ly;

    EXTRACT_WORDS(hx, lx, x);
    EXTRACT_WORDS(hy, ly, y);
    ix = hx & 0x7fffffff;      /* |x| */
    iy = hy & 0x7fffffff;      /* |y| */

    if (((ix >= 0x7ff00000) && ((ix - 0x7ff00000) | lx) != 0) || /* x is nan */
        ((iy >= 0x7ff00000) && ((iy - 0x7ff00000) | ly) != 0)) { /* y is nan */
        return x + y;
    }

    if (x == y) {
        return x;              /* x=y, return x */
    }

    if ((ix | lx) == 0) {      /* x == 0 */
        INSERT_WORDS(x, hy & 0x80000000, 1); /* return +-minsubnormal */
        y = x * x;

        if (y == x) {
            return y;
        } else {
            return x;                        /* raise underflow flag */
        }
    }

    if (hx >= 0) {             /* x > 0 */
        if (hx > hy || ((hx == hy) && (lx > ly))) { /* x > y, x -= ulp */
            if (lx == 0) {
                hx -= 1;
            }

            lx -= 1;
        } else {                /* x < y, x += ulp */
            lx += 1;

            if (lx == 0) {
                hx += 1;
            }
        }
    } else {                    /* x < 0 */
        if (hy >= 0 || hx > hy || ((hx == hy) && (lx > ly))) { /* x < y, x -= ulp */
            if (lx == 0) {
                hx -= 1;
            }

            lx -= 1;
        } else {                /* x > y, x += ulp */
            lx += 1;

            if (lx == 0) {
                hx += 1;
            }
        }
    }

    hy = hx & 0x7ff00000;

    if (hy >= 0x7ff00000) {
        return x + x;          /* overflow  */
    }

    if (hy < 0x00100000) {     /* underflow */
        y = x * x;

        if (y != x) {          /* raise underflow flag */
            INSERT_WORDS(y, hx, lx);
            return y;
        }
    }

    INSERT_WORDS(x, hx, lx);
    return x;
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double nextafterl(long double x, long double y)
{
    return (long double) nextafter((double) x, (double) y);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
