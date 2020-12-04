// SPDX-License-Identifier: PublicDomain
// Written by Matthias Drochner <drochner@NetBSD.org>.

#include <complex.h>
#include "../common/fdlibm.h"

float
crealf(float complex z)
{
	float_complex w = { .z = z };

	return (REAL_PART(w));
}
