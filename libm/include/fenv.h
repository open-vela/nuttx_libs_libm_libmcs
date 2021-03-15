/* SPDX-License-Identifier: GTDGmbH */
/* Copyright 2020-2021 by GTD GmbH. */

#pragma once

#error TBD add error message that fenv.h/fenv.c shall not be used as is.

/* Floating-point Exceptions */
extern int feclearexcept(int);
extern int feraiseexcept(int);
extern int fegetexceptflag(fexcept_t *, int);
extern int fesetexceptflag(const fexcept_t *, int);

/* Rounding Direction */
extern int fegetround();
extern int fesetround(int);

/* Entire Environment */
extern int fegetenv(fenv_t *);
extern int fesetenv(const fenv_t *);
extern int feholdexcept(fenv_t *);
extern int feupdateenv(const fenv_t *);

/* Other */
extern int fetestexcept(int);
