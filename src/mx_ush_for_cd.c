#include "ush.h"

void mx_not_a_dir(char* str) {
    char* str_err = "cd: not a directory: ";
    write(2, str_err, strlen(str_err));
    write(2, str, strlen(str));
    write(2, "\n", 1);
}

void mx_check_flags(char** args, t_cd *cd_flags, int count_flags) {
    for (int i = 1; i <= count_flags; i++) {
        for (int j = 0; args[i][j] != '\0'; j++) {
            if (args[i][j] == 's')
                cd_flags->s = 1;
            if (args[i][j] == 'P')
                cd_flags->P = 2;
        }
    }
}

void mx_error_path(char* str) {
    write (2, "cd: no such file or directory: ", 31);
    write (2, str, strlen(str));
    write (2, "\n", 1);
}

void mx_ch_dir(char *res_path, char* path, t_shell *shell) {
    chdir(res_path);
    setenv("OLDPWD", path, 1);
    shell->pwd = strdup(getenv("OLDPWD"));
    setenv("PWD", res_path, 1);
}
