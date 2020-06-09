#include "ush.h"

static int get_len(char *line, int size) {
    for (int i = 0; line[i] != '\0'; i++)
        if (line[i] != 7)
            size++;
    return size;
}

char *mx_undo_shielding_v(char *line) {
    int size = get_len(line, 0) + 1;
    char *ret_data = (char*)malloc(size * sizeof(char));
    int j = 0;

    ret_data[size] = '\0';
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] != 7)
            ret_data[j++] = line[i];
    }
    mx_strdel(&line);
    return ret_data;
}
