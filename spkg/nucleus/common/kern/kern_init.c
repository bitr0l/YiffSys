/*
 * Kernel entry point.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <pexpert/serial.h>
#include <aux/printf.h>
#include <aux/ignis.h>
#include <ctrace/object.h>
#include <ctrace/registry.h>

/* Globals */
static struct ctrace_object *nuc_ctrace = NULL;

static void
init_logbuf (
    void
    )
{
    /*
     * Allocations will not fail here as it is the first object
     * to be allocated.
     */
    ctrace_root_alloc(&nuc_ctrace);
    ctrace_init_object(
        "nucleus",
        CTRACE_GCONS_SYNC,
        nuc_ctrace
    );
}

/*
 * Print the boot banner.
 */
static void
boot_banner (
    void
    )
{
    printf("Copyright (c) 2026, Apollo Telephone Laboratories, et al.\n");
    ctrace_dbg_write(nuc_ctrace, "begin YiffSys IPL/1\n");
}

void
kmain (
    __in struct ignis_protocol *protocol
    )
{
    /* Initialize the platform serial driver */
    px_serial_init();

    /* Initialize the nucleus log buffer */
    init_logbuf();

    /* Write the boot banner */
    boot_banner();
}
