#include <stdlib.h>
#include <string.h>
#include "lib.h"

/************************************************************
 * itoa():                                                  *
 *  arguments:                                              *
 *      integer: num                                        *
 *      character pointer: str                              *
 *      integer: base                                       *
 *                                                          *
 *  return type: character pointer                          *
 *                                                          *
 *  function:                                               *
 *      converts num into a c-style string in the given     *
 *      base.                                               *
 ************************************************************/
char *itoa(int num, char *str,int base)
{
// if the build is frestanding
#if !__STDC_HOSTED__                                        
    memset(str, '\0', sizeof(int) * 8 + 1);                 // clear the destination string
#endif                                                      
    if(base > 36)                                           // if the base is greater than 36
    {                                                       
        return str;                                         // return the empty string.
    }                                                       
    else                                                    // otherwise:
    {                                                       
        bool neg = false;                                   // initialize a boolean container for if the number is negative
        int i = 0;                                          // initialize an offset iterator to 0
        if(num == 0)                                        // if the number is 0
        {                                                   
            str[i] = '0';                                   // set the first element of the string to '0'
            return str;                                     // return the string.
        }                                                   
        else                                                // otherwise
        {                                                   
            if(num < 0 && base == 10)                       // if the number is less than 0 and the base is 10
            {                                               
                str[i] = '-';                               // set the first element of the destination string to '-'
                neg = true;                                 // set the boolean variable neg to true
                num = -num;                                 // make num a positive value
                i++;                                        // increment the offset iterator
                while(num > 0)                              // until num reaches 0
                {                                           
                    str[i] = hexArray[num % base];          // set the current element in str to value in hexArray offset by the modulus of num by base.
                    i++;                                    // increment the offset interator
                    num = num/base;                         // set num equal to itself divided by base.
                }                                           
            }                                               
            else                                            // otherwise
            {                                               
                unsigned int unum = (unsigned int)num;      // initialize an unsigned integer equal to the unsigned typecast of num
                while(unum > 0)                             // until unum equals 0
                {                                           
                    str[i] = hexArray[unum % base];         // set the current element in str to the value in hexArray offset by the modulus of unum by base.
                    i++;                                    // increment the offset iterator
                    unum = unum/base;                       // set unum equal to unum divided by the base.
                }                                           
            }                                               
            if(neg)                                         // if neg is true
            {                                               
                strrev(str + 1);                            // reverse the string ignoring the first element.
            }                                               
            else                                            // otherwise
            {                                               
                strrev(str);                                // reverse the string.
            }                                               
            return str;                                     //
        }
    }
}