/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

#include <math.h>
#include "../common/tools.h"

static const float
bp[]     = { 1.0f, 1.5f},
dp_h[]   = { 0.0f, 5.84960938e-01f}, /* 0x3f15c000 */
dp_l[]   = { 0.0f, 1.56322085e-06f}, /* 0x35d1cfdc */
zero     =  0.0f,
one      =  1.0f,
two      =  2.0f,
two24    =  16777216.0f,       /* 0x4b800000 */
/* poly coefs for (3/2)*(log(x)-2s-2/3*s**3 */
L1       =  6.0000002384e-01f, /* 0x3f19999a */
L2       =  4.2857143283e-01f, /* 0x3edb6db7 */
L3       =  3.3333334327e-01f, /* 0x3eaaaaab */
L4       =  2.7272811532e-01f, /* 0x3e8ba305 */
L5       =  2.3066075146e-01f, /* 0x3e6c3255 */
L6       =  2.0697501302e-01f, /* 0x3e53f142 */
P1       =  1.6666667163e-01f, /* 0x3e2aaaab */
P2       = -2.7777778450e-03f, /* 0xbb360b61 */
P3       =  6.6137559770e-05f, /* 0x388ab355 */
P4       = -1.6533901999e-06f, /* 0xb5ddea0e */
P5       =  4.1381369442e-08f, /* 0x3331bb4c */
lg2      =  6.9314718246e-01f, /* 0x3f317218 */
lg2_h    =  6.93145752e-01f,   /* 0x3f317200 */
lg2_l    =  1.42860654e-06f,   /* 0x35bfbe8c */
ovt      =  4.2995665694e-08f, /* -(128-log2(ovfl+.5ulp)) */
cp       =  9.6179670095e-01f, /* 0x3f76384f =2/(3ln2) */
cp_h     =  9.6191406250e-01f, /* 0x3f764000 =12b of cp */
cp_l     = -1.1736857402e-04f, /* 0xb8f623c6 =tail of cp_h */
ivln2    =  1.4426950216e+00f, /* 0x3fb8aa3b =1/ln2 */
ivln2_h  =  1.4426879883e+00f, /* 0x3fb8aa00 =16b 1/ln2*/
ivln2_l  =  7.0526075433e-06f; /* 0x36eca570 =1/ln2 tail*/

float powf(float x, float y)
{
    float z, ax, z_h, z_l, p_h, p_l;
    float _y1, t1, t2, r, s, t, u, v, w;
    int32_t i, j, k, yisint, n;
    int32_t hx, hy, ix, iy, is;

    GET_FLOAT_WORD(hx, x);
    GET_FLOAT_WORD(hy, y);
    ix = hx & 0x7fffffff;
    iy = hy & 0x7fffffff;

    /* y==zero: x**0 = 1 */
    if (FLT_UWORD_IS_ZERO(iy)) {
        if (__issignalingf(x) != 0) {
            return x + y;
        }

        return one;
    }

    /* x|y==NaN return NaN unless x==1 then return 1 */
    if (FLT_UWORD_IS_NAN(ix) || FLT_UWORD_IS_NAN(iy)) {
        if (hx == 0x3f800000 && __issignalingf(y) == 0) {
            return one;
        } else {
            return x + y;
        }
    }

#ifdef __LIBMCS_FPU_DAZ
    x *= __volatile_onef;
    y *= __volatile_onef;

    GET_FLOAT_WORD(hx, x);
    GET_FLOAT_WORD(hy, y);
    ix = hx & 0x7fffffff;
    iy = hy & 0x7fffffff;
#endif /* defined(__LIBMCS_FPU_DAZ) */

    /* determine if y is an odd int when x < 0
     * yisint = 0    ... y is not an integer
     * yisint = 1    ... y is an odd int
     * yisint = 2    ... y is an even int
     */
    yisint  = 0;

    if (hx < 0) {
        if (iy >= 0x4b800000) {
            yisint = 2;    /* even integer y */
        } else if (iy >= 0x3f800000) {
            k = (iy >> 23) - 0x7f;   /* exponent */
            j = iy >> (23 - k);

            if ((j << (23 - k)) == iy) {
                yisint = 2 - (j & 1);
            }
        } else {
            /* No action required */
        }
    }

    /* special value of y */
    if (FLT_UWORD_IS_INFINITE(iy)) {    /* y is +-inf */
        if (ix == 0x3f800000) {
            return one;    /* +-1**+-inf = 1 */
        } else if (ix > 0x3f800000) { /* (|x|>1)**+-inf = inf,0 */
            return (hy >= 0) ? y : zero;
        } else {        /* (|x|<1)**-,+inf = inf,0 */
            return (hy < 0) ? -y : zero;
        }
    }

    if (iy == 0x3f800000) { /* y is  +-1 */
        if (hy < 0) {
            return one / x;
        } else {
            return x;
        }
    }

    if (hy == 0x40000000) {
        return x * x;    /* y is  2 */
    }

    if (hy == 0x3f000000) { /* y is  0.5 */
        if (hx >= 0) { /* x >= +0 */
            return sqrtf(x);
        }
    }

    ax   = fabsf(x);

    /* special value of x */
    if (FLT_UWORD_IS_INFINITE(ix) || FLT_UWORD_IS_ZERO(ix) || ix == 0x3f800000) {
        z = ax;                         /*x is +-0,+-inf,+-1*/

        if (hy < 0) {                   /* z = (1/|x|) */
            if (FLT_UWORD_IS_INFINITE(ix)) {
                z = zero;
            } else if (FLT_UWORD_IS_ZERO(ix)) {
                z = __raise_div_by_zerof(z);
            } else {
                /* No action required */
            }
        }

        if (hx < 0) {
            if (((ix - 0x3f800000) | yisint) == 0) {
                z = __raise_invalidf(); /* (-1)**non-int is NaN */
            } else if (yisint == 1) {
                z = -z;                 /* (x<0)**odd = -(|x|**odd) */
            } else {
                /* No action required */
            }
        }

        return z;
    }

    /* (x<0)**(non-int) is NaN */
    if (((((uint32_t)hx >> 31U) - 1U) | (uint32_t)yisint) == 0) {
        return __raise_invalidf();
    }

    /* |y| is huge */
    if (iy > 0x4d000000) { /* if |y| > 2**27 */
        /* over/underflow if x is not close to one */
        /* Contrary to the double procedure we don't need the sign for these over/underflows as |y| > 2**27 means that y is an even integer (should the border ever be lowered to 2**23 or lower, the sign plays a role). */
        if (ix < 0x3f7ffff4) {
            return (hy < 0) ? __raise_overflowf(one) : __raise_underflowf(one);
        }

        if (ix > 0x3f800007) {
            return (hy > 0) ? __raise_overflowf(one) : __raise_underflowf(one);
        }

        /* now |1-x| is tiny <= 2**-20, suffice to compute
           log(x) by x-x^2/2+x^3/3-x^4/4 */
        t = ax - 1;      /* t has 20 trailing zeros */
        w = (t * t) * (0.5f - t * (0.333333333333f - t * 0.25f));
        u = ivln2_h * t;  /* ivln2_h has 16 sig. bits */
        v = t * ivln2_l - w * ivln2;
        t1 = u + v;
        GET_FLOAT_WORD(is, t1);
        SET_FLOAT_WORD(t1, is & 0xfffff000U);
        t2 = v - (t1 - u);
    } else {
        float s2, s_h, s_l, t_h, t_l;
        n = 0;

        /* take care subnormal number */
        if (FLT_UWORD_IS_SUBNORMAL(ix)) {
            ax *= two24;
            n -= 24;
            GET_FLOAT_WORD(ix, ax);
        }

        n  += ((ix) >> 23) - 0x7f;
        j  = ix & 0x007fffff;
        /* determine interval */
        ix = j | 0x3f800000;      /* normalize ix */

        if (j <= 0x1cc471) {
            k = 0;    /* |x|<sqrt(3/2) */
        } else if (j < 0x5db3d7) {
            k = 1;    /* |x|<sqrt(3)   */
        } else {
            k = 0;
            n += 1;
            ix -= 0x00800000;
        }

        SET_FLOAT_WORD(ax, ix);

        /* compute s = s_h+s_l = (x-1)/(x+1) or (x-1.5)/(x+1.5) */
        u = ax - bp[k];      /* bp[0]=1.0, bp[1]=1.5 */
        v = one / (ax + bp[k]);
        s = u * v;
        s_h = s;
        GET_FLOAT_WORD(is, s_h);
        SET_FLOAT_WORD(s_h, is & 0xfffff000U);
        /* t_h=ax+bp[k] High */
        is = ((ix >> 1) & 0xfffff000U) | 0x20000000;
        SET_FLOAT_WORD(t_h, is + 0x00400000 + (k << 21));
        t_l = ax - (t_h - bp[k]);
        s_l = v * ((u - s_h * t_h) - s_h * t_l);
        /* compute log(ax) */
        s2 = s * s;
        r = s2 * s2 * (L1 + s2 * (L2 + s2 * (L3 + s2 * (L4 + s2 * (L5 + s2 * L6)))));
        r += s_l * (s_h + s);
        s2  = s_h * s_h;
        t_h = 3.0f + s2 + r;
        GET_FLOAT_WORD(is, t_h);
        SET_FLOAT_WORD(t_h, is & 0xfffff000U);
        t_l = r - ((t_h - 3.0f) - s2);
        /* u+v = s*(1+...) */
        u = s_h * t_h;
        v = s_l * t_h + t_l * s;
        /* 2/(3log2)*(s+...) */
        p_h = u + v;
        GET_FLOAT_WORD(is, p_h);
        SET_FLOAT_WORD(p_h, is & 0xfffff000U);
        p_l = v - (p_h - u);
        z_h = cp_h * p_h;      /* cp_h+cp_l = 2/(3*log2) */
        z_l = cp_l * p_h + p_l * cp + dp_l[k];
        /* log2(ax) = (s+..)*2/(3*log2) = n + dp_h + z_h + z_l */
        t = (float)n;
        t1 = (((z_h + z_l) + dp_h[k]) + t);
        GET_FLOAT_WORD(is, t1);
        SET_FLOAT_WORD(t1, is & 0xfffff000U);
        t2 = z_l - (((t1 - t) - dp_h[k]) - z_h);
    }

    s = one; /* s (sign of result -ve**odd) = -1 else = 1 */

    if (((((uint32_t)hx >> 31U) - 1U) | (uint32_t)(yisint - 1)) == 0) {
        s = -one;    /* (-ve)**(odd int) */
    }

    /* split up y into _y1+y2 and compute (_y1+y2)*(t1+t2) */
    GET_FLOAT_WORD(is, y);
    SET_FLOAT_WORD(_y1, is & 0xfffff000U);
    p_l = (y - _y1) * t1 + y * t2;
    p_h = _y1 * t1;
    z = p_l + p_h;
    GET_FLOAT_WORD(j, z);
    i = j & 0x7fffffff;

    if (j > 0) {
        if (i > FLT_UWORD_EXP_MAX) {
            return __raise_overflowf(s);      /* overflow */
        } else if (i == FLT_UWORD_EXP_MAX) {
            if (p_l + ovt > z - p_h) {
                return __raise_overflowf(s);  /* overflow */
            }
        } else {
            /* No action required */
        }
    } else {
        if (i > FLT_UWORD_EXP_MIN) {
            return __raise_underflowf(s);      /* underflow */
        } else if (i == FLT_UWORD_EXP_MIN) {
            if (p_l <= z - p_h) {
                return __raise_underflowf(s);  /* underflow */
            }
        } else {
            /* No action required */
        }
    }

    /*
     * compute 2**(p_h+p_l)
     */
    k = (i >> 23) - 0x7f;
    n = 0;

    if (i > 0x3f000000) {     /* if |z| > 0.5, set n = [z+0.5] */
        n = j + (0x00800000 >> (k + 1));
        k = ((n & 0x7fffffff) >> 23) - 0x7f; /* new k for n */
        SET_FLOAT_WORD(t, n & ~(0x007fffff >> k));
        n = ((n & 0x007fffff) | 0x00800000) >> (23 - k);

        if (j < 0) {
            n = -n;
        }

        p_h -= t;
    }

    t = p_l + p_h;
    GET_FLOAT_WORD(is, t);
    SET_FLOAT_WORD(t, is & 0xffff8000U);
    u = t * lg2_h;
    v = (p_l - (t - p_h)) * lg2 + t * lg2_l;
    z = u + v;
    w = v - (z - u);
    t  = z * z;
    t1  = z - t * (P1 + t * (P2 + t * (P3 + t * (P4 + t * P5))));
    r  = (z * t1) / (t1 - two) - (w + z * w);
    z  = one - (r - z);
    GET_FLOAT_WORD(j, z);
    j += (n << 23);

    if ((j >> 23) <= 0) {
        z = scalbnf(z, (int32_t)n);    /* subnormal output */
    } else {
        SET_FLOAT_WORD(z, j);
    }

    return s * z;
}

#ifdef __LIBMCS_DOUBLE_IS_32BITS

double pow(double x, double y)
{
    return (double) powf((float) x, (float) y);
}

#endif /* #ifdef __LIBMCS_DOUBLE_IS_32BITS */
