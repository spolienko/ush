#include "ush.h"

void mx_printforest(t_li *forest) {
    while(forest) {
        while (forest->command) {
            if (forest->command->cmd)
                mx_printstr(forest->command->cmd);
            mx_printstr("\n");
            if (forest->command->or != NULL) {
                forest->command = forest->command->or;
                continue;
            }
            else {
                forest->command = forest->command->and;
                continue;
            }
        }
        forest = forest->next;
    }
}

t_li *mx_create_forest(char *line) {
    char **tokcoma = NULL;
    t_li *forest = NULL;

    tokcoma = mx_tokcoma(line);
    if (tokcoma)
        for (int i = 0; tokcoma[i]; i++) {
            if (forest == NULL) {
                forest = malloc(sizeof(t_li));
                forest->command = mx_treefill(tokcoma[i]);
                forest->next = NULL;
            }
            else
                mx_pushtree(&forest, tokcoma[i]);
        }
    return forest;
}
