#include "ush.h"


void mx_launch_builtin(st_launch *l_inf, t_shell *shell) {
    int (*builtin_f[]) (char **, t_shell *) = {
        &mx_ush_pwd,
        &mx_ush_env,
        &mx_ush_which,
        &mx_ush_echo,
        &mx_ush_unset,
        &mx_ush_export,
        &mx_ush_exit,
        &mx_ush_cd,
        &mx_ush_true,
        &mx_ush_false,
        &mx_ush_alias,
        &mx_ush_return,
        &mx_ush_color_font,
        &mx_ush_color_bg
    };

    for (int i = 0; shell->builtins[i]; i++) {
        if (strcmp(l_inf->cmd_arr[0], shell->builtins[i]) == 0) {
            shell->status_exec = builtin_f[i](l_inf->cmd_arr, shell);
        }
    }
}


void mx_launcher(st_launch *l_inf, t_shell *shell) {
    pid_t child_pid;
    pid_t wpid;
    int status;
    int shell_is_interactive = isatty(STDIN_FILENO);

    l_inf->pgid = 0;
    if (l_inf->type == 1)
        mx_launch_builtin(l_inf, shell);

    else if (l_inf->type == 2) {
        child_pid = fork();
        if (child_pid < 0) {
            mx_printerr("u$h: error forking\n");
            exit(1);
        }
        else if (child_pid == 0) {
            if (shell_is_interactive) {
                if (l_inf->pgid == 0)
                    l_inf->pgid = child_pid;
                setpgid(child_pid, l_inf->pgid);

                tcsetpgrp(STDIN_FILENO, getpid()); //связываем группу процессов из активным терминалом
                signal(SIGINT, MX_SIG_DFL);
                signal(SIGQUIT, MX_SIG_DFL);
                signal(SIGTSTP, MX_SIG_DFL);
                signal(SIGTTIN, MX_SIG_DFL);
                signal(SIGTTOU, MX_SIG_DFL);
                signal(SIGCHLD, SIG_DFL);
            }
            if (execvp(l_inf->filepath, l_inf->cmd_arr) < 0) {
                perror("ush mx_launch_binary: 51");
                _exit(shell->status);
            }
        }
        else {               //  родительский процесс
            if (shell_is_interactive) {
                if (l_inf->pgid == 0)
                    l_inf->pgid = child_pid;
                setpgid(child_pid, 0);
            }
            tcsetpgrp(STDIN_FILENO, l_inf->pgid);
            signal(SIGTTOU, MX_SIG_IGN);
            wpid = waitpid(child_pid, &status, MX_WUNTRACED);
            while(!WIFEXITED(status) && !MX_WIFSTOPP(status))
                wpid = waitpid(child_pid, &status, MX_WUNTRACED);
            shell->status = WEXITSTATUS(status);
            shell->status_exec = shell->status;
            tcsetpgrp(STDIN_FILENO, getpid());
        }
    }
}
