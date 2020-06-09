#include "libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
	unsigned char *dt = dst;
	unsigned const char *sc = src;

	while(n--)
		*dt++ = *sc++;

	return dst;
}
