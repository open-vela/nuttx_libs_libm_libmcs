/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>
#include "../../common/tools.h"
#include "trigf.h"

/* In the float version, the input parameter x contains 8 bit
   integers, not 24 bit integers.  113 bit precision is not supported.  */

static const float PIo2[] = {
    1.5703125000e+00, /* 0x3fc90000 */
    4.5776367188e-04, /* 0x39f00000 */
    2.5987625122e-05, /* 0x37da0000 */
    7.5437128544e-08, /* 0x33a20000 */
    6.0026650317e-11, /* 0x2e840000 */
    7.3896444519e-13, /* 0x2b500000 */
    5.3845816694e-15, /* 0x27c20000 */
    5.6378512969e-18, /* 0x22d00000 */
    8.3009228831e-20, /* 0x1fc40000 */
    3.2756352257e-22, /* 0x1bc60000 */
    6.3331015649e-25, /* 0x17440000 */
};

/*
 * Table of constants for 2/pi, 396 Hex digits (476 decimal) of 2/pi
 */
static const int32_t ipio2[] = {
    0xA2, 0xF9, 0x83, 0x6E, 0x4E, 0x44, 0x15, 0x29, 0xFC,
    0x27, 0x57, 0xD1, 0xF5, 0x34, 0xDD, 0xC0, 0xDB, 0x62,
    0x95, 0x99, 0x3C, 0x43, 0x90, 0x41, 0xFE, 0x51, 0x63,
    0xAB, 0xDE, 0xBB, 0xC5, 0x61, 0xB7, 0x24, 0x6E, 0x3A,
    0x42, 0x4D, 0xD2, 0xE0, 0x06, 0x49, 0x2E, 0xEA, 0x09,
    0xD1, 0x92, 0x1C, 0xFE, 0x1D, 0xEB, 0x1C, 0xB1, 0x29,
    0xA7, 0x3E, 0xE8, 0x82, 0x35, 0xF5, 0x2E, 0xBB, 0x44,
    0x84, 0xE9, 0x9C, 0x70, 0x26, 0xB4, 0x5F, 0x7E, 0x41,
    0x39, 0x91, 0xD6, 0x39, 0x83, 0x53, 0x39, 0xF4, 0x9C,
    0x84, 0x5F, 0x8B, 0xBD, 0xF9, 0x28, 0x3B, 0x1F, 0xF8,
    0x97, 0xFF, 0xDE, 0x05, 0x98, 0x0F, 0xEF, 0x2F, 0x11,
    0x8B, 0x5A, 0x0A, 0x6D, 0x1F, 0x6D, 0x36, 0x7E, 0xCF,
    0x27, 0xCB, 0x09, 0xB7, 0x4F, 0x46, 0x3F, 0x66, 0x9E,
    0x5F, 0xEA, 0x2D, 0x75, 0x27, 0xBA, 0xC7, 0xEB, 0xE5,
    0xF1, 0x7B, 0x3D, 0x07, 0x39, 0xF7, 0x8A, 0x52, 0x92,
    0xEA, 0x6B, 0xFB, 0x5F, 0xB1, 0x1F, 0x8D, 0x5D, 0x08,
    0x56, 0x03, 0x30, 0x46, 0xFC, 0x7B, 0x6B, 0xAB, 0xF0,
    0xCF, 0xBC, 0x20, 0x9A, 0xF4, 0x36, 0x1D, 0xA9, 0xE3,
    0x91, 0x61, 0x5E, 0xE6, 0x1B, 0x08, 0x65, 0x99, 0x85,
    0x5F, 0x14, 0xA0, 0x68, 0x40, 0x8D, 0xFF, 0xD8, 0x80,
    0x4D, 0x73, 0x27, 0x31, 0x06, 0x06, 0x15, 0x56, 0xCA,
    0x73, 0xA8, 0xC9, 0x60, 0xE2, 0x7B, 0xC0, 0x8C, 0x6B,
};

static const float
zero   = 0.0,
one    = 1.0,
two8   =  2.5600000000e+02, /* 0x43800000 */
twon8  =  3.9062500000e-03; /* 0x3b800000 */

static inline int __rem_pio2f_internal(float *x, float *y, int e0, int nx)
{
    int32_t jz, jx, jv, jp, jk, carry, n, i, j, k, m, q0, ih;
    int32_t iq[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    float z, fw;
    float f[20]  = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    float fq[20] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    float q[20]  = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

    bool recompute;

    /* initialize jk*/
    jk = 7;
    jp = jk;

    /* determine jx,jv,q0, note that 3>q0 */
    jx =  nx - 1;
    jv = (e0 - 3) / 8;

    if (jv < 0) {
        jv = 0;
    }

    q0 =  e0 - 8 * (jv + 1);

    /* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
    j = jv - jx;
    m = jx + jk;

    for (i = 0; i <= m; i++, j++) {
        f[i] = (j < 0) ? zero : (float) ipio2[j];
    }

    /* compute q[0],q[1],...q[jk] */
    for (i = 0; i <= jk; i++) {
        for (j = 0, fw = 0.0; j <= jx; j++) {
            fw += x[j] * f[jx + i - j];
        }

        q[i] = fw;
    }

    jz = jk;
    do {
        recompute = false;

        /* distill q[] into iq[] reversingly */
        for (i = 0, j = jz, z = q[jz]; j > 0; i++, j--) {
            fw    = (float)((int32_t)(twon8 * z));
            iq[i] = (int32_t)(z - two8 * fw);
            z     =  q[j - 1] + fw;
        }

        /* compute n */
        z  = scalbnf(z, (int)q0);   /* actual value of z */
        z -= (float)8.0 * floorf(z * (float)0.125); /* trim off integer >= 8 */
        n  = (int32_t) z;
        z -= (float)n;
        ih = 0;

        if (q0 > 0) { /* need iq[jz-1] to determine n */
            i  = (iq[jz - 1] >> (8 - q0));
            n += i;
            iq[jz - 1] -= i << (8 - q0);
            ih = iq[jz - 1] >> (7 - q0);
        } else if (q0 == 0) {
            ih = iq[jz - 1] >> 7;
        } else if (z >= (float)0.5) {
            ih = 2;
        } else {
            /* No action required */
        }

        if (ih > 0) { /* q > 0.5 */
            n += 1;
            carry = 0;

            for (i = 0; i < jz ; i++) { /* compute 1-q */
                j = iq[i];

                if (carry == 0) {
                    if (j != 0) {
                        carry = 1;
                        iq[i] = 0x100 - j;
                    }
                } else {
                    iq[i] = 0xff - j;
                }
            }

            if (q0 > 0) {     /* rare case: chance is 1 in 12 */
                switch (q0) {
                default:
                case 1:
                    iq[jz - 1] &= 0x7f;
                    break;

                case 2:
                    iq[jz - 1] &= 0x3f;
                    break;
                }
            }

            if (ih == 2) {
                z = one - z;

                if (carry != 0) {
                    z -= scalbnf(one, (int)q0);
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
                for (k = 1; iq[jk - k] == 0; k++) { /* k = no. of terms needed */
                }

                for (i = jz + 1; i <= jz + k; i++) { /* add q[jz+1] to q[jz+k] */
                    f[jx + i] = (float) ipio2[jv + i];

                    for (j = 0, fw = 0.0; j <= jx; j++) {
                        fw += x[j] * f[jx + i - j];
                    }

                    q[i] = fw;
                }

                jz += k;
                recompute = true;
            }
        }
    } while (recompute);

    /* chop off zero terms */
    if (z == (float)0.0) {
        q0 -= 8;

        for (jz -= 1; jz>=0; --jz) {
            if (iq[jz]!=0) {
                break;
            }
            q0 -= 8;
        }
    } else { /* break z into 8-bit if necessary */
        z = scalbnf(z, -(int)q0);

        if (z >= two8) {
            fw = (float)((int32_t)(twon8 * z));
            iq[jz] = (int32_t)(z - two8 * fw);
            jz += 1;
            q0 += 8;
            iq[jz] = (int32_t) fw;
        } else {
            iq[jz] = (int32_t) z ;
        }
    }

    /* convert integer "bit" chunk to floating-point value */
    fw = scalbnf(one, (int)q0);

    for (i = jz; i >= 0; i--) {
        q[i] = fw * (float)iq[i];
        fw *= twon8;
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

/* __rem_pio2f(x,y)
 *
 * return the remainder of x rem pi/2 in y[0]+y[1]
 * use __rem_pio2f_internal()
 */

/*
 * invpio2:  24 bits of 2/pi
 * pio2_1:   first  17 bit of pi/2
 * pio2_1t:  pi/2 - pio2_1
 * pio2_2:   second 17 bit of pi/2
 * pio2_2t:  pi/2 - (pio2_1+pio2_2)
 * pio2_3:   third  17 bit of pi/2
 * pio2_3t:  pi/2 - (pio2_1+pio2_2+pio2_3)
 */

static const float
half =  5.0000000000e-01, /* 0x3f000000 */
invpio2 =  6.3661980629e-01, /* 0x3f22f984 */
pio2_1  =  1.5707855225e+00, /* 0x3fc90f80 */
pio2_1t =  1.0804334124e-05, /* 0x37354443 */
pio2_2  =  1.0804273188e-05, /* 0x37354400 */
pio2_2t =  6.0770999344e-11, /* 0x2e85a308 */
pio2_3  =  6.0770943833e-11, /* 0x2e85a300 */
pio2_3t =  6.1232342629e-17; /* 0x248d3132 */

int32_t __rem_pio2f(float x, float *y)
{
    float z, w, t, r, fn;
    float tx[3];
    int32_t i, j, n, ix, hx;
    int e0, nx;

    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;

    if (ix <= 0x3f490fd8) { /* |x| ~<= pi/4 , no need for reduction */
        y[0] = x;
        y[1] = 0;
        return 0;
    }

    if (ix < 0x4016cbe4) { /* |x| < 3pi/4, special case with n=+-1 */
        /* 17+17+24 bit pi has sufficient precision and best efficiency */
        if (hx > 0) {
            z = x - pio2_1;

            if ((ix & 0xfffe0000U) != 0x3fc80000) { /* 17+24 bit pi OK */
                y[0] = z - pio2_1t;
                y[1] = (z - y[0]) - pio2_1t;
            } else {        /* near pi/2, use 17+17+24 bit pi */
                z -= pio2_2;
                y[0] = z - pio2_2t;
                y[1] = (z - y[0]) - pio2_2t;
            }

            return 1;
        } else {    /* negative x */
            z = x + pio2_1;

            if ((ix & 0xfffe0000U) != 0x3fc80000) { /* 17+24 bit pi OK */
                y[0] = z + pio2_1t;
                y[1] = (z - y[0]) + pio2_1t;
            } else {        /* near pi/2, use 17+17+24 bit pi */
                z += pio2_2;
                y[0] = z + pio2_2t;
                y[1] = (z - y[0]) + pio2_2t;
            }

            return -1;
        }
    }

    if (ix <= 0x43490f80) { /* |x| ~<= 2^7*(pi/2), medium size */
        t  = fabsf(x);
        n  = (int32_t)(t * invpio2 + half);
        fn = (float)n;
        r  = t - fn * pio2_1;
        w  = fn * pio2_1t;  /* 1st round good to 40 bit */

        {
            uint32_t high;
            j  = ix >> 23;
            y[0] = r - w;
            GET_FLOAT_WORD(high, y[0]);
            i = j - ((high >> 23) & 0xff);

            if (i > 8) { /* 2nd iteration needed, good to 57 */
                t  = r;
                w  = fn * pio2_2;
                r  = t - w;
                w  = fn * pio2_2t - ((t - r) - w);
                y[0] = r - w;
                GET_FLOAT_WORD(high, y[0]);
                i = j - ((high >> 23) & 0xff);

                if (i > 25) {  /* 3rd iteration need, 74 bits acc */
                    t  = r;    /* will cover all possible cases */
                    w  = fn * pio2_3;
                    r  = t - w;
                    w  = fn * pio2_3t - ((t - r) - w);
                    y[0] = r - w;
                }
            }
        }

        y[1] = (r - y[0]) - w;

        if (hx < 0) {
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
    if (!FLT_UWORD_IS_FINITE(ix)) {
        if (isnan(x)) {
            y[1] = x - x;
            y[0] = y[1];
        } else {
            y[1] = __raise_invalidf();
            y[0] = y[1];
        }
        return 0;
    }

    /* set z = scalbn(|x|,ilogb(x)-7) */
    e0     = (int)((ix >> 23) - 134); /* e0 = ilogb(z)-7; */
    SET_FLOAT_WORD(z, ix - ((int32_t)e0 << 23));

    for (i = 0; i < 2; i++) {
        tx[i] = (float)((int32_t)(z));
        z     = (z - tx[i]) * two8;
    }

    tx[2] = z;

    for (nx = 3; nx>0; --nx) { /* skip zero term */
        if (tx[nx-1]!=zero) {
            break;
        }
    }

    n  =  __rem_pio2f_internal(tx, y, e0, nx);

    if (hx < 0) {
        y[0] = -y[0];
        y[1] = -y[1];
        return -n;
    }

    return n;
}

static const float
C1  =  0xaaaaa5.0p-28f, /*  0.04166664555668830871582031250,    0x3D2AAAA5 */
C2  = -0xb60615.0p-33f, /* -0.001388731063343584537506103516,   0xBAB60615 */
C3  =  0xccf47d.0p-39f; /*  0.00002443254288664320483803749084, 0x37CCF47C */

float __cosf(float x, float y)
{
    float hz, z, r, w;

    z  = x * x;
    r  = z * (C1 + z * (C2 + z * C3));

    hz = 0.5f * z;
    w  = one - hz;
    return w + (((one - w) - hz) + (z * r - x * y));
}

static const float
S1  = -0xaaaaab.0p-26f, /* -0.16666667163,      0xBE2AAAAB */
S2  =  0x8888bb.0p-30f, /*  0.0083333803341,    0x3C0888BB */
S3  = -0xd02de1.0p-36f, /* -0.00019853517006,   0xB9502DE1 */
S4  =  0xbe6dbe.0p-42f; /*  0.0000028376084629, 0x363E6DBE */

float __sinf(float x, float y, int iy)
{
    float z, r, v;

    z    =  x * x;
    v    =  z * x;
    r    =  S2 + z * (S3 + z * S4);

    if (iy == 0) {
        return x + v * (S1 + z * r);
    } else {
        return x - ((z * (half * y - v * r) - y) - v * S1);
    }
}
