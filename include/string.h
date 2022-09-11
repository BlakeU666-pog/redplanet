#ifndef __STRING_H
#define __STRING_H

#include <stddef.h>

size_t strlen(const char *str);
char *strcat(char *dest, const char *src);
void* memcpy(void* dstptr, const void* srcptr, size_t size);
char *strcpy(char *dest, const char *src);
void* memset(void* bufptr, int value, size_t size);
int strcmp(const char *p1, const char *p2);
void append(char *s, char n);

#endif
