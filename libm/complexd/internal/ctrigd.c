// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>

#ifndef _DOUBLE_IS_32BITS

/* calculate cosh and sinh */

void
__cchsh(double x, double *c, double *s)
{
	double e, ei;

	if (fabs(x) <= 0.5) {
		*c = cosh(x);
		*s = sinh(x);
	} else {
		e = exp(x);
		ei = 0.5 / e;
		e = 0.5 * e;
		*s = e - ei;
		*c = e + ei;
	}
}

/* Program to subtract nearest integer multiple of PI */

/* extended precision value of PI: */
static const double DP1 = 3.14159265160560607910E0;
static const double DP2 = 1.98418714791870343106E-9;
static const double DP3 = 1.14423774522196636802E-17;
#define MACHEP 1.1e-16

double
__redupi(double x)
{
	double t;
	long i;

	t = x / M_PI;
	if (t >= 0.0)
		t += 0.5;
	else
		t -= 0.5;

	i = t;	/* the multiple */
	t = i;
	t = ((x - t * DP1) - t * DP2) - t * DP3;
	return t;
}

/* Taylor series expansion for cosh(2y) - cos(2x) */

double
__ctans(double complex z)
{
	double f, x, x2, y, y2, rn, t;
	double d;

	x = fabs(2.0 * creal(z));
	y = fabs(2.0 * cimag(z));

	x = __redupi(x);

	x = x * x;
	y = y * y;
	x2 = 1.0;
	y2 = 1.0;
	f = 1.0;
	rn = 0.0;
	d = 0.0;
	do {
		rn += 1.0;
		f *= rn;
		rn += 1.0;
		f *= rn;
		x2 *= x;
		y2 *= y;
		t = y2 + x2;
		t /= f;
		d += t;

		rn += 1.0;
		f *= rn;
		rn += 1.0;
		f *= rn;
		x2 *= x;
		y2 *= y;
		t = y2 - x2;
		t /= f;
		d += t;
	} while (fabs(t/d) > MACHEP);
	return d;
}

#endif /* defined(_DOUBLE_IS_32BITS) */
