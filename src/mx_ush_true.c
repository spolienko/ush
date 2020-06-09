#include "ush.h"

int mx_ush_true(char **args, t_shell *shell) {
	args[0] = args[0];
	shell->status = 0;
	return shell->status;
}
