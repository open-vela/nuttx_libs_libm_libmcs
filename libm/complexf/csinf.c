// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>
#include "cephes_subrf.h"

float complex
csinf(float complex z)
{
	float complex w;
	float ch, sh;

	_cchshf(cimagf(z), &ch, &sh);
	w = sinf(crealf(z)) * ch + (cosf(crealf(z)) * sh) * I;
	return w;
}
