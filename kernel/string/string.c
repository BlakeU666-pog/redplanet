#include <include/string.h>

void append(char *s, char n) {
	int len = strlen(s);
	s[len] = n;
	s[len + 1] = '\0';
}

void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}

void* memset(void* bufptr, int value, size_t size) {
	unsigned char* buf = (unsigned char*) bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}

char *strcat(char *dest, const char *src) {
  strcpy(dest + strlen (dest), src);
  return dest;
}

int strcmp(const char *p1, const char *p2) {
	const unsigned char *s1 = (const unsigned char *) p1;
  	const unsigned char *s2 = (const unsigned char *) p2;
  	unsigned char c1, c2;
  	do {
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
		if (c1 == '\0')
			return c1 - c2;
	}
	while (c1 == c2);
	return c1 - c2;
}

char *strcpy(char *dest, const char *src) {
	return memcpy(dest, src, strlen(src) + 1);
}

size_t strlen(const char *str)
{
	size_t i = 0;
	while(str[i] != 0)
        i++;
	return i;
}
