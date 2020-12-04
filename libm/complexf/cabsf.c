// SPDX-License-Identifier: PublicDomain
// Written by Matthias Drochner <drochner@NetBSD.org>.

#include <complex.h>
#include <math.h>

float
cabsf(float complex z)
{

	return hypotf( crealf(z), cimagf(z) );
}
