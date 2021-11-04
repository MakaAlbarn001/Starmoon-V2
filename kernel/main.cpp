#include <kernel/boot.h>
#include <kernel/system.h>
#include <kernel/tty.h>
#include <libc/stdio.h>

void outportb(unsigned short port, unsigned char val)
{
    __asm__ __volatile__("outb %0, %1"
                        : : "a"(val), "dN"(port));
}

unsigned char inportb(unsigned short port)
{
    unsigned char ret;
    __asm__ __volatile__("inb %1, %0"
                        : "=a"(ret)
                        : "dN"(port));
    return ret;
}

extern "C" void main() {
    set_basic_gdt();
    terminal_init();
    printf("hello\n");
    for(;;);
}