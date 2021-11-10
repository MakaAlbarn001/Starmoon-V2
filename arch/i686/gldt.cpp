#include <kernel/gldt.h>
#include <kernel/boot.h>

alignas(8) struct seg_descriptor gdt[8192];
alignas(8) struct desc_tbl_ptr gp;

/**************************************************************** 
 * gldt_set_desc():                                             *
 *  arguments:                                                  *
 *      segment descriptor structure pointer: tbl               *
 *      size_t: num                                             *
 *      32-bit unsigned integer: base                           *
 *      32-bit unsigned integer: limit                          *
 *      8-bit unsigned integer: attr                            *
 *      8-bit unsigned integer: flags                           *
 *                                                              *
 *  return type: void                                           *
 *                                                              *
 *  function:                                                   * 
 ****************************************************************/
void gldt_set_desc(struct seg_descriptor *tbl, size_t num, uint32_t base,
                    uint32_t limit, uint8_t attr, uint8_t flags)
{
    tbl[num].lim_lo = limit & 0xFFFF;                               // set the lower 16 bits of the limit
    tbl[num].base_lo = base & 0xFFFF;                               // set the lower 16 bits of the base
    tbl[num].base_mid = (base >> 16) & 0xFF;                        // set the middle 8 bits of the base
    tbl[num].attr = attr;                                           // set the attributes
    tbl[num].flags = (flags & 0xF0) | ((limit >> 16) & 0xF);        // set the flags and the uper 4 bits of the limit
    tbl[num].base_hi = (base >> 24) & 0xFF;                         // set the upper 8 bits of the base.
}

/************************************************
 * set_basic_gdt():                             *
 *  arguments: none                             *
 *  return type: void                           *
 *  function:                                   *
 *      generates a basic GDT with three        *
 *      descriptors.                            *
 ************************************************/
void set_basic_gdt()
{
    // create a Null descriptor in the GDT
	gldt_set_desc(gdt, 0, 0, 0, 0, 0);
    // create a 32-bit code segment descriptor from 0 to 4GB with kernel access
	gldt_set_desc(gdt, 1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // create a 32-bit data segment descriptor from 0 to 4GB with kernel access.
	gldt_set_desc(gdt, 2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // fill the last 8189 entries in the GDT with Null descriptors
    for(int i = 3; i <= 8192; i++)
    {
        gldt_set_desc(gdt, i, 0, 0, 0, 0);
    }

	gp.tbl_addr = (uint32_t)gdt;                                // set the base address of the gdt
	gp.tbl_lim = sizeof(struct seg_descriptor) * 8192 - 1;      // set the size of the gdt

	gdt_flush();                    // flush the GDT
}