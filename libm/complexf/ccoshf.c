// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>

float complex
ccoshf(float complex z)
{
	float complex w;
	float x, y;

	x = crealf(z);
	y = cimagf(z);
	w = coshf(x) * cosf(y) + (sinhf(x) * sinf(y)) * I;
	return w;
}
