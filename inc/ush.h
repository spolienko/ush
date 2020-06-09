#ifndef USH_HEADER_H
#define USH_HEADER_H

#define _GNU_SOURCE
#include "libmx.h"
// #include <dirent.h>
// #include <time.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <sys/xattr.h>
// #include <sys/acl.h>
// #include <sys/ioctl.h>
// #include <pwd.h>
// #include <grp.h>
#include <xlocale.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <pwd.h>

#define MX_PARS_TSTOP       " \n\t\r\v\f/"
#define LS_COLOR_RED        "\x1b[31m"
#define LS_COLOR_RESET      "\x1b[0m"
#define MX_SIG_DFL          (void (*)(int))0
#define MX_SIG_IGN          (void (*)(int))1
#define MX_SIG_HOLD         (void (*)(int))5
#define MX_SIG_ERR          ((void (*)(int))-1)
#define MX_WUNTRACED        0x00000002
#define MX_WSTOPPED         0177
#define MX_W_INT(w)         (*(int *)&(w))
#define MX_WSTAT(x)         (MX_W_INT(x) & 0177)
#define MX_WSTOPSIG(x)     (MX_W_INT(x) >> 8)
#define MX_WIFSTOPP(x)  (MX_WSTAT(x) == MX_WSTOPPED && MX_WSTOPSIG(x) != 0x13)


typedef struct s_variables {
    char *name;
    char *value;
    struct s_variables *next;
}              t_variables;

typedef struct s_shell {
    t_variables *variables;
    t_variables *export_variables;
    char* PROMT_NAME;
    char *pwd;
    int status;
    int status_exec;
    struct termios savetty;
    char **builtins;
    t_variables *alias;
    char** f_color_reg; //for font color
    char** f_color_bold;//for font color
    char** f_color_under;//for font color
    char** bg_color_reg;// for background color
    char** bg_color_bold;// for background color
    char** bg_color_high;// for background color
    char** bg_color_inten;// for background color
    char* font_c; // selected font color
    char* bg_c; // selected background color
    char* cd_path; //last path from cd call
    pid_t shell_pgid; //group pgid shell
}               t_shell;

// substitution
typedef struct s_sub {
    int index;
    int quote;
    int d_quote;
}               t_sub;

typedef struct s_fd {
    int saved_stdin;
    int saved_stdout;
    int output_fds;
    int input_fds;
}               t_fd;

// VLADIK
typedef struct s_cmd {
    char *cmd;
    struct s_cmd *or;
    struct s_cmd *and;
}              t_cmd;

typedef struct s_li {
    struct s_cmd *command; //tree
    struct s_li *next;
}              t_li;

typedef struct launch {
    char *filepath; //path to binary;
    char **cmd_arr; // env -ppp
    char **par; // a=b b=c ..
    int type; // no cmd found , builtin, binary      (alias, shell func)
    pid_t pgid; 
}              st_launch;

//SOFI

typedef struct s_echo { // check flags for echo
    int e;
    int E;
    int n;
    
}             t_echo;

typedef struct s_which {// check flags for which
    int a;
    int s;
}               t_which;

typedef struct s_pwd {// check flags for pwd
    int L;
    int P;
}               t_pwd;

typedef struct s_cd {// check flags for cd
    int s;
    int P;
    
}               t_cd;


//OLEGA

typedef struct s_env {
    bool i;
    char *P;
    char *u;
    char **stream_name;
    char *util;
    char *u_name;
    char **u_flag;
    char *P_name;
    char error;
} t_env;

typedef struct s_exp {
    bool flag_equal;
    char **stream_name;
    char error;
    char **not_found;
} t_exp;

typedef struct s_kv {
    char *key;
    char *val;

    struct s_kv *next;
} t_kv;

// OLEG UTILS
char **mx_strarr_dup(char **str);
char **mx_strarr_join(char **s1, char **s2);
// ENV
t_kv *mx_create_kv(char **environ);
t_kv *mx_push_kv(char *env);
void mx_pushb_kv(t_kv **ptr, char *env);
char **mx_env_copy(void);
t_env *mx_parse_env(char **args);
char **mx_env(char **cmd_arr, t_env *env, t_shell *shell);
char **mx_do_util(char **cmd_arr, char **environ, t_env *env);
// EXPORT
void mx_envp_add(t_shell **res, char *data);
void mx_envp_replace(t_shell **res, char *data);
void mx_print_exp(t_shell *shell);
// FG
// void mx_enable_input_mode(t_shell *ush);
// void mx_disable_input_mode(t_shell *ush);

// init t_shell info
void mx_init_shell(t_shell *shell);
void mx_push_variable(t_variables **list, void *name, void *value);

// expansion
char *mx_exp_param2(char **line, t_shell *shell);
char* mx_exp_tilda(char *line);
void mx_exp_join(char **res, char *source, int *r);

// substitutions
char *mx_str_from_stdin();
void mx_format_sub_result(char **str);
char *mx_substitutions(char *line, t_shell *shell);
char *mx_token_line(char **line, char delim);
char *mx_trim_token(char *str);
void mx_printforest(t_li *forest);
t_li *mx_create_forest(char *line);
char **mx_tokcoma(char *line);

t_cmd *mx_treefill(char *token);
t_cmd *mx_create_cmd(char *cmd, int i);
void mx_pushtree(t_li **forest, char *tokcoma);

void mx_launch_cmd(t_li *forest, t_shell *shell);


//launch_init_utils
int mx_index_cmd(char **cmd);
// int mx_check_builtin(char **cmd_arr);
int mx_find_filepath(char **cmd_arr, char **filepath);

//launchers
void mx_launch_builtin(st_launch *l_inf, t_shell *shell);
void mx_launcher(st_launch *l_inf, t_shell *shell); // for binary and builtin

// OLEG UTILS
char **mx_strarr_dup(char **str);
char **mx_strarr_join(char **s1, char **s2);
// ENV
int mx_ush_export(char **args, t_shell *shell);
int mx_ush_unset(char **args, t_shell *shell);
t_kv *mx_create_kv(char **environ);
t_kv *mx_push_kv(char *env);
void mx_pushb_kv(t_kv **ptr, char *env);
char **mx_env_copy(void);
t_env *mx_parse_env(char **args);
char **mx_env(char **cmd_arr, t_env *env, t_shell *shell);
char **mx_do_util(char **cmd_arr, char **environ, t_env *env);
// EXPORT
void mx_envp_add(t_shell **res, char *data);
void mx_envp_replace(t_shell **res, char *data);
void mx_print_exp(t_shell *shell);

// init t_shell info
void mx_init_shell(t_shell *shell);
void mx_push_variable(t_variables **list, void *name, void *value);


// expansion
char *mx_exp_param(char **line);
void mx_exp_join(char **res, char *source, int *r);

void mx_printforest(t_li *forest);
t_li *mx_create_forest(char *line);
char **mx_tokcoma(char *line);

t_cmd *mx_treefill(char *token);
t_cmd *mx_create_cmd(char *cmd, int i);
void mx_pushtree(t_li **forest, char *tokcoma);

void mx_launch_cmd(t_li *forest, t_shell *shell);
st_launch *mx_launch_init(char *cmd, t_shell *shell);


//launch_init_utils
int mx_index_cmd(char **cmd);
int mx_check_builtin(char **cmd_arr, t_shell *shell);
int mx_find_filepath(char **cmd_arr, char **filepath);

//launchers
void mx_launch_builtin(st_launch *l_inf, t_shell *shell);
void mx_launcher(st_launch *l_inf, t_shell *shell); // for binary and builtin

// alias
int mx_ush_alias(char **args, t_shell *shell);
char *mx_check_alias(char *cmd, t_shell *shell, int r, int result);

//MEFEDRON  validation
int mx_check_line(char *line, int i, char c, int err);
char *mx_undo_shielding_v(char *line);
int mx_check_err(char c, char *line, int i);
char mx_get_bracket(char *string, int i);
int mx_bracket1(char *line, int i);
int mx_bracket2(char *line, int i);
int mx_bracket3(char *line, int i);
int mx_bracket3(char *line, int i);
int mx_bracket4(char *line, int i);
int mx_bracket5(char *line, int i);

//MEFEDRON  ecran
char *mx_ecran(char **line);
void mx_undo_ecran(char **input);

//sofi
int mx_ush_cd(char **args, t_shell *shell); // implementation cd builtin
char* mx_output_path(char *str1, char* str2); // func for cd builtin
int mx_ush_pwd(char **args, t_shell *shell); // implementation pwd builtin
int mx_ush_env(char **args, t_shell *shell); // implementation env builtin
int mx_ush_which(char **args, t_shell *shell); // implementation which builtin
int mx_ush_echo(char **args, t_shell *shell); // implementation echo builtin
int mx_ush_exit(char **args, t_shell *shell);  // implementation exit builtin
int mx_count_flags(char **args, char *flags, char *command, char *error); // for check and cound flags
void mx_print_error_flags(char *command, char *error, char error_arg); // for error case in check flags
int mx_count_flags(char **args, char *flags, char *command, char *error); // check flags
int mx_ush_false(char **args, t_shell *shell); // implementation false builtin
int mx_ush_true(char **args, t_shell *shell); // implementation true builtin
int mx_ush_return(char **args, t_shell *shell); // implementation return builtin
char **mx_modstrsplit(const char *s, char c); // for which auditor
void mx_check_flags_pwd(char **args, t_pwd *pwd_flags, int count_flags); // for pwd auditor
int mx_check_flags_echo(char **args, t_echo *echo_flags); // for echo auditor
void mx_not_a_dir(char* str); // for cd auditor
void mx_check_flags(char** args, t_cd *cd_flags, int count_flags); // for cd auditor
void mx_error_path(char* str); // for cd auditor
void mx_ch_dir(char *res_path, char* path, t_shell *shell);// for cd auditor
void mx_pgid(st_launch *l_inf); // for signal
int mx_ush_color_font(char** args, t_shell *shell);  // color font for shell
int mx_ush_color_bg(char** args, t_shell *shell); // color background for shell 
void mx_init_color_bg(t_shell *shell); // for color background
void mx_init_color_font(t_shell *shell); // for color font
int mx_error_color_f(t_shell *shell, char** args, char* str); // func for color
int mx_error_color_bg(t_shell *shell, char** args, char* str); // func for color
int mx_check_color(char** array, char* str);// func for color
void mx_help_color_f(t_shell *shell);// func for color
void mx_help_color_bg(t_shell *shell);// func for color
void mx_ush_signals(t_shell *shell); // proba signals
char *mx_sub_replace(char *main_str, char *dst, char *src);
#endif
