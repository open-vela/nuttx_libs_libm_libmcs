/* SPDX-License-Identifier: RedHat */
/* Copyright (C) 2002 by  Red Hat, Incorporated. All rights reserved. */

#include <math.h>
#include "../common/tools.h"

float fminf(float x, float y)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_onef;
    y *= __volatile_onef;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    if (isnan(x) || isnan(y)) {
        return x * y;
    }

    return x < y ? x : y;
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double fmin(double x, double y)
{
    return (double) fminf((float) x, (float) y);
}

#endif /* defined(__LIBMCS_DOUBLE_IS_32BITS) */
