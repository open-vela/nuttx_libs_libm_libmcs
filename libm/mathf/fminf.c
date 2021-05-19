/* SPDX-License-Identifier: RedHat */
/* Copyright (C) 2002 by  Red Hat, Incorporated. All rights reserved. */

#include <math.h>

float fminf(float x, float y)
{
    if (isnan(x)) {
        return y;
    }

    if (isnan(y)) {
        return x;
    }

    return x < y ? x : y;
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double fmin(double x, double y)
{
    return (double) fminf((float) x, (float) y);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
