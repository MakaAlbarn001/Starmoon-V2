#include <stdio.h>
#include <string.h>
#include <stdint.h>

/****************************************************
 * puts():                                          *
 *  arguments:                                      *
 *      constant character pointer: str             *
 *                                                  *
 *  return type: integer                            *
 *                                                  *
 *  function:                                       *
 *      prints a simple C-string to the screen.     *
 ****************************************************/
int puts(const char* str)
{
    size_t i = 0;                   // initialize an offset iterator to 0
    while(str[i] != '\0')           // until the value of str is a null terminator
    {
        putchar(str[i]);            // print the current character in str.
        i++;                        // increment the offset iterator
    }
    putchar('\n');                  // print a newline character '\n'
    return i + 1;                   // return the number of characters printed.
}