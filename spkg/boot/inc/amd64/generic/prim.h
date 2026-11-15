/*
 * AMD64 processor primitives.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_PRIM_H
#define _MACHINE_PRIM_H 1

#include <sys/cdef.h>

#define MD_INT_DISABLE() ASMV("cli")
#define MD_INT_ENABLE()  ASMV("sti")
#define MD_CORE_HALT()   ASMV("hlt")

#endif /* !_MACHINE_PRIM_H */
