/*
 * EFI library and interfaces.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _EFILIB_H
#define _EFILIB_H 1

#include <sys/status.h>
#include <sys/comdef.h>
#include <stdint.h>
#include <efi/efi.h>

/*
 * Translate an EFI status code to a YiffSys status code.
 *
 * @status:  Status code to convert
 */
status_t
efi_to_os_status (
    __in EFI_STATUS status
    );

/*
 * Initialize firmware global state.
 *
 * @handle:   Image handle passed by firmware
 * @systab:   System table interface passed by firmware
 *
 * Return value:
 *      Returns STATUS_SUCCESS if successful.
 *      Returns error code on failure.
 */
status_t
efi_init_firmware (
    __in EFI_HANDLE image_handle,
    __in EFI_SYSTEM_TABLE *systab
    );

#endif  /* !_EFILIB_H */
