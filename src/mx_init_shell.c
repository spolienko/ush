#include "ush.h"

static char *get_pwd(void) {
	char *cur_dir = strdup(getcwd(NULL, 1024));
    char *pwd = strdup(getenv("PWD"));
    char *readlink = strdup(realpath(pwd, NULL));

    if (readlink && strcmp(readlink, cur_dir) == 0) {
    	pwd = strdup(getenv("PWD"));
    	free(cur_dir);
    	free(readlink);
    }
    else {
    	pwd = strdup(cur_dir);
    	free(cur_dir);
    }
    return pwd;
}

static char **init_builtin() {
    char **builtins = malloc(15 * sizeof(char *));

    builtins[0] = "pwd";
    builtins[1] = "env";
    builtins[2] = "which";
    builtins[3] = "echo";
	builtins[4] = "unset";
	builtins[5] = "export";
    builtins[6] = "exit";
	builtins[7] = "cd";
    builtins[8] = "true";
    builtins[9] = "false";
	builtins[10] = "alias";
	builtins[11] = "return";
	builtins[12] = "color_font";
	builtins[13] = "color_bg";
    builtins[14] = NULL;
    return builtins;
}

static char *strfdup(char *str, int n) {
	char *res = malloc(strlen(str) - n);
	int y = 0;

	for (int i = n; str[i]; i++) {
		res[y] = str[i];
		y++;
	}
	return res;
}

static t_variables *get_variables(void) {
	t_variables *variables = NULL;
	extern char **environ;
	char *name = NULL;
	char *value = NULL;

	for (int i = 0; environ[i]; i++) {
		name = strndup(environ[i], mx_get_char_index(environ[i], '='));
		value = strfdup(environ[i], mx_get_char_index(environ[i], '=') + 1);
		mx_push_variable(&variables, name, value);
	}
	mx_push_variable(&variables, "?", "0");
	return variables;
}

static t_variables *get_export(void) {
	t_variables *variables = NULL;
	extern char **environ;
	char *name = NULL;
	char *value = NULL;

	for (int i = 0; environ[i]; i++) {
		name = strndup(environ[i], mx_get_char_index(environ[i], '='));
		value = strfdup(environ[i], mx_get_char_index(environ[i], '=') + 1);
		mx_push_variable(&variables, name, value);
	}
	return variables;
}

static void init_shlvl(t_shell *shell) {
	char *shlvl = strdup(getenv("SHLVL"));
	char *tmp = NULL;
	int lvl = 0;

	if (shlvl == NULL)
		shlvl = strdup("1");
	else {
		lvl = atoi(shlvl) + 1;
		tmp = mx_itoa(lvl);
		shlvl = strdup(tmp);
		free(tmp);
	}
	mx_push_variable(&shell->variables, "SHLVL", shlvl);
	setenv("SHLVL", shlvl, 1);

}

void mx_init_shell(t_shell *shell) {
    shell->PROMT_NAME = "u$h> ";
    setenv("PROMT_NAME", shell->PROMT_NAME, 1);
    shell->font_c = "\033[0m";
    shell->bg_c = "\033[0m";
    shell->pwd = get_pwd();
    shell->variables = get_variables();
    shell->export_variables = get_export();
    init_shlvl(shell);
    shell->builtins = init_builtin();
    mx_init_color_font(shell);
    mx_init_color_bg(shell);
    shell->alias = NULL;
    shell->status = 0;
    shell->status_exec = 0;
    shell->cd_path = NULL;
    mx_ush_signals(shell);
}
