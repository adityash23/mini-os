#!/bin/bash

set -xue # debugging, undefined, exit

QEMU=/usr/bin/qemu-system-riscv32 # path found by running 'which qemu-system-riscv32'

# to make sure this works, install opensbi within the mini-os dir
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot
