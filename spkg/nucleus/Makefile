#
# Nucleus build script.
# Copyright (c) 2026, Apollo Telephone Laboratories, et al.
# Provided under the BSD-3 clause.
#

.PHONY: all
all: kernel machine postbuild

.PHONY: kernel
kernel:
	cd common/kern; $(MAKE)

.PHONY: machine
machine:
	cd $(CONFIG_ARCH)/$(CONFIG_CHIP); $(MAKE)

.PHONY: postbuild
postbuild:
	rm -f $(shell find $(GLOBAL_ROOT)/sdk/crt/ -name "*.o")
