// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

#include "fdlibm.h"

#ifdef __STDC__
static const float
#else
static float
#endif
two25      =  3.3554432000e+07, /* 0x4c000000 */
ivln10     =  4.3429449201e-01, /* 0x3ede5bd9 */
log10_2hi  =  3.0102920532e-01, /* 0x3e9a2080 */
log10_2lo  =  7.9034151668e-07; /* 0x355427db */

#ifdef __STDC__
static const float zero   =  0.0;
#else
static float zero   =  0.0;
#endif

#ifdef __STDC__
	float __ieee754_log10f(float x)
#else
	float __ieee754_log10f(x)
	float x;
#endif
{
	float y,z;
	__int32_t i,k,hx;

	GET_FLOAT_WORD(hx,x);

        k=0;
        if (FLT_UWORD_IS_ZERO(hx&0x7fffffff))
            return -two25/zero;             /* log(+-0)=-inf */
        if (hx<0) return (x-x)/zero;        /* log(-#) = NaN */
	if (!FLT_UWORD_IS_FINITE(hx)) return x+x;
        if (FLT_UWORD_IS_SUBNORMAL(hx)) {
            k -= 25; x *= two25; /* subnormal number, scale up x */
	    GET_FLOAT_WORD(hx,x);
        }
	k += (hx>>23)-127;
	i  = ((__uint32_t)k&0x80000000)>>31;
        hx = (hx&0x007fffff)|((0x7f-i)<<23);
        y  = (float)(k+i);
	SET_FLOAT_WORD(x,hx);
	z  = y*log10_2lo + ivln10*__ieee754_logf(x);
	return  z+y*log10_2hi;
}

/* 
 * wrapper log10f(X)
 */

#include "fdlibm.h"
#include <errno.h>

#ifdef __STDC__
	float log10f(float x)		/* wrapper log10f */
#else
	float log10f(x)			/* wrapper log10f */
	float x;
#endif
{
#ifdef _IEEE_LIBM
	return __ieee754_log10f(x);
#else
	float z;
	z = __ieee754_log10f(x);
	if(_LIB_VERSION == _IEEE_ || isnan(x)) return z;
	if(x<=0.0f) {
	    if(x==0.0f) {
		/* log10f(0) */
		errno = ERANGE;
		return -HUGE_VALF;
	    } else { 
		/* log10f(x<0) */
		errno = EDOM;
		return nanf("");
            }
	} else
	    return z;
#endif
}

#ifdef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double log10(double x)
#else
	double log10(x)
	double x;
#endif
{
	return (double) log10f((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
