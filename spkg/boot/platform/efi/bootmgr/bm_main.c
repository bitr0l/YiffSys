/*
 * Boot manager core.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <pexpert/mmu.h>
#include <pexpert/prim.h>
#include <sys/cdef.h>
#include <bootlib.h>
#include <efilib.h>

/*
 * Load the kernel binary.
 *
 * @kernel:  Kernel file descriptor
 * @base:    Resulting image base is written here
 *
 * Return value:
 *     Returns STATUS_SUCCESS if successful.
 *     Returns error code on failure.
 */
static status_t
load_kernel (
    __in struct file_descriptor *kernel,
    __out EFI_PHYSICAL_ADDRESS *base
    )
{
    EFI_PHYSICAL_ADDRESS kernel_image;
    EFI_STATUS efi_status;
    status_t status;
    uint64_t kimage_size;

    if (kernel == NULL || base == NULL) {
        return STATUS_INVALID_PARAM;
    }

    /*
     * Load the kernel, it expects to sit at 1 MiB.
     */

    kimage_size = ALIGN_UP(kernel->size_bytes, EFI_PAGE_SIZE);
    kernel_image = (EFI_PHYSICAL_ADDRESS)0x100000;

    efi_status = g_bs->AllocatePages(
        AllocateAddress,
        EfiLoaderData,
        kimage_size / EFI_PAGE_SIZE,
        &kernel_image
    );

    if (efi_status != EFI_SUCCESS) {
        cons_printf(DOTS L"fatal: failed to reserve region at 1 MiB\r\n");
        return efi_to_os_status(efi_status);
    }

    /*
     * Fill the kernel image.
     */

    status = read_file(
        kernel,
        &kimage_size,
        (void *)kernel_image
    );

    if (!OS_SUCCESS(status)) {
        cons_printf(DOTS L"fatal: failed to read kernel binary\r\n");
        return status;
    }

    *base = kernel_image;
    return STATUS_SUCCESS;
}

/*
 * Used to hang the processor during fatal events in which firmware
 * boot services are no longer around.
 *
 * TODO: Log reason to a serial port
 */
static void
hang (
    __in const char *reason
    )
{
    (void)reason;

    for (;;) {
        PX_INT_DISABLE();
        PX_CORE_HALT();
    }
}

void
bm_main (
    void
    )
{
    EFI_FILE_HANDLE boot_volume;
    EFI_PHYSICAL_ADDRESS kbase;
    EFI_STATUS efi_status;
    status_t status;
    struct memory_map mem_map;
    struct file_descriptor kernel_desc;
    uintptr_t kentry;

    cons_printf(DOTS L"loader revision: %s\r\n", LOADER_REVISION);
    cons_printf(DOTS L"begin %s\r\n", LOADER_NAME);

    /*
     * Disable the platform watchdog timer. On most platforms it is set
     * up to fire after 5 minutes which will most certainly not pass before
     * we exit boot services. However, it is still good practice to do so...
     */

    cons_printf(DOTS L"pawing platform watchdog to NO EXPIRE\r\n");
    status = set_watchdog_timer(
        0,
        0,
        0,
        NULL
    );

    if (!OS_SUCCESS(status)) {
        cons_printf(DOTS L"error: failed to disable watchdog, continuing...\r\n");
    }

    /*
     * Obtain the boot volume.
     */

    status = get_boot_volume(&boot_volume);
    if (!OS_SUCCESS(status)) {
        cons_printf(DOTS L"error: failed to obtain boot volume\r\n");
        return;
    }

    status = open_file_path(
        boot_volume,
        KERNEL_PATH,
        &kernel_desc
    );

    if (!OS_SUCCESS(status)) {
        cons_printf(DOTS L"error: failed to locate %s\r\n", KERNEL_PATH);
        return;
    }

    /*
     * Load the kernel binary.
     */

    status = load_kernel(&kernel_desc, &kbase);
    if (!OS_SUCCESS(status)) {
        cons_printf(DOTS L"fatal: could not bootstrap kernel binary\r\n");
        return;
    }

    /*
     * Obtain the platform memory map.
     *
     * XXX: This must remain the last thing done
     */

    status = get_memory_map(&mem_map);
    if (!OS_SUCCESS(status)) {
        cons_printf(DOTS L"fatal: failed to obtain memory map\r\n");
        return;
    }

    efi_status = g_bs->ExitBootServices(
        g_image,
        mem_map.key
    );

    if (efi_status != EFI_SUCCESS) {
        cons_printf(DOTS L"fatal: failed to exit boot services\r\n");
        return;
    }

    /*
     * Initialize the platform memory management unit.
     */

    status = px_mmu_init((uint64_t)kbase, &kentry);
    if (!OS_SUCCESS(status)) {
        hang("MMU init failure\n");
    }

    ((void(*)(void))kentry)();
    __builtin_unreachable();
}
