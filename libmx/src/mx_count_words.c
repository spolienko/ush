#include "libmx.h"

int mx_count_words(const char *str, char c) {
	int counter = 1;
	int i = 0;

	if (!str)
		return -1;
	for (; str[i] != '\0'; i++) {
		if (str[i] != c)
			break;
	}
	for (; str[i] != '\0'; i++) {
		if (str[i] == c && str[i+1] != c)
			if (str[i] == c && str[i+1] != '\0')
				counter += 1;
	}
	return counter;
}
