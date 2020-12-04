// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>
#include "cephes_subrf.h"

/* calculate cosh and sinh */

void
_cchshf(float x, float *c, float *s)
{
	float e, ei;

	if (fabsf(x) <= 0.5f) {
		*c = coshf(x);
		*s = sinhf(x);
	} else {
		e = expf(x);
		ei = 0.5f / e;
		e = 0.5f * e;
		*s = e - ei;
		*c = e + ei;
	}
}

/* Program to subtract nearest integer multiple of PI */

/* extended precision value of PI: */
static const double DP1 =  3.140625;
static const double DP2 =  9.67502593994140625E-4;
static const double DP3 =  1.509957990978376432E-7;
#define MACHEPF 3.0e-8

float
_redupif(float x)
{
	float t;
	long i;

	t = x / (float)M_PI;
	if (t >= 0.0f)
		t += 0.5f;
	else
		t -= 0.5f;

	i = t;	/* the multiple */
	t = i;
	t = ((x - t * DP1) - t * DP2) - t * DP3;
	return t;
}

/* Taylor series expansion for cosh(2y) - cos(2x) */

float
_ctansf(float complex z)
{
	float f, x, x2, y, y2, rn, t, d;

	x = fabsf(2.0f * crealf(z));
	y = fabsf(2.0f * cimagf(z));

	x = _redupif(x);

	x = x * x;
	y = y * y;
	x2 = 1.0f;
	y2 = 1.0f;
	f = 1.0f;
	rn = 0.0f;
	d = 0.0f;
	do {
		rn += 1.0f;
		f *= rn;
		rn += 1.0f;
		f *= rn;
		x2 *= x;
		y2 *= y;
		t = y2 + x2;
		t /= f;
		d += t;

		rn += 1.0f;
		f *= rn;
		rn += 1.0f;
		f *= rn;
		x2 *= x;
		y2 *= y;
		t = y2 - x2;
		t /= f;
		d += t;
	} while (fabsf(t/d) > MACHEPF);
	return d;
}
