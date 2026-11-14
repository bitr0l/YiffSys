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

    list->head = NULL;
    list->tail = NULL;
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
    struct sio_xaccum *head;

    if (list == NULL || accum == NULL) {
        return STATUS_INVALID_PARAM;
    }

    /* Is this the first element? */
    if (list->head == NULL || list->tail == NULL) {
        list->head = accum;
        list->tail = accum;
        list->nr_entries = 1;
        return STATUS_SUCCESS;
    }

    /* Insert to back of list */
    head = list->head;
    head->next = accum;
    list->head = accum;
    ++list->nr_entries;
    return STATUS_SUCCESS;
}
