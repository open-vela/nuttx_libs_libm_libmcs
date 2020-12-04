// SPDX-License-Identifier: RedHat
// Copyright (C) 2002 by  Red Hat, Incorporated. All rights reserved.

#include "fdlibm.h"

#ifdef __STDC__
	float fminf(float x, float y)
#else
	float fminf(x,y)
	float x;
	float y;
#endif
{
  if (__fpclassifyf(x) == FP_NAN)
    return y;
  if (__fpclassifyf(y) == FP_NAN)
    return x;
  
  return x < y ? x : y;
}

#ifdef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double fmin(double x, double y)
#else
	double fmin(x,y)
	double x;
	double y;
#endif
{
  return (double) fminf((float) x, (float) y);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
