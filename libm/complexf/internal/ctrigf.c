/* SPDX-License-Identifier: NetBSD */

#include <complex.h>
#include <math.h>

#include "ctrigf.h"

/* calculate cosh and sinh */

void __ccoshsinhf(float x, float *c, float *s)
{
    float e, ei;

    if (fabsf(x) <= 0.5f) {
        *c = coshf(x);
        *s = sinhf(x);
    } else {
        e = expf(x);
        ei = 0.5f / e;
        e = 0.5f * e;
        *s = e - ei;
        *c = e + ei;
    }
}

/* Program to subtract nearest integer multiple of PI */

/* extended precision value of PI: */
static const double DP1 =  3.140625;
static const double DP2 =  9.67502593994140625E-4;
static const double DP3 =  1.509957990978376432E-7;

float __redupif(float x)
{
    float t;
    long i;

    t = x / (float)M_PI;

    if (t >= 0.0f) {
        t += 0.5f;
    } else {
        t -= 0.5f;
    }

    i = t;    /* the multiple */
    t = i;
    t = ((x - t * DP1) - t * DP2) - t * DP3;
    return t;
}
