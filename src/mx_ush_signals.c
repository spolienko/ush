#include "ush.h"

static void sig_check() {
	signal(SIGINT, MX_SIG_IGN);
    signal(SIGTSTP, MX_SIG_IGN);
    signal(SIGTTIN, MX_SIG_IGN);
    signal(SIGTTOU, MX_SIG_IGN);
}

static void set_shell_grp(t_shell *shell) {
    pid_t shell_pgid;
    int shell_terminal = STDIN_FILENO;
    int shell_is_interactive = isatty(shell_terminal);

    if (shell_is_interactive) {
        while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
            kill(-shell_pgid, SIGTTIN);
        sig_check();
         shell_pgid = getpid();
        if (setpgid(shell_pgid, shell_pgid) < 0) {
            perror("Couldn't put the shell in its own process group");
            shell->status = 1;
            exit(1);
        }
    tcsetpgrp(STDIN_FILENO, shell_pgid);  // берем контроль над терминалом
    shell->shell_pgid = shell_pgid;
    }
}

void mx_ush_signals(t_shell *shell) {
	 set_shell_grp(shell);
	 shell->status = 0;
}

