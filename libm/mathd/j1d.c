/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*
 * wrapper of j1,y1
 */

#include "../common/tools.h"
#include "internal/besseld.h"

#ifndef _DOUBLE_IS_32BITS

double j1(double x)
{
    return __j1(x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
