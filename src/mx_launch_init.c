#include "ush.h"

static void tokenspace(char *line, char ***tokens, int bufsize, int position) {
    char *token = NULL;
    char *line_cp = line;

    token = mx_token_line(&line_cp, ' ');
    while(token != NULL) {
        (*tokens)[position++] = mx_trim_token(token);
        if (position >= bufsize) {
            bufsize += 64;
            *tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!(*tokens)) {
                fprintf(stderr, "u$h: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = mx_token_line(&line_cp, ' ');
    }
    if ((*tokens)[0] == NULL)
        (*tokens)[position++] = line;
    else
        mx_strdel(&line);
    (*tokens)[position] = NULL;
}

static char *removequotes(char *cmd) {
    char *res = mx_strnew(strlen(cmd));
    int r = 0;

    for(int i = 0; (cmd)[i]; i++) {
        if (i > 0)
            if (((cmd)[i] == '\'' || (cmd)[i] == '"') && (cmd)[i-1] == '\\')
                res[r++] = (cmd)[i];
        if ((cmd)[i] != '\'' && (cmd)[i] != '"')
            res[r++] = (cmd)[i];
    }
    return res;
}

static char **create_arr_cmd(char **command, int index) {
    char **cmd = NULL;
    int count = 0;
    int i = index;
    int n = 0;

    if (index >= 0) {
        for (; command[i]; i++)
            count++;
        cmd = malloc((count + 1) * sizeof(char *));
        for (i = index; command[i]; i++) {
            cmd[n++] = strdup(command[i]);
        }
        cmd[n] = NULL;
    }
    return cmd;
}



st_launch *mx_launch_init(char *cmd, t_shell *shell) {
    int index = -1;
    st_launch *l_inf = malloc(sizeof(st_launch));
    l_inf->filepath = NULL;
    l_inf->cmd_arr = NULL;
    l_inf->par = NULL;
    l_inf->type = -1;
    l_inf->pgid = 0;
    char **command = NULL;

    command = malloc(64 * sizeof(char *));
    cmd = mx_substitutions(cmd, shell);
    cmd = mx_exp_param(&cmd);
    if (!cmd) {
        mx_printerr("error param ${}\n");
        return NULL;
    }
    cmd = mx_exp_param2(&cmd, shell);
    tokenspace(cmd, &command, 64, 0);
    if (command[0] != NULL) {
        index = mx_index_cmd(command);
        if (index != -1)
            l_inf->cmd_arr = create_arr_cmd(command, index);
        for (int i = 0; l_inf->cmd_arr && l_inf->cmd_arr[i]; i++) {
            l_inf->cmd_arr[i] = mx_exp_tilda(l_inf->cmd_arr[i]);
        }
        for (int i = 0; l_inf->cmd_arr && l_inf->cmd_arr[i]; i++) {
            l_inf->cmd_arr[i] = removequotes(l_inf->cmd_arr[i]);
            mx_undo_ecran(&l_inf->cmd_arr[i]);
        }
    }
    if (l_inf->cmd_arr) {
        if ((l_inf->type = mx_check_builtin(l_inf->cmd_arr, shell)) == 1) // 1 = builtin
            return l_inf;
        else if ((l_inf->type = mx_find_filepath(l_inf->cmd_arr, &l_inf->filepath)) == 2) // 2 = binary
            return l_inf;
        else {
            mx_printerr("ush: command ");
            mx_printerr(l_inf->cmd_arr[0]);
            mx_printerr(" not found\n");
        }
    }
    return NULL;
}
