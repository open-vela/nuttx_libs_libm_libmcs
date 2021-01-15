/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*
 * wrapper of j1,y1
 */

#include "../common/tools.h"

#ifndef _DOUBLE_IS_32BITS

double y1(double x)
{
    return __y1(x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
