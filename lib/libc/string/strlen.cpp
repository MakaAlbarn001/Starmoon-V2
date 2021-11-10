#include <string.h>

/************************************************************
 * strlen():                                                *
 *  arguments:                                              *
 *      constant character pointer: str                     *
 *                                                          *
 *  return type: size_t                                     *
 *                                                          *
 *  function:                                               *
 *      determines the length of a string minus the null    *
 *      terminator '\0'                                     *
 ************************************************************/
size_t strlen(const char* str)
{
    int i = 1;                              // initialize the offset index to 1
    while(str[i - 1] != '\0')               // so long as the current character in str is not '\0'
    {
        i++;                                // increment the offset in str
    }
    return i - 1;                           // return the offset minus 1 to exclude the null terminator
}