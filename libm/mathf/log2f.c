// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

/*
 * wrapper log2f(x)
 */

#include "fdlibm.h"
#if __OBSOLETE_MATH
#include <errno.h>
#include <math.h>
#undef log2
#undef log2f

#ifdef __STDC__
	float log2f(float x)		/* wrapper log2f */
#else
	float log2f(x)			/* wrapper log2f */
	float x;
#endif
{
  return (logf(x) / (float_t) M_LN2);
}

#ifdef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double log2(double x)
#else
	double log2(x)
	double x;
#endif
{
	return (double) log2f((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
#endif /* __OBSOLETE_MATH */
