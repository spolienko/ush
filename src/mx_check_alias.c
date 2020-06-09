#include "ush.h"

static int compare_str(char *cmd, int index) {
    if (cmd[index] == ';' || cmd[index] == ' ' || cmd[index] == '$')
        return 1;
    if ((cmd[index] == '&' && cmd[index + 1] == '&')
        || (cmd[index] == '|' && cmd[index + 1] == '|')) {
        return 1;
    }
    return 0;
}

char *mx_check_alias(char *cmd, t_shell *shell, int r, int result) {
    t_variables *alias = shell->alias;
    char *name = NULL;
    char *res = NULL;

    for (; cmd[r] != '\0' && compare_str(cmd, r) != 1; r++);
    name = strndup(cmd, r);
    while (alias != NULL) {
        if (strcmp(name, alias->name) == 0) {
            res = mx_strnew(strlen(cmd + r) + strlen(alias->value));
            mx_exp_join(&res, alias->value, &result);
            mx_exp_join(&res, cmd + r, &result);
        }
        alias = alias->next;
    }
    if (res == NULL)
        return cmd;
    else
        return res;
}
