// SPDX-License-Identifier: NetBSD

/*
FUNCTION
        <<cpow>>, <<cpowf>>---complex power

INDEX
        cpow
INDEX
        cpowf

SYNOPSIS
       #include <complex.h>
       double complex cpow(double complex <[x]>, double complex <[y]>);
       float complex cpowf(float complex <[x]>, float complex <[y]>);


DESCRIPTION
        @ifnottex
        The cpow functions compute the complex power function x^y 
        power, with a branch cut for the first parameter along the 
        negative real axis.
        @end ifnottex
        @tex
        The cpow functions compute the complex power function $x^y$ 
        power, with a branch cut for the first parameter along the 
        negative real axis.
        @end tex

        <<cpowf>> is identical to <<cpow>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        The cpow functions return the complex power function value.

PORTABILITY
        <<cpow>> and <<cpowf>> are ISO C99

QUICKREF
        <<cpow>> and <<cpowf>> are ISO C99

*/


#include <complex.h>
#include <math.h>

double complex
cpow(double complex a, double complex z)
{
	double complex w;
	double x, y, r, theta, absa, arga;

	x = creal(z);
	y = cimag(z);
	absa = cabs(a);
	if (absa == 0.0) {
		return (0.0 + 0.0 * I);
	}
	arga = carg(a);
	r = pow(absa, x);
	theta = x * arga;
	if (y != 0.0) {
		r = r * exp(-y * arga);
		theta = theta + y * log(absa);
	}
	w = r * cos(theta) + (r * sin(theta)) * I;
	return w;
}
