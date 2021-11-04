#include <string.h>

void byteSwap(char* loc1, char* loc2)
{
    char temp;
    temp = *loc2;
    *loc2 = *loc1;
    *loc1 = temp;
    return;
}