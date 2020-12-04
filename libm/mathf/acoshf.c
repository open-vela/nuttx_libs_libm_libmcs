// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

#include "fdlibm.h"

#ifdef __STDC__
static const float 
#else
static float 
#endif
one	= 1.0,
ln2	= 6.9314718246e-01;  /* 0x3f317218 */

#ifdef __STDC__
	float __ieee754_acoshf(float x)
#else
	float __ieee754_acoshf(x)
	float x;
#endif
{	
	float t;
	__int32_t hx;
	GET_FLOAT_WORD(hx,x);
	if(hx<0x3f800000) {		/* x < 1 */
	    return (x-x)/(x-x);
	} else if(hx >=0x4d800000) {	/* x > 2**28 */
	    if(!FLT_UWORD_IS_FINITE(hx)) {	/* x is inf of NaN */
	        return x+x;
	    } else 
		return __ieee754_logf(x)+ln2;	/* acosh(huge)=log(2x) */
	} else if (hx==0x3f800000) {
	    return 0.0;			/* acosh(1) = 0 */
	} else if (hx > 0x40000000) {	/* 2**28 > x > 2 */
	    t=x*x;
	    return __ieee754_logf((float)2.0*x-one/(x+__ieee754_sqrtf(t-one)));
	} else {			/* 1<x<2 */
	    t = x-one;
	    return log1pf(t+__ieee754_sqrtf((float)2.0*t+t*t));
	}
}

/* 
 * wrapper acoshf(x)
 */

#include "fdlibm.h"
#include <errno.h>

#ifdef __STDC__
	float acoshf(float x)		/* wrapper acoshf */
#else
	float acoshf(x)			/* wrapper acoshf */
	float x;
#endif
{
#ifdef _IEEE_LIBM
	return __ieee754_acoshf(x);
#else
	float z;
	z = __ieee754_acoshf(x);
	if(_LIB_VERSION == _IEEE_ || isnan(x)) return z;
	if(x<1.0f) {
	    /* acoshf(x<1) */
	    errno = EDOM;
	    return 0.0f/0.0f;
	} else
	    return z;
#endif
}

#ifdef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double acosh(double x)
#else
	double acosh(x)
	double x;
#endif
{
	return (double) acoshf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
