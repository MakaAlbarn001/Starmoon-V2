#include <stdlib.h>
#include <string.h>
#include "lib.h"

/************************************************************
 * ltoa():                                                  *
 *  arguments:                                              *
 *      long integer: num                                   *
 *      character pointer: str                              *
 *      integer: base                                       *
 *                                                          *
 *  return type: character pointer                          *
 *                                                          *
 *  function:                                               *
 *      converts num into a c-style string in the given     *
 *      base.                                               *
 *                                                          *
 *  NOTE: see itoa() for line by line                       *
 ************************************************************/
char *ltoa(long int num, char *str, int base)
{
#if __SIZEOF_INT__ == __SIZEOF_LONG__
    return itoa(num, str, base);            // run if long and int are the same size.
#else
#if !__STDC_HOSTED__
    memset(str, '\0', sizeof(long int) * 8 + 1);
#endif
    if(base > 36)
    {
        return str;
    }
    else
    {
        bool neg = false;
        int i = 0;
        if(num == 0)
        {
            str[i] = '0';
            return str;
        }
        else
        {
            if(num < 0 && base == 10)
            {
                str[i] = '-';
                neg = true;
                num = -num;
                i++;
                while(num > 0)
                {
                    str[i] = hexArray[num % base];
                    i++;
                    num = num/base;
                }
            }
            else
            {
                unsigned long int unum = (unsigned long int)num;
                while(unum > 0)
                {
                    str[i] = hexArray[unum % base];
                    i++;
                    unum = unum/base;
                }
            }
            if(neg)
            {
                strrev(str + 1);
            }
            else
            {
                strrev(str);
            }
            return str;
        }
    }
#endif
}

