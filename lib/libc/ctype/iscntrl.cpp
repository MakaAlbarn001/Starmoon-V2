#include <ctype.h>

int iscntrl(int c)
{
	return !isprint(c);
}
