#include <ctype.h>

int islower(int c)
{
	if(c >= 0x61 && c <= 0x7a)
	{
		return true;
	}
	else
	{
		return false;
	}
}
