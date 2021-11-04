#include <string.h>

void strrev(char* str)
{
    int i, len;
    len = strlen(str) - 1;
    i = 0;
    while(i < len)
    {
        byteSwap(str + i, str + len);
        i++;
        len--;
    }
    return;
}