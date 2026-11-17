/*
 * IGNIS boot protocol.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _AUX_IGNIS_H
#define _AUX_IGNIS_H 1

#include <sys/types.h>

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
struct ignis_memory_descriptor {
    memkind_t kind;
    uint64_t pbase;
    uint64_t length;
};

/*
 * Represents the platform memory map.
 *
 * @entries:        Entries within map
 * @entry_count:    Number of entries in memory map
 */
struct ignis_memmap {
    struct ignis_memory_descriptor *entries;
    uint64_t entry_count;
};

/*
 * Represents the IGNIS boot protocol.
 *
 * @direct_map:  Physical direct map base
 * @mem_map:     Platform memory map
 */
struct ignis_protocol {
    uint64_t direct_map;
    struct ignis_memmap *mem_map;
};

#endif  /* !_AUX_IGNIS_H */
