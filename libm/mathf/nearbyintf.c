// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.

#include <math.h>
#include "fdlibm.h"

#ifdef __STDC__
	float nearbyintf(float x)
#else
	float nearbyintf(x)
	float x;
#endif
{
  return rintf(x);
}

#ifdef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double nearbyint(double x)
#else
	double nearbyint(x)
	double x;
#endif
{
  return (double) nearbyintf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
