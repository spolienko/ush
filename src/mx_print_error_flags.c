#include "ush.h"

static void print_error(const char *s) {
    write(2, s, mx_strlen(s));
}

static void print_char_error(char c) {
	 write(2, &c, 1);
}

void mx_print_error_flags(char *command, char *error, char error_arg) {
    print_error("ush: ");
    print_error(command);
    print_error(": -");
    print_char_error(error_arg);
    print_error(": invalid option\n");
    print_error(command);
    print_error(": usage: ");
    print_error(command);
    print_error(error);
    print_error(" \n");
}
