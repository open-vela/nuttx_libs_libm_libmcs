/* SPDX-License-Identifier: RedHat */
/* Copyright (C) 2002,2007 by  Red Hat, Incorporated. All rights reserved. */

#include "../../common/tools.h"

int __fpclassifyf(float x)
{
    uint32_t w;

    GET_FLOAT_WORD(w, x);

    if (w == 0x00000000 || w == 0x80000000) {
        return FP_ZERO;
    } else if ((w >= 0x00800000 && w <= 0x7f7fffff) ||
               (w >= 0x80800000 && w <= 0xff7fffff)) {
        return FP_NORMAL;
    } else if ((w >= 0x00000001 && w <= 0x007fffff) ||
               (w >= 0x80000001 && w <= 0x807fffff)) {
        return FP_SUBNORMAL;
    } else if (w == 0x7f800000 || w == 0xff800000) {
        return FP_INFINITE;
    } else {
        return FP_NAN;
    }
}

