/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

#include <math.h>
#include "internal/gammad.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double lgamma(double x)
{
    return __lgamma(x, &__signgam);
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double lgammal(long double x)
{
    return (long double) lgamma((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
