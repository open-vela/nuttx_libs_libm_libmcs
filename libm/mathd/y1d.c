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

static const double U0[5] = {
    -1.96057090646238940668e-01, /* 0xBFC91866, 0x143CBC8A */
    5.04438716639811282616e-02,  /* 0x3FA9D3C7, 0x76292CD1 */
    -1.91256895875763547298e-03, /* 0xBF5F55E5, 0x4844F50F */
    2.35252600561610495928e-05,  /* 0x3EF8AB03, 0x8FA6B88E */
    -9.19099158039878874504e-08, /* 0xBE78AC00, 0x569105B8 */
};
static const double V0[5] = {
    1.99167318236649903973e-02,  /* 0x3F94650D, 0x3F4DA9F0 */
    2.02552581025135171496e-04,  /* 0x3F2A8C89, 0x6C257764 */
    1.35608801097516229404e-06,  /* 0x3EB6C05A, 0x894E8CA6 */
    6.22741452364621501295e-09,  /* 0x3E3ABF1D, 0x5BA69A86 */
    1.66559246207992079114e-11,  /* 0x3DB25039, 0xDACA772A */
};

double y1(double x)
{
#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_one;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    double z, s, c, ss, cc, u, v;
    int32_t hx, ix, lx;

    EXTRACT_WORDS(hx, lx, x);
    ix = 0x7fffffff & hx;

    if (ix >= 0x7ff00000) {
        if (isnan(x)) {     /* y1(NaN) = NaN */
            return x + x;
        } else if (hx > 0) {  /* y1(+Inf) = +0.0 */
            return zero;
        } else {
            /* No action required */
        }
    }

    if ((ix | lx) == 0) {   /* y1(+-0) = +Inf */
        return __raise_div_by_zero(-1.0);
    }

    if (hx < 0) {           /* y1(<0) = NaN, y1(-Inf) = NaN */
        return __raise_invalid();
    }

    if (ix >= 0x40000000) { /* |x| >= 2.0 */
        s = sin(x);
        c = cos(x);
        ss = -s - c;
        cc = s - c;

        if (ix < 0x7fe00000) { /* make sure x+x not overflow */
            z = cos(x + x);

            if ((s * c) > zero) {
                cc = z / ss;
            } else {
                ss = z / cc;
            }
        }

        /* y1(x) = sqrt(2/(pi*x))*(p1(x)*sin(x0)+q1(x)*cos(x0))
         * where x0 = x-3pi/4
         *      Better formula:
         *              cos(x0) = cos(x)cos(3pi/4)+sin(x)sin(3pi/4)
         *                      =  1/sqrt(2) * (sin(x) - cos(x))
         *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
         *                      = -1/sqrt(2) * (cos(x) + sin(x))
         * To avoid cancellation, use
         *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
         * to compute the worse one.
         */
        if (ix > 0x48000000) {
            z = (invsqrtpi * ss) / sqrt(x);
        } else {
            u = __j1_p(x);
            v = __j1_q(x);
            z = invsqrtpi * (u * ss + v * cc) / sqrt(x);
        }

        return z;
    }

    if (ix <= 0x3c900000) { /* x < 2**-54 */
        return (-tpi / x);
    }

    z = x * x;
    u = U0[0] + z * (U0[1] + z * (U0[2] + z * (U0[3] + z * U0[4])));
    v = one + z * (V0[0] + z * (V0[1] + z * (V0[2] + z * (V0[3] + z * V0[4]))));
    return (x * (u / v) + tpi * (j1(x) * log(x) - one / x));
}

#endif /* defined(_DOUBLE_IS_32BITS) */
