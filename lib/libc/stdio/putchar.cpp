#include <stdio.h>
#if !__STDC_HOSTED__
#include <kernel/tty.h>
#else

#endif

int putchar(int ch) {
#if __STDC_HOSTED__
    return ch;
#else
    kputchar((short)ch);
    return ch;
#endif
}