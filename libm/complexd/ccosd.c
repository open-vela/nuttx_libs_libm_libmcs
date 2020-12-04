// SPDX-License-Identifier: NetBSD

/*
FUNCTION
        <<ccos>>, <<ccosf>>---complex cosine

INDEX
        ccos
INDEX
        ccosf

SYNOPSIS
       #include <complex.h>
       double complex ccos(double complex <[z]>);
       float complex ccosf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex cosine of <[z]>.

        <<ccosf>> is identical to <<ccos>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        These functions return the complex cosine value.

PORTABILITY
        <<ccos>> and <<ccosf>> are ISO C99

QUICKREF
        <<ccos>> and <<ccosf>> are ISO C99

*/


#include <complex.h>
#include <math.h>
#include "cephes_subr.h"

double complex
ccos(double complex z)
{
	double complex w;
	double ch, sh;

	_cchsh(cimag(z), &ch, &sh);
	w = cos(creal(z)) * ch - (sin(creal(z)) * sh) * I;
	return w;
}
