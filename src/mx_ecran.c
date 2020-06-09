#include "ush.h"

static int go_skobka(char *line, int i) {
    for (; line[i] != '\0'; i++) {
        if (line[i] == '\'')
            return i;
    }
    return i;
}

static void change_sim(char **input, int i) {
    char *line = *input;

    if (line[i + 1] == '\\')
        line[i] = 5;
    else if (line[i + 1] == '\"')
        line[i] = 3;
    else if (line[i + 1] == '\'')
        line[i] = 1;
    else if (line[i + 1] == '`')
        line[i] = 2;
    else if (line[i + 1] == '$')
        line[i] = 4;
    else if (line[i + 1] == ';')
        line[i] = 6;
    else if (line[i + 1] == ' ')
        line[i] = 8;
}

static int go_double_skobka(char **input, int i) {
    char *line = *input;

    for (; line[i] != '\0'; i++) {
        if (line[i] == '\"')
            return i;
        if (line[i] == '\\' && (line[i + 1] == '\\' || line[i + 1] == '\"'
            || line[i + 1] == '`' || line[i + 1] == '$')) {
            change_sim(&line, i);
            line[i + 1] = 7;
        }
    }
    return i;
}

static void ecran_line(char **input) {
    char *line = *input;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\'')
            i = go_skobka(line, i + 1);
        if (line[i] == '\"')
            i = go_double_skobka(&line, i + 1);
        if (line[i] == '\\' && (line[i + 1] == '\\' || line[i + 1] == '\"'
            || line[i + 1] == '`' || line[i + 1] == '$' ||line[i + 1] == '\''
            || line[i + 1] == ';' || line[i + 1] == ' ')) {
            change_sim(&line, i);
            line[i + 1] = 7;
        } else if (line[i] == '\\') {
            line[i] = line[i + 1];
            line[i + 1] = 7;
        }
    }
}

char *mx_ecran(char **line) {
    ecran_line(line);
    *line = mx_undo_shielding_v(*line);
    return *line;
}
