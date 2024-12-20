/* SPDX-License-Identifier: GTDGmbH */
/* Copyright 2020-2021 by GTD GmbH. */

/**
 *
 * This macro is used to test if :math:`x` is less than or equal to :math:`y`
 * without throwing an ``invalid operation`` exception on ``NaN`` inputs (this
 * even includes ``sNaN``).
 *
 * Synopsis
 * ========
 *
 * .. code-block:: c
 *
 *     #include <math.h>
 *     int islessequal(x, y);
 *
 * Description
 * ===========
 *
 * ``islessequal`` tests whether :math:`x` is less than or equal to :math:`y`
 * without throwing an ``invalid operation`` exception on ``NaN`` inputs. Not
 * throwing an exception is the only difference to using a relational
 * comparison operator.
 *
 * Mathematical Function
 * =====================
 *
 * .. math::
 *
 *    islessequal(x, y) = \left\{\begin{array}{ll} 1, & x \leq y \\
 *                                                 0, & otherwise \end{array}\right.
 *
 * Returns
 * =======
 *
 * ``islessequal`` returns :math:`1` if :math:`x \leq y`, else :math:`0`.
 *
 * Exceptions
 * ==========
 *
 * Does not raise exceptions. This includes ``sNaN`` inputs.
 *
 * Output map
 * ==========
 *
 * +--------------------------+--------------------------+--------------------------+
 * | islessequal(x,y)         | x                                                   |
 * +--------------------------+--------------------------+--------------------------+
 * | y                        | :math:`\neq NaN`         | :math:`NaN`              |
 * +==========================+==========================+==========================+
 * | :math:`\neq NaN`         | :math:`x <= y\ ?\ 1 : 0` | :math:`0`                |
 * +--------------------------+--------------------------+                          +
 * | :math:`NaN`              | :math:`0`                |                          |
 * +--------------------------+--------------------------+--------------------------+
 *
 *///
