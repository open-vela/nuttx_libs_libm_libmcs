// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>

float complex
cpowf(float complex a, float complex z)
{
	float complex w;
	float x, y, r, theta, absa, arga;

	x = crealf(z);
	y = cimagf(z);
	absa = cabsf(a);
	if (absa == 0.0f) {
		return (0.0f + 0.0f * I);
	}
	arga = cargf(a);
	r = powf(absa, x);
	theta = x * arga;
	if (y != 0.0f) {
		r = r * expf(-y * arga);
		theta = theta + y * logf(absa);
	}
	w = r * cosf(theta) + (r * sinf(theta)) * I;
	return w;
}
