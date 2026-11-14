/*
 * System I/O framework.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _IO_SIO_H
#define _IO_SIO_H 1

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
 * @next:  Next accumulator
 */
struct sio_xaccum {
    uint8_t chunk[SIO_X_ACCUM_WIDTH];
    size_t enq;
    size_t deq;
    void *data;
    struct sio_xaccum *next;
};

/*
 * List of fixed width accumulators.
 *
 * @head:           Head of the accumulator list
 * @tail:           Tail of the accumulator list
 * @nr_entries:     Number of accumulators
 * @drain:          Drain callback
 */
struct sio_xaccum_list {
    struct sio_xaccum *head;
    struct sio_xaccum *tail;
    size_t nr_entries;
    xaccum_drain_t drain;
};

#endif  /* !_IO_SIO_H */
