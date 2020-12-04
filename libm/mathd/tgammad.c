// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.

/* __ieee754_tgamma(x)
 * Gamma function. Returns gamma(x)
 *
 * Method: See __ieee754_lgamma_r
 */

#include "fdlibm.h"

#ifdef __STDC__
	double __ieee754_tgamma(double x)
#else
	double __ieee754_tgamma(x)
	double x;
#endif
{
	int signgam_local;
	double y = __ieee754_exp(__ieee754_lgamma_r(x, &signgam_local));
	if (signgam_local < 0)
		y = -y;
	return y;
}

/* double gamma(double x)
 * Return  the logarithm of the Gamma function of x or the Gamma function of x,
 * depending on the library mode.
 */

#include "fdlibm.h"

#ifndef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double tgamma(double x)
#else
	double tgamma(x)
	double x;
#endif
{
        double y;
	y = __ieee754_tgamma(x);
#ifdef _IEEE_LIBM
	return y;
#else
	if(_LIB_VERSION == _IEEE_) return y;

	if(!finite(y)&&finite(x)) {
	  if(floor(x)==x&&x<=0.0)
	    return __kernel_standard(x,x,41); /* tgamma pole */
	  else
	    return __kernel_standard(x,x,40); /* tgamma overflow */
	}
	return y;
#endif
}

#endif /* defined(_DOUBLE_IS_32BITS) */
