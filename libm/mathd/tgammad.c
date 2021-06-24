/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/* __tgamma(x)
 * Gamma function. Returns gamma(x)
 *
 * Method: See __lgamma_r
 */

/* double gamma(double x)
 * Return  the logarithm of the Gamma function of x or the Gamma function of x,
 * depending on the library mode.
 */

#include <math.h>
#include "../common/tools.h"
#include "internal/gammad.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double tgamma(double x)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    int signgam_local = 0;
    double y = 0.0;
    
    if (x == 0.0) {                         /* tgamma(+-0) = +-Inf */
        return __raise_div_by_zero(x);
    } else if (floor(x) == x && isless(x, 0.0) != 0) {  /* tgamma(negative integer, -Inf) = NaN */
        return __raise_invalid(x);
    } else {
        /* No action required */
    }

    y = exp(__lgamma(x, &signgam_local));

    if (signgam_local < 0) {
        y = -y;
    }

    return y;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double tgammal(long double x)
{
    return (long double) tgamma((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
