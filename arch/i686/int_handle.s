.section .text

/************************************
 * irq macro function:              *
 *  function:                       *
 *      Entry point for Interrupt   *
 * Requests.                        *
 *  Arguments: None                 *
 *  Return Type: Void               *
 ************************************/
.macro irqs i
.global irq\i
irq\i:
    cli
    pushl $0
    pushl $(\i + 32)
    jmp fault_stub
.endm

.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31
/****************************************
 * isrX():                              *
 *  function:                           *
 *      entry handles for exceptions.   *
 *  Note:                               *
 *      isrs 8, 10-14, and 17 only push *
 *      the interrupt number because    *
 *      the processor automatically     *
 *      pushes an error code. all other *
 *      exceptions push a dummy code of *
 *      0.                              *
 ****************************************/
isr0:
    pushl $0
    pushl $0
    jmp fault_stub
isr1:
    pushl $0
    pushl $1
    jmp fault_stub
isr2:
    pushl $0
    pushl $2
    jmp fault_stub
isr3:
    pushl $0
    pushl $3
    jmp fault_stub
isr4:
    pushl $0
    pushl $4
    jmp fault_stub
isr5:
    pushl $0
    pushl $5
    jmp fault_stub
isr6:
    pushl $0
    pushl $6
    jmp fault_stub
isr7:
    pushl $0
    pushl $7
    jmp fault_stub
isr8:
    pushl $8
    jmp fault_stub
isr9:
    pushl $0
    pushl $9
    jmp fault_stub
isr10:
    pushl $10
    jmp fault_stub
isr11:
    pushl $11
    jmp fault_stub
isr12:
    pushl $12
    jmp fault_stub
isr13:
    pushl $13
    jmp fault_stub
isr14:
    pushl $14
    jmp fault_stub
isr15:
    pushl $0
    pushl $15
    jmp fault_stub
isr16:
    pushl $0
    pushl $16
    jmp fault_stub
isr17:
    pushl $17
    jmp fault_stub
isr18:
    pushl $0
    pushl $18
    jmp fault_stub
isr19:
    pushl $0
    pushl $19
    jmp fault_stub
isr20:
    pushl $0
    pushl $20
    jmp fault_stub
isr21:
    pushl $0
    pushl $21
    jmp fault_stub
isr22:
    pushl $0
    pushl $22
    jmp fault_stub
isr23:
    pushl $0
    pushl $23
    jmp fault_stub
isr24:
    pushl $0
    pushl $24
    jmp fault_stub
isr25:
    pushl $0
    pushl $25
    jmp fault_stub
isr26:
    pushl $0
    pushl $26
    jmp fault_stub
isr27:
    pushl $0
    pushl $27
    jmp fault_stub
isr28:
    pushl $0
    pushl $28
    jmp fault_stub
isr29:
    pushl $0
    pushl $29
    jmp fault_stub
isr30:
    pushl $0
    pushl $30
    jmp fault_stub
isr31:
    pushl $0
    pushl $31
    jmp fault_stub

irqs 0
irqs 1
irqs 2
irqs 3
irqs 4
irqs 5
irqs 6
irqs 7
irqs 8
irqs 9
irqs 10
irqs 11
irqs 12
irqs 13
irqs 14
irqs 15

/************************************************
 * fault_stub():                                *
 *  arguements: none                            *
 *  return type: none(interrupt)                *
 *  function:                                   *
 *      A universal stub to provide extra       *
 *      information to the interrupt handler    *
 *      to resolve interrupts.                  *
 ************************************************/
.extern fault_handler
fault_stub:
    pusha                       # push all of the current registers
    pushl %ds                    # push the data segment selector
    pushl %es                    # push the extra segment selector
    pushl %fs                    # push the first bonus segment selector
    pushl %gs                    # push the second bonus segment selector
    mov $0x10, %ax              # set ax to the segment offset for the kernel data segment
    mov %ax, %ds                # set ds, es, fs, and gs to the offset in ax
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %esp, %eax              # set eax to the current stack pointer
    # push the value in eax onto the stack, creating a pointer to the interrupt information structure
    push %eax                   
    mov $fault_handler, %eax    # set eax to the memory address of the actual fault handler
    call *%eax                  # call the function address in eax
    pop %eax                    # pop the top of the stack into eax
    popl %gs                     # pop the second bonus segment selector
    popl %fs                     # pop the first bonus segment selector
    popl %es                     # pop the extra segment selector
    popl %ds                     # pop the data segment selector
    popa                        # pop all of the registers
    add $8, %esp                # removes the interrupt number and error code from the stack
    iret                        # preform an interrupt return to resume normal function

/************************************
 * idt_flush():                     *
 *  loads the idt pointer into the  *
 *      idtr with the lidt          *
 *      instruction                 *
 ************************************/
.global idt_flush
.type idt_flush, @function
.extern idtp
idt_flush:
    push %ebp                   // push the current base pointer
    mov %esp, %ebp              // maintain the stack framm
    lidt (idtp)                 // load the idtp into idtr
    mov %ebp, %esp              // back step the stack frame
    pop %ebp                    // restore the original base pointer
    ret