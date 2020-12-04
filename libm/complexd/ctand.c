// SPDX-License-Identifier: NetBSD

/*
FUNCTION
        <<ctan>>, <<ctanf>>---complex tangent

INDEX
        ctan
INDEX
        ctanf

SYNOPSIS
       #include <complex.h>
       double complex ctan(double complex <[z]>);
       float complex ctanf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex tangent of <[z]>.

        <<ctanf>> is identical to <<ctan>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        These functions return the complex tangent value.

PORTABILITY
        <<ctan>> and <<ctanf>> are ISO C99

QUICKREF
        <<ctan>> and <<ctanf>> are ISO C99

*/


#include <complex.h>
#include <math.h>
#include "cephes_subr.h"

double complex
ctan(double complex z)
{
	double complex w;
	double d;

	d = cos(2.0 * creal(z)) + cosh(2.0 * cimag(z));

	if (fabs(d) < 0.25)
		d = _ctans(z);

	if (d == 0.0) {
		/* mtherr ("ctan", OVERFLOW); */
		w = HUGE_VAL + HUGE_VAL * I;
		return w;
	}

	w = sin(2.0 * creal(z)) / d + (sinh(2.0 * cimag(z)) / d) * I;
	return w;
}
