#include <kernel/boot.h>
#include <kernel/system.h>
#include <kernel/tty.h>
#include <libc/stdio.h>
#include <libc/stdlib.h>
#include <kernel/paging.h>


/********************************************
 * outportb():                              *
 *  arguments:                              *
 *      unsigned short integer: port        *
 *      unsigned character: val             *
 *                                          *
 *  return type: void                       *
 *                                          *
 *  function:                               *
 *      transmits an 8-bit value through    *
 *      a processor I/O port.               *
 ********************************************/
void outportb(unsigned short port, unsigned char val)
{
    // use inline assembly to place val in the eax register, port in the edx register,
    // then use outb to transmit the value in eax to the port in edx.
    __asm__ __volatile__("outb %0, %1"
                        : : "a"(val), "dN"(port));
}

/********************************************
 * inportb():                               *
 *  arguments:                              *
 *      unsigned short integer: port        *
 *                                          *
 *  return type: unsigned character         *
 *                                          *
 *  function:                               *
 *      recieve an 8-bit value from a       *
 *      processor I/O port                  *
 ********************************************/
unsigned char inportb(unsigned short port)
{
    unsigned char ret;                          // initialize a container for the recieved data.
    // use inline assembly to recieve data in the eax register from the port that was placed in the
    // edx register, and set ret equal to the value in the eax register.
    __asm__ __volatile__("inb %1, %0"
                        : "=a"(ret)
                        : "dN"(port));
    return ret;                                 // return the recieved data.
}

/********************************************
 * main():                                  *
 *  arguments: none                         *
 *  return type: void                       *
 *  traits:                                 *
 *      external "C" linkage - cannot be    *
 *          overloaded or have it's name    *
 *          mangled                         *
 *                                          *
 *  function:                               *
 *      serves as a centerpoint for the     *
 *      kernel functionality. contains      *
 *      an infinite for loop for idling.    *
 ********************************************/
extern "C" void main() {
    set_basic_gdt();                    // set up a basic gdt
    install_IDT();
    terminal_init();                    // initialize the VGA text terminal
    printf("hello\n");                  // print a test message to screen.
    header_trace();
    char *temp1 = (char *)malloc(sizeof(char));
    printf("character temp1: %x\n", temp1);
    short *temp2 = (short *)malloc(sizeof(short));
    printf("short temp2: %x\n", temp2);
    long long *temp3 = (long long*)malloc(sizeof(long long));
    printf("long long temp3: %x\n", temp3);
    free(temp1);
    free(temp2);
    header_trace();
    int* temp4 = (int *)malloc(sizeof(int));
    printf("long long temp 3: %x\n", temp3);
    printf("int temp 4: %x\n", temp4);
    header_trace();
    for(;;);                            // begin the idle for loop.
}