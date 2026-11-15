/*
 * Platform expert primitive wrappers.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _PEXPERT_PRIM_H
#define _PEXPERT_PRIM_H 1

#include <machine/prim.h>

#define PX_INT_DISABLE MD_INT_DISABLE   /* Disable interrupts */
#define PX_INT_ENABLE  MD_INT_ENABLE    /* Enable interrupts */
#define PX_CORE_HALT   MD_CORE_HALT     /* Halt processor */

#endif  /* !_PEXPERT_PRIM_H */
