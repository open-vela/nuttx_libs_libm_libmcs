// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>
#include "cephes_subrf.h"

float complex
ccosf(float complex z)
{
	float complex w;
	float ch, sh;

	_cchshf(cimagf(z), &ch, &sh);
	w = cosf(crealf(z)) * ch - (sinf(crealf(z)) * sh) * I;
	return w;
}
