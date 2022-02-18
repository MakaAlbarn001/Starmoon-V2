#include <kernel/system.h>
#include <kernel/strace.h>
#include <libc/stdio.h>
#include "isr.h"
#include "memloc.h"

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

extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

extern "C" void idt_flush();

struct idt_pointer
{
    unsigned short limit;
    unsigned int base;
}__attribute__((packed));

struct idt_pointer idtp;

void *irq_routines[] = {
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};

/****************************************************
 * irq_remap():                                     *
 *  function:                                       *
 *      Remaps IRQs 0-7 to interrupt vectors 32-40  *
 *  Arguments: None                                 *
 *  Return Type: Void                               *
 ****************************************************/
void irq_remap()
{
    outportb(PIC_MAS, 0x11);                        // Initialize the Master PIC in cascade mode
    outportb(PIC_SLV, 0x11);                        // Initialize the Slave PIC in cascade mode
    outportb(PIC_MAS+1, 0x20);                      // Set the vector offset for IRQs 0-7
    outportb(PIC_SLV+1, 0x28);                      // Set the vector offset for IRQs 8-15
    outportb(PIC_MAS+1, 0x04);                      // Set Master PIC cascade input pin
    outportb(PIC_SLV+1, 0x02);                      // Set Slave PIC cascide identity
    outportb(PIC_MAS+1, 0x01);                      // Set the Master PIC to 8086 Mode
    outportb(PIC_SLV+1, 0x01);                      // Set the Slave PIC to 8086 Mode
    outportb(PIC_MAS+1, 0x0);                       // Clear the masks in the PIC
    outportb(PIC_SLV+1, 0x0);                       // Clear the masks in the PIC
}

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
    idt_set_gate(32,(void*)irq0, 0x8E, 0x08);
    idt_set_gate(33,(void*)irq1, 0x8E, 0x08);
    idt_set_gate(34,(void*)irq2, 0x8E, 0x08);
    idt_set_gate(35,(void*)irq3, 0x8E, 0x08);
    idt_set_gate(36,(void*)irq4, 0x8E, 0x08);
    idt_set_gate(37,(void*)irq5, 0x8E, 0x08);
    idt_set_gate(38,(void*)irq6, 0x8E, 0x08);
    idt_set_gate(39,(void*)irq7, 0x8E, 0x08);
    idt_set_gate(40,(void*)irq8, 0x8E, 0x08);
    idt_set_gate(41,(void*)irq9, 0x8E, 0x08);
    idt_set_gate(42,(void*)irq10, 0x8E, 0x08);
    idt_set_gate(43,(void*)irq11, 0x8E, 0x08);
    idt_set_gate(44,(void*)irq12, 0x8E, 0x08);
    idt_set_gate(45,(void*)irq13, 0x8E, 0x08);
    idt_set_gate(46,(void*)irq14, 0x8E, 0x08);
    idt_set_gate(47,(void*)irq15, 0x8E, 0x08);
    
    irq_remap();
    
    for(int i = 48; i < 256; i++)
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
    if(r->int_num < 32)
    {
        printf("Interrupt Number %i\nEIP: %#x\nError Code: %x\nESP: %#x\tEBP: %#x\n",
                    r->int_num, r->EIP, r->err_code, r->ESP, r->EBP);
        printf("Segment Selectors:\nCS: %x\tDS: %x\tEFLAGS: %x\n",
                    r->CS, r->DS, r->EFLAGS);
        Debug::StackTrace(6);
        for(;;);
    }
    else
    {
        void (*handler)(struct int_regs *);
        handler = (void (*)(struct int_regs *))irq_routines[r->int_num - 32];
        if(handler)
        {
            handler(r);
        }
        if(r->int_num > 40)
        {
            outportb(0xA0, 0x20);
        }
        outportb(0x20, 0x20);
    }
    return;                             // return to the fault stub to finish the interrupt.
}
