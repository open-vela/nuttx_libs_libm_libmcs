// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

/* 
 * wrapper exp2f(x)
 */

#include "fdlibm.h"
#if __OBSOLETE_MATH
#include <errno.h>
#include <math.h>

#ifdef __STDC__
	float exp2f(float x)		/* wrapper exp2f */
#else
	float exp2f(x)			/* wrapper exp2f */
	float x;
#endif
{
  return powf(2.0, x);
}

#ifdef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double exp2(double x)
#else
	double exp2(x)
	double x;
#endif
{
	return (double) exp2f((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
#endif /* __OBSOLETE_MATH */
