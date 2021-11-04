#ifndef _STDLIB_H
#define _STDLIB_H 1

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

#ifdef __cplusplus
}
#endif

#endif