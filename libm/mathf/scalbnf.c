// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
// Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.

#include "fdlibm.h"
#include <limits.h>
#include <float.h>

#if INT_MAX > 50000
#define OVERFLOW_INT 50000
#else
#define OVERFLOW_INT 30000
#endif

static const float
two25   =  3.355443200e+07,    /* 0x4c000000 */
twom25  =  2.9802322388e-08,    /* 0x33000000 */
huge   = 1.0e+30,
tiny   = 1.0e-30;

float scalbnf (float x, int n)
{
    __int32_t  k,ix;
    __uint32_t hx;

    GET_FLOAT_WORD(ix,x);
    hx = ix&0x7fffffff;
        k = hx>>23;        /* extract exponent */
    if (FLT_UWORD_IS_ZERO(hx))
        return x;
        if (!FLT_UWORD_IS_FINITE(hx))
        return x+x;        /* NaN or Inf */
        if (FLT_UWORD_IS_SUBNORMAL(hx)) {
        x *= two25;
        GET_FLOAT_WORD(ix,x);
        k = ((ix&0x7f800000)>>23) - 25; 
            if (n< -50000) return tiny*x;     /*underflow*/
        }
        k = k+n; 
        if (k > FLT_LARGEST_EXP) return huge*copysignf(huge,x); /* overflow  */
        if (k > 0)                 /* normal result */
        {SET_FLOAT_WORD(x,(ix&0x807fffff)|(k<<23)); return x;}
        if (k < FLT_SMALLEST_EXP) {
            if (n > OVERFLOW_INT)     /* in case integer overflow in n+k */
        return huge*copysignf(huge,x);    /*overflow*/
        else return tiny*copysignf(tiny,x);    /*underflow*/
        }
        k += 25;                /* subnormal result */
    SET_FLOAT_WORD(x,(ix&0x807fffff)|(k<<23));
        return x*twom25;
}

#ifdef _DOUBLE_IS_32BITS

double scalbn(double x, int n)
{
    return (double) scalbnf((float) x, n);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
