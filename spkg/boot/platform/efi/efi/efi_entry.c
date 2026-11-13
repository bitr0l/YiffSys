/*
 * EFI platform entry point.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <sys/comdef.h>
#include <efilib.h>
#include <bootlib.h>

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
    status_t status;

    /*
     * Initialize global firmware state.
     */

    status = efi_init_firmware(image_handle, systab);
    if (!OS_SUCCESS(status)) {
        return EFI_INVALID_PARAMETER;
    }

    /*
     * Reset the console, potential failures are not fatal.
     */

    g_cons->Reset(
        g_cons,
        FALSE
    );

    /*
     * Boot manager handoff.
     */

    bm_main();

    /*
     * Abort if we reach this point.
     */

    cons_printf(DOTS "IPL ABORTED\r\n");
    g_bs->Stall(2000000);
    return EFI_ABORTED;
}
