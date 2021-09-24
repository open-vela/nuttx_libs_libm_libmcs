/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/**
 *
 * This family of functions implements the floating-point remainder :math:`x\ REM\ y`.
 *
 * Synopsis
 * ========
 *
 * .. code-block:: c
 *
 *     #include <math.h>
 *     float remainderf(float x, float y);
 *     double remainder(double x, double y);
 *     long double remainderl(long double x, long double y);
 *
 * Description
 * ===========
 *
 * ``remainder`` computes the floating-point remainder :math:`r = x\ REM\ y = x - n \cdot y` of their arguments :math:`x` and :math:`y`, where :math:`n` is the integral value nearest to :math:`\frac{x}{y}`.
 *
 * The ``fmod`` and ``remainder`` procedures are rather similar, but not the same, see examples:
 *
 * +----------------+----------------+----------------+----------------+
 * | x              | y              | fmod           | remainder      |
 * +================+================+================+================+
 * | :math:`+2.456` | :math:`+2.0`   | :math:`+0.456` | :math:`+0.456` |
 * +----------------+----------------+----------------+----------------+
 * | :math:`+3.456` | :math:`+2.0`   | :math:`+1.456` | :math:`-0.544` |
 * +----------------+----------------+----------------+----------------+
 * | :math:`-2.456` | :math:`+2.0`   | :math:`-0.456` | :math:`-0.456` |
 * +----------------+----------------+----------------+----------------+
 * | :math:`-3.456` | :math:`+2.0`   | :math:`-1.456` | :math:`+0.544` |
 * +----------------+----------------+----------------+----------------+
 * | :math:`+2.456` | :math:`-2.0`   | :math:`+0.456` | :math:`+0.456` |
 * +----------------+----------------+----------------+----------------+
 * | :math:`+3.456` | :math:`-2.0`   | :math:`+1.456` | :math:`-0.544` |
 * +----------------+----------------+----------------+----------------+
 * | :math:`-2.456` | :math:`-2.0`   | :math:`-0.456` | :math:`-0.456` |
 * +----------------+----------------+----------------+----------------+
 * | :math:`-3.456` | :math:`-2.0`   | :math:`-1.456` | :math:`+0.544` |
 * +----------------+----------------+----------------+----------------+
 *
 * Mathematical Function
 * =====================
 * 
 * .. math::
 *
 *    remainder(x, y) = x - n \cdot y \wedge n \in \mathbb{Z} \wedge remainder(x, y) \in \left [-\left | \frac{y}{2} \right |,\left | \frac{y}{2} \right | \right ]
 *
 * Returns
 * =======
 *
 * ``remainder`` returns the floating-point remainder :math:`x\ REM\ y`.
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
 * | remainder(x,y)           | x                                                                                                                                                                                          |
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
 *///

#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

static const double zero = 0.0;

double remainder(double x, double p)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
    p *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    int32_t hx, hp;
    uint32_t sx, lx, lp;
    double p_half;

    EXTRACT_WORDS(hx, lx, x);
    EXTRACT_WORDS(hp, lp, p);
    sx = hx & 0x80000000U;
    hp &= 0x7fffffff;
    hx &= 0x7fffffff;

    /* purge off exception values */
    if ((hx >= 0x7ff00000) || (hp >= 0x7ff00000)) { /* x or p not finite */
        if (isnan(x) || isnan(p)) {                 /* x or p is NaN */
            return x + p;
        } else if (hx == 0x7ff00000) {              /* x is infinite */
            return __raise_invalid();
        } else {
            /* No action required */
        }
    } else if ((hp | lp) == 0) {                    /* p = 0 */
        return __raise_invalid();
    } else {
        /* No action required */
    }

    if (hp <= 0x7fdfffff) {
        x = fmod(x, p + p);                         /* now x < 2p */
    }

    if (((hx - hp) | (lx - lp)) == 0) {             /* x equals p */
        return zero * x;
    }

    x  = fabs(x);
    p  = fabs(p);

    if (hp < 0x00200000) {
        if (x + x > p) {
            x -= p;

            if (x + x >= p) {
                x -= p;
            }
        }
    } else {
        p_half = 0.5 * p;

        if (x > p_half) {
            x -= p;

            if (x >= p_half) {
                x -= p;
            }
        }
    }

    GET_HIGH_WORD(hx, x);
    SET_HIGH_WORD(x, hx ^ sx);
    return x;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double remainderl(long double x, long double y)
{
    return (long double) remainder((double) x, (double) y);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
