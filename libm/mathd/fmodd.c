/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*
 * fmod(x,y)
 * Return x mod y in exact arithmetic
 * Method: shift and subtract
 */

/*
FUNCTION
<<fmod>>, <<fmodf>>---floating-point remainder (modulo)

INDEX
fmod
INDEX
fmodf

SYNOPSIS
#include <math.h>
double fmod(double <[x]>, double <[y]>);
float fmodf(float <[x]>, float <[y]>);

DESCRIPTION
The <<fmod>> and <<fmodf>> functions compute the floating-point
remainder of <[x]>/<[y]> (<[x]> modulo <[y]>).

RETURNS
The <<fmod>> function returns the value
@ifnottex
<[x]>-<[i]>*<[y]>,
@end ifnottex
@tex
$x-i\times y$,
@end tex
for the largest integer <[i]> such that, if <[y]> is nonzero, the
result has the same sign as <[x]> and magnitude less than the
magnitude of <[y]>.

<<fmod(<[x]>,0)>> returns NaN, and sets <<errno>> to <<EDOM>>.

PORTABILITY
<<fmod>> is ANSI C. <<fmodf>> is an extension.
*/

#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

static const double one = 1.0, Zero[] = {0.0, -0.0,};

double fmod(double x, double y)
{
    int32_t n, hx, hy, hz, ix, iy, sx, i;
    uint32_t lx, ly, lz;

    EXTRACT_WORDS(hx, lx, x);
    EXTRACT_WORDS(hy, ly, y);
    sx = hx & 0x80000000;      /* sign of x */
    hx ^= sx;                  /* |x| */
    hy &= 0x7fffffff;          /* |y| */

    /* purge off exception values */
    if ((hy | ly) == 0 || (hx >= 0x7ff00000) || /* y=0,or x not finite */
        ((hy | ((ly | -ly) >> 31)) > 0x7ff00000)) { /* or y is NaN */
        return (x * y) / (x * y);
    }

    if (hx <= hy) {
        if ((hx < hy) || (lx < ly)) {
            return x;    /* |x|<|y| return x */
        }

        if (lx == ly) {
            return Zero[(uint32_t)sx >> 31];    /* |x|=|y| return x*0*/
        }
    }

    /* determine ix = ilogb(x) */
    if (hx < 0x00100000) { /* subnormal x */
        if (hx == 0) {
            for (ix = -1043, i = lx; i > 0; i <<= 1) {
                ix -= 1;
            }
        } else {
            for (ix = -1022, i = (hx << 11); i > 0; i <<= 1) {
                ix -= 1;
            }
        }
    } else {
        ix = (hx >> 20) - 1023;
    }

    /* determine iy = ilogb(y) */
    if (hy < 0x00100000) { /* subnormal y */
        if (hy == 0) {
            for (iy = -1043, i = ly; i > 0; i <<= 1) {
                iy -= 1;
            }
        } else {
            for (iy = -1022, i = (hy << 11); i > 0; i <<= 1) {
                iy -= 1;
            }
        }
    } else {
        iy = (hy >> 20) - 1023;
    }

    /* set up {hx,lx}, {hy,ly} and align y to x */
    if (ix >= -1022) {
        hx = 0x00100000 | (0x000fffff & hx);
    } else {      /* subnormal x, shift x to normal */
        n = -1022 - ix;

        if (n <= 31) {
            hx = (hx << n) | (lx >> (32 - n));
            lx <<= n;
        } else {
            hx = lx << (n - 32);
            lx = 0;
        }
    }

    if (iy >= -1022) {
        hy = 0x00100000 | (0x000fffff & hy);
    } else {      /* subnormal y, shift y to normal */
        n = -1022 - iy;

        if (n <= 31) {
            hy = (hy << n) | (ly >> (32 - n));
            ly <<= n;
        } else {
            hy = ly << (n - 32);
            ly = 0;
        }
    }

    /* fix point fmod */
    n = ix - iy;

    while (n--) {
        hz = hx - hy;
        lz = lx - ly;

        if (lx < ly) {
            hz -= 1;
        }

        if (hz < 0) {
            hx = hx + hx + (lx >> 31);
            lx = lx + lx;
        } else {
            if ((hz | lz) == 0) {  /* return sign(x)*0 */
                return Zero[(uint32_t)sx >> 31];
            }

            hx = hz + hz + (lz >> 31);
            lx = lz + lz;
        }
    }

    hz = hx - hy;
    lz = lx - ly;

    if (lx < ly) {
        hz -= 1;
    }

    if (hz >= 0) {
        hx = hz;
        lx = lz;
    }

    /* convert back to floating value and restore the sign */
    if ((hx | lx) == 0) {      /* return sign(x)*0 */
        return Zero[(uint32_t)sx >> 31];
    }

    while (hx < 0x00100000) {     /* normalize x */
        hx = hx + hx + (lx >> 31);
        lx = lx + lx;
        iy -= 1;
    }

    if (iy >= -1022) {  /* normalize output */
        hx = ((hx - 0x00100000) | ((iy + 1023) << 20));
        INSERT_WORDS(x, hx | sx, lx);
    } else {        /* subnormal output */
        n = -1022 - iy;

        if (n <= 20) {
            lx = (lx >> n) | ((uint32_t)hx << (32 - n));
            hx >>= n;
        } else if (n <= 31) {
            lx = (hx << (32 - n)) | (lx >> n);
            hx = sx;
        } else {
            lx = hx >> (n - 32);
            hx = sx;
        }

        INSERT_WORDS(x, hx | sx, lx);
        x *= one;        /* create necessary signal */
    }

    return x;        /* exact output */
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double fmodl(long double x, long double y)
{
    return (long double) fmod((double) x, (double) y);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
