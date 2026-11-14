/*
 * System I/O framework.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _IO_SIO_H
#define _IO_SIO_H 1

#include <sys/queue.h>
#include <sys/status.h>
#include <stdint.h>
#include <stddef.h>

/* Max width of sio_xaccum */
#define SIO_X_ACCUM_WIDTH 0x2000

/* Forward declarations */
struct sio_xaccum;
struct sio_xaccum_list;

/*
 * Fixed width accumulator drain callback
 *
 * @list:   Accumulator list being drained
 * @accum:  Current accumulator being drained
 * @offset: Offset being drained
 * @length: Length of data being drained
 * @flags:  Backend specific flags
 */
typedef size_t(*xaccum_drain_t) (
    __in struct sio_xaccum_list *list,
    __in struct sio_xaccum *accum,
    __in size_t offset,
    __in size_t length,
    __in uint16_t flags
);

/*
 * Fixed width SIO accumulator.
 *
 * @chunk: Fixed width accumulator chunk
 * @enq:   Chunk enqueue pointer
 * @deq:   Chunk dequeue pointer
 * @data:  Backend specific data
 * @link:  Link chain
 */
struct sio_xaccum {
    uint8_t chunk[SIO_X_ACCUM_WIDTH];
    size_t enq;
    size_t deq;
    void *data;
    TAILQ_ENTRY(sio_xaccum) link;
};

/*
 * List of fixed width accumulators.
 *
 * @head:           Head of the accumulator list
 * @nr_entries:     Number of accumulators
 * @drain:          Drain callback
 */
struct sio_xaccum_list {
    TAILQ_HEAD(, sio_xaccum) head;
    size_t nr_entries;
    xaccum_drain_t drain;
};

/*
 * Initialize a fixed width accumulator list.
 *
 * @list:       List to initialize
 * @drain_cb:   Drain callback to initialize
 *
 * Return value:
 *      Returns STATUS_SUCCESS if successful.
 *      Returns error code on failure.
 */
status_t
sio_xaccum_linit (
    __in struct sio_xaccum_list *list,
    __in xaccum_drain_t drain_cb
    );

/*
 * Initialize an accumulator
 *
 * @accum:  Accumulator to initialize
 * @data:   Backend specific data
 *
 * Return value:
 *      Returns STATUS_SUCCESS if successful.
 *      Returns error code on failure.
 */
status_t
sio_xaccum_init (
    __in struct sio_xaccum *accum,
    __in void *data __optional
    );

/*
 * Insert a fixed width accumulator into an accumulator
 * list.
 *
 * @list:   List to append to
 * @accum:  Accumulator to append
 *
 * Return value:
 *      Returns STATUS_SUCCESS if successful.
 *      Returns error code on failure.
 */
status_t
sio_xaccum_insert (
    __in struct sio_xaccum_list *list,
    __in struct sio_xaccum *accum
    );

/*
 * Write to an accumulator buffer.
 *
 * @accum:  Accumulator to write to
 * @data:   Data to write
 * @length: Length of data to write
 *
 * Return value:
 *      Returns the number of bytes written on success.
 *      Returns a less than zero value on failure.
 */
ssize_t
sio_xaccum_write (
    __in struct sio_xaccum *accum,
    __in const char *data,
    __in size_t length
    );

#endif  /* !_IO_SIO_H */
