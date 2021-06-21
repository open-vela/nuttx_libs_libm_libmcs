/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>

float ldexpf(float value, int exponent)
{
#ifdef __LIBMCS_FPU_DAZ
    value *= __volatile_onef;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    if ((isfinite(value) == 0) || value == 0.0f) {
        return value;
    }

    return scalbnf(value, exponent);
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double ldexp(double value, int exponent)
{
    return (double) ldexpf((float) value, exponent);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
