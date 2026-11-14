/*
 * CTrace registry.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <ctrace/registry.h>
#include <ctrace/ctracevar.h>
#include <string.h>

/* Globals */
static struct ctrace_xdomain root_domain = {0};

status_t
ctrace_root_alloc (
    __out struct ctrace_object **object
    )
{
    if (object == NULL) {
        return STATUS_INVALID_PARAM;
    }

    if (root_domain.nr_entries >= CTRACE_XDOMAIN_ENTRIES) {
        return STATUS_OUT_OF_RESOURCES;
    }

    *object = &root_domain.storage[root_domain.nr_entries++];
    return STATUS_SUCCESS;
}

status_t
ctrace_root_resolve (
    __in const char *name,
    __out struct ctrace_object **object
    )
{
    struct ctrace_object *object_cur;
    size_t index, name_len;

    if (name == NULL || object == NULL) {
        return STATUS_INVALID_PARAM;
    }

    name_len = strlen(name);
    if (name_len >= CTRACE_OBJECT_NAMELEN) {
        return STATUS_NAME_TOO_LONG;
    }

    for (index = 0; index < CTRACE_XDOMAIN_ENTRIES; ++index) {
        object_cur = &root_domain.storage[index];

        /* Must have a valid cookie */
        if (object_cur->cookie != CTRACE_OBJECT_COOKIE) {
            continue;
        }

        /* Quick filter */
        if (object_cur->name[0] != *name) {
            continue;
        }

        /* Does it not match? */
        if (memcmp(object_cur->name, name, name_len) != 0) {
            continue;
        }

        *object = object_cur;
        return STATUS_SUCCESS;
    }

    return STATUS_NOT_FOUND;
}
