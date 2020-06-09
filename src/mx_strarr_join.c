#include "ush.h"

char **mx_strarr_join(char **s1, char **s2) {
    char **new_arr = mx_strarr_dup(s1);
    int len_s1 = 0;
    int len_s2 = 0;
    int i = 0;

    if (new_arr) {
        while (new_arr[len_s1])
            len_s1++;
        while (s2[len_s2])
            len_s2++;

        new_arr = realloc(new_arr, sizeof(char *) * (len_s1 + len_s2 + 1));
        i = len_s1;
        for(int j = 0; i < len_s1 + len_s2; j++, i++) {
            new_arr[i] = mx_strdup(s2[j]);
        }
        new_arr[i] = NULL;
    }
    return new_arr;
}
