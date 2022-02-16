#define _VGA_ 1
#include "memloc.h"
#include <kernel/tty.h>
#include <stdint.h>
#include <stddef.h>
#include <libc/string.h>
#include <kernel/system.h>

unsigned short int* txtmemptr = (unsigned short int *)VGA_MEM;      // a pointer to VGA text memory
size_t x_csr = 0;               // a container for the x position of the cursor
size_t y_csr = 0;               // a container for the y position of the cursor
#define X_MAX 80                // defines the maximum number of character columns on the VGA text screen
#define Y_MAX 25                // defines the maximum number of character rows on the VGA text screen
unsigned char txtclr;           // a container for the color of the text in VGA 80x25 text mode.

/************************************************
 * set_text_color():                            *
 *  arguments:                                  *
 *      unsigned character: foreground          *
 *      unsigned character: background          *
 *                                              *
 *  return type: void                           *
 *                                              *
 *  traits:                                     *
 *      inline: contents of function are copied *
 *          into the calling function.          *
 *                                              *
 *  function:                                   *
 *      sets the color of text for VGA text     *
 *      mode.                                   *
 ************************************************/
void inline set_text_color(unsigned char foreground, unsigned char background)
{
    txtclr = (background << 4) | (foreground & 0xF);    // set the upper 4 bits to the background color, and the lower 4 bits to the foreground color.
}

void move_csr();
void scroll();
inline uint16_t vga_entry(unsigned char uc);

/********************************************************
 * vga_entry():                                         *
 *  arguments:                                          *
 *      unsigned character: uc                          *
 *                                                      *
 *  return type: 16-bit unsigned integer                *
 *                                                      *
 *  traits:                                             *
 *      inline                                          *
 *                                                      *
 *  function:                                           *
 *      generates a 16-bit value corresponding to the   *
 *          character to be printed in VGA text mode    *
 *          with the upper 8 bits used for the color    *
 ********************************************************/
inline uint16_t vga_entry(unsigned char uc)
{
    // use the lower 8 bits of uc with txtclr left shifted by 8 to form a 16-bit value for VGA memory
    return (uint16_t)uc | (uint16_t)(txtclr << 8);
    /*  entry = |  txtclr |   uc   |
                | bg | fg |   uc   |
      bit size: | 4b | 4b |   8b   |*/
}

/********************************************************
 * terminal_init():                                     *
 *  arguments: none                                     *
 *  return type: void                                   *
 *  function:                                           *
 *      initialize the VGA text mode terminal           *
 ********************************************************/
void terminal_init()
{
    set_text_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);       // set the text color to green text on black background
    for(size_t y = 0; y < Y_MAX; y++)                       // run through all rows of the VGA text screen
    {
        for(size_t x = 0; x < X_MAX; x++)                   // for each column in a row
        {
            txtmemptr[x + (y*X_MAX)] = vga_entry(' ');      // fill the row with spaces
        }
    }
}

/********************************************************
 * kputchar():                                          *
 *  arguments:                                          *
 *      integer: ch                                      *
 *                                                      *
 *  return type: void                                   *
 *                                                      *
 *  function:                                           *
 *      prints a character to the kernel terminal       *
 ********************************************************/
void kputchar(int ch)
{
    if(ch == '\n')                                          // if the character is a newline character
    {
        x_csr = 0;                                          // set the x position to 0
        scroll();                                           // scroll the screen
    }
    if(ch == '\t')                                          // if the character is a tablature character
    {
        x_csr += 8;                                         // increase the x position by 8
        if(x_csr >= X_MAX)                                  // if the x position is greater than X_MAX
        {
            x_csr = 0;                                      // set the x position to 0
            scroll();                                       // scroll the screen
        }
    }
    // test to see if ch is between ascii characters ' ' and '~' : look up ascii table for more details.
    if(ch >= 0x20 && ch <= 0x7E)                            // if the character is a printable character
    {
        // set the current position of the VGA text screen to the value generated by passing ch to vga_entry()
        txtmemptr[x_csr + (y_csr * X_MAX)] = vga_entry((unsigned char)ch);
        x_csr++;                            // iterate the x position
        if(x_csr >= X_MAX)                  // if the x position is greater than X_MAX
        {
            x_csr = 0;                      // set the x position to 0
            scroll();                       // scroll the screen
        }
    }
    move_csr();                             // update the cursor position.
}

/****************************************************
 * scroll():                                        *
 *  arguments: none                                 *
 *  return type: void                               *
 *  function:                                       *
 *      scrolls the screen by one line, moving the  *
 *      entire screen up if the last line has been  *
 *      reached.                                    *
 ****************************************************/
void scroll()
{
    y_csr++;                                                // iterate the y position
    if(y_csr >= Y_MAX)                                      // if the y position is greater than or equal to Y_MAX
    {
        for(unsigned int y = 0; y < Y_MAX - 1; y++)         // for every row on the screen
        {
            // make each row a copy of the next row
            memmove(txtmemptr + (y * X_MAX), txtmemptr + ((y + 1) * X_MAX), 2 * X_MAX);
        }
        memset(txtmemptr + (X_MAX * 24), 0, 2 * X_MAX);     // insure that the last line is clear.
        y_csr = 24;                                        // set the y position to 24, the last line on the screen.
    }
}

/****************************************************
 * move_csr():                                      *
 *  arguments: none                                 *
 *  return type: void                               *
 *  function:                                       *
 *      updates the position of the on-screen       *
 *      cursor to the current x and y position.     *
 ****************************************************/
void move_csr()
{
    size_t temp = x_csr + (y_csr * X_MAX);      // initialize a container with the x-y position value

    // update the vga controller by updating the register indecies.
    outportb(0x3D4, 14);                                // access index 0xE (cursor high byte) of the index register
    outportb(0x3D5, temp >> 8);                         // fill the appropriate data register with the upper 8 bits of the x-y position
    outportb(0x3D4, 15);                                // access index 0xF (cursor low byte) of the index register
    outportb(0x3D5, temp);                              // fill the data register with the lower 8 bits of the x-y position.
}