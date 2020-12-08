// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

#include "fdlibm.h"

static const float one = 1.0, huge = 1e30, zero = 0.0;

float atanhf(float x)
{
	float t;
	__int32_t hx,ix;
	GET_FLOAT_WORD(hx,x);
	ix = hx&0x7fffffff;
	if (ix>0x3f800000) 		/* |x|>1 */
	    return (x-x)/(x-x);
	if(ix==0x3f800000) 
	    return x/zero;
	if(ix<0x31800000&&(huge+x)>zero) return x;	/* x<2**-28 */
	SET_FLOAT_WORD(x,ix);
	if(ix<0x3f000000) {		/* x < 0.5 */
	    t = x+x;
	    t = (float)0.5*log1pf(t+t*x/(one-x));
	} else 
	    t = (float)0.5*log1pf((x+x)/(one-x));
	if(hx>=0) return t; else return -t;
}

#ifdef _DOUBLE_IS_32BITS

double atanh(double x)
{
	return (double) atanhf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
