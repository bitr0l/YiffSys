/*
 * EFI platform entry point.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <sys/comdef.h>
#include <efi/efi.h>

/*
 * EFI platform entry point, firmware passes control to us here...
 *
 * @image_handle:   Image handled passed to us by firmware.
 * @systab:         System table interface passed to us by firmware.
 *
 * Return value:
 *      Does not return on success, aborts on failure.
 */
EFIAPI
EFI_STATUS
efi_main (
    __in EFI_HANDLE image_handle,
    __in EFI_SYSTEM_TABLE *systab
    )
{
    /* Abort if we reach this point */
    return EFI_ABORTED;
}
