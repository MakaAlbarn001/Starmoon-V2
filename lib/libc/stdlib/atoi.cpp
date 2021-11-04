#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>

int atoi(const char *nptr)
{
    int result = 0;
    bool neg = false;
    size_t i = 0;
    if(nptr[i] == '-')
    {
        neg = true;
        i++;
    }
    while(isdigit(nptr[i]))
    {
        result *= 10;
        result += (int)nptr[i] - 0x30;
        i++;
    }
    if(neg)
    {
        result = -result;
    }
    return result;
}