#include "ush.h"

void mx_undo_ecran(char **input) {
    char *line = *input;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == 5)
            line[i] = '\\';
        else if (line[i] == 3)
            line[i] = '\"';
        else if (line[i] == 1)
            line[i] = '\'';
        else if (line[i] == 2)
            line[i] = '`';
        else if (line[i] == 4)
            line[i] = '$';
        else if (line[i] == 6)
            line[i] = ';';
        else if (line[i] == 8)
            line[i] = ' ';
    }
}
