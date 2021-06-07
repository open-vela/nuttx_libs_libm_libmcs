/* SPDX-License-Identifier: GTDGmbH */
/* Copyright 2020-2021 by GTD GmbH. */

#ifndef _LIBMCS_FENV_H_
#define	_LIBMCS_FENV_H_

#error TBD add error message that fenv.h/fenv.c shall not be used as is.

#ifdef __cplusplus
extern "C"{
#endif

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

#ifdef __cplusplus
}
#endif

#endif /* !_LIBMCS_FENV_H_ */
