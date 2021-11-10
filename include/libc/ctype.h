#ifndef __CTYPE_H
#define __CTYPE_H 1

#pragma once

#if __cplusplus
extern "C" {
#endif

/* the isxxxx() functions test the status of a input character
    by testing what the appropriate ascii range it falls into.*/

int isalnum(int c);
int isalpha(int c);
int isblank(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);

/* the tolower/toupper() functions convert the a-z ascii characters
    to lowercase or uppercase respectively.*/
int tolower(int c);
int toupper(int c);

#if __cplusplus
}
#endif
#endif