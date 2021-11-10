#include <stdlib.h>
#include <string.h>
#include "lib.h"

/************************************************************
 * lltoa():                                                 *
 *  arguments:                                              *
 *      long long integer: num                              *
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
char *lltoa(long long int num, char *str, int base)
{
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
    return ltoa(num, str, base);                        // run if long and long long are the same.
#else
#if !__STDC_HOSTED__
    memset(str, '\0', sizeof(long long int) * 8 + 1);
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
                unsigned long long int unum = (unsigned long long int)num;
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

