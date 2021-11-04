#include <stdio.h>

int printf(const char * __restrict__ format, ...)
{
    int ret;
    va_list vlist;
    va_start(vlist, format);
    ret = vprintf(format, vlist);
    va_end(vlist);
    return ret;
}