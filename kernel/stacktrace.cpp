#include <kernel/strace.h>
#include <libc/stdio.h>

namespace Debug {

struct stackframe {
    struct stackframe *ebp;
    unsigned long long eip;
};

/****************************************************
 * StackTrace():                                    *
 *  arguments:                                      *
 *      size_t: Max_Frames                          *
 *                                                  *
 *  return type: void                               *
 *                                                  *
 *  function:                                       *
 *      Trace the stack to display what order       *
 *      of functions caused an error.               *
 ****************************************************/
void StackTrace(size_t Max_Frames)
{
    struct stackframe *frame;                           // initialize a pointer to a stack frame structure
    // use inline assembly to set the address pointed to by frame to the address in the EBP register.
    __asm__ __volatile__("mov %%ebp, %0"
                        : "=a"(frame)
                        :);
    int i = 0;                          // initialize an iterator to 0
    // so long as the max number of frames have not been traced and we haven't reached the end of the stack
    printf("Stack Trace:\n");
    while(i < Max_Frames && frame->ebp != NULL)               
    {
        // TODO: Trace the Stack
        printf("EBP: %x\tEIP: %x\n", frame->ebp, frame->eip);
        frame = frame->ebp;             // move to the next frame of the stack.
        i++;                            // increment the iterator.
    }
}

}