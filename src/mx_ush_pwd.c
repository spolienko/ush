#include "ush.h"

static void error_many_args(void) {
    write(2, "pwd: too many arguments", strlen("pwd: too many arguments"));
    write(2, "\n", 1);
}

static bool is_link(char* str) {
    struct stat buf;

    if (lstat(str, &buf) != -1) {
        if((buf.st_mode & S_IFMT) == S_IFLNK)
            return true;
        else 
            return false;
    }
    return false;
}

static void init_path(char** path) {
    if (getenv("PWD")) {
        *path = strdup(getenv("PWD"));
    }
    else {
        *path = strdup(getcwd(NULL, 1024));
    }
}

static void flag_p_true(char* sym_link, char* path) {
    if (is_link(path) == true) {
        sym_link = strdup(realpath(path, sym_link));
        if (sym_link != NULL)
            printf("%s\n", sym_link);
        else
            printf("%s\n", path);
    }
    else
        printf("%s\n", path);
}

int mx_ush_pwd(char **args, t_shell *shell) {
    char* path = NULL;
    char* sym_link = malloc(1024);
    int count_flags = mx_count_flags(args, "LP", "pwd", " [-LP]");
    shell->status = 0;
    t_pwd pwd_flags = {0, 0}; // L == 1, P == 2
    mx_check_flags_pwd(args, &pwd_flags, count_flags);

    if (count_flags < 0) {
        shell->status = 1;
        return shell->status;
    }
    if (args[count_flags + 1] != NULL) { // если есть аргументы помимо флагов
        error_many_args();
        shell->status = 1;
        return shell->status;
    }
    init_path(&path);
    if (path != NULL) {
        if (pwd_flags.P == 2)
            flag_p_true(sym_link, path);
        else 
            printf("%s\n", path);
    }
    else
        perror("ush: pwd");
    return shell->status;
}
