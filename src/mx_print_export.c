#include "ush.h"

static char *add_quotes(char *val) {
    char *val_cp = mx_strjoin("\"", val);

    val = mx_strjoin(val_cp, "\"");
    return val;
}

void mx_print_exp(t_shell *shell) {
    int count = 0;
    extern char **environ;
    
    for (;environ[count]; count++);
    mx_bubble_sort(environ, count);
    for (int i = 0; environ[i]; i++) {
        char *str = strndup(environ[i], mx_get_char_index(environ[i], '='));
        char *str2 = strndup(environ[i] + 
                    mx_get_char_index(environ[i], '=') + 1, 
                    strlen(environ[i]) - mx_get_char_index(environ[i], '='));

        mx_printstr("declare -x ");
        mx_printstr(str);
        mx_printstr("=");
        mx_printstr(add_quotes(str2));
        mx_printstr("\n");
    }
    mx_envp_replace(&shell, "?=0");
}
