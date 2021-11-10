#include <string.h>

/****************************************************************
 * memmove():                                                   *
 *  arguments:                                                  *
 *      void pointer: dest                                      *
 *      void pointer: src                                       *
 *      size_t: count                                           *
 *                                                              *
 *  return type: void pointer                                   *
 *                                                              *
 *  function:                                                   *
 ****************************************************************/
void *memmove(void* dest, void* src, size_t count)
{
    unsigned char* dst = (unsigned char*)dest;                  // initialize a character pointer dst to dest
    if(src > dest)                                              // if the address of src is less than that of dest
    {
        size_t i = 0;                                           // initialize the offset index to 0
        while(i < count)                                        // until the offset index equals count
        {
            *(dst + i) = *((unsigned char*)src + i);            //set dst plus i to the value in src plus i
            i++;                                                // increment the offset index.
        }
    }
    else                                                        // if the address in src is less than dest
    {
        int i = count - 1;                                      // initialize the offset index to count 0 1
        while(i > -1)                                           // until the offset index reaches zero
        {
            *(dst + i) = *((unsigned char*)src + i);            // set dst plus i to the value in src plus i
            i--;                                                // decrement the offset index
        }
    }
    return dest;                                                // return the address dest
}