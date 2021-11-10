#include <string.h>

/****************************************************************
 * strpbrk():                                                   *
 *  arguments:                                                  *
 *      constant character pointer: str1                        *
 *      constant character pointer: str2                        *
 *                                                              *
 *  return type: character pointer                              *
 *                                                              *
 *  function:                                                   *
 *      searches str1 for the first occurence of any character  *
 *      present in str2, and returns the address.               *
 ****************************************************************/
char *strpbrk(const char *str1, const char *str2)
{
    if(str1 == NULL || str2 == NULL)                    // checks if either str1 or str2 is invalid.
    {
        return NULL;                                    // returns a null address if str1/2 is invalid
    }
    int i = 0;                                          // initialize the offset index to 0
    while(str1[i] != '\0')                              // search until the end of the string.
    {
        if(
            strchr(str2, str1[i])                       // check the current character in str1 to the
                                                        // the contents of str2
            != NULL)                                    // to determine if this is a match
        {
            return (char*)str1 + i;                     // if there is, return the address of str1 plus the offset index
        }
        else
        {
            i++;                                        // otherwise, iterate the offset index
        }
    }
    return NULL;                                        // if there is no match, return NULL.
}