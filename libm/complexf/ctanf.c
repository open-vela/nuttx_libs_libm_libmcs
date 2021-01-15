/* SPDX-License-Identifier: NetBSD */

#include <complex.h>
#include <math.h>

/* Taylor series expansion for cosh(2y) - cos(2x) */

float __ctansf(float complex z)
{
    float f, x, x2, y, y2, rn, t, d;

    x = fabsf(2.0f * crealf(z));
    y = fabsf(2.0f * cimagf(z));

    x = __redupif(x);

    x = x * x;
    y = y * y;
    x2 = 1.0f;
    y2 = 1.0f;
    f = 1.0f;
    rn = 0.0f;
    d = 0.0f;

    do {
        rn += 1.0f;
        f *= rn;
        rn += 1.0f;
        f *= rn;
        x2 *= x;
        y2 *= y;
        t = y2 + x2;
        t /= f;
        d += t;

        rn += 1.0f;
        f *= rn;
        rn += 1.0f;
        f *= rn;
        x2 *= x;
        y2 *= y;
        t = y2 - x2;
        t /= f;
        d += t;
    } while (fabsf(t / d) > MACHEPF);

    return d;
}

float complex ctanf(float complex z)
{
    float complex w;
    float d;

    d = cosf(2.0f * crealf(z)) + coshf(2.0f * cimagf(z));

    if (fabsf(d) < 0.25f) {
        d = __ctansf(z);
    }

    if (d == 0.0f) {
        w = HUGE_VALF + HUGE_VALF * I;
        return w;
    }

    w = sinf(2.0f * crealf(z)) / d + (sinhf(2.0f * cimagf(z)) / d) * I;
    return w;
}

#ifdef _DOUBLE_IS_32BITS

double complex ctan(double complex z)
{
    return (double complex) ctanf((float complex) z);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
