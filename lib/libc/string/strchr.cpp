#include <string.h>

char *strchr(const char *str, int ch)
{
    if(str == NULL)
    {
        return NULL;
    }
    else
    {
        int i = 0;
        if((char)ch == '\0')
        {
            while(str[i] != '\0')
            {
                i++;
            }
            return (char*)str + i;
        }
        else
        {
            while(str[i] != '\0')
            {
                if(str[i] == (char)ch)
                {
                    return (char*)str + i;
                }
                else
                {
                    i++;
                }
            }
        }
    }
    return NULL;
}