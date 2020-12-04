// SPDX-License-Identifier: NetBSD

/*
FUNCTION
        <<cacos>>, <<cacosf>>---complex arc cosine

INDEX
        cacos
INDEX
        cacosf

SYNOPSIS
       #include <complex.h>
       double complex cacos(double complex <[z]>);
       float complex cacosf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex arc cosine of <[z]>,
        with branch cuts outside the interval [-1, +1] along the real axis.

        <<cacosf>> is identical to <<cacos>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        @ifnottex
        These functions return the complex arc cosine value, in the range
        of a strip mathematically  unbounded  along the imaginary axis
        and in the interval [0, pi] along the real axis.
        @end ifnottex
        @tex
        These functions return the complex arc cosine value, in the range
        of a strip mathematically  unbounded  along the imaginary axis
        and in the interval [<<0>>, $\pi$] along the real axis.
        @end tex

PORTABILITY
        <<cacos>> and <<cacosf>> are ISO C99

QUICKREF
        <<cacos>> and <<cacosf>> are ISO C99

*/

#include <complex.h>
#include <math.h>

double complex
cacos(double complex z)
{
	double complex w;

	/* FIXME: The original NetBSD code results in an ICE when trying to
	   build this function on ARM/Thumb using gcc 4.5.1.  For now we use
	   a hopefully temporary workaround. */
#if 0
	w = casin(z);
	w = (M_PI_2 - creal(w)) - cimag(w) * I;
#else
	double complex tmp0, tmp1;

	tmp0 = casin(z);
	tmp1 = M_PI_2 - creal(tmp0);
	w = tmp1 - (cimag(tmp0) * I);
#endif
	return w;
}
