#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>

/************************************************
 * atoi():                                      *
 *  arguments:                                  *
 *      constant character pointer: nptr        *
 *                                              *
 *  return type: integer                        *
 *                                              *
 *  function:                                   *
 *      converts a given numeric c-string into  *
 *      a binary integer value.                 *
 ************************************************/
int atoi(const char *nptr)
{
    int result = 0;                             // initialize a container for the result to 0
    bool neg = false;                           // initialize a determinant for negativity
    size_t i = 0;                               // initialize an iterator to 0
    // Checks to see if the giving number string represents a negative number.
    while(isspace(nptr[i]))                     // so long there is leading whitespace
    {
        i++;                                    // incretment the iterator to skip over it.
    }
    if(nptr[i] == '-')                          
    {                               // if so,
        neg = true;                 // set neg to true
        i++;                        // increment the iterator.
    }
    while(isdigit(nptr[i]))                         // so long as the current string character is a number
    {
        result *= 10;                               // multiply the result by 10 to increment the size
        result += (int)nptr[i] - 0x30;              // add the character value minus 0x30 to result
        i++;                                        // increment the iterator
    }
    if(neg)                                         // if the value is supposed to be negative
    {
        result = -result;                           // set result to its' own negative
    }
    return result;                                  // return result
}