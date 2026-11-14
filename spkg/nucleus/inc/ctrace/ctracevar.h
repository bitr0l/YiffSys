/*
 * Internal CTrace variables and routines.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _CTRACE_CTRACEVAR_H
#define _CTRACE_CTRACEVAR_H 1

#include <sys/types.h>
#include <sys/comdef.h>
#include <io/sio.h>
#include <ctrace/object.h>

/*
 * CTrace drain callback
 *
 * See SIO `xaccum_drain_t'
 */
size_t
ctrace_drain_object (
    __in struct sio_xaccum_list *list,
    __in struct sio_xaccum *accum,
    __in void *data,
    __in size_t offset,
    __in size_t length,
    __in uint16_t flags
    );

#endif  /* !_CTRACE_CTRACEVAR_H */
