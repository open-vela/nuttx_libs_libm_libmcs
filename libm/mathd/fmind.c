/* SPDX-License-Identifier: RedHat */
/* Copyright (C) 2002 by  Red Hat, Incorporated. All rights reserved. */

/**
 *
 * This family of functions detemines the minimum value of :math:`x` and :math:`y`.
 *
 * Synopsis
 * ========
 *
 * .. code-block:: c
 *
 *     #include <math.h>
 *     float fminf(float x, float y);
 *     double fmin(double x, double y);
 *     long double fminl(long double x, long double y);
 *
 * Description
 * ===========
 *
 * ``fmin`` computes the minimum value of :math:`x` and :math:`y`.
 *
 * Mathematical Function
 * =====================
 *
 * .. math::
 *
 *    fmin(x, y) = \left\{\begin{array}{ll} x, & x < y \\ y, & otherwise \end{array}\right.
 *
 * Returns
 * =======
 *
 * ``fmin`` returns the minimum value of :math:`x` and :math:`y`.
 *
 * Exceptions
 * ==========
 *
 * Does not raise exceptions.
 *
 * Output map
 * ==========
 *
 * +--------------+--------------+--------------------+------------+------------+--------------------+--------------+--------------+--------------+
 * | fmin(x,y)    | x                                                                                                                             |
 * +--------------+--------------+--------------------+------------+------------+--------------------+--------------+--------------+--------------+
 * | y            | :math:`-Inf` | :math:`<0`         | :math:`-0` | :math:`+0` | :math:`>0`         | :math:`+Inf` | :math:`qNaN` | :math:`sNaN` |
 * +==============+==============+====================+============+============+====================+==============+==============+==============+
 * | :math:`-Inf` | :math:`y`                         | :math:`y`                                    | :math:`y`    | :math:`x`    | :math:`qNaN` |
 * +--------------+--------------+--------------------+                                              +              +              +              +
 * | :math:`<0`   | :math:`x`    | :math:`fmin(x, y)` |                                              |              |              |              |
 * +--------------+              +--------------------+                                              +              +              +              +
 * | :math:`-0`   |              | :math:`x`          |                                              |              |              |              |
 * +--------------+              +                    +                                              +              +              +              +
 * | :math:`+0`   |              |                    |                                              |              |              |              |
 * +--------------+              +                    +------------+------------+--------------------+              +              +              +
 * | :math:`>0`   |              |                    | :math:`x`               | :math:`fmin(x, y)` |              |              |              |
 * +--------------+              +                    +                         +--------------------+              +              +              +
 * | :math:`+Inf` |              |                    |                         | :math:`x`          |              |              |              |
 * +--------------+--------------+--------------------+------------+------------+--------------------+--------------+              +              +
 * | :math:`qNaN` | :math:`y`                                                                                       |              |              |
 * +--------------+--------------+--------------------+------------+------------+--------------------+--------------+--------------+              +
 * | :math:`sNaN` | :math:`qNaN`                                                                                                   |              |
 * +--------------+--------------+--------------------+------------+------------+--------------------+--------------+--------------+--------------+
 *
 *///

#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double fmin(double x, double y)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
    y *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    if (isnan(x) || isnan(y)) {
        return x * y;
    }

    return x < y ? x : y;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double fminl(long double x, long double y)
{
    return (long double) fmin((double) x, (double) y);
}

#endif /* #ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS */
#endif /* #ifndef __LIBMCS_DOUBLE_IS_32BITS */
