// SPDX-License-Identifier: NetBSD

#include <complex.h>

float complex
cacoshf(float complex z)
{
	float complex w;

	w = clogf(z + csqrtf(z + 1) * csqrtf(z - 1));

	return w;
}

#ifdef _DOUBLE_IS_32BITS

double complex cacosh (double complex z)
{
	return (double complex) cacoshf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
