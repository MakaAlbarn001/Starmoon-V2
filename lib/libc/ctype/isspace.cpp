#include <ctype.h>
#include <string.h>

int isspace(int c)
{
	if(strchr(" \f\n\r\t\v",(char)c) != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
