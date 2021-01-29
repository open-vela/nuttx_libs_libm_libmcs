/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>
#include "internal/gammaf.h"

float lgammaf(float x)
{
    return __lgammaf(x, &__signgam);
}

#ifdef _DOUBLE_IS_32BITS

double lgamma(double x)
{
    return (double) lgammaf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
