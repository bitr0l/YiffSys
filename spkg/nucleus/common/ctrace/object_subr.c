/*
 * Object subroutines.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <ctrace/object.h>
#include <ctrace/ctracevar.h>
#include <aux/printf.h>
#include <string.h>
#include <stdarg.h>

status_t
ctrace_init_object (
    __in const char *name,
    __in uint16_t flags,
    __out struct ctrace_object *object
    )
{
    size_t name_length;
    status_t status;

    if (name == NULL || object == NULL) {
        return STATUS_INVALID_PARAM;
    }

    name_length = strlen(name);
    if (name_length >= CTRACE_OBJECT_NAMELEN - 1) {
        return STATUS_NAME_TOO_LONG;
    }

    memcpy(object->name, name, name_length);
    object->cookie = CTRACE_OBJECT_COOKIE;
    object->flags = flags;

    /* Initialize the mbuf */
    status = sio_xaccum_init(&object->mbuf, object);
    if (!OS_SUCCESS(status)) {
        return status;
    }

    /* Initialize the accumulator list */
    status = sio_xaccum_linit(&object->accum_list, ctrace_drain_object);
    if (!OS_SUCCESS(status)) {
        return status;
    }

    /* Insert the mbuf */
    status = sio_xaccum_insert(&object->accum_list, &object->mbuf);
    if (!OS_SUCCESS(status)) {
        return status;
    }

    return STATUS_SUCCESS;
}

ssize_t
ctrace_write (
    __in struct ctrace_object *object,
    __in const char *data,
    __in size_t length
    )
{
    size_t index;

    if (object == NULL || data == NULL) {
        return -1;
    }

    if (object->cookie != CTRACE_OBJECT_COOKIE) {
        return -1;
    }

    /*
     * Write the given bytes to the backing store, if we hit a newline, we are
     * to drain it.
     */
    for (index = 0; index < length; ++index) {
        if (sio_xaccum_write(&object->mbuf, &data[index], 1) == 0) {
            sio_xaccum_ldrain(
                &object->accum_list,
                object->flags,
                true
            );

            continue;
        }

        if (data[index] == '\n') {
            sio_xaccum_ldrain(
                &object->accum_list,
                object->flags,
                false
            );
        }
    }

    return length;
}

ssize_t
ctrace_dbg_write (
    __in struct ctrace_object *object,
    __in const char *fmt,
    ...
    )
{
    va_list ap;
    char buf[CTRACE_DBG_BUF_LEN];
    size_t length;

    if (object == NULL) {
        return -1;
    }

    if (fmt == NULL) {
        fmt = "(null)";
    }

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);

    length = strlen(buf);
    ctrace_write(object, buf, length);
    va_end(ap);
    return length;
}
