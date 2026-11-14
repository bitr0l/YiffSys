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
 */
struct sio_xaccum_list {
    struct sio_xaccum *head;
    struct sio_xaccum *tail;
    size_t nr_entries;
};

#endif  /* !_IO_SIO_H */
