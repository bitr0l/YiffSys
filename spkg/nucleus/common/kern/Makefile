#
# Kernel MI build script.
# Copyright (c) 2026, Apollo Telephone Laboratories, et al.
# Provided under the BSD-3 clause.
#

include ../../../mk/common.mk
include ../../../mk/sys.mk

CFILES = $(shell find . -name "*.c")
CFILES += $(shell find ../xt -name "*.c")
CFILES += $(shell find ../aux -name "*.c")
CFILES += $(shell find ../io -name "*.c")
CFILES += $(shell find ../ctrace -name "*.c")
CFILES += $(shell find $(GLOBAL_ROOT)/sdk/crt -name "*.c")
OFILES = $(CFILES:.c=.o)
DFILES = $(CFILES:.c=.d)

CFLAGS =								\
	$(COMMON_CFLAGS)					\
	-DPRINTF_DISABLE_SUPPORT_PTRDIFF_T	\
	-DPRINTF_DISABLE_SUPPORT_FLOAT

.PHONY: all
all: $(OFILES)

-include $(DFILES)
%.o: %.c
	$(PROMPT) "CC" $<
	$(CC) -c $(CFLAGS) $< -o $@
