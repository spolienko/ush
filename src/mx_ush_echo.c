#include "ush.h"

static void print_echo_E(char **args, int count_flags) {
    int i = count_flags + 1;

    for(; args[i]; i++) {
        for (int j = 0; args[i][j] != '\0'; j++) {
            if (args[i][j] == 92 && args[i][j + 1] == 92) {
                j+= 1;
                write(1, &args[i][j], 1);
            }
            else
                write(1, &args[i][j], 1);
        }
        if (args[i + 1]) 
            mx_printchar(' ');
    }
}

static void case_for_echo(char *c, char arg, t_echo *echo_flags, int* j) {
    switch (*c = arg) {
                    case 'a': *c = '\a'; j+= 1;  break; // alert (beep)
                    case 'b': *c = '\b'; j+= 1; break; // backspace
                    case 'c': ; echo_flags->n = 3; return ;// no further output (EXIT_SUCCESS or 0)
                    case 'e': *c = '\x1B'; j+= 1; break; // escape (?)
                    case 'f': *c = '\f'; j+= 1; break; // form feed
                    case 'n': *c = '\n'; j+= 1; break; // new line
                    case 'r': *c = '\r'; j+= 1; break; // karetka
                    case 't': *c = '\t'; j+= 1; break; // horizontal tab
                    case 'v': *c = '\v'; j+= 1; break; // vertikal tab
                }
}

static void print_echo_e(char **args, int count_flags, t_echo *echo_flags) {
    int i = count_flags + 1;
    char c;

    for(; args[i]; i++) {
        for(int j = 0; args[i][j] != '\0'; j++) {
            if (args[i][j] != 92)
                write(1, &args[i][j], 1);
            if (args[i][j] == 92) {
                case_for_echo(&c, args[i][j + 1], echo_flags, &j);
                mx_printchar(c);
                j+= 1;
            }
        }
        if (args[i + 1]) 
            mx_printchar(' ');
    }
}

static void print_without_flags(char **args, int count_flags) {
    int i = count_flags + 1;

    for(; args[i]; i++) {
        for (int j = 0; args[i][j] != '\0'; j++) {
            if (args[i][j] == 92 && args[i][j + 1] == 92)
                j++;
            write(1, &args[i][j], 1);
        }
        if (args[i + 1]) 
            mx_printstr(" ");
    }
}

static void check_n(t_echo *echo_flags) {
    if (echo_flags->n != 3) {
        mx_printchar('\n');
    }
}

int mx_ush_echo(char **args, t_shell *shell) {
    t_echo echo_flags = {0, 0, 0}; // e == 1, E == 2, n == 3 
    shell->status = 0;
    int count_flags = mx_check_flags_echo(args, &echo_flags);

    if (count_flags == 0 || echo_flags.n == 3) {
        print_without_flags(args, count_flags);
        check_n(&echo_flags);
        return shell->status;
    }
    if (echo_flags.e == 1) {
        print_echo_e(args, count_flags, &echo_flags);
        check_n(&echo_flags);
        return shell->status;
    }
    if (echo_flags.E == 2) {
        print_echo_E(args, count_flags);
        check_n(&echo_flags);
        return shell->status;
    }
    return shell->status;
}
