/*
 * Boot library and interfaces.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _BOOTLIB_H
#define _BOOTLIB_H 1

#include <sys/status.h>
#include <sys/comdef.h>
#include <wchar.h>
#include <stdint.h>

#define LOADER_NAME     L"YiffSys IPL.0"
#define LOADER_REVISION L"v0.0.1"
#define DOTS            L"........ "

/*
 * Configure the platform watchdog timer.
 *
 * @timeout:    Timeout in seconds
 * @wd_code:    Watchdog code to log upon event
 * @data_size:  Size of optional watchdog data
 * @wd_data:    Optional watchdog data
 *
 * Return value:
 *      Returns STATUS_SUCCESS if successful.
 *      Returns error code on failure.
 */
status_t
set_watchdog_timer (
    __in uint64_t timeout,
    __in uint64_t wd_code,
    __in uint64_t data_size,
    __in wchar_t *wd_data __optional
    );

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

/*
 * Boot manager entry point.
 */
void
bm_main (
    void
    );

#endif  /* !_BOOTLIB_H */
