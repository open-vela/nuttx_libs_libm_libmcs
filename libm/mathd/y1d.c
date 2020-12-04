// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.

/* 
 * wrapper of j1,y1 
 */

#include "fdlibm.h"
#include <errno.h>

#ifndef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double y1(double x)		/* wrapper y1 */
#else
	double y1(x)			/* wrapper y1 */
	double x;
#endif
{
#ifdef _IEEE_LIBM
	return __ieee754_y1(x);
#else
	double z;
	z = __ieee754_y1(x);
	if(_LIB_VERSION == _IEEE_ || isnan(x) ) return z;
        if(x < 0.0){
	    /* y1(x<0) = NaN */
	    errno = EDOM;
        }
        if(x == 0.0){
	    /* y1(0) = -inf */
	    errno = ERANGE;
        }
	if(x>X_TLOSS) {
	    /* y1(x>X_TLOSS) */
	    errno = ERANGE;
	}
	return z;
#endif
}

#endif /* defined(_DOUBLE_IS_32BITS) */
