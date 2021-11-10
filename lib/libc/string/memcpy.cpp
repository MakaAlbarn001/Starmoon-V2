#include <string.h>

/********************************************************
 * memcpy():                                            *
 *  arguments:                                          *
 *      restricted void pointer: dest                   *
 *      restricted constant void pointer: src           *
 *      size_t: count                                   *
 *                                                      *
 *  return type: void pointer                           *
 *                                                      *
 *  function:                                           *
 *      copies the data from src to dest for count      *
 ********************************************************/
void* memcpy(void* __restrict__ dest, const void* __restrict__ src, size_t count)
{
    if((char *)dest + count > (char *)src || (char *)src + count > (char *)dest)        // confirms that there is no overlap
    {
        return (void *)src;                                                 // if there is overlap, return src
    }
    unsigned char* dst = (unsigned char*)dest;                              // initialize a character pointer to dest
    int i = count - 1;                                                      // initialize an offset index to count minus 1
    while(i > -1)                                                           // until the offset index equals zero
    {
        *(dst + i) = *((unsigned char*)src + i);                            // copy scr + i to dst + i
        i--;                                                                // decrement the offset index
    }
    return dest;                                                            // return the address of dest
}