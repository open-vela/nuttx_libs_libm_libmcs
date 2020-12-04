// SPDX-License-Identifier: NetBSD
// Copyright (c) 2007 The NetBSD Foundation, Inc.

#include <complex.h>
#include <math.h>

#ifdef __weak_alias
__weak_alias(casinl, _casinl)
#endif

long double complex
casinl(long double complex z)
{
	long double complex w;
	long double complex ca, ct, zz, z2;
	long double x, y;

	x = creall(z);
	y = cimagl(z);

#if 0 /* MD: test is incorrect, casin(>1) is defined */
	if (y == 0.0L) {
		if (fabsl(x) > 1.0L) {
			w = M_PI_2L + 0.0L * I;
#if 0
			mtherr ("casinl", DOMAIN);
#endif
		} else {
			w = asinl(x) + 0.0L * I;
		}
		return w;
	}
#endif

/* Power series expansion */
/*
b = cabsl(z);
if( b < 0.125L )
{
z2.r = (x - y) * (x + y);
z2.i = 2.0L * x * y;

cn = 1.0L;
n = 1.0L;
ca.r = x;
ca.i = y;
sum.r = x;
sum.i = y;
do
	{
	ct.r = z2.r * ca.r  -  z2.i * ca.i;
	ct.i = z2.r * ca.i  +  z2.i * ca.r;
	ca.r = ct.r;
	ca.i = ct.i;

	cn *= n;
	n += 1.0;
	cn /= n;
	n += 1.0;
	b = cn/n;

	ct.r *= b;
	ct.i *= b;
	sum.r += ct.r;
	sum.i += ct.i;
	b = fabsl(ct.r) + fabsl(ct.i);
	}
while( b > MACHEPL );
w->r = sum.r;
w->i = sum.i;
return;
}
*/


	ca = x + y * I;
	ct = ca * I;
	/* sqrtl( 1 - z*z) */
	/* cmull( &ca, &ca, &zz ) */
	/*x * x  -  y * y */
	zz = (x - y) * (x + y) + (2.0L * x * y) * I;

	zz = 1.0L - creall(zz) - cimagl(zz) * I;
	z2 = csqrtl(zz);

	zz = ct + z2;
	zz = clogl(zz);
	/* multiply by 1/i = -i */
	w = zz * (-1.0L * I);
	return w;
}

