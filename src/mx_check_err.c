#include "ush.h"

static int semicol_check(char *line, int i) {
    if (line[i] == ';' && line[i + 2] != 7) {
        fprintf(stderr, "u$h: syntax error near unexpected token `;;'\n");
        return 0;
    }
    return i;
}

static int check_err2(char c, char *line, int i) {
    if (c == '`') {
        if (!(i = mx_bracket3(line, i)))
            return 0;
    } else if (c == ';') {
        if (!(i = semicol_check(line, i)))
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

int mx_check_err(char c, char *line, int i) {
    if (c == '(') {
        fprintf(stderr, "u$h: syntax error near unexpected token `('\n");
        return 0;
    } else if (c == ')') {
        fprintf(stderr, "u$h: syntax error near unexpected token `)'\n");
        return 0;
    } else if (c == '\'') {
        if (!(i = mx_bracket1(line, i)))
            return 0;
    } else if (c == '\"') {
        if (!(i = mx_bracket2(line, i)))
            return 0;
    } else {
        if (!(i = check_err2(c, line, i)))
            return 0;
    }
    return i;
}
