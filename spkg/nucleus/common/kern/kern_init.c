/*
 * Kernel entry point.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <pexpert/serial.h>
#include <aux/printf.h>

/*
 * Print the boot banner.
 */
static void
boot_banner (
    void
    )
{
    printf("Copyright (c) 2026, Apollo Telephone Laboratories, et al.\n");
    printf("[nucleus] begin YiffSys IPL.1\n");
}

void
kmain (
    void
    )
{
    /* Initialize the platform serial driver */
    px_serial_init();

    /* Write the boot banner */
    boot_banner();
}
