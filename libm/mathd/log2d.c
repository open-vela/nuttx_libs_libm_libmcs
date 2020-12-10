// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.

/*
FUNCTION
	<<log2>>, <<log2f>>---base 2 logarithm
INDEX
	log2
INDEX
	log2f

SYNOPSIS
	#include <math.h>
	double log2(double <[x]>);
	float log2f(float <[x]>);

DESCRIPTION
The <<log2>> functions compute the base-2 logarithm of <[x]>.  A domain error
occurs if the argument is less than zero.  A range error occurs if the
argument is zero.

The Newlib implementations are not full, intrinisic calculations, but
rather are derivatives based on <<log>>.  (Accuracy might be slightly off from
a direct calculation.)  In addition to functions, they are also implemented as
macros defined in math.h:
. #define log2(x) (log (x) / _M_LN2)
. #define log2f(x) (logf (x) / (float) _M_LN2)
To use the functions instead, just undefine the macros first.

RETURNS
The <<log2>> functions return
@ifnottex
<<log base-2(<[x]>)>>
@end ifnottex
@tex
$log_2(x)$
@end tex
on success.
When <[x]> is zero, the
returned value is <<-HUGE_VAL>> and <<errno>> is set to <<ERANGE>>.
When <[x]> is negative, the returned value is NaN (not a number) and
<<errno>> is set to <<EDOM>>.

PORTABILITY
C99, POSIX, System V Interface Definition (Issue 6).
*/

/*
 * wrapper log2(x)
 */

#include "fdlibm.h"
#include <math.h>

#ifndef _DOUBLE_IS_32BITS

double log2(double x)		/* wrapper log2 */
{
  return (log(x) / M_LN2);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
