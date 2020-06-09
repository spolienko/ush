#include "ush.h"

int mx_count_flags(char **args, char *flags, char *command, char *error) {
    int count = 0;

    for (int i = 1; args[i] != NULL; i++) {
        if (args[i][0] != '-' || strcmp(args[i], "-") == 0)
        	break;
        if (strcmp(args[i], "--") == 0) {
            count++;
            break;
        }
        for (int j = 1; j < mx_strlen(args[i]); j++) {
            if(mx_get_char_index(flags,args[i][j]) < 0) {
                mx_print_error_flags(command, error, args[i][j]);
                return -1;
            }
        }
        count++;
    }
    return count;
}
