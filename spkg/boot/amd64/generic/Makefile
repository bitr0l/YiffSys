#
# AMD64 bootloader build script.
# Copyright (c) 2026, Apollo Telephone Laboratories, et al.
# Provided under the BSD-3 clause.
#

.PHONY: all
all: target platform

.PHONY: target
target:
	mkdir -p ../../target/machine
	rsync -avr ../../inc/$(CONFIG_ARCH)/$(CONFIG_CHIP)/*.h \
		../../target/machine/

.PHONY: platform
platform:
	make -C ../../platform/efi
