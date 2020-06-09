#include "ush.h"

void mx_exp_join(char **res, char *source, int *r) {
    for (int i = 0; source[i]; i++) {
        (*res)[(*r)] = source[i];
        (*r) += 1;
        (*res)[(*r)] = '\0';
    }
}
