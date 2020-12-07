// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

/* 
 * wrapper exp2f(x)
 */

#include "fdlibm.h"
#include <math.h>

float exp2f(float x)		/* wrapper exp2f */
{
  return powf(2.0, x);
}

#ifdef _DOUBLE_IS_32BITS

double exp2(double x)
{
	return (double) exp2f((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
