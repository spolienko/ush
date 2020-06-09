#include "ush.h"

static void check_flags(char** args, t_which *which_flag, int count_flags) {
    for (int i = 1; i <= count_flags; i++) {
        for (int j = 0; args[i][j] != '\0'; j++) {
            if (args[i][j] == 'a')
                which_flag->a = 1;
            if (args[i][j] == 's')
                which_flag->s = 2;
        }
    }
}

static void not_found(char* str) {
    mx_printerr(str);
    mx_printerr(" not found\n");
}

static void check_shell_builtins(t_shell *shell, t_which *which_flags, char* builtin, bool* printed) {
      for (int y = 0; shell->builtins[y] != NULL; y++) {
            if (strcmp(builtin, shell->builtins[y]) == 0) {
                if (which_flags->s == 2) {
                    *printed = true;
                    shell->status = 0;
                    break ;
                }
              printf("%s: %s\n", builtin, "shell built-in command");
                *printed = true;
                break ;
            }
        }
}

static void find_in_path(t_shell *shell, t_which *which_flags, char* builtin, bool* printed, char** ways) {
        struct stat buf;
        char* tmp = NULL;
        for (int k = 0; ways[k]; k++) {
            tmp = strdup(builtin);
            char* str = mx_strjoin("/", tmp);
            free(tmp);
            tmp = mx_strjoin(ways[k], str);
            free(str);
            if (lstat(tmp, &buf) != -1) {
                if((buf.st_mode & S_IXUSR) == S_IXUSR) {
                    if (which_flags->s == 2) {
                    *printed = true;
                    shell->status = 0;
                    break ;
                }
                    if (*printed == false) {
                        printf("%s\n", tmp);
                        *printed = true;
                    }
                }
            }
        }
}

int mx_ush_which(char** args, t_shell *shell) {
    t_which which_flags = {0, 0}; // a == 1; s == 2;
    shell->status = 0;
    char* path = NULL;
    char **ways;
    bool printed = false;
    int count_flags = mx_count_flags(args, "as","which", " [-as] program ...");
    check_flags(args, &which_flags, count_flags);
    
    if (count_flags < 0) {
        shell->status = 1;
        return shell->status;
    }
    if (getenv("PATH")) {
        path = strdup(getenv("PATH"));
        ways = mx_modstrsplit(path, ':');
    }
    for (int i = count_flags + 1; args[i] != NULL; i++) {
        check_shell_builtins(shell, &which_flags, args[i], &printed);
        if ((printed == false || which_flags.a == 1)  && path != NULL)
            find_in_path(shell,&which_flags, args[i], &printed, ways);
        if (printed == false) {
            if (which_flags.s == 2)
                shell->status = 1;
            else
                not_found(args[i]);
            shell->status = 1;
            return shell->status;
        }
    }
    return shell->status;
}
