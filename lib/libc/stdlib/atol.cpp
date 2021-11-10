#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>

long int atol(const char *nptr)
{
    long int result = 0;
    bool neg = false;
    size_t i = 0;
    while(isspace(nptr[i]))
    {
        i++;                                    
    }
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