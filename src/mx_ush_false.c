#include "ush.h"

int mx_ush_false(char **args, t_shell *shell) {
	args[0] = args[0];
	shell->status = 1;
	return shell->status;
}
