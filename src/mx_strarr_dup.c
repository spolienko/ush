#include "ush.h"

char **mx_strarr_dup(char **str) {
    int len = 0;

    while (str[len])
        len++;
    char **target = malloc(sizeof(char *) * len);
    for (int i = 0; i < len; i++)
        target[i] = mx_strdup(str[i]);
    
    target[len] = NULL;
    return target;
}
