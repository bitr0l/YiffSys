/*
 * AMD64 MMU interface.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <pexpert/mmu.h>
#include <machine/mmu.h>
#include <string.h>

ALIGN(4096) static uint64_t pml4[512];
ALIGN(4096) static uint64_t pdpt_low[512];

uint64_t
mmu_read_cr3 (
    void
    )
{
    uint64_t cr3;

    ASMV(
        "mov %%cr3, %0"
        : "=r" (cr3)
        :
        : "memory"
    );

    return cr3;
}

void
mmu_write_cr3 (
    __in uint64_t value
    )
{
    ASMV(
        "mov %0, %%cr3"
        :
        : "r" (value)
        : "memory"
    );
}

status_t
px_mmu_init (
    void
    )
{
    /* Zero initialize page tables */
    memset(pml4, 0, sizeof(pml4));
    memset(pdpt_low, 0, sizeof(pdpt_low));

    /* Point PML4[0] to PDPT low */
    pml4[0] = (uint64_t)pdpt_low;
    pml4[0] |= PTE_P | PTE_RW;

    /* Setup PDPT low identity mappings */
    pdpt_low[0] = PTE_P | PTE_RW | PTE_PS;
    pdpt_low[1] = 0x40000000 | PTE_P | PTE_RW | PTE_PS;
    pdpt_low[2] = 0x80000000 | PTE_P | PTE_RW | PTE_PS;
    pdpt_low[3] = 0xC0000000 | PTE_P | PTE_RW | PTE_PS;

    /* Write CR3 back */
    mmu_write_cr3((uintptr_t)pml4);
    return STATUS_SUCCESS;
}
