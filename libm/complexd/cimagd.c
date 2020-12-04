// SPDX-License-Identifier: PublicDomain
// Written by Matthias Drochner <drochner@NetBSD.org>.

/*
FUNCTION
        <<cimag>>, <<cimagf>>, <<cimagl>>---imaginary part

INDEX
        cimag
INDEX
        cimagf
INDEX
        cimagl

SYNOPSIS
       #include <complex.h>
       double cimag(double complex <[z]>);
       float cimagf(float complex <[z]>);
       long double cimagl(long double complex <[z]>);


DESCRIPTION
        These functions compute the imaginary part of <[z]>.

        <<cimagf>> is identical to <<cimag>>, except that it performs
        its calculations on <<float complex>>.

        <<cimagl>> is identical to <<cimag>>, except that it performs
        its calculations on <<long double complex>>.

RETURNS
        The cimag* functions return the imaginary part value (as a real).

PORTABILITY
        <<cimag>>, <<cimagf>> and <<cimagl>> are ISO C99

QUICKREF
        <<cimag>>, <<cimagf>> and <<cimagl>> are ISO C99

*/


#include <complex.h>
#include "../common/fdlibm.h"

double
cimag(double complex z)
{
	double_complex w = { .z = z };

	return (IMAG_PART(w));
}
