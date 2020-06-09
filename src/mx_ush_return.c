#include "ush.h"

int mx_ush_return(char **args, t_shell *shell) {
    shell->status = 0;

    if (args[2] != NULL) {
        mx_printerr("return: too many arguments");
        shell->status = 1;
    }
    if (args[1] != NULL)
        shell->status = atoi(args[1]);
    return shell->status;
}
