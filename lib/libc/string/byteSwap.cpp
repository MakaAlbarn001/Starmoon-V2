#include <string.h>

/************************************************
 * byteSwap():                                  *
 *  arguments:                                  *
 *      character pointer: loc1                 *
 *      character pointer: loc2                 *
 *                                              *
 *  return type: void                           *
 *                                              *
 *  function:                                   *
 *      swaps the values in loc1 and loc2       *
 ************************************************/
void byteSwap(char* loc1, char* loc2)
{
    char temp;                          // initialize a temporary variable to hold a value
    temp = *loc2;                       // set the temporary variable to the value in loc2
    *loc2 = *loc1;                      // set the value of loc2 to the value in loc1
    *loc1 = temp;                       // set the value of loc1 to the value in the temporary variable
    return;                             // return
}