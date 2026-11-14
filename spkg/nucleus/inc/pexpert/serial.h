/*
 * Platform expert serial interface.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _PEXPERT_SERIAL_H
#define _PEXPERT_SERIAL_H 1

#include <sys/comdef.h>
#include <stdint.h>
#include <stddef.h>

/*
 * Represents valid serial ports.
 */
typedef enum {
    SERIAL_PORT_COM0
} serial_port_t;

/*
 * Initialize the platform serial driver.
 */
void
px_serial_init (
    void
    );

/*
 * Write to a specific serial port.
 *
 * @port: Port to write to
 * @s:    Data to write
 * @len:  Number of bytes to write
 */
void
px_serial_write (
    __in serial_port_t port,
    __in const char *s,
    __in size_t len
    );

#endif /* !_PEXPERT_SERIAL_H */
