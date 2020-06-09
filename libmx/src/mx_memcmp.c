#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
	unsigned const char *s11 = s1;
	unsigned const char *s22 = s2;
	
	while(n--) {
		if (*s11 != *s22)
			return *s11 - *s22;
		s11++;
		s22++;
	}
	return 0;
}
