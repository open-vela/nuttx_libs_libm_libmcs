// SPDX-License-Identifier: SunMicrosystems
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.

#include "fdlibm.h"

float truncf(float x)
{
  __int32_t signbit, w, exponent_less_127;

  GET_FLOAT_WORD(w,x);

  /* Extract sign bit. */
  signbit = w & 0x80000000;

  /* Extract exponent field. */
  exponent_less_127 = ((w & 0x7f800000) >> 23) - 127;

  if (exponent_less_127 < 23)
    {
      if (exponent_less_127 < 0)
        {
          /* -1 < x < 1, so result is +0 or -0. */
          SET_FLOAT_WORD(x, signbit);
        }
      else
        {
          SET_FLOAT_WORD(x, signbit | (w & ~(0x007fffff >> exponent_less_127)));
        }
    }
  else
    {
      if (exponent_less_127 == 128)
        /* x is NaN or infinite. */
        return x + x;

      /* All bits in the fraction field are relevant. */
    }
  return x;
}

#ifdef _DOUBLE_IS_32BITS

double trunc(double x)
{
    return (double) truncf((float) x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
