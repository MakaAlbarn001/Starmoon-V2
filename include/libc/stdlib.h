#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <stddef.h>

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

char *itoa(int num, char *str, int base);
char *ltoa(long int num, char *str, int base);
char *lltoa(long long int num, char *str, int base);

int atoi(const char *nptr);
long int atol(const char *nptr);
long long int atoll(const char *nptr);

void *malloc(size_t size);
void free(void *addr);

void header_trace();

#ifdef __cplusplus
}
#endif

#endif