/*
 * Platform expert MMU interface.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _PEXPERT_MMU_H
#define _PEXPERT_MMU_H 1

#include <sys/comdef.h>
#include <sys/status.h>
#include <stdint.h>

/* Higher half kernel base address */
#define KERNEL_VBASE 0xFFFFFFFF80000000

/*
 * Initialize the platform MMU
 *
 * @kimage_base: Kernel image base address
 * @kimage_entry: Kernel image entry is written here
 *
 * Return value:
 *      Returns STATUS_SUCCESS if successful.
 *      Returns error code on failure.
 */
status_t
px_mmu_init (
    __in uint64_t kimage_base,
    __out uint64_t *kimage_entry
    );

#endif  /* !_PEXPERT_MMU_H */
