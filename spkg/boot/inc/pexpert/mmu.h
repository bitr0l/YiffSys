/*
 * Platform expert MMU interface.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _PEXPERT_MMU_H
#define _PEXPERT_MMU_H 1

#include <sys/status.h>

/*
 * Initialize the platform MMU
 *
 * Return value:
 *      Returns STATUS_SUCCESS if successful.
 *      Returns error code on failure.
 */
status_t
px_mmu_init (
    void
    );

#endif  /* !_PEXPERT_MMU_H */
