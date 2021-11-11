#include <kernel/system.h>
#include <libc/stdio.h>
#include "isr.h"

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

extern "C" void idt_flush();

struct idt_pointer
{
    unsigned short limit;
    unsigned int base;
}__attribute__((packed));

struct idt_pointer idtp;

/************************************************************
 * install_IDT():                                           *
 *  arguements: none                                        *
 *  return type: void                                       *
 *  function:                                               *
 *      installs a basic Interrupt Descriptor Table and     *
 *      flushes the processors idtr                         *
 ************************************************************/
void install_IDT()
{
    // fill the IDT with the first 32 interrupts which come from the processor.
    idt_set_gate(0,(void*)isr0,0x8E, 0x08);
    idt_set_gate(1,(void*)isr1,0x8E, 0x08);
    idt_set_gate(2,(void*)isr2,0x8E, 0x08);
    idt_set_gate(3,(void*)isr3,0x8E, 0x08);
    idt_set_gate(4,(void*)isr4,0x8E, 0x08);
    idt_set_gate(5,(void*)isr5,0x8E, 0x08);
    idt_set_gate(6,(void*)isr6,0x8E, 0x08);
    idt_set_gate(7,(void*)isr7,0x8E, 0x08);
    idt_set_gate(8,(void*)isr8,0x8E, 0x08);
    idt_set_gate(9,(void*)isr9,0x8E, 0x08);
    idt_set_gate(10,(void*)isr10,0x8E, 0x08);
    idt_set_gate(11,(void*)isr11,0x8E, 0x08);
    idt_set_gate(12,(void*)isr12,0x8E, 0x08);
    idt_set_gate(13,(void*)isr13,0x8E, 0x08);
    idt_set_gate(14,(void*)isr14,0x8E, 0x08);
    idt_set_gate(15,(void*)isr15,0x8E, 0x08);
    idt_set_gate(16,(void*)isr16,0x8E, 0x08);
    idt_set_gate(17,(void*)isr17,0x8E, 0x08);
    idt_set_gate(18,(void*)isr18,0x8E, 0x08);
    idt_set_gate(19,(void*)isr19,0x8E, 0x08);
    idt_set_gate(20,(void*)isr20,0x8E, 0x08);
    idt_set_gate(21,(void*)isr21,0x8E, 0x08);
    idt_set_gate(22,(void*)isr22,0x8E, 0x08);
    idt_set_gate(23,(void*)isr23,0x8E, 0x08);
    idt_set_gate(24,(void*)isr24,0x8E, 0x08);
    idt_set_gate(25,(void*)isr25,0x8E, 0x08);
    idt_set_gate(26,(void*)isr26,0x8E, 0x08);
    idt_set_gate(27,(void*)isr27,0x8E, 0x08);
    idt_set_gate(28,(void*)isr28,0x8E, 0x08);
    idt_set_gate(29,(void*)isr29,0x8E, 0x08);
    idt_set_gate(30,(void*)isr30,0x8E, 0x08);
    idt_set_gate(31,(void*)isr31,0x8E, 0x08);
    // fill the rest of the table will null descriptors
    for(int i = 32; i < 256; i++)
    {
        idt_set_gate(i,0,0,0);
    }

    // create a pointer to the IDT to load the idtr with
    idtp.base = (unsigned int)idt_tlb;
    idtp.limit = sizeof(struct idt_entry) * 256 - 1;

    // flush the idt
    idt_flush();

    return;
}

/************************************************************
 * idt_set_gate():                                          *
 *  arguements:                                             *
 *      size_t: num                                         *
 *      void pointer: handler                               *
 *      unsigned character: attribute                       *
 *      unsigned short: selector                            *
 *                                                          *
 *  return type: void                                       *
 *                                                          *
 *  function:                                               *
 *      fills a descriptor in the idt with a handler for an *
 *          interrupt.                                      *
 ************************************************************/
void idt_set_gate(size_t num, void* handler, unsigned char attribute, unsigned short selector)
{
    idt_tlb[num].offset_lo = (unsigned short)((unsigned int)handler & 0xFFFF);
    idt_tlb[num].selector = selector;
    idt_tlb[num].attr = attribute;
    idt_tlb[num].offset_hi = (unsigned short)(((unsigned int)handler >> 16) & 0xFFFF);
    return;
}

/****************************************************
 * fault_handler()                                  *
 *  arguments:                                      *
 *      int_regs structure pointer: r               *
 *                                                  *
 *  return type: void                               *
 *                                                  *
 *  traits:                                         *
 *      External "C" linkage                        *
 *                                                  *
 *  function:                                       *
 *      primary handler for interrupts passed to    *
 *      the processor.                              *
 ****************************************************/
void fault_handler(struct int_regs *r)
{
    printf("Interrupt Number %i\nEIP: %#x\nError Code: %x\nESP: %#x\tEBP: %#x\n",
                r->int_num, r->EIP, r->err_code, r->ESP, r->EBP);
    for(;;);
    return;                             // return to the fault stub to finish the interrupt.
}
