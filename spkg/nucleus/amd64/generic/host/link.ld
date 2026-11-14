/*
 * Kernel linker script.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

ENTRY(_start)

SECTIONS {
    . = 1M;

    .text : ALIGN(4K) {
        *(.ipl)
        *(.text .text.*)
    }

    . += CONSTANT(MAXPAGESIZE);

    .data : ALIGN(4K) {
        *(.data .data.*)
    }

    . += CONSTANT(MAXPAGESIZE);

    .rodata : ALIGN(4K) {
        *(.rodata .rodata.*)
    }

    . += CONSTANT(MAXPAGESIZE);

    .bss : ALIGN(4K) {
        *(COMMON)
        *(.bss .bss.*)
    }
}
