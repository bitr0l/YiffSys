/*
 * Physical segment manager.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _RSM_PHYSSEG_H
#define _RSM_PHYSSEG_H 1

#include <sys/types.h>

/*
 * Initialize the physical segment manager
 */
void
mm_physseg_init (
    void
    );

#endif  /* !_RSM_PHYSSEG_H */
