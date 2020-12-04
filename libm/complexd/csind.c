// SPDX-License-Identifier: NetBSD

/*
FUNCTION
        <<csin>>, <<csinf>>---complex sine

INDEX
        csin
INDEX
        csinf

SYNOPSIS
       #include <complex.h>
       double complex csin(double complex <[z]>);
       float complex csinf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex sine of <[z]>.

        <<csinf>> is identical to <<csin>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        These functions return the complex sine value.

PORTABILITY
        <<csin>> and <<csinf>> are ISO C99

QUICKREF
        <<csin>> and <<csinf>> are ISO C99

*/


#include <complex.h>
#include <math.h>
#include "cephes_subr.h"

double complex
csin(double complex z)
{
	double complex w;
	double ch, sh;

	_cchsh(cimag(z), &ch, &sh);
	w = sin(creal(z)) * ch + (cos(creal(z)) * sh) * I;
	return w;
}
