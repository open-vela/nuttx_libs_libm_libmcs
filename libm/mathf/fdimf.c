/* SPDX-License-Identifier: RedHat */
/* Copyright (C) 2002 by  Red Hat, Incorporated. All rights reserved. */

#include <math.h>

float fdimf(float x, float y)
{
    if (isnan(x)) {
        return (x);
    }

    if (isnan(y)) {
        return (y);
    }

    return x > y ? x - y : 0.0;
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double fdim(double x, double y)
{
    return (double) fdimf((float) x, (float) y);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
