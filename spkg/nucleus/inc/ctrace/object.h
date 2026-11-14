/*
 * CTrace object definitions.
 * Copyright (c) 2026, Apollo Telephone Laboratories, et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _CTRACE_OBJECT_H
#define _CTRACE_OBJECT_H 1

#include <sys/status.h>
#include <sys/cdef.h>
#include <sys/types.h>
#include <io/sio.h>

/* Maximum name length of a CTrace object */
#define CTRACE_OBJECT_NAMELEN 256

/* Object cookie for verification */
#define CTRACE_OBJECT_COOKIE 0xCA7F00D

/* Object specific flags */
#define CTRACE_GCONS_SYNC    BIT(0)

/*
 * Represents a CTrace object.
 *
 * @cookie:         Cookie to verify object
 * @name:           Name of CTrace object
 * @accum_list:     Single entry accumulator list
 * @mbuf:           Message buffer
 * @flags:          Object specific flags
 */
struct ctrace_object {
    uint32_t cookie;
    char name[CTRACE_OBJECT_NAMELEN];
    struct sio_xaccum_list accum_list;
    struct sio_xaccum mbuf;
    uint16_t flags;
};

/*
 * Initialize a CTrace object.
 *
 * @name:   Name of object to initialize
 * @flags:  Object specific flags
 * @object: Resulting object is written here
 *
 * Return value:
 *      Returns STATUS_SUCCESS if successful.
 *      Returns error code on failure.
 */
status_t
ctrace_init_object (
    __in const char *name,
    __in uint16_t flags,
    __out struct ctrace_object *object
    );

/*
 * Write to a CTrace object
 *
 * @object:  Object to write to
 * @data:    Data to write
 * @length:  Length of data to write
 *
 * Return value:
 *      Returns STATUS_SUCCESS if successful.
 *      Returns error code on failure.
 */
ssize_t
ctrace_write (
    __in struct ctrace_object *object,
    __in const char *data,
    __in size_t length
    );

#endif  /* !_CTRACE_OBJECT_H */
