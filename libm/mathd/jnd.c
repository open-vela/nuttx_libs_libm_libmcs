// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.

/*
 * wrapper jn(int n, double x), yn(int n, double x)
 * floating point Bessel's function of the 1st and 2nd kind
 * of order n
 *          
 * Special cases:
 *    y0(0)=y1(0)=yn(n,0) = -inf with division by zero signal;
 *    y0(-ve)=y1(-ve)=yn(n,-ve) are NaN with invalid signal.
 * Note 2. About jn(n,x), yn(n,x)
 *    For n=0, j0(x) is called,
 *    for n=1, j1(x) is called,
 *    for n<x, forward recursion us used starting
 *    from values of j0(x) and j1(x).
 *    for n>x, a continued fraction approximation to
 *    j(n,x)/j(n-1,x) is evaluated and then backward
 *    recursion is used starting from a supposed value
 *    for j(n,x). The resulting value of j(0,x) is
 *    compared with the actual value to correct the
 *    supposed value of j(n,x).
 *
 *    yn(n,x) is similar in all respects, except
 *    that forward recursion is used for all
 *    values of n>1.
 *    
 */

#include "fdlibm.h"

#ifndef _DOUBLE_IS_32BITS

double jn(int n, double x)    /* wrapper jn */
{
    return __ieee754_jn(n,x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
