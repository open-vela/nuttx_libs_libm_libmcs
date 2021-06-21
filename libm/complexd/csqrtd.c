/* SPDX-License-Identifier: NetBSD */

/*
FUNCTION
        <<csqrt>>, <<csqrtf>>---complex square root

INDEX
        csqrt
INDEX
        csqrtf

SYNOPSIS
       #include <complex.h>
       double complex csqrt(double complex <[z]>);
       float complex csqrtf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex square root of <[z]>, with
        a branch cut along the negative real axis.

        <<csqrtf>> is identical to <<csqrt>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        The csqrt functions return the complex square root value, in
        the range of the right halfplane (including the imaginary axis).

PORTABILITY
        <<csqrt>> and <<csqrtf>> are ISO C99

QUICKREF
        <<csqrt>> and <<csqrtf>> are ISO C99

*/


#include <complex.h>
#include <math.h>

#ifndef __LIBMCS_DOUBLE_IS_32BITS

double complex csqrt(double complex z)
{
#ifdef __LIBMCS_FPU_DAZ
    z *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    double complex w;
    double x, y, r, t, scale;

    x = creal(z);
    y = cimag(z);

    if (y == 0.0) {
        if (x == 0.0) {
            w = 0.0 + y * I;
        } else {
            r = fabs(x);
            r = sqrt(r);

            if (x < 0.0) {
                w = 0.0 + r * I;
            } else {
                w = r + y * I;
            }
        }

        return w;
    }

    if (x == 0.0) {
        r = fabs(y);
        r = sqrt(0.5 * r);

        if (y > 0) {
            w = r + r * I;
        } else {
            w = r - r * I;
        }

        return w;
    }

    /* Rescale to avoid internal overflow or underflow.  */
    if ((fabs(x) > 4.0) || (fabs(y) > 4.0)) {
        x *= 0.25;
        y *= 0.25;
        scale = 2.0;
    } else {
        x *= 1.8014398509481984e16;  /* 2^54 */
        y *= 1.8014398509481984e16;
        scale = 7.450580596923828125e-9; /* 2^-27 */
    }

    w = x + y * I;
    r = cabs(w);

    if (x > 0) {
        t = sqrt(0.5 * r + 0.5 * x);
        r = scale * fabs((0.5 * y) / t);
        t *= scale;
    } else {
        r = sqrt(0.5 * r - 0.5 * x);
        t = scale * fabs((0.5 * y) / r);
        r *= scale;
    }

    if (y < 0) {
        w = t - r * I;
    } else {
        w = t + r * I;
    }

    return w;
}

#ifdef __LIBMCS_LONG_DOUBLE_IS_64BITS

long double complex csqrtl(long double complex z)
{
    return (long double complex) csqrt((double complex) z);
}

#endif /* defined(_LONG_DOUBLE_IS_64BITS) */
#endif /* defined(_DOUBLE_IS_32BITS) */
