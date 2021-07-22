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
/* R0/S0 on [0, 2.00] */
R02       =  1.56249999999999947958e-02, /* 0x3F8FFFFF, 0xFFFFFFFD */
R03       = -1.89979294238854721751e-04, /* 0xBF28E6A5, 0xB61AC6E9 */
R04       =  1.82954049532700665670e-06, /* 0x3EBEB1D1, 0x0C503919 */
R05       = -4.61832688532103189199e-09, /* 0xBE33D5E7, 0x73D63FCE */
S01       =  1.56191029464890010492e-02, /* 0x3F8FFCE8, 0x82C8C2A4 */
S02       =  1.16926784663337450260e-04, /* 0x3F1EA6D2, 0xDD57DBF4 */
S03       =  5.13546550207318111446e-07, /* 0x3EA13B54, 0xCE84D5A9 */
S04       =  1.16614003333790000205e-09; /* 0x3E1408BC, 0xF4745D8F */

double j0(double x)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    double z, s, c, ss, cc, r, u, v;
    int32_t hx, ix;

    GET_HIGH_WORD(hx, x);
    ix = hx & 0x7fffffff;

    if (ix >= 0x7ff00000) {
        return one / (x * x);
    }

    x = fabs(x);

    if (ix >= 0x40000000) {   /* |x| >= 2.0 */
        s = sin(x);
        c = cos(x);
        ss = s - c;
        cc = s + c;

        if (ix < 0x7fe00000) { /* make sure x+x not overflow */
            z = -cos(x + x);

            if ((s * c) < zero) {
                cc = z / ss;
            } else {
                ss = z / cc;
            }
        }

        /*
         * j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
         * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x)
         */
        if (ix > 0x48000000) {
            z = (invsqrtpi * cc) / sqrt(x);
        } else {
            u = __j0_p(x);
            v = __j0_q(x);
            z = invsqrtpi * (u * cc - v * ss) / sqrt(x);
        }

        return z;
    }

    if (ix < 0x3f200000) { /* |x| < 2**-13 */
        if (x != 0.0) {
            (void)__raise_inexact(x); /* raise inexact if x != 0 */
        }
        if (ix < 0x3e400000) {
            return one;    /* |x|<2**-27 */
        } else {
            return one - 0.25 * x * x;
        }
    }

    z = x * x;
    r =  z * (R02 + z * (R03 + z * (R04 + z * R05)));
    s =  one + z * (S01 + z * (S02 + z * (S03 + z * S04)));

    if (ix < 0x3FF00000) {   /* |x| < 1.00 */
        return one + z * (-0.25 + (r / s));
    } else {
        u = 0.5 * x;
        return ((one + u) * (one - u) + z * (r / s));
    }
}

#endif /* defined(_DOUBLE_IS_32BITS) */
