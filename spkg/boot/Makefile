#
# Bootloader build script.
# Copyright (c) 2026, Apollo Telephone Laboratories, et al.
# Provided under the BSD-3 clause.
#

.PHONY: all
all:
	./host/deps.sh
	cd stand; ./build.sh
	cp stand/out/BOOTX64.EFI $(GLOBAL_ROOT)/../out
