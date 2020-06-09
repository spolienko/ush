#include "libmx.h"

int mx_bubble_sort(char **arr, int size) {
	int counter = 0;

	for (int i = 0; i < size; i++) {
		for (int k = i + 1; k < size; k++) {
			if (mx_strcmp(arr[i], arr[k]) > 0) {
				char *t = arr[i];
				arr[i] = arr[k];
				arr[k] = t;
				counter++;
			}
		}
	}
	return counter;
}
