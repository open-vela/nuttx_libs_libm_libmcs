// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

/* __ieee754_tgammaf(x)
 * Float version the Gamma function. Returns gamma(x)
 *
 * Method: See __ieee754_lgammaf_r
 */

#include "fdlibm.h"

#ifdef __STDC__
	float __ieee754_tgammaf(float x)
#else
	float __ieee754_tgammaf(x)
#endif
{
	int signgam_local;
	float y = __ieee754_expf(__ieee754_lgammaf_r(x, &signgam_local));
	if (signgam_local < 0)
		y = -y;
	return y;
}

#include "math.h"
#include "fdlibm.h"

#ifdef __STDC__
	float tgammaf(float x)
#else
	float tgammaf(x)
	float x;
#endif
{
        float y;
	y = __ieee754_tgammaf(x);
#ifdef _IEEE_LIBM
	return y;
#else
	if(_LIB_VERSION == _IEEE_) return y;

	if(!finitef(y)&&finitef(x)) {
	  if(floorf(x)==x&&x<=(float)0.0)
	    /* tgammaf pole */
	    return (float)__kernel_standard((double)x,(double)x,141);
	  else
	    /* tgammaf overflow */
	    return (float)__kernel_standard((double)x,(double)x,140);
	}
	return y;
#endif
}

#ifdef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double tgamma(double x)
#else
	double tgamma(x)
	double x;
#endif
{
	return (double) tgammaf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
