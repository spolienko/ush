#include "libmx.h"

char *mx_strnew(const int size) {
	char *target = NULL;

	if (size < 0)
		return NULL;
	target = malloc((size + 1) * sizeof(char));
	if (target == NULL)
		return NULL;
	for (int i = 0; i < size + 1; i++) {
		target[i] = '\0';
	}
	return target;
}
