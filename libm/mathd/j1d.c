/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*
 * wrapper of j1,y1
 */

#include <math.h>
#include "internal/besseld.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double j1(double x)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    return __j1(x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
