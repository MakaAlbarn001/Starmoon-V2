#if defined(_VGA_)
#define VGA_COLOR_BLACK 0x0
#define VGA_COLOR_MAROON 0x1
#define VGA_COLOR_GREEN 0x2
#define VGA_COLOR_OLIVE 0x3
#define VGA_COLOR_NAVY 0x4
#define VGA_COLOR_PURPLE 0x5
#define VGA_COLOR_TEAL 0x6
#define VGA_COLOR_SILVER 0x7
#define VGA_COLOR_GREY 0x8
#define VGA_COLOR_RED 0x9
#define VGA_COLOR_LIME 0xA
#define VGA_COLOR_YELLOW 0xB
#define VGA_COLOR_BLUE 0xC
#define VGA_COLOR_FUCHSIA 0xD
#define VGA_COLOR_AQUA 0xE
#define VGA_COLOR_WHITE 0xF
#endif

void static inline set_text_color(unsigned char foreground, unsigned char background);
void kputchar(int ch);
void terminal_init();