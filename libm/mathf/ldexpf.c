/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>

float ldexpf(float value, int exp)
{
    if (!isfinite(value) || value == (float)0.0) {
        return value;
    }

    return scalbnf(value, exp);
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double ldexp(double value, int exp)
{
    return (double) ldexpf((float) value, exp);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
