// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.

/* 
 * wrapper of j1,y1 
 */

#include "fdlibm.h"
#include <errno.h>

#ifndef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double j1(double x)		/* wrapper j1 */
#else
	double j1(x)			/* wrapper j1 */
	double x;
#endif
{
#ifdef _IEEE_LIBM
	return __ieee754_j1(x);
#else
	double z;
	z = __ieee754_j1(x);
	if(_LIB_VERSION == _IEEE_ || isnan(x) ) return z;
	if(fabs(x)>X_TLOSS) {
	    /* j1(|x|>X_TLOSS) */
	    errno = ERANGE;
	    return 0.0;
	} else
	    return z;
#endif
}

#endif /* defined(_DOUBLE_IS_32BITS) */
