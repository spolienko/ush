#include "ush.h"

int mx_ush_env(char **cmd_arr, t_shell *shell) {
    char **new_env = NULL;
    int status = 0;
    t_env *env = malloc(sizeof(t_env));
    //nullify

    if (strcmp(cmd_arr[0], "env") == 0) {
        env = mx_parse_env(cmd_arr);
        new_env = mx_env(cmd_arr, env, shell);

        if (new_env == NULL)
            return 1;
        else {
            status = execve(env->u_name, env->u_flag, new_env);
            if ((env->i == 1 && !env->stream_name) || env->util[0] == '/' || 
                 env->P)
                mx_strdel(env->stream_name);
        }
    }
    else {
        if ((status = execvp(cmd_arr[0], cmd_arr)) == -1)
            mx_printerr("ERROR2\n");
        exit(0);
    }
    free(env);
    shell->status = status;
    return status;
}

