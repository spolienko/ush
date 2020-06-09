#include "libmx.h"

char *mx_strdup(const char *str) {
	if (str) {
		int len = mx_strlen(str);
		char *target = mx_strnew(len);

		for (int i = 0; i < len; i++) {
			target[i] = str[i];
			target[i+1] = '\0';
		}
		return target;
	}
	return NULL;
}
