// SPDX-License-Identifier: NetBSD

/*
FUNCTION
        <<csinh>>, <<csinhf>>---complex hyperbolic sine

INDEX
        csinh
INDEX
        csinhf

SYNOPSIS
       #include <complex.h>
       double complex csinh(double complex <[z]>);
       float complex csinhf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex hyperbolic sine of <[z]>.

        <<ccoshf>> is identical to <<ccosh>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        These functions return the complex hyperbolic sine value.

PORTABILITY
        <<csinh>> and <<csinhf>> are ISO C99

QUICKREF
        <<csinh>> and <<csinhf>> are ISO C99

*/

#include <complex.h>
#include <math.h>

double complex
csinh(double complex z)
{
	double complex w;
	double x, y;

	x = creal(z);
	y = cimag(z);
	w = sinh(x) * cos(y) + (cosh(x) * sin(y)) * I;
	return w;
}
