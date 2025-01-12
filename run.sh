#!/bin/bash

set -xue # debugging, undefined, exit

QEMU=/usr/bin/qemu-system-riscv32 # path found by running 'which qemu-system-riscv32'

CC=clang
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32 -ffreestanding -nostdlib" # O2 for optimized machine code generation

# build kernel
$CC $CFLAGS -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf kernel.c common.c

# to make sure this works, install opensbi within the mini-os dir
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot -kernel kernel.elf 
