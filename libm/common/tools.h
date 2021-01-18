/* SPDX-License-Identifier: SunMicrosystems */
/* Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved. */

/* REDHAT LOCAL: Include files.  */
#include <complex.h>
#include <math.h>

#include <stdbool.h>
#include <stdint.h>

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    #define __IEEE_BIG_ENDIAN
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define __IEEE_LITTLE_ENDIAN
#endif

/* A union which permits us to convert between a double and two 32 bit
   ints.  */

#ifdef __IEEE_BIG_ENDIAN

typedef union {
    double value;
    struct {
        uint32_t msw;
        uint32_t lsw;
    } parts;
} ieee_double_shape_type;

#endif

#ifdef __IEEE_LITTLE_ENDIAN

typedef union {
    double value;
    struct {
        uint32_t lsw;
        uint32_t msw;
    } parts;
} ieee_double_shape_type;

#endif

/* Get two 32 bit ints from a double.  */

#define EXTRACT_WORDS(ix0,ix1,d)                        \
    do {                                                \
        ieee_double_shape_type ew_u;                    \
        ew_u.value = (d);                               \
        (ix0) = ew_u.parts.msw;                         \
        (ix1) = ew_u.parts.lsw;                         \
    } while (0)

/* Get the more significant 32 bit int from a double.  */

#define GET_HIGH_WORD(i,d)                              \
    do {                                                \
        ieee_double_shape_type gh_u;                    \
        gh_u.value = (d);                               \
        (i) = gh_u.parts.msw;                           \
    } while (0)

/* Get the less significant 32 bit int from a double.  */

#define GET_LOW_WORD(i,d)                               \
    do {                                                \
        ieee_double_shape_type gl_u;                    \
        gl_u.value = (d);                               \
        (i) = gl_u.parts.lsw;                           \
    } while (0)

/* Set a double from two 32 bit ints.  */

#define INSERT_WORDS(d,ix0,ix1)                         \
    do {                                                \
        ieee_double_shape_type iw_u;                    \
        iw_u.parts.msw = (ix0);                         \
        iw_u.parts.lsw = (ix1);                         \
        (d) = iw_u.value;                               \
    } while (0)

/* Set the more significant 32 bits of a double from an int.  */

#define SET_HIGH_WORD(d,v)                              \
    do {                                                \
        ieee_double_shape_type sh_u;                    \
        sh_u.value = (d);                               \
        sh_u.parts.msw = (v);                           \
        (d) = sh_u.value;                               \
    } while (0)

/* Set the less significant 32 bits of a double from an int.  */

#define SET_LOW_WORD(d,v)                               \
    do {                                                \
        ieee_double_shape_type sl_u;                    \
        sl_u.value = (d);                               \
        sl_u.parts.lsw = (v);                           \
        (d) = sl_u.value;                               \
    } while (0)

/* A union which permits us to convert between a float and a 32 bit
   int.  */

typedef union {
    float value;
    __uint32_t word;
} ieee_float_shape_type;

/* Get a 32 bit int from a float.  */

#define GET_FLOAT_WORD(i,d)                             \
    do {                                                \
        ieee_float_shape_type gf_u;                     \
        gf_u.value = (d);                               \
        (i) = gf_u.word;                                \
    } while (0)

/* Set a float from a 32 bit int.  */

#define SET_FLOAT_WORD(d,i)                             \
    do {                                                \
        ieee_float_shape_type sf_u;                     \
        sf_u.word = (i);                                \
        (d) = sf_u.value;                               \
    } while (0)

/* Macros to avoid undefined behaviour that can arise if the amount
   of a shift is exactly equal to the size of the shifted operand.  */

#define SAFE_LEFT_SHIFT(op,amt)                         \
    (((amt) < 8 * sizeof(op)) ? ((op) << (amt)) : 0)

#define SAFE_RIGHT_SHIFT(op,amt)                        \
    (((amt) < 8 * sizeof(op)) ? ((op) >> (amt)) : 0)

/*
 * Quoting from ISO/IEC 9899:TC2:
 *
 * 6.2.5.13 Types
 * Each complex type has the same representation and alignment requirements as
 * an array type containing exactly two elements of the corresponding real type;
 * the first element is equal to the real part, and the second element to the
 * imaginary part, of the complex number.
 */
typedef union {
    float complex z;
    float parts[2];
} float_complex;

typedef union {
    double complex z;
    double parts[2];
} double_complex;

typedef union {
    long double complex z;
    long double parts[2];
} long_double_complex;

#define REAL_PART(z)    ((z).parts[0])
#define IMAG_PART(z)    ((z).parts[1])

