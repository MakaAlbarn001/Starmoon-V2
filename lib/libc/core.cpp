#include "core.h"
#include <string.h>

unsigned short int *heap_ptr;

/****************************************************************
 * initialize_standard_library():                               *
 *  arguments:                                                  *
 *      void pointer: heap_begin                                *
 *      void pointer: heap_end                                  *
 *                                                              *
 *  return type: void                                           *
 *                                                              *
 *  function:                                                   *
 *      Initializes the C standard library backend for memory   *
 *          management, FILE I/O, ...
 ****************************************************************/
extern "C" void initialize_standard_library(void *heap_begin, void *heap_end)
{
    int heap_sz = (unsigned int)heap_end - (unsigned int)heap_begin;
    memset(heap_begin, 0, heap_sz);
    heap_ptr = (unsigned short int*)heap_begin;                      // set the heap pointer to the begining of heap memory
    *heap_ptr = MEM_USED;     // set the first heap header to used with no offset
    // create a temporary pointer to the end of heap memory
    unsigned short int *EOM_ptr = ((unsigned short int* )heap_end - 1);
    *EOM_ptr = MEM_EOM;      // set the last heap header to free/EOM/zero-offset
    unsigned short int *temp = heap_ptr + 1;       // set the temporary pointer to the first free header
    // set the header to free with the offset being the memory between the current header and the EOM header.
    *temp = 0;
    *temp = (((unsigned int)heap_end - sizeof(unsigned short int)) -
                     ((unsigned int)temp + sizeof(unsigned short int))) & 0x3FFF;
    return;
}