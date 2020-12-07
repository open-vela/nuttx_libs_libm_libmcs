// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.

/* 
 * wrapper of j1,y1 
 */

#include "fdlibm.h"

#ifndef _DOUBLE_IS_32BITS

double j1(double x)		/* wrapper j1 */
{
	return __ieee754_j1(x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
