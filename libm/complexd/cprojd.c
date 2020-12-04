// SPDX-License-Identifier: NetBSD

/*
FUNCTION
        <<cproj>>, <<cprojf>>--- Riemann sphere projection
 
INDEX
        cproj
INDEX
        cprojf

SYNOPSIS
       #include <complex.h>
       double complex cproj(double complex <[z]>);
       float complex cprojf(float complex <[z]>);


DESCRIPTION
        These functions compute a projection of <[z]> onto the Riemann 
        sphere: <[z]> projects to <[z]> except that all complex infinities 
        (even those with one infinite part and one NaN part) project 
        to positive infinity on the real axis. If <[z]> has an infinite part,
        then <<cproj>>(<[z]>) is equivalent to

                 INFINITY + I * copysign(0.0, cimag(z))

        <<cprojf>> is identical to <<cproj>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        The cproj functions return the value of the projection onto 
        the Riemann sphere.

PORTABILITY
        <<cproj>> and <<cprojf>> are ISO C99

QUICKREF
        <<cproj>> and <<cprojf>> are ISO C99

*/

#include <sys/cdefs.h>
/*__RCSID("$NetBSD: cproj.c,v 1.3 2010/09/20 17:51:38 christos Exp $"); */

#include <complex.h>
#include <math.h>

#include "../common/fdlibm.h"

/*
 * cproj(double complex z)
 *
 * These functions return the value of the projection (not stereographic!)
 * onto the Riemann sphere.
 *
 * z projects to z, except that all complex infinities (even those with one
 * infinite part and one NaN part) project to positive infinity on the real axis.
 * If z has an infinite part, then cproj(z) shall be equivalent to:
 *
 * INFINITY + I * copysign(0.0, cimag(z))
 */
double complex
cproj(double complex z)
{
	double_complex w = { .z = z };

	if (isinf(creal(z)) || isinf(cimag(z))) {
#ifdef __INFINITY
		REAL_PART(w) = __INFINITY;
#else
		REAL_PART(w) = INFINITY;
#endif
		IMAG_PART(w) = copysign(0.0, cimag(z));
	}

	return (w.z);
}
