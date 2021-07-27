/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/**
 *
 * This family of functions implements the floating-point remainder :math:`x\ REM\ y` and puts the quotient (or at least the 3 least significant bits) into the outpointer.
 *
 * Synopsis
 * ========
 *
 * .. code-block:: c
 *
 *     #include <math.h>
 *     float remquof(float x, float y, int *quo);
 *     double remquo(double x, double y, int *quo);
 *     long double remquol(long double x, long double y, int *quo);
 *
 * Description
 * ===========
 *
 * ``remquo`` computes the floating-point remainder :math:`r = x\ REM\ y = x - n \cdot y` of their arguments :math:`x` and :math:`y`, where :math:`n` is the integral value nearest to :math:`\frac{x}{y}`.
 :math:`n` is then put into the output pointer :math:`*quo`. If :math:`n` is too large to be represented in an ``integer``, only the three least significant bits of :math:`n` are correct.
 *
 * ``remquo`` and ``remainder`` are functionally equivalent concerning the return value, ``remquo`` only adds an additional output.
 *
 * Mathematical Function
 * =====================
 * 
 * .. math::
 *
 *    remquo(x, y) = x - n \cdot y \wedge n \in \mathbb{Z} \wedge remquo(x, y) \in \left [-\left | \frac{y}{2} \right |,\left | \frac{y}{2} \right | \right ] \wedge quo = n
 *
 * Returns
 * =======
 *
 * ``remquo`` returns the floating-point remainder :math:`x\ REM\ y`. The quotient :math:`n` is put into :math:`*quo`.
 *
 * Exceptions
 * ==========
 *
 * Raise ``invalid operation`` exception when :math:`x` is infinite or :math:`y` is zero.
 *
 * .. May raise ``underflow`` exception.
 *
 * Output map
 * ==========
 *
 * +--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+
 * | remquo(x,y)              | x                                                                                                                                                                                          |
 * +--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+
 * | y                        | :math:`-Inf`             | :math:`<0`               | :math:`-0`               | :math:`+0`               | :math:`>0`               | :math:`+Inf`             | :math:`NaN`              |
 * +==========================+==========================+==========================+==========================+==========================+==========================+==========================+==========================+
 * | :math:`-Inf`             | :math:`qNaN`             | :math:`x`                                                                                                 | :math:`qNaN`             | :math:`qNaN`             |
 * +--------------------------+                          +--------------------------+--------------------------+--------------------------+--------------------------+                          +                          +
 * | :math:`<0`               |                          | :math:`x\ REM\ y`        | :math:`x`                                           | :math:`x\ REM\ y`        |                          |                          |
 * +--------------------------+                          +--------------------------+--------------------------+--------------------------+--------------------------+                          +                          +
 * | :math:`-0`               |                          | :math:`qNaN`                                                                                              |                          |                          |
 * +--------------------------+                          +                                                                                                           +                          +                          +
 * | :math:`+0`               |                          |                                                                                                           |                          |                          |
 * +--------------------------+                          +--------------------------+--------------------------+--------------------------+--------------------------+                          +                          +
 * | :math:`>0`               |                          | :math:`x\ REM\ y`        | :math:`x`                                           | :math:`x\ REM\ y`        |                          |                          |
 * +--------------------------+                          +--------------------------+--------------------------+--------------------------+--------------------------+                          +                          +
 * | :math:`+Inf`             |                          | :math:`x`                                                                                                 |                          |                          |
 * +--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+                          +
 * | :math:`NaN`              | :math:`qNaN`                                                                                                                                                    |                          |
 * +--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+
 *
 * +--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+
 * | :math:`*quo`             | x                                                                                                                                                                                          |
 * +--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+
 * | y                        | :math:`-Inf`             | :math:`<0`               | :math:`-0`               | :math:`+0`               | :math:`>0`               | :math:`+Inf`             | :math:`NaN`              |
 * +==========================+==========================+==========================+==========================+==========================+==========================+==========================+==========================+
 * | :math:`-Inf`             | :math:`0`                | :math:`0`                                                                                                 | :math:`0`                | :math:`0`                |
 * +--------------------------+                          +--------------------------+--------------------------+--------------------------+--------------------------+                          +                          +
 * | :math:`<0`               |                          | :math:`n`                | :math:`0`                                           | :math:`n`                |                          |                          |
 * +--------------------------+                          +--------------------------+--------------------------+--------------------------+--------------------------+                          +                          +
 * | :math:`-0`               |                          | :math:`0`                                                                                                 |                          |                          |
 * +--------------------------+                          +                                                                                                           +                          +                          +
 * | :math:`+0`               |                          |                                                                                                           |                          |                          |
 * +--------------------------+                          +--------------------------+--------------------------+--------------------------+--------------------------+                          +                          +
 * | :math:`>0`               |                          | :math:`n`                | :math:`0`                                           | :math:`n`                |                          |                          |
 * +--------------------------+                          +--------------------------+--------------------------+--------------------------+--------------------------+                          +                          +
 * | :math:`+Inf`             |                          | :math:`0`                                                                                                 |                          |                          |
 * +--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+                          +
 * | :math:`NaN`              | :math:`0`                                                                                                                                                       |                          |
 * +--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+--------------------------+
 *
 *///

#include <assert.h>
#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

/* For quotient, return either all 31 bits that can from calculation (using
 * int32_t), or as many as can fit into an int that is smaller than 32 bits.  */
#if INT_MAX > 0x7FFFFFFFL
    #define QUO_MASK 0x7FFFFFFF
#else
    #define QUO_MASK INT_MAX
#endif

static const double Zero[] = {0.0, -0.0,};

/*
 * Return the IEEE remainder and set *quo to the last n bits of the
 * quotient, rounded to the nearest integer.  We choose n=31--if that many fit--
 * because we wind up computing all the integer bits of the quotient anyway as
 * a side-effect of computing the remainder by the shift and subtract
 * method.  In practice, this is far more bits than are needed to use
 * remquo in reduction algorithms.
 */
double remquo(double x, double y, int *quo)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
    y *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    int _quo = 0;
    int32_t n, hx, hy, hz, ix, iy, sx, i;
    uint32_t lx, ly, lz, q, sxy;

    assert(quo != (void*)0);
    if(quo == (void*)0) {
        quo = &_quo;
    }
    *quo = 0;

    EXTRACT_WORDS(hx, lx, x);
    EXTRACT_WORDS(hy, ly, y);
    sxy = (hx ^ hy) & 0x80000000U;
    sx = hx & 0x80000000U;     /* sign of x */
    hx ^= sx;                  /* |x| */
    hy &= 0x7fffffff;          /* |y| */

    /* purge off exception values */
    if ((hx >= 0x7ff00000) || (hy >= 0x7ff00000)) { /* x or y not finite */
        if (isnan(x) || isnan(y)) {                 /* x or y is NaN */
            return x + y;
        } else if (hx == 0x7ff00000 && lx == 0) {   /* x is infinite */
            return __raise_invalid();
        } else {
            /* No action required */
        }
    } else if ((hy | ly) == 0) {                    /* y = 0 */
        return __raise_invalid();
    } else {
        /* No action required */
    }

    if (hx <= hy) {
        if ((hx < hy) || (lx < ly)) {
            q = 0;
            goto fixup;                             /* |x|<|y| return x or x-y */
        }

        if (lx == ly) {
            *quo = ((sxy != 0) ? -1 : 1);
            return Zero[(uint32_t)sx >> 31];        /* |x|=|y| return x*0 */
        }
    }

    /* determine ix = ilogb(x) */
    if (hx < 0x00100000) {                            /* subnormal x */
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
    if (hy < 0x00100000) {                            /* subnormal y */
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
    } else {                                          /* subnormal x, shift x to normal */
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
    } else {                                          /* subnormal y, shift y to normal */
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
    q = 0;

    while (n-- > 0) {
        hz = hx - hy;
        lz = lx - ly;

        if (lx < ly) {
            hz -= 1;
        }

        if (hz < 0) {
            hx = hx + hx + (lx >> 31);
            lx = lx + lx;
        } else {
            hx = hz + hz + (lz >> 31);
            lx = lz + lz;
            q++;
        }

        q <<= 1;
    }

    hz = hx - hy;
    lz = lx - ly;

    if (lx < ly) {
        hz -= 1;
    }

    if (hz >= 0) {
        hx = hz;
        lx = lz;
        q++;
    }

    /* convert back to floating value and restore the sign */
    if ((hx | lx) == 0) {         /* return sign(x)*0 */
        q &= QUO_MASK;
        *quo = ((sxy != 0) ? -q : q);
        return Zero[(uint32_t)sx >> 31];
    }

    while (hx < 0x00100000) {     /* normalize x */
        hx = hx + hx + (lx >> 31);
        lx = lx + lx;
        iy -= 1;
    }

    if (iy >= -1022) {            /* normalize output */
        hx = ((hx - 0x00100000) | ((iy + 1023) << 20));
    } else {                      /* subnormal output */
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
    }

fixup:
    INSERT_WORDS(x, hx, lx);
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */
    y = fabs(y);

    if (y < 0x1p-1021) {
        if (x + x > y || (x + x == y && (q & 1))) {
            q++;
            x -= y;
        }
    } else if (x > 0.5 * y || (x == 0.5 * y && (q & 1))) {
        q++;
        x -= y;
    } else {
        /* No action required */
    }

    GET_HIGH_WORD(hx, x);
    SET_HIGH_WORD(x, hx ^ sx);
    q &= QUO_MASK;
    *quo = ((sxy != 0) ? -q : q);
    return x;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double remquol(long double x, long double y, int *quo)
{
    return (long double) remquo((double) x, (double) y, quo);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
