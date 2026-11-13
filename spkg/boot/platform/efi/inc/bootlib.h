/*
 * Boot library and interfaces.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _BOOTLIB_H
#define _BOOTLIB_H 1

#include <sys/comdef.h>
#include <wchar.h>

#define LOADER_NAME     L"YiffSys IPL.0"
#define LOADER_REVISION L"v0.0.1"
#define DOTS            L"........ "

/*
 * Write a formatted string to the console.
 *
 * @fmt:    Format specifier
 * @<...>:  Variadic arguments
 */
void
cons_printf (
    __in const wchar_t *fmt,
    ...
    );

#endif  /* !_BOOTLIB_H */
