#include <string.h>

/****************************************
 *  strrev():                           *
 *  arguments:                          *
 *      character pointer: str          *
 *                                      *
 *  return type: void                   *
 *                                      *
 *  function:                           *
 *      reverses the characters within  *
 *      a string with the exception of  *
 *      the null terminator(/0)         *
 ****************************************/
void strrev(char* str)
{
    int i, len;                             // initialize the forward and backward indecies.
    len = strlen(str) - 1;                  // determine the length of the string minus '\0'
    i = 0;                                  // set the forward-index to zero
    while(i < len)                          // iterate until the midpoint has been passed.
    {
        byteSwap(str + i, str + len);       // swaps the characters at offset i and len
        i++;                                // increments the forward-index
        len--;                              // decrements the backwards-index
    }
    return;                                 // return.
}