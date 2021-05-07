/* SPDX-License-Identifier: GTDGmbH */
/* Copyright 2020-2021 by GTD GmbH. */

#include <math.h>
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double nan(const char *payload)
{
    (void)payload;

    double x;
    INSERT_WORDS(x,0x7FF80000,0x000D067D);
    return x;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double nanl(const char *payload)
{
    return (long double) nan(payload);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
