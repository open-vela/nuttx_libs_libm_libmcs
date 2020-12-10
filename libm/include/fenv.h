// SPDX-License-Identifier: GTDGmbH
// Copyright 2020-2021 by GTD GmbH.

#pragma once

#error TBD add error message that fenv.h/fenv.c shall not be used as is.

// Floating-point Exceptions
extern int feclearexcept(int excepts);
extern int feraiseexcept(int excepts);
extern int fegetexceptflag(fexcept_t* flagp, int excepts);
extern int fesetexceptflag(const fexcept_t* flagp, int excepts);

// Rounding Direction
extern int fegetround();
extern int fesetround(int rdir);

// Entire Environment
extern int fegetenv(fenv_t* envp);
extern int fesetenv(const fenv_t* envp);
extern int feholdexcept(fenv_t* envp);
extern int feupdateenv(const fenv_t* envp);

// Other
extern int fetestexcept(int excepts);
