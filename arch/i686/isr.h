#pragma once

/************************************************************************
 * int_regs: interrupt register structure: Stack Layout                 *
 *----------------------------------------------------------------------*
 *    offset|                       Contents                        |   *
 *----------------------------------------------------------------------*
 *      72  |     User Stack Segment Selector (64-bit/PL Change)    |   *
 *      68  |              User ESP (64-bit/PL Change)              |   *
 *      64  |                   EFLAGS Register                     |   *
 *      60  |               Code Segment Selector                   |   *
 *      56  |                   EIP Register                        |   *
 *      52  |            Error Code(Dummy Possible)                 |   *
 *      48  |               Interrupt Number                        |   *
 *      44  |                    EAX Register                       |   *
 *      40  |                    ECX Register                       |   *
 *      36  |                    EDX Register                       |   *
 *      32  |                    EBX Register                       |   *
 *      28  |                   Interrupt ESP                       |   *
 *      24  |                   Interrupt EBP                       |   *
 *      20  |                    ESI Register                       |   *
 *      16  |                    EDI Register                       |   *
 *      12  |                Date Segment Selector                  |   *
 *       8  |               Extra Segment Selector                  |   *
 *       4  |               Bonus Segment 1 Selector                |   *
 *       0  |               Bonus Segment 2 Selector                |   *
 ************************************************************************/
struct int_regs {
    unsigned int GS, FS, ES, DS;
    unsigned int EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
    unsigned int int_num, err_code;
    unsigned int EIP, CS, EFLAGS, ESP_U, SS_U;
};

struct idt_entry {
    unsigned short offset_lo;
    unsigned short selector;
    unsigned char res = 0;
    unsigned char attr;
    unsigned short offset_hi;
};

struct idt_entry idt_tlb[256];

extern "C" void fault_handler(struct int_regs *r);