/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*
FUNCTION
<<jN>>, <<jNf>>, <<yN>>, <<yNf>>---Bessel functions

INDEX
j0
INDEX
j0f
INDEX
j1
INDEX
j1f
INDEX
jn
INDEX
jnf
INDEX
y0
INDEX
y0f
INDEX
y1
INDEX
y1f
INDEX
yn
INDEX
ynf

SYNOPSIS
#include <math.h>
double j0(double <[x]>);
float j0f(float <[x]>);
double j1(double <[x]>);
float j1f(float <[x]>);
double jn(int <[n]>, double <[x]>);
float jnf(int <[n]>, float <[x]>);
double y0(double <[x]>);
float y0f(float <[x]>);
double y1(double <[x]>);
float y1f(float <[x]>);
double yn(int <[n]>, double <[x]>);
float ynf(int <[n]>, float <[x]>);

DESCRIPTION
The Bessel functions are a family of functions that solve the
differential equation
@ifnottex
.  2               2    2
. x  y'' + xy' + (x  - p )y  = 0
@end ifnottex
@tex
$$x^2{d^2y\over dx^2} + x{dy\over dx} + (x^2-p^2)y = 0$$
@end tex
These functions have many applications in engineering and physics.

<<jn>> calculates the Bessel function of the first kind of order
<[n]>.  <<j0>> and <<j1>> are special cases for order 0 and order
1 respectively.

Similarly, <<yn>> calculates the Bessel function of the second kind of
order <[n]>, and <<y0>> and <<y1>> are special cases for order 0 and
1.

<<jnf>>, <<j0f>>, <<j1f>>, <<ynf>>, <<y0f>>, and <<y1f>> perform the
same calculations, but on <<float>> rather than <<double>> values.

RETURNS
The value of each Bessel function at <[x]> is returned.

PORTABILITY
None of the Bessel functions are in ANSI C.
*/

/* __j0(x), __y0(x)
 * Bessel function of the first and second kinds of order zero.
 * Method -- j0(x):
 *    1. For tiny x, we use j0(x) = 1 - x^2/4 + x^4/64 - ...
 *    2. Reduce x to |x| since j0(x)=j0(-x),  and
 *       for x in (0,2)
 *        j0(x) = 1-z/4+ z^2*R0/S0,  where z = x*x;
 *       (precision:  |j0-1+z/4-z^2R0/S0 |<2**-63.67 )
 *       for x in (2,inf)
 *         j0(x) = sqrt(2/(pi*x))*(p0(x)*cos(x0)-q0(x)*sin(x0))
 *        where x0 = x-pi/4. It is better to compute sin(x0),cos(x0)
 *       as follow:
 *        cos(x0) = cos(x)cos(pi/4)+sin(x)sin(pi/4)
 *            = 1/sqrt(2) * (cos(x) + sin(x))
 *        sin(x0) = sin(x)cos(pi/4)-cos(x)sin(pi/4)
 *            = 1/sqrt(2) * (sin(x) - cos(x))
 *        (To avoid cancellation, use
 *        sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
 *         to compute the worse one.)
 *
 *    3 Special cases
 *        j0(nan)= nan
 *        j0(0) = 1
 *        j0(inf) = 0
 *
 * Method -- y0(x):
 *    1. For x<2.
 *       Since
 *        y0(x) = 2/pi*(j0(x)*(ln(x/2)+Euler) + x^2/4 - ...)
 *       therefore y0(x)-2/pi*j0(x)*ln(x) is an even function.
 *       We use the following function to approximate y0,
 *        y0(x) = U(z)/V(z) + (2/pi)*(j0(x)*ln(x)), z= x^2
 *       where
 *        U(z) = u00 + u01*z + ... + u06*z^6
 *        V(z) = 1  + v01*z + ... + v04*z^4
 *       with absolute approximation error bounded by 2**-72.
 *       Note: For tiny x, U/V = u0 and j0(x)~1, hence
 *        y0(tiny) = u0 + (2/pi)*ln(tiny), (choose tiny<2**-27)
 *    2. For x>=2.
 *         y0(x) = sqrt(2/(pi*x))*(p0(x)*cos(x0)+q0(x)*sin(x0))
 *        where x0 = x-pi/4. It is better to compute sin(x0),cos(x0)
 *       by the method mentioned above.
 *    3. Special cases: y0(0)=-inf, y0(x<0)=NaN, y0(inf)=0.
 */

#include <math.h>
#include "internal/besseld.h"
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

static const double
u00  = -7.38042951086872317523e-02, /* 0xBFB2E4D6, 0x99CBD01F */
u01  =  1.76666452509181115538e-01, /* 0x3FC69D01, 0x9DE9E3FC */
u02  = -1.38185671945596898896e-02, /* 0xBF8C4CE8, 0xB16CFA97 */
u03  =  3.47453432093683650238e-04, /* 0x3F36C54D, 0x20B29B6B */
u04  = -3.81407053724364161125e-06, /* 0xBECFFEA7, 0x73D25CAD */
u05  =  1.95590137035022920206e-08, /* 0x3E550057, 0x3B4EABD4 */
u06  = -3.98205194132103398453e-11, /* 0xBDC5E43D, 0x693FB3C8 */
v01  =  1.27304834834123699328e-02, /* 0x3F8A1270, 0x91C9C71A */
v02  =  7.60068627350353253702e-05, /* 0x3F13ECBB, 0xF578C6C1 */
v03  =  2.59150851840457805467e-07, /* 0x3E91642D, 0x7FF202FD */
v04  =  4.41110311332675467403e-10; /* 0x3DFE5018, 0x3BD6D9EF */

double y0(double x)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    double z, s, c, ss, cc, u, v;
    int32_t hx, ix, lx;

    EXTRACT_WORDS(hx, lx, x);
    ix = 0x7fffffff & hx;

    if (ix >= 0x7ff00000) {
        if (isnan(x)) {     /* y0(NaN) = NaN */
            return x + x;
        } else if (hx > 0) {  /* y0(+Inf) = +0.0 */
            return zero;
        } else {
            /* No action required */
        }
    }

    if ((ix | lx) == 0) {   /* y0(+-0) = +Inf */
        return __raise_div_by_zero(-1.0);
    }

    if (hx < 0) {           /* y0(<0) = NaN, y0(-Inf) = NaN */
        return __raise_invalid();
    }

    if (ix >= 0x40000000) { /* |x| >= 2.0 */
        /* y0(x) = sqrt(2/(pi*x))*(p0(x)*sin(x0)+q0(x)*cos(x0))
         * where x0 = x-pi/4
         *      Better formula:
         *              cos(x0) = cos(x)cos(pi/4)+sin(x)sin(pi/4)
         *                      =  1/sqrt(2) * (sin(x) + cos(x))
         *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
         *                      =  1/sqrt(2) * (sin(x) - cos(x))
         * To avoid cancellation, use
         *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
         * to compute the worse one.
         */
        s = sin(x);
        c = cos(x);
        ss = s - c;
        cc = s + c;

        /*
         * j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
         * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x)
         */
        if (ix < 0x7fe00000) { /* make sure x+x not overflow */
            z = -cos(x + x);

            if ((s * c) < zero) {
                cc = z / ss;
            } else {
                ss = z / cc;
            }
        }

        if (ix > 0x48000000) {
            z = (invsqrtpi * ss) / sqrt(x);
        } else {
            u = __j0_p(x);
            v = __j0_q(x);
            z = invsqrtpi * (u * ss + v * cc) / sqrt(x);
        }

        return z;
    }

    if (ix <= 0x3e400000) { /* x < 2**-27 */
        return (u00 + tpi * log(x));
    }

    z = x * x;
    u = u00 + z * (u01 + z * (u02 + z * (u03 + z * (u04 + z * (u05 + z * u06)))));
    v = one + z * (v01 + z * (v02 + z * (v03 + z * v04)));
    return (u / v + tpi * (j0(x) * log(x)));
}

#endif /* defined(_DOUBLE_IS_32BITS) */
