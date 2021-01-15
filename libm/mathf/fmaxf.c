/* SPDX-License-Identifier: RedHat */
/* Copyright (C) 2002 by  Red Hat, Incorporated. All rights reserved. */

#include "../common/tools.h"

float fmaxf(float x, float y)
{
    if (__fpclassifyf(x) == FP_NAN) {
        return y;
    }

    if (__fpclassifyf(y) == FP_NAN) {
        return x;
    }

    return x > y ? x : y;
}

#ifdef _DOUBLE_IS_32BITS

double fmax(double x, double y)
{
    return (double) fmaxf((float) x, (float) y);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
