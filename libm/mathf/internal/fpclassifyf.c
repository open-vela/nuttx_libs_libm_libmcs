/* SPDX-License-Identifier: RedHat */
/* Copyright (C) 2002,2007 by  Red Hat, Incorporated. All rights reserved. */

#include <math.h>
#include "../../common/tools.h"

int __fpclassifyf(float x)
{
    uint32_t w;

    GET_FLOAT_WORD(w, x);

    if (w == 0x00000000U || w == 0x80000000U) {
        return FP_ZERO;
    } else if ((w >= 0x00800000U && w <= 0x7f7fffffU) ||
               (w >= 0x80800000U && w <= 0xff7fffffU)) {
        return FP_NORMAL;
    } else if ((w <= 0x007fffffU) ||
               (w >= 0x80000001U && w <= 0x807fffffU)) {
        return FP_SUBNORMAL;
    } else if (w == 0x7f800000U || w == 0xff800000U) {
        return FP_INFINITE;
    } else {
        return FP_NAN;
    }
}

