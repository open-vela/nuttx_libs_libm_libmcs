/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

/* __tgammaf(x)
 * Float version the Gamma function. Returns gamma(x)
 *
 * Method: See __lgammaf
 */

#include <math.h>
#include "../common/tools.h"
#include "internal/gammaf.h"

float tgammaf(float x)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_onef;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    int signgam_local = 0;
    float y = 0.0f;
    
    if (x == 0.0f) {                            /* tgamma(+-0) = +-Inf */
        return __raise_div_by_zerof(x);
    } else if (floorf(x) == x && isless(x, 0.0f) != 0) {    /* tgamma(negative integer, -Inf) = NaN */
        return __raise_invalidf(x);
    } else {
        /* No action required */
    }
    
    y = expf(__lgammaf(x, &signgam_local));

    if (signgam_local < 0) {
        y = -y;
    }

    return y;
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double tgamma(double x)
{
    return (double) tgammaf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
