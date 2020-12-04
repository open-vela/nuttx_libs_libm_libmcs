// SPDX-License-Identifier: NetBSD

/*
FUNCTION
        <<casin>>, <<casinf>>---complex arc sine

INDEX
        casin
INDEX
        casinf

SYNOPSIS
       #include <complex.h>
       double complex casin(double complex <[z]>);
       float complex casinf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex arc sine of <[z]>,
        with branch cuts outside the interval [-1, +1] along the real axis.

        <<casinf>> is identical to <<casin>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        @ifnottex
        These functions return the complex arc sine value, in the range
        of a strip mathematically  unbounded  along the imaginary axis
        and in the interval [-pi/2, +pi/2] along the real axis.
        @end ifnottex
        @tex
        These functions return the complex arc sine value, in the range
        of a strip mathematically  unbounded  along the imaginary axis
        and in the interval [$-\pi/2$, $+\pi/2$] along the real axis.
        @end tex

PORTABILITY
        <<casin>> and <<casinf>> are ISO C99

QUICKREF
        <<casin>> and <<casinf>> are ISO C99

*/


#include <complex.h>
#include <math.h>

#ifdef __weak_alias
__weak_alias(casin, _casin)
#endif

double complex
casin(double complex z)
{
	double complex w;
	double complex ca, ct, zz, z2;
	double x, y;

	x = creal(z);
	y = cimag(z);

#if 0 /* MD: test is incorrect, casin(>1) is defined */
	if (y == 0.0) {
		if (fabs(x) > 1.0) {
			w = M_PI_2 + 0.0 * I;
#if 0
			mtherr ("casin", DOMAIN);
#endif
		} else {
			w = asin(x) + 0.0 * I;
		}
		return w;
	}
#endif

/* Power series expansion */
/*
b = cabs(z);
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
	b = fabs(ct.r) + fabs(ct.i);
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
	zz = (x - y) * (x + y) + (2.0 * x * y) * I;

	zz = 1.0 - creal(zz) - cimag(zz) * I;
	z2 = csqrt(zz);

	zz = ct + z2;
	zz = clog(zz);
	/* multiply by 1/i = -i */
	w = zz * (-1.0 * I);
	return w;
}
