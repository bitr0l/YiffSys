/*
 * EFI state keeping.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <efilib.h>

/* Globals */
EFI_HANDLE g_image;
EFI_SYSTEM_TABLE *g_st;
EFI_BOOT_SERVICES *g_bs;
EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *g_cons;

status_t
efi_init_firmware (
    __in EFI_HANDLE image_handle,
    __in EFI_SYSTEM_TABLE *systab
    )
{
    if (image_handle == NULL || systab == NULL) {
        return STATUS_INVALID_PARAM;
    }

    g_image = image_handle;
    g_st = systab;
    g_bs = g_st->BootServices;
    g_cons = g_st->ConOut;
    return STATUS_SUCCESS;
}
