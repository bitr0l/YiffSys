/*
 * CTrace registry.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _CTRACE_REGISTRY_H
#define _CTRACE_REGISTRY_H 1

#include <sys/comdef.h>
#include <sys/status.h>
#include <ctrace/object.h>

/*
 * Allocate a CTrace object from the root domain.
 *
 * @object:  Resulting object is written here
 *
 * Return value:
 *      Returns STATUS_SUCCESS if successful.
 *      Returns an error code on failure.
 */
status_t
ctrace_root_alloc (
    __out struct ctrace_object **object
    );

/*
 * Resolve an object from the root domain.
 *
 * @name:   Name to resolve.
 * @object: Resulting object is written here
 */
status_t
ctrace_root_resolve (
    __in const char *name,
    __out struct ctrace_object **object
    );

#endif /* !_CTRACE_REGISTRY_H */
