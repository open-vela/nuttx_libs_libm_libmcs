/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <assert.h>
#include <math.h>
#include "../common/tools.h"

float modff(float x, float *iptr)
{
    float _xi = 0.0f;
    int32_t i0, j0;
    uint32_t i;

	assert(iptr != (void*)0);
	if(iptr == (void*)0) {
	    iptr = &_xi;
	}

    GET_FLOAT_WORD(i0, x);
    j0 = ((i0 >> 23) & 0xff) - 0x7f; /* exponent of x */

    if (j0 < 23) {         /* integer part in x */
        if (j0 < 0) {         /* |x|<1 */
            SET_FLOAT_WORD(*iptr, i0 & 0x80000000U); /* *iptr = +-0 */
            return x;
        } else {
            i = (0x007fffff) >> j0;

            if ((i0 & i) == 0) {       /* x is integral */
                *iptr = x;
                SET_FLOAT_WORD(x, i0 & 0x80000000U); /* return +-0 */
                return x;
            } else {
                SET_FLOAT_WORD(*iptr, i0 & (~i));
                return x - *iptr;
            }
        }
    } else {            /* no fraction part */
        *iptr = x;

        if (isnan(x)) {
            return *iptr = x + x;    /* x is NaN, return NaN */
        }

        SET_FLOAT_WORD(x, i0 & 0x80000000U); /* return +-0 */
        return x;
    }
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double modf(double x, double *iptr)
{
    return (double) modff((float) x, (float *) iptr);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
