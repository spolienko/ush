#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
	unsigned char c1 = c;
	unsigned const char *s1 = s;

	while(*s1 && n--) {
		if (*s1 == c1)
			return (char*)s1;
			s1++;
		}
	return NULL;
}
