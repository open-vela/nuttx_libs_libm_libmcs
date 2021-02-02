/* SPDX-License-Identifier: GTDGmbH */
/* Copyright 2020-2021 by GTD GmbH. */
/* TBD Check if license/copyright should be SunMicrosystems */

#pragma once

/* If an FPU is not standard compliant for subnormal values, use the define LIBMCS_FPU_DAZ to force 
 * each procedure to first multiply the input value(s) by 1, therefore using the FPUs defined
 * behaviour for subnormal values as follows:
 * If the FPU is standard compliant for subnormals, the multiplication does not cause any
 * difference in the behaviour of the procedure.
 * If the FPU can not handle subnormals at all, it's very likely that a special FPU trap will be
 * thrown. This trap can then be handled by the user if so inclined.
 * If the FPU has an internal implementation for DAZ (denormals are zero), the input values will be
 * reduced to zero and the procedures will then behave as if a zero was used as an input. Usually
 * this will also generate an inexact exception. */
// #define LIBMCS_FPU_DAZ
#ifdef LIBMCS_FPU_DAZ
    #define __LIBMCS_FPU_DAZ
    static volatile double __volatile_one = 1.0;
    static volatile float __volatile_onef = 1.0f;
#endif /* LIBMCS_FPU_DAZ */

/* Define to tell the libm to be built for 32bit doubles. */
// #define LIBMCS_DOUBLE_IS_32BITS
#ifdef LIBMCS_DOUBLE_IS_32BITS
    #define __LIBMCS_DOUBLE_IS_32BITS
#endif /* LIBMCS_DOUBLE_IS_32BITS */

/* Define to tell the libm to be built for 64bit long doubles. */
#define LIBMCS_LONG_DOUBLE_IS_64BITS
#ifdef LIBMCS_LONG_DOUBLE_IS_64BITS
    #define __LIBMCS_LONG_DOUBLE_IS_64BITS
#endif /* LIBMCS_LONG_DOUBLE_IS_64BITS */

/* Most routines need to check whether a float is finite, infinite, or not a
   number, and many need to know whether the result of an operation will
   overflow. The macros below wrap up that kind of information:

   FLT_UWORD_IS_FINITE(X)
    True if a positive float with bitmask X is finite.

   FLT_UWORD_IS_NAN(X)
    True if a positive float with bitmask X is not a number.

   FLT_UWORD_IS_INFINITE(X)
    True if a positive float with bitmask X is +infinity.

   FLT_UWORD_MAX
    The bitmask of FLT_MAX.

   FLT_UWORD_HALF_MAX
    The bitmask of FLT_MAX/2.

   FLT_UWORD_EXP_MAX
    The bitmask of the largest finite exponent (129 if the largest
    exponent is used for finite numbers, 128 otherwise).

   FLT_UWORD_LOG_MAX
    The bitmask of log(FLT_MAX), rounded down.  This value is the largest
    input that can be passed to exp() without producing overflow.

   FLT_UWORD_LOG_2MAX
    The bitmask of log(2*FLT_MAX), rounded down.  This value is the
    largest input than can be passed to cosh() without producing
    overflow.

   FLT_LARGEST_EXP
    The largest biased exponent that can be used for finite numbers
    (255 if the largest exponent is used for finite numbers, 254
    otherwise) */

#define FLT_UWORD_IS_FINITE(x) ((x)<0x7f800000L)
#define FLT_UWORD_IS_NAN(x) ((x)>0x7f800000L)
#define FLT_UWORD_IS_INFINITE(x) ((x)==0x7f800000L)
#define FLT_UWORD_MAX 0x7f7fffffL
#define FLT_UWORD_EXP_MAX 0x43000000
#define FLT_UWORD_LOG_MAX 0x42b17217
#define FLT_UWORD_LOG_2MAX 0x42b2d4fc
#define HUGE ((float)3.40282346638528860e+38)
#define FLT_UWORD_HALF_MAX (FLT_UWORD_MAX-(1L<<23))
#define FLT_LARGEST_EXP (FLT_UWORD_MAX>>23)

/* Many routines check for zero and subnormal numbers.  Such things depend
   on whether the target supports denormals or not:

   FLT_UWORD_IS_ZERO(X)
    True if a positive float with bitmask X is +0.    Without denormals,
    any float with a zero exponent is a +0 representation.    With
    denormals, the only +0 representation is a 0 bitmask.

   FLT_UWORD_IS_SUBNORMAL(X)
    True if a non-zero positive float with bitmask X is subnormal.
    (Routines should check for zeros first.)

   FLT_UWORD_MIN
    The bitmask of the smallest float above +0.  Call this number
    REAL_FLT_MIN...

   FLT_UWORD_EXP_MIN
    The bitmask of the float representation of REAL_FLT_MIN's exponent.

   FLT_UWORD_LOG_MIN
    The bitmask of |log(REAL_FLT_MIN)|, rounding down.

   FLT_SMALLEST_EXP
    REAL_FLT_MIN's exponent - EXP_BIAS (1 if denormals are not supported,
    -22 if they are).
*/

#ifdef __LIBMCS_FPU_DAZ
    #define FLT_UWORD_IS_ZERO(x) ((x)<0x00800000L)
    #define FLT_UWORD_IS_SUBNORMAL(x) 0
    #define FLT_UWORD_MIN 0x00800000
    #define FLT_UWORD_EXP_MIN 0x42fc0000
    #define FLT_UWORD_LOG_MIN 0x42aeac50
    #define FLT_SMALLEST_EXP 1
#else
    #define FLT_UWORD_IS_ZERO(x) ((x)==0)
    #define FLT_UWORD_IS_SUBNORMAL(x) ((x)<0x00800000L)
    #define FLT_UWORD_MIN 0x00000001
    #define FLT_UWORD_EXP_MIN 0x43160000
    #define FLT_UWORD_LOG_MIN 0x42cff1b5
    #define FLT_SMALLEST_EXP -22
#endif

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    #define __IEEE_BIG_ENDIAN
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define __IEEE_LITTLE_ENDIAN
#endif

/* The original code used statements like
    n0 = ((*(int*)&one)>>29)^1;        * index of high word *
    ix0 = *(n0+(int*)&x);            * high word of x *
    ix1 = *((1-n0)+(int*)&x);        * low word of x *
   to dig two 32 bit words out of the 64 bit IEEE floating point
   value.  That is non-ANSI, and, moreover, the gcc instruction
   scheduler gets it wrong.  We instead use the following macros.
   Unlike the original code, we determine the endianness at compile
   time, not at run time; I don't see much benefit to selecting
   endianness at run time.  */

#ifndef __IEEE_BIG_ENDIAN
    #ifndef __IEEE_LITTLE_ENDIAN
        #error Must define endianness
    #endif
#endif