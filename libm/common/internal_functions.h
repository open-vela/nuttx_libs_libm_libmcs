/* SPDX-License-Identifier: GTDGmbH */
/* Copyright 2020-2021 by GTD GmbH. */

#pragma once

/* Double internal trigonometric functions */
extern double __sin(double x, double y, int iy);
extern double __cos(double x, double y);
extern __int32_t __rem_pio2(double x, double *y);

/* Float internal trigonometric functions */
extern float __sinf(float x, float y, int iy);
extern float __cosf(float x, float y);
extern __int32_t __rem_pio2f(float x, float *y);

/* Double internal Bessel functions */
extern double __j0(double x);
extern double __j1(double x);
extern double __jn(int n, double x);
extern double __y0(double x);
extern double __y1(double x);
extern double __yn(int n, double x);

/* Double complex internal trigonometric functions */
extern void __cchsh(double x, double *c, double *s);
extern double __redupi(double x);

/* Float complex internal trigonometric functions */
extern void __cchshf(float x, float *c, float *s);
extern float __redupif(float x);
