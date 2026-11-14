/*
 * System I/O accumulator.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#include <io/sio.h>
#include <string.h>

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

status_t
sio_xaccum_init (
    __in struct sio_xaccum *accum,
    __in void *data __optional
    )
{
    if (accum == NULL) {
        return STATUS_INVALID_PARAM;
    }

    accum->enq = 0;
    accum->deq = 0;
    accum->data = data;
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

ssize_t
sio_xaccum_write (
    __in struct sio_xaccum *accum,
    __in const char *data,
    __in size_t length
    )
{
    size_t trunc_length = length;

    if (accum == NULL || data == NULL) {
        return -1;
    }

    if ((length + accum->enq) > SIO_X_ACCUM_WIDTH) {
        trunc_length = (length + accum->enq) - SIO_X_ACCUM_WIDTH;
    }

    memcpy(&accum->chunk[accum->enq], data, trunc_length);
    accum->enq += trunc_length;
    return trunc_length;
}
