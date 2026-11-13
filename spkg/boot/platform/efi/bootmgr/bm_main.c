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
    cons_printf(DOTS L"loader revision: %s\r\n", LOADER_REVISION);
    cons_printf(DOTS L"begin %s\r\n", LOADER_NAME);
}
