/*
 * Kernel processor entry and low level commons.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

    .section .ipl, "ax", @progbits
    .globl _start
    .extern __bss_start
    .extern __bss_end
_start:
    /* Compute size of .bss */
    lea __bss_start(%rip), %rdi
    lea __bss_end(%rip), %rsi
    sub %rdi, %rsi

    /* Zero .bss */
    mov %rsi, %rcx
    xor %al, %al
    lea __bss_start(%rip), %rdi
    cld
    rep stosb

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
