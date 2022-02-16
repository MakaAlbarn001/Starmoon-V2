ENTRY(_start)

SECTIONS {
    . = 1M;
    .text : ALIGN(4K) {
        *(.multiboot)
        *(.text)
    }
    .rodata : {
        *(.rodata)
    }
    KERNEL_DATA = .;
    .data : ALIGN(4K) {
        *(.data)
    }
    .bss : ALIGN(4K) {
        _sbss = .;
        *(COMMON)
        *(.bss)
        _ebss = .;
    }
    .data1 : ALIGN(4K) {
        *(.heap)
    }
    KERNEL_END = .;
}