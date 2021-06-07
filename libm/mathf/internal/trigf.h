/* SPDX-License-Identifier: GTDGmbH */
/* Copyright 2020-2021 by GTD GmbH. */

#ifndef __LIBMCS_TRIGF_H
#define	__LIBMCS_TRIGF_H

#include "../../common/tools.h"

extern float __sinf(float x, float y, int iy);
extern float __cosf(float x, float y);
extern int32_t __rem_pio2f(float x, float *y);

#endif /* !__LIBMCS_TRIGF_H */
