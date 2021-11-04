#include <string.h>

char *strpbrk(const char *dest, const char *breakset)
{
    if(dest == NULL || breakset == NULL)
    {
        return NULL;
    }
    int i = 0;
    while(dest[i] != '\0')
    {
        if(strchr(breakset, dest[i]) != NULL)
        {
            return (char*)dest + i;
        }
        else
        {
            i++;
        }
    }
    return NULL;
}