// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

#include "fdlibm.h"

#ifdef __STDC__
static const float one = 1.0, shuge = 1.0e37;
#else
static float one = 1.0, shuge = 1.0e37;
#endif

#ifdef __STDC__
	float __ieee754_sinhf(float x)
#else
	float __ieee754_sinhf(x)
	float x;
#endif
{	
	float t,w,h;
	__int32_t ix,jx;

	GET_FLOAT_WORD(jx,x);
	ix = jx&0x7fffffff;

    /* x is INF or NaN */
	if(!FLT_UWORD_IS_FINITE(ix)) return x+x;	

	h = 0.5;
	if (jx<0) h = -h;
    /* |x| in [0,22], return sign(x)*0.5*(E+E/(E+1))) */
	if (ix < 0x41b00000) {		/* |x|<22 */
	    if (ix<0x31800000) 		/* |x|<2**-28 */
		if(shuge+x>one) return x;/* sinh(tiny) = tiny with inexact */
	    t = expm1f(fabsf(x));
	    if(ix<0x3f800000) return h*((float)2.0*t-t*t/(t+one));
	    return h*(t+t/(t+one));
	}

    /* |x| in [22, log(maxdouble)] return 0.5*exp(|x|) */
	if (ix<=FLT_UWORD_LOG_MAX)  return h*__ieee754_expf(fabsf(x));

    /* |x| in [log(maxdouble), overflowthresold] */
	if (ix<=FLT_UWORD_LOG_2MAX) {
	    w = __ieee754_expf((float)0.5*fabsf(x));
	    t = h*w;
	    return t*w;
	}

    /* |x| > overflowthresold, sinh(x) overflow */
	return x*shuge;
}

/* 
 * wrapper sinhf(x)
 */

#include "fdlibm.h"
#include <errno.h>

#ifdef __STDC__
	float sinhf(float x)		/* wrapper sinhf */
#else
	float sinhf(x)			/* wrapper sinhf */
	float x;
#endif
{
#ifdef _IEEE_LIBM
	return __ieee754_sinhf(x);
#else
	float z; 
	z = __ieee754_sinhf(x);
	if(_LIB_VERSION == _IEEE_) return z;
	if(!finitef(z)&&finitef(x)) {
	    /* sinhf(finite) overflow */
	    errno = ERANGE;
	    return ( (x>0.0f) ? HUGE_VALF : -HUGE_VALF);
	} else
	    return z;
#endif
}

#ifdef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double sinh(double x)
#else
	double sinh(x)
	double x;
#endif
{
	return (double) sinhf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
