#include <ctype.h>

int isblank(int c)
{
	return ((char)c == ' ' || (char)c == '\t');
}
