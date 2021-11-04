#include <ctype.h>
#include <string.h>

int isxdigit(int c)
{
	if(strchr("0123456789abcdefABCDEF", (char)c) != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
