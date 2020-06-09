#include "ush.h"

int mx_check_builtin(char **cmd_arr, t_shell *shell) {
    for (int i = 0; shell->builtins[i]; i++)
        if (strcmp(shell->builtins[i], cmd_arr[0]) == 0)
            return 1;
    return -1;
}
