#include "ush.h"

void mx_check_flags_pwd(char **args, t_pwd *pwd_flags, int count_flags) {
     for (int i = 1; i <= count_flags; i++) {
        for (int j = 0; args[i][j] != '\0'; j++) {
            if (args[i][j] == 'L')
                pwd_flags->L = 1;
            if (args[i][j] == 'P')
                pwd_flags->P = 2;
        }
    }
}
