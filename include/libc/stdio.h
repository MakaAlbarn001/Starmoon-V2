#ifndef _STDIO_H
#define _STDIO_H 1

#pragma once

#include <stdarg.h>

#define EOF -1

#ifdef __cplusplus
extern "C" {
#endif

int putchar(int ch);
int puts(const char* str);

int printf(const char * __restrict__ format, ...);
int vprintf(const char * __restrict__ format, va_list vlist);

#ifdef __cplusplus
}
#endif
#endif