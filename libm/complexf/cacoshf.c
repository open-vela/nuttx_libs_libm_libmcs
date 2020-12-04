// SPDX-License-Identifier: NetBSD

#include <complex.h>

float complex
cacoshf(float complex z)
{
	float complex w;

#if 0 /* does not give the principal value */
	w = I * cacosf(z);
#else
	w = clogf(z + csqrtf(z + 1) * csqrtf(z - 1));
#endif
	return w;
}
