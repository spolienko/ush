#include "ush.h"

static t_variables *unset_kv_del(t_variables *var, char *com) {
    t_variables *head = var;
    t_variables *head2 = var;
    t_variables *buf = NULL;
    int count = 0;

    for (;head; head = head->next, count++) {
        if (!strcmp(head->name, com)) {
            for (int i = 0; i < count - 1; i++)
                head2 = head2->next;
            buf = head->next;
            mx_strdel(&head->name);
            mx_strdel(&head->value);
            free(head);
            head2->next = buf;
            break;
        }
    }
    return var;
}

int mx_ush_unset(char **args, t_shell *shell) {
    t_variables *head = shell->variables;

    for (int i = 1; args[i]; i++) {
        unsetenv(args[i]);
        head = unset_kv_del(head, args[i]);
    }
    mx_envp_replace(&shell, "?=0");
    return 0;
}
