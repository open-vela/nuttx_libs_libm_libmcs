/* SPDX-License-Identifier: GTDGmbH */
/* Copyright 2020-2021 by GTD GmbH. */

#ifndef _LIBMCS_TRIGD_H_
#define	_LIBMCS_TRIGD_H_

#include "../../common/tools.h"

extern double __sin(double x, double y, int iy);
extern double __cos(double x, double y);
extern int32_t __rem_pio2(double x, double *y);

#endif /* !_LIBMCS_TRIGD_H_ */
