#include "ush.h"

int mx_bracket4(char *line, int i) {
    char c = '\0';

    for (; line[i] != '\0'; i++) {
        if (line[i] == ')' && line[i + 1] != 7)
            return i;
        if ((c = mx_get_bracket(line, i)) != '\0') {
            if (!(i = mx_check_err(c, line, i + 1))) {
                fprintf(stderr, "u$h: parse error in command substitution\n");
                return 0;
            }
        }
    }
    fprintf(stderr, "u$h: parse error near `('\n");
    return 0;
}
