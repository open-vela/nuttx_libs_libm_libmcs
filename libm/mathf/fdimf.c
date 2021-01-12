// SPDX-License-Identifier: RedHat
// Copyright (C) 2002 by  Red Hat, Incorporated. All rights reserved.

#include "fdlibm.h"

float fdimf(float x, float y)
{
    if (__fpclassifyf(x) == FP_NAN) {
        return (x);
    }

    if (__fpclassifyf(y) == FP_NAN) {
        return (y);
    }

    return x > y ? x - y : 0.0;
}

#ifdef _DOUBLE_IS_32BITS

double fdim(double x, double y)
{
    return (double) fdimf((float) x, (float) y);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
