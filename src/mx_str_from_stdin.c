#include "ush.h"

char *mx_str_from_stdin () {
    char buf[4096];
    size_t n;
    char *str = NULL;
    size_t len = 0;

    while ((n = read(STDIN_FILENO, buf, sizeof buf))) {
        if (n < 0) {
            break;
        }
        str = realloc(str, len + n + 1);
        memcpy(str + len, buf, n);
        len += n;
        str[len] = '\0';
    }
    return str;
}
