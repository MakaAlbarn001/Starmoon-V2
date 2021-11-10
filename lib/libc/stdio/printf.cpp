#include <stdio.h>

/************************************************************
 * printf():                                                *
 *  arguments:                                              *
 *      restricted constant character pointer: format       *
 *      variable arguments: ...                             *
 *                                                          *
 *  return type: integer                                    *
 *                                                          *
 *  function:                                               *
 *      prints a formatted string to the screen using a     *
 *      template string and a variable number of secondary  *
 *      values that get formatted into the string.          *
 ************************************************************/
int printf(const char * __restrict__ format, ...)
{
    int ret;                                        // initialize a return value container
    va_list vlist;                                  // initialize a variable argument list.
    va_start(vlist, format);                        // set the variable arguement list to the given arguments.
    ret = vprintf(format, vlist);                   // set ret to the return value of vprintf having passed the original string and the variable arguement list
    va_end(vlist);                                  // close out the variable argument list.
    return ret;                                     // return the number of characters printed.
}