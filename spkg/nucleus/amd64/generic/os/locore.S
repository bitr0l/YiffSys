/*
 * Kernel processor entry and low level commons.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

    .section .ipl, "ax", @progbits
    .globl _start
_start:
    /* Set our stack */
    xor %rbp, %rbp
    lea stack_top(%rip), %rsp

    mfence
1:  cli
    hlt
    jmp 1b

    .section .bss
    .align 16
stack_base:
    .skip 8192
stack_top:
