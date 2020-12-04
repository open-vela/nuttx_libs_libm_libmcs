// SPDX-License-Identifier: NetBSD

/*
FUNCTION
        <<ctanh>>, <<ctanf>>---complex hyperbolic tangent

INDEX
        ctanh
INDEX
        ctanhf

SYNOPSIS
       #include <complex.h>
       double complex ctanh(double complex <[z]>);
       float complex ctanhf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex hyperbolic tangent of <[z]>.

        <<ctanhf>> is identical to <<ctanh>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        These functions return the complex hyperbolic tangent value.

PORTABILITY
        <<ctanh>> and <<ctanhf>> are ISO C99

QUICKREF
        <<ctanh>> and <<ctanhf>> are ISO C99

*/


#include <complex.h>
#include <math.h>

double complex
ctanh(double complex z)
{
	double complex w;
	double x, y, d;

	x = creal(z);
	y = cimag(z);
	d = cosh(2.0 * x) + cos(2.0 * y);
	w = sinh(2.0 * x) / d  +  (sin(2.0 * y) / d) * I;

	return w;
}
