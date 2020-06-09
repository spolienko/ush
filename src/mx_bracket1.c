#include "ush.h"

int mx_bracket1(char *line, int i) {
    for (; line[i] != '\0'; i++) {
        if (line[i] == '\'')
            return i;
    }
    fprintf(stderr, "u$h: parse error near `\''\n");
    return 0;
}
