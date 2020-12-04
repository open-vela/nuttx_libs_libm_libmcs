// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

#include "fdlibm.h"

#ifdef __STDC__
static const float zero = 0.0;
#else
static float zero = 0.0;
#endif


#ifdef __STDC__
	float __ieee754_remainderf(float x, float p)
#else
	float __ieee754_remainderf(x,p)
	float x,p;
#endif
{
	__int32_t hx,hp;
	__uint32_t sx;
	float p_half;

	GET_FLOAT_WORD(hx,x);
	GET_FLOAT_WORD(hp,p);
	sx = hx&0x80000000;
	hp &= 0x7fffffff;
	hx &= 0x7fffffff;

    /* purge off exception values */
	if(FLT_UWORD_IS_ZERO(hp)||
	   !FLT_UWORD_IS_FINITE(hx)||
	   FLT_UWORD_IS_NAN(hp))
	    return (x*p)/(x*p);


	if (hp<=FLT_UWORD_HALF_MAX) x = __ieee754_fmodf(x,p+p); /* now x < 2p */
	if ((hx-hp)==0) return zero*x;
	x  = fabsf(x);
	p  = fabsf(p);
	if (hp<0x01000000) {
	    if(x+x>p) {
		x-=p;
		if(x+x>=p) x -= p;
	    }
	} else {
	    p_half = (float)0.5*p;
	    if(x>p_half) {
		x-=p;
		if(x>=p_half) x -= p;
	    }
	}
	GET_FLOAT_WORD(hx,x);
	SET_FLOAT_WORD(x,hx^sx);
	return x;
}

/* 
 * wrapper remainderf(x,p)
 */

#include "fdlibm.h"
#include <errno.h>

#ifdef __STDC__
	float remainderf(float x, float y)	/* wrapper remainder */
#else
	float remainderf(x,y)			/* wrapper remainder */
	float x,y;
#endif
{
#ifdef _IEEE_LIBM
	return __ieee754_remainderf(x,y);
#else
	float z;
	z = __ieee754_remainderf(x,y);
	if(_LIB_VERSION == _IEEE_ || isnan(y)) return z;
	if(y==0.0f) {
	    /* remainderf(x,0) */
	    errno = EDOM;
	    return 0.0f/0.0f;
	} else
	    return z;
#endif
}

#ifdef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double remainder(double x, double y)
#else
	double remainder(x,y)
	double x,y;
#endif
{
	return (double) remainderf((float) x, (float) y);
}

#endif /* defined(_DOUBLE_IS_32BITS) */




