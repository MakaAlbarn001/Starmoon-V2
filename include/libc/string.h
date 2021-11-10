#ifndef _STRING_H
#define _STRING_H 1

#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t strlen(const char* str);
void strrev(char* str);
char *strchr(const char *str, int ch);
char *strpbrk(const char  * str1, const char *str2);

void* memset(void *dest, int ch, size_t count);
void* memmove(void *dest, const void *src, size_t count);
void* memcpy(void* __restrict__ dest, const void* __restrict__ src, size_t count);

void byteSwap(char* loc1, char* loc2);
void shortSwap(short* loc1, short* loc2);
void intSwap(int* loc1, int* loc2);
void longSwap(long* loc1, long* loc2);

#ifdef __cplusplus
}
#endif
#endif