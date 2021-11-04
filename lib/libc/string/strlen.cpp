#include <string.h>

int strlen(const char* str)
{
    int i = 1;
    while(str[i - 1] != '\0')
    {
        i++;
    }
    return i - 1;
}