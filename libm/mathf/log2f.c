/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include "../common/tools.h"
#include <math.h>

float log2f(float x)
{
    return (logf(x) / (float_t) M_LN2);
}

#ifdef _DOUBLE_IS_32BITS

double log2(double x)
{
    return (double) log2f((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
