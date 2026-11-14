/*
 * System I/O framework.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H 1

#include <stdint.h>
#include <stddef.h>

#if __SIZEOF_SIZE_T__ == 8
typedef int64_t ssize_t;
#else
typedef int32_t ssize_t;
#endif

#endif  /* !_SYS_TYPES_H */
