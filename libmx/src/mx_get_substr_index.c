#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
	char *ptr = NULL;
	
	if (!sub || !str)
		return -2;
	ptr = mx_strstr(str,sub);
	if (!ptr) 
		return -1;
	return ptr - str;
}
