// SPDX-License-Identifier: RedHat
// Copyright (C) 2015 by  Red Hat, Incorporated. All rights reserved.

#include <complex.h>
#include <math.h>

long double
cabsl (long double complex z)
{
#ifdef _LDBL_EQ_DBL
  return cabs (z);
#else
  return hypotl (creall (z), cimagl (z));
#endif
}
