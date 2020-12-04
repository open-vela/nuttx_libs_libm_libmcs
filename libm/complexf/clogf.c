// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>

float complex
clogf(float complex z)
{
	float complex w;
	float p, rr;

	rr = cabsf(z);
	p = logf(rr);
	rr = atan2f(cimagf(z), crealf(z));
	w = p + rr * I;
	return w;
}
