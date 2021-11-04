#include <string.h>

void *memmove(void* dest, void* src, size_t count)
{
    unsigned char* dst = (unsigned char*)dest;
    if(src > dest)
    {
        size_t i = 0;
        while(i < count)
        {
            *(dst + i) = *((unsigned char*)src + i);
            i++;
        }
    }
    else
    {
        int i = count - 1;
        while(i > -1)
        {
            *(dst + i) = *((unsigned char*)src + i);
            i--;
        }
    }
    return dest;
}