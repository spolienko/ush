#include "libmx.h"

int mx_strncmp(const char *s1, const char *s2, size_t n) {
	int size = n;
	
	if (s1 == NULL && s2 == NULL)
		return 0;
	if (s1 == NULL)
		return *s2;
	if (s2 == NULL)
		return *s1;
	for (int i = 0; i < size; i++) {
		if (s1[i] != s2[i]) {
			return s1[i] - s2[i];
		}
	}
	return 0;
}
