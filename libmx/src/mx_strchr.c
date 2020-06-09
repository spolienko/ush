#include "libmx.h"

char *mx_strchr(const char *str, int ch) {
	while(*str) {
		if (*str == ch)
			return (char*)str;
		str++;
	}
	return NULL;
}
