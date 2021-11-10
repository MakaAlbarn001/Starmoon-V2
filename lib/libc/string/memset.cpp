#include <string.h>

/********************************************************
 * memset():                                            *
 *  arguments:                                          *
 *      void pointer: dest                              *
 *      integer: ch                                     *
 *      size_t: count                                   *
 *                                                      *
 *  return type: void pointer                           *
 *                                                      *
 *  function:                                           *
 *      sets the values of dest to dest plus count      *
 *      to the value described in the lowest 8 bits     *
 *      of ch.                                          *
 ********************************************************/
void* memset(void* dest, int ch, size_t count)
{
    if(dest == NULL)                                        // checks if the address of dest is NULL
    {
        return NULL;                                        // if so, return NULL
    }
    unsigned char* dst = (unsigned char*)dest;              // initialize an internal character pointer to dest
    for(size_t i = 0; i < count; i++)                       // from i = 0, until i equals count
    {
        *(dst + i) = (unsigned char)ch;                     // set dst + i to the lowest 8 bits of ch
    }                                                       // and increment i
    return dest;                                            // return the address of dest.
}