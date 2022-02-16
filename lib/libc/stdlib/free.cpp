#include "../core.h"
#include <libc/stdlib.h>

void free(void *addr)
{
    unsigned short int* header = (unsigned short int*)((unsigned int)addr - sizeof(unsigned short int));
    *header = (*header) & 0x3FFF;
    return;
}