/* SPDX-License-Identifier: GTDGmbH */
/* Copyright 2020-2021 by GTD GmbH. */

#ifndef _LIBMCS_TRIGF_H_
#define	_LIBMCS_TRIGF_H_

#include "../../common/tools.h"

extern float __sinf(float x, float y, int iy);
extern float __cosf(float x, float y);
extern int32_t __rem_pio2f(float x, float *y);

#endif /* !_LIBMCS_TRIGF_H_ */
