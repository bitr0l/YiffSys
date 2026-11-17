#!/bin/bash
#
# IGNIS bootloader dep script.
# Copyright (c) 2026, Apollo Telephone Laboratories, et al.
# Provided under the BSD-3 clause.
#

if [ ! -d stand ]
then
    git clone https://github.com/bitr0l/Ignis/ \
        --depth=1                              \
        stand
fi
