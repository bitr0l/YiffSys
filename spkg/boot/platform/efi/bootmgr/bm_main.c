/*
 * Boot manager core.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <bootlib.h>

void
bm_main (
    void
    )
{
    status_t status;

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
}
