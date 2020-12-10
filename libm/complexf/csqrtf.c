// SPDX-License-Identifier: NetBSD

#include <complex.h>
#include <math.h>

float complex
csqrtf(float complex z)
{
    float complex w;
    float x, y, r, t, scale;

    x = crealf (z);
    y = cimagf (z);

    if (y == 0.0f) {
        if (x < 0.0f) {
            w = 0.0f + sqrtf(-x) * I;
            return w;
        } else if (x == 0.0f) {
            return (0.0f + y * I);
        } else {
            w = sqrtf(x) + y * I;
            return w;
        }
    }

    if (x == 0.0f) {
        r = fabsf(y);
        r = sqrtf(0.5f * r);
        if (y > 0)
            w = r + r * I;
        else
            w = r - r * I;
        return w;
    }

    /* Rescale to avoid internal overflow or underflow.  */
    if ((fabsf(x) > 4.0f) || (fabsf(y) > 4.0f)) {
        x *= 0.25f;
        y *= 0.25f;
        scale = 2.0f;
    } else {
        x *= 6.7108864e7f; /* 2^26 */
        y *= 6.7108864e7f;
        scale = 1.220703125e-4f; /* 2^-13 */
    }
    w = x + y * I;
    r = cabsf(w);
    if( x > 0 ) {
        t = sqrtf(0.5f * r + 0.5f * x);
        r = scale * fabsf((0.5f * y) / t);
        t *= scale;
    } else {
        r = sqrtf(0.5f * r - 0.5f * x);
        t = scale * fabsf((0.5f * y) / r);
        r *= scale;
    }

    if (y < 0)
        w = t - r * I;
    else
        w = t + r * I;
    return w;
}

#ifdef _DOUBLE_IS_32BITS

double complex csqrt (double complex z)
{
    return (double complex) csqrtf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
