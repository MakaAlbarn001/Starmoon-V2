#include <string.h>

void* memset(void* dest, int ch, size_t count)
{
    if(dest == NULL)
    {
        return NULL;
    }
    unsigned char* dst = (unsigned char*)dest;
    for(size_t i = 0; i < count; i++)
    {
        *(dst + i) = (unsigned char)ch;
    }
    return dest;
}