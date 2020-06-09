#include "libmx.h"

void mx_str_reverse(char *s) {
	int j = mx_strlen(s) - 1;
	
	for (int i = 0; i < mx_strlen(s)/2; i++, j--) {
		char temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
}
