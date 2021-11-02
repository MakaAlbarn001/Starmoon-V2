#define DATA_UP_READ_CLEAR 0x0
#define DATA_UP_READ 0x1
#define DATA_UP_WRITE_CLEAR 0x2
#define DATA_UP_WRITE 0x3
#define DATA_DOWN_READ_CLEAR 0x4
#define DATA_DOWN_READ 0x5
#define DATA_DOWN_WRITE_CLEAR 0x6
#define DATA_DOWN_WRITE 0x7
#define CODE_NONCONFORM_EXECUTE_CLEAR 0x8
#define CODE_NONCONFORM_EXECUTE 0x9
#define CODE_NONCONFORM_READ_CLEAR 0xA
#define CODE_NONCONFORM_READ 0xB
#define CODE_CONFORM_EXECUTE_CLEAR 0xC
#define CODE_CONFORM_EXECUTE 0xD
#define CODE_CONFORM_READ_CLEAR 0xE
#define CODE_CONFORM_READ 0xF

#define SYS_RESERVED_1 0x0
#define SYS_TSS_16_AVAIL 0x1
#define SYS_LDT 0x2
#define SYS_TSS_16_BUSY 0x3
#define SYS_CALL_GATE_16 0x4
#define SYS_TASK_GATE 0x5
#define SYS_INT_GATE_16 0x6
#define SYS_TRAP_GATE_16 0x7
#define SYS_RESERVED_2 0x8
#define SYS_TSS_32_64_AVAIL 0x9
#define SYS_RESERVED_3 0xA
#define SYS_TSS_32_64_BUSY 0xB
#define SYS_CALL_GATE_32_64 0xC
#define SYS_RESERVED_4 0xD
#define SYS_INT_GATE_32_64 0xE
#define SYS_TRAP_GATE_32_64 0xF

#include <stdint.h>
#include <stddef.h>

/*********************************************
 *   seg_descriptor structure:               *
 *   defines the structure of the descriptor *
 *   entries in the GDT and LDT.             *
 *********************************************/
struct seg_descriptor {
    unsigned short lim_lo;          // lower 16 bits of the limit
    unsigned short base_lo;         // lower 16 bits of the base address
    char base_mid;                  // middle 8 bits of the base address
    char attr;                      // descriptor attributes
    char flags;                     // upper 4 bits of the limit and descriptor flags
    char base_hi;                   // upper 8 bits of the base address.
}__attribute__((packed));
/****************************************************
 *  seg_descriptor.attr:                            *
 *  bits 0-3: descriptor type                       *
 *  bit 4: 0 for system descriptor, 1 for code/data *
 *  bits 5-6: descriptor privelege level: 0-3       *
 *  bit 7: present flag, if clear, bits 0-40,48-64  *
 *      are available.                              *
 *                                                  *
 *  seg_descriptor.flags:                           *
 *  bits 0-3: upper 4 bits of the limit             *
 *  bit 4: unreserved, free for use                 *
 *  bit 5: 64-bit code segment                      *
 *  bit 6: 0 for 16-bit code/data, 1 for 32-bit     *
 *  bit 7: 0 for byte limit multiplier, 1 for 4KB   *
 *      limit multiplier.                           *
 ****************************************************/

/********************************
 * struct desc_tbl_ptr          *
 *  contains pointers to the    *
 *  descriptor tables.          *
 ********************************/
 struct desc_tbl_ptr {
     uint16_t tbl_lim;
     uint32_t tbl_addr;
 }__attribute__((packed));

 // set a segment descriptor
 void gldt_set_desc(struct seg_descriptor *tbl, size_t num, uint32_t base, uint32_t limit, uint8_t attr, uint8_t flags);
 