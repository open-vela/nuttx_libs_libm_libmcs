// SPDX-License-Identifier: PublicDomain

#include <complex.h>
#include <math.h>

long double
cargl(long double complex z)
{     
       #ifdef _LDBL_EQ_DBL
         return carg (z);
       #else
         return atan2l (cimagl (z), creall (z));
       #endif
}
