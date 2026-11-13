/*
 * Platform device interface.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <bootlib.h>
#include <efilib.h>

status_t
set_watchdog_timer (
    __in uint64_t timeout,
    __in uint64_t wd_code,
    __in uint64_t data_size,
    __in wchar_t *wd_data __optional
    )
{
    EFI_STATUS efi_status;

    efi_status = g_bs->SetWatchdogTimer(
        timeout,
        wd_code,
        data_size,
        wd_data
    );

    return efi_to_os_status(efi_status);
}
