#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
	const char *bg = big;
	const char *lt = little;
	char *b = NULL;
	char *l = NULL;

	if (big_len < little_len || big_len == 0 || little_len == 0)
		return NULL;
	if (!mx_strlen(little))
		return NULL;
	b = mx_strndup(bg, big_len);
	l = mx_strndup(lt, little_len);
	if (mx_strstr(b, l))
		return mx_strstr(b, l);
	return NULL;
}
