#include "ush.h"

void static undo_shielding(char **input) {
    char *line = *input;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i + 1] == 7) {
            line[i + 1] = line[i];
            line[i] = '\\';
        }
    }
}
static int go_skobka(char *line, int i) {
    for (; line[i] != '\0'; i++) {
        if (line[i] == '\'')
            return i;
    }
    return i;
}

static int go_double_skobka(char **input, int i) {
    char *line = *input;

    for (; line[i] != '\0'; i++) {
        if (line[i] == '\"')
            return i;
        if (line[i] == '\\' && (line[i + 1] == '\\' || line[i + 1] == '\"'
            || line[i + 1] == '`' || line[i + 1] == '$')) {
            line[i] = line[i + 1];
            line[i + 1] = 7;
        }
    }
    return i;
}

static int make_shielding(char **input, int i, char *line) {
    line = *input;
    for (; line[i] != '\0'; i++) {
        if (line[i] == '\'')
            i = go_skobka(line, i + 1);
        if (line[i] == '\"')
            i = go_double_skobka(&line, i + 1);
        if (line[i] == '\\' && line[i + 1] != '\0') {
            line[i] = line[i + 1];
            line[i + 1] = 7;
        }
    }
    if (line[i - 1] == '\\' && line[i] == '\0') {
        fprintf(stderr, "u$h: parse error near `\\'\n");
        return 0;
    }
    return 1;
}

int mx_check_line(char *line, int i, char c, int err) {
    if (!(err = make_shielding(&line, 0, NULL)))
        return 1;
    for (; line[i] != '\0'; i++)
        if ((c = mx_get_bracket(line, i)) != '\0')
            if ((i = mx_check_err(c, line, i + 1)) == 0)
                return 1;
    undo_shielding(&line);
    return 0;
}
