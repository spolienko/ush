#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {
	char *target = mx_strnew(n);
	
	mx_strncpy(target, s1, n);
	return target;
}
