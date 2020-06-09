#include "ush.h"

static void cd_without_args(t_shell *shell, char* path) {
    if (getenv("HOME")) {
        if (chdir(getenv("HOME")) < 0) {
            mx_error_path(strdup(getenv("HOME")));
            shell->status = 0;
            return ;
        }
        else {
            setenv("OLDPWD", path, 1);
            shell->pwd = strdup(getenv("OLDPWD"));
            setenv("PWD", getenv("HOME"), 1);
            shell->status = 0;
            return ;
        }
    }
    else {
            chdir(shell->pwd);
            shell->status = 0;
            return ;
    }
}

static void cd_minus(t_shell *shell, char* path) {
    if (getenv("OLDPWD")) {
        mx_strdel(&shell->cd_path);
        shell->cd_path = strdup(getenv("OLDPWD"));
        chdir(shell->cd_path);
        shell->pwd = strdup(getenv("OLDPWD"));
        setenv("PWD", getenv("OLDPWD"), 1);
        setenv("OLDPWD", path, 1);
        printf("%s\n", getenv("PWD"));
        shell->status = 0;
        return ;
    }
    else {
        mx_printerr("cd: OLDPWD not set\n");
        shell->status = 1;
        return ;
        }
}

static void cd_with_flag(t_shell* shell ,char* resolved_path, char* res, char* path, char* arg, t_cd *cd_flags) {
    if (resolved_path && strcmp(res, resolved_path) == 0) {
            mx_ch_dir(resolved_path, path, shell);
            shell->status = 0;
            return ;
    }
    else if (resolved_path && cd_flags->P == 2 && strcmp(res, resolved_path) != 0) {
        mx_ch_dir(resolved_path, path, shell);
        shell->status = 0;
        return ;
    }
    else if (!resolved_path) {
        mx_error_path(arg);
        shell->status = 1;
        return ;
    }
    else {
        mx_not_a_dir(arg);
        shell->status = 1;
         return ;
    }
}

static void cd_without_flags(t_shell* shell,char* res, char* resolved_path, char* path) {
    if (strcmp(res, resolved_path) != 0) {
                setenv("OLDPWD", getenv("PWD"), 1);
                chdir(res);
                shell->pwd = strdup(getenv("OLDPWD"));
                setenv("PWD", res, 1);
                shell->status = 0;
                return ;
            }
            else  {
                mx_ch_dir(resolved_path, path, shell);
                shell->status = 0;
                return ;
            }
}

static void cd_job(t_shell* shell, char* path, int count_flags, char* arg, t_cd *cd_flags) {
    char* resolved_path = NULL;
    char* res = mx_strnew(strlen(path) + strlen(arg));

    res = mx_output_path(path, arg);
    mx_strdel(&shell->cd_path);
    shell->cd_path = strdup(res);
    resolved_path = strdup(realpath(res, NULL));
    if (count_flags)
        cd_with_flag(shell, resolved_path, res, path, arg, cd_flags);
    else if (resolved_path)
        cd_without_flags(shell, res, resolved_path, path);
    else {
        mx_strdel(&shell->cd_path);
        mx_error_path(arg);
        shell->status = 1;
    }
}

static char *get_last_arr_elem(char **arr) {
    int i = 0;
    char *res = NULL;
    char *tmp = NULL;

    while (arr[i] != NULL)
        i++;

    if(i > 0) {
        res = arr[i - 1];
    }
    else {
        res = arr[0];
        if (res == NULL) {
            return strdup("/");
        }
    }
    if(res[0] != '/') {
        tmp = res;
        res = mx_strjoin("/", tmp);
        mx_strdel(&tmp);
    }
    return res;
}

static char* mx_getcwd(t_shell *shell) {
    char *path = strdup(getcwd(NULL, 1024));
    char *last_getcwd = NULL;
    char *last_shell_cd_path = NULL;

    if(shell->cd_path == NULL)
        return path;
    if(strcmp(path, shell->cd_path) == 0)
        return path;
    else if(strcmp(path, shell->cd_path) != 0) {
        last_getcwd = get_last_arr_elem(mx_strsplit(path, '/'));
        last_shell_cd_path = get_last_arr_elem(mx_strsplit(shell->cd_path, '/'));
        if(strcmp(last_getcwd, last_shell_cd_path) == 0)
            return shell->cd_path;
    }
    return path;
}

int mx_ush_cd(char **args, t_shell *shell) {
    int count_flags = mx_count_flags(args, "sP", "cd", "[-L|-P] [dir]");
    t_cd cd_flags = {0, 0}; // s == 1, P == 2
    mx_check_flags(args, &cd_flags, count_flags);
    char* path = mx_getcwd(shell);
    shell->status = 0;
    if (count_flags < 0) {
        shell->status = 1;
        return shell->status;
    }
    if (args[count_flags + 1] == NULL) {
        cd_without_args(shell, path);
        return shell->status;
    }
    if (strcmp(args[count_flags + 1], "-") == 0) {
        cd_minus(shell, path);
        return shell->status;
    }
    cd_job(shell, path, count_flags, args[count_flags + 1], &cd_flags);
  return shell->status;
}
