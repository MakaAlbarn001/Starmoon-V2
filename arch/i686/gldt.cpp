#include <kernel/gldt.h>
#include <kernel/boot.h>

alignas(8) struct seg_descriptor gdt[8192];
alignas(8) struct desc_tbl_ptr gp;

void gldt_set_desc(struct seg_descriptor *tbl, size_t num, uint32_t base,
                    uint32_t limit, uint8_t attr, uint8_t flags)
{
    tbl[num].lim_lo = limit & 0xFFFF;
    tbl[num].base_lo = base & 0xFFFF;
    tbl[num].base_mid = (base >> 16) & 0xFF;
    tbl[num].attr = attr;
    tbl[num].flags = (flags & 0xF0) | ((limit >> 16) & 0xF);
    tbl[num].base_hi = (base >> 24) & 0xFF;
}

void set_basic_gdt()
{
	gldt_set_desc(gdt, 0, 0, 0, 0, 0);
	gldt_set_desc(gdt, 1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gldt_set_desc(gdt, 2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    for(int i = 3; i <= 8192; i++)
    {
        gldt_set_desc(gdt, i, 0, 0, 0, 0);
    }

	gp.tbl_addr = (uint32_t)gdt;
	gp.tbl_lim = sizeof(struct seg_descriptor) * 8192 - 1;

	gdt_flush();
}