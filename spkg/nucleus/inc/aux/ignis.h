/*
 * IGNIS boot protocol.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _AUX_IGNIS_H
#define _AUX_IGNIS_H 1

#include <sys/types.h>

/*
 * Represents the IGNIS boot protocol.
 *
 * @direct_map:  Physical direct map base
 */
struct ignis_protocol {
    uint64_t direct_map;
};

#endif  /* !_AUX_IGNIS_H */
