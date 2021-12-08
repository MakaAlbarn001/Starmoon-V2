#include <kernel/paging.h>

// create global pointers for the page directory and 3 page tables
unsigned int *page_directory;
unsigned int *page_table, *page_table_2, *page_table_3;

extern "C" void setup_paging(unsigned int* page_table_start);

extern "C" void init_paging();

// import linker symbols to access memory locations
extern int KERNEL_DATA;
extern int KERNEL_END;

/************************************************************
 * setup_paging():                                          *
 *  arguements:                                             *
 *      unsigned integer pointer: page_table_start          *
 *                                                          *
 *  return type: void                                       *
 *                                                          *
 *  function:                                               *
 *      fills the initialization paging tables with a       *
 *      one-to-one paging scheme, allowing for direct       *
 *      access to low memory for VGA and hardware.          *
 ************************************************************/
void setup_paging(unsigned int *page_table_start)
{
    int i;                                                  // initialize an iterator
    unsigned int addr = 0;                                  // initialize a memory address counter
    page_directory = page_table_start;                      // set the address of the page directory to the location of the page table memory
    page_table = page_table_start + 0x1000;                 // set the address of the first page table to the page tbl memory plus 4KB
    page_table_2 = page_table_start + 0x2000;               // set the address of the second page table to the page tbl memory plus 8KB
    page_table_3 = page_table_start + 0x3000;               // set the address of the third page table to the page tbl memory plus 12KB
    page_directory[0] = (unsigned int)page_table | 0x3;     // fill the first page directory entry with the address of the first page table and the permissions
    for(i = 0; addr < 0x100000; i++)                        // so long as the address is less than 1MB
    {
        page_table[i] = addr | 0x3;                         // fill the first page table with the base physical address of the page frame
        addr += 0x1000;                                     // increment the base address by 4KB
    }
    for(; addr < (unsigned int)&KERNEL_DATA; i++)           // so long as the address is less than the beginning of the kernel data section
    {
        page_table[i] = addr | 0x1;                         // fill the page table entries with the Read-Only sections of kernel memory
        addr += 0x1000;                                     // increment the base address by 4KB
    }
    if((unsigned int)&KERNEL_END > 0x400000)                // if the end of kernel memory is greater than 4MB
    {
        for(;i<1024;i++)                                    // fill the rest of the first page table
        {
            page_table[i] = addr | 0x3;                     // fill the table with the base address with read/write permissions
            addr += 0x1000;                                 // increment the base address by 4KB
        }
        page_directory[1] = (unsigned int)page_table_2 | 0x3; // fill the second entry of the page directory with the address of
                                                                    // the second page table with read/write permissions
        if((unsigned int)&KERNEL_END > 0x800000)        // if the kernel extends past 8 MB
        {
            for(i=0;i<1024;i++)                         // for all 1024 entries of the second page table
            {
                page_table_2[i] = addr | 0x3;           // fill the entries with the base address with read/write permissions
                addr += 0x1000;                         // increment the base address by 4KB
            }
            // fill the third entry of the page directory with the address of the third page table with read/write permissions
            page_directory[2] = (unsigned int)page_table_3 | 0x3;
            for(i = 0; addr < (unsigned int)&KERNEL_END; i++)       // for the rest of the kernel
            {
                page_table_3[i] = addr | 0x3;               // fill the page table with the base address with read/write permissions
                addr += 0x1000;                         // increment the base address by 4KB
            }
            for(i=3;i<1024;i++)                         // for the rest of the page directory entries
            {
                page_directory[i] = 0x0;                // mark them as not present
            }
        }
        else                        // otherwise
        {
            for(i=0;addr < (unsigned int)&KERNEL_END; i++)        // until the end of the kernel is reached
            {
                page_table_2[i] = addr | 0x3;       // fill the second page table with the base address with read/write permissions
                addr += 0x1000;                     // increment the base address by 4KB
            }
        }
    }
    else            // otherwise
    {
        for(;i<1024;i++)            // for the rest of the first page table
        {
            page_table[i] = addr | 0x3;         // fill the entries with the base address with read/write permissions
            addr += 0x1000;                     // increment the base address by 4KB
        }
        for(i=1;i<1024;i++)             // for the rest of the page directory
        {
            page_directory[i] = 0x0;    // mark entry as not present
        }
    }

    init_paging();              // initialize paging.
}