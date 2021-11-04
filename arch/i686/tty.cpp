#define _VGA_ 1
#include "memloc.h"
#include <kernel/tty.h>
#include <stdint.h>
#include <stddef.h>
#include <libc/string.h>
#include <kernel/system.h>

unsigned short int* txtmemptr = (unsigned short int *)VGA_MEM;
size_t x_csr = 0;
size_t y_csr = 0;
#define X_MAX 80
#define Y_MAX 25
unsigned char txtclr;

void static inline set_text_color(unsigned char foreground, unsigned char background)
{
    txtclr = (background << 4) | (foreground & 0xF);
}

void move_csr();
void scroll();
static inline uint16_t vga_entry(unsigned char uc);

static inline uint16_t vga_entry(unsigned char uc)
{
    return (uint16_t)uc | (uint16_t)(txtclr << 8);
}

void terminal_init()
{
    set_text_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
    for(size_t y = 0; y < Y_MAX; y++)
    {
        for(size_t x = 0; x < X_MAX; x++)
        {
            txtmemptr[x + (y*X_MAX)] = vga_entry(' ');
        }
    }
}

void kputchar(int ch)
{
    if(ch == '\n')
    {
        x_csr = 0;
        scroll();
    }
    if(ch == '\t')
    {
        x_csr += 8;
        if(x_csr >= X_MAX)
        {
            x_csr = 0;
            scroll();
        }
    }
    if(ch >= 0x20 && ch <= 0x7E)
    {
        txtmemptr[x_csr + (y_csr * X_MAX)] = vga_entry((unsigned char)ch);
        x_csr++;
        if(x_csr >= X_MAX)
        {
            x_csr = 0;
            scroll();
        }
    }
    move_csr();
}

void scroll()
{
    y_csr++;
    if(y_csr >= Y_MAX)
    {
        for(unsigned int y = 0; y < Y_MAX - 1; y++)
        {
            memcpy(txtmemptr + (y * X_MAX), txtmemptr + ((y + 1) * X_MAX), X_MAX);
        }
        y_csr = 24;
    }
}

void move_csr()
{
    size_t temp = x_csr + (y_csr * X_MAX);

    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}