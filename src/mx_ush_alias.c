#include "ush.h"

static t_variables *create_node(void *name, void *value) {
    t_variables *node =  (t_variables *)malloc(sizeof(t_variables));

    node->name = strdup(name);
    if(!value)
        node->value = strdup("");
    else
        node->value = strdup(value);
    node->next = NULL;
    return node;
}

static void push_node(t_variables *list, void *name, void *value) {
    t_variables *tmp;
    t_variables *res;
	int flag = 0;

    if (!list)
        return;
    res = list;
    while (res != NULL) {
        if (strcmp(res->name, name) == 0) {
			mx_strdel(&res->value);
			res->value = mx_strdup(value);
			flag = 1;
			break;
		}
		if (res->next == NULL)
			break;
		res = res->next;
	}
	if (flag == 0) {
		tmp = create_node(name, value);
	    res->next = tmp;
	}
}


static void mx_print_variables(t_variables *alias) {
	t_variables *al = alias;
	while(al != NULL) {
		mx_printstr(al->name);
		mx_printstr("=");
		mx_printstr(al->value);
		mx_printstr("\n");
		al = al->next;
	}
}

static void add_arg(char *arg, t_shell *shell) {
	int i = 0;
	char *name = NULL;
	char *value = NULL;
	char *argument = arg;

	for(; arg[i] && arg[i] !='='; i++);
	name = mx_strndup(arg, i);
	argument += i+1;
	value = mx_strdup(argument);
	if (shell->alias == NULL)
		shell->alias = create_node(name, value);
	else 
		push_node(shell->alias, name, value);
}

int mx_ush_alias(char **args, t_shell *shell) {
	if (args[1] != NULL) {
		for(int i = 1; args[i] != NULL; i++) {
			if (mx_strcmp(args[i], "=") == 0) {
				mx_printerr("u$h: bad assignment");
				shell->status = 1;
			}
			if (args[i][0] == '=') {
				mx_printerr("u$h: argument not found\n");
				shell->status = 1;
			}
		}
		for (int i = 1; args[i] != NULL; i++) {
			if (mx_get_char_index(args[i], '=') != -1)
				if (args[i][mx_get_char_index(args[i], '=') + 1] != '=')
					add_arg(args[i], shell);
		}
	} else {
		mx_print_variables(shell->alias);
	}
	return 0;
}
