/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/*
 * __rem_pio2_internal(x,y,e0,nx,prec,ipio2)
 * double x[],y[]; int e0,nx,prec; int ipio2[];
 *
 * __rem_pio2_internal return the last three digits of N with
 *        y = x - N*pi/2
 * so that |y| < pi/2.
 *
 * The method is to compute the integer (mod 8) and fraction parts of
 * (2/pi)*x without doing the full multiplication. In general we
 * skip the part of the product that are known to be a huge integer (
 * more accurately, = 0 mod 8 ). Thus the number of operations are
 * independent of the exponent of the input.
 *
 * (2/pi) is represented by an array of 24-bit integers in ipio2[].
 *
 * Input parameters:
 *     x[]    The input value (must be positive) is broken into nx
 *        pieces of 24-bit integers in double precision format.
 *        x[i] will be the i-th 24 bit of x. The scaled exponent
 *        of x[0] is given in input parameter e0 (i.e., x[0]*2^e0
 *        match x's up to 24 bits.
 *
 *        Example of breaking a double positive z into x[0]+x[1]+x[2]:
 *            e0 = ilogb(z)-23
 *            z  = scalbn(z,-e0)
 *        for i = 0,1,2
 *            x[i] = floor(z)
 *            z    = (z-x[i])*2**24
 *
 *
 *    y[]    ouput result in an array of double precision numbers.
 *        The dimension of y[] is:
 *            24-bit  precision    1
 *            53-bit  precision    2
 *            64-bit  precision    2
 *            113-bit precision    3
 *        The actual value is the sum of them. Thus for 113-bit
 *        precison, one may have to do something like:
 *
 *        long double t,w,r_head, r_tail;
 *        t = (long double)y[2] + (long double)y[1];
 *        w = (long double)y[0];
 *        r_head = t+w;
 *        r_tail = w - (r_head - t);
 *
 *    e0    The exponent of x[0]
 *
 *    nx    dimension of x[]
 *
 *      prec    an integer indicating the precision:
 *            0    24  bits (single)
 *            1    53  bits (double)
 *            2    64  bits (extended)
 *            3    113 bits (quad)
 *
 *    ipio2[]
 *        integer array, contains the (24*i)-th to (24*i+23)-th
 *        bit of 2/pi after binary point. The corresponding
 *        floating value is
 *
 *            ipio2[i] * 2^(-24(i+1)).
 *
 * External function:
 *    double scalbn(), floor();
 *
 *
 * Here is the description of some local variables:
 *
 *     jk    jk+1 is the initial number of terms of ipio2[] needed
 *        in the computation. The recommended value is 2,3,4,
 *        6 for single, double, extended,and quad.
 *
 *     jz    local integer variable indicating the number of
 *        terms of ipio2[] used.
 *
 *    jx    nx - 1
 *
 *    jv    index for pointing to the suitable ipio2[] for the
 *        computation. In general, we want
 *            ( 2^e0*x[0] * ipio2[jv-1]*2^(-24jv) )/8
 *        is an integer. Thus
 *            e0-3-24*jv >= 0 or (e0-3)/24 >= jv
 *        Hence jv = max(0,(e0-3)/24).
 *
 *    jp    jp+1 is the number of terms in PIo2[] needed, jp = jk.
 *
 *     q[]    double array with integral value, representing the
 *        24-bits chunk of the product of x and 2/pi.
 *
 *    q0    the corresponding exponent of q[0]. Note that the
 *        exponent for q[i] would be q0-24*i.
 *
 *    PIo2[]    double precision array, obtained by cutting pi/2
 *        into 24 bits chunks.
 *
 *    f[]    ipio2[] in floating point
 *
 *    iq[]    integer array by breaking up q[] in 24-bits chunk.
 *
 *    fq[]    final product of x*(2/pi) in fq[0],..,fq[jk]
 *
 *    ih    integer. If >0 it indicates q[] is >= 0.5, hence
 *        it also indicates the *sign* of the result.
 *
 */


/*
 * Constants:
 * The hexadecimal values are the intended ones for the following
 * constants. The decimal values may be used, provided that the
 * compiler will convert from decimal to binary accurately enough
 * to produce the hexadecimal values shown.
 */

#include <math.h>
#include "../../common/tools.h"
#include "trigd.h"

#ifndef __LIBMCS_DOUBLE_IS_32BITS

static const double PIo2[] = {
    1.57079625129699707031e+00, /* 0x3FF921FB, 0x40000000 */
    7.54978941586159635335e-08, /* 0x3E74442D, 0x00000000 */
    5.39030252995776476554e-15, /* 0x3CF84698, 0x80000000 */
    3.28200341580791294123e-22, /* 0x3B78CC51, 0x60000000 */
    1.27065575308067607349e-29, /* 0x39F01B83, 0x80000000 */
    1.22933308981111328932e-36, /* 0x387A2520, 0x40000000 */
    2.73370053816464559624e-44, /* 0x36E38222, 0x80000000 */
    2.16741683877804819444e-51, /* 0x3569F31D, 0x00000000 */
};

/*
 * Table of constants for 2/pi, 396 Hex digits (476 decimal) of 2/pi
 */
static const int32_t ipio2[] = {
    0xA2F983, 0x6E4E44, 0x1529FC, 0x2757D1, 0xF534DD, 0xC0DB62, 0x95993C, 0x439041, 0xFE5163,
    0xABDEBB, 0xC561B7, 0x246E3A, 0x424DD2, 0xE00649, 0x2EEA09, 0xD1921C, 0xFE1DEB, 0x1CB129,
    0xA73EE8, 0x8235F5, 0x2EBB44, 0x84E99C, 0x7026B4, 0x5F7E41, 0x3991D6, 0x398353, 0x39F49C,
    0x845F8B, 0xBDF928, 0x3B1FF8, 0x97FFDE, 0x05980F, 0xEF2F11, 0x8B5A0A, 0x6D1F6D, 0x367ECF,
    0x27CB09, 0xB74F46, 0x3F669E, 0x5FEA2D, 0x7527BA, 0xC7EBE5, 0xF17B3D, 0x0739F7, 0x8A5292,
    0xEA6BFB, 0x5FB11F, 0x8D5D08, 0x560330, 0x46FC7B, 0x6BABF0, 0xCFBC20, 0x9AF436, 0x1DA9E3,
    0x91615E, 0xE61B08, 0x659985, 0x5F14A0, 0x68408D, 0xFFD880, 0x4D7327, 0x310606, 0x1556CA,
    0x73A8C9, 0x60E27B, 0xC08C6B,
};

static const double
zero    =  0.0,
one     =  1.0,
two24   =  1.67772160000000000000e+07, /* 0x41700000, 0x00000000 */
twon24  =  5.96046447753906250000e-08; /* 0x3E700000, 0x00000000 */

int __rem_pio2_internal(double *x, double *y, int e0, int nx)
{
    int32_t jz, jx, jv, jp, jk, carry, n, iq[20], i, j, k, m, q0, ih;
    double z, fw, f[20], fq[20], q[20];

    /* initialize jk*/
    jk = 4;
    jp = jk;

    /* determine jx,jv,q0, note that 3>q0 */
    jx =  nx - 1;
    jv = (e0 - 3) / 24;

    if (jv < 0) {
        jv = 0;
    }

    q0 =  e0 - 24 * (jv + 1);

    /* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
    j = jv - jx;
    m = jx + jk;

    for (i = 0; i <= m; i++, j++) {
        f[i] = (j < 0) ? zero : (double) ipio2[j];
    }

    /* compute q[0],q[1],...q[jk] */
    for (i = 0; i <= jk; i++) {
        for (j = 0, fw = 0.0; j <= jx; j++) {
            fw += x[j] * f[jx + i - j];
        }

        q[i] = fw;
    }

    jz = jk;
recompute:

    /* distill q[] into iq[] reversingly */
    for (i = 0, j = jz, z = q[jz]; j > 0; i++, j--) {
        fw    = (double)((int32_t)(twon24 * z));
        iq[i] = (int32_t)(z - two24 * fw);
        z     =  q[j - 1] + fw;
    }

    /* compute n */
    z  = scalbn(z, (int)q0);       /* actual value of z */
    z -= 8.0 * floor(z * 0.125);    /* trim off integer >= 8 */
    n  = (int32_t) z;
    z -= (double)n;
    ih = 0;

    if (q0 > 0) { /* need iq[jz-1] to determine n */
        i  = (iq[jz - 1] >> (24 - q0));
        n += i;
        iq[jz - 1] -= i << (24 - q0);
        ih = iq[jz - 1] >> (23 - q0);
    } else if (q0 == 0) {
        ih = iq[jz - 1] >> 23;
    } else if (z >= 0.5) {
        ih = 2;
    }

    if (ih > 0) { /* q > 0.5 */
        n += 1;
        carry = 0;

        for (i = 0; i < jz ; i++) { /* compute 1-q */
            j = iq[i];

            if (carry == 0) {
                if (j != 0) {
                    carry = 1;
                    iq[i] = 0x1000000 - j;
                }
            } else {
                iq[i] = 0xffffff - j;
            }
        }

        if (q0 > 0) {     /* rare case: chance is 1 in 12 */
            switch (q0) {
            case 1:
                iq[jz - 1] &= 0x7fffff;
                break;

            case 2:
                iq[jz - 1] &= 0x3fffff;
                break;
            }
        }

        if (ih == 2) {
            z = one - z;

            if (carry != 0) {
                z -= scalbn(one, (int)q0);
            }
        }
    }

    /* check if recomputation is needed */
    if (z == zero) {
        j = 0;

        for (i = jz - 1; i >= jk; i--) {
            j |= iq[i];
        }

        if (j == 0) { /* need recomputation */
            for (k = 1; iq[jk - k] == 0; k++); /* k = no. of terms needed */

            for (i = jz + 1; i <= jz + k; i++) { /* add q[jz+1] to q[jz+k] */
                f[jx + i] = (double) ipio2[jv + i];

                for (j = 0, fw = 0.0; j <= jx; j++) {
                    fw += x[j] * f[jx + i - j];
                }

                q[i] = fw;
            }

            jz += k;
            goto recompute;
        }
    }

    /* chop off zero terms */
    if (z == 0.0) {
        jz -= 1;
        q0 -= 24;

        while (iq[jz] == 0) {
            jz--;
            q0 -= 24;
        }
    } else { /* break z into 24-bit if necessary */
        z = scalbn(z, -(int)q0);

        if (z >= two24) {
            fw = (double)((int32_t)(twon24 * z));
            iq[jz] = (int32_t)(z - two24 * fw);
            jz += 1;
            q0 += 24;
            iq[jz] = (int32_t) fw;
        } else {
            iq[jz] = (int32_t) z ;
        }
    }

    /* convert integer "bit" chunk to floating-point value */
    fw = scalbn(one, (int)q0);

    for (i = jz; i >= 0; i--) {
        q[i] = fw * (double)iq[i];
        fw *= twon24;
    }

    /* compute PIo2[0,...,jp]*q[jz,...,0] */
    for (i = jz; i >= 0; i--) {
        for (fw = 0.0, k = 0; k <= jp && k <= jz - i; k++) {
            fw += PIo2[k] * q[i + k];
        }

        fq[jz - i] = fw;
    }

    /* compress fq[] into y[] */
    fw = 0.0;

    for (i = jz; i >= 0; i--) {
        fw += fq[i];
    }

    y[0] = (ih == 0) ? fw : -fw;
    fw = fq[0] - fw;

    for (i = 1; i <= jz; i++) {
        fw += fq[i];
    }

    y[1] = (ih == 0) ? fw : -fw;

    return n & 7;
}

/* __rem_pio2(x,y)
 *
 * return the remainder of x rem pi/2 in y[0]+y[1]
 * use __rem_pio2_internal()
 */

static const int32_t npio2_hw[] = {
    0x3FF921FB, 0x400921FB, 0x4012D97C, 0x401921FB, 0x401F6A7A, 0x4022D97C, 0x4025FDBB, 0x402921FB,
    0x402C463A, 0x402F6A7A, 0x4031475C, 0x4032D97C, 0x40346B9C, 0x4035FDBB, 0x40378FDB, 0x403921FB,
    0x403AB41B, 0x403C463A, 0x403DD85A, 0x403F6A7A, 0x40407E4C, 0x4041475C, 0x4042106C, 0x4042D97C,
    0x4043A28C, 0x40446B9C, 0x404534AC, 0x4045FDBB, 0x4046C6CB, 0x40478FDB, 0x404858EB, 0x404921FB,
};

/*
 * invpio2:  53 bits of 2/pi
 * pio2_1:   first  33 bit of pi/2
 * pio2_1t:  pi/2 - pio2_1
 * pio2_2:   second 33 bit of pi/2
 * pio2_2t:  pi/2 - (pio2_1+pio2_2)
 * pio2_3:   third  33 bit of pi/2
 * pio2_3t:  pi/2 - (pio2_1+pio2_2+pio2_3)
 */
static const double
half     =  5.00000000000000000000e-01, /* 0x3FE00000, 0x00000000 */
invpio2  =  6.36619772367581382433e-01, /* 0x3FE45F30, 0x6DC9C883 */
pio2_1   =  1.57079632673412561417e+00, /* 0x3FF921FB, 0x54400000 */
pio2_1t  =  6.07710050650619224932e-11, /* 0x3DD0B461, 0x1A626331 */
pio2_2   =  6.07710050630396597660e-11, /* 0x3DD0B461, 0x1A600000 */
pio2_2t  =  2.02226624879595063154e-21, /* 0x3BA3198A, 0x2E037073 */
pio2_3   =  2.02226624871116645580e-21, /* 0x3BA3198A, 0x2E000000 */
pio2_3t  =  8.47842766036889956997e-32; /* 0x397B839A, 0x252049C1 */

int32_t __rem_pio2(double x, double *y)
{
    double z = 0.0, w, t, r, fn;
    double tx[3];
    int32_t i, j, n, ix, hx;
    int e0, nx;
    uint32_t low;

    GET_HIGH_WORD(hx, x);       /* high word of x */
    ix = hx & 0x7fffffff;

    if (ix <= 0x3fe921fb) { /* |x| ~<= pi/4 , no need for reduction */
        y[0] = x;
        y[1] = 0;
        return 0;
    }

    if (ix < 0x4002d97c) { /* |x| < 3pi/4, special case with n=+-1 */
        if (hx > 0) {
            z = x - pio2_1;

            if (ix != 0x3ff921fb) {  /* 33+53 bit pi is good enough */
                y[0] = z - pio2_1t;
                y[1] = (z - y[0]) - pio2_1t;
            } else {        /* near pi/2, use 33+33+53 bit pi */
                z -= pio2_2;
                y[0] = z - pio2_2t;
                y[1] = (z - y[0]) - pio2_2t;
            }

            return 1;
        } else {    /* negative x */
            z = x + pio2_1;

            if (ix != 0x3ff921fb) {  /* 33+53 bit pi is good enough */
                y[0] = z + pio2_1t;
                y[1] = (z - y[0]) + pio2_1t;
            } else {        /* near pi/2, use 33+33+53 bit pi */
                z += pio2_2;
                y[0] = z + pio2_2t;
                y[1] = (z - y[0]) + pio2_2t;
            }

            return -1;
        }
    }

    if (ix <= 0x413921fb) { /* |x| ~<= 2^19*(pi/2), medium size */
        t  = fabs(x);
        n  = (int32_t)(t * invpio2 + half);
        fn = (double)n;
        r  = t - fn * pio2_1;
        w  = fn * pio2_1t;  /* 1st round good to 85 bit */

        if (n < 32 && ix != npio2_hw[n - 1]) {
            y[0] = r - w;  /* quick check no cancellation */
        } else {
            uint32_t high;
            j  = ix >> 20;
            y[0] = r - w;
            GET_HIGH_WORD(high, y[0]);
            i = j - ((high >> 20) & 0x7ff);

            if (i > 16) { /* 2nd iteration needed, good to 118 */
                t  = r;
                w  = fn * pio2_2;
                r  = t - w;
                w  = fn * pio2_2t - ((t - r) - w);
                y[0] = r - w;
                GET_HIGH_WORD(high, y[0]);
                i = j - ((high >> 20) & 0x7ff);

                if (i > 49)  { /* 3rd iteration need, 151 bits acc */
                    t  = r;    /* will cover all possible cases */
                    w  = fn * pio2_3;
                    r  = t - w;
                    w  = fn * pio2_3t - ((t - r) - w);
                    y[0] = r - w;
                }
            }
        }

        y[1] = (r - y[0]) - w;

        if (hx < 0)     {
            y[0] = -y[0];
            y[1] = -y[1];
            return -n;
        } else {
            return n;
        }
    }

    /*
     * all other (large) arguments
     */
    if (ix >= 0x7ff00000) {     /* x is inf or NaN */
        y[0] = y[1] = x - x;
        return 0;
    }

    /* set z = scalbn(|x|,ilogb(x)-23) */
    GET_LOW_WORD(low, x);
    SET_LOW_WORD(z, low);
    e0 = (int)((ix >> 20) - 1046); /* e0 = ilogb(z)-23; */
    SET_HIGH_WORD(z, ix - ((int32_t)e0 << 20));

    for (i = 0; i < 2; i++) {
        tx[i] = (double)((int32_t)(z));
        z     = (z - tx[i]) * two24;
    }

    tx[2] = z;
    nx = 3;

    while (tx[nx - 1] == zero) {
        nx--;    /* skip zero term */
    }

    n  =  __rem_pio2_internal(tx, y, e0, nx, two_over_pi);

    if (hx < 0) {
        y[0] = -y[0];
        y[1] = -y[1];
        return -n;
    }

    return n;
}

/*
 * __cos( x,  y )
 * internal cos function on [-pi/4, pi/4], pi/4 ~ 0.785398164
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 *
 * Algorithm
 *    1. Since cos(-x) = cos(x), we need only to consider positive x.
 *    2. if x < 2^-27 (hx<0x3e400000 0), return 1 with inexact if x!=0.
 *    3. cos(x) is approximated by a polynomial of degree 14 on
 *       [0,pi/4]
 *                               4            14
 *           cos(x) ~ 1 - x*x/2 + C1*x + ... + C6*x
 *       where the remez error is
 *
 *     |              2     4     6     8     10    12     14 |     -58
 *     |cos(x)-(1-.5*x +C1*x +C2*x +C3*x +C4*x +C5*x  +C6*x  )| <= 2
 *     |                                       |
 *
 *                    4     6     8     10    12     14
 *    4. let r = C1*x +C2*x +C3*x +C4*x +C5*x  +C6*x  , then
 *           cos(x) = 1 - x*x/2 + r
 *       since cos(x+y) ~ cos(x) - sin(x)*y
 *              ~ cos(x) - x*y,
 *       a correction term is necessary in cos(x) and hence
 *        cos(x+y) = 1 - (x*x/2 - (r - x*y))
 *       For better accuracy when x > 0.3, let qx = |x|/4 with
 *       the last 32 bits mask off, and if x > 0.78125, let qx = 0.28125.
 *       Then
 *        cos(x+y) = (1-qx) - ((x*x/2-qx) - (r-x*y)).
 *       Note that 1-qx and (x*x/2-qx) is EXACT here, and the
 *       magnitude of the latter is at least a quarter of x*x/2,
 *       thus, reducing the rounding error in the subtraction.
 */

static const double
C1  =  4.16666666666666019037e-02, /* 0x3FA55555, 0x5555554C */
C2  = -1.38888888888741095749e-03, /* 0xBF56C16C, 0x16C15177 */
C3  =  2.48015872894767294178e-05, /* 0x3EFA01A0, 0x19CB1590 */
C4  = -2.75573143513906633035e-07, /* 0xBE927E4F, 0x809C52AD */
C5  =  2.08757232129817482790e-09, /* 0x3E21EE9E, 0xBDB4B1C4 */
C6  = -1.13596475577881948265e-11; /* 0xBDA8FAE9, 0xBE8838D4 */

double __cos(double x, double y)
{
    double a, hz, z, r, qx;
    int32_t ix;
    GET_HIGH_WORD(ix, x);
    ix &= 0x7fffffff;            /* ix = |x|'s high word*/

    if (ix < 0x3e400000) {         /* if x < 2**27 */
        if (((int)x) == 0) {
            return one;    /* generate inexact */
        }
    }

    z  = x * x;
    r  = z * (C1 + z * (C2 + z * (C3 + z * (C4 + z * (C5 + z * C6)))));

    if (ix < 0x3FD33333) {          /* if |x| < 0.3 */
        return one - (0.5 * z - (z * r - x * y));
    } else {
        if (ix > 0x3fe90000) {       /* x > 0.78125 */
            qx = 0.28125;
        } else {
            INSERT_WORDS(qx, ix - 0x00200000, 0); /* x/4 */
        }

        hz = 0.5 * z - qx;
        a  = one - qx;
        return a - (hz - (z * r - x * y));
    }
}

/* __sin( x, y, iy)
 * internal sin function on [-pi/4, pi/4], pi/4 ~ 0.7854
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 * Input iy indicates whether y is 0. (if iy=0, y assume to be 0).
 *
 * Algorithm
 *    1. Since sin(-x) = -sin(x), we need only to consider positive x.
 *    2. if x < 2^-27 (hx<0x3e400000 0), return x with inexact if x!=0.
 *    3. sin(x) is approximated by a polynomial of degree 13 on
 *       [0,pi/4]
 *                       3            13
 *           sin(x) ~ x + S1*x + ... + S6*x
 *       where
 *
 *     |sin(x)         2     4     6     8     10     12  |     -58
 *     |----- - (1+S1*x +S2*x +S3*x +S4*x +S5*x  +S6*x   )| <= 2
 *     |  x                                |
 *
 *    4. sin(x+y) = sin(x) + sin'(x')*y
 *            ~ sin(x) + (1-x*x/2)*y
 *       For better accuracy, let
 *             3      2      2      2      2
 *        r = x *(S2+x *(S3+x *(S4+x *(S5+x *S6))))
 *       then                   3    2
 *        sin(x) = x + (S1*x + (x *(r-y/2)+y))
 */

static const double
S1   = -1.66666666666666324348e-01, /* 0xBFC55555, 0x55555549 */
S2   =  8.33333333332248946124e-03, /* 0x3F811111, 0x1110F8A6 */
S3   = -1.98412698298579493134e-04, /* 0xBF2A01A0, 0x19C161D5 */
S4   =  2.75573137070700676789e-06, /* 0x3EC71DE3, 0x57B1FE7D */
S5   = -2.50507602534068634195e-08, /* 0xBE5AE5E6, 0x8A2B9CEB */
S6   =  1.58969099521155010221e-10; /* 0x3DE5D93A, 0x5ACFD57C */

double __sin(double x, double y, int iy)
{
    double z, r, v;
    int32_t ix;
    GET_HIGH_WORD(ix, x);
    ix &= 0x7fffffff;            /* high word of x */

    if (ix < 0x3e400000) {       /* |x| < 2**-27 */
        if ((int)x == 0) {
            return x;    /* generate inexact */
        }
    }

    z    =  x * x;
    v    =  z * x;
    r    =  S2 + z * (S3 + z * (S4 + z * (S5 + z * S6)));

    if (iy == 0) {
        return x + v * (S1 + z * r);
    } else {
        return x - ((z * (half * y - v * r) - y) - v * S1);
    }
}

#endif /* defined(_DOUBLE_IS_32BITS) */
