/* SPDX-License-Identifier: GTDGmbH */
/* Copyright 2020-2021 by GTD GmbH. */

#include <math.h>

float fmaf(float x, float y, float z)
{
    return x * y + z;
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double fma(double x, double y, double z)
{
    return (double) fmaf((float) x, (float) y, (float) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
