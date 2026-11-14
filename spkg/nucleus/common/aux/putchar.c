/*
 * Kernel putchar bridge.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <pexpert/serial.h>

void
_putchar (
    __in char c
    )
{
    if (c == '\n') {
        px_serial_write(SERIAL_PORT_COM0, "\r\n", 2);
        return;
    }

    px_serial_write(SERIAL_PORT_COM0, &c, 1);
}
