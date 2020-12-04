// SPDX-License-Identifier: NetBSD

#include <complex.h>

float complex
catanhf(float complex z)
{
	float complex w;

	w = -1.0f * I * catanf(z * I);
	return w;
}
