#include "../core.h"
#include <libc/stdlib.h>
#include <libc/stdio.h>
#include <kernel/paging.h>

/****************************************************
 * malloc():                                        *
 *  arguments:                                      *
 *      size_t: size - number of bytes to allocate  *
 *                                                  *
 *  return type:                                    *
 *      void pointer                                *
 *                                                  *
 *  function:                                       *
 *      Allocates 'size' bytes of memory in the     *
 *      heap and returns the address.               *
 ****************************************************/
void *malloc(size_t size)
{
    // create a pointer that points to the first non-NULL header in heap memory.
    unsigned short int *header = (unsigned short int*)((unsigned int)heap_ptr + sizeof(unsigned short int));
    // while the current header does not have the End-Of-Memory flag set
    while((*header & 0x4000) != MEM_EOM)
    {
        // if the used flag is clear
        if((*header & 0x8000) == 0)
        {
            if((*header & 0x3FFF) > (size + 2))
            {
                unsigned short int *new_head = (unsigned short int*)((unsigned int)header +
                    sizeof(unsigned short int) + size);
                *new_head = (*header & 0x3FFF) - (size + 2);
                *header = MEM_USED | size;
                return (void *)((unsigned int)header + sizeof(unsigned short));
            }
        }
        header = (unsigned short int*)((unsigned int)header + sizeof(unsigned short int)
            + (*header & 0x3FFF));
    }
    return NULL;
}

/****************************************
 * header_trace():                      *
 *  arguments: none                     *
 *  return type: void                   *
 *  function:                           *
 *      Prints out the location and     *
 *      contents of the heap headers.   *
 ****************************************/
void header_trace()
{
    unsigned short int* trace = heap_ptr;           // create a trace pointer for the heap headers.
    while(*trace != MEM_EOM)                // until the End-of-Memory header is reached
    {
        // print the location and contents of the headers
        printf("%#x:\t%04x\n",trace,*trace);
        // increment the trace pointer to the next header
        trace = (unsigned short int*)((unsigned int)trace + 
            sizeof(unsigned short int) + (*trace & 0x3FFF));
    }
    // print the location and contents of the End-of-Memory header
    printf("%#x:\t%04x\n",trace,*trace);
    return;
}