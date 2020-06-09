#include "ush.h"

char mx_get_bracket(char *string, int i) {
    char brackets[6] = {'$', '`', '\'', '\"', '(', ';'};

    if (string[i + 1] == 7)
        return '\0';
    for (int j = 0; j < 6; j++)
        if (string[i] == brackets[j])
            return string[i];
    return '\0';
}
