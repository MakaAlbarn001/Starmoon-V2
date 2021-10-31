#include <strace.h>

struct stackframe {
    struct *stackframe ebp;
    unsigned long long eip;
}

void StackTrace(size_t Max_Frames)
{
    struct *stackframe frame;
    __volatile__ __asm__("mov %%esp, %0"
                        : "=a"(frame)
                        :);
    int i = 0;
    while(i < Max_Frames)
    {
        // Trace the Stack
        frame = frame->ebp;
        i++;
    }
}