#include "ush.h"

// добавить сюда функцию очистки памяти (дико много мемори ликов)

static void exit_eror(char* str) {
	mx_printerr("ush: exit: ");
    mx_printerr(str);
    mx_printerr(": numeric argument required\n");
}

static int count_args(char** args) {
	int count = 0;

	while(args[count] != NULL)
		count++;
	return count;
}

static void status_255(t_shell *shell, char* str) { // -1, возвращает 255, так как это 8-битное значение без знака
	exit_eror(str);
	shell->status = 255;
	exit(shell->status);
}

int mx_ush_exit(char **args, t_shell *shell) {
	int count = count_args(args);
	bool finded = false;
	shell->status = 0;

	if (count > 2)
		status_255(shell, args[1]);
	if (args[1] != NULL) {
		for (int i = 0; args[1][i] != '\0'; i++) {
			if (isdigit(args[1][i]) == 0) // если не диджит
				finded = true;
		}
		if (finded == true)
			status_255(shell, args[1]);
		else {
			shell->status = atoi(args[1]);
			exit(shell->status);
		}
	}
	exit(shell->status);
	return shell->status;
}
