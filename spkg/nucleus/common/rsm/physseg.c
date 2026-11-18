/*
 * Physical segment manager.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <sys/cdef.h>
#include <rsm/physseg.h>
#include <aux/ignis.h>
#include <ctrace/object.h>
#include <ctrace/registry.h>

/*
 * Safe memtype_tab indexing macro
 */
#define MEM_TYPESTR(TYPE)           \
    ((TYPE) >= NELEM(memtype_tab))  \
        ? "???"                     \
        : memtype_tab[(TYPE)]

/* Globals */
static struct ctrace_object *phys_ctrace = NULL;

/* Memory type to string table */
static const char *memtype_tab[] = {
    [BOOT_MEMORY_RESERVED] = "reserved",
    [BOOT_MEMORY_USABLE] = "usable",
    [BOOT_MEMORY_BAD] = "bad",
    [BOOT_MEMORY_LOADER] = "ignis",
    [BOOT_MEMORY_ACPI_NVS] = "acpi nvs"
};

/*
 * Initializes logging within the subsystem.
 *
 * TODO: Bugcheck on failure
 */
static void
init_logging (
    void
    )
{
    ctrace_root_alloc(&phys_ctrace);
    ctrace_init_object(
        "physseg",
        CTRACE_GCONS_SYNC,
        phys_ctrace
    );
}

static void
physseg_probe (
    void
    )
{
    extern struct ignis_protocol *g_proto;
    const char *typestr;
    struct ignis_memmap *mem_map;
    struct ignis_memory_descriptor *desc;
    uintptr_t start, end;
    uintptr_t prev_start = 0;
    size_t i;

    mem_map = g_proto->mem_map;
    for (i = 0; i < mem_map->entry_count; ++i) {
        desc = &mem_map->entries[i];

        /* Filter out entries we don't need */
        if (desc->pbase == 0 || desc->pbase == prev_start) {
            continue;
        }

        typestr = MEM_TYPESTR(desc->kind);
        start = desc->pbase;
        end = desc->pbase + desc->length;

        /* Log the type */
        ctrace_dbg_write(
            phys_ctrace,
            "[%p - %p) : %s\n",
            start,
            end,
            typestr
        );

        prev_start = start;
    }
}

void
mm_physseg_init (
    void
    )
{
    /* Initialize log buffer */
    init_logging();

    /* Probe physical memory */
    physseg_probe();
}
