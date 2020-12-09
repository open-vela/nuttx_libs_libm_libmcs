// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>

float complex
ctanhf(float complex z)
{
	float complex w;
	float x, y, d;

	x = crealf(z);
	y = cimagf(z);
	d = coshf(2.0f * x) + cosf(2.0f * y);
	w = sinhf(2.0f * x) / d  +  (sinf(2.0f * y) / d) * I;

	return w;
}

#ifdef _DOUBLE_IS_32BITS

double complex ctanh (double complex z)
{
	return (double complex) ctanhf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
