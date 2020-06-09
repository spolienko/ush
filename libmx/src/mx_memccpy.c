#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
	char *dt = dst;
	const char *sc = src;

	while (n > 0) {
		*dt = *sc;
		if (*dt == c) {
			dt++;
			return dt;
		}
		dt++;
		sc++;
		n--;
	}
	return NULL;
}
