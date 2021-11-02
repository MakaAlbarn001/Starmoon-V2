#include <kernel/boot.h>

extern "C" void main() {
    set_basic_gdt();
    __asm__("movw $0x0241, 0xB8000");
    for(;;);
}