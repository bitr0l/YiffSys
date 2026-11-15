/*
 * AMD64 MMU interface.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_MMU_H
#define _MACHINE_MMU_H 1

#include <sys/comdef.h>
#include <sys/cdef.h>
#include <stdint.h>

/*
 * Page-Table Entry (PTE) flags
 */

#define PTE_ADDR_MASK   0x000FFFFFFFFFF000
#define PTE_P           BIT(0)        /* Present */
#define PTE_RW          BIT(1)        /* Writable */
#define PTE_US          BIT(2)        /* User r/w allowed */
#define PTE_PWT         BIT(3)        /* Page-level write-through */
#define PTE_PCD         BIT(4)        /* Page-level cache disable */
#define PTE_ACC         BIT(5)        /* Accessed */
#define PTE_DIRTY       BIT(6)        /* Dirty (written-to page) */
#define PTE_PS          BIT(7)        /* Page size */
#define PTE_GLOBAL      BIT(8)        /* Global; sticky */
#define PTE_NX          BIT(63)       /* Execute-disable */

/*
 * Read the contents of the CR3 register.
 *
 * Return value:
 *      Returns the value within CR3.
 */
uint64_t
mmu_read_cr3 (
    void
    );

/*
 * Write the contents of the CR3 register.
 *
 * @value:  Value to write into CR3
 */
void
mmu_write_cr3 (
    __in uint64_t value
    );

#endif  /* !_MACHINE_MMU_H */
