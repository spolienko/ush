#include "ush.h"

char *mx_get_line(void) {
    char *line = NULL;
    size_t bufsize = 0;

    getline(&line, &bufsize, stdin);
    line[strlen(line) - 1] = '\0';
    return line;
}

static void echo_term(char *line, t_li *forest, t_shell *shell) {
        if (!(line = mx_get_line()) || mx_check_line(line, 0, '\0', 0)) {
            mx_strdel(&line);
            return;
        }
        line = mx_ecran(&line);
        line = mx_check_alias(line, shell, 0, 0);
        if (line)
            forest = mx_create_forest(line);
        if (line != NULL && forest)
            mx_launch_cmd(forest, shell);
}

static void term(char *line, t_li *forest, t_shell *shell) {
    while (1) {
        printf("%s%s%s", shell->font_c, shell->bg_c, getenv("PROMT_NAME"));
        if (!(line = mx_get_line()) || mx_check_line(line, 0, '\0', 0)) {
            mx_strdel(&line);
            continue;
        }
        line = mx_ecran(&line);
        line = mx_check_alias(line, shell, 0, 0);
        if (line)
            forest = mx_create_forest(line);
        if (line != NULL && forest)
            mx_launch_cmd(forest, shell);
    }
}

int main () {
    extern char **environ;
    t_shell *shell = (t_shell *)malloc(sizeof(t_shell));

    mx_init_shell(shell);
    (!(isatty(0))) ? echo_term(NULL, NULL, shell) : term(NULL, NULL, shell);
    return 0;
}
