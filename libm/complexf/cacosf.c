// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>

float complex
cacosf(float complex z)
{
	float complex w;

	w = casinf(z);
	w = ((float)M_PI_2 - crealf(w)) - cimagf(w) * I;
	return w;
}
