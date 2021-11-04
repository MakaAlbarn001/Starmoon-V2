#include <string.h>

void* memcpy(void* __restrict__ dest, const void* __restrict__ src, size_t count)
{
    if((char *)dest + count > (char *)src || (char *)src + count > (char *)dest)
    {
        return (void *)src;
    }
    unsigned char* dst = (unsigned char*)dest;
    int i = count - 1;
    while(i > -1)
    {
        *(dst + i) = *((unsigned char*)src + i);
        i--;
    }
    return dest;
}