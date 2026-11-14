/*
 * Platform memory interface.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <sys/cdef.h>
#include <bootlib.h>
#include <efilib.h>

/*
 * Convert an EFI memory region kind into a YiffSys memory
 * region kind...
 */
static memkind_t
efi_memtype_conv (
    __in UINT32 efi_type
    )
{
    switch (efi_type) {
    case EfiConventionalMemory:
        return BOOT_MEMORY_USABLE;
    case EfiUnusableMemory:
        return BOOT_MEMORY_BAD;
    default:
        return BOOT_MEMORY_RESERVED;
    }
}

status_t
get_memory_map (
    __out struct memory_map *map
    )
{
    EFI_STATUS efi_status;
    EFI_MEMORY_DESCRIPTOR *efi_map;
    EFI_MEMORY_DESCRIPTOR *efi_map_cur;
    UINT32 efi_desc_ver;
    UINTN efi_desc_size;
    UINTN efi_map_size;
    uint64_t index;
    uint64_t map_size;
    uint64_t nr_entries;
    struct memory_descriptor *map_entries;
    struct memory_descriptor *map_cur;

    if (map == NULL) {
        return STATUS_INVALID_PARAM;
    }

    /*
     * Zero initialize resulting map.
     */

    map->entries = NULL;
    map->entry_count = 0;
    map->key = 0;

    /*
     * Zero initialize EFI map variables.
     */

    efi_map = NULL;
    efi_desc_size = 0;
    efi_desc_ver = 0;
    efi_map_size = 0;

    /*
     * Obtain the size of the memory map.
     */

    efi_status = g_bs->GetMemoryMap(
        &efi_map_size,
        efi_map,
        &map->key,
        &efi_desc_size,
        &efi_desc_ver
    );

    if (efi_status != EFI_BUFFER_TOO_SMALL) {
        cons_printf(DOTS L"fatal: could get memory map information\r\n");
        return efi_to_os_status(efi_status);
    }

    /*
     * Allocate memory for the EFI memory map.
     */

    efi_status = g_bs->AllocatePool(
        EfiLoaderData,
        efi_map_size,
        (void **)&efi_map
    );

    if (efi_status != EFI_SUCCESS) {
        cons_printf(DOTS L"fatal: could not allocate memory for map\r\n");
        return efi_to_os_status(efi_status);
    }

    /*
     * Allocate memory for our map.
     */

    nr_entries = (efi_map_size / efi_desc_size);
    map_size = nr_entries * sizeof(struct memory_descriptor);

    efi_status = g_bs->AllocatePool(
        EfiLoaderData,
        map_size,
        (void **)&map_entries
    );

    if (efi_status != EFI_SUCCESS) {
        cons_printf(DOTS L"fatal: could not allocate memory for internal map\r\n");
        g_bs->FreePool(efi_map);
        return efi_to_os_status(efi_status);
    }

    /*
     * Now actually obtain the platform memory map. Due to us allocating
     * memory beforehand which most likely altered the map, we'll need to
     * call GetMemoryMap() twice.
     */

    for (index = 0; index < 2; ++index) {
        efi_status = g_bs->GetMemoryMap(
            &efi_map_size,
            efi_map,
            &map->key,
            &efi_desc_size,
            &efi_desc_ver
        );

        if (efi_status == EFI_SUCCESS) {
            break;
        }
    }

    if (efi_status != EFI_SUCCESS) {
        cons_printf(DOTS L"fatal: unable to request memory map\r\n");
        g_bs->FreePool(efi_map);
        g_bs->FreePool(map_entries);
        return efi_to_os_status(efi_status);
    }

    /*
     * Populate our map.
     */

    efi_map_cur = efi_map;
    for (index = 0; index < nr_entries; ++index) {
        map_cur = &map_entries[index];
        map_cur->kind = efi_memtype_conv(efi_map_cur->Type);
        map_cur->pbase = efi_map_cur->PhysicalStart;
        map_cur->length = efi_map_cur->NumberOfPages * EFI_PAGE_SIZE;
        efi_map_cur = PTR_OFFSET(efi_map_cur, efi_desc_size);
    }

    map->entry_count = nr_entries;
    return STATUS_SUCCESS;
}
