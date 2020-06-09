#include "ush.h"

static int check_err(char *line, int i) {
    char *str1 = "u$h: unexpected EOF while looking for matching ``'\n";
    char *str2 = "u$h: parse error in command substitution\n";

    for (; line[i] != '\0'; i++) {
        if (line[i] == '`' && line[i + 1] != 7) {
            fprintf(stderr, "%s", str1);
            fprintf(stderr, "%s", str2);
            return 0;
        } else {
            return i + 1;
        }
    }
    fprintf(stderr, "%s", str1);
    fprintf(stderr, "%s", str2);
    return 0;
}

int mx_bracket3(char *line, int i) {
    char c = '\0';

    for (; line[i] != '\0'; i++) {
        if (line[i] == '`' && line[i + 1] != 7)
            return i;
        else
            if (!(i = check_err(line, i + 2)))
                return 0;
        if ((c = mx_get_bracket(line, i)) != '\0') {
            if (!(i = mx_check_err(c, line, i + 1))) {
                fprintf(stderr, "u$h: parse error in command substitution\n");
                return 0;
            }
        }
    }
    fprintf(stderr, "u$h: parse error near ``'\n");
    return 0;
}
