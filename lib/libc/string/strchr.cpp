#include <string.h>

/****************************************************
 * strchr():                                        *
 *  arguments:                                      *
 *      constant character pointer: str             *
 *      integer: ch                                 *
 *                                                  *
 *  return type: character pointer                  *
 *                                                  *
 *  function:                                       *
 *      checks str for the presence of character    *
 *      ch. if present, return the address of str   *
 *      plus the offset into str.                   *
 ****************************************************/
char *strchr(const char *str, int ch)
{
    if(str == NULL)                                     // check if the address of str is NULL
    {
        return NULL;                                    // if so, return NULL
    }
    else
    {
        int i = 0;                                      // initialize the offset index to 0
        if((char)ch == '\0')                            // check if ch equals the null terminator
        {
            return (char*)str + strlen(str);            // if so, return the address of str plus it's length
        }
        else
        {
            while(str[i] != '\0')                       // until str + i equals '\0'
            {
                if(str[i] == (char)ch)                  // check if str + i equals ch
                {
                    return (char*)str + i;              // if so, return str + i
                }
                else
                {
                    i++;                                // otherwise, increment the offset index
                }
            }
        }
    }
    return NULL;                                        // return NULL if ch is not present in str
}