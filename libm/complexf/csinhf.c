// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>

float complex
csinhf(float complex z)
{
	float complex w;
	float x, y;

	x = crealf(z);
	y = cimagf(z);
	w = sinhf(x) * cosf(y) + (coshf(x) * sinf(y)) * I;
	return w;
}
