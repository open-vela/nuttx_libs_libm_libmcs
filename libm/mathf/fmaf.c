// SPDX-License-Identifier: GTDGmbH
// Copyright 2020-2021 by GTD GmbH.

float fmaf (float x, float y, float z)
{
    return x * y + z;
}

#ifdef _DOUBLE_IS_32BITS

double fma (double x, double y, double z)
{
	return (double) fmaf((float) x, (float) y, (float) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
