ENTRY(boot)

SECTIONS {
    . = 0x80200000; /* base address */

    .text :{
        KEEP(*(.text.boot));
        *(.text .text.*);
    }

    .rodata : ALIGN(4) { /* read-only data */
        *(.rodata .rodata.*);
    }

    .data : ALIGN(4) {
        *(.data .data.*);
    }

    .bss : ALIGN(4) {
        __bss = .;
        *(.bss .bss.* .sbss .sbss.*);
        __bss_end = .;
    }

    . = ALIGN(4);
    . += 128 * 1024; /* kernel stack size = 128KB */
    __stack_top = .;

    /* defining memory space to be managed */
    . = ALIGN(4096);
    __free_ram = .;
    . += 64 * 1024; /* 64 MB */
    __free_ram_end = .;
}
