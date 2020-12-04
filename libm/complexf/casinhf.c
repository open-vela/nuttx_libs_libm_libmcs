// SPDX-License-Identifier: NetBSD

#include <complex.h>

float complex
casinhf(float complex z)
{
	float complex w;

	w = -1.0f * I * casinf(z * I);
	return w;
}
