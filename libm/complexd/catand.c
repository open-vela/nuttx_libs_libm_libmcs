// SPDX-License-Identifier: NetBSD

/*
FUNCTION
        <<catan>>, <<catanf>>---complex arc tangent

INDEX
        catan
INDEX
        catanf

SYNOPSIS
       #include <complex.h>
       double complex catan(double complex <[z]>);
       float complex catanf(float complex <[z]>);


DESCRIPTION
        @ifnottex
        These functions compute the complex arc tangent of <[z]>,
        with branch cuts outside the interval [-i, +i] along the 
        imaginary axis.
        @end ifnottex
        @tex
        These functions compute the complex arc tangent of <[z]>,
        with branch cuts outside the interval [$-i$, $+i$] along the 
        imaginary axis.
        @end tex

        <<catanf>> is identical to <<catan>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        @ifnottex
        These functions return the complex arc tangent value, in the range
        of a strip mathematically  unbounded  along the imaginary axis
        and in the interval [-pi/2, +pi/2] along the real axis.
        @end ifnottex
        @tex
        These functions return the complex arc tangent, in the range
        of a strip mathematically  unbounded  along the imaginary axis
        and in the interval [$-\pi/2$, $+\pi/2$] along the real axis.
        @end tex

PORTABILITY
        <<catan>> and <<catanf>> are ISO C99

QUICKREF
        <<catan>> and <<catanf>> are ISO C99

*/


#include <complex.h>
#include <math.h>
#include "cephes_subr.h"

#ifdef __weak_alias
__weak_alias(catan, _catan)
#endif

double complex
catan(double complex z)
{
	double complex w;
	double a, t, x, x2, y;

	x = creal(z);
	y = cimag(z);

	if ((x == 0.0) && (y > 1.0))
		goto ovrf;

	x2 = x * x;
	a = 1.0 - x2 - (y * y);
	if (a == 0.0)
		goto ovrf;

	t = 0.5 * atan2(2.0 * x, a);
	w = _redupi(t);

	t = y - 1.0;
	a = x2 + (t * t);
	if (a == 0.0)
		goto ovrf;

	t = y + 1.0;
	a = (x2 + (t * t))/a;
	w = w + (0.25 * log(a)) * I;
	return w;

ovrf:
#if 0
	mtherr ("catan", OVERFLOW);
#endif
	w = HUGE_VAL + HUGE_VAL * I;
	return w;
}
