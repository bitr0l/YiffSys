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
        lip->DeviceHandle,
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

status_t
open_file_path (
    __in EFI_FILE_HANDLE volume,
    __in wchar_t *file_path,
    __out struct file_descriptor *descriptor
    )
{
    EFI_STATUS efi_status;

    if (volume == NULL || file_path == NULL) {
        return STATUS_INVALID_PARAM;
    }

    if (descriptor == NULL) {
        return STATUS_INVALID_PARAM;
    }

    /*
     * Open the file by path.
     */

    efi_status = volume->Open(
        volume,
        &descriptor->handle,
        file_path,
        EFI_FILE_MODE_READ,
        EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM
    );

    if (efi_status != EFI_SUCCESS) {
        return efi_to_os_status(efi_status);
    }

    /*
     * Obtain the file size.
     */

    efi_status = descriptor->handle->SetPosition(
        descriptor->handle,
        0xFFFFFFFFFFFFFFFF
    );

    if (efi_status != EFI_SUCCESS) {
        return efi_to_os_status(efi_status);
    }

    efi_status = descriptor->handle->GetPosition(
        descriptor->handle,
        &descriptor->size_bytes
    );

    if (efi_status != EFI_SUCCESS) {
        descriptor->handle->SetPosition(descriptor->handle, 0);
        return efi_to_os_status(efi_status);
    }

    efi_status = descriptor->handle->SetPosition(
        descriptor->handle,
        0
    );

    return efi_to_os_status(efi_status);
}

status_t
read_file (
    __in struct file_descriptor *descriptor,
    __inout uint64_t *buf_size,
    __out void *buffer
    )
{
    EFI_STATUS efi_status;

    if (descriptor == NULL || buf_size == NULL) {
        return STATUS_INVALID_PARAM;
    }

    if (buffer == NULL) {
        return STATUS_INVALID_PARAM;
    }

    efi_status = descriptor->handle->Read(
        descriptor->handle,
        buf_size,
        buffer
    );

    return efi_to_os_status(efi_status);
}
