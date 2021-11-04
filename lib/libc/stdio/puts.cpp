#include <stdio.h>
#include <string.h>
#include <stdint.h>

int puts(const char* str)
{
    size_t i = 0;
    while(str[i] != '\0')
    {
        putchar(str[i]);
        i++;
    }
    putchar('\n');
    return i + 1;
}