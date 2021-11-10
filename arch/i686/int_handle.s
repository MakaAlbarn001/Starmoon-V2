.section .text

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

fault_stub:
