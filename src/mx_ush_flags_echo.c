#include "ush.h"

static void choice_E(t_echo *echo_flags) {
	if (echo_flags->e != 1) {
        echo_flags->E = 2;
        return ;
	}
    if (echo_flags->e == 1) {
        echo_flags->E = 2;
        echo_flags->e = 0;
        return ;
    }
}

static void choice_ee(t_echo *echo_flags) {
	if (echo_flags->E != 2) {
        echo_flags->e = 1;
        return ;
	}
    if (echo_flags->E == 2) {
        echo_flags->e = 1;
        echo_flags->E = 0;
        return ;
    }
}

static void choice_flag(t_echo *echo_flags, char c) {
	if (c == 'e')
        choice_ee(echo_flags);
    if (c == 'E')
        choice_E(echo_flags);
    if (c == 'n')
        echo_flags->n = 3;
}

int mx_check_flags_echo(char **args, t_echo *echo_flags) {
    int count_flags = 0;

    for (int i = 1; args[i] != NULL; i++) {
         if (args[i][0] == '-' && args[i][1] != '-') {
            for (int j = 1; args[i][j] != '\0'; j++) {
                if (strchr("eEn", args[i][j])) {
                	choice_flag(echo_flags, args[i][j]);
                	count_flags++;
                }
                else {
                	count_flags = 0;
                    return count_flags; // error handling
                }
            }
        }
        else
            break ;
    }
    return count_flags;
}
