#include <stdio.h>
#if !__STDC_HOSTED__
#include <kernel/tty.h>
#else

#endif

/********************************************************
 * putchar():                                           *
 *  arguments:                                          *
 *      integer: ch                                     *
 *                                                      *
 *  return type: integer                                *
 *                                                      *
 *  function:                                           *
 *      prints a single unformatted character to the    *
 *      screen.                                         *
 ********************************************************/
int putchar(int ch) {
// if this is part of the hosted C Library
#if __STDC_HOSTED__
    // TODO: implement hosted putchar()
    return ch;
// otherwise
#else
    kputchar((short)ch);            // Tell the kernel to print the character
    return ch;                      // return the value of character
#endif
}