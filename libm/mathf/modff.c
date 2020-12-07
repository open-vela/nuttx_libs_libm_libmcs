// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

#include "fdlibm.h"

float modff(float x, float *iptr)
{
	__int32_t i0,j0;
	__uint32_t i;
	GET_FLOAT_WORD(i0,x);
	j0 = ((i0>>23)&0xff)-0x7f;	/* exponent of x */
	if(j0<23) {			/* integer part in x */
	    if(j0<0) {			/* |x|<1 */
	        SET_FLOAT_WORD(*iptr,i0&0x80000000);	/* *iptr = +-0 */
		return x;
	    } else {
		i = (0x007fffff)>>j0;
		if((i0&i)==0) {			/* x is integral */
		    *iptr = x;
		    SET_FLOAT_WORD(x,i0&0x80000000);	/* return +-0 */
		    return x;
		} else {
		    SET_FLOAT_WORD(*iptr,i0&(~i));
		    return x - *iptr;
		}
	    }
	} else {			/* no fraction part */
	    *iptr = x;
	    if (__fpclassifyf(x) == FP_NAN) return *iptr = x+x; /* x is NaN, return NaN */
	    SET_FLOAT_WORD(x,i0&0x80000000);	/* return +-0 */
	    return x;
	}
}

#ifdef _DOUBLE_IS_32BITS

double modf(double x, double *iptr)
{
	return (double) modff((float) x, (float *) iptr);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
