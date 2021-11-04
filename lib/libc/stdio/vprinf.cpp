#include <stdio.h>
#if !__STDC_HOSTED__
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "io.h"
#endif

int vprintf(const char * __restrict__ format, va_list vlist)
{
#if !__STDC_HOSTED__
    char flag = 0;
    int precision = -1;
    int width = 0;
    char length;
    size_t i = 0;
    int pad = 0;
    size_t print_count = 0;
    union tagValue tagInput;
    while(format[i] != '\0')
    {
        if(format[i] != '%')
        {
            putchar(format[i]);
            print_count++;
        }
        else
        {
            i++;
            while(strchr(specifiers, format[i]) == NULL && format[i] != '\0')
            {
                if(strchr(flags, format[i]) && !isdigit(format[i-1]))
                {
                    switch(format[i])
                    {
                        case ' ':
                            flag += FLAG_SPACE;
                            break;
                        case '+':
                            flag += FLAG_SIGN;
                            break;
                        case '#':
                            flag += FLAG_TYPE;
                            break;
                        case '0':
                            flag += FLAG_ZERO;
                            break;
                        case '-':
                            flag += FLAG_LEFT;
                            break;
                    }
                    i++;
                }
                else if(strchr(lengths, format[i]))
                {
                    switch(format[i])
                    {
                        case 'h':
                            if(format[i+1] == 'h')
                            {
                                length = LENGTH_HH;
                                i++;
                            }
                            else
                            {
                                length = LENGTH_H;
                            }
                            break;
                        case 'l':
                            if(format[i+1] == 'l')
                            {
                                length = LENGTH_LL;
                                i++;
                            }
                            else
                            {
                                length = LENGTH_L;
                            }
                            break;
                        case 'j':
                            length = LENGTH_J;
                            break;
                        case 'z':
                            length = LENGTH_Z;
                            break;
                        case 't':
                            length = LENGTH_T;
                            break;
                        case 'L':
                            length = LENGTH_LLL;
                            break;
                    }
                    i++;
                }
                else if(isdigit(format[i]))
                {
                    width *= 10;
                    width += (int)(format[i] - 0x30);
                    i++;
                }
                else if(format[i] == '*')
                {
                    width = va_arg(vlist, int);
                    i++;
                }
                else if(format[i] == '.')
                {
                    i++;
                    if(format[i] == '*')
                    {
                        precision = va_arg(vlist, int);
                        i++;
                    }
                    else if(isdigit(format[i]))
                    {
                        precision = 0;
                        while(isdigit(format[i]))
                        {
                            precision *= 10;
                            precision += (int)(format[i] - 0x30);
                            i++;
                        }
                    }
                    else
                    {
                        precision = 0;
                    }
                }
            }
            switch(format[i])
            {
                case 'c':
                    tagInput.schar = (char)va_arg(vlist, int);
                    if(flag & FLAG_LEFT)
                    {
                        putchar(tagInput.schar);
                        print_count++;
                        width--;
                        while(width > 0)
                        {
                            putchar(' ');
                            print_count++;
                            width--;
                        }
                    }
                    else
                    {
                        while(width > 1)
                        {
                            putchar(' ');
                            print_count++;
                            width--;
                        }
                        putchar(tagInput.schar);
                        print_count++;
                    }
                    break;
                case 's':
                    tagInput.cptr = (char *)va_arg(vlist, int*);
                    if(flag & FLAG_LEFT)
                    {
                        if(precision < 0)
                        {
                            if(strlen(tagInput.cptr) < width)
                            {
                                pad = (size_t)width - strlen(tagInput.cptr);
                                while(*(tagInput.cptr) != '\0')
                                {
                                    putchar(*(tagInput.cptr));
                                    tagInput.cptr++;
                                    print_count++;
                                }
                                while(pad > 0)
                                {
                                    putchar(' ');
                                    print_count++;
                                }
                            }
                            else
                            {
                                while(*(tagInput.cptr) != '\0')
                                {
                                    putchar(*(tagInput.cptr));
                                    tagInput.cptr++;
                                    print_count++;
                                }
                            }
                        }
                        else
                        {
                            if(strlen(tagInput.cptr) < precision)
                            {
                                pad = width - strlen(tagInput.cptr);
                                while(*(tagInput.cptr) != '\0')
                                {
                                    putchar(*(tagInput.cptr));
                                    tagInput.cptr++;
                                    print_count++;
                                }
                                while(pad > 0)
                                {
                                    putchar(' ');
                                    print_count++;
                                    pad--;
                                }
                            }
                            else
                            {
                                pad = width - precision;
                                while(precision > 0)
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    tagInput.cptr++;
                                    precision--;
                                }
                                while(pad > 0)
                                {
                                    putchar(' ');
                                    pad--;
                                    print_count++;
                                }
                            }
                        }
                    }
                    else
                    {
                        if(precision < 0)
                        {
                            pad = width - strlen(tagInput.cptr);
                            while(pad > 0)
                            {
                                putchar(' ');
                                print_count++;
                            }
                            while(*(tagInput.cptr) != '\0')
                            {
                                putchar(*(tagInput.cptr));
                                tagInput.cptr++;
                                print_count++;
                            }
                        }
                        else
                        {
                            if(strlen(tagInput.cptr) < precision)
                            {
                                pad = width - strlen(tagInput.cptr);
                                while(pad > 0)
                                {
                                    putchar(' ');
                                    print_count++;
                                    pad--;
                                }
                                while(*(tagInput.cptr) != '\0')
                                {
                                    putchar(*(tagInput.cptr));
                                    tagInput.cptr++;
                                    print_count++;
                                }
                            }
                            else
                            {
                                pad = width - precision;
                                while(pad > 0)
                                {
                                    putchar(' ');
                                    print_count++;
                                    pad--;
                                }
                                while(precision > 0)
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    tagInput.cptr++;
                                    precision--;
                                }
                            }
                        }
                    }
                    break;
                case 'd':
                case 'i':
                    switch(length)
                    {
                        case LENGTH_HH:
                            tagInput.schar = (char)va_arg(vlist, int);
                            if(flag & FLAG_SIGN && tagInput.schar >= 0)
                            {
                                putchar('+');
                                print_count++;
                                width--;
                            }
                            if(tagInput.schar < 0)
                            {
                                putchar('-');
                                tagInput.schar *= -1;
                                print_count++;
                                width--;
                            }
                            if(flag & FLAG_SPACE && !(flag & FLAG_SIGN))
                            {
                                putchar(' ');
                                print_count++;
                                width--;
                            }
                            tagInput.cptr = itoa(tagInput.schar, conBuffer, 10);
                            break;
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
                    if(precision < 0)
                    {
                        pad = width - strlen(tagInput.cptr);
                        if(flag & FLAG_LEFT)
                        {
                            while(*(tagInput.cptr) != '\0')
                            {
                                putchar(*(tagInput.cptr));
                                print_count++;
                                tagInput.cptr++;
                            }
                            while(pad > 0)
                            {
                                putchar(' ');
                                print_count++;
                                pad--;
                            }
                        }
                        else
                        {
                            while(pad > 0)
                            {
                                if(flag & FLAG_ZERO)
                                {
                                    putchar('0');
                                }
                                else
                                {
                                    putchar(' ');
                                }
                                print_count++;
                                pad--;
                            }
                            while(*(tagInput.cptr) != '\0')
                            {
                                putchar(*(tagInput.cptr));
                                print_count++;
                                tagInput.cptr++;
                            }
                        }
                    }
                    else
                    {
                        if(strlen(tagInput.cptr) > precision)
                        {
                            pad = width - precision;
                            if(flag & FLAG_LEFT)
                            {
                                while(precision > 0)
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    tagInput.cptr++;
                                    precision--;
                                }
                                while(pad > 0)
                                {
                                    putchar(' ');
                                    print_count++;
                                    pad--;
                                }
                            }
                            else
                            {
                                while(pad > 0)
                                {
                                    if(flag & FLAG_ZERO)
                                    {
                                        putchar('0');
                                    }
                                    else
                                    {
                                        putchar(' ');
                                    }
                                    print_count++;
                                    pad--;
                                }
                                while(precision > 0)
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    precision--;
                                    tagInput.cptr++;
                                }
                            }
                        }
                        else
                        {
                            pad = width - strlen(tagInput.cptr);
                            if(flag & FLAG_LEFT)
                            {
                                while(*(tagInput.cptr) != '\0')
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    tagInput.cptr++;
                                }
                                while(pad > 0)
                                {
                                    putchar(' ');
                                    print_count++;
                                    pad--;
                                }
                            }
                            else
                            {
                                while(pad > 0)
                                {
                                    if(flag & FLAG_ZERO)
                                    {
                                        putchar('0');
                                    }
                                    else
                                    {
                                        putchar(' ');
                                    }
                                    print_count++;
                                    pad--;
                                }
                                while(*(tagInput.cptr) != '\0')
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    tagInput.cptr++;
                                }
                            }
                        }
                    }
                    break;
                case 'x':
                    switch(length)
                    {
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
                    if(flag & FLAG_LEFT)
                    {
                        if(precision < 0)
                        {
                            pad = width - strlen(tagInput.cptr);
                            if(flag & FLAG_TYPE)
                            {
                                putchar('0');
                                putchar('x');
                                print_count += 2;
                                pad -= 2;
                            }
                            while(*(tagInput.cptr) != '\0')
                            {
                                putchar(*(tagInput.cptr));
                                print_count++;
                                tagInput.cptr++;
                            }
                            while(pad > 0)
                            {
                                putchar(' ');
                                print_count++;
                                pad--;
                            }
                        }
                        else
                        {
                            if(strlen(tagInput.cptr) > precision)
                            {
                                pad = width - strlen(tagInput.cptr);
                                if(flag & FLAG_TYPE)
                                {
                                    putchar('0');
                                    putchar('x');
                                    pad -= 2;
                                    print_count += 2;
                                }
                                while(*(tagInput.cptr) != '\0')
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    tagInput.cptr++;
                                }
                                while(pad > 0)
                                {
                                    putchar(' ');
                                    print_count++;
                                    pad--;
                                }
                            }
                            else
                            {
                                pad = width - precision;
                                precision -= strlen(tagInput.cptr);
                                if(flag & FLAG_TYPE)
                                {
                                    putchar('0');
                                    putchar('x');
                                    pad -= 2;
                                }
                                while(precision > 0)
                                {
                                    putchar('0');
                                    print_count++;
                                    precision--;
                                }
                                while(*(tagInput.cptr) != '\0')
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    tagInput.cptr++;
                                }
                                while(pad > 0)
                                {
                                    putchar(' ');
                                    print_count++;
                                    pad--;
                                }
                            }
                        }
                    }
                    else
                    {
                        if(precision < 0)
                        {
                            pad = width - strlen(tagInput.cptr);
                            if(flag & FLAG_ZERO)
                            {
                                if(flag & FLAG_TYPE)
                                {
                                    putchar('0');
                                    putchar('x');
                                    pad -= 2;
                                    print_count += 2;
                                }
                                while(pad > 0)
                                {
                                    putchar('0');
                                    print_count++;
                                    pad--;
                                }
                                while(*(tagInput.cptr) != '\0')
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    tagInput.cptr++;
                                }
                            }
                            else
                            {
                                if(flag & FLAG_TYPE)
                                {
                                    pad -= 2;
                                    while(pad > 0)
                                    {
                                        putchar(' ');
                                        print_count++;
                                        pad--;
                                    }
                                    putchar('0');
                                    putchar('x');
                                    print_count += 2;
                                }
                                else
                                {
                                    while(pad > 0)
                                    {
                                        putchar(' ');
                                        print_count++;
                                        pad--;
                                    }
                                }
                                while(*(tagInput.cptr) != '\0')
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    tagInput.cptr++;
                                }
                            }
                        }
                        else
                        {
                            if(strlen(tagInput.cptr) > precision)
                            {
                                pad = width - strlen(tagInput.cptr);
                                if(flag & FLAG_TYPE)
                                {
                                    putchar('0');
                                    putchar('x');
                                    pad -= 2;
                                    print_count += 2;
                                }
                                while(*(tagInput.cptr) != '\0')
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    tagInput.cptr++;
                                }
                                while(pad > 0)
                                {
                                    putchar(' ');
                                    print_count++;
                                    pad--;
                                }
                            }
                            else
                            {
                                pad = width - precision;
                                precision -= strlen(tagInput.cptr);
                                if(flag & FLAG_TYPE)
                                {
                                    pad -= 2;
                                    while(pad > 0)
                                    {
                                        putchar(' ');
                                        print_count++;
                                        pad--;
                                    }
                                    putchar('0');
                                    putchar('x');
                                    print_count += 2;
                                }
                                else
                                {
                                    while(pad > 0)
                                    {
                                        putchar(' ');
                                        print_count++;
                                        pad--;
                                    }
                                }
                                while(precision > 0)
                                {
                                    putchar('0');
                                    print_count++;
                                    precision--;
                                }
                                while(*(tagInput.cptr) != '\0')
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    tagInput.cptr++;
                                }
                            }
                        }
                    }
                    break;
                case 'X':
                    switch(length)
                    {
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
                    if(flag & FLAG_LEFT)
                    {
                                if(precision < 0)
                                {
                                    pad = width - strlen(tagInput.cptr);
                                    if(flag & FLAG_TYPE)
                                    {
                                        putchar('0');
                                        putchar('X');
                                        print_count += 2;
                                        pad -= 2;
                                    }
                                    while(*(tagInput.cptr) != '\0')
                                    {
                                        putchar(toupper(*(tagInput.cptr)));
                                        print_count++;
                                        tagInput.cptr++;
                                    }
                                    while(pad > 0)
                                    {
                                        putchar(' ');
                                        print_count++;
                                        pad--;
                                    }
                                }
                                else
                                {
                                    if(strlen(tagInput.cptr) > precision)
                                    {
                                        pad = width - strlen(tagInput.cptr);
                                        if(flag & FLAG_TYPE)
                                        {
                                            putchar('0');
                                            putchar('X');
                                            pad -= 2;
                                            print_count += 2;
                                        }
                                        while(*(tagInput.cptr) != '\0')
                                        {
                                            putchar(toupper(*(tagInput.cptr)));
                                            print_count++;
                                            tagInput.cptr++;
                                        }
                                        while(pad > 0)
                                        {
                                            putchar(' ');
                                            print_count++;
                                            pad--;
                                        }
                                    }
                                    else
                                    {
                                        pad = width - precision;
                                        precision -= strlen(tagInput.cptr);
                                        if(flag & FLAG_TYPE)
                                        {
                                            putchar('0');
                                            putchar('X');
                                            pad -= 2;
                                        }
                                        while(precision > 0)
                                        {
                                            putchar('0');
                                            print_count++;
                                            precision--;
                                        }
                                        while(*(tagInput.cptr) != '\0')
                                        {
                                            putchar(toupper(*(tagInput.cptr)));
                                            print_count++;
                                            tagInput.cptr++;
                                        }
                                        while(pad > 0)
                                        {
                                            putchar(' ');
                                            print_count++;
                                            pad--;
                                        }
                                    }
                                }
                    }
                    else
                    {
                                if(precision < 0)
                                {
                                    pad = width - strlen(tagInput.cptr);
                                    if(flag & FLAG_ZERO)
                                    {
                                        if(flag & FLAG_TYPE)
                                        {
                                            putchar('0');
                                            putchar('X');
                                            pad -= 2;
                                            print_count += 2;
                                        }
                                        while(pad > 0)
                                        {
                                            putchar('0');
                                            print_count++;
                                            pad--;
                                        }
                                        while(*(tagInput.cptr) != '\0')
                                        {
                                            putchar(toupper(*(tagInput.cptr)));
                                            print_count++;
                                            tagInput.cptr++;
                                        }
                                    }
                                    else
                                    {
                                        if(flag & FLAG_TYPE)
                                        {
                                            pad -= 2;
                                            while(pad > 0)
                                            {
                                                putchar(' ');
                                                print_count++;
                                                pad--;
                                            }
                                            putchar('0');
                                            putchar('X');
                                            print_count += 2;
                                        }
                                        else
                                        {
                                            while(pad > 0)
                                            {
                                                putchar(' ');
                                                print_count++;
                                                pad--;
                                            }
                                        }
                                        while(*(tagInput.cptr) != '\0')
                                        {
                                            putchar(toupper(*(tagInput.cptr)));
                                            print_count++;
                                            tagInput.cptr++;
                                        }
                                    }
                                }
                                else
                                {
                                    if(strlen(tagInput.cptr) > precision)
                                    {
                                        pad = width - strlen(tagInput.cptr);
                                        if(flag & FLAG_TYPE)
                                        {
                                            putchar('0');
                                            putchar('X');
                                            pad -= 2;
                                            print_count += 2;
                                        }
                                        while(*(tagInput.cptr) != '\0')
                                        {
                                            putchar(toupper(*(tagInput.cptr)));
                                            print_count++;
                                            tagInput.cptr++;
                                        }
                                        while(pad > 0)
                                        {
                                            putchar(' ');
                                            print_count++;
                                            pad--;
                                        }
                                    }
                                    else
                                    {
                                        pad = width - precision;
                                        precision -= strlen(tagInput.cptr);
                                        if(flag & FLAG_TYPE)
                                        {
                                            pad -= 2;
                                            while(pad > 0)
                                            {
                                                putchar(' ');
                                                print_count++;
                                                pad--;
                                            }
                                            putchar('0');
                                            putchar('X');
                                            print_count += 2;

                                        }
                                        else
                                        {
                                            while(pad > 0)
                                            {
                                                putchar(' ');
                                                print_count++;
                                                pad--;
                                            }
                                        }
                                        while(precision > 0)
                                        {
                                            putchar('0');
                                            print_count++;
                                            precision--;
                                        }
                                        while(*(tagInput.cptr) != '\0')
                                        {
                                            putchar(toupper(*(tagInput.cptr)));
                                            print_count++;
                                            tagInput.cptr++;
                                        }
                                    }
                                }
                    }
                    break;
                case 'n':
                    tagInput.iptr = va_arg(vlist, int*);
                    *(tagInput.iptr) = print_count;
                    break;
                case 'p':
                    tagInput.cptr = lltoa(va_arg(vlist, unsigned long long), conBuffer, 16);
                    putchar('0');
                    putchar('x');
                    print_count += 2;
                    while(*(tagInput.cptr) != '\0')
                    {
                        putchar(toupper(*(tagInput.cptr)));
                        print_count++;
                        tagInput.cptr++;
                    }
                    break;
                case '%':
                    putchar('%');
                    print_count++;
                    break;
                case 'u':
                    switch(length)
                    {
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
                    if(precision < 0)
                    {
                        pad = width - strlen(tagInput.cptr);
                        if(flag & FLAG_LEFT)
                        {
                            while(*(tagInput.cptr) != '\0')
                            {
                                putchar(*(tagInput.cptr));
                                print_count++;
                                tagInput.cptr++;
                            }
                            while(pad > 0)
                            {
                                putchar(' ');
                                print_count++;
                                pad--;
                            }
                        }
                        else
                        {
                            while(pad > 0)
                            {
                                if(flag & FLAG_ZERO)
                                {
                                    putchar('0');
                                }
                                else
                                {
                                    putchar(' ');
                                }
                                print_count++;
                                pad--;
                            }
                            while(*(tagInput.cptr) != '\0')
                            {
                                putchar(*(tagInput.cptr));
                                print_count++;
                                tagInput.cptr++;
                            }
                        }
                    }
                    else
                    {
                        if(strlen(tagInput.cptr) > precision)
                        {
                            pad = width - precision;
                            if(flag & FLAG_LEFT)
                            {
                                while(precision > 0)
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    tagInput.cptr++;
                                    precision--;
                                }
                                while(pad > 0)
                                {
                                    putchar(' ');
                                    print_count++;
                                    pad--;
                                }
                            }
                            else
                            {
                                while(pad > 0)
                                {
                                    if(flag & FLAG_ZERO)
                                    {
                                        putchar('0');
                                    }
                                    else
                                    {
                                        putchar(' ');
                                    }
                                    print_count++;
                                    pad--;
                                }
                                while(precision > 0)
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    precision--;
                                    tagInput.cptr++;
                                }
                            }
                        }
                        else
                        {
                            pad = width - strlen(tagInput.cptr);
                            if(flag & FLAG_LEFT)
                            {
                                while(*(tagInput.cptr) != '\0')
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    tagInput.cptr++;
                                }
                                while(pad > 0)
                                {
                                    putchar(' ');
                                    print_count++;
                                    pad--;
                                }
                            }
                            else
                            {
                                while(pad > 0)
                                {
                                    if(flag & FLAG_ZERO)
                                    {
                                        putchar('0');
                                    }
                                    else
                                    {
                                        putchar(' ');
                                    }
                                    print_count++;
                                    pad--;
                                }
                                while(*(tagInput.cptr) != '\0')
                                {
                                    putchar(*(tagInput.cptr));
                                    print_count++;
                                    tagInput.cptr++;
                                }
                            }
                        }
                    }
                    break;
                default:
                    print_count += puts("\nERROR: No conversion specifier supplied!");
                    break;
            }
            flag = 0;
            length = '\0';
            precision = -1;
            width = 0;
        }
        i++;
    }
    return print_count;
#else
// will call vfprintf();
    return 0;
#endif
}