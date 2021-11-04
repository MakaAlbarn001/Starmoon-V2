#ifndef __IO_H
#define __IO_H 1

#define __need_wint_t 1

#include <stddef.h>
#include <stdint.h>

#pragma once

#define FLAG_LEFT   0x01 // '-'
#define FLAG_SIGN   0x02 // '+'
#define FLAG_SPACE  0x04 // ' '
#define FLAG_TYPE   0x08 // '#'
#define FLAG_ZERO   0x10 // '0'

#define LENGTH_HH   0x01
#define LENGTH_H    0x02
#define LENGTH_L    0x03
#define LENGTH_LL   0x04
#define LENGTH_J    0x05
#define LENGTH_Z    0x06
#define LENGTH_T    0x07
#define LENGTH_LLL  0x08

const char* specifiers = "%ncpsidouxX"; // add later: fFeEgGaA
const char* lengths = "hljztL";
const char* flags = " +0#-";

char conBuffer[66] = {'\0'};

union tagValue {
    unsigned char uchar;
    signed char schar;
    unsigned short int unshort;
    signed short int sshort;
    unsigned int unint;
    signed int ssint;
    unsigned long int ulong;
    signed long int slong;
    unsigned long long int ulonglong;
    signed long long int slonglong;
    void *vptr;
    char *cptr;
    int *iptr;
    uintmax_t uimax;
    intmax_t imax;
    size_t usize;
    long signed int ssize;
    ptrdiff_t sptrdiff;
    long unsigned int uptrdiff;
    double dbl;
    long double ldbl;
    wchar_t wchar;
    wint_t* wintptr;
};

#endif