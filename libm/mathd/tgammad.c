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

#include "../common/tools.h"

#ifndef _DOUBLE_IS_32BITS

double tgamma(double x)
{
    int signgam_local;
    double y = __exp(__lgamma(x, &signgam_local));

    if (signgam_local < 0) {
        y = -y;
    }

    return y;
}

#ifdef _LONG_DOUBLE_IS_64BITS

long double tgammal(long double x)
{
    return (long double) tgamma((double) x);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
