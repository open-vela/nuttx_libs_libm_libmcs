// SPDX-License-Identifier: NetBSD

/*
FUNCTION
        <<cexp>>, <<cexpf>>---complex base-e exponential

INDEX
        cexp
INDEX
        cexpf

SYNOPSIS
       #include <complex.h>
       double complex cexp(double complex <[z]>);
       float complex cexpf(float complex <[z]>);


DESCRIPTION
        These functions compute  the complex base-<[e]> exponential of <[z]>.

        <<cexpf>> is identical to <<cexp>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        The cexp functions return the complex base-<[e]> exponential value.

PORTABILITY
        <<cexp>> and <<cexpf>> are ISO C99

QUICKREF
        <<cexp>> and <<cexpf>> are ISO C99

*/


#include <complex.h>
#include <math.h>

double complex
cexp(double complex z)
{
	double complex w;
	double r, x, y;

	x = creal(z);
	y = cimag(z);
	r = exp(x);
	w = r * cos(y) + r * sin(y) * I;
	return w;
}
