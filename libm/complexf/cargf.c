// SPDX-License-Identifier: PublicDomain
// Written by Matthias Drochner <drochner@NetBSD.org>.

#include <complex.h>
#include <math.h>

float
cargf(float complex z)
{
	return atan2f( cimagf(z), crealf(z) );
}
