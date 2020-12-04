// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.

/* __ieee754_atanh(x)
 * Method :
 *    1.Reduced x to positive by atanh(-x) = -atanh(x)
 *    2.For x>=0.5
 *                  1              2x                          x
 *	atanh(x) = --- * log(1 + -------) = 0.5 * log1p(2 * --------)
 *                  2             1 - x                      1 - x
 *	
 * 	For x<0.5
 *	atanh(x) = 0.5*log1p(2x+2x*x/(1-x))
 *
 * Special cases:
 *	atanh(x) is NaN if |x| > 1 with signal;
 *	atanh(NaN) is that NaN with no signal;
 *	atanh(+-1) is +-INF with signal.
 *
 */

#include "fdlibm.h"

#ifndef _DOUBLE_IS_32BITS

#ifdef __STDC__
static const double one = 1.0, huge = 1e300;
#else
static double one = 1.0, huge = 1e300;
#endif

#ifdef __STDC__
static const double zero = 0.0;
#else
static double zero = 0.0;
#endif

#ifdef __STDC__
	double __ieee754_atanh(double x)
#else
	double __ieee754_atanh(x)
	double x;
#endif
{
	double t;
	__int32_t hx,ix;
	__uint32_t lx;
	EXTRACT_WORDS(hx,lx,x);
	ix = hx&0x7fffffff;
	if ((ix|((lx|(-lx))>>31))>0x3ff00000) /* |x|>1 */
	    return (x-x)/(x-x);
	if(ix==0x3ff00000) 
	    return x/zero;
	if(ix<0x3e300000&&(huge+x)>zero) return x;	/* x<2**-28 */
	SET_HIGH_WORD(x,ix);
	if(ix<0x3fe00000) {		/* x < 0.5 */
	    t = x+x;
	    t = 0.5*log1p(t+t*x/(one-x));
	} else 
	    t = 0.5*log1p((x+x)/(one-x));
	if(hx>=0) return t; else return -t;
}

#endif /* defined(_DOUBLE_IS_32BITS) */

/*
FUNCTION
	<<atanh>>, <<atanhf>>---inverse hyperbolic tangent 

INDEX
	atanh
INDEX
	atanhf

SYNOPSIS
	#include <math.h>
	double atanh(double <[x]>);
	float atanhf(float <[x]>);

DESCRIPTION
	<<atanh>> calculates the inverse hyperbolic tangent of <[x]>.

	<<atanhf>> is identical, other than taking and returning
	<<float>> values.

RETURNS
	<<atanh>> and <<atanhf>> return the calculated value.

	If 
	@ifnottex
	|<[x]>|
	@end ifnottex
	@tex
	$|x|$
	@end tex
	is greater than 1, the global <<errno>> is set to <<EDOM>> and
	the result is a NaN.  A <<DOMAIN error>> is reported.

	If 
	@ifnottex
	|<[x]>|
	@end ifnottex
	@tex
	$|x|$
	@end tex
	is 1, the global <<errno>> is set to <<EDOM>>; and the result is 
	infinity with the same sign as <<x>>.  A <<SING error>> is reported.

PORTABILITY
	Neither <<atanh>> nor <<atanhf>> are ANSI C.

QUICKREF
	atanh - pure
	atanhf - pure


*/

/* 
 * wrapper atanh(x)
 */

#include "fdlibm.h"
#include <errno.h>

#ifndef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double atanh(double x)		/* wrapper atanh */
#else
	double atanh(x)			/* wrapper atanh */
	double x;
#endif
{
#ifdef _IEEE_LIBM
	return __ieee754_atanh(x);
#else
	double z,y;
	z = __ieee754_atanh(x);
	if(_LIB_VERSION == _IEEE_ || isnan(x)) return z;
	y = fabs(x);
	if(y>=1.0) {
	    if(y>1.0) {
		/* atanh(|x|>1) */
		errno = EDOM;
		return 0.0/0.0;
	    } else { 
		/* atanh(|x|=1) */
		errno = EDOM;
		return x/0.0;	/* sign(x)*inf */
	    }
	} else
	    return z;
#endif
}

#endif /* defined(_DOUBLE_IS_32BITS) */
