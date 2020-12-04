// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>

float complex
cexpf(float complex z)
{
	float complex w;
	float r, x, y;

	x = crealf(z);
	y = cimagf(z);
	r = expf(x);
	w = r * cosf(y) + r * sinf(y) * I;
	return w;
}
