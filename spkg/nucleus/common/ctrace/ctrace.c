/*
 * Object subroutines.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <ctrace/ctracevar.h>
#include <ctrace/object.h>
#include <aux/printf.h>

size_t
ctrace_drain_object (
    __in struct sio_xaccum_list *list,
    __in struct sio_xaccum *accum,
    __in void *data,
    __in size_t offset,
    __in size_t length,
    __in uint16_t flags
    )
{
    struct ctrace_object *object;
    size_t index;
    char *byte_data = (char *)data;

    if (list == NULL || accum == NULL) {
        return 0;
    }

    if (data == NULL) {
        return 0;
    }

    /* There must be a backend object */
    if ((object = accum->data) == NULL) {
        return 0;
    }

    /* The cookie must match */
    if (object->cookie != CTRACE_OBJECT_COOKIE) {
        return 0;
    }

    if (ISSET(flags, CTRACE_GCONS_SYNC)) {
        printf("[%s] : ", object->name);
        for (index = 0; index < length; ++index) {
            printf("%c", byte_data[index]);
        }
    }

    return length;
}
