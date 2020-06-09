#include "ush.h"

static void mx_export_new_var(t_shell *shell, char *str) {
    char *name = strndup(str, mx_get_char_index(str, '='));
    char *val = strdup(str + mx_get_char_index(str, '=') + 1);

    setenv(name, val, 1);
    mx_envp_replace(&shell, str);
    mx_strdel(&name);
    mx_strdel(&val);
}

static void mx_export_from_envp(t_shell *shell, char *com) {
    t_variables *head = shell->variables;

    for (;head; head = head->next) {
        if (!strcmp(com, head->name))
            setenv(com, head->value, 1);
    }
}

int mx_ush_export(char **args, t_shell *shell) {
    if (!args[1]) {
        mx_print_exp(shell);
        return 0;
    }
    for (int i = 1; args[i]; i++) {
        if (mx_get_char_index(args[i], '=') < 0) {
            mx_export_from_envp(shell, args[i]);
        }
        if (mx_get_char_index(args[i], '=') > 0)
            mx_export_new_var(shell, args[i]);
    }
    mx_envp_replace(&shell, "?=0");
    return 0;
}
