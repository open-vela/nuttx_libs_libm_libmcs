// SPDX-License-Identifier: NetBSD

#include <complex.h>

float complex
cacoshf(float complex z)
{
	float complex w;

	w = clogf(z + csqrtf(z + 1) * csqrtf(z - 1));

	return w;
}
