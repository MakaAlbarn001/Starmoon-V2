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
    .data : {
        *(.data)
    }
    .bss : ALIGN(4K){
        _sbss = .;
        *(COMMON)
        *(.bss)
        _ebss = .;
    }
}