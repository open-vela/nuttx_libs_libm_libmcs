/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

/* __tgammaf(x)
 * Float version the Gamma function. Returns gamma(x)
 *
 * Method: See __lgammaf
 */

#include <math.h>
#include "internal/gammaf.h"

float tgammaf(float x)
{
    int signgam_local;
    float y = expf(__lgammaf(x, &signgam_local));

    if (signgam_local < 0) {
        y = -y;
    }

    return y;
}

#ifdef _DOUBLE_IS_32BITS

double tgamma(double x)
{
    return (double) tgammaf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
