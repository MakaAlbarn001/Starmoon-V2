#include <stddef.h>
#include <stdint.h>

void outportb(unsigned short port, unsigned char val);
unsigned char inportb(unsigned short port);

void install_IDT();
void idt_set_gate(size_t num, void* handler, unsigned char attribute, unsigned short selector);