/*
 * AMD64 UART driver.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

    .text
    .globl px_serial_init
px_serial_init:
    /*
     * This is mostly used on emulators and most PCs nowadays lack a serial
     * port to use, therefore this a stub.
     */
    retq

    .globl px_serial_write
px_serial_write:
    pushfq
    cld
    mov %rdx, %rcx
    mov $0x3F8, %dx
    rep outsb
    popfq
    retq
