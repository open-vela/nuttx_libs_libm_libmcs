// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.

/* __ieee754_cosh(x)
 * Method : 
 * mathematically cosh(x) if defined to be (exp(x)+exp(-x))/2
 *	1. Replace x by |x| (cosh(x) = cosh(-x)). 
 *	2. 
 *		                                        [ exp(x) - 1 ]^2 
 *	    0        <= x <= ln2/2  :  cosh(x) := 1 + -------------------
 *			       			           2*exp(x)
 *
 *		                                  exp(x) +  1/exp(x)
 *	    ln2/2    <= x <= 22     :  cosh(x) := -------------------
 *			       			          2
 *	    22       <= x <= lnovft :  cosh(x) := exp(x)/2 
 *	    lnovft   <= x <= ln2ovft:  cosh(x) := exp(x/2)/2 * exp(x/2)
 *	    ln2ovft  <  x	    :  cosh(x) := overflow
 *
 * Special cases:
 *	cosh(x) is |x| if x is +INF, -INF, or NaN.
 *	only cosh(0)=1 is exact for finite x.
 */

#include "fdlibm.h"
#include "math_config.h"

#ifndef _DOUBLE_IS_32BITS

#ifdef __STDC__
static const double one = 1.0, half=0.5;
#else
static double one = 1.0, half=0.5;
#endif

#ifdef __STDC__
	double __ieee754_cosh(double x)
#else
	double __ieee754_cosh(x)
	double x;
#endif
{	
	double t,w;
	__int32_t ix;
	__uint32_t lx;

    /* High word of |x|. */
	GET_HIGH_WORD(ix,x);
	ix &= 0x7fffffff;

    /* x is INF or NaN */
	if(ix>=0x7ff00000) return x*x;	

    /* |x| in [0,0.5*ln2], return 1+expm1(|x|)^2/(2*exp(|x|)) */
	if(ix<0x3fd62e43) {
	    t = expm1(fabs(x));
	    w = one+t;
	    if (ix<0x3c800000) return w;	/* cosh(tiny) = 1 */
	    return one+(t*t)/(w+w);
	}

    /* |x| in [0.5*ln2,22], return (exp(|x|)+1/exp(|x|)/2; */
	if (ix < 0x40360000) {
		t = __ieee754_exp(fabs(x));
		return half*t+half/t;
	}

    /* |x| in [22, log(maxdouble)] return half*exp(|x|) */
	if (ix < 0x40862E42)  return half*__ieee754_exp(fabs(x));

    /* |x| in [log(maxdouble), overflowthresold] */
	GET_LOW_WORD(lx,x);
	if (ix<0x408633CE || 
             (ix==0x408633ce && lx<=(__uint32_t)0x8fb9f87d)) {
	    w = __ieee754_exp(half*fabs(x));
	    t = half*w;
	    return t*w;
	}

    /* |x| > overflowthresold, cosh(x) overflow */
	return __math_oflow(0);
}

#endif /* defined(_DOUBLE_IS_32BITS) */

/*

FUNCTION
        <<cosh>>, <<coshf>>---hyperbolic cosine

SYNOPSIS
        #include <math.h>
        double cosh(double <[x]>);
        float coshf(float <[x]>);

DESCRIPTION

	<<cosh>> computes the hyperbolic cosine of the argument <[x]>.
	<<cosh(<[x]>)>> is defined as 
	@ifnottex
	. (exp(x) + exp(-x))/2
	@end ifnottex
	@tex
	$${(e^x + e^{-x})} \over 2$$
	@end tex

	Angles are specified in radians.  
		
	<<coshf>> is identical, save that it takes and returns <<float>>.

RETURNS
	The computed value is returned.  When the correct value would create
	an overflow,  <<cosh>> returns the value <<HUGE_VAL>> with the
	appropriate sign, and the global value <<errno>> is set to <<ERANGE>>.

PORTABILITY
	<<cosh>> is ANSI.  
	<<coshf>> is an extension.

QUICKREF
	cosh ansi pure
	coshf - pure
*/

/* 
 * wrapper cosh(x)
 */

#include "fdlibm.h"
#include <errno.h>

#ifndef _DOUBLE_IS_32BITS
 
#ifdef __STDC__
	double cosh(double x)		/* wrapper cosh */
#else
	double cosh(x)			/* wrapper cosh */
	double x;
#endif
{
#ifdef _IEEE_LIBM
	return __ieee754_cosh(x);
#else
	double z;
	z = __ieee754_cosh(x);
	if(_LIB_VERSION == _IEEE_ || isnan(x)) return z;
	if(fabs(x)>7.10475860073943863426e+02) {	
	    /* cosh(finite) overflow */
	    errno = ERANGE;
	    return HUGE_VAL;
	} else
	    return z;
#endif
}

#endif /* defined(_DOUBLE_IS_32BITS) */
