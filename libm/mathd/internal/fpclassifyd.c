/* SPDX-License-Identifier: RedHat */
/* Copyright (C) 2002,2007 by  Red Hat, Incorporated. All rights reserved. */

#include <math.h>
#include "../../common/tools.h"

int __fpclassifyd(double x)
{
    uint32_t msw, lsw;

    EXTRACT_WORDS(msw, lsw, x);

    if ((msw == 0x00000000U && lsw == 0x00000000U) ||
        (msw == 0x80000000U && lsw == 0x00000000U)) {
        return FP_ZERO;
    } else if ((msw >= 0x00100000U && msw <= 0x7fefffffU) ||
               (msw >= 0x80100000U && msw <= 0xffefffffU)) {
        return FP_NORMAL;
    } else if ((msw <= 0x000fffffU) ||
               (msw >= 0x80000000U && msw <= 0x800fffffU))
        /* zero is already handled above */
    {
        return FP_SUBNORMAL;
    } else if ((msw == 0x7ff00000U && lsw == 0x00000000U) ||
               (msw == 0xfff00000U && lsw == 0x00000000U)) {
        return FP_INFINITE;
    } else {
        return FP_NAN;
    }
}
