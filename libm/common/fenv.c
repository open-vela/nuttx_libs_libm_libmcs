// SPDX-License-Identifier: GTDGmbH
// Copyright 2020-2021 by GTD GmbH.

#include <fenv.h>

#error TBD add error message that fenv.h/fenv.c shall not be used as is.

int feclearexcept(int excepts)
{
    return -1;
}

int feraiseexcept(int excepts)
{
    return -1;
}

int fegetexceptflag(fexcept_t* flagp, int excepts)
{
    return -1;
}

int fesetexceptflag(const fexcept_t* flagp, int excepts)
{
    return -1;
}

int fegetround()
{
    return -1;
}

int fesetround(int rdir)
{
    return -1;
}

int fegetenv(fenv_t* envp)
{
    return -1;
}

int fesetenv(const fenv_t* envp)
{
    return -1;
}

int feholdexcept(fenv_t* envp)
{
    return -1;
}

int feupdateenv(const fenv_t* envp)
{
    return -1;
}

int fetestexcept(int excepts)
{
    return -1;
}