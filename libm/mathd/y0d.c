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

/*
 * wrapper j0(double x), y0(double x)
 */

#include "fdlibm.h"

#ifndef _DOUBLE_IS_32BITS

double y0(double x)
{
    return __ieee754_y0(x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
