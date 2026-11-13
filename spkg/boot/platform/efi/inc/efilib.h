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

#endif  /* !_EFILIB_H */
