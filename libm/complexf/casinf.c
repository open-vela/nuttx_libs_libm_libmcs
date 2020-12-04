// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>

#ifdef __weak_alias
__weak_alias(casinf, _casinf)
#endif

float complex
casinf(float complex z)
{
	float complex w;
	float complex ca, ct, zz, z2;
	float x, y;

	x = crealf(z);
	y = cimagf(z);

#if 0 /* MD: test is incorrect, casin(>1) is defined */
	if (y == 0.0f) {
		if (fabsf(x) > 1.0) {
			w = M_PI_2 + 0.0f * I;
#if 0
			mtherr ("casin", DOMAIN);
#endif
		} else {
			w = asinf(x) + 0.0f * I;
		}
		return w;
	}
#endif

/* Power series expansion */
/*
b = cabsf(z);
if( b < 0.125 )
{
z2.r = (x - y) * (x + y);
z2.i = 2.0 * x * y;

cn = 1.0;
n = 1.0;
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
	b = fabsf(ct.r) + fabsf(ct.i);
	}
while( b > MACHEP );
w->r = sum.r;
w->i = sum.i;
return;
}
*/


	ca = x + y * I;
	ct = ca * I;
	/* sqrt( 1 - z*z) */
	/* cmul( &ca, &ca, &zz ) */
	/*x * x  -  y * y */
	zz = (x - y) * (x + y) + (2.0f * x * y) * I;

	zz = 1.0f - crealf(zz) - cimagf(zz) * I;
	z2 = csqrtf(zz);

	zz = ct + z2;
	zz = clogf(zz);
	/* multiply by 1/i = -i */
	w = zz * (-1.0f * I);
	return w;
}
