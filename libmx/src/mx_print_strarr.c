#include "libmx.h"

void mx_print_strarr(char **arr, const char *delim) {
	if (delim != NULL || arr != NULL) {
		for (int i = 0; arr[i] != NULL; i++) {
			mx_printstr(arr[i]);
			if (arr[i+1] != NULL)
				mx_printstr(delim);
			else mx_printchar('\n');
		}
	}
}
