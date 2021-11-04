#include <stdlib.h>
#include <string.h>
#include "lib.h"

char *itoa(int num, char *str,int base)
{
#if !__STDC_HOSTED__
    memset(str, '\0', sizeof(int) * 8 + 1);
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
                unsigned int unum = (unsigned int)num;
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
}