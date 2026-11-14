/*
 * File I/O interface.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <bootlib.h>

status_t
get_boot_volume (
    __out EFI_FILE_HANDLE *volume
    )
{
    EFI_GUID lip_guid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    EFI_GUID fs_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_LOADED_IMAGE *lip = NULL;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *io_volume;
    EFI_STATUS efi_status;

    if (volume == NULL) {
        return STATUS_INVALID_PARAM;
    }

    /*
     * Obtain the loaded image protocol interface.
     */

    efi_status = g_bs->HandleProtocol(
        g_image,
        &lip_guid,
        (void **)&lip
    );

    if (efi_status != EFI_SUCCESS) {
        return efi_to_os_status(efi_status);
    }

    /*
     * Obtain the boot volume handle.
     */

    efi_status = g_bs->HandleProtocol(
        &lip->DeviceHandle,
        &fs_guid,
        (void *)&io_volume
    );

    if (efi_status != EFI_SUCCESS) {
        return efi_to_os_status(efi_status);
    }

    efi_status = io_volume->OpenVolume(
        io_volume,
        (EFI_FILE_PROTOCOL **)volume
    );

    return efi_to_os_status(efi_status);
}
