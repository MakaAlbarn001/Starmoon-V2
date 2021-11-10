#include <stdio.h>
#if !__STDC_HOSTED__
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "io.h"
#endif

/****************************************************************
 * vprintf():													*
 *	arguments:													*
 *		restricted constant character pointer: format			*
 *		variable argument list: vlist							*
 *																*
 *	return type: integer										*
 *																*
 *	function:													*
 *		prints a formatted C string to the screen from a given	*
 *		template string and a variable list of arguements to be	*
 *		integrated into the string.								*
 ****************************************************************/
int vprintf(const char * __restrict__ format, va_list vlist)
{
	// if the implementation is freestanding
#if !__STDC_HOSTED__
	char flag = 0;					// initialize a container for the arguement conversion flags
	int precision = -1;				// initialize a container for the arguement conversion precision
	int width = 0;					// initialize a container for the arguement conversion width
	char length;					// initialize a container for the arguement conversion length
	size_t i = 0;					// initialize an offset iterator to 0
	int pad = 0;					// initialize a container for conversion padding size
	size_t print_count = 0;			// initialize a container for counting printed characters.
	union tagValue tagInput;		// initialize a container for inputed arguements.
	while(format[i] != '\0')		// continue printing until the current element of format is a null terminator.
	{
		if(format[i] != '%')		// if the current element of format is not a conversition specifier
		{
			putchar(format[i]);		// print the current element of format to the screen
			print_count++;			// increment the print count.
		}
		else
		{
			i++;						// increment the offset iterator
			// so long as the current element of format is not a conversion specifier or null terminator
			while(strchr(specifiers, format[i]) == NULL && format[i] != '\0')	
			{
				// if the current element is a flag and not a multi-digit number
				if(strchr(flags, format[i]) && !isdigit(format[i-1]))
				{
					switch(format[i])				// case by case check on the current flag value
					{
						case ' ':					// if the flag is a space
							flag += FLAG_SPACE;		// set the space flag bit in flag
							break;					// break the case check
						case '+':					// if the flag is a plus sign
							flag += FLAG_SIGN;		// set the sign flag bit in flag
							break;
						case '#':					// if the flag is a pound
							flag += FLAG_TYPE;		// set the type flag in flag
							break;
						case '0':					// if the flag is a zero
							flag += FLAG_ZERO;		// set the zero flag in flag
							break;
						case '-':					// if the flag is a minus sign
							flag += FLAG_LEFT;		// set the left flag in flag
							break;
					}
					i++; 							// increment the offset iterator
				}
				else if(strchr(lengths, format[i]))  // if the current element of format is a length specifier
				{
					switch(format[i])					// case check the specifier
					{
						case 'h':						// if the length specifier is 'h'
							if(format[i+1] == 'h')		// if the next element is also 'h'
							{
								length = LENGTH_HH;		// set the HH length flag
								i++;					// increment the offset iterator
							}
							else						// otherwise
							{
								length = LENGTH_H;		// the the H length flag
							}
							break;
						case 'l':						// if the length specifier is 'l'
							if(format[i+1] == 'l')		// if the next element is also 'l'
							{
								length = LENGTH_LL;		// set the LL length flag
								i++;					// increment the offset operator
							}
							else						// otherwise
							{
								length = LENGTH_L;		// set the L length flag
							}
							break;
						case 'j':						// if the length specifier is 'j'
							length = LENGTH_J;			// set the J length flag
							break;
						case 'z':						// if the length specifier is 'z'
							length = LENGTH_Z;			// set the Z length flag
							break;
						case 't':						// if the length specifier is 't'
							length = LENGTH_T;			// set the T length flag
							break;
						case 'L':						// if the length specifier is 'L'
							length = LENGTH_LLL;		// set the LLL length flag
							break;
					}
					i++;								// increment the offset iterator
				}
				else if(isdigit(format[i]))		// if the current element of format is a numeric width specifier
				{
					width *= 10;						// multiply the current width by 10
					width += (int)(format[i] - 0x30);		// add the integer value of the element to width
					i++;						// increment the offset iterator
				}
				else if(format[i] == '*')		// if the current element of format is an argument width specifier
				{
					width = va_arg(vlist, int); // set width to the next argument in vlist
					i++;						// increment the offset iterator
				}
				else if(format[i] == '.')		// if the current element of format is a precision marker
				{
					i++;						// increment the offset iterator
					if(format[i] == '*')				// if the current element of format is an arguement specifier
					{
						precision = va_arg(vlist, int);	// set the precision to the next arguement in vlist.
						i++;				// increment the offset iterator
					}
					else if(isdigit(format[i]))		// if the current element of format is a numeric precision specifier
					{
						precision = 0;				// set the current precision to 0
						while(isdigit(format[i]))	// until we reach the last numeric specifier in the current conversion tag
						{
							precision *= 10;			// multiply the current precision by 10
							precision += (int)(format[i] - 0x30);	// add the integer value of the numeric element to precision
							i++;					// increment the offset iterator
						}
					}
					else						// otherwise
					{
						precision = 0;			// set the precision to 0
					}
				}
				else			// any non-flag value in the conversion tag
				{
					break;		// break the loop.
				}
			}
			switch(format[i])	// case check the current element of format
			{
				case 'c':					// it the conversion specifier is 'c'
					tagInput.schar = (char)va_arg(vlist, int);		// get the character from the variable arguement list
					if(flag & FLAG_LEFT)					// if the LEFT flag is set
					{
						putchar(tagInput.schar);			// print the character
						print_count++;						// increment the print count
						width--;							// decrement the width
						while(width > 0)					// so long as the width is greater than zero
						{
							putchar(' ');					// print a space
							print_count++;					// increment the print count
							width--;						// decrement the width
						}
					}
					else									// otherwise
					{
						while(width > 1)					// so long as the width is greater than one
						{
							putchar(' ');					// print a padding space
							print_count++;					// increment the print count
							width--;						// decrement the width
						}
						putchar(tagInput.schar);			// print the character
						print_count++;						// increment the print count
					}
					break;
				case 's':					// if the conversion specifier is 's'
					tagInput.cptr = (char *)va_arg(vlist, int*);		// get the address of the string from vlist
					if(flag & FLAG_LEFT)								// if the Left Flag is set
					{	
						if(precision < 0)								// if precision is less than zero
						{
							if(strlen(tagInput.cptr) < width)			// if the length of the string is less than width
							{
								// set the padding size to set width minus the length of the string
								pad = (size_t)width - strlen(tagInput.cptr);	
								while(*(tagInput.cptr) != '\0')			// untill a null terminator is reached
								{
									putchar(*(tagInput.cptr));			// print the current character of the string
									tagInput.cptr++;					// increment the offset in the string
									print_count++;						// increment the print count
								}
								while(pad > 0)							// until the padding size reaches zero
								{
									putchar(' ');						// print a space
									print_count++;						// increment the print count
									pad--;								// decrement the pad size
								}
							}
							else					// otherwise
							{
								while(*(tagInput.cptr) != '\0')			// until a null terminator is reached
								{
									putchar(*(tagInput.cptr));			// print the current character of the string
									tagInput.cptr++;					// increment the offset in the string
									print_count++;						// increment the print count
								}
							}
						}
						else						// otherwise
						{
							if(strlen(tagInput.cptr) < precision)		// if the length of the string is less than the precision
							{
								pad = width - strlen(tagInput.cptr);	// set pad equal to the width minux the string length
								while(*(tagInput.cptr) != '\0')			// until a null terminator is reached
								{
									putchar(*(tagInput.cptr));			// print the current character of the string
									tagInput.cptr++;					// increment the offset in the string
									print_count++;						// increment the print count
								}
								while(pad > 0)							// while pad is greater than zero
								{
									putchar(' ');						// print a space character
									print_count++;						// increment the print count
									pad--;								// decrement the pad size
								}
							}
							else										// otherwise
							{
								pad = width - precision;				// set pad equal to width minus precision
								while(precision > 0)					// while precision is greater than zero
								{
									putchar(*(tagInput.cptr));			// print the current character of the string
									print_count++;						// increment the print count
									tagInput.cptr++;					// increment the offset within the string
									precision--;						// decrement the precision
								}
								while(pad > 0)							// while pad is greater than zero
								{
									putchar(' ');						// print a space character
									pad--;								// decrement the pad size
									print_count++;						// increment the print count
								}
							}
						}
					}
					else						// otherwiae
					{
						if(precision < 0)			// if the precision is less than zero
						{
							pad = width - strlen(tagInput.cptr);		// set pad equal to width minux the string length
							while(pad > 0)								// while pad is greater than zero
							{
								putchar(' ');							// print a space character
								print_count++;							// increment the print count
								pad--;									// decrement the pad size
							}
							while(*(tagInput.cptr) != '\0')				// until a null terminator is reached
							{
								putchar(*(tagInput.cptr));				// print the current character of the string
								tagInput.cptr++;						// increment the offset within the string
								print_count++;							// increment the print count
							}
						}
						else			// otherwise
						{
							if(strlen(tagInput.cptr) < precision)		// if the length of the string is less than the precision
							{
								pad = width - strlen(tagInput.cptr);		// set pad equal to width minus the length of the string
								while(pad > 0)							// while pad is greater than zero
								{
									putchar(' ');							// print a space character
									print_count++;							// increment the print count
									pad--;									// decrement the print size
								}
								while(*(tagInput.cptr) != '\0')				// until a null terminator is reached
								{
									putchar(*(tagInput.cptr));				// print the current character of the string
									tagInput.cptr++;						// increment the offset within the string
									print_count++;							// increment the print count
								}
							}
							else			// otherwise
							{
								pad = width - precision;					// set pad equal to width minus the precision
								while(pad > 0)								// until pad reaches zero
								{
									putchar(' ');							// print a space character
									print_count++;							// increment the print count
									pad--;									// decrement the pad size
								}
								while(precision > 0)						// while precision is greater than zero
								{
									putchar(*(tagInput.cptr));				// print the current character of the string
									print_count++;							// increment the print count
									tagInput.cptr++;						// increment the offset within the string
									precision--;							// decrement the precision
								}
							}
						}
					}
					break;
				case 'd':
				case 'i':					// if the conversion specifier is 'd' or 'i'
					switch(length)			// case check the length
					{
						case LENGTH_HH:		// if the length is 'HH'
							tagInput.schar = (char)va_arg(vlist, int);	// *A: retrieve the value from vlist
							if(flag & FLAG_SIGN && tagInput.schar >= 0)		// if the value is greater than 0 and the Sign flag is set
							{
								putchar('+');			// print a '+' to the screen
								print_count++;			// increment the print count
								width--;				// decrement the width
							}
							if(tagInput.schar < 0)		// if the number is less than zero
							{
								putchar('-');			// print a '-' to the screen
								tagInput.schar *= -1;	// multiply the number by -1 to make it positive
								print_count++;			// increment the print count
								width--;				// decrement the width
							}
							if(flag & FLAG_SPACE && !(flag & FLAG_SIGN))	// if the Flag is set and the Sign flag is not set
							{
								putchar(' ');		// print a space character
								print_count++;		// increment the print count
								width--;			// decrement the width
							}
							tagInput.cptr = itoa(tagInput.schar, conBuffer, 10); // convert the number into a string in base 10
							break;
						/* All of the other cases are the same with the difference being the size of the number. */
						case LENGTH_H:
							tagInput.sshort = (short)va_arg(vlist, int);
							if(flag & FLAG_SIGN && tagInput.sshort >= 0)
							{
								putchar('+');
								print_count++;
								width--;
							}
							if(tagInput.sshort < 0)
							{
								putchar('-');
								tagInput.sshort *= -1;
								print_count++;
								width--;
							}
							if(flag & FLAG_SPACE && !(flag & FLAG_SIGN))
							{
								putchar(' ');
								print_count++;
								width--;
							}
							tagInput.cptr = itoa(tagInput.sshort, conBuffer, 10);
							break;
						case LENGTH_L:
							tagInput.slong = (long)va_arg(vlist, long);
							if(flag & FLAG_SIGN && tagInput.slong >= 0)
							{
								putchar('+');
								print_count++;
								width--;
							}
							if(tagInput.slong < 0)
							{
								putchar('-');
								tagInput.slong *= -1;
								print_count++;
								width--;
							}
							if(flag & FLAG_SPACE && !(flag & FLAG_SIGN))
							{
								putchar(' ');
								print_count++;
								width--;
							}
							tagInput.cptr = lltoa(tagInput.slong, conBuffer, 10);
							break;
						case LENGTH_LL:
							tagInput.slonglong = (long long)va_arg(vlist, long long);
							if(flag & FLAG_SIGN && tagInput.slonglong >= 0)
							{
								putchar('+');
								print_count++;
								width--;
							}
							if(tagInput.slonglong < 0)
							{
								putchar('-');
								tagInput.slonglong *= -1;
								print_count++;
								width--;
							}
							if(flag & FLAG_SPACE && !(flag & FLAG_SIGN))
							{
								putchar(' ');
								print_count++;
								width--;
							}
							tagInput.cptr = lltoa(tagInput.slonglong, conBuffer, 10);
							break;
						case LENGTH_J:
							tagInput.imax = va_arg(vlist, intmax_t);
							if(flag & FLAG_SIGN && tagInput.imax >= 0)
							{
								putchar('+');
								print_count++;
								width--;
							}
							if(tagInput.imax < 0)
							{
								putchar('-');
								tagInput.imax *= -1;
								print_count++;
								width--;
							}
							if(flag & FLAG_SPACE && !(flag & FLAG_SIGN))
							{
								putchar(' ');
								print_count++;
								width--;
							}
							tagInput.cptr = lltoa(tagInput.imax, conBuffer, 10);
							break;
						case LENGTH_Z:
							tagInput.ssize = va_arg(vlist, long signed int);
							if(flag & FLAG_SIGN && tagInput.ssize >= 0)
							{
								putchar('+');
								print_count++;
								width--;
							}
							if(tagInput.ssize < 0)
							{
								putchar('-');
								tagInput.ssize *= -1;
								print_count++;
								width--;
							}
							if(flag & FLAG_SPACE && !(flag & FLAG_SIGN))
							{
								putchar(' ');
								print_count++;
								width--;
							}
							tagInput.cptr = lltoa(tagInput.ssize, conBuffer, 10);
							break;
						case LENGTH_T:
							tagInput.sptrdiff = va_arg(vlist, ptrdiff_t);
							if(flag & FLAG_SIGN && tagInput.sptrdiff >= 0)
							{
								putchar('+');
								print_count++;
								width--;
							}
							if(tagInput.sptrdiff < 0)
							{
								putchar('-');
								tagInput.sptrdiff *= -1;
								print_count++;
								width--;
							}
							if(flag & FLAG_SPACE && !(flag & FLAG_SIGN))
							{
								putchar(' ');
								print_count++;
								width--;
							}
							tagInput.cptr = lltoa(tagInput.sptrdiff, conBuffer, 10);
							break;
						default:
							tagInput.ssint = va_arg(vlist, int);
							if(flag & FLAG_SIGN && tagInput.ssint >= 0)
							{
								putchar('+');
								print_count++;
								width--;
							}
							if(tagInput.ssint < 0)
							{
								putchar('-');
								tagInput.ssint *= -1;
								print_count++;
								width--;
							}
							if(flag & FLAG_SPACE && !(flag & FLAG_SIGN))
							{
								putchar(' ');
								print_count++;
								width--;
							}
							tagInput.cptr = itoa(tagInput.ssint, conBuffer, 10);
							break;
					
						break;
					}
					if(precision < 0)		// if the precision is less than zero
					{
						pad = width - strlen(tagInput.cptr);	// set the pad size equal to the width minus the string length
						if(flag & FLAG_LEFT)			// if the Left flag is set
						{
							while(*(tagInput.cptr) != '\0')		// until a null terminator is reached
							{
								putchar(*(tagInput.cptr));		// print the current character of the string
								print_count++;					// increment the print count
								tagInput.cptr++;				// increment the offset within the string
							}
							while(pad > 0)					// so long the pad size is greater than zero
							{
								putchar(' ');				// print a space character
								print_count++;				// increment the print count
								pad--;						// decrement the pad size
							}
						}
						else				// otherwise
						{
							while(pad > 0)		// so long as the pad size is greater than zero
							{
								if(flag & FLAG_ZERO)	// if the zero flag is set
								{
									putchar('0');		// print a '0' to the screen
								}
								else		// otherwise
								{
									putchar(' ');		// print a space character
								}
								print_count++;			// increment the print count
								pad--;					// decrement the pad size
							}
							while(*(tagInput.cptr) != '\0')		// until a null terminator is reached
							{
								putchar(*(tagInput.cptr));		// print the current character of the string
								print_count++;					// increment the print count
								tagInput.cptr++;				// increment the offset within the string
							}
						}
					}
					else			// otherwise
					{
						if(strlen(tagInput.cptr) > precision)	// if the string length is greater than the precision
						{
							pad = width - precision;	// set the pad size equal to the width minus the precision
							if(flag & FLAG_LEFT)		// if the Left flag is set
							{
								while(precision > 0)	// so long as the precision is greater than zero
								{
									putchar(*(tagInput.cptr));	// print the current character of the string
									print_count++;				// increment the print count
									tagInput.cptr++;			// increment the offset within the string
									precision--;				// decrement the precision
								}
								while(pad > 0)			// so long as the pad size is greater than zero
								{
									putchar(' ');		// print a space character
									print_count++;		// increment the print count
									pad--;				// decrement the pad size
								}
							}
							else	// otherwise
							{
								while(pad > 0)		// so long as the pad size is greater than zero
								{
									if(flag & FLAG_ZERO)	// if the Zero flag is set
									{
										putchar('0');		// print a '0' to the screen
									}
									else				// otherwise
									{
										putchar(' ');		// print a space character
									}
									print_count++;			// increment the print count
									pad--;					// decrement the pad size
								}
								while(precision > 0)		// so long as the precision is greator than zero
								{
									putchar(*(tagInput.cptr));	// print the current character of the string
									print_count++;				// increment the print count
									precision--;				// decrement the precision
									tagInput.cptr++;			// increment the offset within the string
								}
							}
						}
						else				// otherwise
						{
							pad = width - strlen(tagInput.cptr);	// set the pad size equal to the width minus the string length
							if(flag & FLAG_LEFT)		// if the Left flag is set
							{
								while(*(tagInput.cptr) != '\0')		// until a null terminator is reached
								{
									putchar(*(tagInput.cptr));		// print the current character of the string
									print_count++;					// increment the print count
									tagInput.cptr++;				// increment the offset within the string
								}
								while(pad > 0)				// so long a the pad size is greater than zero
								{
									putchar(' ');			// print a space character
									print_count++;			// increment the print count
									pad--;					// decrement the pad size
								}
							}
							else				// otherwise
							{
								while(pad > 0)		// so long as the pad size is greater than zero
								{
									if(flag & FLAG_ZERO)		// if the zero flag is set
									{
										putchar('0');		// print a '0' to the screen
									}
									else		// otherwise
									{
										putchar(' ');		// print a space character
									}
									print_count++;			// increment the print count
									pad--;					// decrement the pad size
								}
								while(*(tagInput.cptr) != '\0')		// until a null terminator is reached
								{
									putchar(*(tagInput.cptr));		// print the current character of the stirng
									print_count++;					// increment the print count
									tagInput.cptr++;				// increment the offset within the string
								}
							}
						}
					}
					break;
				case 'x':					// if the conversion specifier is 'x'
					switch(length)			// case check the length
					{
						/* check the length flag for the conversion. retrieve the corresponding argument from
							vlist and convert the numeric value into a string with base 16 *//* check the length flag for the conversion. retrieve the corresponding argument from
							vlist and convert the numeric value into a string with base 16 */
						case LENGTH_HH:
							tagInput.cptr = itoa((unsigned char)va_arg(vlist, unsigned int), conBuffer, 16);
							break;
						case LENGTH_H:
							tagInput.cptr = itoa((unsigned short)va_arg(vlist, unsigned int), conBuffer, 16);
							break;
						case LENGTH_L:
							tagInput.cptr = lltoa((unsigned long)va_arg(vlist, unsigned long), conBuffer, 16);
							break;
						case LENGTH_LL:
							tagInput.cptr = lltoa((unsigned long long)va_arg(vlist, unsigned long long), conBuffer, 16);
							break;
						case LENGTH_J:
							tagInput.cptr = lltoa((uintmax_t)va_arg(vlist, uintmax_t), conBuffer, 16);
							break;
						case LENGTH_Z:
							tagInput.cptr = lltoa((size_t)va_arg(vlist, size_t), conBuffer, 16);
							break;
						case LENGTH_T:
							tagInput.cptr = lltoa((unsigned long int)va_arg(vlist, unsigned long int), conBuffer, 16);
							break;
						default:
							tagInput.cptr = itoa(va_arg(vlist, unsigned int), conBuffer, 16);
							break;
					}
					if(flag & FLAG_LEFT)		// if the Left flag is set
					{
						if(precision < 0)		// if the precision is less than zero
						{
							pad = width - strlen(tagInput.cptr);		// set the pad size to the width minus the string length
							if(flag & FLAG_TYPE)			// if the Type flag is set
							{
								putchar('0');				// print a '0' to the screen
								putchar('x');				// print a 'x' to the screen
								print_count += 2;			// increment the print count by 2
								pad -= 2;					// decrement the pad size by 2
							}
							while(*(tagInput.cptr) != '\0')		// until a null terminator is reached
							{
								putchar(*(tagInput.cptr));		// print the current character of the string
								print_count++;					// increment the print count
								tagInput.cptr++;				// increment the offset within the string
							}
							while(pad > 0)						// so long as the pad size is greater than zero
							{
								putchar(' ');					// print a space character
								print_count++;					// increment the print count
								pad--;							// decrement the pad size
							}
						}
						else					// otherwise
						{
							if(strlen(tagInput.cptr) > precision)		// if the string length is greater than the precision
							{
								pad = width - strlen(tagInput.cptr);	// set the pad size equal to the width minus the string length
								if(flag & FLAG_TYPE)					// if the Type flag is set
								{
									putchar('0');						// print a '0' to the screen
									putchar('x');						// print a 'x' to the screen
									pad -= 2;							// decrement the pad size by 2
									print_count += 2;					// increment the print count by 2
								}
								while(*(tagInput.cptr) != '\0')			// until a null terminator is reached
								{
									putchar(*(tagInput.cptr));			// print the current character of the string
									print_count++;						// increment the print count
									tagInput.cptr++;					// increment the offset within the string
								}
								while(pad > 0)							// so long as the pad size is greater than zero
								{
									putchar(' ');						// print a space character
									print_count++;						// increment the print count
									pad--;								// decrement the pad size
								}
							}
							else				// otherwise
							{
								pad = width - precision;				// set the pad size equal to the width minus the precision
								precision -= strlen(tagInput.cptr);		// set the precision equal to itself minus the string length
								if(flag & FLAG_TYPE)					// if the Type flag is set
								{
									putchar('0');						// print a '0' to the screen
									putchar('x');						// print a 'x' to the screen
									pad -= 2;							// decrement the pad size by 2
									print_count += 2;					// increment the print count by 2
								}
								while(precision > 0)					// so long as the precision is greater than zero
								{
									putchar('0');						// print a '0' to the screen
									print_count++;						// increment the print count
									precision--;						// decrement the precision
								}
								while(*(tagInput.cptr) != '\0')			// until a null terminator is reached
								{
									putchar(*(tagInput.cptr));			// print the current character of the string
									print_count++;						// increment the print count
									tagInput.cptr++;					// increment the offset within the string
								}
								while(pad > 0)							// so long as the pad size is greater than zero
								{
									putchar(' ');						// print a space character
									print_count++;						// increment the print count
									pad--;								// decrement the pad size
								}
							}
						}
					}
					else						// otherwise
					{
						if(precision < 0)				// if the precision is less than zero
						{
							pad = width - strlen(tagInput.cptr);		// set the pad size equal to the width minus the sting length							if(flag & FLAG_ZERO)
							if(flag & FLAG_ZERO)		// if the Zero flag is set
							{
								if(flag & FLAG_TYPE)			// if the Type flag is set
								{
									putchar('0');					// print a '0' to the screen
									putchar('x');					// print a 'x' to the screen
									pad -= 2;						// decrement the pad size by 2
									print_count += 2;				// increment the print count by 2
								}
								while(pad > 0)					// so long as the pad size is greater than zero
								{
									putchar('0');				// print a '0' to the screen
									print_count++;				// increment the print count
									pad--;						// decrement the pad size
								}
								while(*(tagInput.cptr) != '\0')		// until a null terminator is reached
								{
									putchar(*(tagInput.cptr));		// print the current character of the string
									print_count++;					// increment the print count
									tagInput.cptr++;				// incremetn the offset within the string
								}
							}
							else							// otherwise
							{
								if(flag & FLAG_TYPE)			// if the Type flag is set
								{
									pad -= 2;					// decrement the pad size by 2
									while(pad > 0)				// so long a the pad size is greater than zero
									{
										putchar(' ');			// print a space character
										print_count++;			// increment the print count
										pad--;					// decrement the pad size
									}
									putchar('0');				// print a '0' to the screen
									putchar('x');				// print a 'x' to the screen
									print_count += 2;			// increment the print count by 2
								}
								else						// otherwise
								{
									while(pad > 0)					// so long a the pad size is greater than zero
									{
										putchar(' ');			// print a space character
										print_count++;			// increment the print count
										pad--;					// decrement the pad size
									}
								}
								while(*(tagInput.cptr) != '\0')		// until a null terminator is reached
								{
									putchar(*(tagInput.cptr));		// print the current character of the string
									print_count++;					// increment the print count
									tagInput.cptr++;				// increment the offset within the string
								}
							}
						}
						else						// otherwise
						{
							if(strlen(tagInput.cptr) > precision)		// if the string length is greater than the precision
							{
								pad = width - strlen(tagInput.cptr);	// set the pad size to the width minus the string length
								if(flag & FLAG_TYPE)					// if the Type flag is set
								{
									pad -= 2;							// decrement the pad size by 2
									while(pad > 0)			// so long as the pad size is greater than zero
									{
										putchar(' ');				// print a space character
										print_count++;				// increment the print count
										pad--;						// decrement the pad size
									}
									putchar('0');						// print a '0' to the screen
									putchar('x');						// print a 'x' to the screen
									print_count += 2;					// increment the print count
								}
								while(*(tagInput.cptr) != '\0')			// until a null terminator is reached
								{
									putchar(*(tagInput.cptr));		// print the current character of the string
									print_count++;					// increment the print count
									tagInput.cptr++;				// increment the offset within the string
								}
							}
							else							// otherwise
							{
								pad = width - precision;			// set the pad size to the width minus the precision
								precision -= strlen(tagInput.cptr);	// decrement the pad size by the length of the string
								if(flag & FLAG_TYPE)		// if the Type flag is set
								{
									pad -= 2;				// decrement the pad size by 2
									while(pad > 0)				// so long as the pad size is greater than zero
									{
										putchar(' ');			// print a space character
										print_count++;			// increment the print count
										pad--;					// decrement the pad size
									}
									putchar('0');				// print a '0' to the screen
									putchar('x');				// print a 'x' to the screen
									print_count += 2;			// increment the print count by 2
								}
								else		// otherwise
								{
									while(pad > 0)			// so long as the pad size is greater than zero
									{
										putchar(' ');		// print a space character
										print_count++;		// increment the print count
										pad--;				// decrement the pad size
									}
								}
								while(precision > 0)		// so long as the precision is greater than zero
								{
									putchar('0');			// print a '0' to the screen
									print_count++;			// increment the print count
									precision--;			// decrement the precision
								}
								while(*(tagInput.cptr) != '\0')		// until a null terminator is reached
								{
									putchar(*(tagInput.cptr));		// print the current character of the string
									print_count++;					// increment the print count
									tagInput.cptr++;				// increment the offset within the string
								}
							}
						}
					}
					break;
				case 'X':					// if the conversion specifier is 'X'
					switch(length)		// case check the length
					{
						/* check the length flag for the conversion. retrieve the corresponding argument from
							vlist and convert the numeric value into a string with base 16 */
						case LENGTH_HH:
							tagInput.cptr = itoa((unsigned char)va_arg(vlist, unsigned int), conBuffer, 16);
							break;
						case LENGTH_H:
							tagInput.cptr = itoa((unsigned short)va_arg(vlist, unsigned int), conBuffer, 16);
							break;
						case LENGTH_L:
							tagInput.cptr = lltoa((unsigned long)va_arg(vlist, unsigned long), conBuffer, 16);
							break;
						case LENGTH_LL:
							tagInput.cptr = lltoa((unsigned long long)va_arg(vlist, unsigned long long), conBuffer, 16);
							break;
						case LENGTH_J:
							tagInput.cptr = lltoa((uintmax_t)va_arg(vlist, uintmax_t), conBuffer, 16);
							break;
						case LENGTH_Z:
							tagInput.cptr = lltoa((size_t)va_arg(vlist, size_t), conBuffer, 16);
							break;
						case LENGTH_T:
							tagInput.cptr = lltoa((unsigned long int)va_arg(vlist, unsigned long int), conBuffer, 16);
							break;
						default:
							tagInput.cptr = itoa(va_arg(vlist, unsigned int), conBuffer, 16);
							break;
					}
					if(flag & FLAG_LEFT)		// if the Left flag is set
					{
						if(precision < 0)		// if the precision is less than zero
						{
							pad = width - strlen(tagInput.cptr);		// set the pad size to the width minus the string length
							if(flag & FLAG_TYPE)			// if the Type flag is set
							{
								putchar('0');				// print a '0' to the screen
								putchar('X');				// print a 'X' to the screen
								print_count += 2;			// increment the print count by 2
								pad -= 2;					// decrement the pad size by 2
							}
							while(*(tagInput.cptr) != '\0')		// until a null terminator is reached
							{
								putchar(toupper(*(tagInput.cptr)));	// print the current character of the string capitalized
								print_count++;						// increment the print count
								tagInput.cptr++;					// increment the offset within the string
							}
							while(pad > 0)			// so long as the pad size is greater than zero
							{
								putchar(' ');		// print a space character
								print_count++;		// increment the print count
								pad--;				// decrement the pad size
							}
						}
						else	// otherwise
						{
							if(strlen(tagInput.cptr) > precision)		// if the string length is greater than the precision
							{
								pad = width - strlen(tagInput.cptr);	// set the pad size to the width minus the string length
								if(flag & FLAG_TYPE)		// if the Type flag is set
								{
									putchar('0');			// print a '0' to the screen
									putchar('X');			// print a 'X' to the screen
									pad -= 2;				// decrement the pad size by 2
									print_count += 2;		// increment the print count by 2
								}
								while(*(tagInput.cptr) != '\0')		// until a null terminator is reached
								{
									putchar(toupper(*(tagInput.cptr)));		// print the current character of the string capitalized
									print_count++;				// increment the print count
									tagInput.cptr++;			// increment the offset within the string
								}
								while(pad > 0)			// so long as the pad size is greater than zero
								{
									putchar(' ');		// print a space character
									print_count++;		// increment the print count
									pad--;				// decrement the pad size
								}
							}
							else		// otherwise
							{
								pad = width - precision;				// set the pad size to the width minus the precision
								precision -= strlen(tagInput.cptr);		// decrement the precision by the string length
								if(flag & FLAG_TYPE)					// if the Type flag is set
								{
									putchar('0');						// print a '0' to the screen
									putchar('X');						// print a 'X' to the screen
									print_count += 2;					// increment the print count by 2
									pad -= 2;							// decrement the pad size by 2
								}
								while(precision > 0)		// so long as the precision is greater tha zero
								{
									putchar('0');			// print a '0' to the screen
									print_count++;			// increment the print count
									precision--;			// decrement the precision
								}
								while(*(tagInput.cptr) != '\0')		// until a null terminator is reached
								{
									putchar(toupper(*(tagInput.cptr)));	// print the current character of the string capitalized
									print_count++;					// increment the print count
									tagInput.cptr++;				// increment the offset within the string
								}
								while(pad > 0)						// so long as the pad size is greater than zero
								{
									putchar(' ');					// print a space character
									print_count++;					// increment the print count
									pad--;							// decrement the pad size
								}
							}
						}
					}
					else		// otherwise
					{
						if(precision < 0)		// if the precision is less than zero
						{
							pad = width - strlen(tagInput.cptr);	// set the pad size equal to the width minus the string length
							if(flag & FLAG_ZERO)			// if the Zero flag is set
							{
								if(flag & FLAG_TYPE)		// if the Type flag is set
								{
									pad -= 2;				// decrement the pad size by 2
									putchar('0');			// print a '0' to the screen
									putchar('X');			// print a 'X' to the screen
									print_count += 2;		// increment the print count by 2
								}
								while(pad > 0)				// so long as the pad size is greater than zero
								{
									putchar('0');			// print a '0' to the screen
									print_count++;			// increment the print count
									pad--;					// decrement the pad size
								}
								while(*(tagInput.cptr) != '\0')		// until a null terminator is reached
								{
									putchar(toupper(*(tagInput.cptr)));		// print the current character of the string capitalized
									print_count++;					// increment the print count
									tagInput.cptr++;				// increment the offset within the string
								}
							}
							else		// otherwise
							{
								if(flag & FLAG_TYPE)	// if the flag type is set
								{
									pad -= 2;			// decrement the pad size by 2
									while(pad > 0)		// so long as the pad size is greater than zero
									{
										putchar(' ');	// print a space character
										print_count++;	// increment the print count
										pad--;			// decrement the pad size
									}
									putchar('0');		// print a '0' to the screen
									putchar('X');		// print a 'X' to the screen
									print_count += 2;	// increment the print count by 2
								}
								else		// otherwise
								{
									while(pad > 0)		// so long as the pad size is greater than zero
									{
										putchar(' ');		// print a space character
										print_count++;		// increment the print count
										pad--;				// decrement the pad size
									}
								}
								while(*(tagInput.cptr) != '\0')		// until a null terminator is reached
								{
									putchar(toupper(*(tagInput.cptr)));	// print the current character of the string capitalized
									print_count++;				// increment the print count
									tagInput.cptr++;			// increment the offset within the string
								}
							}
						}
						else			// otherwise
						{
							if(strlen(tagInput.cptr) > precision)		// if the string length is greater than the precision
							{
								pad = width - strlen(tagInput.cptr);	// set the pad size equal to the width minus the string length
								if(flag & FLAG_TYPE)				// if the Type flag is set
								{
									pad -= 2;						// decrement the pad size by 2
									while(pad > 0)					// so long as the pad size is greater than zero
									{
										putchar(' ');				// print a space character
										print_count++;				// increment the print count
										pad--;						// decrement the pad size
									}
									putchar('0');					// print a '0' to the screen
									putchar('X');					// print a 'X' to the screen
									print_count += 2;				// increment the print count by 2
								}
								while(*(tagInput.cptr) != '\0')		// until a null terminator is reached
								{
									putchar(toupper(*(tagInput.cptr)));	// print the current character of the string capitalized
									print_count++;				// increment the print count
									tagInput.cptr++;			// increment the offset within the string
								}
							}
							else			// otherwise
							{
								pad = width - precision;			// set the pad size to the width minus the precision
								precision -= strlen(tagInput.cptr);		// decrement the precision by the string length
								if(flag & FLAG_TYPE)		// if the Type flag is set
								{
									pad -= 2;		// decrement the pad size by 2
									while(pad > 0)		// so long as the pad size is greater than zero
									{
										putchar(' ');		// print a space character
										print_count++;		// increment the print count
										pad--;				// decrement the pad size
									}
									putchar('0');			// print a '0' to the screen
									putchar('X');			// print a 'X' to the screen
									print_count += 2;		// increment the print count by 2
								}
								else			// otherwise
								{
									while(pad > 0)		// so long as the pad size is greater than zero
									{
										putchar(' ');	// print a space character
										print_count++;	// increment the print count
										pad--;			// decrement the pad size
									}
								}
								while(precision > 0)		// so long as the precision is greater than zero
								{
									putchar('0');			// print a '0' to the screen
									print_count++;			// increment the print count
									precision--;			// decrement the precision
								}
								while(*(tagInput.cptr) != '\0')	// until a null terminator is reached
								{
									putchar(toupper(*(tagInput.cptr)));		// print the current character to the screen capitalized
									print_count++;			// increment the print count
									tagInput.cptr++;		// increment the offset within the string
								}
							}
						}
					}
					break;
				case 'n':					// if the conversion specifier is 'n'
					tagInput.iptr = va_arg(vlist, int*);		// get the pointer address from the variable arguement list
					*(tagInput.iptr) = print_count;				// save the current print count to that address
					break;
				case 'p':					// if the conversion specifier is 'p'
					// get the pointer address from vlist and convert it to a string
					tagInput.cptr = lltoa(va_arg(vlist, unsigned long long), conBuffer, 16);
					putchar('0');			// print a leading '0'
					putchar('x');			// print a leading 'x'
					print_count += 2;		// increment the print count by 2
					while(*(tagInput.cptr) != '\0')		// until the converted string reaches a null terminator
					{
						putchar(toupper(*(tagInput.cptr)));		// print the uppercase form of the string element
						print_count++;							// increment the print count
						tagInput.cptr++;						// increment the string offset
					}
					break;
				case '%':					// if the conversion specifier is '%'
					putchar('%');					// print the percentile character
					print_count++;					// increment the print count
					break;
				case 'u':					// if the conversion specifier is 'u'
					switch(length)			// case check the length
					{
						/* For each case, retrieve a integer-type arguement from vlist,
							then converts it into a string value which is stored in tagInput. */
						case LENGTH_HH:	
							tagInput.cptr = itoa((unsigned char)va_arg(vlist, unsigned int), conBuffer, 10);
							break;
						case LENGTH_H:
							tagInput.cptr = itoa((unsigned short)va_arg(vlist, unsigned int), conBuffer, 10);
							break;
						case LENGTH_L:
							tagInput.cptr = lltoa((unsigned long)va_arg(vlist, unsigned long), conBuffer, 10);
							break;
						case LENGTH_LL:
							tagInput.cptr = lltoa((unsigned long long)va_arg(vlist, unsigned long long), conBuffer, 10);
							break;
						case LENGTH_J:
							tagInput.cptr = lltoa((uintmax_t)va_arg(vlist, uintmax_t), conBuffer, 10);
							break;
						case LENGTH_Z:
							tagInput.cptr = lltoa((size_t)va_arg(vlist, size_t), conBuffer, 10);
							break;
						case LENGTH_T:
							tagInput.cptr = lltoa((unsigned long int)va_arg(vlist, unsigned long int), conBuffer, 10);
							break;
						default:
							tagInput.cptr = itoa(va_arg(vlist, unsigned int), conBuffer, 10);
							break;
					}
					if(precision < 0)				// if the precision is less than zero
					{
						pad = width - strlen(tagInput.cptr);		// set pad equal to the width minus the string length
						if(flag & FLAG_LEFT)						// if the Left Flag is set
						{
							while(*(tagInput.cptr) != '\0')			// until a null terminator is reached
							{
								putchar(*(tagInput.cptr));			// print the current character of the string
								print_count++;						// increment the print count
								tagInput.cptr++;					// increment the offset in the string
							}
							while(pad > 0)							// so long as pad is greater than zero
							{
								putchar(' ');						// print a space character
								print_count++;						// increment the print count
								pad--;								// decrement the pad size
							}
						}
						else										// otherwise
						{
							while(pad > 0)							// until the pad size reaches zero
							{
								if(flag & FLAG_ZERO)				// if the Zero Flag is set
								{
									putchar('0');					// print a '0' to the screen
								}
								else								// otherwise
								{
									putchar(' ');					// print a space character
								}
								print_count++;						// increment the print count
								pad--;								// decrement the pad size
							}
							while(*(tagInput.cptr) != '\0')			// until a null terminator is reached
							{
								putchar(*(tagInput.cptr));			// print the current character of the string
								print_count++;						// increment the print count
								tagInput.cptr++;					// increment the offset within the string
							}
						}
					}
					else			// otherwise
					{
						if(strlen(tagInput.cptr) > precision)		// if the string length is greater than the precision
						{
							pad = width - precision;			// set pad equal to the width minus the precision
							if(flag & FLAG_LEFT)				// if the Left flag is set
							{
								while(precision > 0)			// so long as the precision is greater than zero
								{
									putchar(*(tagInput.cptr));		// print the current character of the string
									print_count++;					// increment the print count
									tagInput.cptr++;				// increment the offset within the string
									precision--;					// decrement the precision
								}
								while(pad > 0)						// so long as the pad size is greater than zero
								{
									putchar(' ');					// print a space character
									print_count++;					// increment the print count
									pad--;							// decrement the pad size
								}
							}
							else			// otherwise
							{
								while(pad > 0)				// so long as the pad size is greater than zero
								{
									if(flag & FLAG_ZERO)		// if the Zero flag is set
									{
										putchar('0');			// print a '0' to the screen
									}
									else						// otherwise
									{
										putchar(' ');			// print a space character
									}
									print_count++;				// increment the print count
									pad--;						// decrement the pad size
								}
								while(precision > 0)			// so long as the precision is greater than zero
								{
									putchar(*(tagInput.cptr));		// print the current character of the string
									print_count++;					// increment the print count
									precision--;					// decrement the precision
									tagInput.cptr++;				// increment the offset within the string
								}
							}
						}
						else				// otherwise
						{
							pad = width - strlen(tagInput.cptr);		// set the pad size equal to the width minus the string length
							if(flag & FLAG_LEFT)					// if the Left flag is set
							{
								while(*(tagInput.cptr) != '\0')			// until a null terminator is reached
								{
									putchar(*(tagInput.cptr));				// print the current character of the string
									print_count++;						// increment the print count
									tagInput.cptr++;					// increment the offset within the string
								}
								while(pad > 0)							// until the pad size reaches zero
								{
									putchar(' ');						// print a space character
									print_count++;						// increment the print count
									pad--;								// decrement the pad size
								}
							}
							else			// otherwise
							{
								while(pad > 0)					// until the pad size reaches zero
								{
									if(flag & FLAG_ZERO)		// if the Zero flag is set
									{
										putchar('0');			// print a '0' to the screen
									}
									else						// otherwise
									{
										putchar(' ');				// print a space character
									}
									print_count++;					// increment the print count
									pad--;							// decrement the pad size
								}	
								while(*(tagInput.cptr) != '\0')			// until a null terminator is reached
								{
									putchar(*(tagInput.cptr));			// print the current character of teh string
									print_count++;					// increment the print count
									tagInput.cptr++;				// increment the offset within the string
								}
							}
						}
					}
					break;
				default:					// if no conversion specifier was detected
					print_count += puts("\nERROR: No conversion specifier supplied!");	// print an error message
					break;
			}
			flag = 0;					// reset the flags
			length = 0;					// reset the length
			precision = -1;				// reset the precision
			width = 0;					// reset the width
		}
		i++;							// increment the offset iterator
	}
	return print_count;		// return the number of characters printed.
#else  // otherwise
// will call vfprintf();
	return 0;		// return 0 for the time being.
#endif
}