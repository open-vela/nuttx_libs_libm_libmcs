// SPDX-License-Identifier: PublicDomain
// Written by Matthias Drochner <drochner@NetBSD.org>.

#include <complex.h>
#include "../common/fdlibm.h"

float
cimagf(float complex z)
{
	float_complex w = { .z = z };

	return (IMAG_PART(w));
}
