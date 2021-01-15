/* SPDX-License-Identifier: GTDGmbH */
/* Copyright 2020-2021 by GTD GmbH. */

float nanf(const char *payload)
{
    return 0.0f / 0.0f;
}

#ifdef _DOUBLE_IS_32BITS

double nan(const char *payload)
{
    return (double) nanf(payload);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
