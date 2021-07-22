/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/* __j1(x), __y1(x)
 * Bessel function of the first and second kinds of order zero.
 * Method -- j1(x):
 *    1. For tiny x, we use j1(x) = x/2 - x^3/16 + x^5/384 - ...
 *    2. Reduce x to |x| since j1(x)=-j1(-x),  and
 *       for x in (0,2)
 *        j1(x) = x/2 + x*z*R0/S0,  where z = x*x;
 *       (precision:  |j1/x - 1/2 - R0/S0 |<2**-61.51 )
 *       for x in (2,inf)
 *         j1(x) = sqrt(2/(pi*x))*(p1(x)*cos(x1)-q1(x)*sin(x1))
 *         y1(x) = sqrt(2/(pi*x))*(p1(x)*sin(x1)+q1(x)*cos(x1))
 *        where x1 = x-3*pi/4. It is better to compute sin(x1),cos(x1)
 *       as follow:
 *        cos(x1) =  cos(x)cos(3pi/4)+sin(x)sin(3pi/4)
 *            =  1/sqrt(2) * (sin(x) - cos(x))
 *        sin(x1) =  sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
 *            = -1/sqrt(2) * (sin(x) + cos(x))
 *        (To avoid cancellation, use
 *        sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
 *         to compute the worse one.)
 *
 *    3 Special cases
 *        j1(nan)= nan
 *        j1(0) = 0
 *        j1(inf) = 0
 *
 * Method -- y1(x):
 *    1. screen out x<=0 cases: y1(0)=-inf, y1(x<0)=NaN
 *    2. For x<2.
 *       Since
 *        y1(x) = 2/pi*(j1(x)*(ln(x/2)+Euler)-1/x-x/2+5/64*x^3-...)
 *       therefore y1(x)-2/pi*j1(x)*ln(x)-1/x is an odd function.
 *       We use the following function to approximate y1,
 *        y1(x) = x*U(z)/V(z) + (2/pi)*(j1(x)*ln(x)-1/x), z= x^2
 *       where for x in [0,2] (abs err less than 2**-65.89)
 *        U(z) = U0[0] + U0[1]*z + ... + U0[4]*z^4
 *        V(z) = 1  + v0[0]*z + ... + v0[4]*z^5
 *       Note: For tiny x, 1/x dominate y1 and hence
 *        y1(tiny) = -2/pi/tiny, (choose tiny<2**-54)
 *    3. For x>=2.
 *         y1(x) = sqrt(2/(pi*x))*(p1(x)*sin(x1)+q1(x)*cos(x1))
 *        where x1 = x-3*pi/4. It is better to compute sin(x1),cos(x1)
 *       by method mentioned above.
 */

#include <math.h>
#include "internal/besseld.h"
#include "../common/tools.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

static const double
/* R0/S0 on [0,2] */
r00       = -6.25000000000000000000e-02, /* 0xBFB00000, 0x00000000 */
r01       =  1.40705666955189706048e-03, /* 0x3F570D9F, 0x98472C61 */
r02       = -1.59955631084035597520e-05, /* 0xBEF0C5C6, 0xBA169668 */
r03       =  4.96727999609584448412e-08, /* 0x3E6AAAFA, 0x46CA0BD9 */
s01       =  1.91537599538363460805e-02, /* 0x3F939D0B, 0x12637E53 */
s02       =  1.85946785588630915560e-04, /* 0x3F285F56, 0xB9CDF664 */
s03       =  1.17718464042623683263e-06, /* 0x3EB3BFF8, 0x333F8498 */
s04       =  5.04636257076217042715e-09, /* 0x3E35AC88, 0xC97DFF2C */
s05       =  1.23542274426137913908e-11; /* 0x3DAB2ACF, 0xCFB97ED8 */

double j1(double x)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    double z, s, c, ss, cc, r, u, v, y;
    int32_t hx, ix;

    GET_HIGH_WORD(hx, x);
    ix = hx & 0x7fffffff;

    if (ix >= 0x7ff00000) {
        return one / x;
    }

    y = fabs(x);

    if (ix >= 0x40000000) {   /* |x| >= 2.0 */
        s = sin(y);
        c = cos(y);
        ss = -s - c;
        cc = s - c;

        if (ix < 0x7fe00000) { /* make sure y+y not overflow */
            z = cos(y + y);

            if ((s * c) > zero) {
                cc = z / ss;
            } else {
                ss = z / cc;
            }
        }

        /*
         * j1(x) = 1/sqrt(pi) * (P(1,x)*cc - Q(1,x)*ss) / sqrt(x)
         * y1(x) = 1/sqrt(pi) * (P(1,x)*ss + Q(1,x)*cc) / sqrt(x)
         */
        if (ix > 0x48000000) {
            z = (invsqrtpi * cc) / sqrt(y);
        } else {
            u = __j1_p(y);
            v = __j1_q(y);
            z = invsqrtpi * (u * cc - v * ss) / sqrt(y);
        }

        if (hx < 0) {
            return -z;
        } else {
            return  z;
        }
    }

    if (ix < 0x3e400000) { /* |x|<2**-27 */
        if (x != 0.0) {
            (void)__raise_inexact(x); /* raise inexact if x != 0 */
        }
        return 0.5 * x;
    }

    z = x * x;
    r =  z * (r00 + z * (r01 + z * (r02 + z * r03)));
    s =  one + z * (s01 + z * (s02 + z * (s03 + z * (s04 + z * s05))));
    r *= x;
    return (x * 0.5 + r / s);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
