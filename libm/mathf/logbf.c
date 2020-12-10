// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

/* float logb(float x)
 * return the binary exponent of non-zero x
 * logbf(0) = -inf, raise divide-by-zero floating point exception
 * logbf(+inf|-inf) = +inf (no signal is raised)
 * logbf(NaN) = NaN (no signal is raised)
 * Per C99 recommendation, a NaN argument is returned unchanged.
 */

#include "fdlibm.h"

float logbf(float x)
{
	__int32_t hx,ix;

	GET_FLOAT_WORD(hx,x);
	hx &= 0x7fffffff;
	if(FLT_UWORD_IS_ZERO(hx))  {
		float  xx;
		/* arg==0:  return -inf and raise divide-by-zero exception */
		SET_FLOAT_WORD(xx,hx);	/* +0.0 */
		return -1./xx;	/* logbf(0) = -inf */
		}
	if(FLT_UWORD_IS_SUBNORMAL(hx)) {
	    for (ix = -126,hx<<=8; hx>0; hx<<=1) ix -=1;
	    return (float) ix;
	}
	else if (FLT_UWORD_IS_INFINITE(hx)) return HUGE_VALF;	/* x==+|-inf */
	else if (FLT_UWORD_IS_NAN(hx)) return x;
	else return (float) ((hx>>23)-127);
}

#ifdef _DOUBLE_IS_32BITS

double logb(double x)
{
	return (double) logbf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
