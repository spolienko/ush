#include "ush.h"

static int check_err(char c, char *line, int i) {
    if (c == '\'') {
        if (!(i = mx_bracket1(line, i)))
            return 0;
    } else if (c == '`') {
        if (!(i = mx_bracket3(line, i)))
            return 0;
    } else if (c == '$') {
        if (line[i] == '(')
            if (!(i = mx_bracket4(line, i + 1)))
                return 0;
        if (line[i] == '{')
            if (!(i = mx_bracket5(line, i + 1)))
                return 0;
    }
    return i;
}

int mx_bracket2(char *line, int i) {
    char c = '\0';

    for (; line[i] != '\0'; i++)  {
        if (line[i] == '\"' && line[i + 1] != 7)
            return i;
        if ((c = mx_get_bracket(line, i)) != '\0')
            if (!(i = check_err(c, line, i + 1)))
                return 0;
    }
    fprintf(stderr, "u$h: parse error near `\"'\n");
    return 0;
}
