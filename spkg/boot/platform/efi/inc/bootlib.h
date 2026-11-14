/*
 * Boot library and interfaces.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _BOOTLIB_H
#define _BOOTLIB_H 1

#include <sys/status.h>
#include <sys/comdef.h>
#include <efilib.h>
#include <wchar.h>
#include <stdint.h>

#define LOADER_NAME     L"YiffSys IPL.0"
#define LOADER_REVISION L"v0.0.1"
#define DOTS            L"........ "
#define KERNEL_PATH     L"yiff.sys"

/*
 * Valid memory descriptor kinds.
 */
#define BOOT_MEMORY_RESERVED 0x00000000UL   /* Reserved by firmware */
#define BOOT_MEMORY_USABLE   0x00000001UL   /* Usable memory */
#define BOOT_MEMORY_BAD      0x00000002UL   /* Unusable memory */

typedef uint32_t memkind_t;

/*
 * Represents an entry within the platform memory map.
 *
 * @kind:       Memory region kind
 * @pbase:      Physical base address of region
 * @length:     Length of region in bytes
 */
struct memory_descriptor {
    memkind_t kind;
    uint64_t pbase;
    uint64_t length;
};

/*
 * YiffSys internal representation of platform memory map.
 *
 * @entries:        Platform memory map entries
 * @entry_count:    Number of entries in map
 * @key:            Platform memory map key
 */
struct memory_map {
    struct memory_descriptor *entries;
    uint64_t entry_count;
    uint64_t key;
};

/*
 * Represents an opened file.
 *
 * @handle:         EFI file handle interface
 * @size_bytes:     Size of file in bytes
 */
struct file_descriptor {
    EFI_FILE_HANDLE handle;
    uint64_t size_bytes;
};

/*
 * Read the contents of a file into the specified buffer.
 *
 * @descriptor:  Descriptor of file to read
 * @buf_size:    Number of bytes to read
 * @buffer:      Destination buffer.
 *
 * Return value:
 *     Returns STATUS_SUCCESS if successful.
 *     Returns error code on failure.
 */
status_t
read_file (
    __in struct file_descriptor *descriptor,
    __inout uint64_t *buf_size,
    __out void *buffer
    );

/*
 * Open a file by path.
 *
 * @volume:     Volume file resides on.
 * @file_path:  Path of file to open.
 * @descriptor: Resulting descriptor is written here.
 *
 * Return value:
 *     Returns STATUS_SUCCESS if successful.
 *     Returns error code on failure.
 */
status_t
open_file_path (
    __in EFI_FILE_HANDLE volume,
    __in wchar_t *file_path,
    __out struct file_descriptor *descriptor
    );

/*
 * Obtain the volume in which we are booting from.
 *
 * @volume: Result is written here
 *
 * Return value:
 *     Returns STATUS_SUCCESS if successful.
 *     Returns error code on failure.
 */
status_t
get_boot_volume (
    __out EFI_FILE_HANDLE *volume
    );

/*
 * Obtain the platform memory map.
 *
 * @map: Result is written here
 *
 * Return value:
 *     Returns STATUS_SUCCESS if successful.
 *     Returns error code on failure.
 */
status_t
get_memory_map (
    __out struct memory_map *map
    );

/*
 * Configure the platform watchdog timer.
 *
 * @timeout:    Timeout in seconds
 * @wd_code:    Watchdog code to log upon event
 * @data_size:  Size of optional watchdog data
 * @wd_data:    Optional watchdog data
 *
 * Return value:
 *      Returns STATUS_SUCCESS if successful.
 *      Returns error code on failure.
 */
status_t
set_watchdog_timer (
    __in uint64_t timeout,
    __in uint64_t wd_code,
    __in uint64_t data_size,
    __in wchar_t *wd_data __optional
    );

/*
 * Write a formatted string to the console.
 *
 * @fmt:    Format specifier
 * @<...>:  Variadic arguments
 */
void
cons_printf (
    __in const wchar_t *fmt,
    ...
    );

/*
 * Boot manager entry point.
 */
void
bm_main (
    void
    );

#endif  /* !_BOOTLIB_H */
