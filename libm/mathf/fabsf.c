/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

/*
 * fabsf(x) returns the absolute value of x.
 */

#include "tools.h"

float fabsf(float x)
{
    uint32_t ix;
    GET_FLOAT_WORD(ix, x);
    SET_FLOAT_WORD(x, ix & 0x7fffffff);
    return x;
}

#ifdef _DOUBLE_IS_32BITS

double fabs(double x)
{
    return (double) fabsf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
