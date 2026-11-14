/*
 * System I/O accumulator.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <io/sio.h>

status_t
sio_xaccum_linit (
    __in struct sio_xaccum_list *list,
    __in xaccum_drain_t drain_cb
    )
{
    if (list == NULL) {
        return STATUS_INVALID_PARAM;
    }

    TAILQ_INIT(&list->head);
    list->nr_entries = 0;
    list->drain = drain_cb;
    return STATUS_SUCCESS;
}

/*
 * TODO: This probably needs some kind of locking.
 */
status_t
sio_xaccum_insert (
    __in struct sio_xaccum_list *list,
    __in struct sio_xaccum *accum
    )
{
    if (list == NULL || accum == NULL) {
        return STATUS_INVALID_PARAM;
    }

    TAILQ_INSERT_TAIL(&list->head, accum, link);
    ++list->nr_entries;
    return STATUS_SUCCESS;
}
